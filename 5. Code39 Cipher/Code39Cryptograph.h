/*
* Code 39 Cryptograph by Jason Joseph
* Created on October 14, 2024
* Updated on October 31, 2024
* 
* Code39Cipher: Implements a map that links binary and hex code representations of code 39 to their corresponding
* ASCII values. The tuple class is used to allow for reverse lookups if necessary. This serves as the base class for both
* encryption and decryption, containing the core methods like searching and translating.
* 
* Code39Decryptor: This class is responsible for decrypting files encoded with code 39, in either binary or hex format.
* Inheriting from Code39Cipher, this class adds functions for reading processing binary or hex text files to retrieve 
* their ASCII values. Doing so from the parent class's cipher map.
* 
* Code39Encryptor: This class provides the functionality to encrypt text files into binary or hex code 39 format. This
* does so from the cipher map provided from its parent, converting input text from a file into its appropriate code 39
* binary or hex values and writes the output to a file. 
* 
* Updated the classes to use the hashtable and tuplemanager classes described in its header file, removing cases of vector<tuple>.
* Changed some parts of code to use regex rather than looping through strings.
*/

#pragma once
#include <sstream>
#include <tuple>
#include <vector>
#include <bitset>
#include <string>
#include <iostream>
#include <optional>
#include <regex>
#include <fstream>
#include "FileReader.h"
#include "TupleManager.h"

using namespace std;

/* *********************************************************************************************** */
/*                                     Code39Cipher Class                                          */
/*                                                                                                 */
/*   Using tuples, creates a cipher map of Code39 that allows for reverse lookup if necessary      */
/* *********************************************************************************************** */

class Code39Cipher {

public:
    Code39Cipher() : code39Cipher() {
        vector<vector<string>> original39Data = openFile();
        char code39ASCII;

        // Parse the file data and create the cipher map
        for (const vector<string>& row : original39Data) {
            // Handle special case for spaces ("SP" represents a space)
            code39ASCII = (row[0] == "SP") ? ' ' : row[0][0];
            string code39String = row[1];

            try {
                // Convert the 'w' and 'n' pattern to binary and store it with the ASCII character
                auto code39binary = translateToBinary(code39String, code39ASCII);
                code39Cipher.insert(code39binary);

                // Debugging line for hashtable
                //cout << "binary: " << get<0>(code39binary) << " | hexCode:  " << get<1>(code39binary) << " | ASCII: " << get<2>(code39binary) << endl;
            }
            catch (const out_of_range& e) {
                cerr << "Error: " << e.what() << " for string: " << code39String << endl;
            }
        }
    }

    virtual ~Code39Cipher() = default;

protected:
    // Shared shorthand type definition for the tuple used
    using CipherTuple = TupleManager<bitset<9>, string, char>;

    // Instance of the HashTable, replacing the vector-based structure
    HashTable<bitset<9>, string, char> code39Cipher;

    // Convert the binary Code39 string into its decimal string equivalent (for lookup purposes)
    string bitsToHexConversion(const bitset<9>& binary) {
        bitset<3> hundreds((binary >> 6).to_ulong());  // Extract the 3 MSB bits (hundreds place)
        bitset<3> tens((binary >> 3).to_ulong() & 0b111);  // Extract the middle 3 bits (tens place)
        bitset<3> ones(binary.to_ulong() & 0b111);  // Extract the 3 LSB bits (ones place)

        // Combine the values from each section to get the full hexCode value
        string hexCode = to_string(hundreds.to_ulong()) + to_string(tens.to_ulong()) + to_string(ones.to_ulong());
        return hexCode;
    }

    // Find the corresponding ASCII character for a given binary value
    optional<char> findByBinary(const bitset<9>& binary) const {
        auto it = code39Cipher.findByKey(binary);
        if (it != code39Cipher.end()) {
            return it->getASCIIValue();
        }
        return nullopt;
    }

    // Find the corresponding ASCII character for a given hex value
    optional<char> findByHex(const string& hexString) const {
        auto it = code39Cipher.findByString(hexString);
        if (it != code39Cipher.end()) {
            return it->getASCIIValue();
        }
        return nullopt;
    }

