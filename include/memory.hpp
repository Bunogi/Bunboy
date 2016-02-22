#pragma once

#include <string>

#include "typedefs.hpp"

enum class RomBankType {
	none,
	MBC1,
	MBC2
};

//Timer addresses
const u16 TimerLocation = 0xFF05;
const u16 TimerModulator = 0xFF06;
const u16 TimerController = 0xFF07;

//The timer controller can set 4 different speeds, depending the value of the last two bits. 
//These have been calculated from the GB clock speed in order to run at the correct speed.
//CPU frequency divided by the frequency of the different timer speeds.
const unsigned timerSpeeds[4] = { 1024, 16, 64, 256 };

const unsigned dividerRegisterMax = 255; //Same as above
const u16 DividerRegister = 0xFF04;

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

		extern bool isTimerEnabled();
		extern void updateTimers(unsigned cycles);
		extern unsigned timerCycles;

		extern u16 dividerCycles;

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
