#ifndef SecondChoiceHashTable_Included
#define SecondChoiceHashTable_Included

#include "Hashes.h"
#include <vector>
#include <list>

class SecondChoiceHashTable {
public:
  /**
   * Constructs a new second-choice table with the specified number of buckets,
   * using hash functions drawn from the indicated family of hash functions.
   * Because our testing harness attempts to exercise a number of different
   * load factors, you should not change the number of buckets once the hash
   * table has initially be created.
   *
   * You can choose a hash function out of the family of hash functions by
   * declaring a variable of type HashFunction and assigning it the value
   * family->get(). For example:
   *
   *    HashFunction h;
   *    h = family->get();
   */
  SecondChoiceHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family);
  
  /**
   * Cleans up all memory allocated by this hash table.
   */
  ~SecondChoiceHashTable();
  
  /**
   * Inserts the specified element into this hash table. If the element already
   * exists, this operation is a no-op.
   */
  void insert(int key);
  
  /**
   * Returns whether the specified key is contained in this hash tasble.
   */
  bool contains(int key) const;
  
  /**
   * Removes the specified element from this hash table. If the element is not
   * present in the hash table, this operation is a no-op.
   */
  void remove(int key);
  
private:
  HashFunction h1;
  HashFunction h2;
  std::vector<std::list<int> > table;
  
  /* Fun with C++: these next two lines disable implicitly-generated copy
   * functions that would otherwise cause weird errors if you tried to
   * implicitly copy an object of this type. You don't need to touch these
   * lines.
   */
  SecondChoiceHashTable(SecondChoiceHashTable const &) = delete;
  void operator=(SecondChoiceHashTable const &) = delete;
};
 
#endif
