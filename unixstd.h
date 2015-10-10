#ifndef __UNIXSTD_H
#define __UNIXSTD_H
#include "panic.h"
void abort(){
panic("abort() was called.");
}
#endif
