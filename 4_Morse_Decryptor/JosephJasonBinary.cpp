/*
Exercise Binary: Submitted by Jason Joseph
Submitted on October 4, 2024
Updated on October 31, 2024

This program decodes Morse code stored in binary format. It uses two unordered_maps for efficient
lookup of Morse symbols, starting with a dot (.) or a dash (-). The MorseDecryptor class
handles reading the binary data, transcribing it into Morse code Binary String, and converting it to ASCII characters.
Main function prints the ASCII translation, if you desire to see the morse translation, uncomment the specified line in the function.

UPDATE: Implemented a tuple manager and hashtable class to remove the use of unordered_map
*/

#include <unordered_map>
#include "FileReader.cpp"
#include "TupleManager.h"

using namespace std;

// Morse Cipher Class Definition
class MorseCipher {
public:
	// MorseCipher Constructor, uses lambda to create two hash tables for searching
	MorseCipher() {
		try {
			// Lambda to convert Morse code to binary ("." to "10" and "-" to "01")
			auto morseToBinary = [](const string& morseCode) -> string {
				string binary;
				for (char c : morseCode) {
					if (c == '.') {
						binary += "10";  // Dot is '10'
					}
					else if (c == '-') {
						binary += "01";  // Dash is '01'
					}
				}
				return binary;
				};

			FileReader fileReader;
			vector<vector<string>> morseKey = fileReader.csv("MorseCode.csv"); // CSV File read here

			// Lambda for processing a valid row
			auto processRow = [&](const vector<string>& row) {
				if (row.size() == 2) {
					// Extract letter and Morse code
					char letter = row[0][0];
					string morseCode = row[1];
					string morseBinary = morseToBinary(morseCode);

					// Debugging output
					/*cout << "Letter: " << letter
						<< ", Morse: " << morseCode
						<< ", Binary: " << morseBinary << endl;*/

					// Insert into the appropriate hash table based on Morse code's first character
					if (morseCode[0] == '.') {
						dotFirstMap.insert(TupleManager<string, string, char>{morseBinary, morseCode, letter});
					}
					else if (morseCode[0] == '-') {
						dashFirstMap.insert(TupleManager<string, string, char>{morseBinary, morseCode, letter});
					}
				}
				else {
					// Skip rows without exactly two columns
					cerr << "Skipping invalid row: does not contain exactly two columns" << endl;
				}
				};

			// Process each row in the CSV file
			for (const vector<string>& row : morseKey) {
				processRow(row);
			}
		}
		catch (const exception& error) {
			cerr << "Error initializing MorseCipher: " << error.what() << endl;
		}
	}

	virtual ~MorseCipher() = default;

protected:
	// Hash tables now use std::string for the binary key, std::string for Morse, and char for letter
	HashTable<string, string, char> dotFirstMap;
	HashTable<string, string, char> dashFirstMap;

	// Helper function to find the letter corresponding to a binary string
	char findLetterFromBinary(const string& binaryString) {
		auto& mapToSearch = (binaryString[0] == '0') ? dashFirstMap : dotFirstMap;
		auto it = mapToSearch.findByKey(binaryString);

		return (it != mapToSearch.end()) ? it->getASCIIValue() : '?';
	}

	// Helper function to find the Morse code corresponding to a binary string
	string findMorseFromBinary(const string& binaryString) {
		auto& mapToSearch = (binaryString[0] == '0') ? dashFirstMap : dotFirstMap;
		auto it = mapToSearch.findByKey(binaryString);

		return (it != mapToSearch.end()) ? it->getString() : "?";
	}
}; // end of class MorseCipher

/*******************************************************************************************************/

// MorseDecryptor class definition
class MorseDecryptor : public MorseCipher {
public:
	// MorseDecryptor Constructor: Reads binary data from the binary file
	MorseDecryptor() : MorseCipher() {
		binaryData = fileReader.bin("MorseCode.bin"); // Binary file read here
	}

