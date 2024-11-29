/*
Excercise File Reader: Submitted by Jason Joseph
Submitted on September 25, 2024

*/

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>

using namespace std;

// File Reader class definition
class FileReader {
public:
	// Constructor to initialize with a file name
	FileReader(const string& fileName) : fileName(fileName) {}

	// Destructor
	~FileReader() {
		if (fileStream.is_open()) {
			fileStream.close();
		}
	}

	// Returns the file name
	string name() {
		return fileName;
	}
	
	// Returns the file size
	size_t size() {
		fileStream.open(fileName, ios::binary | ios::ate); // open at the end of file
		if (!fileStream.is_open()) {
			cerr << "Error opening the file" << endl;
			return 0;
		}

		size_t fileSize = fileStream.tellg(); // get file size
		fileStream.close();
		return fileSize;
	}

	// Returns the file data in ASCII (text file)
	vector<string> txt() {
		vector<string> lines;
		fileStream.open(fileName);
		if (!fileStream.is_open()) {
			cerr << "Error opening the file" << endl;
			return lines;
		}

		string line;
		while (getline(fileStream, line)) {
			lines.push_back(line);
		}
		fileStream.close();
		return lines;
	}

	// Returns the file data in Binary as a string
	string bin() {
		// Open the file in binary mode
		fileStream.open(fileName, ios::binary);
		if (!fileStream.is_open()) {
			cerr << "Error opening the file" << endl;
			return {};
		}

		// Seek to the end to determine the file size
		fileStream.seekg(0, ios::end);
		size_t fileSize = fileStream.tellg();
		fileStream.seekg(0, ios::beg);  // Reset to the beginning

		// Resize the string to hold binary data
		string binaryData(fileSize, '\0');  // Fill string with null characters initially

		// Read the binary data into the string
		fileStream.read(&binaryData[0], fileSize);

		fileStream.close();
		return binaryData;
	}

	// Returns the file data parsed as CSV using regex
	vector<vector<string>> csv() {
		vector<vector<string>> csvData;
		fileStream.open(fileName);
		if (!fileStream.is_open()) {
			cerr << "Error opening the file" << endl;
			return csvData;
		}

		string line;
		while (getline(fileStream, line)) {
			vector<string> row;
			regex re(R"(([^,]+))");  // Regex to split by commas
			sregex_token_iterator it(line.begin(), line.end(), re);
			sregex_token_iterator end;
			for (; it != end; ++it) {
				row.push_back(it->str());
			}
			csvData.push_back(row);
		}
		fileStream.close();
		return csvData;
	}

private:
	ifstream fileStream;
	string fileName;
};


// Main function for testing
int main() {
	// Test the text file reading functionality
	FileReader txtReader("MorseMap.txt");
	vector<string> textData = txtReader.txt();
	cout << "Text File Data:" << endl;
	for (const auto& line : textData) {
		cout << line << endl;
	}
	cout << endl;

	// Test the binary file reading functionality
	FileReader binReader("CompressEx.bin");
	string binaryData = binReader.bin();
	cout << "Binary File Data (Hex Representation):" << endl;
	for (unsigned char c : binaryData) {
		cout << hex << setw(2) << setfill('0') << static_cast<int>(c) << " ";
	}
	cout << endl << endl;

	// Test the CSV file reading functionality
	FileReader csvReader("Frequencies.csv");
	vector<vector<string>> csvData = csvReader.csv();
	cout << "CSV File Data:" << endl;
	for (const auto& row : csvData) {
		for (const auto& field : row) {
			cout << field << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Test the file size function
	size_t textFileSize = txtReader.size();
	cout << "Size of Text File: " << textFileSize << " bytes" << endl;

	size_t binaryFileSize = binReader.size();
	cout << "Size of Binary File: " << binaryFileSize << " bytes" << endl;

	size_t csvFileSize = csvReader.size();
	cout << "Size of CSV File: " << csvFileSize << " bytes" << endl;

	return 0;
}
