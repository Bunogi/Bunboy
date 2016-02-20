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
		int opcode00() {                                  return 4;  } //NOP
		int opcode01() { set16Reg(B, C, readShort(++PC)); return 12; } //LD BC, nn
		int opcode02() { A = readByte(BC());              return 8;  } //LD (BC), A
		int opcode03() { INC16(B, C);                     return 8;  } //INC BC
		int opcode04() { INC(B);                          return 4;  } //INC B
		int opcode05() { DEC(B);                          return 4;  } //DEC B
		int opcode06() { writeByte(++PC, B);              return 8;  }  //LD B, d8. 
		int opcode07() { unkownOpcode();                             }
		int opcode08() { writeShort(readShort(++PC), SP); return 20; } //LD (nn), SP
		int opcode09() { ADD_HL(BC());                    return 8;  } //ADD HL, BC
		int opcode0A() { writeByte(BC(), A);              return 8;  } //LD A, (BC)
		int opcode0B() { DEC16(B, C);                     return 8;  } //DEC BC
		int opcode0C() { INC(C);                          return 4;  } //INC C
		int opcode0D() { DEC(C);                          return 4;  } //DEC C
		int opcode0E() { writeByte(++PC, C);              return 8;  } //LD C, d8
		int opcode0F() { unkownOpcode();                             }
		int opcode10() { unkownOpcode();                             }
		int opcode11() { set16Reg(D, E, readShort(++PC)); return 12; } //LD DE, nn
		int opcode12() { A = readByte(DE());              return 8;  } //LD (DE), A
		int opcode13() { INC16(D, E);                     return 8;  } //INC DE
		int opcode14() { INC(D);                          return 4;  } //INC D
		int opcode15() { DEC(D);                          return 4;  } //DEC D
		int opcode16() { writeByte(++PC, D);              return 8;  } //LD D, d8
		int opcode17() { unkownOpcode();                             }
		int opcode18() { unkownOpcode();                             }
		int opcode19() { ADD_HL(DE());                    return 8;  } //ADD HL, DE
		int opcode1A() { writeByte(DE(), A);              return 8;  } //LD A, (DE)
		int opcode1B() { DEC16(D, E);                     return 8;  } //DEC DE
		int opcode1C() { INC(E);                          return 4;  } //INC E
		int opcode1D() { DEC(E);                          return 4;  } //DEC E
		int opcode1E() { writeByte(++PC, E);              return 8;  } //LD E, d8
		int opcode1F() { unkownOpcode();                             }
		int opcode20() { unkownOpcode();                             }
		int opcode21() { set16Reg(H, L, readShort(++PC)); return 12; } //LD HL, nn
		int opcode22() { writeByte(HL(), A); INC16(H, L); return 8;  } //LD (HL+, A)
		int opcode23() { INC16(H, L);                     return 8;  } //INC HL
		int opcode24() { INC(H);                          return 4;  } //INC H
		int opcode25() { DEC(H);                          return 4;  } //DEC H
		int opcode26() { writeByte(++PC, H);              return 8;  } //LD H, d8
		int opcode27() { unkownOpcode();                             }
		int opcode28() { unkownOpcode();                             }
		int opcode29() { ADD_HL(HL());                               } //ADD HL, HL
		int opcode2A() { A = readByte(HL()); INC16(H, L); return 8;  } //LD A, (HL+)
		int opcode2B() { DEC16(H, L);                     return 8;  } //DEC HL
		int opcode2C() { INC(L);                          return 4;  } //INC L
		int opcode2D() { DEC(L);                          return 4;  } //DEC L
		int opcode2E() { writeByte(++PC, L);              return 8;  } //LD E, d8
		int opcode2F() { unkownOpcode();                             }
		int opcode30() { unkownOpcode();                             }
		int opcode31() { SP = readShort(++PC);                       } //LD SP, nn
		int opcode32() { writeByte(HL(), A); INC16(H, L); return 12; } //LD (HL-), A
		int opcode33() { SP++;                            return 8;  } //INC SP
		int opcode34() { INC(readByte(HL()));             return 12; } //INC (HL)
		int opcode35() { DEC(readByte(HL()));             return 12; } //DEC (HL)
		int opcode36() { writeByte(HL(), ++PC);           return 12; } //LD (HL), d8
		int opcode37() { unkownOpcode();                             }
		int opcode38() { unkownOpcode();                             }
		int opcode39() { ADD_HL(SP);                      return 8;  } //ADD HL, SP
		int opcode3A() { A = readByte(HL()); DEC16(H, L); return 8;  } //LD A, (HL-)
		int opcode3B() { SP--;                            return 8;  } //DEC SP
		int opcode3C() { INC(A);                          return 4;  } //INC A
		int opcode3D() { DEC(A);                          return 4;  } //DEC A
		int opcode3E() { unkownOpcode();                             }
		int opcode3F() { unkownOpcode();                             }
		int opcode40() { /* B = B; */                     return 4;  } //LD B, B
		int opcode41() { B = C;                           return 4;  } //LD B, C
		int opcode42() { B = D;                           return 4;  } //LD B, D
		int opcode43() { B = E;                           return 4;  } //LD B, E
		int opcode44() { B = H;                           return 4;  } //LD B, H
		int opcode45() { B = L;                           return 4;  } //LD B, L
		int opcode46() { B = readByte(HL());                         } //LD B, (HL)
		int opcode47() { B = A;                           return 4;  } //LD B, A
		int opcode48() { C = B;                           return 4;  } //LD C, B
		int opcode49() { /* C = C; */                     return 4;  } //LD C, C
		int opcode4A() { C = D;                           return 4;  } //LD C, D
		int opcode4B() { C = E;                           return 4;  } //LD C, E
		int opcode4C() { C = H;                           return 4;  } //LD C, H
		int opcode4D() { C = L;                           return 4;  } //LD C, L
		int opcode4E() { C = readByte(HL());                         } //LD C, (HL)
		int opcode4F() { C = A;                           return 4;  } //LD C, A
		int opcode50() { D = B;                           return 4;  } //LD D, B
		int opcode51() { D = C;                           return 4;  } //LD D, C
		int opcode52() { /* D = D; */                     return 4;  } //LD D, D
		int opcode53() { D = E;                           return 4;  } //LD D, E
		int opcode54() { D = H;                           return 4;  } //LD D, H
		int opcode55() { D = L;                           return 4;  } //LD D, L
		int opcode56() { D = readByte(HL());                         } //LD D, (HL)
		int opcode57() { D = A;                                      } //LD D, A
		int opcode58() { E = B;                           return 4;  } //LD E, B
		int opcode59() { E = C;                           return 4;  } //LD E, C
		int opcode5A() { E = D;                           return 4;  } //LD E, D
		int opcode5B() { /* E = E; */                     return 4;  } //LD E, E
		int opcode5C() { E = H;                           return 4;  } //LD E, H
		int opcode5D() { E = L;                           return 4;  } //LD E, L 
		int opcode5E() { E = readByte(HL()); } //LD E, (HL)
		int opcode5F() { E = A;                           return 4;  } //LD E, A
		int opcode60() { H = B;                           return 4;  } //LD H, B
		int opcode61() { H = C;                           return 4;  } //LD H, C
		int opcode62() { H = D;                           return 4;  } //LD H, D
		int opcode63() { H = E;                           return 4;  } //LD H, E
		int opcode64() { /* H = H; */                     return 4;  } //LD H, H
		int opcode65() { H = L;                           return 4;  } //LD H, L
		int opcode66() { H = readByte(HL());              return 4;  } //LD H, (HL)
		int opcode67() { H = A;                           return 4;  } //LD H, A
		int opcode68() { L = B;                           return 4;  } //LD L, B
		int opcode69() { L = D;                           return 4;  } //LD L, D
		int opcode6A() { L = C;                           return 4;  } //LD L, C
		int opcode6B() { L = E;                           return 4;  } //LD L, E
		int opcode6C() { L = H;                           return 4;  } //LD L, H
		int opcode6D() { /* L = L; */                     return 4;  } //LD L, L
		int opcode6E() { L = readByte(HL());              return 8;  } //LD L, (HL)
		int opcode6F() { L = A;                           return 4;  } //LD L, A
		int opcode70() { writeByte(HL(), B);              return 8;  } //LD (HL), B
		int opcode71() { writeByte(HL(), C);              return 8;  } //LD (HL), C
		int opcode72() { writeByte(HL(), D);              return 8;  } //LD (HL), D
		int opcode73() { writeByte(HL(), E);              return 8;  } //LD (HL), E
		int opcode74() { writeByte(HL(), H);              return 8;  } //LD (HL), H
		int opcode75() { writeByte(HL(), L);              return 8;  } //LD (HL), L
		int opcode76() { unkownOpcode();                             } 
		int opcode77() { writeByte(HL(), A);              return 8;  } //LD (HL), A
		int opcode78() { A = B;                           return 4;  } //LD A, B
		int opcode79() { A = C;                           return 4;  } //LD A, C
		int opcode7A() { A = D;                           return 4;  } //LD A, D
		int opcode7B() { A = E;                           return 4;  } //LD A, E
		int opcode7C() { A = H;                           return 4;  } //LD A, H
		int opcode7D() { A = L;                           return 4;  } //LD A, L
		int opcode7E() { A = readByte(HL());              return 8;  } //LD A, (HL) (Read from memory adress at HL)
		int opcode7F() { /* A = A; */                     return 4;  } //LD A, A
		int opcode80() { A = addByte(A, B);               return 4;  } //ADD A, B
		int opcode81() { A = addByte(A, C);               return 4;  } //ADD A, C
		int opcode82() { A = addByte(A, D);               return 4;  } //ADD A, D
		int opcode83() { A = addByte(A, E);               return 4;  } //ADD A, E
		int opcode84() { A = addByte(A, H);               return 4;  } //ADD A, H
		int opcode85() { A = addByte(A, L);               return 4;  } //ADD A, L
		int opcode86() { A = addByte(A, readByte(HL()));  return 8;  } //ADD A, (HL)
		int opcode87() { A = addByte(A, A);               return 4;  } //ADD A, A
		int opcode88() { A = ADC(A, B);                   return 4;  } //ADC A, B
		int opcode89() { A = ADC(A, C);                   return 4;  } //ADC A, C
		int opcode8A() { A = ADC(A, D);                   return 4;  } //ADC A, D
		int opcode8B() { A = ADC(A, E);                   return 4;  } //ADC A, E
		int opcode8C() { A = ADC(A, H);                   return 4;  } //ADC A, H
		int opcode8D() { A = ADC(A, L);                   return 4;  } //ADC A, L
		int opcode8E() { A = ADC(A, readByte(HL()) );     return 8;  } //ADC A, (HL)
		int opcode8F() { A = ADC(A, A);                   return 4;  } //ADC A, A
		int opcode90() { A = subByte(A, B);               return 4;  } //SUB B
		int opcode91() { A = subByte(A, C);               return 4;  } //SUB C
		int opcode92() { A = subByte(A, D);               return 4;  } //SUB D
		int opcode93() { A = subByte(A, E);               return 4;  } //SUB E
		int opcode94() { A = subByte(A, H);               return 4;  } //SUB H
		int opcode95() { A = subByte(A, L);               return 4;  } //SUB L
		int opcode96() { A = subByte(A, readByte(HL()));  return 8;  } //SUB(HL)
		int opcode97() { A = subByte(A, A);               return 4;  } //SUB A
		int opcode98() { A = SBC(A, B);                   return 4;  } //SBC A, B
		int opcode99() { A = SBC(A, C);                   return 4;  } //SBC A, C
		int opcode9A() { A = SBC(A, D);                   return 4;  } //SBC A, D
		int opcode9B() { A = SBC(A, E);                   return 4;  } //SBC A, E
		int opcode9C() { A = SBC(A, H);                   return 4;  } //SBC A, H
		int opcode9D() { A = SBC(A, L);                   return 4;  } //SBC A, L
		int opcode9E() { A = SBC(A, readByte(HL()));      return 8;  } //SBC A, (HL)
		int opcode9F() { A = SBC(A, A);                   return 4;  } //SBC A, A
		int opcodeA0() { AND(B);                          return 4;  } //AND B
		int opcodeA1() { AND(C);                          return 4;  } //AND C
		int opcodeA2() { AND(D);                          return 4;  } //AND D
		int opcodeA3() { AND(E);                          return 4;  } //AND E
		int opcodeA4() { AND(H);                          return 4;  } //AND H
		int opcodeA5() { AND(L);                          return 4;  } //AND L
		int opcodeA6() { AND(readByte(HL()));                        } //AND (HL)
		int opcodeA7() { AND(A);                          return 4;  } //AND A
		int opcodeA8() { XOR(B);                          return 4;  } //XOR B
		int opcodeA9() { XOR(C);                          return 4;  } //XOR C
		int opcodeAA() { XOR(D);                          return 4;  } //XOR D
		int opcodeAB() { XOR(E);                          return 4;  } //XOR E
		int opcodeAC() { XOR(H);                          return 4;  } //XOR H
		int opcodeAD() { XOR(L);                          return 4;  } //XOR L
		int opcodeAE() { XOR(readByte(HL()));                        } //XOR (HL)
		int opcodeAF() { XOR(A);                          return 4;  } //XOR A
		int opcodeB0() { OR(B);                           return 4;  } //OR B
		int opcodeB1() { OR(C);                           return 4;  } //OR C
		int opcodeB2() { OR(D);                           return 4;  } //OR D
		int opcodeB3() { OR(E);                           return 4;  } //OR E
		int opcodeB4() { OR(H);                           return 4;  } //OR H
		int opcodeB5() { OR(L);                           return 4;  } //OR L
		int opcodeB6() { OR(readByte(HL()));                         } //OR (HL)
		int opcodeB7() { OR(A);                           return 4;  } //OR A
		int opcodeB8() { CP(B);                           return 4;  } //CP B
		int opcodeB9() { CP(C);                           return 4;  } //CP C
		int opcodeBA() { CP(D);                           return 4;  } //CP D
		int opcodeBB() { CP(E);                           return 4;  } //CP E
		int opcodeBC() { CP(H);                           return 4;  } //CP H
		int opcodeBD() { CP(L);                           return 4;  } //CP L
		int opcodeBE() { CP(readByte(HL()));                         } //CP (HL)
		int opcodeBF() { CP(A);                           return 4;  } //CP A
		int opcodeC0() { unkownOpcode();                             }
		int opcodeC1() { set16Reg(B, C, readShortStack());return 12; } //POP BC
		int opcodeC2() { unkownOpcode();                             }
		int opcodeC3() { PC = readShort(PC + 1);          return 16; } //JP a16
		int opcodeC4() { unkownOpcode();                             }
		int opcodeC5() { writeShortStack(BC());           return 16; } //PUSH BC
		int opcodeC6() { A = addByte(A, readByte(++PC));  return 8;  } //ADD A, d8
		int opcodeC7() { unkownOpcode();                             }
		int opcodeC8() { unkownOpcode();                             }
		int opcodeC9() { unkownOpcode();                             }
		int opcodeCA() { unkownOpcode();                             }
		int opcodeCB() { unkownOpcode();                             }
		int opcodeCC() { unkownOpcode();                             }
		int opcodeCD() { unkownOpcode();                             }
		int opcodeCE() { A = ADC(A, readByte(++PC));      return 8;  } //ADC A, d8
		int opcodeCF() { unkownOpcode();                             }
		int opcodeD0() { unkownOpcode();                             }
		int opcodeD1() { set16Reg(D, E, readShortStack());return 12; } //POP DE
		int opcodeD2() { unkownOpcode();                             }
		int opcodeD3() { unkownOpcode();                             }
		int opcodeD4() { unkownOpcode();                             }
		int opcodeD5() { writeShortStack(DE());           return 16; } //PUSH DE
		int opcodeD6() { unkownOpcode();                             }
		int opcodeD7() { unkownOpcode();                             }
		int opcodeD8() { unkownOpcode();                             }
		int opcodeD9() { unkownOpcode();                             }
		int opcodeDA() { unkownOpcode();                             }
		int opcodeDB() { unkownOpcode();                             }
		int opcodeDC() { unkownOpcode();                             }
		int opcodeDD() { unkownOpcode();                             }
		int opcodeDE() { A = SBC(A, readByte(++PC));      return 8;  } //SBC A, d8
		int opcodeDF() { unkownOpcode();                             }
		int opcodeE0() { writeByte(0xFF00 + readByte(++PC), A); return 12; } //LDH (n), A
		int opcodeE1() { set16Reg(H, L, readShortStack());           } //POP HL
		int opcodeE2() { writeByte(0xFF00 + C, A);        return 8;  } //LD ($FF00 + C), A
		int opcodeE3() { unkownOpcode();                             }
		int opcodeE4() { unkownOpcode();                             }
		int opcodeE5() { writeShortStack(HL());           return 16; } //PUSH HL
		int opcodeE6() { AND(readByte(++PC));             return 8;  } //AND d8
		int opcodeE7() { unkownOpcode();                             }
		int opcodeE8() { 
			//Same as opcode F8, but store result in SP instead
			F = 0;
			i8 n = static_cast<i8>(readByte(++PC));
			unsigned result = SP + n;
			if (result > 0xFFFF)
				setFlag(Flags::Carry);
			if ((n & 0x0F) + (SP & 0x000F) > 0xF)
				setFlag(Flags::HalfCarry);

			SP = static_cast<u16>(result);
			return 16;
		} //ADD SP, r8
		int opcodeE9() { unkownOpcode();                             }
		int opcodeEA() { writeShort(readShort(++PC), A);  return 16; } //LD (nn), A
		int opcodeEB() { unkownOpcode();                             }
		int opcodeEC() { unkownOpcode();                             }
		int opcodeED() { unkownOpcode();                             }
		int opcodeEE() { XOR(readByte(++PC));             return 8;  } //XOR d8
		int opcodeEF() { unkownOpcode();                             }
		int opcodeF0() { A = 0xFF00 + readByte(++PC);     return 12; } //LD A, ($FF00 + n)
		int opcodeF1() { set16Reg(A, F, readShortStack());return 12; } //POP AF
		int opcodeF2() { A = readByte(0xFF00 + C);        return 8;  } //LD A, (C)
		int opcodeF3() { unkownOpcode();                             }
		int opcodeF4() { unkownOpcode();                             }
		int opcodeF5() { writeShortStack(AF());           return 16; } //PUSH AF
		int opcodeF6() { OR(readByte(++PC));              return 8;  } //OR d8
		int opcodeF7() { unkownOpcode();                             }
		int opcodeF8() { 
			//Put SP + n effective address into HL
			F = 0;
			i8 n = static_cast<i8>(readByte(++PC));
			unsigned result = SP + n;
			if (result > 0xFFFF)
				setFlag(Flags::Carry);
			if ((n & 0x0F) + (SP & 0x000F) > 0xF)
				setFlag(Flags::HalfCarry);

			set16Reg(H, L, static_cast<u16>(result));
			return 12;
		} //LDHL SP, n
		int opcodeF9() { SP = HL();                       return 8;  } //LD SP, HL
		int opcodeFA() { A = readShort(++PC);             return 16; } //LD A, (nn)
		int opcodeFB() { unkownOpcode();                             }
		int opcodeFC() { unkownOpcode();                             }
		int opcodeFD() { unkownOpcode();                             }
		int opcodeFE() { CP(readByte(++PC));              return 8;  } //CP d8
		int opcodeFF() { unkownOpcode();                             }
	}
}
