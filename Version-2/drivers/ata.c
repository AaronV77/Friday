#include "ata.h"

#define ATA_PRIMARY_IO 0x1F0
#define ATA_SECONDARY_IO 0x170
uint8_t ata_pm = 0; /* Primary master exists? */
int *ide_buf = 0;

void ide_select_drive(int bus, int i)
{
	if(bus == ATA_PRIMARY)
		if(i == ATA_MASTER)
			port_byte_out(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else 
			port_byte_out(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xB0);
	else
		if(i == ATA_MASTER)
			port_byte_out(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else 
			port_byte_out(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xB0);
}

int ide_identify(int bus, int drive)
{
	int io = 0;
	ide_select_drive(bus, drive);
	if (bus == ATA_PRIMARY) 
		io = ATA_PRIMARY_IO;	// IO = 496
	else 
		io = ATA_SECONDARY_IO;	// IO = 368

	/* ATA specs say these values must be zero before sending IDENTIFY */
	port_byte_out(io + ATA_REG_SECCOUNT0, 0);
	port_byte_out(io + ATA_REG_LBA0, 0);
	port_byte_out(io + ATA_REG_LBA1, 0);
	port_byte_out(io + ATA_REG_LBA2, 0);

	/* Now, send IDENTIFY */
	port_byte_out(io + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
	// mprint("Sent IDENTIFY\n");
	
	/* Now, read status port */
	int status = port_byte_in(io + ATA_REG_STATUS);
    print("HERE: ");
    print_number(status);
    print("\n");

	if(status)
	{
// 		/* Now, poll untill BSY is clear. */
		while(port_byte_in(io + ATA_REG_STATUS) & ATA_SR_BSY != 0) ;
pm_stat_read:		status = port_byte_in(io + ATA_REG_STATUS);
		if(status & ATA_SR_ERR)
		{
			print("ERROR-1\n");
			return 0;
		}
		while(!(status & ATA_SR_DRQ)) 
			goto pm_stat_read;

		for(int i = 0; i<256; i++)
		{
			*(int *)(ide_buf + i*2) = port_word_in(io + ATA_REG_DATA);
		}
		print("We made it out?\n");
	}
	return 1;
}

void ata_probe()
{	
	if(ide_identify(ATA_PRIMARY, ATA_MASTER))
	{
		ata_pm = 1;
		device_t *dev = (device_t *)malloc(sizeof(device_t));
		ide_private_data *priv = (ide_private_data *)malloc(sizeof(ide_private_data));

		/* Now, process the IDENTIFY data */
		/* Model goes from W#27 to W#46 */
		char *str = (char *)malloc(40);
		for(int i = 0; i < 40; i += 2)
		{
			str[i] = ide_buf[ATA_IDENT_MODEL + i + 1];
			str[i + 1] = ide_buf[ATA_IDENT_MODEL + i];
		}

		dev->name = str;
		dev->unique_id = 32;
		dev->dev_type = DEVICE_BLOCK;
		priv->drive = (ATA_PRIMARY << 1) | ATA_MASTER;
		dev->priv = priv;
		// dev->read = ata_read;
		
		device_add(dev);
		print("Device: ");
		print(dev->name);
		print("\n");
	}
	// ide_identify(ATA_PRIMARY, ATA_SLAVE);
}

void ata_init()
{
	print("Checking for ATA drives\n");
	ide_buf = (int *)malloc(512);
	// set_int(ATA_PRIMARY_IRQ, ide_primary_irq);
	// set_int(ATA_SECONDARY_IRQ, ide_secondary_irq);
	ata_probe();
	// _kill();
}
