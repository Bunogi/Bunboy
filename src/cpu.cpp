#include <iostream>

#include "cpu.hpp"
#include "memory.hpp"

namespace GB {
	namespace CPU {
		int tick() {
			u8 opcode = RAM::readByte(PC);
			std::cout << std::hex << "PC: " << static_cast<unsigned>(PC) << " SP: " << static_cast<unsigned>(SP) << " Opcode: " << static_cast<unsigned>(opcode) << "\n";
			PC++;
			return opcodes[opcode]();
		}

		u16 AF() { return A << 8 | F; }
		u16 BC() { return B << 8 | C; }
		u16 DE() { return D << 8 | E; }
		u16 HL() { return H << 8 | L; }

		void setFlag(Flags flag) {
			F |= flag;
		}

		u8 addByte(u8 x, u8 y) {
			F = 0;
			unsigned result = x + y;
			if (result == 0)
				setFlag(Flags::Zero);
			if (result > 0xFF)
				setFlag(Flags::Carry);
			if ((x & 0xF) + (y & 0xF) > 0xF) 
				setFlag(Flags::HalfCarry);
			return static_cast<u8>(result);
		}

		u8 ADC(u8 x, u8 y) {
			if (F & Flags::Carry)
				x++;
			return addByte(x, y);
		}

		u8 subByte(u8 x, u8 y) {
			F = Flags::Subtract;
			unsigned result = x - y; 

			if (result == 0)
				setFlag(Flags::Zero);
			if ((x & 0xF) - (y & 0xF) < 0) 
				setFlag(Flags::HalfCarry); 
			if (x > y)
				setFlag(Flags::Carry);
			return static_cast<u8>(result); 
		}

		u8 SBC(u8 x, u8 y) {
			if (F & Flags::Carry)
				y++;
			return subByte(x, y); 
		}

		void ADD_HL(u16 value) {
			u8 zeroFlag = F & Flags::Zero;
			F = 0;
			unsigned result = HL() + value;
			if ((HL() & 0x0F00) + (value & 0x0F00) > 0x0F00)
				setFlag(Flags::HalfCarry);
			if (result > 0xFFFF)
				setFlag(Flags::Carry);
			F |= zeroFlag;
			set16Reg(H, L, static_cast<u16>(result)); 
		}

		void set16Reg(u8& regx, u8& regy, u16 value) {
			regx = value >> 8;
			regy = value & 0x00FF;
		}

		void AND(u8 value) {
			A &= value;
			F = Flags::HalfCarry;
			if (A == 0)
				setFlag(Flags::Zero);
		}

		void OR(u8 value) {
			A |= value;
			F = 0;
			if (A == 0)
				setFlag(Flags::Zero);
		}

		void XOR(u8 value) {
			A ^= value;
			F = 0;
			if (A == 0)
				setFlag(Flags::Zero);
		}

		void CP(u8 value) {
			subByte(A, value);
		}

		void INC(u8& value) {
			u8 result = value + 1;
			u8 carryFlag = F & Flags::Carry;
			F = 0;
			if (result == 0) 
				setFlag(Flags::Zero);
			if ((value & 0x0F) == 0x0F)
				setFlag(Flags::HalfCarry);
			F |= carryFlag;
			value = result;
		}

		void INC16(u8& regX, u8& regY) {
			regX++;
			if (regX == 0) //regX was 0xFF, overflow
				regY++;
		}

		void DEC(u8& value) {
			u8 result = value - 1;
			u8 carryFlag = F & Flags::Carry;
			F = Flags::Subtract;
			if (result == 0)
				setFlag(Flags::Zero);
			if ((result & 0xF0) != (value & 0xF0))
				setFlag(Flags::HalfCarry);
			F |= carryFlag;
		}

		void DEC16(u8& regX, u8& regY) {
			regX--;
			if (regX == 0xFF) //regX was 0, underflow
				regY--;
		}


	}
}
