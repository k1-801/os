#pragma once

#ifndef STDINCLUDE_H
#define SDTINCLUDE_H

#if defined(__linux__)
#error "Compiling is not allowed without the cross-compiler"
#endif

#define CONCAT(a,b) a##b
#define QUOTATE(a) #a

#if __STDC_HOSTED__
#warning "__STDC_HOSTED__ is defined, fixing"
#undef __STDC_HOSTED__
#define __STDC_HOSTED__ 0
#endif

#ifndef DISTNAME
#warning DISTNAME is not set, setting to "Unknown"
#define DISTNAME "Unknown"
#endif

#endif