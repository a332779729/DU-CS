// RamPreview.c
//
//Computer Forensics
//ASG4
//ChengZhang
//2019.2.22

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>	// open()
#include <unistd.h>	// pread()
#include <stdio.h>	// printf()
#include <stdint.h>	// uint16_t
#include <string.h>	// strncmp()
#include <stdlib.h>	// malloc()d

#define FIRST_PROC_DESC_ADDR 0x00660BC0
#define DEFAULT_MEM_OFFSET 0xC0000000

//data struct and memory struct
typedef struct __attribute__((packed)) {
	char padding0[0x7C];
	uint32_t addr_next_proc_desc;
	uint32_t addr_prev_proc_desc;
	uint32_t addr_mem_mapping;
	char padding1[0xA8 - 0x88];
	uint32_t pid;
	char padding2[0xB0 - 0xAC];
	uint32_t addr_parent_proc_desc;
	char padding3[0x14C - 0xB4];
	uint32_t user_id;
	char padding4[0x194 - 0x150];
	char name[16];
} proc_desc;

typedef struct __attribute__((packed)) {
	uint32_t addr_first_virt_mem_area;
} mem_mapping;

typedef struct __attribute__((packed)) {
	char padding0[4];
	uint32_t addr_begin_mem;
	uint32_t addr_end_mem;
	uint32_t addr_next_virt_mem_area;
} virt_mem_area;

// it is ppid
uint32_t get_parent_proc_pid(int fd, off_t addr_parent_proc_desc)
{
    int nbyte_readed;
    size_t size_proc_desc = sizeof(proc_desc);
    proc_desc *buf_parent_proc_desc = malloc(size_proc_desc);
    
    nbyte_readed = pread(fd, buf_parent_proc_desc, size_proc_desc, addr_parent_proc_desc);
    if (nbyte_readed != size_proc_desc) {
        printf("Error: pread() failure!\n");
        return -2;
    }
    
    free(buf_parent_proc_desc);
    return buf_parent_proc_desc->pid;
}

//this is vmz
uint32_t get_vmz(int fd, off_t addr_mem_mapping)
{
    int nbyte_readed;
    size_t size_mem_mapping = sizeof(mem_mapping);
    size_t size_virt_mem_area = sizeof(virt_mem_area);
    mem_mapping *buf_mem_mapping = malloc(size_mem_mapping);
    virt_mem_area *buf_virt_mem_area = malloc(size_virt_mem_area);
    off_t addr_virt_mem_area = 0;
    uint32_t vmz = 0;
    
    nbyte_readed = pread(fd, buf_mem_mapping, size_mem_mapping, addr_mem_mapping);
    if (nbyte_readed != size_mem_mapping) {
        printf("Error: pread() failure!\n");
        return -2;
    }
    
    addr_virt_mem_area = buf_mem_mapping->addr_first_virt_mem_area;
    addr_virt_mem_area -= DEFAULT_MEM_OFFSET;
    
    while (1) {
        nbyte_readed = pread(fd, buf_virt_mem_area, size_virt_mem_area, addr_virt_mem_area);
        if (nbyte_readed != size_virt_mem_area) {
            printf("Error: pread() failure!\n");
            return -2;
        }
        
        vmz += buf_virt_mem_area->addr_end_mem - buf_virt_mem_area->addr_begin_mem;
        
        addr_virt_mem_area = buf_virt_mem_area->addr_next_virt_mem_area;
        if (addr_virt_mem_area == 0) {
            break;
        } else {
            addr_virt_mem_area -= DEFAULT_MEM_OFFSET;
        }
    }
    
    free(buf_mem_mapping);
    free(buf_virt_mem_area);
    return vmz;
}

//read descriptor
int read_proc_desc(int fd, off_t first_proc_desc_offset)
{
	int nbyte_readed = 0;
	size_t size_proc_desc = sizeof(proc_desc);
	size_t size_mem_mapping = sizeof(mem_mapping);
	size_t size_virt_mem_area = sizeof(virt_mem_area);

	off_t addr_next_proc_desc = first_proc_desc_offset;
	off_t addr_end = first_proc_desc_offset;

	proc_desc *buf_proc_desc = malloc(size_proc_desc);
	// mem_mapping *buf_mem_mapping = malloc(size_mem_mapping);
	// virt_mem_area *buf_virt_mem_area = malloc(size_virt_mem_area);
	
    //print title
	printf("PID \tPPID \tUID \tVMZ \tTASK \tCOMM\n");

	do {
		nbyte_readed = pread(fd, buf_proc_desc, size_proc_desc, addr_next_proc_desc);
		if (nbyte_readed != size_proc_desc) {
			printf("Error: pread() failure!\n");
			return -2;
		}
        size_t addr_mem_mapping = buf_proc_desc->addr_mem_mapping;
        size_t vmz = 0;
        if (addr_mem_mapping != 0) {
            addr_mem_mapping -= DEFAULT_MEM_OFFSET;
            vmz = get_vmz(fd, addr_mem_mapping);
        }
        //print the all
		printf("%u \t%u \t%u \t%u \t%lx \t\t%s\n",\
			buf_proc_desc->pid,\
            get_parent_proc_pid(fd,buf_proc_desc->addr_parent_proc_desc-0xC0000000U),\
			buf_proc_desc->user_id,\
            vmz/1024, \
			addr_next_proc_desc + DEFAULT_MEM_OFFSET,\
			buf_proc_desc->name);

		addr_next_proc_desc = buf_proc_desc->addr_next_proc_desc - 0x7C;
		addr_next_proc_desc -= DEFAULT_MEM_OFFSET;
	} while (addr_next_proc_desc != addr_end);

	return 0;
}

//main
int main(int argc, char *argv[])
{
	char *target_ram_dump_path;
	int fd;
	off_t fd_offset;
	int main_rc;

	if (argc > 1 ) {
		target_ram_dump_path = argv[1];
	} else {
		target_ram_dump_path = "./challenge.mem";
	}

    //open it
	fd = open(target_ram_dump_path, O_RDONLY);
	if (fd < 0) {
		printf("Error: open() failure!\n");
		return -1;
	}

	fd_offset = FIRST_PROC_DESC_ADDR;

	main_rc = read_proc_desc(fd, fd_offset);

	close(fd);
	return main_rc;
}
