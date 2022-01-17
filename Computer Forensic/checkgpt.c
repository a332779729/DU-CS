// checkgtp.c
// gcc -o checkgpt checkgtp.c
// ./checkgpt /path/to/target/disk
//
//Computer Forensics
//ASG2
//ChengZhang
//2019.1.29

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    // open()
#include <unistd.h>    // read()
#include <stdio.h>    // printf()
#include <stdint.h>    // uint16_t
#include <string.h>    // strncmp()

#define LBA_SIZE 512
#define DEFAULT_PARTITION_ENTRY_SIZE 128

uint32_t g_num_partition_entries;
uint32_t g_size_each_partition_entry;

struct gpt_header_info {
    char signature[8];
    char revision[4];
    uint32_t header_size;
    uint32_t crc32_of_header;
    uint32_t reserved_zero;
    uint64_t current_lba; // location of this header copy
    uint64_t backup_lba;
    uint64_t first_usable_lba_for_partition;
    uint64_t last_usable_lba;
    uint16_t disk_guid[8];
    uint64_t start_lba_part_entries;
    uint32_t num_partition_entries;
    uint32_t size_single_partition_entry;
};

union gpt_header {
    char padding[LBA_SIZE];
    struct gpt_header_info info;
};

uint16_t thtobe16(uint16_t x) {
    uint16_t a = x;
    uint16_t b = x;
    a &= 0x00FF;
    a <<= 8;
    b &= 0xFF00;
    b >>= 8;
    return a + b;
}

int print_guid(const uint16_t *guid)
{
    printf("%04X%04X-%04X-%04X-%04X-%04X%04X%04X\n",\
           guid[1], guid[0],
           guid[2], guid[3],
           thtobe16(guid[4]),
           thtobe16(guid[5]),
           thtobe16(guid[6]),
           thtobe16(guid[7]));
    return 0;
}

int print_gpt_header_info(const int fd, off_t offset)
{
    char buf[LBA_SIZE];
    int size_readed;
    union gpt_header *header;
    
    // Reading gpt header information.
    size_readed = pread(fd, buf, LBA_SIZE, offset);
    if (size_readed != LBA_SIZE) {
        printf("Error: read() failed!\n");
        return 2;
    }
    
    header = (union gpt_header *)buf;
    if (strncmp((*header).info.signature, "EFI PART", 8) != 0) {
        printf("Error: Bad signagure!\n");
        return 3;
    }
    
    printf("Disk GUID: ");
    print_guid((*header).info.disk_guid);
    printf("LBA address of first usable LBA for user partitions: %lu (0x%lX)\n",\
           (*header).info.first_usable_lba_for_partition,
           (*header).info.first_usable_lba_for_partition);
    printf("LBA address of last usable LBA: %lu (0x%lX)\n",\
           (*header).info.last_usable_lba,
           (*header).info.last_usable_lba);
    printf("LBA address of starting LBA where partition entries begin: %lu (0x%lX)\n",\
           (*header).info.start_lba_part_entries,
           (*header).info.start_lba_part_entries);
    g_num_partition_entries = (*header).info.num_partition_entries;
    g_size_each_partition_entry = (*header).info.size_single_partition_entry;
    printf("Number of partition entries: %u (0x%X)\n",\
           g_num_partition_entries,
           g_num_partition_entries);
    printf("Size of each partition: %u (0x%X)\n",\
           g_size_each_partition_entry,
           g_size_each_partition_entry);
    
    return 0;
}

struct partition_entry_info {
    uint16_t partition_type_guid[8];
    uint16_t unique_partition_guid[8];
    uint64_t first_lba;
    uint64_t last_lba;
    uint64_t attribute_flags;
    char partition_name[72]; // 36 UTF-16LE code units.
};

union partition_entry {
    char padding[DEFAULT_PARTITION_ENTRY_SIZE];
    struct partition_entry_info info;
};

int print_part_name(const char *part_name)
{
    int i = 0;
    printf("Partition name: ");
    while (i < 36) {
        if (part_name[i * 2] != '\0') {
            printf("%c", part_name[i * 2]);
            i++;
        } else {
            break;
        }
    }
    printf("\n");
    
    return 0;
}

int print_partition_info(const int fd, off_t offset)
{
    int loop;
    char *buf[LBA_SIZE];
    int size_readed;
    union partition_entry *entry;
    
    for (loop = 0; loop < g_num_partition_entries; loop++) {
        size_readed = pread(fd, buf, g_size_each_partition_entry, offset);
        if (size_readed != g_size_each_partition_entry) {
            printf("Error: read() failed!\n");
            return 2;
        }
        offset += g_size_each_partition_entry;
        
        entry = (union partition_entry *)buf;
        
        if ((*entry).info.partition_type_guid[0] == 0) {
            continue;
        }
        
        printf("=====Partition %d=====\n", loop);
        printf("Partition GUID: ");
        print_guid((*entry).info.partition_type_guid);
        printf("First LBA address of the partition: %lu (0x%lX)\n",\
               (*entry).info.first_lba, (*entry).info.first_lba);
        printf("Last LBA address of the partition: %lu (0x%lX)\n",\
               (*entry).info.last_lba, (*entry).info.last_lba);
        printf("Attribute flags: %016lX\n",\
               (*entry).info.attribute_flags);
        print_part_name((*entry).info.partition_name);
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    char *target_disk_path;
    int fd;
    off_t offset;
    int rc;
    
    
    if (argc > 1) {
        target_disk_path = argv[1];
    } else {
        target_disk_path = "./disk.img";
    }
    
    fd = open(target_disk_path, O_RDONLY);
    if (fd < 0) {
        printf("Error: open() failed!\n");
        return 1;
    }
    
    // Skiping MBR table, first LBA.
    offset = LBA_SIZE;
    rc = print_gpt_header_info(fd, offset);
    if (rc != 0)
        return rc;
    
    offset += LBA_SIZE;
    rc = print_partition_info(fd, offset);
    if (rc != 0)
        return rc;
    
    close(fd);
    return 0;
}