    // Find the corresponding binary and decimal tuple for a given ASCII character
    optional<CipherTuple> findByASCII(char ascii) const {
        for (const auto& entry : code39Cipher) {
            if (entry.getASCIIValue() == ascii) {
                return entry;
            }
        }
        return nullopt;
    }

private:
    // Open the CSV file containing the Code39 data and return it as a 2D vector of strings
    vector<vector<string>> openFile() {
        FileReader filereader;
        return filereader.csv("3of9.csv");  // Read the file using FileReader
    }

    // Translate a string of 'w' and 'n' characters into a binary bitset and its corresponding decimal key
    TupleManager<bitset<9>, string, char> translateToBinary(const string& row, char code39ASCII) {
        bitset<9> binary;
        size_t bitsetIndex = 8;
        size_t count = 0;
        binary.reset();

        // Translate the 'w' and 'n' characters into binary
        for (size_t i = 0; i < row.size(); i++) {
            if (row.at(i) != ' ') {
                if (row.at(i) == 'w') {
                    binary.set(bitsetIndex);
                }
                bitsetIndex--;
                count++;
            }
        }

        if (count != 9) {
            cerr << "Error: Invalid binary string length in row: " << row << endl;
        }

        string decimalKey = bitsToHexConversion(binary);  // Convert binary to decimal

        // Return a TupleManager instance with the binary, decimalKey, and ASCII character
        return TupleManager<bitset<9>, string, char>{binary, decimalKey, code39ASCII};
    }

};  // End of Code39Cipher class


/* *********************************************************************************************** */
/*                                      Code39Decryptor Class                                      */
/*                                                                                                 */
/*    Decrypts a text file containing either byte 9 binary or hex codes using a tuple map created  */
/*                                    by the Code39Cipher Class                                    */        
/* *********************************************************************************************** */

class Code39Decryptor : public Code39Cipher {
public:
    Code39Decryptor(const string fileName, bool hexTranslation = false)
        : Code39Cipher(), translation(make_unique<tuple<string, vector<string>>>()) {
        get<0>(*translation).clear();  // Clear ASCII translation
        get<1>(*translation).clear();  // Clear hex translation

        // Decide whether to decrypt binary or hex files
        if (!hexTranslation) {
            binaryData = fileReader.txt(fileName);  // Read binary file
            parseBinaryData(translation.get());  // Parse and decrypt binary data
            cout << get<0>(*translation) << endl << endl;
        }
        else {
            hexData = fileReader.txt(fileName);  // Read hex file
            parseHexData(translation.get());  // Parse and decrypt hex data
            cout << get<0>(*translation) << endl << endl;
        }
    }

    ~Code39Decryptor() = default;

private:
    using Translation = tuple<string, vector<string>>;  // Tuple replacing the struct

    unique_ptr<Translation> translation;  // Tuple to manage translation data
    FileReader fileReader;
    vector<string> binaryData;
    vector<string> hexData;

    // Parse and decrypt binary data into ASCII

    void parseBinaryData(Translation* translation) {
        vector<bitset<9>> binary;
        regex bitPattern("[01]");  // Match only '1' and '0'

        for (const string& line : binaryData) {
            string cleanedBits;
            for (auto it = sregex_iterator(line.begin(), line.end(), bitPattern);
                it != sregex_iterator(); ++it) {
                cleanedBits += it->str();  // Append matched bits to cleanedBits
            }

            while (cleanedBits.size() >= 9) {
                bitset<9> byte(cleanedBits.substr(0, 9));
                binary.push_back(byte);
                cleanedBits.erase(0, 9);  // Remove processed bits
            }
        }

        // Decrypt the binary values into ASCII
        for (const bitset<9>&bytes : binary) {
            try {
                string hexCode = bitsToHexConversion(bytes);
                optional<char> ASCIIValue = findByBinary(bytes);

                if (ASCIIValue.has_value()) {
                    get<0>(*translation).push_back(ASCIIValue.value());
                    get<1>(*translation).push_back(hexCode);
                }
                else {
                    cerr << "Binary key not found for: " << bytes.to_string() << endl;
                }
            }
            catch (const runtime_error& e) {
                cerr << "Key not found: " << e.what() << endl;
            }
        }
    }

