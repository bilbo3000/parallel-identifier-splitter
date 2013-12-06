#ifndef SPLITUTILS_H_
#define SPLITUTILS_H_

#include <string> 
#include <set> 
#include <algorithm> 
#include <vector> 
#include <iostream> 
#include <climits>

using namespace std; 

/**
 * Class contains identifier split algorithms including the camel case 
 * split algorithm and same case split algorithm. 
 *
 * Dongpu 
 * 11/30/2013
 */ 
class SplitUtils {
public: 
	// Split camel case identifers  
	static string camelCaseSplit(string word, const set<string> &wordList); 
	
	// Split same case identifiers (after camel case split)
	static vector<string> sameCaseSplitDP(string word, const set<string> &wordList, int version);

private: 
	static vector<string> maxLongestWord(string word, const set<string> &wordList);
	static vector<string> maxNumOfWordsInDict(string word, const set<string> &wordList);
	static vector<string> minNumOfWordsNotInDict(string word, const set<string> &wordList);
	
	static void printMatrix(const vector<vector<int> > &mat);

	static string reconstruct(string s, const vector<vector<int> > &d, int k);
}; 

#endif
