/*
 * global.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: jbb
 */

#include "global.h"
#include "RegFile.h"
#include "Memory.h"

RegFile reg;
unsigned lo;
unsigned hi;
Memory M;
unsigned pc;
bool quietMode;
bool bareMachineMode;
unsigned instructionCount;
unsigned itokenCounts[NUM_ITOKEN];
unsigned xtypeCounts[NUM_XTYPE];

const char* ITokenName[] = {
	"NONE", "sll", "srl", "sra", "sllv", "srlv", "srav",
	"jr", "add", "addu", "sub", "subu", "and",
	"or", "xor", "nor", "slt", "sltu", "j", "jal", "jalr",
	"mult", "multu", "div", "divu",
	"mfhi", "mthi", "mflo", "mtlo",
	"beq", "bne", "bgez", "bgtz", "blez", "bltz",
	"addi", "addiu", "slti", "sltiu", "andi", "ori", "xori",
	"lui", "lb", "lh", "lw", "lbu", "lhu", "sb", "sh", "sw",
	"syscall"
};

const char* IFormatName[] = { "NONE", "R_TYPE", "I_TYPE", "J_TYPE" };
const char* XTypeName[] =   { "NONE", "ALU", "SHIFT", "LOAD", "STORE", "BRANCH", "JUMP", "OTHER" };
