all:
	echo "Compiling..."
	~/opt/cross/bin/i686-elf-as boot.s -o boot.o > boot.log
	~/opt/cross/bin/i686-elf-as paging.s -o paging.o
	yasm rtp.asm -o rtp.o -f elf32
	~/opt/cross/bin/i686-elf-g++ -c kernel.cpp -o kernel.o -O2 -ffreestanding -Wall -Wextra -Wmaybe-uninitialized -fno-exceptions -std=gnu++11 -fno-rtti -fpermissive> kernel.log
	echo "done."
	~/opt/cross/bin/i686-elf-g++ -T link.ld -o os365.bin -O2 -nostdlib paging.o rtp.o boot.o kernel.o -lgcc > linker.log
	echo "Creating ISO..."
	cp os365.bin isodir/boot/os365.bin
	mkdir -p isodir/boot/grub
	cp isodir/grub.cfg isodir/boot/grub/
	grub-mkrescue -o os365.iso isodir > isomake.log
	echo "done. Running in QEMU..."
	qemu-system-i386 -cdrom os365.iso
clean:
	rm *.o *.iso *.bin
qemu:
	qemu-system-i386 -cdrom os365.iso
