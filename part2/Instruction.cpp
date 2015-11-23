/*
 * Instruction.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: jbb
 */

#include "Instruction.h"
#include "RegFile.h"
#include "Memory.h"
#include <iomanip>

/*
 * This procedure should decode the 32-bit instruction
 * machineCode and instantiate it as an Instruction object
 * The decoding process includes extracting values from the
 * machineCode instruction for the opcode, func, rs, rt, rd,
 * shamt, imm, and target fields, as well as assigning a format,
 * token, and execution type (xtype)
 */
	Instruction::Instruction(unsigned machineCode)
: raw     (machineCode),
	opcode  (bitRange(31, 26)),
	func    (bitRange(5,  0)),
	rs      (bitRange(25, 21)),
	rt      (bitRange(20, 16)),
	rd      (bitRange(15, 11)),
	shamt   (bitRange(10, 6)),
	imm     (bitRange(15, 0)),
	target  (bitRange(25, 0))
{
	switch (opcode) {
		case 0:
			format = R_TYPE;
			switch(func) {
				case 0:
					token = SLL;
					xtype = SHIFT;
					break;
				case 2:
					token = SRL;
					xtype = SHIFT;
					break;
				case 3:
					token = SRA;
					xtype = SHIFT;
					break;
				case 4:
					token = SLLV;
					xtype = SHIFT;
					break;
				case 6:
					token = SRLV;
					xtype = SHIFT;
					break;
				case 7:
					token = SRAV;
					xtype = SHIFT;
					break;
				case 8:
					token = JR;
					xtype = JUMP;
					break;
				case 9:
					token = JALR;
					xtype = JUMP;
					break;
				case 12:
					token = SYSCALL;
					xtype = OTHER;
					break;
				case 16:
					token = MFHI;
					xtype = ALU;
					break;
				case 17:
					token = MTHI;
					xtype = ALU;
					break;
				case 18:
					token = MFLO;
					xtype = ALU;
					break;
				case 19:
					token = MTLO;
					xtype = ALU;
					break;
				case 24:
					token = MULT;
					xtype = ALU;
					break;
				case 25:
					token = MULTU;
					xtype = ALU;
					break;
				case 26:
					token = DIV;
					xtype = ALU;
					break;
				case 27:
					token = DIVU;
					xtype = ALU;
					break;
				case 32:
					token = ADD;
					xtype = ALU;
					break;
				case 33:
					token = ADDU;
					xtype = ALU;
					break;
				case 34:
					token = SUB;
					xtype = ALU;
					break;
				case 35:
					token = SUBU;
					xtype = ALU;
					break;
				case 36:
					token = AND;
					xtype = ALU;
					break;
				case 37:
					token = OR;
					xtype = ALU;
					break;
				case 38:
					token = XOR;
					xtype = ALU;
					break;
				case 39:
					token = NOR;
					xtype = ALU;
					break;
				case 42:
					token = SLT;
					xtype = ALU;
					break;
				case 43:
					token = SLTU;
					xtype = ALU;
					break;
				default:
					printf("unknown func:  raw=%08x  opcode=%u  func=%u\n", raw, opcode, func);
					assert(false && "unknown func");
			}
			break;
		case 1:
			format = I_TYPE;
			xtype = BRANCH;
			switch (rt) {
				case 0:
					token = BLTZ;
					break;
				case 1:
					token = BGEZ;
					break;
				default:
					printf("unknown opcode 1 subtype: raw=%08x  rt=%u\n", raw, rt);
					assert(false && "unknown opcode 1 subtype");
					break;
			}
			break;
		case 2:
			token = J;
			format = J_TYPE;
			xtype = JUMP;
			break;
		case 3:
			token = JAL;
			format = J_TYPE;
			xtype = JUMP;
			break;
		case 4:
			token = BEQ;
			format = I_TYPE;
			xtype = BRANCH;
			break;
		case 5:
			token = BNE;
			format = I_TYPE;
			xtype = BRANCH;
			break;
		case 6:
			token = BLEZ;
			format = I_TYPE;
			xtype = BRANCH;
			break;
		case 7:
			token = BGTZ;
			format = I_TYPE;
			xtype = BRANCH;
			break;
		case 8:
			token = ADDI;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 9:
			token = ADDIU;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 10:
			token = SLTI;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 11:
			token = SLTIU;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 12:
			token = ANDI;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 13:
			token = ORI;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 14:
			token = XORI;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 15:
			token = LUI;
			format = I_TYPE;
			xtype = ALU;
			break;
		case 32:
			token = LB;
			format = I_TYPE;
			xtype = LOAD;
			break;
		case 33:
			token = LH;
			format = I_TYPE;
			xtype = LOAD;
			break;
		case 35:
			token = LW;
			format = I_TYPE;
			xtype = LOAD;
			break;
		case 36:
			token = LBU;
			format = I_TYPE;
			xtype = LOAD;
			break;
		case 37:
			token = LHU;
			format = I_TYPE;
			xtype = LOAD;
			break;
		case 40:
			token = SB;
			format = I_TYPE;
			xtype = STORE;
			break;
		case 41:
			token = SH;
			format = I_TYPE;
			xtype = STORE;
			break;
		case 43:
			token = SW;
			format = I_TYPE;
			xtype = STORE;
			break;
		default:
			printf("unknown opcode: raw=%08x  opcode=%u\n", raw, opcode);
			assert(false && "unknown opcode");
			break;
	}
}

