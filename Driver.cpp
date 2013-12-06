#include <iostream> 
#include <fstream> 
#include "Dictionary.h"
#include "SplitUtils.h"
#include <cassert>

using namespace std; 

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
	
	// Same case split
	SplitUtils::sameCaseSplitDP(temp, vocabDict, version);
	
	return 0; 
}
