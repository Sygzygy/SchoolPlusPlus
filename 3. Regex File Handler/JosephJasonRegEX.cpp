/*
Excercise RegEx: Submitted by Jason Joseph
Submitted on September 30, 2024

This program focuses on a file handler class that can search for lines containing a specific keyword from any file, regardless of casing.
regex constant icase from: https://cplusplus.com/reference/regex/regex_constants/ and https://en.cppreference.com/w/cpp/regex/syntax_option_type
*/

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>

using namespace std;
 
//start of class FileHandler
class FileHandler {
public:

	// FileHandler constructor
	FileHandler(const string& fileName) : fileName(fileName) {}

	// FileHandler destructor
	~FileHandler() {
		if (fileStream.is_open()) {
			fileStream.close();
		}
	}

	// File opening function
	bool openFile() {
		fileStream.open(fileName);
		if (!fileStream.is_open()) {
			cerr << "Error opening the file" << endl;
			return false;
		}
		return true;
	}

	// Keyword finding function
	vector<string> findKeyword(const string& keyword) {
		vector<string> foundLines;
		string line;

		if (!openFile()) {
			return foundLines;
		}

		// Regex pattern to match whole word occurrences of the keyword, regardless of casing
		regex keywordPattern("\\b" + keyword + "\\b", regex_constants::icase);

		// Read the file line by line
		while (getline(fileStream, line)) {
			smatch matches;
			// Search for the keyword in the current line
			if (regex_search(line, matches, keywordPattern)) {
				// Add the matching line to the result
				foundLines.push_back(line);
			}
		}
		fileStream.close();
		return foundLines;
	}

private:
	ifstream fileStream;
	string fileName;
	string keyword;
}; // end of class FileHandler

// *************************************************************************

// Creates a FileHandler object for the specified file, searches for lines containing the specified keyword using regex,
// and outputs each matching line to the console.
int main() {
	// Replace "keywordfile.cpp" with your file's name
	FileHandler cppFile("keywordfile.cpp");

	// Replace keyword "if" with any desired keyword
	vector<string> keywordList = cppFile.findKeyword("if");

	for (const string output : keywordList) {
		cout << output << endl;
	}
}