bool Instruction::exec() {
	//
	// NOTE: Assumes pc has been pre-incremented
	// Important for branch instruction operation
	//
	uint64_t p;  // product for mult, div
	bool keepGoing = true;
	pc += 4;
	switch(token) {
		case SLL:
			reg[rd] = reg[rt] << shamt;
			break;
		case SRL:
			reg[rd] = reg[rt] >> shamt;
			break;
		case SRA:
			reg[rd] = (int) reg[rt] >> shamt;
			break;
		case SLLV:
			reg[rd] = reg[rt] << reg[rs];
			break;
		case SRLV:
			reg[rd] = reg[rt] >> reg[rs];
			break;
		case SRAV:
			reg[rd] = (int) reg[rt] >> reg[rs];
			break;
		case ADD:
			reg[rd] = reg[rs] + reg[rt];
			break;
		case ADDU:
			reg[rd] = reg[rs] + reg[rt];
			break;
		case SUB:
			reg[rd] = reg[rs] - reg[rt];
			break;
		case SUBU:
			reg[rd] = reg[rs] - reg[rt];
			break;
		case AND:
			reg[rd] = reg[rs] & reg[rt];
			break;
		case OR:
			reg[rd] = reg[rs] | reg[rt];
			break;
		case XOR:
			reg[rd] = reg[rs] ^ reg[rt];
			break;
		case NOR:
			reg[rd] = ~(reg[rs] | reg[rt]);
			break;
		case MULT:
			p = (int) reg[rs] * (int) reg[rt];
			hi = p >> 32L;
			lo = p & 0x00000000ffffffffL;
			break;
		case MULTU:
			p = (uint64_t) reg[rs] * (uint64_t) reg[rt];
			hi = p >> 32L;
			lo = p & 0x00000000ffffffffL;
			break;
		case DIV:
			lo = (int) reg[rs] / (int) reg[rt];
			hi = (int) reg[rs] % (int) reg[rt];
			break;
		case DIVU:
			lo = reg[rs] / reg[rt];
			hi = reg[rs] % reg[rt];
			break;
		case SLT:
			reg[rd] = ((int) reg[rs] < (int) reg[rt]) ? 1 : 0;
			break;
		case SLTU:
			reg[rd] = (reg[rs] < reg[rt]) ? 1 : 0;
			break;
		case MFHI:
			reg[rd] = hi;
			break;
		case MFLO:
			reg[rd] = lo;
			break;
		case MTHI:
			hi = reg[rs];
			break;
		case MTLO:
			lo = reg[rs];
			break;
		case JR:
			pc = reg[rs];
			break;
		case J:
			pc = (target << 2) | (pc & 0xf0000000);
			break;
		case JAL:
			reg[31] = pc;   // pc has been pre-incremented
			pc = (target << 2) | (pc & 0xf0000000);
			break;
		case JALR:
			reg[31] = pc;
			pc = reg[rs];
			break;
		case BEQ:
			// note pc was pre-incremented
			pc = (reg[rs] == reg[rt]) ? pc + (signExtend16(imm) << 2) - 4 : pc;
			break;
		case BNE:
			pc = (reg[rs] != reg[rt]) ? pc + (signExtend16(imm) << 2) - 4 : pc;
			break;
		case BGEZ:
			pc = ((int) reg[rs] >= 0) ? pc + (signExtend16(imm) << 2) - 4 : pc;
			break;
		case BGTZ:
			pc = ((int) reg[rs] > 0) ? pc + (signExtend16(imm) << 2) - 4 : pc;
			break;
		case BLEZ:
			pc = ((int) reg[rs] <= 0) ? pc + (signExtend16(imm) << 2) - 4 : pc;
			break;
		case BLTZ:
			pc = ((int) reg[rs] < 0) ? pc + (signExtend16(imm) << 2) - 4 : pc;
			break;
		case ADDI:
			reg[rt] = reg[rs] + signExtend16(imm);
			break;
		case ADDIU:
			reg[rt] = reg[rs] + signExtend16(imm);;
			break;
		case SLTI:
			reg[rt] = ((int) reg[rs] < (int) signExtend16(imm)) ? 1 : 0;
			break;
		case SLTIU:
			reg[rt] = (reg[rs] < signExtend16(imm)) ? 1 : 0;
			break;
		case ANDI:
			reg[rt] = reg[rs] & imm;
			break;
		case ORI:
			reg[rt] = reg[rs] | imm;
			break;
		case XORI:
			reg[rt] = reg[rs] ^ imm;
			break;
		case LUI:
			reg[rt] = (imm << 16);
			break;
		case LB:
			reg[rt] = signExtend8(M.read8(reg[rs] + signExtend16(imm)));
			break;
		case LH:
			reg[rt] = signExtend16(M.read16(reg[rs] + signExtend16(imm)));
			break;
		case LW:
			reg[rt] = M.read32(reg[rs] + signExtend16(imm));
			break;
		case LBU:
			reg[rt] = M.read8(reg[rs] + signExtend16(imm));
			break;
		case LHU:
			reg[rt] = M.read16(reg[rs] + signExtend16(imm));
			break;
		case SB:
			M.write8(reg[rt], reg[rs] + signExtend16(imm));
			break;
		case SH:
			M.write16(reg[rt], reg[rs] + signExtend16(imm));
			break;
		case SW:
			M.write32(reg[rt], reg[rs] + signExtend16(imm));
			break;
		case SYSCALL:
			switch (reg[2]) {
				case 1:
					printf("%d", reg[4]);
					break;
				case 4:
					printf("%s", M.getMemoryPtr(reg[4]));
					break;
				case 9:
					reg[2] = M.alloc(reg[4]);
					break;
				case 10:
					keepGoing = false;
					break;
				case 11:
					printf("%c", reg[4]);
					break;
				default:
					printf("Undefined syscall code: %d\n", reg[2]);
					//      assert(false && "undefined syscall code");
					break;
			}
			break;
		default:
			printf("undefined opcode: %u\n", opcode);
			assert(false);
			break;
	}
	++instructionCount;
	++itokenCounts[token];
	++xtypeCounts[xtype];
	return keepGoing;
}

