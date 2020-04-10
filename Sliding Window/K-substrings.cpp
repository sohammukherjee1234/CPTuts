/*Problem statement : Find  no of substrings of length K with no repeated characters*/

#include <bits/stdc++.h>
using namespace std;


bool isDistinct(int *freq){
	//Returns true if freq array has all elements <= 1

	for(int i=0; i<26; i++) if(freq[i] > 1) return false;

	return true;
}

int kSubstrings(string &s, int k){
	int freq[26]; //Frequency of characters in current window
	fill(freq, freq+26, 0);

	//count for first window i.e first k elements

	for(int i=0; i<k; i++){
		freq[(int)(s[i] - 'a')] ++;
	}

	int ans = 0;
	//check if first window has all distinct elements i.e freq[i] <= 1
	if(isDistinct(freq)) ans++;

	/*
		Now slide the window by 1 unit in each iteration.
		In each iteration, one element gets included in current window
		and one gets excluded
	*/

	for(int i=k; i<s.length(); i++){
		freq[(int)(s[i] - 'a')] ++; //element included
		freq[(int)(s[i-k] - 'a')] --; //element excluded

		if(isDistinct(freq)) ans++;
	}

	return ans;
}



int main() {
	// your code goes here
	
    string s = "abcdabacde";
    cout<<kSubstrings(s, 4);
	return 0;
}
