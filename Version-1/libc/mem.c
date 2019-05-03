// #include "mem.h"

// int starting_address;
// int ending_address;
// int max_memory_address;
// int total_elements;

// struct heap_elements {
//     int start_address;
//     int end_address;
//     int size;
//     int reservation;
// };

// struct heap_elements heap[15];

// // Write len copies of val into dest.
// void memset(int *dest, int val, int len)
// {
//     int *temp = (int *)dest;
//     for ( ; len != 0; len--) *temp++ = val;
// }

// /*
//  * This function will take a source and destination and copy n amount
//  * - of bytes from the source to the destination address. 
//  */ 
// void memcpy(unsigned char *source, unsigned char *destination, int bytes) {
//     for (int i = 0; i < bytes; i++) {
//         *(destination + i) = *(source + i);
//     }
// }

// int find_memory_hole(int size) {

//     for (int i = 0; i < 15; i++) {
//         if (heap[i].reservation == 0) {
//             if (heap[i].size >= size || heap[i].size == 0) {
//               return i;
//             }
//         }
//     }
//     return -1;
// }

// void * malloc(int size) {   
//     int hole = find_memory_hole(size);
//     if (hole != -1) {
//         if (heap[hole].start_address == 0) {
//             // if (ending_address <= max_memory_address) {
//                 heap[hole].start_address = ending_address;
//                 ending_address += size;
//                 heap[hole].end_address = ending_address;
//                 heap[hole].size = size;
//                 heap[hole].reservation = 1;
//             // }
//         } else {
//             // heap[hole].size = size;
//             heap[hole].reservation = 1;
//         }
//         memset((void*)heap[hole].start_address, 0, heap[hole].size);
//         return (void*)heap[hole].start_address;
//     } else {
//         kprintf("FREE SOME MEMORY~!\n");
//         kprintf("WE NEED ROOM IN HERE~!\n");
//         return 0;
//     }
// }

// void heap_install() {
    
//     total_elements = 15;
//     starting_address = 0x100000;  // 1 - MB
//     ending_address = 0x100000;    // 1 - MB
//     max_memory_address = 0xEEE00000;  // 4 - GB

//     for (int i = 0; i < total_elements; i++) {
//         heap[i].start_address = 0;
//         heap[i].end_address = 0;
//         heap[i].size = 0;
//         heap[i].reservation = 0;
//     }

//     return;
// }

// void free(void * pointer) {
//     int i = 0;
//     int memory_found = 0;
//     int memory_address = (int)pointer;
    
//     for (i = 0; i < 15; i++) {
//         if (heap[i].start_address == memory_address) {
//             // heap[i].size = 0;
//             heap[i].reservation = 0;
//             memory_found = 1;
//             break;
//         }
//     }

//     if (memory_found == 0)
//         kprintf("Memory could not be free'd (NOT FOUND).\n");
//     else
//         memset((int*)pointer, 0, heap[i].size);

//     return;
// }