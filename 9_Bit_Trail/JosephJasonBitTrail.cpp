/*
 * Huffman Bit Trails by Jason Joseph
 * Created on November 12, 2024
 *
 * This program reads character frequencies from a CSV file to construct a Huffman tree, dynamically
 * generates bit trails by traversing said tree, and encodes a user-provided text file into a
 * binary file. The program also decodes the binary file back into text by walking the Huffman
 * tree branches. Results are displayed on the console and saved to output files.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <regex>
#include "Heap.h"
#include "FileReader.h"
#include "HuffmanCoder.h"

using namespace std;

// Data class definition
class Data {
public:
    Data(char ascii, double freq) : asciiChar(ascii), frequency(freq), bitTrail("") {}

    char getAsciiChar() const { return asciiChar; }
    double getFrequency() const { return frequency; }
    string getBitTrail() const { return bitTrail; }
    void setBitTrail(const string& trail) { bitTrail = trail; }

private:
    char asciiChar;
    double frequency;
    string bitTrail;
};

// Recursive function to generate bit trails
void generateBitTrails(Node* currentNode, const string& trail, vector<Data>& dataEntries) {
    if (auto* leafNode = dynamic_cast<Leaf*>(currentNode)) {
        char symbol = leafNode->characterSymbol()[0];
        string bitTrail = trail;

        for (auto& data : dataEntries) {
            if (data.getAsciiChar() == symbol) {
                data.setBitTrail(bitTrail); // Update Data with the bit trail
                break;
            }
        }
        return;
    }

    if (auto* branchNode = dynamic_cast<Branch*>(currentNode)) {
        generateBitTrails(branchNode->getLeft(), trail + "0", dataEntries);
        generateBitTrails(branchNode->getRight(), trail + "1", dataEntries);
    }
}

int main() {
    // Read Frequencies.csv using FileReader
    FileReader fileReader;
    vector<Data> dataEntries;

    // Preprocessing Lambda to make sure there are only valid characters using regex
    auto preprocessText = [](const string& input) -> string {
        regex validCharRegex("[\\x20-\\x7E]+"); // Matches printable ASCII characters
        smatch matches;

        string sanitizedText = "";
        string::const_iterator searchStart(input.cbegin());
        while (regex_search(searchStart, input.cend(), matches, validCharRegex)) {
            sanitizedText += matches.str(); // Append valid characters
            searchStart = matches.suffix().first;
        }

        return sanitizedText;
        };

    auto csvData = fileReader.csv("Frequencies.csv"); // Read the CSV file
    for (const auto& row : csvData) {
        if (row.size() < 2 || row[0] == "ascii") continue; // Skip invalid rows and header
        char asciiChar = static_cast<char>(stoi(row[0]));  // Convert ASCII value
        double frequency = stod(row[1]);                  // Convert frequency
        dataEntries.emplace_back(asciiChar, frequency);   // Store data in the vector
    }

    // Create HeapTree from Data
    vector<unique_ptr<Node>> heapNodes; // Vector to hold nodes for the heap
    for (const auto& data : dataEntries) {
        heapNodes.push_back(make_unique<Leaf>(string(1, data.getAsciiChar()), data.getFrequency()));
    }

    HeapTree<Node> heapTree(move(heapNodes)); // Initialize the heap tree

    // Combine nodes into a single Huffman tree
    while (heapTree.heapSize() > 1) {
        auto left = move(heapTree.front());
        heapTree.pop();
        auto right = move(heapTree.front());
        heapTree.pop();

        heapTree.pushBack(make_unique<Branch>(move(left), move(right))); // Combine nodes into a new branch
    }

    // Generate Bit Trails dynamically
    if (!heapTree.isEmpty()) {
        generateBitTrails(heapTree.front().get(), "", dataEntries);
    }

    // Prompt user for input file name
    string inputFileName;
    cout << "Enter the input file name: ";
    cin >> inputFileName;

    string encodedFileName = "encoded.bin";             // File to store the encoded binary data
    string decodedFileName = "decoded.txt";             // File to store the decoded text

    vector<string> fileContents = fileReader.txt(inputFileName); // Read the input file as text
    if (fileContents.empty()) {
        cerr << "Error: Unable to read input file or file is empty." << endl;
        return 1;
    }

    string textToEncode = preprocessText(fileContents[0]); // Preprocess the text

    HuffmanCoder coder;                                    // Use HuffmanCoder for encoding and decoding
    coder.encodeToFile(textToEncode, encodedFileName, heapTree.front().get()); // Encode the text into the binary file

    string decodedText = coder.decodeFromFile(encodedFileName, heapTree.front().get()); // Decode the binary file back into text

    // Write decoded text to a file
    ofstream outputFile(decodedFileName);
    if (outputFile.is_open()) {
        outputFile << decodedText;
        outputFile.close();
        cout << "Decoded text written to: " << decodedFileName << endl;
    }
    else {
        cerr << "Error writing decoded text to file: " << decodedFileName << endl;
    }

    // Output decoded text to the console
    cout << "Decoded Text: " << decodedText << endl;

    return 0;
}
