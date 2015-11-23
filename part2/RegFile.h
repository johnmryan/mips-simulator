/*
 * RegFile.h
 *
 *  Created on: Sep 14, 2015
 *      Author: jbb
 */

#ifndef NDSIM_REGFILE_H_
#define NDSIM_REGFILE_H_

#include "global.h"

class RegFile {
  friend class SimpleSim;
  uint32_t A[32];
public:
  uint32_t& operator[] (unsigned i);
  RegFile();
};

#endif /* NDSIM_REGFILE_H_ */
