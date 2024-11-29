/*
Excercise File Reader: Submitted by Jason Joseph
Submitted on September 25, 2024

10/03/2024: Updated the binary file reader to use the bitset library rather than returning a string
10/17/2024: Updated the binary file reader to return 9 bit bytes rather than 8
*/

#pragma once

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

    // Reads a binary file and returns its contents as a vector of bitset<9>
    vector<bitset<9>> bin(const string& fileName) {
        ifstream fileStream(fileName, ios::binary);
        if (!fileStream.is_open()) {
            cerr << "Error opening the file: " << fileName << endl;
            return {};
        }

        vector<bitset<9>> binaryData;  // Store 9-bit chunks
        bitset<9> bitBuffer;           // Accumulate bits for the current 9-bit chunk
        int bitCount = 0;              // Track the number of bits in the buffer
        char byte;

        // Read the file byte by byte
        while (fileStream.read(&byte, 1)) {
            unsigned char byteValue = static_cast<unsigned char>(byte);

            // Extract bits from the byte, one by one
            for (int i = 7; i >= 0; --i) {
                bool bit = (byteValue >> i) & 1;  // Extract the i-th bit

                // Add the bit to the buffer
                bitBuffer[8 - bitCount] = bit;  // Add the bit to the current position

                bitCount++;

                // Once we have 9 bits, push it to the vector
                if (bitCount == 9) {
                    binaryData.push_back(bitBuffer);

                    // Print the extracted 9-bit chunk for debugging
                    cout << "Extracted 9-bit binary: " << bitBuffer << endl;

                    // Reset the buffer and bit count for the next 9-bit chunk
                    bitBuffer.reset();
                    bitCount = 0;
                }
            }
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
}; // End of Class FileReader
