/*
 * Memory.h
 *
 *  Created on: Sep 14, 2015
 *      Author: jbb
 */

#ifndef NDSIM_MEMORY_H_
#define NDSIM_MEMORY_H_

#include "global.h"

class Memory {
  uint8_t*  textMemory;
  unsigned  textSize;
  unsigned  textBase;
  unsigned  textBound;
  uint8_t*  dataMemory;
  unsigned  dataSize;
  unsigned  dataBase;
  unsigned  dataBound;
  uint8_t*  stackMemory;
  unsigned  stackSize;
  unsigned  stackBound;
  unsigned  stackBase;
public:
  Memory(unsigned tSize = (1<<20), unsigned dSize = (1<<20), unsigned sSize = (1<<20));
  Memory(unsigned tBase, unsigned tSize,
      unsigned dBase, unsigned dSize,
      unsigned sBound, unsigned sSize);
  virtual   ~Memory();
  void      loadText(void *source, unsigned numBytes);
  void      loadData(void *source, unsigned numBytes);
  void      readSpimLogFile(char *filename);
  uint8_t   read8(unsigned addr);
  uint16_t  read16(unsigned addr);
  uint32_t  read32(unsigned addr);
  void      write8(uint8_t data, unsigned addr);
  void      write16(uint16_t data, unsigned addr);
  void      write32(uint32_t data, unsigned addr);
private:
  uint8_t*  getMemoryPtr(unsigned addr);
};

#endif /* NDSIM_MEMORY_H_ */