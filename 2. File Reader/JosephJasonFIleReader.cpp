/*
Excercise File Reader: Submitted by Jason Joseph
Submitted on September 25, 2024

*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>

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

    // Returns the file data in Binary as a string
    string bin(const string& fileName) {
        fileStream.open(fileName, ios::binary);
        if (!fileStream.is_open()) {
            cerr << "Error opening the file: " << fileName << endl;
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

int main() {
    FileReader fileReader;
    
    // Test the file size function
    int textFileSize = fileReader.size("MorseMap.txt"); // Edit this line for to test
    cout << "Size of Text File: " << textFileSize << " bytes" << endl;

    int binaryFileSize = fileReader.size("CompressEx.bin"); // Edit this line for to test
    cout << "Size of Binary File: " << binaryFileSize << " bytes" << endl;

    int csvFileSize = fileReader.size("Frequencies.csv"); // Edit this line for to test
    cout << "Size of CSV File: " << csvFileSize << " bytes" << endl;

    /******************************************************************************************/

    // File Tests
    // Test the text file reading functionality
    vector<string> textData = fileReader.txt("MorseMap.txt");  // Edit this line for to test
    cout << "Text File Data:" << endl;
    for (const string& line : textData) {
        cout << line << endl;
    }
    cout << endl;

    // Test the binary file reading functionality
    string binaryData = fileReader.bin("CompressEx.bin"); // Edit this line for to test
    cout << "Binary File Data (Hex Representation):" << endl;
    for (unsigned char c : binaryData) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(c) << " ";
    }
    cout << endl << endl;

    // Test the CSV file reading functionality
    vector<vector<string>> csvData = fileReader.csv("Frequencies.csv"); // Edit this line for to test
    cout << "CSV File Data:" << endl;
    for (const vector<string> row : csvData) {
        for (const string& field : row) {
            cout << field << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
