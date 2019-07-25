#include "ChainedHashTable.h"
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//Creates a vector of lists, (array of linkedlist) and the hashfunction
ChainedHashTable::ChainedHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
	table.resize(numBuckets);
	h = family->get();
}

ChainedHashTable::~ChainedHashTable() {
	
}

void ChainedHashTable::insert(int data) {
	int m = table.size();
	int hval = h(data) % m;
	if(!contains(data)) {
		table[hval].push_back(data);
	}
}

bool ChainedHashTable::contains(int data) const {
	int m = table.size();
	int hval = h(data) % m;
	auto contains = find(table[hval].begin(), table[hval].end(), data);
	//the element is not in the list!
	if(contains == table[hval].end()) {
		return false;
	}
	return true;
}

void ChainedHashTable::remove(int data) {
	int m = table.size();
	int hval = h(data) % m;
	table[hval].remove(data);
}
