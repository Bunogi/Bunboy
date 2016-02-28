#include <iostream>

#include "opcodes.hpp"
#include "memory.hpp"
#include "cpu.hpp"

/*
	Instruction set used:
	http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
*/


namespace GB {
	namespace CPU {
		using namespace GB::CPU;
		using namespace GB::RAM;
		auto unkownOpcode = [](){ std::cout << "Unknown opcode. Terminating.\n"; exit(1); };
		int opcode00() {                                                              return 4;  } //NOP
		int opcode01() { registers.BC = readShort(PC++);                              return 12; } //LD BC, nn
		int opcode02() { registers.A = readByte(registers.BC);                        return 8;  } //LD (BC), A
		int opcode03() { registers.BC++;                                              return 8;  } //INC BC
		int opcode04() { INC(registers.B);                                            return 4;  } //INC B
		int opcode05() { DEC(registers.B);                                            return 4;  } //DEC B
		int opcode06() { writeByte(PC++, registers.B);                                return 8;  }  //LD B, d8.
		int opcode07() { unkownOpcode();                                                         }
		int opcode08() { writeShort(readShort(PC++), SP);                             return 20; } //LD (nn), SP
		int opcode09() { ADD_HL(registers.BC);                                        return 8;  } //ADD HL, BC
		int opcode0A() { writeByte(registers.BC, registers.A);                        return 8;  } //LD A, (BC)
		int opcode0B() { registers.BC--;                                              return 8;  } //DEC BC
		int opcode0C() { INC(registers.C);                                            return 4;  } //INC C
		int opcode0D() { DEC(registers.C);                                            return 4;  } //DEC C
		int opcode0E() { writeByte(PC++, registers.C);                                return 8;  } //LD C, d8
		int opcode0F() { unkownOpcode();                                                         }
		int opcode10() { unkownOpcode();                                                         }
		int opcode11() { registers.DE = readShort(PC++);                              return 12; } //LD DE, nn
		int opcode12() { registers.A = readByte(registers.DE);                        return 8;  } //LD (DE), A
		int opcode13() { registers.DE++;                                              return 8;  } //INC DE
		int opcode14() { INC(registers.D);                                            return 4;  } //INC D
		int opcode15() { DEC(registers.D);                                            return 4;  } //DEC D
		int opcode16() { writeByte(PC++, registers.D);                                return 8;  } //LD D, d8
		int opcode17() { unkownOpcode();                                                         }
		int opcode18() { unkownOpcode();                                                         }
		int opcode19() { ADD_HL(registers.DE);                                        return 8;  } //ADD HL, DE
		int opcode1A() { writeByte(registers.DE, registers.A);                        return 8;  } //LD A, (DE)
		int opcode1B() { registers.DE++;                                              return 8;  } //DEC DE
		int opcode1C() { INC(registers.E);                                            return 4;  } //INC E
		int opcode1D() { DEC(registers.E);                                            return 4;  } //DEC E
		int opcode1E() { writeByte(PC++, registers.E);                                return 8;  } //LD E, d8
		int opcode1F() { unkownOpcode();                                                         }
		int opcode20() { unkownOpcode();                                                         }
		int opcode21() { registers.HL = readShort(PC++);                              return 12; } //LD HL, nn
		int opcode22() { writeByte(registers.HL, registers.A); registers.HL++;        return 8;  } //LD (HL+, A)
		int opcode23() { registers.HL++;                                              return 8;  } //INC HL
		int opcode24() { INC(registers.H);                                            return 4;  } //INC H
		int opcode25() { DEC(registers.H);                                            return 4;  } //DEC H
		int opcode26() { writeByte(PC++, registers.H);                                return 8;  } //LD H, d8
		int opcode27() { unkownOpcode();                                                         }
		int opcode28() { unkownOpcode();                                                         }
		int opcode29() { ADD_HL(registers.HL);                                        return 8;  } //ADD HL, HL
		int opcode2A() { registers.A = readByte(registers.HL); registers.HL++;        return 8;  } //LD A, (HL+)
		int opcode2B() { registers.HL--;                                              return 8;  } //DEC HL
		int opcode2C() { INC(registers.L);                                            return 4;  } //INC L
		int opcode2D() { DEC(registers.L);                                            return 4;  } //DEC L
		int opcode2E() { writeByte(PC++, registers.L);                                return 8;  } //LD E, d8
		int opcode2F() { unkownOpcode();                                                         }
		int opcode30() { unkownOpcode();                                                         }
		int opcode31() { SP = readShort(PC++);                                        return 12; } //LD SP, nn
		int opcode32() { writeByte(registers.HL, registers.A); registers.HL++;        return 12; } //LD (HL-), A
		int opcode33() { SP++;                                                        return 8;  } //INC SP
		int opcode34() { INCaddr(registers.HL);                                       return 12; } //INC (HL)
		int opcode35() { DECaddr(registers.HL);                                       return 12; } //DEC (HL)
		int opcode36() { writeByte(registers.HL, PC++);                               return 12; } //LD (HL), d8
		int opcode37() { unkownOpcode();                                                         }
		int opcode38() { unkownOpcode();                                                         }
		int opcode39() { ADD_HL(SP);                                                  return 8;  } //ADD HL, SP
		int opcode3A() { registers.A = readByte(registers.HL); registers.HL--;        return 8;  } //LD A, (HL-)
		int opcode3B() { SP--;                                                        return 8;  } //DEC SP
		int opcode3C() { INC(registers.A);                                            return 4;  } //INC A
		int opcode3D() { DEC(registers.A);                                            return 4;  } //DEC A
		int opcode3E() { unkownOpcode();                                                         }
		int opcode3F() { unkownOpcode();                                                         }
		int opcode40() { /* registers.B = registers.B; */                             return 4;  } //LD B, B
		int opcode41() { registers.B = registers.C;                                   return 4;  } //LD B, C
		int opcode42() { registers.B = registers.D;                                   return 4;  } //LD B, D
		int opcode43() { registers.B = registers.E;                                   return 4;  } //LD B, E
		int opcode44() { registers.B = registers.H;                                   return 4;  } //LD B, H
		int opcode45() { registers.B = registers.L;                                   return 4;  } //LD B, L
		int opcode46() { registers.B = readByte(registers.HL);                        return 8;  } //LD B, (HL)
		int opcode47() { registers.B = registers.A;                                   return 4;  } //LD B, A
		int opcode48() { registers.C = registers.B;                                   return 4;  } //LD C, B
		int opcode49() { /* registers.C = registers.C; */                             return 4;  } //LD C, C
		int opcode4A() { registers.C = registers.D;                                   return 4;  } //LD C, D
		int opcode4B() { registers.C = registers.E;                                   return 4;  } //LD C, E
		int opcode4C() { registers.C = registers.H;                                   return 4;  } //LD C, H
		int opcode4D() { registers.C = registers.L;                                   return 4;  } //LD C, L
		int opcode4E() { registers.C = readByte(registers.HL);                        return 8;  } //LD C, (HL)
		int opcode4F() { registers.C = registers.A;                                   return 4;  } //LD C, A
		int opcode50() { registers.D = registers.B;                                   return 4;  } //LD D, B
		int opcode51() { registers.D = registers.C;                                   return 4;  } //LD D, C
		int opcode52() { /* registers.D = registers.D; */                             return 4;  } //LD D, D
		int opcode53() { registers.D = registers.E;                                   return 4;  } //LD D, E
		int opcode54() { registers.D = registers.H;                                   return 4;  } //LD D, H
		int opcode55() { registers.D = registers.L;                                   return 4;  } //LD D, L
		int opcode56() { registers.D = readByte(registers.HL);                        return 8;  } //LD D, (HL)
		int opcode57() { registers.D = registers.A;                                   return 4;  } //LD D, A
		int opcode58() { registers.E = registers.B;                                   return 4;  } //LD E, B
		int opcode59() { registers.E = registers.C;                                   return 4;  } //LD E, C
		int opcode5A() { registers.E = registers.D;                                   return 4;  } //LD E, D
		int opcode5B() { /* registers.E = registers.E; */                             return 4;  } //LD E, E
		int opcode5C() { registers.E = registers.H;                                   return 4;  } //LD E, H
		int opcode5D() { registers.E = registers.L;                                   return 4;  } //LD E, L
		int opcode5E() { registers.E = readByte(registers.HL);                        return 8;  } //LD E, (HL)
		int opcode5F() { registers.E = registers.A;                                   return 4;  } //LD E, A
		int opcode60() { registers.H = registers.B;                                   return 4;  } //LD H, B
		int opcode61() { registers.H = registers.C;                                   return 4;  } //LD H, C
		int opcode62() { registers.H = registers.D;                                   return 4;  } //LD H, D
		int opcode63() { registers.H = registers.E;                                   return 4;  } //LD H, E
		int opcode64() { /* registers.H = registers.H; */                             return 4;  } //LD H, H
		int opcode65() { registers.H = registers.L;                                   return 4;  } //LD H, L
		int opcode66() { registers.H = readByte(registers.HL);                        return 4;  } //LD H, (HL)
		int opcode67() { registers.H = registers.A;                                   return 4;  } //LD H, A
		int opcode68() { registers.L = registers.B;                                   return 4;  } //LD L, B
		int opcode69() { registers.L = registers.D;                                   return 4;  } //LD L, D
		int opcode6A() { registers.L = registers.C;                                   return 4;  } //LD L, C
		int opcode6B() { registers.L = registers.E;                                   return 4;  } //LD L, E
		int opcode6C() { registers.L = registers.H;                                   return 4;  } //LD L, H
		int opcode6D() { /* registers.L = registers.L; */                             return 4;  } //LD L, L
		int opcode6E() { registers.L = readByte(registers.HL);                        return 8;  } //LD L, (HL)
		int opcode6F() { registers.L = registers.A;                                   return 4;  } //LD L, A
		int opcode70() { writeByte(registers.HL, registers.B);                        return 8;  } //LD (HL), B
		int opcode71() { writeByte(registers.HL, registers.C);                        return 8;  } //LD (HL), C
		int opcode72() { writeByte(registers.HL, registers.D);                        return 8;  } //LD (HL), D
		int opcode73() { writeByte(registers.HL, registers.E);                        return 8;  } //LD (HL), E
		int opcode74() { writeByte(registers.HL, registers.H);                        return 8;  } //LD (HL), H
		int opcode75() { writeByte(registers.HL, registers.L);                        return 8;  } //LD (HL), L
		int opcode76() { unkownOpcode();                                                         }
		int opcode77() { writeByte(registers.HL, registers.A);                        return 8;  } //LD (HL), A
		int opcode78() { registers.A = registers.B;                                   return 4;  } //LD A, B
		int opcode79() { registers.A = registers.C;                                   return 4;  } //LD A, C
		int opcode7A() { registers.A = registers.D;                                   return 4;  } //LD A, D
		int opcode7B() { registers.A = registers.E;                                   return 4;  } //LD A, E
		int opcode7C() { registers.A = registers.H;                                   return 4;  } //LD A, H
		int opcode7D() { registers.A = registers.L;                                   return 4;  } //LD A, L
		int opcode7E() { registers.A = readByte(registers.HL);                        return 8;  } //LD A, (HL)
		int opcode7F() { /* registers.A = registers.A; */                             return 4;  } //LD A, A
		int opcode80() { registers.A = addByte(registers.A, registers.B);             return 4;  } //ADD A, B
		int opcode81() { registers.A = addByte(registers.A, registers.C);             return 4;  } //ADD A, C
		int opcode82() { registers.A = addByte(registers.A, registers.D);             return 4;  } //ADD A, D
		int opcode83() { registers.A = addByte(registers.A, registers.E);             return 4;  } //ADD A, E
		int opcode84() { registers.A = addByte(registers.A, registers.H);             return 4;  } //ADD A, H
		int opcode85() { registers.A = addByte(registers.A, registers.L);             return 4;  } //ADD A, L
		int opcode86() { registers.A = addByte(registers.A, readByte(registers.HL));  return 8;  } //ADD A, (HL)
		int opcode87() { registers.A = addByte(registers.A, registers.A);             return 4;  } //ADD A, A
		int opcode88() { registers.A = ADC(registers.A, registers.B);                 return 4;  } //ADC A, B
		int opcode89() { registers.A = ADC(registers.A, registers.C);                 return 4;  } //ADC A, C
		int opcode8A() { registers.A = ADC(registers.A, registers.D);                 return 4;  } //ADC A, D
		int opcode8B() { registers.A = ADC(registers.A, registers.E);                 return 4;  } //ADC A, E
		int opcode8C() { registers.A = ADC(registers.A, registers.H);                 return 4;  } //ADC A, H
		int opcode8D() { registers.A = ADC(registers.A, registers.L);                 return 4;  } //ADC A, L
		int opcode8E() { registers.A = ADC(registers.A, readByte(registers.HL) );     return 8;  } //ADC A, (HL)
		int opcode8F() { registers.A = ADC(registers.A, registers.A);                 return 4;  } //ADC A, A
		int opcode90() { registers.A = subByte(registers.A, registers.B);             return 4;  } //SUB B
		int opcode91() { registers.A = subByte(registers.A, registers.C);             return 4;  } //SUB C
		int opcode92() { registers.A = subByte(registers.A, registers.D);             return 4;  } //SUB D
		int opcode93() { registers.A = subByte(registers.A, registers.E);             return 4;  } //SUB E
		int opcode94() { registers.A = subByte(registers.A, registers.H);             return 4;  } //SUB H
		int opcode95() { registers.A = subByte(registers.A, registers.L);             return 4;  } //SUB L
		int opcode96() { registers.A = subByte(registers.A, readByte(registers.HL));  return 8;  } //SUB(HL)
		int opcode97() { registers.A = subByte(registers.A, registers.A);             return 4;  } //SUB A
		int opcode98() { registers.A = SBC(registers.A, registers.B);                 return 4;  } //SBC A, B
		int opcode99() { registers.A = SBC(registers.A, registers.C);                 return 4;  } //SBC A, C
		int opcode9A() { registers.A = SBC(registers.A, registers.D);                 return 4;  } //SBC A, D
		int opcode9B() { registers.A = SBC(registers.A, registers.E);                 return 4;  } //SBC A, E
		int opcode9C() { registers.A = SBC(registers.A, registers.H);                 return 4;  } //SBC A, H
		int opcode9D() { registers.A = SBC(registers.A, registers.L);                 return 4;  } //SBC A, L
		int opcode9E() { registers.A = SBC(registers.A, readByte(registers.HL));      return 8;  } //SBC A, (HL)
		int opcode9F() { registers.A = SBC(registers.A, registers.A);                 return 4;  } //SBC A, A
		int opcodeA0() { AND(registers.B);                                            return 4;  } //AND B
		int opcodeA1() { AND(registers.C);                                            return 4;  } //AND C
		int opcodeA2() { AND(registers.D);                                            return 4;  } //AND D
		int opcodeA3() { AND(registers.E);                                            return 4;  } //AND E
		int opcodeA4() { AND(registers.H);                                            return 4;  } //AND H
		int opcodeA5() { AND(registers.L);                                            return 4;  } //AND L
		int opcodeA6() { AND(readByte(registers.HL));                                 return 8;  } //AND (HL)
		int opcodeA7() { AND(registers.A);                                            return 4;  } //AND A
		int opcodeA8() { XOR(registers.B);                                            return 4;  } //XOR B
		int opcodeA9() { XOR(registers.C);                                            return 4;  } //XOR C
		int opcodeAA() { XOR(registers.D);                                            return 4;  } //XOR D
		int opcodeAB() { XOR(registers.E);                                            return 4;  } //XOR E
		int opcodeAC() { XOR(registers.H);                                            return 4;  } //XOR H
		int opcodeAD() { XOR(registers.L);                                            return 4;  } //XOR L
		int opcodeAE() { XOR(readByte(registers.HL));                                 return 8;  } //XOR (HL)
		int opcodeAF() { XOR(registers.A);                                            return 4;  } //XOR A
		int opcodeB0() { OR(registers.B);                                             return 4;  } //OR B
		int opcodeB1() { OR(registers.C);                                             return 4;  } //OR C
		int opcodeB2() { OR(registers.D);                                             return 4;  } //OR D
		int opcodeB3() { OR(registers.E);                                             return 4;  } //OR E
		int opcodeB4() { OR(registers.H);                                             return 4;  } //OR H
		int opcodeB5() { OR(registers.L);                                             return 4;  } //OR L
		int opcodeB6() { OR(readByte(registers.HL));                                  return 8;  } //OR (HL)
		int opcodeB7() { OR(registers.A);                                             return 4;  } //OR A
		int opcodeB8() { CP(registers.B);                                             return 4;  } //CP B
		int opcodeB9() { CP(registers.C);                                             return 4;  } //CP C
		int opcodeBA() { CP(registers.D);                                             return 4;  } //CP D
		int opcodeBB() { CP(registers.E);                                             return 4;  } //CP E
		int opcodeBC() { CP(registers.H);                                             return 4;  } //CP H
		int opcodeBD() { CP(registers.L);                                             return 4;  } //CP L
		int opcodeBE() { CP(readByte(registers.HL));                                  return 8;  } //CP (HL)
		int opcodeBF() { CP(registers.A);                                             return 4;  } //CP A
		int opcodeC0() { unkownOpcode();                                                         }
		int opcodeC1() { registers.BC = readShortStack();                             return 12; } //POP BC
		int opcodeC2() { unkownOpcode();                                                         }
		int opcodeC3() { PC = readShort(PC);                                          return 16; } //JP a16
		int opcodeC4() { unkownOpcode();                                                         }
		int opcodeC5() { writeShortStack(registers.BC);                               return 16; } //PUSH BC
		int opcodeC6() { registers.A = addByte(registers.A, readByte(PC++));          return 8;  } //ADD A, d8
		int opcodeC7() { unkownOpcode();                                                         }
		int opcodeC8() { unkownOpcode();                                                         }
		int opcodeC9() { unkownOpcode();                                                         }
		int opcodeCA() { unkownOpcode();                                                         }
		int opcodeCB() { unkownOpcode();                                                         }
		int opcodeCC() { unkownOpcode();                                                         }
		int opcodeCD() { unkownOpcode();                                                         }
		int opcodeCE() { registers.A = ADC(registers.A, readByte(PC++));              return 8;  } //ADC A, d8
		int opcodeCF() { unkownOpcode();                                                         }
		int opcodeD0() { unkownOpcode();                                                         }
		int opcodeD1() { registers.DE = readShortStack();                             return 12; } //POP DE
		int opcodeD2() { unkownOpcode();                                                         }
		int opcodeD3() { unkownOpcode();                                                         }
		int opcodeD4() { unkownOpcode();                                                         }
		int opcodeD5() { writeShortStack(registers.DE);                               return 16; } //PUSH DE
		int opcodeD6() { unkownOpcode();                                                         }
		int opcodeD7() { unkownOpcode();                                                         }
		int opcodeD8() { unkownOpcode();                                                         }
		int opcodeD9() { unkownOpcode();                                                         }
		int opcodeDA() { unkownOpcode();                                                         }
		int opcodeDB() { unkownOpcode();                                                         }
		int opcodeDC() { unkownOpcode();                                                         }
		int opcodeDD() { unkownOpcode();                                                         }
		int opcodeDE() { registers.A = SBC(registers.A, readByte(PC++));              return 8;  } //SBC A, d8
		int opcodeDF() { unkownOpcode();                                                         }
		int opcodeE0() { writeByte(0xFF00 + readByte(PC++), registers.A);             return 12; } //LDH (n), A
		int opcodeE1() { registers.HL = readShortStack();                             return 12; } //POP HL
		int opcodeE2() { writeByte(0xFF00 + registers.C, registers.A);                return 8;  } //LD ($FF00 + C), A
		int opcodeE3() { unkownOpcode();                                                         }
		int opcodeE4() { unkownOpcode();                                                         }
		int opcodeE5() { writeShortStack(registers.HL);                               return 16; } //PUSH HL
		int opcodeE6() { AND(readByte(PC++));                                         return 8;  } //AND d8
		int opcodeE7() { unkownOpcode();                                                         }
		int opcodeE8() {
			//Same as opcode F8, but store result in SP instead
			registers.F = 0;
			i8 n = static_cast<i8>(readByte(PC++));
			unsigned result = SP + n;
			if (result > 0xFFFF)
				setFlag(Flags::Carry);
			if ((n & 0x0F) + (SP & 0x000F) > 0xF)
				setFlag(Flags::HalfCarry);

			SP = static_cast<u16>(result);
			return 16;
		} //ADD SP, r8
		int opcodeE9() { unkownOpcode();                                                         }
		int opcodeEA() { writeShort(readShort(PC++), registers.A);                    return 16; } //LD (nn), A
		int opcodeEB() { unkownOpcode();                                                         }
		int opcodeEC() { unkownOpcode();                                                         }
		int opcodeED() { unkownOpcode();                                                         }
		int opcodeEE() { XOR(readByte(PC++));                                         return 8;  } //XOR d8
		int opcodeEF() { unkownOpcode();                                                         }
		int opcodeF0() { registers.A = 0xFF00 + readByte(PC++);                       return 12; } //LD A, ($FF00 + n)
		int opcodeF1() { registers.AF = readShortStack();                             return 12; } //POP AF
		int opcodeF2() { registers.A = readByte(0xFF00 + registers.C);                return 8;  } //LD A, (C)
		int opcodeF3() { unkownOpcode();                                                         }
		int opcodeF4() { unkownOpcode();                                                         }
		int opcodeF5() { writeShortStack(registers.AF);                               return 16; } //PUSH AF
		int opcodeF6() { OR(readByte(PC++));                                          return 8;  } //OR d8
		int opcodeF7() { unkownOpcode();                                                         }
		int opcodeF8() {
			//Put SP + n effective address into HL
			registers.F = 0;
			i8 n = static_cast<i8>(readByte(PC++));
			unsigned result = SP + n;
			if (result > 0xFFFF)
				setFlag(Flags::Carry);
			if ((n & 0x0F) + (SP & 0x000F) > 0xF)
				setFlag(Flags::HalfCarry);

			registers.HL = static_cast<u16>(result);
			return 12;
		} //LDHL SP, n
		int opcodeF9() { SP = registers.HL;                                           return 8;  } //LD SP, HL
		int opcodeFA() { registers.A = readShort(PC++);                               return 16; } //LD A, (nn)
		int opcodeFB() { unkownOpcode();                                                         }
		int opcodeFC() { unkownOpcode();                                                         }
		int opcodeFD() { unkownOpcode();                                                         }
		int opcodeFE() { CP(readByte(PC++));                                          return 8;  } //CP d8
		int opcodeFF() { unkownOpcode();                                                         }
	}
}
