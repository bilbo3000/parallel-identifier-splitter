#include "Utils.h"

vector<string> Utils::splitStringVector(string str, string delim) {
	int start = 0;
	int end;
	vector<string> v;
	while ((end = str.find(delim, start)) != string::npos) {
		v.push_back(str.substr(start, end - start)); // get substring
		start = end + delim.length(); // process rest of the string
	}
	v.push_back(str.substr(start));
	return v;
}

string Utils::joinStringVector(vector<string> strVector, string delim) {
	if (strVector.empty()) { // empty set
		return "";
	}

	// not empty
	vector<string>::iterator strSetit = strVector.begin();
	string result = *strSetit; // points first item
	strSetit++;

	while (strSetit != strVector.end()) {
		result = result + delim + *strSetit;
		strSetit++;
	}

	return result;
}
