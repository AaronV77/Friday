
#ifndef __DEVICE_H_
#define __DEVICE_H_

#include "../libc/mem.h"
#include "../libc/string.h"

struct __fs_t;

typedef enum __device_type {
	DEVICE_UNKNOWN = 0,
	DEVICE_CHAR = 1,
	DEVICE_BLOCK = 2,
} device_type;


typedef struct __device_t {
	char *name;
	int unique_id;
	device_type dev_type;
	struct __fs_t *fs;
	int (*read)(char* buffer, int offset , int len, void* dev);
	int (*write)(char *buffer, int offset, int len, void* dev);
	void *priv;
} device_t;

extern void device_init();
extern int device_add(device_t* dev);

#endif
