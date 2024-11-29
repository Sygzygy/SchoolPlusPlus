/*
Excercise File Reader: Submitted by Jason Joseph

10/03/2024: Updated the FileReader::bin() to use the bitset library rather than returning a string.
10/04/2024: Updated the FileReader::csv() function to check for a comma and not delimit it when it is the first character in the row.
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>
#include <bitset>

using namespace std;

// File Reader class definition
class FileReader {
public:
    // Destructor
    ~FileReader() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    // Returns the file size
    int size(const string& fileName) {
        ifstream file(fileName, ios::binary | ios::ate);  // Open in binary mode, pointer at end
        if (!file.is_open()) {
            cerr << "Error opening the file: " << fileName << endl;
            return -1;  // Return -1 to indicate an error
        }

        int fileSize = static_cast<int>(file.tellg());  // Get the current position (file size)
        file.close();
        return fileSize;
    }

    // Returns the file data in ASCII (text file)
    vector<string> txt(const string& fileName) {
        vector<string> lines;
        fileStream.open(fileName);
        if (!fileStream.is_open()) {
            cerr << "Error opening the file: " << fileName << endl;
            return lines;
        }

        string line;
        while (getline(fileStream, line)) {
            lines.push_back(line);
        }
        fileStream.close();
        return lines;
    }

    // Reads a binary file and returns its contents as a vector of bitset<8>
    vector<bitset<8>> bin(const string& fileName) {
        fileStream.open(fileName, ios::binary);
        if (!fileStream.is_open()) {
            cerr << "Error opening the file: " << fileName << endl;
            return {};
        }

        vector<bitset<8>> binaryData;
        char byte;

        // Read each byte from the binary file
        while (fileStream.read(&byte, 1)) {
            bitset<8> bits(byte);  // Convert each byte into a bitset of 8 bits
            binaryData.push_back(bits);
        }

        fileStream.close();
        return binaryData;
    }

    // Returns the file data parsed as CSV using regex
    vector<vector<string>> csv(const string& fileName) {
        vector<vector<string>> csvData;
        fileStream.open(fileName);
        if (!fileStream.is_open()) {
            cerr << "Error opening the file: " << fileName << endl;
            return csvData;
        }

        string line;
        while (getline(fileStream, line)) {
            vector<string> row;
            // Added an if-else block for when the csv row starts with a comma, 
            // to catch any rows that define the morse code for a comma.
            if (line[0] == ',') {
                // Special handling for the first comma being a character
                row.push_back(",");  // Push the first comma as a character
                line = line.substr(1);  // Remove the first character (comma) from the line

                // Split the remaining part of the line using regular CSV logic
                regex re(R"(([^,]+))");
                sregex_token_iterator it(line.begin(), line.end(), re);
                sregex_token_iterator end;
                for (; it != end; ++it) {
                    row.push_back(it->str());
                }
            }
            else {
                // Normal handling for rows without the special first comma
                regex re(R"(([^,]+))");
                sregex_token_iterator it(line.begin(), line.end(), re);
                sregex_token_iterator end;
                for (; it != end; ++it) {
                    row.push_back(it->str());
                }
            }
            csvData.push_back(row);
        }
        fileStream.close();
        return csvData;
    }

private:
    ifstream fileStream;
}; // End of Class FileReader