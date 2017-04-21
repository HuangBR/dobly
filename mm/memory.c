#include <types.h>
#include "mm.h"

static unsigned short mem_map[PAGING_COUNT] = { 0 };

int get_free_page()
{
    unsigned short *s;
    int idx;
    char *base = (char *) PTE_BASE;
    unsigned int addr;

    for(s = mem_map, idx = 0; s < mem_map + PAGING_COUNT; s++, idx++){
        if(*s == 0){
            *s = 1;
            base += 4 * idx; 
            addr = (unsigned int *)base & 0xfffff000;
            return addr;
        }
    }

    return -1;
}

int alloc_page()
{
    
}

int free_page(unsigned int addr)
{
    if(addr < PAGING_LOW || addr > PAGING_HIGH)
        return -1;

    unsigned int mem_addr = addr >> 12;
    if(mem_map[mem_addr] != 1)
        return -1;

    mem_map[mem_addr]--;

    return 0;
}

int free_page_tables(unsigned int addr, size_t size)
{

}

int copy_page_tables(unsigned int dest, unsigned int src, size_t size)
{

}

unsigned int vir2phy(unsigned int addr)
{

    unsigned int *base;
    unsigned short pgdir_idx;
    unsigned int *pgdir_addr;
    unsigned short pg_table_idx;
    unsigned int *pg_table;
    unsigned int phy_addr;

    base = (unsigned int *)PDT_BASE;
    pgdir_idx = (addr >> 22);
    pgdir_addr = (unsigned int *)(base + 4 * pgdir_idx);

    pg_table_idx = (addr >> 12) & 0x3ff;
    pg_table = (unsigned int *)((char *)(pgdir_addr & 0xfffff000) + pg_table_idx * 4);
    phy_addr = (unsigned int) (pg_table & 0xfffff000);

    return phy_addr;
}
