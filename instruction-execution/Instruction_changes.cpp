/*
 * Instruction_changes.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: jbb
 */

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


