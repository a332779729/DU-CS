// DiskPreview.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    // open()
#include <unistd.h>    // read()
#include <stdio.h>    // printf()
#include <stdint.h>    // uint16_t
#include <string.h>    // strncmp()
#include <stdlib.h>    // malloc(), free()

uint16_t g_bytes_per_sector;    // +0x0B
uint8_t g_sector_per_cluster;    // +0x0D
uint32_t g_bytes_per_cluster;
uint64_t g_mft_byte_number;
uint16_t g_mft_begin_byte;

struct __attribute__((packed)) part_boot_sector {
    char jmp_instruction[3];
    char oem_id[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    char padding[0x28 - 0x0E];
    uint64_t total_sectors;
    uint64_t mft_begin_cluster_number;
};

int read_partition_boot_sector(int fd, off_t fd_offset)
{
    char *buf[512];
    int size_readed;
    struct part_boot_sector *pbs;
    
    // Reading 512B into buffer.
    size_readed = pread(fd, buf, 512, fd_offset);
    if (size_readed != 512) {
        printf("Error: pread() failed!\n");
        return -1;
    }
    
    pbs = (struct part_boot_sector *)buf;
    g_bytes_per_sector = pbs->bytes_per_sector;
    g_sector_per_cluster = pbs->sectors_per_cluster;
    g_bytes_per_cluster = g_bytes_per_sector * g_sector_per_cluster;
    g_mft_byte_number = pbs->total_sectors * g_bytes_per_sector / 2;
    
    //find mft
    g_mft_begin_byte = pbs->mft_begin_cluster_number * g_bytes_per_cluster;
    
    return 0;
}

struct __attribute__((packed)) mft_record_header {
    char type[4]; // "FILE"
    char padding0[0x14 - 0x04];
    uint16_t first_attribute_offset;
    // 0x00: deleted file; 0x01: normal file;
    // 0x02: deleted folder; 0x03: normal folder;
    uint16_t flags;
};

struct __attribute__((packed)) mft_record_attribute {
    uint32_t type;
    uint16_t length;
};

struct __attribute__((packed)) attribute_filename {
    uint32_t type;
    uint16_t length;
    char padding[0x5A - 0x06];
    char name[32];
};

struct __attribute__((packed)) attribute_data {
    uint32_t type;
    uint16_t length;
    char padding0[0x02];
    char resident_flag; // 0x00 = resident
    char padding1[0x40- 0x09];
    uint8_t data_runs[32];
};

struct data_run {
    uint64_t lcn; // logical cluster number.
    uint64_t length;
    struct data_run *next;
};

int read_one_record(int fd, off_t fd_offset)
{
    char buf[1024];
    int size_readed;
    struct mft_record_header *record_header;
    off_t record_offset;
    struct mft_record_attribute *record_attribute;
    int count_of_name;
    int count_of_data_stream;
    
    char *filename = NULL;
    int name_length;
    off_t cn = 0;
    off_t fbcn = 0;
    off_t off = 0;
    int nds = 0;
    struct data_run *data_runs = NULL;
    int is_resident_file = 1;
    
    size_readed = pread(fd, buf, 1024, fd_offset);
    if (size_readed != 1024) {
        printf("Error: pread() failed!\n");
        return -1;
    }
    
    record_header = (struct mft_record_header *)buf;
    if (strncmp(record_header->type, "FILE", 4) != 0\
        || record_header->flags != 0x01) {
        return 1;
    }
    
    cn = fd_offset / g_bytes_per_cluster + 1;
    
    record_offset = record_header->first_attribute_offset;
    count_of_name = 0;
    count_of_data_stream = 0;
    while (record_offset < 1024) {
        record_attribute = (struct mft_record_attribute *)(buf + record_offset);
        if (record_attribute->type == 0x30) {
            if (count_of_name++ != 0) {
                free(filename);
                filename = NULL;
            }
            
            struct attribute_filename *attr_filename;
            
            attr_filename = (struct attribute_filename *)(buf + record_offset);
            
            // Skipping hiding files.
            if (attr_filename->name[0] == '$')
                break;
            
            name_length = (attr_filename->length - 0x5A) / 2;
            filename = (char *)malloc(name_length);
            memset(filename, 0, name_length);
            
            for (int i = 0; i < name_length; i += 1) {
                filename[i] = attr_filename->name[2 * i];
            }
        } else if (record_attribute->type == 0x80) {
            /* if (filename == NULL) {
             record_offset += record_attribute->length;
             continue;
             } */
            
            if (count_of_data_stream++ != 0) {
                record_offset += record_attribute->length;
                continue;
            }
            
            struct attribute_data *attr_data;
            attr_data = (struct attribute_data *)(buf + record_offset);
            if (attr_data->resident_flag == 0x00) {
                is_resident_file = 1;
                fbcn = cn;
                off = record_offset + 0x18;
            } else if (attr_data->resident_flag == 0x01) {
                is_resident_file = 0;
                off_t attr_data_offset = 0;
                while (1) {
                    uint32_t lcn_bits_count = attr_data->data_runs[attr_data_offset];
                    uint32_t length_bits_count = attr_data->data_runs[attr_data_offset];
                    uint64_t length = 0;
                    uint64_t lcn = 0;
                    off_t j;
                    struct data_run *tmp_data_run;
                    
                    lcn_bits_count &= 0xF0;
                    lcn_bits_count >>= 4;
                    length_bits_count &= 0x0F;
                    
                    for (j = length_bits_count; j > 0; j--) {
                        length |= attr_data->data_runs[j + attr_data_offset];
                        if (j > 1) {
                            length <<= 8;
                        }
                    }
                    for (j = lcn_bits_count; j > 0; j--) {
                        lcn |= attr_data->data_runs[j + length_bits_count + attr_data_offset];
                        if (j > 1) {
                            lcn <<= 8;
                        }
                    }
                    tmp_data_run = (struct data_run *)malloc(sizeof(struct data_run));
                    tmp_data_run->lcn = lcn;
                    tmp_data_run->length = length;
                    tmp_data_run->next = data_runs;
                    
                    if (data_runs == NULL) {
                        fbcn = lcn;
                        off = 0;
                        data_runs = tmp_data_run;
                    } else {
                        data_runs = tmp_data_run;
                    }
                    
                    attr_data_offset += (lcn_bits_count + length_bits_count + 1);
                    if (attr_data->data_runs[attr_data_offset] == 0x00\
                        || attr_data_offset > 32)
                        break;
                }
            }
        }
        
        if (record_attribute->length == 0) {
            break;
        }
        record_offset += record_attribute->length;
    }
    
    if (filename != NULL) {
        for (int i = 0; i < name_length; i++) {
            printf("%c", filename[i]);
        }
        printf(":\n");
        
        if (is_resident_file == 1) {
            nds = count_of_data_stream - 1;
            printf("\t%lu :: %lu(+%lu) :: %d\n", cn, fbcn, off, nds);
        } else {
            printf("\t%lu :: %lu(+%lu) :: ", cn, fbcn, off);
            struct data_run *tmp_data_runs = data_runs;
            while (tmp_data_runs != NULL) {
                printf("(%lu, %lu); ", tmp_data_runs->lcn, tmp_data_runs->length);
                tmp_data_runs = tmp_data_runs->next;
            }
            printf("\n");
        }
        
        while (data_runs != NULL ) {
            struct data_run *tmp = data_runs;
            data_runs = data_runs->next;
            free(tmp);
            data_runs = NULL;
        }
        free(filename);
        filename = NULL;
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    char *target_disk_path;
    int fd;
    off_t fd_offset;
    off_t offset_end_of_mft;
    int main_rc;
    
    if (argc > 1) {
        target_disk_path = argv[1];
    } else {
        target_disk_path = "./USB1.dd";
    }
    
    fd = open(target_disk_path, O_RDONLY);
    if (fd < 0) {
        printf("Error: Open image file failed!\n");
        return -1;
    }
    
    // Reading partition boot sector, which is first sector of image.
    fd_offset = 0;
    read_partition_boot_sector(fd, fd_offset);
    
    // Skipping first 16 reserved sectors.
    // Skipping first 16 reserved file records in MFT.
    fd_offset = g_mft_begin_byte;
    
    // Calculating the bytes used by MFT.
    offset_end_of_mft = g_mft_begin_byte;
    offset_end_of_mft += g_mft_byte_number;
    while (fd_offset < offset_end_of_mft) {
        read_one_record(fd, fd_offset);
        // Operating next file record in MFT.
        fd_offset += 1024;
    }
    
    close(fd);
    return 0;
}
