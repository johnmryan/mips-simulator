/*
 * Instruction.h
 *
 *  Created on: Sep 13, 2015
 *      Author: jbb
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
#include <stdio.h>
#include <assert.h>
#include <string>
using namespace std;

enum IToken {
  ITOKEN_NONE, SLL, SRL, JR, ADD, ADDU, SUB, SUBU, AND,
  OR, XOR, NOR, SLT, SLTU, J, JAL, BEQ,
  BNE, ADDI, ADDIU, SLTI, SLTIU, ANDI, ORI, XORI,
  LUI, LB, LH, LW, LBU, LHU, SB, SH, SW,
  SYSCALL
};

enum IFormat { IFORMAT_NONE, R_TYPE, I_TYPE, J_TYPE };
enum XType   { XTYPE_NONE, ALU, SHIFT, LOAD, STORE, BRANCH, JUMP, OTHER };

class Instruction {
  unsigned raw;
  IFormat  format;
  XType    xtype;
  IToken   token;
  unsigned opcode;
  unsigned func;
  unsigned rs;
  unsigned rt;
  unsigned rd;
  unsigned imm;
  unsigned shamt;
  unsigned target;
public:
  Instruction(unsigned machineCode);
  void print();
  string str();
  IToken getToken()  { return token; }
  unsigned bitRange(unsigned hi, unsigned lo);
  unsigned signExtend8(unsigned n);
  unsigned signExtend16(unsigned n);
};

#endif /* INSTRUCTION_H_ */
