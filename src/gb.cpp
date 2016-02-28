#include <cstring>

#include "gb.hpp"

FuncPointer GB::CPU::opcodes[0x100] = {
	&opcode00, &opcode01, &opcode02, &opcode03, &opcode04, &opcode05, &opcode06, &opcode07,
	&opcode08, &opcode09, &opcode0A, &opcode0B, &opcode0C, &opcode0D, &opcode0E, &opcode0F,
	&opcode10, &opcode11, &opcode12, &opcode13, &opcode14, &opcode15, &opcode16, &opcode17,
	&opcode18, &opcode19, &opcode1A, &opcode1B, &opcode1C, &opcode1D, &opcode1E, &opcode1F,
	&opcode20, &opcode21, &opcode22, &opcode23, &opcode24, &opcode25, &opcode26, &opcode27,
	&opcode28, &opcode29, &opcode2A, &opcode2B, &opcode2C, &opcode2D, &opcode2E, &opcode2F,
	&opcode30, &opcode31, &opcode32, &opcode33, &opcode34, &opcode35, &opcode36, &opcode37,
	&opcode38, &opcode39, &opcode3A, &opcode3B, &opcode3C, &opcode3D, &opcode3E, &opcode3F,
	&opcode40, &opcode41, &opcode42, &opcode43, &opcode44, &opcode45, &opcode46, &opcode47,
	&opcode48, &opcode49, &opcode4A, &opcode4B, &opcode4C, &opcode4D, &opcode4E, &opcode4F,
	&opcode50, &opcode51, &opcode52, &opcode53, &opcode54, &opcode55, &opcode56, &opcode57,
	&opcode58, &opcode59, &opcode5A, &opcode5B, &opcode5C, &opcode5D, &opcode5E, &opcode5F,
	&opcode60, &opcode61, &opcode62, &opcode63, &opcode64, &opcode65, &opcode66, &opcode67,
	&opcode68, &opcode69, &opcode6A, &opcode6B, &opcode6C, &opcode6D, &opcode6E, &opcode6F,
	&opcode70, &opcode71, &opcode72, &opcode73, &opcode74, &opcode75, &opcode76, &opcode77,
	&opcode78, &opcode79, &opcode7A, &opcode7B, &opcode7C, &opcode7D, &opcode7E, &opcode7F,
	&opcode80, &opcode81, &opcode82, &opcode83, &opcode84, &opcode85, &opcode86, &opcode87,
	&opcode88, &opcode89, &opcode8A, &opcode8B, &opcode8C, &opcode8D, &opcode8E, &opcode8F,
	&opcode90, &opcode91, &opcode92, &opcode93, &opcode94, &opcode95, &opcode96, &opcode97,
	&opcode98, &opcode99, &opcode9A, &opcode9B, &opcode9C, &opcode9D, &opcode9E, &opcode9F,
	&opcodeA0, &opcodeA1, &opcodeA2, &opcodeA3, &opcodeA4, &opcodeA5, &opcodeA6, &opcodeA7,
	&opcodeA8, &opcodeA9, &opcodeAA, &opcodeAB, &opcodeAC, &opcodeAD, &opcodeAE, &opcodeAF,
	&opcodeB0, &opcodeB1, &opcodeB2, &opcodeB3, &opcodeB4, &opcodeB5, &opcodeB6, &opcodeB7,
	&opcodeB8, &opcodeB9, &opcodeBA, &opcodeBB, &opcodeBC, &opcodeBD, &opcodeBE, &opcodeBF,
	&opcodeC0, &opcodeC1, &opcodeC2, &opcodeC3, &opcodeC4, &opcodeC5, &opcodeC6, &opcodeC7,
	&opcodeC8, &opcodeC9, &opcodeCA, &opcodeCB, &opcodeCC, &opcodeCD, &opcodeCE, &opcodeCF,
	&opcodeD0, &opcodeD1, &opcodeD2, &opcodeD3, &opcodeD4, &opcodeD5, &opcodeD6, &opcodeD7,
	&opcodeD8, &opcodeD9, &opcodeDA, &opcodeDB, &opcodeDC, &opcodeDD, &opcodeDE, &opcodeDF,
	&opcodeE0, &opcodeE1, &opcodeE2, &opcodeE3, &opcodeE4, &opcodeE5, &opcodeE6, &opcodeE7,
	&opcodeE8, &opcodeE9, &opcodeEA, &opcodeEB, &opcodeEC, &opcodeED, &opcodeEE, &opcodeEF,
	&opcodeF0, &opcodeF1, &opcodeF2, &opcodeF3, &opcodeF4, &opcodeF5, &opcodeF6, &opcodeF7,
	&opcodeF8, &opcodeF9, &opcodeFA, &opcodeFB, &opcodeFC, &opcodeFD, &opcodeFE, &opcodeFF
};

u16 GB::CPU::SP = 0, GB::CPU::PC = 0;
u8 GB::RAM::memory[0x10000], GB::RAM::rom[0x200000], GB::RAM::ramBank[0x8000];

const int maxCycles = 69905; //CPU runs at 4194304Hz, which divided by 60 gives the cycles per frame (69905)


namespace GB {
	void update() { //TODO Cycle magic
		int cycles = 0;

		while (cycles < maxCycles) {
			int thisCycle = CPU::tick();
			cycles += thisCycle;
			RAM::updateTimers(thisCycle);

			//Update divider register
			RAM::dividerCycles += thisCycle;
			if (RAM::dividerCycles >= dividerRegisterMax) {
				RAM::memory[DividerRegister]++;
				RAM::dividerCycles = 0;
			}
		}
		//Video::renderScreen();
	}
	void reset() {  //Run the gameboy powerup sequence
		using namespace GB::CPU;
		using namespace GB::RAM;
		registers.AF = 0;
		registers.BC = 0x0013; 
		registers.DE = 0x00D8;
		registers.HL = 0x014D;
		PC = 0x100;
		SP = 0xFFFE;
		std::memset(&memory, 0, sizeof memory);
		std::memset(&rom, 0, sizeof rom);
		std::memset(&ramBank, 0, sizeof ramBank);
		writeByte(0xFF10, 0x80);
		writeByte(0xFF11, 0xBF);
		writeByte(0xFF12, 0xF3);
		writeByte(0xFF14, 0xBF);
		writeByte(0xFF16, 0x3F);
		writeByte(0xFF19, 0xBF);
		writeByte(0xFF1A, 0x7F);
		writeByte(0xFF1B, 0xFF);
		writeByte(0xFF1C, 0x9F);
		writeByte(0xFF1E, 0xBF);
		writeByte(0xFF20, 0xFF);
		writeByte(0xFF23, 0xBF);
		writeByte(0xFF24, 0x77);
		writeByte(0xFF25, 0xF3);
		writeByte(0xFF26, 0xF1);
		writeByte(0xFF40, 0x91);
		writeByte(0xFF47, 0xFC);
		writeByte(0xFF48, 0xFF);
		writeByte(0xFF49, 0xFF);
	}
}