/*
 * Helper function to print decoded instruction results
 */
void Instruction::print() {
	if (token == ITOKEN_NONE) {
		printf("0x%08x  Unable to decode\n", raw);
		return;
	}

	printf("%08x  %-8s %-8s %-8s ", raw, ITokenName[token], IFormatName[format], XTypeName[xtype]);
	if (format == R_TYPE)
		printf("rs=%2u  rt=%2u  rd=%2u  shamt=%u\n", rs, rt, rd, shamt);
	else if (format == I_TYPE)
		printf("rs=%2u  rt=%2u  imm=0x%x\n", rs, rt, imm);
	else if (format == J_TYPE)
		printf("target=0x%x\n", target);
}

/*
 * Function to produce a formatted string with the assembly language
 * representation of a decoded instruction.
 */
string Instruction::str() {
	char buf[64];
	switch (format) {
		case R_TYPE:
			switch (xtype) {
				case ALU:
					if (token == MULT || token == MULTU || token == DIV || token == DIVU) {
						sprintf(buf, "%08x  %s $%u, $%u", raw, ITokenName[token], rs, rt);
					}
					else if (token == MTHI || token == MTLO) {
						sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rs);
					}
					else if (token == MFHI || token == MFLO) {
						sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rd);
					}
					else {
						sprintf(buf, "%08x  %s $%u, $%u, $%u", raw, ITokenName[token], rd, rs, rt);
					}
					break;
				case SHIFT:
					if (token == SLLV || token == SRLV || token == SRAV) {
						sprintf(buf, "%08x  %s $%u, $%u, $%u", raw, ITokenName[token], rd, rs, rt);
					}
					else
					{
						sprintf(buf, "%08x  %s $%u, $%u, %u", raw, ITokenName[token], rd, rt, shamt);
					}
					break;
				case JUMP:
					sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rs);
					break;
				default:
					sprintf(buf, "%08x  %s", raw, ITokenName[token]);
					break;
			}
			break;
		case I_TYPE:
			switch (xtype) {
				case ALU:
					sprintf(buf, "%08x  %s $%u, $%u, %d", raw, ITokenName[token], rt, rs, signExtend16(imm));
					break;
				case LOAD:
				case STORE:
					sprintf(buf, "%08x  %s $%u, %d($%u)", raw, ITokenName[token], rt, signExtend16(imm), rs);
					break;
				case BRANCH:
					if (token == BGEZ || token == BGTZ || token == BLEZ || token == BLTZ) {
						sprintf(buf, "%08x  %s $%u, %d", raw, ITokenName[token], rs, signExtend16(imm));
					}
					else {
						sprintf(buf, "%08x  %s $%u, $%u, %d", raw, ITokenName[token], rs, rt, signExtend16(imm));
					}
					break;
				default:
					sprintf(buf, "%08x  %s", raw, ITokenName[token]);
					break;
			}
			break;
		case J_TYPE:
			sprintf(buf, "%08x  %s 0x%x", raw, ITokenName[token], target<<2);
			break;
		default:
			sprintf(buf, "%08x  %s", raw, ITokenName[token]);
			break;
	}
	string s(buf);
	s.insert(s.end(), 36 - s.size(), ' ');
	return s;
}

