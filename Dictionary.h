#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <set> 
#include <string> 
#include <fstream> 

using namespace std; 

/**
 * Class that creates the dictionary used for parsing. 
 * Dongpu
 * 12/5/2013
 */ 
class Dictionary {
private: 
	// Private constructor 
	Dictionary(); 
	
	// Singleton instance of the class
	static Dictionary* instance; 
	 
	set<string> vocabDict;  // Set of vocabularies and cs abbreviations 
	set<string> preSufDict;  // Set of commonly used prefix/suffix
	
	// Build dictionaries 
	void buildDict(); 
	void collectWords(set<string> &s, string filePath); 
	
public: 
	// Retrieve the singleton instance 
	static Dictionary* getInstance(); 
	 
	set<string> getVocabDict() { return vocabDict; }
	set<string> getPreSufDict() { return preSufDict; }
}; 

#endif
