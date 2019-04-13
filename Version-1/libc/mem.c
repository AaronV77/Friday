#include "mem.h"

// Write len copies of val into dest.
void memset(int *dest, int val, int len)
{
    int *temp = (int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/*
 * This function will take a source and destination and copy n amount
 * - of bytes from the source to the destination address. 
 */ 
void memory_copy(uint8_t *source, uint8_t *destination, int bytes) {
  for (int i = 0; i < bytes; i++) {
    *(destination + i) = *(source + i);
  }
}

// end is defined in the linker script.
// extern int end;
// int placement_address = (int)&end;
// extern page_directory_t *kernel_directory;
// heap_t *kheap=0;

// int kmalloc(int sz, int align, int *phys)
// {
//     // if (kheap != 0)
//     // {
//     //     void *addr = alloc(sz, (u8int)align, kheap);
//     //     if (phys != 0)
//     //     {
//     //         page_t *page = get_page((u32int)addr, 0, kernel_directory);
//     //         *phys = page->frame*0x1000 + ((u32int)addr&0xFFF);
//     //     }
//     //     return (u32int)addr;
//     // }
//     // else
//     // {
//         if (align == 1 && (placement_address & 0xFFFFF000) )
//         {
//             // Align the placement address;
//             placement_address &= 0xFFFFF000;
//             placement_address += 0x1000;
//         }
//         if (phys)
//         {
//             *phys = placement_address;
//         }
//         int tmp = placement_address;
//         placement_address += sz;
//         return tmp;
//     // }
// }

