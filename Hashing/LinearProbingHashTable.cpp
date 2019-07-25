#include "LinearProbingHashTable.h"
#include <vector>
#include <iostream>

using namespace std;


LinearProbingHashTable::LinearProbingHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
	table.resize(numBuckets);
	for(size_t i = 0; i < numBuckets; i++) {
		table[i] = -1;
	}
	h = family->get();
}

LinearProbingHashTable::~LinearProbingHashTable() {
	
}

void LinearProbingHashTable::insert(int data) {
	int m = table.size();
	int hval = h(data) % m;
	for(int i = 0; i < m; i++) {
		int cur = (hval + i) % m;
		if(table[cur] == -1) {
			//insert here!
			table[cur] = data;
			return;
		}
		if(table[cur] == data) {
			return;
		}
	}
}

bool LinearProbingHashTable::contains(int data) const {
	int m = table.size();
	int hval = h(data) % m;
	for(int i = 0; i < m; i++) {
		int cur = (hval + i) % m;
		if(table[cur] == -1) {
			return false;
		}
		if(table[cur] == data) {
			return true;
		}
	}
	return false;
}

void LinearProbingHashTable::remove(int data) {
	int m = table.size();
	int hval = h(data) % m;
	for(int i = 0; i < m; i++) {
		int cur = (hval + i) % m;
		if(table[cur] == data) {
			table[cur] = -2;
			return;
		}
	}
}
