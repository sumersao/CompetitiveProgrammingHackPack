#include "SparseTableRMQ.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

SparseTableRMQ::SparseTableRMQ(const RMQEntry* elems, std::size_t numElems) {
  this->elems = elems;
  locs.resize(numElems);
  //pow2[i] = the largest power of 2 <= i
  pow2.resize(numElems + 1);

  size_t sparsesize = (size_t)(log2(numElems)) + 1;
  pow2[1] = 0;
  for(size_t i = 0; i < numElems; i++) {
    locs[i] = vector<size_t>(sparsesize);
    locs[i][0] = i;
 }

 for(size_t i = 1; i < pow2.size(); i++){
    if(i == (1U<<(pow2[i-1]+1))) {
           pow2[i] = pow2[i-1]+1;
      }
    else {
       pow2[i] = pow2[i-1];
    }
 }

 //have to go from smaller to larger intervals
 for(size_t j = 1; j < sparsesize; j++){
  for(size_t i = 0; (i + (1<<j) - 1) < numElems; i++){
    if(elems[locs[i][j-1]] < elems[locs[i + (1<<(j-1))][j-1]]){
      locs[i][j] = locs[i][j-1];
    }
    else{
      locs[i][j] = locs[i + (1<<(j-1))][j-1];
    }
  }
 }

}

SparseTableRMQ::~SparseTableRMQ() {
  /* TODO: Delete this comment and implement this function. */
}

std::size_t SparseTableRMQ::rmq(std::size_t low, std::size_t high) const {
  size_t range = high-low;
  size_t k = pow2[range-1];
  if(elems[locs[low][k]] < elems[locs[high - (1 << k)][k]]) return locs[low][k];
  return locs[high - (1 << k)][k];
}