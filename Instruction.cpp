/*
 * Instruction.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: jbb
 */

#include "Instruction.h"
#include <iomanip>

const char* ITokenName[] = {
    "NONE", "sll", "srl", "jr", "add", "addu", "sub", "subu", "and",
    "or", "xor", "nor", "slt", "sltu", "j", "jal", "beq",
    "bne", "addi", "addiu", "slti", "sltiu", "andi", "ori", "xori",
    "lui", "lb", "lh", "lw", "lbu", "lhu", "sb", "sh", "sw",
    "syscall"
};

const char* IFormatName[] = { "NONE", "R_TYPE", "I_TYPE", "J_TYPE" };
const char* XTypeName[] =   { "NONE", "ALU", "SHIFT", "LOAD", "STORE", "BRANCH", "JUMP", "OTHER" };

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
  rs      (0),
  rt      (0),
  rd      (0),
  shamt   (0),
  imm     (0),
  target  (0)
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
    // Add remaining cases for func files
    default:
      break;
    }
    break;
  case 2:
    token = J;
    format = J_TYPE;
    xtype = JUMP;
    break;
  // Add remaining cases for opcodes
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
  return raw;
}

/*
 * This function should sign extend the 8-bit value n
 * to 32 bits and return it
 */
unsigned Instruction::signExtend8(unsigned n) {
  return n;
}

/*
 * This function should sign extend the 16-bit value n
 * to 32 bits and return it
 */
unsigned Instruction::signExtend16(unsigned n) {
  return n;
}

