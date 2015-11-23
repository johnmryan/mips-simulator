/*
 * Memory.h
 *
 *  Created on: Sep 14, 2015
 *      Author: jbb
 */

#ifndef NDSIM_MEMORY_H_
#define NDSIM_MEMORY_H_

#include "Cache.h"
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
  uint8_t*  heapMemory;
  unsigned  heapSize;
  unsigned  heapBase;
  unsigned  heapBound;
  uint8_t*  stackMemory;
  unsigned  stackSize;
  unsigned  stackBound;
  unsigned  stackBase;
  uint32_t  mainAddr;
  Cache*    iCache;
  Cache*    dCache;
public:
  Memory(unsigned tSize = (1<<20),
         unsigned dSize = (1<<20),
         unsigned hSize = (1<<20),
         unsigned sSize = (1<<20));

  void      loadText(void *source, unsigned numBytes);
  void      loadData(void *source, unsigned numBytes);
  void      readSpimLogFile(char *filename);
  void      readElfFile(char *filename);
  uint8_t   read8(unsigned addr);
  uint16_t  read16(unsigned addr);
  uint32_t  read32(unsigned addr);
  void      write8(uint8_t data, unsigned addr);
  void      write16(uint16_t data, unsigned addr);
  void      write32(uint32_t data, unsigned addr);
  unsigned  alloc(unsigned n);
  uint32_t  getMainAddr()  { return mainAddr; }
  uint8_t*  getMemoryPtr(unsigned addr);

  void      initCache(unsigned iLogDepth,
                      unsigned iLogBlksize,
                      unsigned dLogDepth,
                      unsigned dLogBlksize);

  unsigned  getIcacheAccesses() { return iCache->getAccesses(); }
  unsigned  getIcacheHits()     { return iCache->getHits(); }
  unsigned  getDcacheAccesses() { return dCache->getAccesses(); }
  unsigned  getDcacheHits()     { return dCache->getHits(); }

  void      printStats();
  virtual   ~Memory();
};

#endif /* NDSIM_MEMORY_H_ */
