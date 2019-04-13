#include "devices.h"

device_t *devices = 0;
int lastid = 0;

void device_init()
{
	devices = (device_t*)malloc(64*sizeof(device_t));
	// memset(devices, 0, 64*sizeof(device_t));
	lastid = 0;
	print("Device Manager initialized.\n");
}

int device_add(device_t* dev)
{
	devices[lastid] = *dev;
	// mprint("Registered Device %s (%d) as Device#%d\n", dev->name, dev->unique_id, lastid);
	lastid++;
	return lastid-1;
}