/*
 * Memory.cpp
 *
 *  Created on: Sep 14, 2015
 *      Author: jbb
 */

#include "Memory.h"

Memory::Memory(unsigned tSize, unsigned dSize, unsigned sSize)
: textSize    (tSize),
  textBase    (0x400000),
  textBound   (textBase + tSize - 1),
  dataSize    (dSize),
  dataBase    (0x10000000),
  dataBound   (dataBase + dSize - 1),
  stackSize   (sSize),
  stackBound  (0x7fffffff),
  stackBase   (stackBound - sSize + 1),
  textMemory  (new uint8_t [tSize]),
  dataMemory  (new uint8_t [dSize]),
  stackMemory (new uint8_t [sSize])
{ }

Memory::Memory(unsigned tBase, unsigned tSize,
    unsigned dBase, unsigned dSize,
    unsigned sBound, unsigned sSize)
: textSize    (tSize),
  textBase    (tBase),
  textBound   (tBase + tSize - 1),
  dataSize    (dSize),
  dataBase    (dBase),
  dataBound   (dBase + dSize - 1),
  stackSize   (sSize),
  stackBound  (sBound),
  stackBase   (sBound - sSize + 1),
  textMemory  (new uint8_t [tSize]),
  dataMemory  (new uint8_t [dSize]),
  stackMemory (new uint8_t [sSize])
{ }

Memory::~Memory() {
  // TODO Auto-generated destructor stub
}

void Memory::loadText(void *source, unsigned numBytes) {
  assert(numBytes <= textSize && "text to load exceeds memory size");
  memcpy(textMemory, source, numBytes);
}

void Memory::loadData(void *source, unsigned numBytes) {
  assert(numBytes <= dataSize && "data to load exceeds memory size");
  memcpy(dataMemory, source, numBytes);
}

void Memory::readSpimLogFile(char *filename) {
  ifstream logfile;
  logfile.open(filename);
  assert(logfile && "unable to open logfile");
  string line;
  size_t found;
  unsigned a, d0, d1, d2, d3;

  while (!getline(logfile, line).eof()) {
    found = line.find("User Text Segment");
    if (found != string::npos)
      break;
  }
  assert(!logfile.eof() && "couldn't find User Text Segment");
  do {
    getline(logfile, line);
    sscanf(line.c_str(), "[%x] %x", &a, &d0);
//    printf("%08x  %08x\n", a, d0);
    write32(d0, a);
  } while(line[0] == '[');

  while (!getline(logfile, line).eof()) {
    found = line.find("User data segment");
    if (found != string::npos)
      break;
  }
  assert(!logfile.eof() && "couldn't find User data segment");
  do {
    getline(logfile, line);
    if (line[10] != '.') {
      sscanf(line.c_str(), "[%x] %x %x %x %x", &a, &d0, &d1, &d2, &d3);
//      printf("%08x  %08x  %08x  %08x  %08x\n", a, d0, d1, d2, d3);
      write32(d0, a);
      write32(d1, a+4);
      write32(d2, a+8);
      write32(d3, a+12);
    }
  } while(line[0] == '[');

}

uint8_t Memory::read8(unsigned addr) {
  uint8_t* ptr = getMemoryPtr(addr);
  return *ptr;
}

uint16_t Memory::read16(unsigned addr) {
  uint16_t* ptr = (uint16_t*) getMemoryPtr(addr);
  return *ptr;
}

uint32_t Memory::read32(unsigned addr) {
  uint32_t* ptr = (uint32_t*) getMemoryPtr(addr);
  return *ptr;
}

void Memory::write8(uint8_t data, unsigned addr) {
  uint8_t* ptr = getMemoryPtr(addr);
  *ptr = data;
}

void Memory::write16(uint16_t data, unsigned addr) {
  uint16_t* ptr = (uint16_t*) getMemoryPtr(addr);
  *ptr = data;
}

void Memory::write32(uint32_t data, unsigned addr) {
  uint32_t* ptr = (uint32_t*) getMemoryPtr(addr);
  *ptr = data;
}

uint8_t* Memory::getMemoryPtr(unsigned addr) {

  assert(false && "memory access out of range");
}
