#include <iostream> 
#include <fstream> 
#include "Dictionary.h"
#include "SplitUtils.h"
#include "Utils.h"
#include <cassert>
#include <vector>

using namespace std; 

vector<string> combineWords(vector<vector<string> > &words);

/**
 * Main class that drives the program. 
 */ 
int main(int argc, char* argv[]) {
	// Validate arguments
	assert(argc == 3);
	string word = argv[1];
	int version = atoi(argv[2]);

	// Build dictionaries 
	Dictionary* dictionary = Dictionary::getInstance(); 
	set<string> vocabDict = dictionary->getVocabDict(); 
	
	// Camel case split
	string temp = SplitUtils::camelCaseSplit(word, vocabDict);
	vector<string> tempv = Utils::splitStringVector(temp, " ");

	vector<vector<string> > result;

	for (int i = 0; i < tempv.size(); i++) {
		// Same case split
		vector<string> sameCasesplitResult = SplitUtils::sameCaseSplitDP(tempv[i], vocabDict, version);
		result.push_back(sameCasesplitResult);
	}
	
	vector<string> finalResults = combineWords(result);

	for (int i = 0; i < finalResults.size(); i++)
		cout << finalResults[i] << endl;
	return 0; 
}

/*
 * Generate all combinations of words.
 */
vector<string> combineWords(vector<vector<string> > &words) {
	vector<string> result;
	if (words.size() == 0) return result;
	if (words.size() == 1) return words[0];

	vector<string> curr = words[0];
	words.erase(words.begin());
	vector<string> temp = combineWords(words);
	set<string> history;

	for (int i = 0; i < curr.size(); i++) {
		for (int j = 0; j < temp.size(); j++) {
			string currWord = curr[i] + " " + temp[j];

			if (history.find(currWord) == history.end()) {
				history.insert(currWord);
				result.push_back(currWord);
			}
		}
	}

	return result;
}
