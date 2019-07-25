#include "CuckooHashTable.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/**
 * Since cuckoo hashing requires two tables, you should create two tables
 * of size numBuckets / 2. Because our testing harness attempts to exercise
 * a number of different load factors, you should not change the number of
 * buckets once the hash table has initially be created.
 */
CuckooHashTable::CuckooHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
	n = numBuckets;
	hfam = family;
	table1.resize(n/2);
	table2.resize((n+1)/2);
	for(size_t i = 0; i < table1.size(); i++) {
		table1[i] = -1;
	}
	for(size_t i = 0; i < table2.size(); i++) {
		table2[i] = -1;
	}
	h1 = hfam->get();
	h2 = hfam->get();
}

CuckooHashTable::~CuckooHashTable() {
	
}

//return -1 if it worked, otherwise return the element currently not placed
int CuckooHashTable::insert_helper(int data) {
	int cycle = (int) 6*log(n);
	// 0 = 1, 1 = 2
	int table_num = 0;
	int curelem = data;
	int numdisp = -1;
	int m1 = table1.size();
	int m2 = table2.size();
	while(numdisp < cycle) {
		numdisp++;
		if(table_num == 0) {
			//check if the spot for curelem is empty in table1
			int hval1 = h1(curelem) % m1;
			int prevelem = table1[hval1];
			if(table1[hval1] == -1) {
				table1[hval1] = curelem;
				return -1;
			}
			table1[hval1] = curelem;
			curelem = prevelem;
			table_num = (table_num + 1) % 2;
		} else {
			//check if the spot for curelem is empty in table2
			int hval2 = h2(curelem) % m2;
			int prevelem = table2[hval2];
			if(table2[hval2] == -1) {
				table2[hval2] = curelem;
				return -1;
			}
			table2[hval2] = curelem;
			curelem = prevelem;
			table_num = (table_num + 1) % 2;
		}
	}
	return curelem;
}

void CuckooHashTable::insert(int data) {
	if(contains(data)) return;
	//try to insert the element
	int excluded = insert_helper(data);
	if(excluded == -1) return;
	
	//we have to do rehash :/
	//save the previous elems
	vector<int> elems;
	for(size_t i = 0; i < table1.size(); i++) {
		if(table1[i] != -1) elems.push_back(table1[i]);
	}
	for(size_t i = 0; i < table2.size(); i++) {
		if(table2[i] != -1) elems.push_back(table2[i]);
	}
	elems.push_back(excluded);
	//reset our tables to be empty
	for(size_t i = 0; i < table1.size(); i++) {
		table1[i] = -1;
	}
	for(size_t i = 0; i < table2.size(); i++) {
		table2[i] = -1;
	}
	//get new functions
	h1 = hfam->get();
	h2 = hfam->get();

	//now try adding all of the new elems
	for(size_t i = 0; i < elems.size(); i++) {
		insert(elems[i]);
	}
}

bool CuckooHashTable::contains(int data) const {
	int m1 = table1.size();
	int m2 = table2.size();
	int hval1 = h1(data) % m1;
	int hval2 = h2(data) % m2;
	return table1[hval1] == data || table2[hval2] == data;
}

void CuckooHashTable::remove(int data) {
	//try the first table first
	int m1 = table1.size();
	int hval1 = h1(data) % m1;

	if(table1[hval1] == data) {
		table1[hval1] = -1;
		return;
	}

	//try the second
	int m2 = table2.size();
	int hval2 = h2(data) % m2;
	if(table2[hval2] == data){
		table2[hval2] = -1;
	}
}
