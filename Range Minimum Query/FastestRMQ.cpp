#include "FastestRMQ.h"
#include "sparse_ispc.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <cmath>
#include <iostream>
#include "Timer.h"

using namespace std;

FastestRMQ::FastestRMQ(const RMQEntry* elems, std::size_t numElems) {
  this->elems = elems;

  if(numElems < 64) blockSize = 1;
  else blockSize = 64;

  int32_t nelems = (int32_t) numElems;
  int32_t topSize = nelems / blockSize;
  
  topMinimums = (RMQEntry*) malloc(topSize * sizeof(RMQEntry));
  assert(topMinimums != NULL);

  topMinimumsInd = (int32_t*) malloc(topSize * sizeof(int32_t));
  assert(topMinimumsInd != NULL);
  
  ispc::findBlockMinimums((int32_t*)elems, (int32_t *) topMinimums, topMinimumsInd, topSize, blockSize);

  topRMQ = new SparseTableISPCRMQ(topMinimums, topSize);
}

FastestRMQ::~FastestRMQ() {
  free(topMinimums);
  delete(topRMQ);
}

std::size_t FastestRMQ::rmq(std::size_t low, std::size_t high) const {
  int32_t lower_block_id = (int32_t) low / blockSize;
  int32_t upper_block_id = (int32_t ) (high-1) / blockSize;

  //no top-level search necessary, perform linear scan
  if(lower_block_id == upper_block_id || lower_block_id + 1 == upper_block_id) { 
    int32_t min = low;
    for(int32_t idx = low; idx < (int32_t)high; idx++) {
      min = (elems[idx] < elems[min] ? idx : min);
    }
    return min;
  }

  //else, need top-level search

  //part 1: search lower block
  int32_t upper_bound_1 = (lower_block_id + 1) * blockSize;
  int32_t ans = low;
  for(int32_t i = low; i <= upper_bound_1; i++) {
    if(elems[i] < elems[ans]) ans = i;
  }

  //part 2: search upper block
  int32_t lower_bound_2 = upper_block_id * blockSize;
  for(int32_t i = lower_bound_2; i < (int32_t)high; i++) {
    if(elems[i] < elems[ans]) ans = i;
  }

  //part 3: search top-level structure
  int32_t minBlockIndex = topRMQ->rmq(lower_block_id+1, upper_block_id);
  if(elems[topMinimumsInd[minBlockIndex]] < elems[ans]) ans = topMinimumsInd[minBlockIndex];
  
  return (size_t)ans;
}