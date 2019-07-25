#include "Search.h"
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

//This function checks to see if pattern is lexicographically less, greater, or equal than suffix
int check(const string& pattern, const string& text, const size_t suffix) {

	size_t i = 0;
	for(i = 0; i < pattern.length() && i < text.length() - suffix; i++) {
		if(pattern[i] != text[i+suffix]) {
			return pattern[i] - text[i+suffix];
		}
	}
	//handle case where it matches first k characters but suffix is shorter
	if(i < pattern.length()) return 1;
	return 0;

}

vector<size_t> searchFor(const string& pattern,
                         const string& text,
                         const SuffixArray& suffixArr) {

	size_t n = text.length();
	//Let's binary search for the bottom index that matches
	int lo = 0;
	int hi = n;
	int ans = -1;
	while(lo <= hi) {
		size_t mid = (lo + hi)/2;
		int res = check(pattern, text, suffixArr[mid]);
		if(res == 0) {
			ans = mid;
			hi = mid - 1;
		} else if(res < 0){
			hi = mid - 1;
		}
		else{
			lo = mid + 1;
		}
	}

	//found nothing
	if(ans == -1) return {};

	//try upper
	lo = 0;
	hi = n;
	int ans1 = -1;
	while(lo <= hi) {
		size_t mid = (lo + hi)/2;
		int res = check(pattern, text, suffixArr[mid]);
		if(res == 0) {
			ans1 = mid;
			lo = mid + 1;
		} else if(res < 0){
			hi = mid - 1;
		}
		else{
			lo = mid + 1;
		}
	}
	//All indices between these two are in our answer!
	vector<size_t> ind;

	for(int i = ans; i <= ans1; i++){
		ind.push_back(suffixArr[i]);
	}
	return ind;
}
