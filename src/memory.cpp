#include <iostream>
#include <fstream>

#include "memory.hpp"
#include "cpu.hpp"

u8 oamZero = 0; //So readByte can return a reference, there's probably a better way, but I'm lazy and this probably works

namespace GB {
	namespace RAM {
		u8& readByte(u16 address) {
			switch (address & 0xF000) {
				case 0x0000:
				case 0x1000:
				case 0x2000:
				case 0x3000:
					return rom0[address];

				case 0x4000:
				case 0x5000:
				case 0x6000:
				case 0x7000:
					return rom1[address - 0x4000];
				
				case 0x8000:
				case 0x9000:
					return vram[address - 0x8000];

				case 0xA000:
				case 0xB000:
					return eram[address - 0xA000];

				case 0xC000:
				case 0xD000: //Echo of internal ram
					return ram[address - 0xC000];
				
				case 0xE000: //Echo of internal ram
					return ram[address - 0xE000];

				case 0xF000:
					if (address < 0xFE00) 
						return ram[address - 0xF000];
					switch (address & 0x0F00) {
						case 0xE00:
							if (address < 0xFEA0)
								return oam[address - 0xFE00];
							else 
								return oamZero;
						case 0xF00:
							if (address >= 0xFF80)
								return zram[address - 0xFF80];
							else //Interrupts and such, TODO implement interrupts
								return oamZero;
					}
			}
		}
		void writeByte(u16 address, u8 value) {
			using namespace GB::RAM;
			switch (address & 0xF000) {
				case 0x8000:
				case 0x9000:
					vram[address - 0x8000] = value; 
					return;

				case 0xA000:
				case 0xB000:
					eram[address - 0xA000] = value;
					return;

				case 0xC000:
				case 0xD000: //Echo of internal ram
					ram[address - 0xC000] = value;
					return;
				
				case 0xE000: //Echo of internal ram
					ram[address - 0xE000] = value;
					return;

				case 0xF000:
					if (address < 0xFE00) 
						ram[address - 0xF000] = value;
					switch (address & 0x0F00) {
						case 0xE00:
							if (address < 0xFEA0)
								oam[address - 0xFE00] = value;
							return;
						case 0xF00:
							if (address >= 0xFF80)
								zram[address - 0xFF80] = value;
							return;
					}
					return;
			}
		}
		u16 readShort(u16 address) {
			return readByte(address + 1) << 8 | readByte(address); //Least significant byte comes first
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
		void loadROM(std::string file) {
			std::ifstream fileStream;
			fileStream.open(file, std::ios::in | std::ios::binary | std::ios::ate);
			int length = fileStream.tellg();
			fileStream.seekg(0, fileStream.beg);

			std::cout << "File Size: " << length << "\n";
			char *buffer = new char [length];
			fileStream.read(buffer, length);
			for (int i = 0; i < 0x8000; i++)
				GB::RAM::rom0[i] = buffer[i];
			
			delete[] buffer;
			fileStream.close();
		}
	}
}
