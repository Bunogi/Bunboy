#include <iostream>

#include "cpu.hpp"
#include "memory.hpp"

namespace GB {
	namespace CPU {
		RegisterStruct registers;
		int tick() {
			u8 opcode = RAM::readByte(PC);
			std::cout << std::hex << "PC: " << static_cast<unsigned>(PC) << " SP: " << static_cast<unsigned>(SP) << " Opcode: " << static_cast<unsigned>(opcode) << "\n";
			PC++;
			return opcodes[opcode]();
		}

		void setFlag(Flags flag) {
			registers.F |= flag;
		}

		u8 addByte(u8 x, u8 y) {
			registers.F = 0;
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
			if (registers.F & Flags::Carry)
				x++;
			return addByte(x, y);
		}

		u8 subByte(u8 x, u8 y) {
			registers.F = Flags::Subtract;
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
			if (registers.F & Flags::Carry)
				y++;
			return subByte(x, y);
		}

		void ADD_HL(u16 value) {
			u8 zeroFlag = registers.F & Flags::Zero;
			registers.F = 0;
			unsigned result = registers.HL + value;
			if ((registers.HL & 0x0F00) + (value & 0x0F00) > 0x0F00)
				setFlag(Flags::HalfCarry);
			if (result > 0xFFFF)
				setFlag(Flags::Carry);
			registers.F |= zeroFlag;
			registers.HL = static_cast<u16>(result);
		}

		void AND(u8 value) {
			registers.A &= value;
			registers.F = Flags::HalfCarry;
			if (registers.A == 0)
				setFlag(Flags::Zero);
		}

		void OR(u8 value) {
			registers.A |= value;
			registers.F = 0;
			if (registers.A == 0)
				setFlag(Flags::Zero);
		}

		void XOR(u8 value) {
			registers.A ^= value;
			registers.F = 0;
				if (registers.A == 0)
				setFlag(Flags::Zero);
		}

		void CP(u8 value) {
			subByte(registers.A, value);
		}

		void INC(u8& value) {
			u8 result = value + 1;
			u8 carryFlag = registers.F & Flags::Carry;
			registers.F = 0;
			if (result == 0)
				setFlag(Flags::Zero);
			if ((value & 0x0F) == 0x0F)
				setFlag(Flags::HalfCarry);
			registers.F |= carryFlag;
			value = result;
		}

		void INC16(u8& regX, u8& regY) {
			regX++;
			if (regX == 0) //regX was 0xFF, overflow
				regY++;
		}

		void INCaddr(u16 address) {
			u8 value = RAM::readByte(address);
			INC(value);
			RAM::writeByte(address, value);
		}

		void DEC(u8& value) {
			u8 result = value - 1;
			u8 carryFlag = registers.F & Flags::Carry;
			registers.F = Flags::Subtract;
			if (result == 0)
				setFlag(Flags::Zero);
			if ((result & 0xF0) != (value & 0xF0))
				setFlag(Flags::HalfCarry);
			registers.F |= carryFlag;
		}

		void DECaddr(u16 address) {
			u8 value = RAM::readByte(address);
			DEC(value);
			RAM::writeByte(address, value);
		}
	}
}
