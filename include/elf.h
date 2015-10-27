#pragma once

#ifndef ELF_H
#define ELF_H

#include <stdint.h>

#define EI_IDENT	16

typedef uint32_t    Elf32_Addr;
typedef uint16_t    Elf32_Half;
typedef uint32_t    Elf32_Off;
typedef signed long Elf32_Sword;
typedef uint32_t    Elf32_Word;

typedef enum
{
    ET_NONE=0,
    ET_REL =1,
    ET_EXEC=2,
    ET_DYN =3,
    ET_CORE=4,
    ET_LOPROC=0xff00,
    ET_HIPROC=0xffff,
} etype;

typedef enum
{
    EM_NONE,
    EM_M32,
    EM_SPARC,
    EM_386,
    EM_68K,
    EM_88K,
    EM_860 =7,
    EM_MIPS=8
} emachine;

typedef enum
{
    EV_NONE,
    EV_CURRENT
} eversion;

typedef enum
{
    EI_MAG0,
    EI_MAG1,
    EI_MAG2,
    EI_MAG3,
    EI_CLASS,
    EI_DATA,
    EI_VERSION,
    EI_PAD,
    EI_NIDENT=16
} ident;

typedef enum
{
    ELFCLASSNONE,
    ELFCLASS32,
    ELFCLASS64
} eclass;

typedef enum
{
    ELFDATANONE,
    ELFDATA2LSB,
    ELFDATA2MSB
} edata;

typedef enum
{
    SHN_UNDEF    =0,
    SHN_LORESERVE=0xff00,
    SHN_LOPROC   =0xff00,
    SHN_HIPROC   =0xff1f,
    SHN_ABS      =0xfff1,
    SHN_COMMON   =0xfff2,
    SHN_HIRESERVE=0xffff
} schindexes;

typedef struct
{
    unsigned char e_ident[EI_IDENT];
	Elf32_Half    e_type;
	Elf32_Half    e_machine;
	Elf32_Word    e_version;
	Elf32_Addr    e_entry;
	Elf32_Off     e_phoff;
	Elf32_Off     e_shoff;
	Elf32_Word    e_flags;
	Elf32_Half    e_ehsize;
	Elf32_Half    e_phentsize;
	Elf32_Half    e_phnum;
	Elf32_Half    e_shentsize;
	Elf32_Half    e_shnum;
	Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

#endif // ELF_H