	// Parse a bit pair from the byte and return the corresponding Morse code symbol
	string parseBitPair(const bitset<8>& byte, int i) {
		bool bit1 = byte[i];     // MSB
		bool bit2 = byte[i - 1]; // LSB

		// Check bit pairs and return corresponding Morse code symbol
		if (bit1 == 0 && bit2 == 0) {
			return " ";  // Letter space
		}
		else if (bit1 == 1 && bit2 == 1) {
			return " / ";  // Word space
		}
		else if (bit1 == 0 && bit2 == 1) {
			return "01";  // Dash
		}
		else if (bit1 == 1 && bit2 == 0) {
			return "10";  // Dot
		}
		return "";  // In case of invalid bit pair
	}

	// Transcribe the binary data into Morse symbols and store in binaryString
	void transcribeData() {
		binaryString.clear();  // Clear any previous data

		for (bitset<8> byte : binaryData) {
			for (int i = 7; i >= 1; i -= 2) {
				string morseSymbol = parseBitPair(byte, i);
				binaryString.push_back(morseSymbol);  // Append Morse code symbol
			}
		}
	}

	// Convert the transcribed binary data to ASCII letters
	vector<char> convertBinaryToASCII() {
		transcribeData(); // transcribes the data for reading
		vector<char> decryptedString;
		string currentBinary;

		for (const string& binarySegment : binaryString) {
			if (binarySegment == " ") {
				// End of a letter, find the corresponding ASCII character
				if (!currentBinary.empty()) {
					char letter = findLetterFromBinary(currentBinary);
					decryptedString.push_back(letter);
					currentBinary.clear();  // Reset for the next letter
				}
			}
			else if (binarySegment == " / ") {
				// Word space
				if (!currentBinary.empty()) {
					char letter = findLetterFromBinary(currentBinary);
					decryptedString.push_back(letter);
					currentBinary.clear();
				}
				decryptedString.push_back(' ');  // Add space between words
			}
			else {
				currentBinary += binarySegment;  // Accumulate Morse code
			}
		}

		// Process the final letter (if any)
		if (!currentBinary.empty()) {
			char letter = findLetterFromBinary(currentBinary);
			decryptedString.push_back(letter);
		}

		return decryptedString;
	}

	vector<string> convertBinaryToMorse() {
		vector<string> decryptedMorse;
		string currentBinary;

		for (const string& binarySegment : binaryString) {
			if (binarySegment == " ") {
				// End of a letter
				if (!currentBinary.empty()) {
					string morseCode = findMorseFromBinary(currentBinary);
					decryptedMorse.push_back(morseCode);
					currentBinary.clear();
				}
				decryptedMorse.push_back("  "); // Letter seperator
			}
			else if (binarySegment == " / ") {
				// Word space
				if (!currentBinary.empty()) {
					string morseCode = findMorseFromBinary(currentBinary);
					decryptedMorse.push_back(morseCode);
					currentBinary.clear();
				}
				decryptedMorse.push_back(" / ");  // Word separator
			}
			else {
				currentBinary += binarySegment;  // Accumulate Morse code
			}
		}

		// Process the final letter (if any)
		if (!currentBinary.empty()) {
			string morseCode = findMorseFromBinary(currentBinary);
			decryptedMorse.push_back(morseCode);
		}

		return decryptedMorse;
	}

	// Display both Morse and ASCII translations
	// If morseTranslationEnabled is true, Morse translation will be displayed.
	// By default, only ASCII translation is shown.
	void displayTranslation(bool morseTranslationEnabled = false) {
		vector<char> ASCIITranslation = convertBinaryToASCII();

		if (morseTranslationEnabled) {
			vector<string> morseTranslation = convertBinaryToMorse();

			// Display both Morse and ASCII translations
			cout << "Morse Translation: \n\n";
			for (string line : morseTranslation) {
				cout << line;
			}
			cout << endl << endl;
		}

		// Display ASCII Translation regardless of the toggle
		cout << "ASCII Translation: \n\n ";
		for (char letter : ASCIITranslation) {
			cout << letter;
		}
		cout << endl;
	}

private:
	FileReader fileReader;
	vector<bitset<8>> binaryData;
	vector<string> binaryString;

}; // End of class MorseDecryptor

/*******************************************************************************************************/

int main() {
	MorseDecryptor binaryFile;

	// Only ASCII translation will be shown (default behavior)
	binaryFile.displayTranslation();

	// Uncomment the following line to show both Morse and ASCII translations:
	//binaryFile.displayTranslation(true);

	return 0;
}
