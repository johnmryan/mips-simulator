#include "global.h"
#include "Memory.h"
#include "RegFile.h"

Memory M;
RegFile reg;

int main()
{
  M.write32(0x12345678, 0x10010000);
  assert(M.read32(0x10010000) == 0x12345678);
  assert(M.read8(0x10010000) == 0x78);
  assert(M.read8(0x10010001) == 0x56);
  assert(M.read16(0x10010000) == 0x5678);

  M.write32(0x12345678, 0x00400000);
  assert(M.read32(0x00400000) == 0x12345678);

  M.write32(0x12345678, 0x7fff0000);
  assert(M.read32(0x7fff0000) == 0x12345678);

  reg[5] = 7;
  assert(reg[5] == 7);
  reg[0] = 7;
  assert(reg[0] == 0);

  return 0;
}