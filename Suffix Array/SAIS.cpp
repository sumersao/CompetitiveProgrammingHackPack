#include "SAIS.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;

//Marks every character to be 1 if it's an S-type or 0 if L-type
vector<bool> s_or_l(const vector<size_t>& text) {
	size_t n = text.size();
	vector<bool> res(n);
	for(int i = n - 2; i >= 0; i--) {
		if(text[i] < text[i + 1]) res[i] = 1;
		else if(text[i] == text[i+1]) res[i] = res[i+1];
	}
	//sentinel
	res[n-1] = 1;
	return res;
}

//This function computes the LMS values in the string
vector<size_t> find_lms(vector<bool>& marked) {
	size_t n = marked.size();
	vector<size_t> res;
	for(int i = n - 1; i > 0; i--) {
		if(marked[i] && !marked[i-1]) res.push_back(i);
	}
	return res;
}

void forwardArrayPass(vector<size_t>& out, const vector<size_t>& text, const vector<bool>& marked_suffixes, 
					 const vector<pair<size_t, size_t>>& boundaries, const vector<size_t>& lms, 
					 vector<bool>& usedForward, vector<bool>& usedBackward) {

	vector<size_t> firstIndexPointers(boundaries.size());

	for(size_t i = 0; i < boundaries.size(); i++) {
		firstIndexPointers[i] = boundaries[i].first;
	}

	for(size_t i = 0; i < out.size(); i++) {
		if(usedForward[i] && out[i] > 0 && !marked_suffixes[out[i]-1]) {
			size_t curr_char = text[out[i]-1];
			out[firstIndexPointers[curr_char]] = out[i] - 1;
			usedForward[firstIndexPointers[curr_char]] = true;
			usedBackward[firstIndexPointers[curr_char]] = true;
			firstIndexPointers[curr_char] += 1;
		}
	}
}

void backwardArrayPass(vector<size_t>& out, const vector<size_t>& text, const vector<bool>& marked_suffixes, 
					 const vector<pair<size_t, size_t>>& boundaries, const vector<size_t>& lms, 
					 vector<bool>& usedForward, vector<bool>& usedBackward) {

	vector<size_t> lastIndexesPointers(boundaries.size());

	for(size_t i = 0; i < boundaries.size(); i++) {
		lastIndexesPointers[i] = boundaries[i].second - 1;
	}

	for(int i = out.size()-1; i >= 0; i--) {

		if(usedBackward[i] && out[i] > 0 && marked_suffixes[out[i]-1]) {
			size_t curr_char = text[out[i]-1];
			out[lastIndexesPointers[curr_char]] = out[i] - 1;
			usedBackward[lastIndexesPointers[curr_char]] = true;
			lastIndexesPointers[curr_char] -= 1;
		}
	}
}

//This function computes the suffix array using induced sorting
SuffixArray computeSuffixArray(const vector<size_t>& text, const vector<bool>& marked_suffixes, 
								  const vector<pair<size_t, size_t>>& boundaries, const vector<size_t> lms) {
	vector<size_t> out(text.size());

	for(size_t i = 0; i < out.size(); i++) {
		out[i] = 99;
	}

	vector<size_t> lastIndexesPointers(boundaries.size());



	for(size_t i = 0; i < boundaries.size(); i++) {
		lastIndexesPointers[i] = boundaries[i].second-1;
	}

	vector<bool> usedForward(text.size(), false);
	vector<bool> usedBackward(text.size(), false);

	for(int i = lms.size()-1; i >= 0; i--) {
		size_t curr_lms = lms[i];
		size_t curr_char = text[curr_lms];
		out[lastIndexesPointers[curr_char]] = curr_lms;
		usedForward[lastIndexesPointers[curr_char]] = true;
		lastIndexesPointers[curr_char] -= 1;
	}

	forwardArrayPass(out, text, marked_suffixes, boundaries, lms, usedForward, usedBackward);
	backwardArrayPass(out, text, marked_suffixes, boundaries, lms, usedForward, usedBackward);

	return out;
}

