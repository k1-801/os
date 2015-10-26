#pragma once
#ifndef TSTREAM_H
#define TSTREAM_H

/**
 * k1-801's file abstraction
 * Basic template struct for text stream
 * Struct fields are pointers to the action functions
 */

#include "stdinclude.h"
// C
#include <stdint.h>

typedef struct tstream
{
    void* _obj;
    int16_t(*getc )(struct tstream*);
    int16_t(*putc )(struct tstream*, char);
    int64_t(*gets )(struct tstream*,       char*, uint64_t);
    int64_t(*puts )(struct tstream*, const char*, uint64_t);
    int64_t(*size )(struct tstream*);
    int64_t(*pos  )(struct tstream*);
    int64_t(*seek )(struct tstream*, int64_t, uint8_t);
    int8_t (*close)(struct tstream*);
} tstream;

// Get one character from the file carry position; returns that character or -1 on error
int16_t ts_getc(tstream*);

// Write one character to the carry position; returns written character or -1 on error
int16_t ts_putc(tstream*, char);

// Read a few bytes to the string buffer; returns number of read bytes (0 may mean that an error has occured)
int64_t ts_gets(tstream*,       char*, uint64_t);

// Write a few bytes to the file; returns number of written bytes (0 may mean that an error has occured)
int64_t ts_puts(tstream*, const char*, uint64_t);

// Returns current file size on disk
int64_t ts_size(tstream*);

// Returns current carry position
int64_t ts_pos(tstream*);

// Set carry position (third parameter means where to count from: 0 - beginning of the file (positive only), 1 - current carry position, 2 - end of the file(negative only)); returns new carry position or -1 on error
int64_t ts_seek(tstream*, int64_t, uint8_t);

// Just close that file
int8_t ts_close(tstream*);

// Default functions
// Will be set automatically if NULL in struct, but getc and putc are set
int64_t ts_gets_default(tstream*,       char*, uint64_t);
int64_t ts_puts_default(tstream*, const char*, uint64_t);

#endif