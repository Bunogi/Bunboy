#pragma once

#include <string>

#include "typedefs.hpp"

namespace GB {
	namespace RAM {
		extern u8& readByte(u16 address);
		extern u16 readShort(u16 address);
		extern u16 readShortStack();
		extern void writeByte(u16 address, u8 value);
		extern void writeShort(u16 address, u16 value);
		extern void writeShortStack(u16 value);
		extern void loadROM(std::string file);
		extern u8 ram[0x2000]; //8kB of internal ram
		extern u8 eram[0x2000]; //8kB of extenal ram, in cartridge
		extern u8 vram[0x2000]; //8kB of vram
		extern u8 rom0[0x4000]; //Rom bank #0 16kB
		extern u8 rom1[0x4000]; //Switchable ROM bank, 16kB
		extern u8 oam[0xA0]; //Sprite attrib Memory
		extern u8 io[0x4C]; //IO ports
		extern u8 zram[0x7F]; //Zero page ram
	}
}
