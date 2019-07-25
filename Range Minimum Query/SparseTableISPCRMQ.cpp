#include "SparseTableISPCRMQ.h"
#include "sparse_ispc.h"
#include "assert.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
using namespace ispc;

SparseTableISPCRMQ::SparseTableISPCRMQ(const RMQEntry* elems, std::size_t numElems) {
  this->elems = elems;
  int32_t nelems = (int32_t)numElems;
  sparsesize = (int32_t)(log2(numElems));

  locs = (int32_t **)malloc(sparsesize * sizeof(int32_t *));
  assert(locs != NULL);

  for(int32_t i = 0; i < sparsesize; i++) {
    locs[i] = (int32_t *)malloc((nelems - (1 << (i + 1)) + 1) * sizeof(int32_t));
    assert(locs[i] != NULL);
 }  

 //do the first row 
 fillFirstRow((int32_t *)elems, locs[0], nelems-1);

 //have to go from smaller to larger intervals
 for(int32_t j = 1; j < sparsesize; j++){ 
  int32_t thing = (int32_t)(1 << (j));
  fillOtherRows((int32_t *)elems, locs[j-1], locs[j], (nelems - (1 << (j+1)) + 1),  thing);
 }
} 

SparseTableISPCRMQ::~SparseTableISPCRMQ() {
  for(int32_t i = 0; i < sparsesize; i++) {
    free(locs[i]);
  }
  free(locs);
}

std::size_t SparseTableISPCRMQ::rmq(std::size_t low, std::size_t high) const {
  int32_t range = high-low;
  if(range == 1 || range == 0) return low;

  union { double a; int b[2]; };
  a = range;
  int32_t k = (b[1] >> 20) - 1023;

  if(elems[locs[k-1][low]] < elems[locs[k-1][high - (1 << k)]]) return locs[k-1][low];
  return locs[k-1][high - (1 << k)];
}
