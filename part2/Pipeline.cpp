/*
 * Pipeline.cpp
 *
 *  Created on: Oct 25, 2015
 *      Author: jbb
 */

#include "Pipeline.h"

bool Pipeline::step() {
  bool pipeEmpty = true;
  for (int i = NUM_PS - 1;  i > 0;  i--) {
    pipeline[i] = pipeline[i-1];
    if (pipeline[i] != 0)
      pipeEmpty = false;
  }
  if (!instBuffer.empty()) {
    pipeline[PS_IF] = instBuffer.front();
    instBuffer.pop();
  }
  if (!pipeEmpty || !instBuffer.empty())
    return true;
  else
    return false;
}
