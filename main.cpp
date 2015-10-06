/*
 * main.cpp
 *
 *  Created on: Sep 14, 2015
 *      Author: jbb
 */

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "Instruction.h"

unsigned testProgram[] = {
		0x8fa40000,
		0x27a50004,
		0x24a60004,
		0x00041080,
		0x00c23021,
		0x0c100009,
		0x00000000,
		0x3402000a,
		0x0000000c,
		0x3408000c,
		0x3409000a,
		0x340a0001,
		0x340b0002,
		0x3c0cffff,
		0x358cfffe,
		0x01097824,
		0x01097825,
		0x01097826,
		0x318fa0b0,
		0x354f1000,
		0x390ffffa,
		0x014b7820,
		0x014c7820,
		0x016c7820,
		0x014b7822,
		0x014c7822,
		0x014b7821,
		0x014c7821,
		0x016c7821,
		0x014b7823,
		0x014c7823,
		0x214ffffe,
		0x254ffffe,
		0x018b782a,
		0x018b782b,
		0x298fffff,
		0x2d4fffff,
		0x3c081001,
		0x8d0f0000,
		0x850f0000,
		0x950f0000,
		0x810f0000,
		0x910f0000,
		0x3c09deca,
		0x3529fbad,
		0xad090004,
		0x8d0f0004,
		0x34090012,
		0xa1090007,
		0x8d0f0004,
		0x34097654,
		0xa5090004,
		0x8d0f0004,
		0x10000002,
		0x340f0001,
		0x340f0002,
		0x340f0003,
		0x14000004,
		0x340f0004,
		0x340f0005,
		0x0810003f,
		0x340f0006,
		0x340f0007,
		0x340f0008,
		0x34020000,
		0x0c100045,
		0x340f0009,
		0x3402000a,
		0x0000000c,
		0x34020001,
		0x03e00008,
		0x340f000a
};

void testBitRange()
{
	Instruction inst(0x12345678);
	assert(inst.bitRange(31, 28) == 0x1);
	assert(inst.bitRange(27, 4)  == 0x234567);
	assert(inst.bitRange(3, 0)   == 0x8);
}

void testSignExtend()
{
	Instruction inst(0);
	assert(inst.signExtend8(0x4f) == 0x4f);
	assert(inst.signExtend8(0x8f) == 0xffffff8f);
	assert(inst.signExtend16(0x4fff) == 0x4fff);
	assert(inst.signExtend16(0x8fff) == 0xffff8fff);
}

void testToken()
{
	assert(Instruction(0x00041080).getToken() == SLL);
	assert(Instruction(0x00041082).getToken() == SRL);
	assert(Instruction(0x03e00008).getToken() == JR);
	assert(Instruction(0x0000000c).getToken() == SYSCALL);
	assert(Instruction(0x014b7820).getToken() == ADD);
	assert(Instruction(0x014b7821).getToken() == ADDU);
	assert(Instruction(0x014b7822).getToken() == SUB);
	assert(Instruction(0x014c7823).getToken() == SUBU);
	assert(Instruction(0x01097824).getToken() == AND);
	assert(Instruction(0x01097825).getToken() == OR);
	assert(Instruction(0x01097826).getToken() == XOR);
	assert(Instruction(0x01097827).getToken() == NOR);
	assert(Instruction(0x018b782a).getToken() == SLT);
	assert(Instruction(0x018b782b).getToken() == SLTU);
	assert(Instruction(0x0810003f).getToken() == J);
	assert(Instruction(0x0c100045).getToken() == JAL);
	assert(Instruction(0x10000002).getToken() == BEQ);
	assert(Instruction(0x14000004).getToken() == BNE);
	assert(Instruction(0x214ffffe).getToken() == ADDI);
	assert(Instruction(0x254ffffe).getToken() == ADDIU);
	assert(Instruction(0x298fffff).getToken() == SLTI);
	assert(Instruction(0x2d4fffff).getToken() == SLTIU);
	assert(Instruction(0x318fa0b0).getToken() == ANDI);
	assert(Instruction(0x354f1000).getToken() == ORI);
	assert(Instruction(0x390ffffa).getToken() == XORI);
	assert(Instruction(0x3c0cffff).getToken() == LUI);
	assert(Instruction(0x810f0000).getToken() == LB);
	assert(Instruction(0x850f0000).getToken() == LH);
	assert(Instruction(0x8d0f0000).getToken() == LW);
	assert(Instruction(0x910f0000).getToken() == LBU);
	assert(Instruction(0x950f0000).getToken() == LHU);
	assert(Instruction(0xa1090007).getToken() == SB);
	assert(Instruction(0xa5090004).getToken() == SH);
	assert(Instruction(0xad090004).getToken() == SW);
}

void testInstructionPrint()
{
	for (int i = 0;  i < 72;  i++) {
		Instruction inst(testProgram[i]);
		inst.print();
		cout << inst.str() << endl << endl;
	}
}

int main(int argc, char** argv)
{
	testBitRange();
	testSignExtend();
	testToken();
//  testInstructionPrint();
	return 0;
}


