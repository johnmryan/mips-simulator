/*
 * Instruction.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: jbb
 */
#include "RegFile.h"
#include "Memory.h"
#include "Instruction.h"
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
	format  (IFORMAT_NONE),
	xtype   (XTYPE_NONE),
	token   (ITOKEN_NONE),
	opcode  (bitRange(31, 26)),
	func    (bitRange(5, 0)),
	rs      (bitRange(25,21)),
	rt      (bitRange(20,16)),
	rd      (bitRange(15,11)),
	shamt   (bitRange(10,6)),
	imm     (bitRange(15,0)),
	target  (bitRange(15,0))
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
		case 8:
			token = JR;
			xtype = JUMP;
			break;
		case 12:
			token = SYSCALL;
			xtype = OTHER;
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
	default:
		break;
	}
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
			sprintf(buf, "%08x  %s $%u, $%u, $%u", raw, ITokenName[token], rd, rs, rt);
			break;
		case SHIFT:
			sprintf(buf, "%08x  %s $%u, $%u, $%u", raw, ITokenName[token], rd, rt, shamt);
			break;
		case JUMP:
			sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rs);
			break;
		default:
			sprintf(buf, "%08x  %s", raw, ITokenName[token]);
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
			sprintf(buf, "%08x  %s $%u, $%u, %d", raw, ITokenName[token], rs, rt, signExtend16(imm));
			break;
		default:
			sprintf(buf, "%08x  %s", raw, ITokenName[token]);
		}
		break;
	case J_TYPE:
		sprintf(buf, "%08x  %s 0x%x", raw, ITokenName[token], target<<2);
		break;
	default:
		sprintf(buf, "%08x  %s", raw, ITokenName[token]);
	}
	string s(buf);
	s.insert(s.end(), 32 - s.size(), ' ');
	return s;
}

/*
 * This function should operate on the 32-bit raw value
 * and return a value consisting of the range of bits
 * between bit positions hi and lo, inclusive
 */
unsigned Instruction::bitRange(unsigned hi, unsigned lo) {
	// logical left shift so that hi is now in position 31 and
	// then logical right shift so that low is in position 0
	unsigned tempRaw = raw;
	int shiftLeftAmount = 31 - hi;
	int shiftRightAmount = shiftLeftAmount + lo;
	tempRaw = tempRaw << shiftLeftAmount;
	tempRaw = tempRaw >> shiftRightAmount;

	return tempRaw;
}

/*
 * This function should sign extend the 8-bit value n
 * to 32 bits and return it
 */
unsigned Instruction::signExtend8(unsigned n) {
	unsigned leadingBit = n >> 7;
	if(leadingBit == 0) {
		// n already has leading 0's by default
		return n;
	} else {
		// leading bit == 1
		// bits 31:8 should all be 1 without affecting first 8 bits
		unsigned leading1s = 0b11111111111111111111111100000000;
		return n | leading1s;
	}
}

/*
 * This function should sign extend the 16-bit value n
 * to 32 bits and return it
 */
unsigned Instruction::signExtend16(unsigned n) {
	unsigned leadingBit = n >> 15;
	if(leadingBit == 0) {
		// n already has leading 0's by default
		return n;
	} else {
		// leading bit == 1
		// bits 31:16 should all be 1 without affecting first 16 bits
		unsigned leading1s = 0b11111111111111110000000000000000;
		return n | leading1s;
	}
}

string Instruction::resultStr() {
  char buf[64];
  switch (format) {
  case R_TYPE:
    switch (xtype) {
    case ALU:
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

bool Instruction::exec() {
  //
  // NOTE: Assumes pc has been pre-incremented
  // Important for branch instruction operation
  //
  bool keepGoing = true;
  pc += 4;
  switch(token) {
  case SLL:
    break;
  case SRL:
    break;
  case ADD:
    break;
  case ADDU:
    break;
  case SUB:
    break;
  case SUBU:
    break;
  case AND:
    break;
  case OR:
    break;
  case XOR:
    break;
  case NOR:
    break;
  case SLT:
    reg[rd] = ((int) reg[rs] < (int) reg[rt]) ? 1 : 0;
    break;
  case SLTU:
    break;
  case JR:
    pc = reg[rs];
    break;
  case J:
    break;
  case JAL:
    break;
  case BEQ:
    // note pc was pre-incremented, need to subtract 4 from branch offset
    break;
  case BNE:
    // note pc was pre-incremented, need to subtract 4 from branch offset
    break;
  case ADDI:
    break;
  case ADDIU:
    break;
  case SLTI:
    break;
  case SLTIU:
    break;
  case ANDI:
    break;
  case ORI:
    reg[rt] = reg[rs] | imm;
    break;
  case XORI:
    break;
  case LUI:
    break;
  case LB:
    reg[rt] = signExtend8(M.read8(reg[rs] + signExtend16(imm)));
    break;
  case LH:
    break;
  case LW:
    break;
  case LBU:
    break;
  case LHU:
    break;
  case SB:
    break;
  case SH:
    break;
  case SW:
    break;
  case SYSCALL:
    keepGoing = false;
    break;
  default:
    break;
  }
  ++instructionCount;
  ++itokenCounts[token];
  ++xtypeCounts[xtype];
  return keepGoing;
}
