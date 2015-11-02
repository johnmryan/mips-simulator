/*
 * complete-main.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: jbb
 */

#include "global.h"
#include "Memory.h"
#include "RegFile.h"
#include "Instruction.h"
#include <getopt.h>

void instructionExecTest()
{
  M.write32(0x3210dcba, 0x10010000);
  pc = 0x00400000;
  Instruction(0x3408000c).exec();  TESTEQ(reg[8], 0xc);               // ori $8, $0, 0xc
  Instruction(0x3409000a).exec();  TESTEQ(reg[9], 0xa);               // ori $9, $0, 0xa
  Instruction(0x340a0001).exec();  TESTEQ(reg[10], 1);                // ori $10, $0, 1
  Instruction(0x340b0002).exec();  TESTEQ(reg[11], 2);                // ori $11, $0, 2
  Instruction(0x3c0cffff).exec();  TESTEQ(reg[12], 0xffff0000);       // lui $12, 0xffff
  Instruction(0x358cfffe).exec();  TESTEQ(reg[12], -2);               // ori $12, $12, 0xfffe
  Instruction(0x000c7c00).exec();  TESTEQ(reg[15], 0xfffe0000);       // sll $15, $12, 16
  Instruction(0x000c7c02).exec();  TESTEQ(reg[15], 0xffff);           // srl $15, $12, 16
  Instruction(0x01097824).exec();  TESTEQ(reg[15], 0x8);              // and $15, $8, $9
  Instruction(0x01097825).exec();  TESTEQ(reg[15], 0xe);              // or  $15, $8, $9
  Instruction(0x01097826).exec();  TESTEQ(reg[15], 0x6);              // xor $15, $8, $9
  Instruction(0x01097827).exec();  TESTEQ(reg[15], 0xfffffff1);       // nor $15, $8, $9
  Instruction(0x318fa0b0).exec();  TESTEQ(reg[15], 0xa0b0);           // andi $15, $12, 0xa0b0
  Instruction(0x354f1000).exec();  TESTEQ(reg[15], 0x1001);           // ori $15, $10, 0x1000
  Instruction(0x390ffffa).exec();  TESTEQ(reg[15], 0xfff6);           // xori $15, $8, 0xfffa
  Instruction(0x014b7820).exec();  TESTEQ(reg[15], 3);                // add $15, $10, $11
  Instruction(0x014c7820).exec();  TESTEQ(reg[15], 0xffffffff);       // add $15, $10, $12
  Instruction(0x016c7820).exec();  TESTEQ(reg[15], 0);                // add $15, $11, $12
  Instruction(0x014b7822).exec();  TESTEQ(reg[15], 0xffffffff);       // sub $15, $10, $11
  Instruction(0x014c7822).exec();  TESTEQ(reg[15], 3);                // sub $15, $10, $12
  Instruction(0x014b7821).exec();  TESTEQ(reg[15], 3);                // addu $15, $10, $11
  Instruction(0x014c7821).exec();  TESTEQ(reg[15], 0xffffffff);       // addu $15, $10, $12
  Instruction(0x016c7821).exec();  TESTEQ(reg[15], 0);                // addu $15, $11, $12
  Instruction(0x014b7823).exec();  TESTEQ(reg[15], 0xffffffff);       // subu $15, $10, $11
  Instruction(0x014c7823).exec();  TESTEQ(reg[15], 3);                // subu $15, $10, $12
  Instruction(0x214ffffe).exec();  TESTEQ(reg[15], -1);               // addi $15, $10, -2
  Instruction(0x254ffffe).exec();  TESTEQ(reg[15], -1);               // addiu $15, $10, -2
  Instruction(0x018b782a).exec();  TESTEQ(reg[15], 1);                // slt $15, $12, $11
  Instruction(0x018b782b).exec();  TESTEQ(reg[15], 0);                // sltu $15, $12, $11
  Instruction(0x298fffff).exec();  TESTEQ(reg[15], 1);                // slti $15, $12, -1
  Instruction(0x2d4fffff).exec();  TESTEQ(reg[15], 1);                // sltiu $15, $10, -1
  Instruction(0x3c081001).exec();  TESTEQ(reg[8] , 0x10010000);       // lui $8, 0x1001
  Instruction(0x8d0f0000).exec();  TESTEQ(reg[15], 0x3210dcba);       // lw $15, 0($8)
  Instruction(0x850f0000).exec();  TESTEQ(reg[15], 0xffffdcba);       // lh $15, 0($8)
  Instruction(0x950f0000).exec();  TESTEQ(reg[15], 0xdcba);           // lhu $15, 0($8)
  Instruction(0x810f0000).exec();  TESTEQ(reg[15], 0xffffffba);       // lb $15, 0($8)
  Instruction(0x910f0000).exec();  TESTEQ(reg[15], 0xba);             // lbu $15, 0($8)
  Instruction(0x3c09deca).exec();  TESTEQ(reg[9] , 0xdeca0000);       // lui $9, 0xdeca
  Instruction(0x3529fbad).exec();  TESTEQ(reg[9] , 0xdecafbad);       // ori $9, $9, 0xfbad
  Instruction(0xad090004).exec();  TESTEQ(M.read32(0x10010004), 0xdecafbad);  // sw $9, 4($8)
  Instruction(0x8d0f0004).exec();  TESTEQ(reg[15], 0xdecafbad);       // lw $15, 4($8)
  Instruction(0x34090012).exec();  TESTEQ(reg[9] , 0x12);             // ori $9, $0, 0x12
  Instruction(0xa1090007).exec();  TESTEQ(M.read8(0x10010007), 0x12); // sb $9, 7($8)
  Instruction(0x8d0f0004).exec();  TESTEQ(reg[15], 0x12cafbad);       // lw $15, 4($8)
  Instruction(0x34097654).exec();  TESTEQ(reg[9] , 0x7654);           // ori $9, $0, 0x7654
  Instruction(0xa5090004).exec();  TESTEQ(M.read16(0x10010004), 0x7654);  // sh $9, 4($8)
  Instruction(0x8d0f0004).exec();  TESTEQ(reg[15], 0x12ca7654);        // lw $15, 4($8)

  pc = 0x00400000;
  Instruction(0x10000003).exec();  TESTEQ(pc, 0x0040000c);    // beq $0, $0, 12
  Instruction(0x14000005).exec();  TESTEQ(pc, 0x00400010);    // bne $0, $0, 20
  Instruction(0x08100042).exec();  TESTEQ(pc, 0x00400108);    // j 0x00400108
  Instruction(0x0c100048).exec();  TESTEQ(pc, 0x00400120);    // jal 0x00400120
  Instruction(0x03e00008).exec();  TESTEQ(pc, 0x0040010c);    // jr $31
}

