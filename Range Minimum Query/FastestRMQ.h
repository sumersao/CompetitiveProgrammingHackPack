
/******************************************************************************
 * File: FastestRMQ.h
 *
 * This file is relevant for Problem Five on PS1, where you're asked to
 * implement a range minimum query data structure that has the fastest runtime
 * you can achieve.
 *
 * We're leaving it completely up to you to decide how you want to implement
 * this type. Be creative! See what you come up with!

Our final solution uses the <O(n), O(logn)> hybrid approach used in part 3 of 
this problem. The query times were about as fast as we could get, but we had
several ideas on how to speed up the preprocessing time. The preprocessing 
composes of 2 steps. First, computing the block minima values. Then building
a sparse table from these values. Let's first explain how we improved upon
our sparse table.

 We think there are 4 novel parts of our solution, that overall gave us a speedup
 of 12x on preprocessing and 2x on querying.

 1) For the dynamic programming array accesses, we rotated our sparse table so that the
    (log n) dimension was the rows rather than the columns. We then also traversed our array
    rows first.We thought this would improve locality of data accesses, and we were right, 
    because we got a speedup of 6x.

 2) We then added the speedup of computing our table using SIMD programming. This allows us 
    to efficiently use the hardware of one core to do vectorized operations across 8 
    different array values at the same time. Our solution uses the ISPC compiler and files 
    sparse.ispc and sparse_ispc.h. We observe a speed-up of 2x using this approach. The reason 
    we weren't able to get closer to the theoretical maximum of 8x is probably due to the 
    slowness of the gather operation in SIMD, which are vectorized array accesses in different 
    locations so no locality.
  3) We also realized that there was no point in creating the first row of our sparse table. 
     The first row would always be filled with 0,1...,n-1, so we could just use this knowledge
     in computions and save a constant factor of linear work in filling this longest array 
     (note we only allocated however much space for each row of the sparse table per row)
  4) We also decided that precomputing powers of 2 for O(1) queries was also unecessary and
     also added an extra amount of linear work, so we swapped this and used bit manipulations
     to lower the query time.

  For our hybrid approach we didn't change any of the query aspect, however we did once again
  use SIMD programming on the preprocessing to find the minima of blocks. We were able to do 
  so, by computing 8 blocks in parallel, which also served great locality. This gave us another
  2x speedup.

  Finally, we got rid of all vectors, and went low level to use pointer arithmetic
  to help moving, accessing, and changing memory.

  We also realized that having our block size be exactly log(n) size might not be optimal. We 
  realized cache lines are 64 bytes, so tried allocating block sizes in line with this knoweldge.
  Testing on a few cases, such as 4, 16, 32, 64, 128, and 256. We realized as we went higher in 
  block size, we could get our preprocessing down to as low as 240k ns, but query times jumped to
  around 500 ns. We ultimately decided that this half in preprocessing time wasn't worth the 
  doubling of query times especially since query times become so much more important with a 
  large number of queries. Thus we chose block size to be 64, and finished with:
  preprocess: 425k ns
  Query: 240 ns

 */

#ifndef FastestRMQ_Included
#define FastestRMQ_Included

#include "RMQEntry.h"
#include "SparseTableISPCRMQ.h"

class FastestRMQ {
public:
  /* Constructs an RMQ structure from the specified array of elements. That
   * array may be empty.
   *
   * You aren't responsible for managing the memory of the elements array
   * provided to you here. You can assume that the array will remain valid
   * throughout the lifetime of this data structure. You should not modify the
   * contents of this array, as it might be shared across multiple RMQ
   * structures, nor should you delete it.
   */
  FastestRMQ(const RMQEntry* elems, std::size_t numElems);
  
  /* Frees all memory associated with this RMQ structure. */
  ~FastestRMQ();

  /* Performs an RMQ over the specified range. You can assume that low < high
   * and that the bounds are in range and don't need to do any error-handling
   * if this is not the case.
   *
   * The interval here is half-open. That is, the range in question here is
   * [low, high). Note that this follows the C++ convention, but is slightly
   * different from how we presented things in lecture.
   *
   * This function should return the *index* at which the minimum value occurs,
   * rather than the minimum value itself.
   */
  std::size_t rmq(std::size_t low, std::size_t high) const;

private:
  const RMQEntry* elems;

  std::int32_t blockSize;
  RMQEntry* topMinimums;
  std::int32_t* topMinimumsInd;

  SparseTableISPCRMQ* topRMQ;

  /* Copying is disabled. */
  FastestRMQ(const FastestRMQ &) = delete;
  void operator= (FastestRMQ) = delete;
};


#endif
