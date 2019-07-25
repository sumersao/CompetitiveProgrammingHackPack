#include "FischerHeunRMQ.h"
#include <string>
#include <stack>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <cmath>
#include <iostream>

using namespace std;

size_t compute_cartesian(const RMQEntry* elems, size_t numElems) {


  stack<RMQEntry> stk;
  size_t res = 0;
  size_t sub = 0;
  for(size_t i = 0; i < numElems; i++){
    while(!stk.empty() && stk.top() > elems[i]) {
      sub++;
      stk.pop();
    }
    stk.push(elems[i]);
    res += 1L << (2*numElems - sub - 1);
    sub++;
  }
  while(!stk.empty()) {
    stk.pop();
  }
  return res;
}

FischerHeunRMQ::FischerHeunRMQ(const RMQEntry* elems, std::size_t numElems) {

  bottomRMQs.resize(numElems);
  bottomRMQsBooleans.resize(numElems);
  fill(bottomRMQsBooleans.begin(), bottomRMQsBooleans.end(), false);

  this->elems = elems;
  this->numElems = numElems;

  if(numElems <= 15)  blockSize = 1;
  else blockSize = floor(0.25 * log2(numElems));

  //Top level work
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

  //Bottom level work
  numBlocksTotal = ceil((float)numElems / blockSize);
  blockToTree.resize(numBlocksTotal);
  for(size_t i = 0; i < numBlocksTotal; i++) {
    
    //last block is a special case
    if(i == numBlocksTotal - 1) { 
      size_t numElemsLastBlock = (numElems % blockSize == 0 ? blockSize : numElems % blockSize);
      lastBlockRMQ = new PrecomputedRMQ(elems + i * blockSize, numElemsLastBlock);
    } 

    //all other blocks
    else {
      size_t cartesian_idx = compute_cartesian(elems + i * blockSize, blockSize);
      blockToTree[i] = cartesian_idx;
      if(bottomRMQsBooleans[cartesian_idx] == false) { //RMQ not been computed yet for this block
        bottomRMQsBooleans[cartesian_idx] = true;
        bottomRMQs[cartesian_idx] = new PrecomputedRMQ(elems + i * blockSize, blockSize);
      }
    }
  }
}


FischerHeunRMQ::~FischerHeunRMQ() {
  free(topMinimums);
  delete(topRMQ);
  for(size_t i = 0; i < bottomRMQsBooleans.size(); i++) {
    if(bottomRMQsBooleans[i]) {
      delete(bottomRMQs[i]);
    }
  }
  delete(lastBlockRMQ);
}

//Obeys half-interval convention of searching [relativeLow, relativeHigh) in block block_id 
std::size_t FischerHeunRMQ::getAbsoluteMinimumIndex(size_t block_id, size_t relativeLow, size_t relativeHigh) const {
  if(block_id == numBlocksTotal - 1) {
    size_t queryIndex = lastBlockRMQ->rmq(relativeLow, relativeHigh);
    return block_id * blockSize + queryIndex;
  }
  else {
    size_t cartesianIndex = blockToTree[block_id];
    assert(bottomRMQsBooleans[cartesianIndex]);
    size_t queryIndex = bottomRMQs[cartesianIndex]->rmq(relativeLow, relativeHigh);
    return block_id * blockSize + queryIndex;    
  }
}

std::size_t FischerHeunRMQ::rmq(std::size_t low, std::size_t high) const {

  size_t lower_block_id = low / blockSize;
  size_t upper_block_id = (high-1) / blockSize;

  assert(lower_block_id <= upper_block_id);


  //Case 1: One block traversal
  if(lower_block_id == upper_block_id) { //Only require one block
    return getAbsoluteMinimumIndex(lower_block_id, low % blockSize, (high-1) % blockSize + 1);
  }

  size_t min_idx_lower = getAbsoluteMinimumIndex(lower_block_id, low % blockSize, blockSize);
  size_t min_idx_upper = getAbsoluteMinimumIndex(upper_block_id, 0, (high-1) % blockSize + 1);

  //Case 2: Two block traversal - no top-level traversal needed
  if(lower_block_id + 1 == upper_block_id) {
    if(elems[min_idx_lower] < elems[min_idx_upper])
      return min_idx_lower;
    else
      return min_idx_upper;
  }

  //Case 3: Three or more block traversal - need top-level traversal
  size_t minBlockIndex = topRMQ->rmq(lower_block_id+1, upper_block_id);
  size_t min_idx_mid = getAbsoluteMinimumIndex(minBlockIndex, 0, blockSize);


  if(elems[min_idx_lower] <= elems[min_idx_mid] && elems[min_idx_lower] <= elems[min_idx_upper])
    return min_idx_lower;

  if(elems[min_idx_mid] <= elems[min_idx_lower] && elems[min_idx_mid] <= elems[min_idx_upper])
    return min_idx_mid;

  else
    return min_idx_upper;
}
