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
  return A[i];
}
