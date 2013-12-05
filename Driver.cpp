#include <iostream> 
#include <fstream> 
#include "Dictionary.h"
#include "SplitUtils.h"

using namespace std; 

/**
 * Main class that drives the program. 
 */ 
int main(int argc, char* argv[]) {
	// Build dictionaries 
	Dictionary* dictionary = Dictionary::getInstance(); 
	set<string> vocabDict = dictionary->getVocabDict(); 
	set<string> preSufDict = dictionary->getPreSufDict(); 
	
	// Process identifiers 
	string line = ""; 
	string filePath = "./input/identifier.txt"; 
	ifstream inputStream; 
	inputStream.open(filePath.c_str()); 
	
	if (inputStream.is_open()) {
		while (inputStream.good()) {
			getline(inputStream, line);
			string temp = SplitUtils::camelCaseSplit(line, vocabDict);   
		}
	}
	
	SplitUtils::sameCaseSplitDP("casesensitive", vocabDict);
	// SplitUtils::sameCaseSplitDP("browserid", vocabDict);
	
	return 0; 
}