SuffixArray sais(const vector<size_t>& text) {

  	vector<bool> marked_suffixes = s_or_l(text);
  	vector<size_t> lms = find_lms(marked_suffixes);
  	//Reverse lms order to be from small to large for ease later
  	reverse(lms.begin(), lms.end());
  	//we need to also make a boolean vector of indexed lms for later
  	vector<bool> indexed_lms(text.size());
  	for(size_t i = 0; i < lms.size(); i++) {
  		indexed_lms[lms[i]] = 1;
  	}

  	//let's now compute the boundary array
  	//first get the largest character value in our text
  	size_t maxi = 0;
  	for(size_t i = 0; i < text.size(); i++) {
  		maxi = max(text[i], maxi);
  	}
  	vector<size_t> f(maxi + 1);
  	for(size_t i = 0; i < text.size(); i++) {
  		f[text[i]]++;
  	}

  	//Base case for recursion: if frequency of all is 1 or 0 return ans
  	bool base = 1;
  	for(size_t i = 0; i < f.size(); i++) {
  		if(f[i] > 1) {
  			base = false;
  		}
  	}

  	if(base) {
  		SuffixArray res(text.size());
  		for(size_t i = 0; i < text.size(); i++) {
  			res[text[i]] = i;
  		}
  		return res;
  	}

    //Let's compute the boundaries using the frequency table

  	vector<pair<size_t, size_t> > boundaries(maxi + 1);
  	size_t num = 0;
  	for(size_t i = 0; i < boundaries.size(); i++) {
  		boundaries[i] = make_pair(num, num + f[i]);
  		num += f[i];
  	}

    //First pass to sort LMS blocks
  	SuffixArray incorrect = computeSuffixArray(text, marked_suffixes, boundaries, lms);

  	//Let's now extract the correct order of lms blocks
  	vector<size_t> sorted_lms_blocks;
  	//Also maintain a mapping: takes in original index, maps to index in sorted 
  	vector<size_t> map(text.size());
  	for(size_t i = 0; i < incorrect.size(); i++) {
  		if(indexed_lms[incorrect[i]]) {
  			sorted_lms_blocks.push_back(incorrect[i]);
  			map[incorrect[i]] = (sorted_lms_blocks.size() - 1);
  		}
  	}

  	//let's compute the length of each lms block to help later
  	vector<size_t> lms_block_len(lms.size());
  	for(size_t i = 0; i < lms.size(); i++) {
  		size_t j = lms[i] + 1;
  		size_t cur = 1;
  		while(j < text.size()) {

  			if(indexed_lms[j]) {
  				cur++;
  				break;
  			}
  			cur++;
  			j++;
  		}
  		lms_block_len[map[lms[i]]] = cur;
  	}

  	//Now let's map each lms to a distinct num
  	vector<size_t> lms_to_num(lms.size());

  	lms_to_num[0] = 0;
  	size_t num_dis = 0;
  	for(size_t i = 1; i < sorted_lms_blocks.size(); i++) {
  		//compare these two blocks to see if they're the same
  		bool same = 1;
  		size_t s1 = sorted_lms_blocks[i-1];
  		size_t s2 = sorted_lms_blocks[i];
  		size_t up1 = s1 + lms_block_len[i-1];
  		size_t up2 = s2 + lms_block_len[i];
  		while(s1 < up1 && s2 < up2) {
  			if(text[s1] != text[s2]) {
  				same = 0;
  				break;
  			}
  			s1++;
  			s2++;
  		}

  		if(!same) {
  			num_dis++;
  		}
  		lms_to_num[i] = num_dis;
  	}

  	//Now that I have lms to num, create the new array
  	vector<size_t> new_text(lms.size());

  	for(size_t i = 0; i < lms.size(); i++) {
  		new_text[i] = lms_to_num[map[lms[i]]];
  	}

    //Get the SA for this new array (recursion)
  	SuffixArray order_lms = sais(new_text);

  	//now we can get our real sorted using this SA
  	vector<size_t> actual_sorted;
  	for(size_t i = 0; i < order_lms.size(); i++) {
  		actual_sorted.push_back(lms[order_lms[i]]);
  	}

  	//now call Induced sorting again to complete the SA construction
  	SuffixArray SA = computeSuffixArray(text, marked_suffixes, boundaries, actual_sorted);
  	return SA;
}