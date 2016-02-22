#include <iostream>
#include <fstream>

#include "memory.hpp"
#include "cpu.hpp"

namespace GB {
	namespace RAM {
		u8 currentRomBank = 1;
		u8 currentRamBank = 0;

		RomBankType bankType = RomBankType::none;

		bool ramEnabled = false;
		bool romBanking = false;

		unsigned timerCycles = timerSpeeds[0];

		u16 dividerCycles = 0;

		u8 readByte(u16 address) {
			if (address < 0x4000)
				return rom[address];
			else if (address >= 0x4000 and address <= 0x7FFF) //Reading from ROM memory bank
				return rom[(address - 0x4000) + currentRomBank * 0x4000]; //Each rom bank is $4000 bytes in size
			else if (address >= 0xA000 and address <= 0xBFFF) //Reading from RAM bank
				return ramBank[(address - 0xA000) + currentRamBank * 0x2000]; //Each RAM Bank is $2000 bytes in size
			else
				return memory[address];
		}

		void writeByte(u16 address, u8 value) {
			if (address < 0x8000)
				changeBanks(address, value);
			else if (address >= 0xA000 and address < 0xC000) {
				if (ramEnabled)
					ramBank[(address - 0xA00) + currentRamBank * 0x2000] = value;
			}
			else if (address >= 0xE000 and address < 0xFE00) { //Echo of internal ram
				memory[address] = value;
				writeByte(address - 0x2000, value);
			}
			else if (address == TimerController) { //Changing timer settings
				memory[TimerController] = value;
				timerCycles = timerSpeeds[value & 3]; //last two bits decide the speed
			}
			else if (address == DividerRegister)
				memory[DividerRegister] = 0;
			else
				memory[address] = value;
		}

		u16 readShort(u16 address) {
			u16 output = readByte(address + 1) << 8 | readByte(address); //Least significant byte comes first
			std::cout << std::hex << "Read short : " << static_cast<unsigned>(output) << " from memory at " << static_cast<unsigned>(address) <<"\n";
			return output;
		}

		u16 readShortStack() {
			CPU::SP += 2;
			return readShort(CPU::SP);
		}

		void writeShort(u16 address, u16 value) {
			writeByte(address, value & 0x00FF);
			writeByte(address + 1, (value & 0xFF00) >> 8);
		}
		void writeShortStack(u16 value) {
			CPU::SP -= 2;
			writeShort(CPU::SP, value);
		}
		void changeBanks(u16 address, u8 value) {
			//Enable RAM
			if (address < 0x2000) {
				if (bankType == RomBankType::MBC1 or bankType == RomBankType::MBC2)
					enableRamBank(address, value);
			}
			//Change ROM bank
			else if (address >= 0x200 and address < 0x4000) {
				if (bankType == RomBankType::MBC1 or bankType == RomBankType::MBC2)
					changeLowRomBank(value);
			}
			//Change either RAM or ROM bank
			else if (address >= 0x4000 and address < 0x6000) {
				if (bankType == RomBankType::MBC1) {
					if (romBanking)
						changeHighRomBank(value);
					else
						changeRamBank(value);
				}
			}
			else if (address >= 0x6000 and address < 0x8000)
				if (bankType == RomBankType::MBC1)
					changeRomRamMode(value);
		}

		bool isTimerEnabled() {
			return readByte(TimerController) & 4; //0b0100
		}

		void updateTimers(unsigned cycles) {
			if (not isTimerEnabled())
				return;
			if (timerCycles - cycles > timerCycles) {
				timerCycles = timerSpeeds[readByte(TimerController) & 3];
				if (readByte(TimerLocation) + 1 == 0xFF) {
					writeByte(TimerModulator, readByte(TimerLocation));
					#warning "Interrupts not enabled, timers won't work properly"
					//CPU::sendInterrupt(/* Timer interrupt */);
				}
				else
					writeByte(TimerLocation, readByte(TimerLocation) + 1);
			}
		}

		void enableRamBank(u16 address, u8 value) {
			if (bankType == RomBankType::MBC2 and (address & 0x10) == 1)
				return;

			u8 test = value & 0x0F;
			if (test == 0xA)
				ramEnabled = true;
			else if (test == 0)
				ramEnabled = false;
		}

		void changeLowRomBank(u8 value) {
			if (bankType == RomBankType::MBC2) {
				currentRomBank = value & 0x0F;
				if (currentRomBank == 0)
					currentRomBank = 1;
				return;
			}

			u8 lower5 = value & 31; //Get lower 5
			currentRomBank &= 224;  //Reset lower 5
			currentRomBank |= lower5;
			if (currentRomBank == 0)
				currentRomBank = 1;
		}

		void changeHighRomBank(u8 value) {
			currentRomBank &= 31;

			value &= 224;
			currentRomBank |= value;
			if (currentRomBank == 0)
				currentRomBank = 1;
		}

		void changeRamBank(u8 value) {
			currentRamBank = value & 3;
		}

		void changeRomRamMode(u8 value) {
			romBanking = (value & 1) ? false : true;
			if (romBanking)
				currentRamBank = 0;
		}

		void loadROM(std::string file) {
			std::ifstream fileStream;
			fileStream.open(file, std::ios::in | std::ios::binary | std::ios::ate);
			int length = fileStream.tellg();
			fileStream.seekg(0, fileStream.beg);

			std::cout << "File Size: " << length << "\n";
			char *buffer = new char [length];
			fileStream.read(buffer, length);
			for (int i = 0; i < length; i++)
				RAM::rom[i] = buffer[i];

			delete[] buffer;
			fileStream.close();

			switch(RAM::rom[0x147]) {
				case 1: case 2: case 3:
					bankType = RomBankType::MBC1;
					break;
				case 5: case 6:
					bankType = RomBankType::MBC2;
					break;
				default:
					bankType = RomBankType::none;
			}
		}
	}
}
