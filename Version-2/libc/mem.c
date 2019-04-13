#include "mem.h"

int starting_address;
int ending_address;
int max_memory_address;
int total_elements;

struct heap_elements {
    int start_address;
    int end_address;
    int size;
    int reservation;
};

struct heap_elements heap[500];

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
void memory_copy(unsigned char *source, unsigned char *destination, int bytes) {
    for (int i = 0; i < bytes; i++) {
        *(destination + i) = *(source + i);
    }
}

void * malloc(int size) {   
    int hole = find_memory_hole();
    if (hole != -1) {
        if (heap[hole].start_address == 0) {
            heap[hole].start_address = ending_address;
            ending_address += size;
            heap[hole].end_address = ending_address;
            heap[hole].size = size;
            heap[hole].reservation = 1;
        } else {
            heap[hole].size = size;
            heap[hole].reservation = 1;
        }
        return (void*)heap[hole].start_address;
    } else {
        print("FREE SOME MEMORY~!\n");
        print("WE NEED ROOM IN HERE~!\n");
        return 0;
    }
}

void heap_install(int kernel_start, int kernel_end) {

    starting_address = kernel_start;
    // ending_address = kernel_end;
    int random = kernel_end;
    random += 2;
    ending_address = 0x100000;
    total_elements = 25;

    for (int i = 0; i < total_elements; i++) {
        heap[i].start_address = 0;
        heap[i].end_address = 0;
        heap[i].size = 0;
        heap[i].reservation = 0;
    }

    return;
}

int find_memory_hole() {

    for (int i = 0; i < total_elements; i++) {
        if (heap[i].reservation == 0)
            return i;
    }

    return -1;
}

void free(int * pointer) {

    int memory_found = 0;
    int memory_address = (int)pointer;
    
    for (int i = 0; i < total_elements; i++) {
        if (heap[i].start_address == memory_address) {
            heap[i].size = 0;
            heap[i].reservation = 0;
            memory_found = 1;
            break;
        }
    }

    if (memory_found == 0) {
        print("Memory could not bee free'd (NOT FOUND).\n");
    }

    return;
}