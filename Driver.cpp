#include <iostream> 
#include <fstream> 
#include "Dictionary.h"
#include "SplitUtils.h"
#include "Utils.h"
#include <cassert>
#include <vector>
#include <time.h> 

using namespace std; 

vector<string> combineWords(vector<vector<string> > &words);

/**
 * Main class that drives the program. 
 */ 
int main(int argc, char* argv[]) {
    time_t t1;
    time(&t1); 
    cout << "t1:" << t1 << endl;

	// Validate arguments
	assert(argc == 3);
	vector<string> inputs  = Utils::splitStringVector(argv[1], ",");
	string word = inputs[0];
	string oracle = inputs[1];
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
	cout << word << endl;  // Print out original word;
	transform(oracle.begin(), oracle.end(), oracle.begin(), ::tolower);
	cout << oracle << endl;  // Print out oracle
	cout << finalResults.size() << endl;  // Print out number of splits

	for (int i = 0; i < finalResults.size(); i++)
		cout << finalResults[i] << endl;

    time_t t2;
    time(&t2); 
    cout << "t2:" << t2 << endl; 
    //cout << "time:" << double(t2 - t1) / CLOCKS_PER_SEC << endl; 

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
