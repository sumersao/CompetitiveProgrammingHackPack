#include "HybridRMQ.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <cmath>
#include <iostream>

using namespace std;

HybridRMQ::HybridRMQ(const RMQEntry* elems, std::size_t numElems) {

  this->elems = elems;

  if(numElems == 1)  blockSize = 1;
  else blockSize = floor(log2(numElems));

  size_t topSize = numElems / blockSize;
  
  topMinimums = (RMQEntry*) malloc(topSize * sizeof(RMQEntry));
  assert(topMinimums != NULL);

  for(size_t i = 0; i < topSize; i++) {
    RMQEntry min = elems[i * blockSize];
    for(size_t j = 0; j < blockSize; j++) {
      min = (elems[i * blockSize + j] < min ? elems[i * blockSize + j] : min);
    }
    topMinimums[i] = min;
  }

  topRMQ = new SparseTableRMQ(topMinimums, topSize);
}

HybridRMQ::~HybridRMQ() {
  free(topMinimums);
  delete(topRMQ);
}

std::size_t HybridRMQ::rmq(std::size_t low, std::size_t high) const {
  size_t lower_block_id = low / blockSize;
  size_t upper_block_id = (high-1) / blockSize;

  //no top-level search necessary, perform linear scan
  if(lower_block_id == upper_block_id || lower_block_id + 1 == upper_block_id) { 
    size_t min = low;
    for(size_t idx = low; idx < high; idx++) {
      min = (elems[idx] < elems[min] ? idx : min);
    }
    return min;
  }

  //else, need top-level search

  //part 1: search lower block
  size_t upper_bound_1 = (lower_block_id + 1) * blockSize;
  size_t ans = low;
  for(size_t i = low; i <= upper_bound_1; i++) {
    if(elems[i] < elems[ans]) ans = i;
  }

  //part 2: search upper block
  size_t lower_bound_2 = upper_block_id * blockSize;
  for(size_t i = lower_bound_2; i < high; i++) {
    if(elems[i] < elems[ans]) ans = i;
  }

  //part 3: search top-level structure
  size_t minBlockIndex = topRMQ->rmq(lower_block_id+1, upper_block_id);
  size_t lower_bound_3 = minBlockIndex * blockSize;
  size_t upper_bound_3 = lower_bound_3 + blockSize;
  for(size_t i = lower_bound_3; i < upper_bound_3; i++) {
    if(elems[i] < elems[ans]) ans = i;
  }

  return ans;
}