string Instruction::resultStr() {
	char buf[64];
	switch (format) {
		case R_TYPE:
			switch (xtype) {
				case ALU:
					if (token == MULT || token == MULTU || token == DIV || token == DIVU) {
						sprintf(buf, "| $hi = 0x%08x  $lo = 0x%08x", hi, lo);
					}
					else if (token == MTHI)  {
						sprintf(buf, "| $hi = 0x%x", hi);
					}
					else if (token == MTLO)  {
						sprintf(buf, "| $lo = 0x%x", lo);
					}
					else {
						sprintf(buf, "| $%u = 0x%x", rd, reg[rd]);
					}
					break;
				case SHIFT:
					sprintf(buf, "| $%u = 0x%x", rd, reg[rd]);
					break;
				case JUMP:
					sprintf(buf, "| pc = %08x", pc);
					break;
				default:
					sprintf(buf, "|");
					break;
			}
			break;
		case I_TYPE:
			switch (xtype) {
				case ALU:
				case LOAD:
					sprintf(buf, "| $%u = 0x%x", rt, reg[rt]);
					break;
				case STORE:
					sprintf(buf, "| M[%08x] = 0x%08x", reg[rs]+imm, M.read32(reg[rs]+imm));
					break;
				case BRANCH:
					sprintf(buf, "| pc = %08x", pc);
					break;
				default:
					sprintf(buf, "unformatted");
					break;
			}
			break;
		case J_TYPE:
			sprintf(buf, "| pc = %08x", pc);
			break;
		default:
			sprintf(buf, "|");
			break;
	}
	return string(buf);
}

/*
 * This function should operate on the 32-bit raw value
 * and return a value consisting of the range of bits
 * between bit positions hi and lo, inclusive
 */
unsigned Instruction::bitRange(unsigned hi, unsigned lo) {
	unsigned mask = (1 << (hi - lo + 1)) - 1;
	return (raw >> lo) & mask;
}

/*
 * This function should sign extend the 8-bit value n
 * to 32 bits and return it
 */
unsigned Instruction::signExtend8(unsigned n) {
	return (((int) n << 24) >> 24);
}

/*
 * This function should sign extend the 16-bit value n
 * to 32 bits and return it
 */
unsigned Instruction::signExtend16(unsigned n) {
	return (((int) n << 16) >> 16);
}

