# Assignment: Binary Morse Decryptor

## Description
This assignment involves creating a `MorseCipher` class to convert Morse code stored in binary format into human-readable text. The `MorseDecryptor` class extends `MorseCipher` to manage the decoding of binary Morse code, transcribing it into Morse symbols, and converting it to ASCII characters. The implementation utilizes `TupleManager` and `HashTable` for efficient Morse code lookup, replacing the use of `unordered_map` to achieve a custom storage solution.

## Features
- **MorseCipher Class**: Handles Morse code decryption by managing hash tables for Morse lookup using a modular `TupleManager` and `HashTable` structure.
- **MorseDecryptor Class**: Reads Morse code binary data, transcribes it into Morse symbols, and converts it to ASCII characters for output.
- **TupleManager and HashTable**: Manage Morse code lookup, offering custom storage and efficient access with capabilities for inserting, looking up, and deleting data.
- **FileReader Class**: Reads data from CSV and binary files, supporting Morse code decryption and binary data parsing.

## File Structure
- **JosephJasonBinary.cpp**: Contains the `MorseCipher` and `MorseDecryptor` classes for reading and decrypting Morse code from binary format. Includes a main function for demonstration purposes.
- **TupleManager.h**: Defines the `TupleManager` and `HashTable` classes to encapsulate Morse code data and provide efficient access through a map-like structure.
- **FileReader.cpp**: Provides functions to read from text, CSV, and binary files, supporting both Morse key data and encoded binary data.
- **MorseCode.csv**: A CSV file containing Morse code mappings used by the program for converting Morse symbols to ASCII characters.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile the program.
   ```sh
   g++ JosephJasonBinary.cpp FileReader.cpp -o binary_morse_handler
   ```

2. **Run the Executable**:
   ```sh
   ./binary_morse_handler
   ```

## Example Output
The program reads the binary file "MorseCode.bin" and prints the ASCII translation. Uncomment the specified line in the main function to display the Morse translation alongside the ASCII output.

## Requirements
- **C++11 or Later**: Required for features like lambdas, regex, and modern C++ syntax.

## Notes
- **Data Management**: The `MorseCipher` class uses the `TupleManager` and `HashTable` to provide a more flexible and modular approach to Morse code storage, allowing for efficient access and removal.
- **Error Handling**: The program manages file operations carefully to ensure that files are properly opened and closed, with error messages provided in case of access issues.
- **Binary Parsing**: The `FileReader` class reads binary files into `bitset` objects, supporting Morse code decoding with direct bit manipulation.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