void runSimpleMachine()
{
  Instruction *execI;
  unsigned execPC;

  bool keepGoing = true;
  while (keepGoing) {
    execI = new Instruction(M.read32(pc));
    execPC = pc;
    keepGoing = execI->exec();
    if (!quietMode)
      printf("[%08x] %s %s\n", execPC, execI->str().c_str(), execI->resultStr().c_str());
    delete execI;
  }
}

void runBareMachine()
{
  Instruction *fetchI, *execI;
  unsigned fetchPC, execPC;

  execI = new Instruction(M.read32(pc));
  execPC = pc;
  pc += 4;
  bool keepGoing = true;
  while (keepGoing) {
    fetchI = new Instruction(M.read32(pc));
    fetchPC = pc;
    keepGoing = execI->exec();
    if (!quietMode)
      printf("[%08x] %s %s\n", execPC, execI->str().c_str(), execI->resultStr().c_str());
    delete execI;
    execI = fetchI;
    execPC = fetchPC;
  }
}

void outputStats()
{
  ofstream statFile;
  statFile.open("stats.csv");
  assert(statFile && "unable to open statFile");
  statFile << "instructionCount," << instructionCount << endl;
  for (int i = 0;  i < NUM_XTYPE;  i++) {
    statFile << XTypeName[i] << "," << xtypeCounts[i] << endl;
  }
  for (int i = 0;  i < NUM_ITOKEN;  i++) {
    statFile << ITokenName[i] << "," << itokenCounts[i] << endl;
  }
}

void printHelp()
{
  printf("Usage: mipsim [<mipsim-options>] <qtSpim-log-file>\n");
  printf("Options:\n");
  printf("  --help             -h  help\n");
  printf("  --test             -t  test instructions\n");
  printf("  --simple           -s  simple machine mode         (default false)\n");
  printf("  --bare             -b  bare machine model          (default true)\n");
  printf("  --quiet            -q  quiet mode\n");
  exit(0);
}

int main(int argc, char **argv)
{
  int opt;
  static struct option longopts[] = {
      {"help",            no_argument,        0,   'h'},
      {"test",            no_argument,        0,   't'},
      {"simple",          no_argument,        0,   's'},
      {"bare",            no_argument,        0,   'b'},
      {"quiet",           no_argument,        0,   'q'},
      {0, 0, 0, 0}
  };
  int longindex;

  bareMachineMode = true;
  quietMode = false;

  while ((opt = getopt_long(argc, argv, "+htsbq", longopts, &longindex)) != -1) {
    switch (opt) {
    case 'h' :
      printHelp();
      return 0;
    case 't' :
      bareMachineMode = false;
      instructionExecTest();
      return 0;
    case 's' :
      bareMachineMode = false;
      break;
    case 'b' :
      bareMachineMode = true;
      break;
    case 'q' :
      quietMode = true;
      break;
    default :
      printf("usage error\n");
      exit(0);
    }
  }

  assert(argc > 1 && "need to specify input file");
  char* infile = argv[optind];
  M.readSpimLogFile(infile);
  pc = 0x00400000;
  reg[28] = 0x10008000; // $gp
  reg[29] = 0x7ffff240; // $sp

  if (bareMachineMode)
    runBareMachine();
  else
    runSimpleMachine();
  outputStats();
  return 0;
}

