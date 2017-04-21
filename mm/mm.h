#ifndef _MM_H
#define _MM_H

#define PDT_BASE 0x5000
#define PTE_BASE 0x6000

#define PAGE_SIZE 4096

#define PAGING_LOW 0x200000
#define PAGING_HIGH 0xA00000
#define PAGING_MEM (PAGING_HIGH - PAGING_LOW)
#define PAGING_COUNT (PAGING_MEM / PAGE_SIZE)

int get_free_page();

int alloc_page();

int free_page(unsigned int addr);

int free_page_tables(unsigned int addr, size_t size);

int copy_page_tables(unsigned int dest, const unsigned int src, size_t size);

#endif /* _MM_H */

