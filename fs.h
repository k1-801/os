#ifndef __FS_H
#define __FS_H
//Small RamFS driver.
//Directory 0 is the root of the filesystem.
#include "graphics.h"
#include "mem.h"
#include "strfcn.h"
#define MAX_FSENTS	65536
enum fsentType {
TYPE_DIR,    //directory
TYPE_FILE,   //normal file
TYPE_DEVICE, //device connected to the I/O port 
TYPE_NONE,   //the FS entry is null.
};
class fsEnt {
public:
unsigned long ino;
char *addr="";
enum fsentType type=TYPE_NONE;
uint8_t addrToDevs=0;   //if type is device
fsEnt *parentDir=NULL;  //parent directory
char *contents=(char*)0xDEAD;       //if it's a file, there's a contents, otherwise it points to 0xDEAD.
};
fsEnt nullFSEnt;

unsigned long lastFSNullEnt=0;
fsEnt ramfs365[MAX_FSENTS];
void registerDirectory(char *name,fsEnt parentDir)
{
	ramfs365[lastFSNullEnt].parentDir=&parentDir;
	ramfs365[lastFSNullEnt++].addr=strcat(strcat(parentDir.addr,"/"),name);
	
}
void initFS()
{
	nullFSEnt.ino=0;
	nullFSEnt.addr="";
	nullFSEnt.type=TYPE_DIR;
	nullFSEnt.addrToDevs=0;
	nullFSEnt.parentDir=NULL;
	nullFSEnt.contents=(char*)0xDEAD;
	memset(&ramfs365,0,sizeof(fsEnt)*MAX_FSENTS); //null the virtual FS address space
	//register the directories.
	ramfs365[0]=nullFSEnt;
	registerDirectory("",nullFSEnt);
}
#endif
