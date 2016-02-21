#pragma once

#include <string>

#include "typedefs.hpp"

enum class RomBankType {
	none,
	MBC1,
	MBC2
};

namespace GB {
	namespace RAM {
		extern u8 readByte(u16 address);
		extern u16 readShort(u16 address);
		extern u16 readShortStack();
		extern void writeByte(u16 address, u8 value);
		extern void writeShort(u16 address, u16 value);
		extern void writeShortStack(u16 value);
		extern void loadROM(std::string file);
		extern void changeBanks(u16 address, u8 value);

		extern void enableRamBank(u16 address, u8 value);
		extern void changeLowRomBank(u8 value);
		extern void changeHighRomBank(u8 value);
		extern void changeRamBank(u8 value);
		extern void changeRomRamMode(u8 value);

		extern RomBankType bankType;
		extern u8 currentRomBank;
		extern u8 currentRamBank;
		extern u8 memory[0x10000];
		extern u8 rom[0x200000];
		extern u8 ramBank[0x8000];
	}
}
