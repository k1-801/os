#ifndef __365B_H
#define __365B_H
#include <stdint.h>
#define E365B_MAGIC 0x365B
struct sect365b {
	unsigned char sectname[8]; //Section name, not null-terminated
	char *sectData; //Section data.
	struct sect365b *nextSect;
};
typedef struct bin_365B_header {
	unsigned char smagic[4]; //Needs to be "365B", not null-terminated
	uint16_t version; //version
	/*
	 * Version code is like that:
	 * Version 1.0: 0x0100
	 * Version 1.2: 0x0120
	 * Version 2.9: 0x0290
	 * Version 3.8.5: 0x0385
	 * and more...
	 * Now the section info.
	 * In any section strings starts with S.
	*/
}Hdr365B;
#endif
