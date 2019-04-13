#ifndef PAGING_H
#define PAGING_H

#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/common.h"
#include "../libc/mem.h"

typedef struct page
{
    int present    : 1;   // Page present in memory
    int rw         : 1;   // Read-only if clear, readwrite if set
    int user       : 1;   // Supervisor level only if clear
    int accessed   : 1;   // Has the page been accessed since last refresh?
    int dirty      : 1;   // Has the page been written to since last refresh?
    int unused     : 7;   // Amalgamation of unused and reserved bits
    int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    /**
       Array of pointers to pagetables.
    **/
    page_table_t *tables[1024];
    /**
       Array of pointers to the pagetables above, but gives their *physical*
       location, for loading into the CR3 register.
    **/
    int tablesPhysical[1024];

    /**
       The physical address of tablesPhysical. This comes into play
       when we get our kernel heap allocated and the directory
       may be in a different location in virtual memory.
    **/
    int physicalAddr;
} page_directory_t;

/**
   Sets up the environment, page directories etc and
   enables paging.
**/
void paging_install();

/**
   Causes the specified page directory to be loaded into the
   CR3 register.
**/
void switch_page_directory(page_directory_t *new);

/**
   Retrieves a pointer to the page required.
   If make == 1, if the page-table in which this page should
   reside isn't created, create it!
**/
page_t *get_page(int address, int make, page_directory_t *dir);


// void page_fault(registers_t *regs);
page_directory_t *clone_directory(page_directory_t *src);

#endif
