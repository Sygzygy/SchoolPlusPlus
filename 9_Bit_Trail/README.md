# Assignment: Huffman Bit Trails Encoding and Decoding

## Overview
This assignment is an extension of the previous `HeapTree` assignment, focusing on implementing a Huffman coding system to encode and decode text using character frequencies. The system reads character frequencies from a CSV file, constructs a Huffman tree using the `HeapTree` structure, dynamically generates bit trails by traversing the tree, and then encodes a user-provided text file into a binary file. It also decodes the binary file back into text using the Huffman tree. The project demonstrates the application of heap-based trees, file handling, and bit-level operations in data compression.

## Features
- **Data Class**
  - Represents each character with its ASCII value, frequency, and corresponding bit trail.
  - Provides methods to get and set the bit trail for each character.
- **HeapTree Structure** (`Heap.h`)
  - Implements the Huffman tree using a heap-based structure (`HeapTree`) with `Branch` and `Leaf` nodes.
  - Combines nodes iteratively to build the Huffman tree.
- **HuffmanCoder Class** (`HuffmanCoder.h`)
  - **encodeToFile**: Encodes input text into a binary file using the Huffman tree.
  - **decodeFromFile**: Decodes a binary file back into text using the Huffman tree.
  - Uses recursive traversal to find the bit trail for each character during encoding.
- **Bit Trail Generation**
  - The `generateBitTrails` function dynamically traverses the Huffman tree to generate bit trails for each character.
  - Uses recursion to ensure all characters are assigned their correct bit sequences based on the tree structure.
- **File Handling** (`FileReader` and Standard C++ File I/O)
  - Reads character frequency data from a CSV file and text from user-specified input files.
  - Writes encoded binary data to a file and decodes it back into text.
- **Text Preprocessing**
  - Uses regular expressions to sanitize input, allowing only valid printable ASCII characters.

## File Structure
- **`Heap.h`**: Contains the implementation of the heap-based tree used for constructing the Huffman tree.
- **`HuffmanCoder.h`**: Defines the `HuffmanCoder` class, responsible for encoding and decoding text using a Huffman tree.
- **`JosephJasonBItTrail.cpp`**: The main driver program that integrates reading character frequencies, constructing the Huffman tree, generating bit trails, encoding, and decoding text.

## How to Run
1. **Compile the Code**
   - Use a C++ compiler like `g++` to compile the source files:
     ```sh
     g++ JosephJasonBItTrail.cpp -o huffman_bit_trails -I.
     ```
2. **Run the Executable**
   - Execute the program:
     ```sh
     ./huffman_bit_trails
     ```
3. **Provide Input**
   - The program will prompt you for an input file name containing the text to be encoded.
   - Ensure that a CSV file named `Frequencies.csv` containing character frequencies is available in the same directory.

## Example Output
- **Huffman Tree Construction**
  - Nodes are created from character frequencies, and branches are combined to form the final Huffman tree.
- **Bit Trail Generation**
  - Each character is assigned a unique bit trail based on the tree structure, which is used during encoding.
- **Encoded and Decoded Output**
  - Encoded binary data is saved to `encoded.bin`.
  - Decoded text is saved to `decoded.txt` and also displayed on the console.

## Requirements
- **C++11 or later**: Required for features like smart pointers, lambda expressions, and other modern C++ syntax.

## Additional Notes
- **Heap-Based Huffman Tree**: The Huffman tree is implemented using a min-heap to ensure efficient combination of nodes based on character frequencies.
- **Recursive Bit Trail Generation**: Recursion is used to navigate the Huffman tree and generate bit trails for each character.
- **Error Handling**: The program includes error checks for file operations, ensuring that users are notified of issues such as missing files or invalid input.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

