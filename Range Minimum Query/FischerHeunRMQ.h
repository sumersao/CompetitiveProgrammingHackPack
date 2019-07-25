/******************************************************************************
 * File: FischerHeunRMQ.h
 *
 * A range minimum query data structure implemented using the Fischer-Heun
 * structure described in class.
 */

#ifndef FischerHeunRMQ_Included
#define FischerHeunRMQ_Included

#include "RMQEntry.h"
#include "SparseTableRMQ.h"
#include "PrecomputedRMQ.h"

#include <vector>
#include <string>

class FischerHeunRMQ {
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
  FischerHeunRMQ(const RMQEntry* elems, std::size_t numElems);
  
  /* Frees all memory associated with this RMQ structure. */
  ~FischerHeunRMQ();

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
  std::size_t numElems;
  std::size_t blockSize;

  RMQEntry* topMinimums;
  SparseTableRMQ* topRMQ;

  std::size_t numBlocksTotal;
  std::vector<PrecomputedRMQ*> bottomRMQs;
  std::vector<bool> bottomRMQsBooleans;

  std::vector<std::size_t> blockToTree;
  PrecomputedRMQ* lastBlockRMQ;

  std::size_t getAbsoluteMinimumIndex(std::size_t block_id, std::size_t relativeLow, std::size_t relativeHigh) const;
  //std::string compute_cartesian(RMQEntry* elems, std::size_t numElems);
  /* Copying is disabled. */
  FischerHeunRMQ(const FischerHeunRMQ &) = delete;
  void operator= (FischerHeunRMQ) = delete;
};


#endif
