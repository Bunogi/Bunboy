#pragma once

#include "typedefs.hpp"
#include "opcodes.hpp"

typedef int(*FuncPointer)();

enum Flags : int {
	Zero      = 128, //0b1000 0000
	Subtract  = 64,  //0b0100 0000
	HalfCarry = 32,  //0b0010 0000
	Carry     = 16   //0b0001 0000
};

namespace GB {
	namespace CPU {
		extern u8 A, B, C, D, E, F, H, L; //General registers
		extern u16 SP, PC; //Stack pointer, program counter
		extern u16 AF(), BC(), DE(), HL(); //Functions for the pairing of registers
		extern FuncPointer opcodes[0x100];
		extern int tick();

		extern void setFlag(Flags flag);
		extern void set16Reg(u8& regx, u8& regy, u16 value); 

		extern u8 addByte(u8 x, u8 y); 
		extern u8 ADC(u8 x, u8 y); 
		extern void ADD_HL(u16 value); 

		extern u8 subByte(u8 x, u8 y);
		extern u8 SBC(u8 x, u8 y);

		extern void AND(u8 value);
		extern void OR(u8 value);
		extern void XOR(u8 value); 
		extern void CP(u8 value);
		extern void INC(u8& value);
		extern void INC16(u8& regX, u8& regY);
		extern void INCaddr(u16 address);
		extern void DEC(u8& value);
		extern void DEC16(u8& regX, u8& regY); 
		extern void DECaddr(u16 address);
	}
}
