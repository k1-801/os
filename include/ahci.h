#ifndef __AHCI_H
#define __AHCI_H

/*#include "graphics.h"
#include "mem.h"
#include "panic.h"
#include <stdarg.h>
#define	SATA_SIG_ATA	0x00000101	// SATA drive
#define	SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define	SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define	SATA_SIG_PM	0x96690101	// Port multiplier
#define	AHCI_BASE	0x400000	// 4M
#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08
 
 
typedef enum
{
	FIS_TYPE_REG_H2D	= 0x27,	// Register FIS - host to device
	FIS_TYPE_REG_D2H	= 0x34,	// Register FIS - device to host
	FIS_TYPE_DMA_ACT	= 0x39,	// DMA activate FIS - device to host
	FIS_TYPE_DMA_SETUP	= 0x41,	// DMA setup FIS - bidirectional
	FIS_TYPE_DATA		= 0x46,	// Data FIS - bidirectional
	FIS_TYPE_BIST		= 0x58,	// BIST activate FIS - bidirectional
	FIS_TYPE_PIO_SETUP	= 0x5F,	// PIO setup FIS - device to host
	FIS_TYPE_DEV_BITS	= 0xA1,	// Set device bits FIS - device to host
} FIS_TYPE;
typedef struct tagFIS_REG_H2D
{
	// dword 0
	byte	fis_type;	// FIS_TYPE_REG_H2D
 
	byte	pmport:4;	// Port multiplier
	byte	rsv0:3;		// Reserved
	byte	c:1;		// 1: Command, 0: Control
 
	byte	command;	// Command register
	byte	featurel;	// Feature register, 7:0
 
	// dword 1
	byte	lba0;		// LBA low register, 7:0
	byte	lba1;		// LBA mid register, 15:8
	byte	lba2;		// LBA high register, 23:16
	byte	device;		// Device register
 
	// dword 2
	byte	lba3;		// LBA register, 31:24
	byte	lba4;		// LBA register, 39:32
	byte	lba5;		// LBA register, 47:40
	byte	featureh;	// Feature register, 15:8
 
	// dword 3
	byte	countl;		// Count register, 7:0
	byte	counth;		// Count register, 15:8
	byte	icc;		// Isochronous command completion
	byte	control;	// Control register
 
	// dword 4
	byte	rsv1[4];	// Reserved
} FIS_REG_H2D;
typedef struct tagFIS_REG_D2H
{
	// dword 0
	byte	fis_type;    // FIS_TYPE_REG_D2H
 
	byte	pmport:4;    // Port multiplier
	byte	rsv0:2;      // Reserved
	byte	i:1;         // Interrupt bit
	byte	rsv1:1;      // Reserved
 
	byte	status;      // Status register
	byte	error;       // Error register
 
	// dword 1
	byte	lba0;        // LBA low register, 7:0
	byte	lba1;        // LBA mid register, 15:8
	byte	lba2;        // LBA high register, 23:16
	byte	device;      // Device register
 
	// dword 2
	byte	lba3;        // LBA register, 31:24
	byte	lba4;        // LBA register, 39:32
	byte	lba5;        // LBA register, 47:40
	byte	rsv2;        // Reserved
 
	// dword 3
	byte	countl;      // Count register, 7:0
	byte	counth;      // Count register, 15:8
	byte	rsv3[2];     // Reserved
 
	// dword 4
	byte	rsv4[4];     // Reserved
} FIS_REG_D2H;
typedef struct tagFIS_DATA
{
	// dword 0
	byte	fis_type;	// FIS_TYPE_DATA
 
	byte	pmport:4;	// Port multiplier
	byte	rsv0:4;		// Reserved
 
	byte	rsv1[2];	// Reserved
 
	// dword 1 ~ N
	dword	data[1];	// Payload
} FIS_DATA;
typedef struct tagFIS_PIO_SETUP
{
	// dword 0
	byte	fis_type;	// FIS_TYPE_PIO_SETUP
 
	byte	pmport:4;	// Port multiplier
	byte	rsv0:1;		// Reserved
	byte	d:1;		// Data transfer direction, 1 - device to host
	byte	i:1;		// Interrupt bit
	byte	rsv1:1;
 
	byte	status;		// Status register
	byte	error;		// Error register
 
	// dword 1
	byte	lba0;		// LBA low register, 7:0
	byte	lba1;		// LBA mid register, 15:8
	byte	lba2;		// LBA high register, 23:16
	byte	device;		// Device register
 
	// dword 2
	byte	lba3;		// LBA register, 31:24
	byte	lba4;		// LBA register, 39:32
	byte	lba5;		// LBA register, 47:40
	byte	rsv2;		// Reserved
 
	// dword 3
	byte	countl;		// Count register, 7:0
	byte	counth;		// Count register, 15:8
	byte	rsv3;		// Reserved
	byte	e_status;	// New value of status register
 
	// dword 4
	word	tc;		// Transfer count
	byte	rsv4[2];	// Reserved
} FIS_PIO_SETUP;
typedef struct tagFIS_DMA_SETUP
{
	// dword 0
	byte	fis_type;	// FIS_TYPE_DMA_SETUP
 
	byte	pmport:4;	// Port multiplier
	byte	rsv0:1;		// Reserved
	byte	d:1;		// Data transfer direction, 1 - device to host
	byte	i:1;		// Interrupt bit
	byte	a:1;            // Auto-activate. Specifies if DMA Activate FIS is needed
 
        byte    rsved[2];       // Reserved
 
	//dword 1&2
 
        qword   DMAbufferID;    // DMA Buffer Identifier. Used to Identify DMA buffer in host memory. SATA Spec says host specific and not in Spec. Trying AHCI spec might work.
 
        //dword 3
        dword   rsvd;           //More reserved
 
        //dword 4
        dword   DMAbufOffset;   //byte offset into buffer. First 2 bits must be 0
 
        //dword 5
        dword   TransferCount;  //Number of bytes to transfer. Bit 0 must be 0
 
        //dword 6
        dword   resvd;          //Reserved
 
} FIS_DMA_SETUP;
typedef volatile struct tagHBA_MEM
{
	// 0x00 - 0x2B, Generic Host Control
	dword	cap;		// 0x00, Host capability
	dword	ghc;		// 0x04, Global host control
	dword	is;		// 0x08, Interrupt status
	dword	pi;		// 0x0C, Port implemented
	dword	vs;		// 0x10, Version
	dword	ccc_ctl;	// 0x14, Command completion coalescing control
	dword	ccc_pts;	// 0x18, Command completion coalescing ports
	dword	em_loc;		// 0x1C, Enclosure management location
	dword	em_ctl;		// 0x20, Enclosure management control
	dword	cap2;		// 0x24, Host capabilities extended
	dword	bohc;		// 0x28, BIOS/OS handoff control and status
 
	// 0x2C - 0x9F, Reserved
	byte	rsv[0xA0-0x2C];
 
	// 0xA0 - 0xFF, Vendor specific registers
	byte	vendor[0x100-0xA0];
 
	// 0x100 - 0x10FF, Port control registers
	HBA_PORT	ports[1];	// 1 ~ 32
} HBA_MEM;
 
typedef volatile struct tagHBA_PORT
{
	dword	clb;		// 0x00, command list base address, 1K-byte aligned
	dword	clbu;		// 0x04, command list base address upper 32 bits
	dword	fb;		// 0x08, FIS base address, 256-byte aligned
	dword	fbu;		// 0x0C, FIS base address upper 32 bits
	dword	is;		// 0x10, interrupt status
	dword	ie;		// 0x14, interrupt enable
	dword	cmd;		// 0x18, command and status
	dword	rsv0;		// 0x1C, Reserved
	dword	tfd;		// 0x20, task file data
	dword	sig;		// 0x24, signature
	dword	ssts;		// 0x28, SATA status (SCR0:SStatus)
	dword	sctl;		// 0x2C, SATA control (SCR2:SControl)
	dword	serr;		// 0x30, SATA error (SCR1:SError)
	dword	sact;		// 0x34, SATA active (SCR3:SActive)
	dword	ci;		// 0x38, command issue
	dword	sntf;		// 0x3C, SATA notification (SCR4:SNotification)
	dword	fbs;		// 0x40, FIS-based switch control
	dword	rsv1[11];	// 0x44 ~ 0x6F, Reserved
	dword	vendor[4];	// 0x70 ~ 0x7F, vendor specific
} HBA_PORT;
typedef volatile struct tagHBA_FIS
{
	// 0x00
	FIS_DMA_SETUP	dsfis;		// DMA Setup FIS
	byte		pad0[4];
 
	// 0x20
	FIS_PIO_SETUP	psfis;		// PIO Setup FIS
	byte		pad1[12];
 
	// 0x40
	FIS_REG_D2H	rfis;		// Register – Device to Host FIS
	byte		pad2[4];
 
	// 0x58
	FIS_DEV_BITS	sdbfis;		// Set Device Bit FIS
 
	// 0x60
	byte		ufis[64];
 
	// 0xA0
	byte		rsv[0x100-0xA0];
} HBA_FIS;
typedef struct tagHBA_CMD_HEADER
{
	// DW0
	byte	cfl:5;		// Command FIS length in dwordS, 2 ~ 16
	byte	a:1;		// ATAPI
	byte	w:1;		// Write, 1: H2D, 0: D2H
	byte	p:1;		// Prefetchable
 
	byte	r:1;		// Reset
	byte	b:1;		// BIST
	byte	c:1;		// Clear busy upon R_OK
	byte	rsv0:1;		// Reserved
	byte	pmp:4;		// Port multiplier port
 
	word	prdtl;		// Physical region descriptor table length in entries
 
	// DW1
	volatile
	dword	prdbc;		// Physical region descriptor byte count transferred
 
	// DW2, 3
	dword	ctba;		// Command table descriptor base address
	dword	ctbau;		// Command table descriptor base address upper 32 bits
 
	// DW4 - 7
	dword	rsv1[4];	// Reserved
} HBA_CMD_HEADER;
typedef struct tagHBA_CMD_TBL
{
	// 0x00
	byte	cfis[64];	// Command FIS
 
	// 0x40
	byte	acmd[16];	// ATAPI command, 12 or 16 bytes
 
	// 0x50
	byte	rsv[48];	// Reserved
 
	// 0x80
	HBA_PRDT_ENTRY	prdt_entry[1];	// Physical region descriptor table entries, 0 ~ 65535
} HBA_CMD_TBL;
 
typedef struct tagHBA_PRDT_ENTRY
{
	dword	dba;		// Data base address
	dword	dbau;		// Data base address upper 32 bits
	dword	rsv0;		// Reserved
 
	// DW3
	dword	dbc:22;		// byte count, 4M max
	dword	rsv1:9;		// Reserved
	dword	i:1;		// Interrupt on completion
} HBA_PRDT_ENTRY;
char *ahci_log;
void trace_ahci(char *str,...)
{
	return;
}
void probe_port(HBA_MEM *abar)
{
	// Search disk in impelemented ports
	dword pi = abar->pi;
	int i = 0;
	while (i<32)
	{
		if (pi & 1)
		{
			int dt = check_type(&abar->ports[i]);
			if (dt == AHCI_DEV_SATA)
			{
				trace_ahci("SATA drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SATAPI)
			{
				trace_ahci("SATAPI drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SEMB)
			{
				trace_ahci("SEMB drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_PM)
			{
				trace_ahci("PM drive found at port %d\n", i);
			}
			else
			{
				trace_ahci("No drive found at port %d\n", i);
			}
		}
 
		pi >>= 1;
		i ++;
	}
}
 
// Check device type
static int check_type(HBA_PORT *port)
{
	dword ssts = port->ssts;
 
	byte ipm = (ssts >> 8) & 0x0F;
	byte det = ssts & 0x0F;
 
	if (det != HBA_PORT_DET_PRESENT)	// Check drive status
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;
 
	switch (port->sig)
	{
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;
	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;
	case SATA_SIG_PM:
		return AHCI_DEV_PM;
	default:
		return AHCI_DEV_SATA;
	}
}
// Start command engine
void start_cmd(HBA_PORT *port)
{
	// Wait until CR (bit15) is cleared
	while (port->cmd & HBA_PxCMD_CR);
 
	// Set FRE (bit4) and ST (bit0)
	port->cmd |= HBA_PxCMD_FRE;
	port->cmd |= HBA_PxCMD_ST; 
}
 
// Stop command engine
void stop_cmd(HBA_PORT *port)
{
	// Clear ST (bit0)
	port->cmd &= ~HBA_PxCMD_ST;
 
	// Wait until FR (bit14), CR (bit15) are cleared
	while(1)
	{
		if (port->cmd & HBA_PxCMD_FR)
			continue;
		if (port->cmd & HBA_PxCMD_CR)
			continue;
		break;
	}
 
	// Clear FRE (bit4)
	port->cmd &= ~HBA_PxCMD_FRE;
}
void port_rebase(HBA_PORT *port, int portno)
{
	stop_cmd(port);	// Stop command engine
 
	// Command list offset: 1K*portno
	// Command list entry size = 32
	// Command list entry maxim count = 32
	// Command list maxim size = 32*32 = 1K per port
	port->clb = AHCI_BASE + (portno<<10);
	port->clbu = 0;
	memset((void*)(port->clb), 0, 1024);
 
	// FIS offset: 32K+256*portno
	// FIS entry size = 256 bytes per port
	port->fb = AHCI_BASE + (32<<10) + (portno<<8);
	port->fbu = 0;
	memset((void*)(port->fb), 0, 256);
 
	// Command table offset: 40K + 8K*portno
	// Command table size = 256*32 = 8K per port
	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)(port->clb);
	for (int i=0; i<32; i++)
	{
		cmdheader[i].prdtl = 8;	// 8 prdt entries per command table
					// 256 bytes per command table, 64+16+48+16*8
		// Command table offset: 40K + 8K*portno + cmdheader_index*256
		cmdheader[i].ctba = AHCI_BASE + (40<<10) + (portno<<13) + (i<<8);
		cmdheader[i].ctbau = 0;
		memset((void*)cmdheader[i].ctba, 0, 256);
	}
 
	start_cmd(port);	// Start command engine
}
// Find a free command list slot
int find_cmdslot(HBA_PORT *port)
{
	// If not set in SACT and CI, the slot is free
	dword slots = (m_port->sact | m_port->ci);
	for (int i=0; i<cmdslots; i++)
	{
		if ((slots&1) == 0)
			return i;
		slots >>= 1;
	}
	trace_ahci("Cannot find free command list entry\n");
	return -1;
}
bool read(HBA_PORT *port, dword startl, dword starth, dword count, word *buf)
{
	port->is = (dword)-1;		// Clear pending interrupt bits
	int spin = 0; // Spin lock timeout counter
	int slot = find_cmdslot(port);
	if (slot == -1)
		return false;
 
	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D)/sizeof(dword);	// Command FIS size
	cmdheader->w = 0;		// Read from device
	cmdheader->prdtl = (word)((count-1)>>4) + 1;	// PRDT entries count
 
	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) +
 		(cmdheader->prdtl-1)*sizeof(HBA_PRDT_ENTRY));
 
	// 8K bytes (16 sectors) per PRDT
	for (int i=0; i<cmdheader->prdtl-1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (dword)buf;
		cmdtbl->prdt_entry[i].dbc = 8*1024;	// 8K bytes
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4*1024;	// 4K words
		count -= 16;	// 16 sectors
	}
	// Last entry
	cmdtbl->prdt_entry[i].dba = (dword)buf;
	cmdtbl->prdt_entry[i].dbc = count<<9;	// 512 bytes per sector
	cmdtbl->prdt_entry[i].i = 1;
 
	// Setup command
	FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);
 
	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = ATA_CMD_READ_DMA_EX;
 
	cmdfis->lba0 = (byte)startl;
	cmdfis->lba1 = (byte)(startl>>8);
	cmdfis->lba2 = (byte)(startl>>16);
	cmdfis->device = 1<<6;	// LBA mode
 
	cmdfis->lba3 = (byte)(startl>>24);
	cmdfis->lba4 = (byte)starth;
	cmdfis->lba5 = (byte)(starth>>8);
 
	cmdfis->countl = LObyte(count);
	cmdfis->counth = HIbyte(count);
 
	// The below loop waits until the port is no longer busy before issuing a new command
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		panic("AHCI: Port is hung\n");
		return false;
	}
 
	port->ci = 1<<slot;	// Issue command
 
	// Wait for completion
	while (1)
	{
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		if ((port->ci & (1<<slot)) == 0) 
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			trace_ahci("Read disk error\n");
			return false;
		}
	}
 
	// Check again
	if (port->is & HBA_PxIS_TFES)
	{
		panic("AHCI: Read disk error\n");
		return false;
	}
 
	return true;
}*/
#endif
