/*
 * RegFile.cpp
 *
 *  Created on: Sep 14, 2015
 *      Author: jbb
 */

#include "RegFile.h"

RegFile::RegFile() {

}

uint32_t& RegFile::operator [](unsigned i) {
  if (i == 0) {
    A[0] = 0;
    return A[0];
  }
  else
  return A[i];
}

