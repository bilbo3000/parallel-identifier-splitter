#include "Dictionary.h"

Dictionary* Dictionary::instance = 0; 

// Private constructor, bulid dictoinary 
Dictionary::Dictionary() {
	buildDict(); ; 
}

Dictionary* Dictionary::getInstance() {
	if (instance == 0) {
		instance = new Dictionary(); 
	}
	
	return instance; 
}

void Dictionary::buildDict() {
	collectWords(vocabDict, "./dict.txt");  // Vocabulary 
	// collectWords(vocabDict, "./dict/cs_abbr.txt");  // CS abbreviations 
	// collectWords(preSufDict, "./dict/prefixes.txt");  // Commonly used prefix
	// collectWords(preSufDict, "./dict/suffixes.txt");  // Commonly used suffix
}

void Dictionary::collectWords(set<string> &s, string filePath) {
	ifstream inputStream; 
	string line = ""; 
	inputStream.open(filePath.c_str()); 
	
	if (inputStream.is_open()) {
		while (inputStream.good()) {
			getline(inputStream, line); 
			s.insert(line); 
		}
	}
	
	inputStream.close(); 
} 
