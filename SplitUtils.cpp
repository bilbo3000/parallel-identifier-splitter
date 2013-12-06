#include "SplitUtils.h"

/**
 * Split identifiers at camel case.
 */
string SplitUtils::camelCaseSplit(string word, const set<string> &wordList) {
	if (word.length() <= 1) return word;
	
	int i = 1; // i points to the current character
	
	while (i < word.length()) {
		// lower in front of upper, split before upper
		if (isupper(word[i]) && islower(word[i - 1])) {
			word.insert(i, " ");
			i = i + 1;
		}

		// multiple upper in front of lower (i points to last upper)
		if (i < word.length() - 1 && isupper(word[i]) && isupper(word[i - 1])
				&& islower(word[i + 1])) {
			// find the last space ahead of i
			int lindex = word.find_last_of(" ", i);

			// substrs when split before current upper
			string left = word.substr(lindex + 1, i - lindex - 1);
			transform(left.begin(), left.end(), left.begin(), ::tolower); 
			string right = word.substr(i, word.length() - i);
			transform(right.begin(), right.end(), right.begin(), ::tolower); 

			// substrs when split after current upper 
			string left2 = word.substr(lindex + 1, i - lindex);
			transform(left2.begin(), left2.end(), left2.begin(), ::tolower); 
			string right2 = word.substr(i + 1, word.length() - i - 1);
			transform(right2.begin(), right2.end(), right2.begin(), ::tolower); 

			if (wordList.find(left) != wordList.end()
					|| wordList.find(right) != wordList.end()) {
				word.insert(i, " ");
				i = i + 1;  // points to space
			} else if (wordList.find(left2) != wordList.end()
					|| wordList.find(right2) != wordList.end()) {
				word.insert(i + 1, " ");  // points to space
				i = i + 1;
			}
		}

		i = i + 1;  // points to next character
	}  // end of while

	return word;
} 
	
/**
 * Dynamic programming approach to split same case identifiers.
 */
vector<string> SplitUtils::sameCaseSplitDP(string word, const set<string> &wordList, int version) {
	vector<string> result;

	if (word.size() <= 1) {
		result.push_back(word);
		return result;
	}

	transform(word.begin(), word.end(), word.begin(), ::tolower);  // Convert to lower case
	if (wordList.find(word) != wordList.end())
	{
		result.push_back(word);
		return result;
	}

	// Choose which version of dp splitting algorithm to use
	// 1: maximize longest word
	// 2: maximize number of words in dictionary
	// 3: minimize number of words not in dictionary
	switch(version) {
	case 1:
		result = maxLongestWord(word, wordList);
		break;
	case 2:
		result = maxNumOfWordsInDict(word, wordList);
		break;
	case 3:
		result = minNumOfWordsNotInDict(word, wordList);
		break;
	default:
		result = maxLongestWord(word, wordList);
	}

	return result;
}

/**
 * Maximize the length of longest word that exists in the dictionary.
 */
vector<string> SplitUtils::maxLongestWord(string word, const set<string> &wordList) {
	// Create cost table t and reconstruct table d
	int n = word.size();
	vector<vector<int> > t; 
	vector<vector<int> > d; 
	
	// Initialize the cost table and reconstruct table
	for (int i = 0; i < n; i++) {
		vector<int> temp(n, 0);
		t.push_back(temp);
	}

	for (int i = 0; i < n; i++) {
		vector<int> temp(n, -1);
		d.push_back(temp);
	}
	
	// Initialize first row: split just the first char
	if (wordList.find(word.substr(0, 1)) != wordList.end()) {
		t[0].resize(n, 1);
	}

	// Initialize first column: split just into one range
	for (int i = 0; i < n; i++) {
		if (wordList.find(word.substr(0, i + 1)) != wordList.end()) {
			t[i][0] = i + 1;
		}
	}
	
	// Evaluate the main DP recurrence
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int x = j - 1; x < i; x++) {  // Each possible split
				int cost = 0;

				if (wordList.find(word.substr(x + 1, i - x)) != wordList.end()) {
					cost = max(t[x][j - 1], i - x);
				}
				else {
					cost = t[x][j - 1];
				}

				// Get max length among all splits
				if (cost > t[i][j]) {
					t[i][j] = cost;
					d[i][j] = x;  // Get divider, insert after x
				}
			}
		}
	}

	// Reconstruct the word
	vector<string> result;
	int max = t[n - 1][0];

	for (int j = 1; j < n; j++) {
		if (t[n - 1][j] > max) {
			max = t[n - 1][j];
		}
	}

	set<string> history;

	for (int j = 0; j < n; j++) {
		if (t[n - 1][j] == max) {
			string line = reconstruct(word, d, j);
			if (history.find(line) == history.end()) {
				result.push_back(line);
				history.insert(line);
			}
		}
	}

	return result;
}

