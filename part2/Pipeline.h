/*
 * Pipeline.h
 *
 *  Created on: Oct 25, 2015
 *      Author: jbb
 */

#ifndef NDSIM_COMPLETE_PIPELINE_H_
#define NDSIM_COMPLETE_PIPELINE_H_

#include "global.h"
#include "Instruction.h"
#include <queue>

enum PipeStages { PS_IF, PS_ID, PS_EX, PS_MEM, PS_WB, NUM_PS };

class Pipeline {
  Pipeline() { }
  queue<Instruction*> instBuffer;
  Instruction* pipeline[NUM_PS];
public:
  void insert(Instruction* inst)    { instBuffer.push(inst); }
  bool step();
};

#endif /* NDSIM_COMPLETE_PIPELINE_H_ */
