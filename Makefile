SHELL=/bin/bash

## Common visual building Makefile 
## Author: k1-801 (Kychanov Dmitry)
## Edit as for your project

DISTNAME=Smidgen
VERSION=0.3.0

CPREFIX=~/opt/cross/bin/i686-elf-
SRCDIR=./src/
OBJDIR=./obj/
BINDIR=./bin/
ISO=./$(DISTNAME)_$(VERSION).iso

DEFS= -DDISTNAME=\"$(DISTNAME)\" -DVERSION=\"$(VERSION)\"
ASMFLAGS=  -f elf32
SFLAGS=
CFLAGS=    $(DEFS) -O2 -m32
CXXFLAGS=  $(DEFS) -O2 -m32 -ffreestanding -fno-exceptions -std=gnu++11 -fno-rtti -fpermissive
LINKFLAGS= -nostdlib -lgcc

SOURCES=gdt.asm \
	rtp.asm \
	boot.s \
	paging.s \
	kernel.cpp \
	GoMenu.cpp \
	HCL/Char.cpp \
	HCL/String.cpp

#end

OBJECTS:=$(SOURCES)
OBJECTS:= $(patsubst %.asm,$(OBJDIR)%.asm.o,$(OBJECTS))
OBJECTS:= $(patsubst %.s,$(OBJDIR)%.s.o,$(OBJECTS))
OBJECTS:= $(patsubst %.c,$(OBJDIR)%.c.o,$(OBJECTS))
OBJECTS:= $(patsubst %.cpp,$(OBJDIR)%.cpp.o,$(OBJECTS))
OBJECTS:= $(patsubst %.cxx,$(OBJDIR)%.cxx.o,$(OBJECTS))
OBJECTS:= $(patsubst %.c++,$(OBJDIR)%.c++.o,$(OBJECTS))

SFILES=$(SOURCES)
TARGET=$(DISTNAME).bin

all:	_welcome clean build iso qemu
	@echo -en

#Compilation definitions
%.s:
	@echo -e " \e[0;32m"$@"\e[0m"
	@$(CPREFIX)as  -c $(SRCDIR)$@ -o $(OBJDIR)$@.o $(SFLAGS)
%.c:
	@echo -e " \e[0;32m"$@"\e[0m"
	@$(CPREFIX)gcc -c $(SRCDIR)$@ -o $(OBJDIR)$@.o $(CFLAGS)
%.cpp:
	@echo -e " \e[0;32m"$@"\e[0m"
	@$(CPREFIX)g++ -c $(SRCDIR)$@ -o $(OBJDIR)$@.o $(CXXFLAGS)
%.asm:
	@echo -e " \e[0;32m$@\e[0m"
	@yasm             $(SRCDIR)$@ -o $(OBJDIR)$@.o $(ASMFLAGS)

# Just print messages; no work done
_welcome:
	@echo -e " \e[0;32mMakefile for\e[0m \e[1;36m$(DISTNAME)\e[0m \e[0;36mv$(VERSION)\e[0m\n"
	@mkdir -p $(OBJDIR) $(BINDIR) $(OBJDIR)/HCL
_build:
	@echo -e " \e[1;34m==>\e[0m \e[1mBuilding\e[0m"
_clean:
	@echo -e " \e[1;34m==>\e[0m \e[1mCleaning\e[0m"
_compile:
	@echo -e " \e[1;34m==>\e[0m \e[1mCompiling\e[0m"
_link:
	@echo -e " \e[1;34m==>\e[0m \e[1mLinking\e[0m"
_grub:
	@echo -e " \e[1;34m==>\e[0m \e[1mReconfiguring \e[1;36mgrub.cfg\e[0m"
_iso:
	@echo -e " \e[1;34m==>\e[0m \e[1mGenerating ISO image\e[0m"
_qemu:
	@echo -e " \e[1;34m==>\e[0m \e[1mRunning image in QEMU\e[0m"
_git:
	@echo -e " \e[1;34m==>\e[0m \e[1mSaving changes to GIT\e[0m"
	
# WOOORK
#Target  _welcome deps    _messsage work
compile: _welcome         _compile  $(SOURCES)
	@echo -e " \e[1;34m==>\e[0m \e[1;32mCompilation success\e[0m"

link:    _welcome compile _link
	@echo -e " \e[0;32m$(TARGET)\e[0m"
	@$(CPREFIX)gcc $(OBJECTS) -T link.ld -o $(TARGET) $(LINKFLAGS)
	@echo -e " \e[1;34m==>\e[0m \e[1;32mLink success\e[0m"

build:   _welcome         _build    compile link
	@echo -e " \e[1;34m==>\e[0m \e[1;32mBuild success\e[0m"

clean:   _welcome         _clean
	@rm *.o *.iso *.bin &> /dev/null | true


# Resu

grub:    _welcome         _grub
	@echo "menuentry \"$(DISTNAME) $(VERSION)\" \
{ \
	multiboot /boot/$(TARGET) \
	GRUB_GFXMODE=1024x768x16 \
}" > isodir/grub.cfg
	@echo -e " \e[1;34m==>\e[0m \e[1;32mGRUB success\e[0m"

iso:     _welcome grub    _iso
	@mkdir -p isodir/boot/grub
	@cp $(TARGET) ./isodir/boot/$(TARGET)
	@cp isodir/grub.cfg isodir/boot/grub/
	@grub-mkrescue -o $(ISO) isodir
	@echo -e " \e[1;34m==>\e[0m \e[1;32mISO success\e[0m"

qemu:   _welcome          _qemu
	@qemu-system-i386 -cdrom $(ISO)

git:    _welcome          _git
	@git add *
	@git commit -m "make git"
	@git push
	@echo -e " \e[1;34m==>\e[0m \e[1;32mGIT success\e[0m"

# OLD TEXT OF all:
#	$(compiling) boot.s
#	~/opt/cross/bin/i686-elf-as boot.s -o boot.o > boot.log
#	~/opt/cross/bin/i686-elf-as paging.s -o paging.o
#	yasm rtp.asm -o rtp.o -f elf32
#	yasm gdt.asm -o gdt.o -f elf32
#	~/opt/cross/bin/i686-elf-g++ -c kernel.cpp -o kernel.o -O2 -ffreestanding -Wall -Wextra -Wmaybe-uninitialized -fno-exceptions -std=gnu++11 -fno-rtti -fpermissive>/dev/null
#	echo "done."
#	~/opt/cross/bin/i686-elf-g++ -T link.ld -o os365.bin -O2 -nostdlib paging.o rtp.o gdt.o boot.o kernel.o -lgcc > linker.log
#	echo "Creating ISO..."
#	cp os365.bin isodir/boot/os365.bin
#	mkdir -p isodir/boot/grub
#	cp isodir/grub.cfg isodir/boot/grub/
#	grub-mkrescue -o os365.iso isodir > isomake.log
#	echo "done. Running in QEMU..."
#	qemu-system-i386 -cdrom os365.iso
#backup:
#	./bkp.sh