SHELL=/bin/bash
DISTNAME=Smidgen
VERSION=0.3.0

CPREFIX=~/opt/cross/bin/i686-elf-
SRCDIR=./src/
OBJDIR=./obj/
BINDIR=./bin/
ISO=./$(DEISNAME)_$(VERSION).iso

SFLAGS=
CFLAGS=   -O2
CXXFLAGS= -O2 -ffreestanding -fno-exceptions -std=gnu++11 -fno-rtti -fpermissive
LINKFLAGS= -nostdlib -lgcc

SOURCES=HCL/Char.cpp HCL/String.cpp HCL/StringData.cpp kernel.cpp boot.s
OBJECTS:=SOURCES
OBJECTS:= $(patsubst %.asm,%.o,$(SOURCES))
OBJECTS:= $(patsubst %.s,%.o,$(SOURCES))
OBJECTS:= $(patsubst %.c,%.o,$(SOURCES))
OBJECTS:= $(patsubst %.cpp,%.o,$(SOURCES))
OBJECTS:= $(patsubst %.cxx,%.o,$(SOURCES))
OBJECTS:= $(patsubst %.c++,%.o,$(SOURCES))

SFILES=$(SOURCES)
TARGET=$(DISTNAME).bin

all:	_welcome clean build iso qemu
#	$(compiling) boot.s
#	~/opt/cross/bin/i686-elf-as boot.s -o boot.o > boot.log
#	~/opt/cross/bin/i686-elf-as paging.s -o paging.o
#	yasm rtp.asm -o rtp.o -f elf32
#	yasm gdt.asm -o gdt.o -f elf32
#	~/opt/cross/bin/i686-elf-gcc -c src/tstream.c -o tstream.o -O2
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

#Compilation definitions
%.s:
	@echo -e " \e[0;32m"$@"\e[0m"
	@$(CPREFIX)as  -c $(SRCDIR)$@ -o $(OBJDIR)$@.o -DDISTNAME=$(DISTNAME) $(ASFLAGS)
%.c:
	@echo -e " \e[0;32m"$@"\e[0m"
	@$(CPREFIX)gcc -c $(SRCDIR)$@ -o $(OBJDIR)$@.o -DDISTNAME=$(DISTNAME) $(CFLAGS)
%.cpp:
	@echo -e " \e[0;32m"$@"\e[0m"
	@$(CPREFIX)g++ -c $(SRCDIR)$@ -o $(OBJDIR)$@.o -DDISTNAME=$(DISTNAME) $(CXXFLAGS)
%.asm:
	@echo -e " \e[0;32m$@\e[0m"
	@yasm             $(SRCDIR)$@ -o $(OBJDIR)$@.o -DDISTNAME=$(DISTNAME)

# Just print messages; no work done
_welcome:
	@echo -e " \e[0;32mMakefile for\e[0m \e[1;36m$(DISTNAME)\e[0m \e[0;36mv$(VERSION)\e[0m\n"
	@mkdir -p $(OBJDIR) $(BINDIR) $(OBJDIR)/HCL
	@echo "Sources: $(SOURCES);"
	@echo "Objects: $(OBJECTS);"
_build:
	@echo -e " \e[1;34m==>\e[0m \e[1mBuilding\e[0m"
_clean:
	@echo -e " \e[1;34m==>\e[0m \e[1mCleaning\e[0m"
_compile:
	@echo -e " \e[1;34m==>\e[0m \e[1mCompiling\e[0m"
_link:
	@echo -e " \e[1;34m==>\e[0m \e[1mLinking\e[0m"
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
	@gcc $(OBJECTS) link.ld -o $(TARGET) $(LINKFLAGS)

build:   _welcome         _build    compile link

clean:   _welcome         _clean
	@rm *.o *.iso *.bin &> /dev/null | true

iso:     _welcome         _iso
	@cp $(TARGET) isodir/boot/$(TARGET)
	@mkdir -p isodir/boot/grub
	@cp isodir/grub.cfg isodir/boot/grub/
	@grub-mkrescue -o os365.iso isodir > isomake.log

qemu:   _welcome          _qemu
	@qemu-system-i386 -cdrom $(ISO)

#backup:
#	./bkp.sh

git:    _welcome          _git
	@git add *
	@git commit * -m "make git"
	@git push
