#include "RobinHoodHashTable.h"
#include <vector>
#include <iostream>

using namespace std;

RobinHoodHashTable::RobinHoodHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
	table.resize(numBuckets);
	for(size_t i = 0; i < numBuckets; i++) {
		table[i] = -1;
	}
	h = family->get();
}

RobinHoodHashTable::~RobinHoodHashTable() {
	
}

void RobinHoodHashTable::printt() {
	for(size_t j = 0; j < table.size(); j++) {
		cout << table[j] << " ";
	}
	cout << endl;
}

void RobinHoodHashTable::insert(int data) {
	int m = table.size();
	int hval = h(data) % m;
	int mydist = -1;
	int curitem = data;
	for(int i = 0; i < m; i++) {
		int cur = (hval + i) % m;
		mydist++;
		//if we're at open spot insert
		if(table[cur] == -1) {
			//insert here!
			table[cur] = curitem;
			return;
		}
		//if it's not open, let's see if we're closer to home than current resident
		int placed_item = table[cur];
		int placed_hash = h(placed_item) % m;
		int placed_dist = (cur - placed_hash + m) % m;
		//we need to swap
		if(placed_dist < mydist) {
			table[cur] = curitem;
			mydist = placed_dist;
			curitem = placed_item;
		}
		if(table[cur] == curitem) {
			return;
		}
	}
}

bool RobinHoodHashTable::contains(int data) const {
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

/**
 * You should implement this operation using backward-shift deletion: once
 * you've found the element to remove, continue scanning forward until you
 * find an element that is at its home location or an empty cell, then shift
 * each element up to that point backwards by one step.
 */
void RobinHoodHashTable::remove(int data) {
	int m = table.size();
	int hval = h(data) % m;
	//let's first find elem to remove
	int sind = -1;
	for(int i = 0; i < m; i++) {
		int cur = (hval + i) % m;
		if(table[cur] == data) {
			sind = cur;
			break;
		}
	}
	//element not found :/
	if(sind == -1) return;

	//now let's bubble
	for(int i = 1; i < m; i++){
		size_t cur = (sind + i) % m;
		//if we found our stopping point
		if(table[cur] == -1 || (h(table[cur]) % m) == cur) {
			//clear the previous spot of a value
			table[(cur - 1 + m) % m] = -1;
			return;
		}
		//we need to bubble this element back
		table[(cur - 1 + m) % m] = table[cur];
	}
}