#include "SecondChoiceHashTable.h"
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

SecondChoiceHashTable::SecondChoiceHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
	table.resize(numBuckets);
	h1 = family->get();
	h2 = family->get();
}

SecondChoiceHashTable::~SecondChoiceHashTable() {
	
}

void SecondChoiceHashTable::insert(int data) {
	int m = table.size();
	int hval1 = h1(data) % m;
	int hval2 = h2(data) % m;
	if(!contains(data)) {
		//add it to the shorter one
		if(table[hval1].size() < table[hval2].size()) {
			table[hval1].push_back(data);
		}
		else {
			table[hval2].push_back(data);
		}
	}
}

bool SecondChoiceHashTable::contains(int data) const {
	int m = table.size();
	int hval1 = h1(data) % m;
	int hval2 = h2(data) % m;
	auto contains1 = find(table[hval1].begin(), table[hval1].end(), data);
	auto contains2 = find(table[hval2].begin(), table[hval2].end(), data);
	//the element is not in the list!
	if(contains1 == table[hval1].end() && contains2 == table[hval2].end()) {
		return false;
	}
	return true;
}

void SecondChoiceHashTable::remove(int data) {
	int m = table.size();
	int hval1 = h1(data) % m;
	int hval2 = h2(data) % m;
	table[hval1].remove(data);
	table[hval2].remove(data);
}