/**
 * Maximize the number of words that exists in the dictionary.
 */
vector<string> SplitUtils::maxNumOfWordsInDict(string word, const set<string> &wordList) {
	// Create cost table t and reconstruct table d
	int n = word.size();
	vector<vector<int> > t;
	vector<vector<int> > d;

	// Initialize the cost table and reconstruct table
	for (int i = 0; i < n; i++) {
		vector<int> temp(n, 0);
		t.push_back(temp);
	}

	for (int i = 0; i < n; i++) {
		vector<int> temp(n, -1);
		d.push_back(temp);
	}
	
	// Initialize first row: split just the first char 
	if (wordList.find(word.substr(0, 1)) != wordList.end()) {
		t[0].resize(n, 1); 
	}
	
	// Initialize first column: split just into one range
	for (int i = 0; i < n; i++) {
		if (wordList.find(word.substr(0, i + 1)) != wordList.end()) {
			t[i][0] = 1;
		}
	}
	
	// Evaluate the main DP recurrence 
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int x = j - 1; x < i; x++) {  // Each possible split
				int cost = 0; 
				
				if (wordList.find(word.substr(x + 1, i - x)) != wordList.end()) {
					cost = t[x][j - 1] + 1;
				}
				else {
					cost = t[x][j - 1]; 
				}
				
				// Get max length among all splits 
				if (cost > t[i][j]) {
					t[i][j] = cost; 
					d[i][j] = x;  // Get divider, insert after x
				}
			}
		}
	}

	// Reconstruct the word
	vector<string> result;
	int max = t[n - 1][0];

	for (int j = 1; j < n; j++) {
		if (t[n - 1][j] > max) {
			max = t[n - 1][j];
		}
	}

	set<string> history;

	for (int j = 0; j < n; j++) {
		if (t[n - 1][j] == max) {
			string line = reconstruct(word, d, j);
			if (history.find(line) == history.end()) {
				result.push_back(line);
				history.insert(line);
			}
		}
	}

	return result;
}

/**
 * Minimize the number of words that do not exist in the dictionary.
 */
vector<string> SplitUtils::minNumOfWordsNotInDict(string word, const set<string> &wordList) {
	// Create cost table t and reconstruct table d
	int n = word.size();
	vector<vector<int> > t;
	vector<vector<int> > d;

	// Initialize the cost table and reconstruct table
	for (int i = 0; i < n; i++) {
		vector<int> temp(n, INT_MAX);
		t.push_back(temp);
	}

	for (int i = 0; i < n; i++) {
		vector<int> temp(n, -1);
		d.push_back(temp);
	}

	// Initialize first row: split just the first char
	if (wordList.find(word.substr(0, 1)) != wordList.end()) {
		t[0].resize(n, 0);
	}
	else {
		t[0].resize(n, 1);
	}

	// Initialize first column: split just into one range
	for (int i = 0; i < n; i++) {
		if (wordList.find(word.substr(0, i + 1)) != wordList.end()) {
			t[i][0] = 0;
		}
		else {
			t[i][0] = 1;
		}
	}

	// Evaluate the main DP recurrence
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int x = j - 1; x < i; x++) {  // Each possible split
				int cost = 0;

				if (wordList.find(word.substr(x + 1, i - x)) == wordList.end()) {
					cost = t[x][j - 1] + 1;
				}
				else {
					cost = t[x][j - 1];
				}

				// Get max length among all splits
				if (cost < t[i][j]) {
					t[i][j] = cost;
					d[i][j] = x;  // Get divider, insert after x
				}
			}
		}
	}

	// Reconstruct the word
	vector<string> result;
	int min = t[n - 1][0];

	for (int j = 1; j < n; j++) {
		if (t[n - 1][j] < min) {
			min = t[n - 1][j];
		}
	}

	set<string> history;

	for (int j = 0; j < n; j++) {
		if (t[n - 1][j] == min) {
			string line = reconstruct(word, d, j);
			if (history.find(line) == history.end()) {
				result.push_back(line);
				history.insert(line);
			}
		}
	}

	return result;
}

/**
 * Reconstruct the path and make the split. 
 * s: substring to be construct
 * d: divider table
 * k: column (divided into k + 1 regions)
 */ 
string SplitUtils::reconstruct(string s, const vector<vector<int> > &d, int k) {
	if (k == 0) {
		return s; 
	}

	int n = s.size();  // Length of current substring
	int dividerPos = d[n - 1][k];  // Get the divider position
	
	if (dividerPos == -1) return s;

	return reconstruct(s.substr(0, dividerPos + 1), d, k - 1) + " " + s.substr(dividerPos + 1); 
}

/**
 * Helper function that prints out a matrix.
 */
void SplitUtils::printMatrix(const vector<vector<int> > &mat) {
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[i].size(); j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}
