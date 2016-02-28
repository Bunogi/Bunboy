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

struct RegisterStruct {
	union {
		u16 AF;
		struct {
			u8 F;
			u8 A;
		};
	};
	union {
		u16 BC;
		struct {
			u8 C;
			u8 B;
		};
	};
	union {
		u16 DE;
		struct {
			u8 E;
			u8 D;
		};
	};
	union {
		u16 HL;
		struct {
			u8 L;
			u8 H;
		};
	};
};

namespace GB {
	namespace CPU {
		extern RegisterStruct registers;
		extern u16 SP, PC; //Stack pointer, program counter
		extern FuncPointer opcodes[0x100];
		extern int tick();

		extern u8 addByte(u8 x, u8 y); 
		extern u8 ADC(u8 x, u8 y); 
		extern void ADD_HL(u16 value); 
		extern void setFlag(Flags flag);

		extern u8 subByte(u8 x, u8 y);
		extern u8 SBC(u8 x, u8 y);

		extern void AND(u8 value);
		extern void OR(u8 value);
		extern void XOR(u8 value);
		extern void CP(u8 value);
		extern void INC(u8& value);
		extern void INC(u16& value);
		extern void INCaddr(u16 address);
		extern void DEC(u8& value);
		extern void DECaddr(u16 address);
	}
}
