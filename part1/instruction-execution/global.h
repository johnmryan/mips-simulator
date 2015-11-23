/*
 * global.h
 *
 *  Created on: Sep 19, 2015
 *      Author: jbb
 */

#ifndef NDSIM_GLOBAL_H_
#define NDSIM_GLOBAL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TEST(e) \
  if (!(e)) \
    printf("* TEST   FAIL: %s, %s line %d in %s\n", #e, __FILE__, __LINE__, __func__); \
  else \
    printf("  TEST   pass: %s, %s line %d in %s\n", #e, __FILE__, __LINE__, __func__);

#define TESTEQ(act, exp) \
  if ((exp) == (act)) \
    cout << "  TESTEQ pass: " << __FILE__ << " line " << dec << __LINE__ << " in " << __func__ << endl; \
  else \
    cout << "* TESTEQ FAIL: " << __FILE__ << " line " << dec << __LINE__ << " in " << __func__ << \
      " EXPECTED= " << dec << exp << "/" << hex << "0x" << exp << \
      " ACTUAL= " << dec << act << "/" << hex << "0x" << act << endl;

class RegFile;
class Memory;

enum IToken {
  ITOKEN_NONE, SLL, SRL, JR, ADD, ADDU, SUB, SUBU, AND,
  OR, XOR, NOR, SLT, SLTU, J, JAL, BEQ,
  BNE, ADDI, ADDIU, SLTI, SLTIU, ANDI, ORI, XORI,
  LUI, LB, LH, LW, LBU, LHU, SB, SH, SW,
  SYSCALL, NUM_ITOKEN
};

enum IFormat { IFORMAT_NONE, R_TYPE, I_TYPE, J_TYPE };
enum XType   { XTYPE_NONE, ALU, SHIFT, LOAD, STORE, BRANCH, JUMP, OTHER, NUM_XTYPE };

extern RegFile reg;
extern Memory M;
extern unsigned pc;
extern bool quietMode;
extern bool bareMachineMode;
extern unsigned instructionCount;
extern unsigned itokenCounts[NUM_ITOKEN];
extern unsigned xtypeCounts[NUM_XTYPE];

extern const char* ITokenName[];
extern const char* IFormatName[];
extern const char* XTypeName[];

#endif /* NDSIM_GLOBAL_H_ */
