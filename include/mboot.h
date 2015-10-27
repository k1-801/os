#ifndef __MBOOT_H
#define __MBOOT_H
#include <stdint.h>
struct multiboot
{
	uintptr_t flags;
	uintptr_t mem_lower;
	uintptr_t mem_upper;
	uintptr_t boot_device;
	uintptr_t cmdline;
	uintptr_t mods_count;
	uintptr_t mods_addr;
	uintptr_t num;
	uintptr_t size;
	uintptr_t addr;
	uintptr_t shndx;
	uintptr_t mmap_length;
	uintptr_t mmap_addr;
	uintptr_t drives_length;
	uintptr_t drives_addr;
	uintptr_t config_table;
	uintptr_t boot_loader_name;
	uintptr_t apm_table;
	uintptr_t vbe_control_info;
	uintptr_t vbe_mode_info;
	uintptr_t vbe_mode;
	uintptr_t vbe_interface_seg;
	uintptr_t vbe_interface_off;
	uintptr_t vbe_interface_len;
} __attribute__ ((packed));

typedef struct {
	uint16_t attributes;
	uint8_t  winA, winB;
	uint16_t granularity;
	uint16_t winsize;
	uint16_t segmentA, segmentB;
	uint32_t realFctPtr;
	uint16_t pitch;

	uint16_t Xres, Yres;
	uint8_t  Wchar, Ychar, planes, bpp, banks;
	uint8_t  memory_model, bank_size, image_pages;
	uint8_t  reserved0;

	uint8_t  red_mask, red_position;
	uint8_t  green_mask, green_position;
	uint8_t  blue_mask, blue_position;
	uint8_t  rsv_mask, rsv_position;
	uint8_t  directcolor_attributes;

	uint32_t physbase;
	uint32_t reserved1;
	uint16_t reserved2;
} __attribute__ ((packed)) vbe_info_t;

typedef struct {
	uintptr_t mod_start;
	uintptr_t mod_end;
	uintptr_t cmdline;
	uintptr_t reserved;
} __attribute__ ((packed)) mboot_mod_t;

typedef struct {
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} __attribute__ ((packed)) mboot_memmap_t;
struct mboot_info_struct {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
	uint64_t framebuffer_addr;
	uint32_t framebuffer_pitch;
	uint32_t framebuffer_width;
	uint32_t framebuffer_height;
	uint8_t framebuffer_bpp;
	uint8_t framebuffer_type;
	union
	{
		struct
		{
			uint32_t framebuffer_palette_addr;
			uint16_t framebuffer_palette_num_colors;
		};
		struct
		{
			uint8_t framebuffer_red_field_position;
			uint8_t framebuffer_red_mask_size;
			uint8_t framebuffer_green_field_position;
			uint8_t framebuffer_green_mask_size;
			uint8_t framebuffer_blue_field_position;
			uint8_t framebuffer_blue_mask_size;
		};
	};
};
#endif
