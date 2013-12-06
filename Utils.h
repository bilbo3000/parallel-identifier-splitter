#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>

using namespace std;

/**
 * Utility static class.
 */
class Utils {
public:
	/*
	 * Split a string into a vector at given delimiter.
	 */
	static vector<string> splitStringVector(string str, string delim);

	/*
	 * Join a vector of string using given delimiter.
	 */
	static string joinStringVector(vector<string> strVector, string delim);
};

#endif
