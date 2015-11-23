/*
 * Instruction.h
 *
 *  Created on: Sep 13, 2015
 *      Author: jbb
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "global.h"

using namespace std;

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
  bool exec();
  void print();
  string str();
  string resultStr();
  IToken getToken()  { return token; }
  XType getXType()   { return xtype; }
  unsigned bitRange(unsigned hi, unsigned lo);
  unsigned signExtend8(unsigned n);
  unsigned signExtend16(unsigned n);
};

#endif /* INSTRUCTION_H_ */
