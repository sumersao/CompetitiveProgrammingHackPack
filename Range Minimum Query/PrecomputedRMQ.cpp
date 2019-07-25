#include "PrecomputedRMQ.h"
#include "assert.h"
#include <iostream>
#include <vector>

using namespace std;

PrecomputedRMQ::PrecomputedRMQ(const RMQEntry* elems, std::size_t numElems) {
  
  precomputedSums.resize(numElems);
  precomputedLocations.resize(numElems);

  for(size_t i = 0; i < numElems; i++) {
    precomputedSums[i] = vector<RMQEntry>(numElems);
    precomputedLocations[i] = vector<size_t>(numElems);
    precomputedSums[i][i] = elems[i];
    precomputedLocations[i][i] = i;
 }
  for(size_t i = 0; i < precomputedSums.size(); i++){
    for(size_t j = i+1; j < precomputedSums.size(); j++){
      precomputedSums[i][j] = precomputedSums[i][j-1];
      precomputedLocations[i][j] = precomputedLocations[i][j-1];
      if(precomputedSums[i][j-1] > elems[j]){
        precomputedSums[i][j] = elems[j];
        precomputedLocations[i][j] = j;
      }
    }
  }
}

PrecomputedRMQ::~PrecomputedRMQ() {
}

std::size_t PrecomputedRMQ::rmq(std::size_t low, std::size_t high) const {
  return precomputedLocations[low][high-1];
}