    // Parse and decrypt hex data into ASCII
    void parseHexData(Translation* translation) {
        regex hexPattern("\\d{3}");  // Match exactly three digits

        for (const string& line : hexData) {
            vector<string> hex3Keys;

            for (auto it = sregex_iterator(line.begin(), line.end(), hexPattern);
                it != sregex_iterator(); ++it) {
                hex3Keys.push_back(it->str());  // Store each 3-digit match
            }

            for (const string& hexCode : hex3Keys) {
                optional<char> ASCIIValue = findByHex(hexCode);

                if (ASCIIValue.has_value()) {
                    get<0>(*translation).push_back(ASCIIValue.value());
                    get<1>(*translation).push_back(hexCode);
                }
                else {
                    cerr << "Key not found for hex string: " << hexCode << endl;
                }
            }
        }
    }

};  // End of Code39Decryptor class


/* ************************************************************************************************ */
/*                                      Code39Encryptor Class                                       */
/*                                                                                                  */
/* Allows for encryption of a user-submitted file into either Code 39 Binary or equivalent hex code */
/* ************************************************************************************************ */

class Code39Encryptor : public Code39Cipher {
public:
    Code39Encryptor(string fileName, bool isHex = false)
        : Code39Cipher(), code39Translation(make_unique<HashTable<bitset<9>, string, char>>()) {
        code39Translation->clear();
        textFile = fileReader.txt(fileName);  // Read the text file

        parseTextData(code39Translation.get());  // Parse and encrypt text data

        // Write output as either text (hex) or binary
        if (isHex) {
            writeHexTextFile("outputHex.txt", *code39Translation);  // Write hex file
        }
        else {
            writeBinaryTextFile("outputBinary.txt", *code39Translation);  // Write binary file
        }
    }

    // Parse and encrypt the text file into binary/decimal tuples
    void parseTextData(HashTable<bitset<9>, string, char>* encryption) {
        for (const string& line : textFile) {
            for (const char& ASCIIchar : line) {
                try {
                    optional<CipherTuple> result = findByASCII(toupper(ASCIIchar));  // Find the corresponding tuple

                    if (result.has_value()) {
                        encryption->insert(result.value());  // Store the tuple in the encryption HashTable
                    }
                    else {
                        cerr << "Value not found for Character: " << ASCIIchar << endl;
                    }
                }
                catch (const runtime_error& e) {
                    cerr << "Value not found: " << e.what() << endl;
                }
            }
        }
    }

private:
    FileReader fileReader;
    vector<string> textFile;
    unique_ptr<HashTable<bitset<9>, string, char>> code39Translation;

    // Write the encrypted data as a text file with 3-digit hex numbers (with spaces between them)
    void writeHexTextFile(const string& filename, const HashTable<bitset<9>, string, char>& data) {
        ofstream outFile(filename);

        if (outFile.is_open()) {
            for (const CipherTuple& tuple : data) {
                string decimalString = get<1>(tuple);  // Get the decimal value (3 digits)

                outFile << setw(3) << setfill('0') << decimalString << ' ';
            }

            outFile << endl;  // End with a newline
            outFile.close();
            cout << "Hex data written to outputHex file successfully!" << endl << endl;
        }
        else {
            cerr << "Error: Could not open the file for writing!" << endl;
        }
    }

    // Write the encrypted data as a binary string text file
    void writeBinaryTextFile(const string& filename, const HashTable<bitset<9>, string, char>& data) {
        ofstream outFile(filename);  // Open the file in text mode (default mode)

        if (outFile.is_open()) {
            for (const CipherTuple& tuple : data) {
                const bitset<9>& binaryData = get<0>(tuple);  // Get the binary data (bitset<9>)

                // Write the binary string (e.g., "110101101") to the file
                outFile << binaryData.to_string() << ' ';  // Write the string followed by a space
            }

            outFile << endl;  // End with a newline
            outFile.close();  // Close the file after writing all data
            cout << "Binary string data written to outputBinary file successfully!" << endl << endl;
        }
        else {
            cerr << "Error: Could not open the file for writing!" << endl;
        }
    }
};  // End of Code39Encryptor class