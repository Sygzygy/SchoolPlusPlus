/*
 * Huffman Coder by Jason Joseph
 * Created on November 11, 2024
 *
 * This class dynamically traverses the Huffman tree to encode each character into its bit trail
 * and to decode each bit trail back into its corresponding character. This ensures efficient
 * compression and decompression of text files.
 * 
 * encodeToFile: Encodes input text into a binary file using a Huffman tree.
 * decodeFromFile: Decodes a binary file back into text using a Huffman tree.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "Heap.h"

using namespace std;

/* ========================= HuffmanCoder Class ========================= */


class HuffmanCoder {
public:
    void encodeToFile(const string& text, const string& fileName, Node* root) {
        ofstream binaryFile(fileName, ios::binary); // Open the binary file for writing
        if (!binaryFile.is_open()) {
            cerr << "Error opening file for encoding: " << fileName << endl;
            return;
        }

        for (char ch : text) { // Iterate over each character in the input text
            string bitTrail;
            if (findBitTrail(root, ch, bitTrail)) {
                binaryFile << bitTrail; // Write the bit trail to the file
            } else {
                cerr << "Error: Character '" << ch << "' not found in the tree." << endl;
            }
        }

        binaryFile.close(); // Close the binary file after encoding
        cout << "Encoding completed: " << fileName << endl;
    }

    string decodeFromFile(const string& fileName, Node* root) {
        // Lambda for tree traversal based on the current bit
        auto traverseTree = [](Node* currentNode, char bit) -> Node* {
            if (!currentNode) {
                cerr << "Error: Current node is null during traversal." << endl;
                return nullptr;
            }

            auto* branch = dynamic_cast<Branch*>(currentNode); // Ensure it's a branch
            if (!branch) {
                cerr << "Error: Current node is not a branch." << endl;
                return nullptr;
            }

            // Check for valid bit
            if (bit != '0' && bit != '1') {
                cerr << "Error: Invalid bit '" << bit << "' encountered during decoding." << endl;
                return nullptr;
            }

            // Navigate left for '0' and right for '1'
            return (bit == '0') ? branch->getLeft() : branch->getRight();
            };

        ifstream binaryFile(fileName, ios::binary); // Open the binary file for reading
        if (!binaryFile.is_open()) {
            cerr << "Error opening file for decoding: " << fileName << endl;
            return "";
        }

        string decodedText; // Stores the decoded text
        Node* currentNode = root; // Start traversal from the root
        char bit;

        while (binaryFile.get(bit)) { // Read each bit from the binary file
            currentNode = traverseTree(currentNode, bit); // Traverse the tree based on the bit
            if (!currentNode) {
                cerr << "Error: Traversal failed due to an invalid bit or null node." << endl;
                return ""; // Stop decoding on error
            }

            // If a leaf node is reached, append its character to the decoded text
            if (auto* leaf = dynamic_cast<Leaf*>(currentNode)) {
                decodedText += leaf->characterSymbol(); // Add the leaf's symbol to the result
                currentNode = root; // Reset to the root for the next sequence
            }
        }

        binaryFile.close(); // Close the binary file after decoding
        return decodedText; // Return the decoded text
    }

private:
    bool findBitTrail(Node* node, char target, string& trail) {
        if (!node) return false; // Base case: Null node

        // Check if the current node is a leaf and matches the target character
        if (auto* leaf = dynamic_cast<Leaf*>(node)) {
            return leaf->characterSymbol()[0] == target;
        }

        // Traverse the left subtree and append '0' to the trail if the character is found
        trail.push_back('0');
        if (findBitTrail(dynamic_cast<Branch*>(node)->getLeft(), target, trail)) {
            return true;
        }
        trail.pop_back(); // Backtrack if not found in the left subtree

        // Traverse the right subtree and append '1' to the trail if the character is found
        trail.push_back('1');
        if (findBitTrail(dynamic_cast<Branch*>(node)->getRight(), target, trail)) {
            return true;
        }
        trail.pop_back(); // Backtrack if not found in the right subtree

        return false; // Character not found in this subtree
    }
};