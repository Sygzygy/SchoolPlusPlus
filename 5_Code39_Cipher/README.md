# Assignment: Code 39 Cipher System

## Description
This assignment involves implementing a `Code39Cipher` class system for both encryption and decryption using the Code 39 encoding scheme. The system includes `Code39Decryptor` and `Code39Encryptor` classes for decrypting and encrypting data, respectively, in both binary and hex Code 39 formats. The classes make use of hash tables for efficient encoding and decoding, alongside the `TupleManager` for managing data.

## Features
- **Code 39 Cipher Map**: A cipher map is implemented using hash tables, allowing for both forward and reverse lookups.
- **Binary and Hexadecimal Conversion**: Supports conversion between ASCII, binary, and hexadecimal representations.
- **Tuple Management**: The `TupleManager` is used to manage the relationships between Code 39 representations and ASCII characters.
- **Decryption** (`Code39Decryptor` class):
  - Reads files encoded with Code 39 (either binary or hex format).
  - Converts the encoded data into readable ASCII text.
- **Encryption** (`Code39Encryptor` class):
  - Reads a text file and converts the contents into either binary or hex Code 39 format.
  - Writes the encoded data to an output file.

## File Structure
- `Code39Cryptograph.h`: Contains the class definitions for `Code39Cipher`, `Code39Decryptor`, and `Code39Encryptor`.
- `JosephJason3of9.cpp`: A simple driver program that uses a menu to interact with the Code 39 encryption and decryption system.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile both the header and the driver program.
   ```sh
   g++ JosephJason3of9.cpp -o code39_cipher -I.
   ```
2. **Run the Executable**:
   ```sh
   ./code39_cipher
   ```

## Example Output
- **Decryption**:
  - Reads an encoded file (binary or hex) and prints the corresponding ASCII text.
- **Encryption**:
  - Converts a given text file to Code 39 format and writes the output to a new file (either binary or hex).

## Requirements
- **C++11 or later**: Required for features such as regex and smart pointers.

## Notes
- **Efficient Lookup**: The `Code39Cipher` class uses hash tables to facilitate efficient lookups and translations between ASCII, binary, and hex codes.
- **Encryption and Decryption**: The separation of encryption and decryption into different classes (`Code39Encryptor` and `Code39Decryptor`) allows for modular and reusable code.
- **Menu Interaction**: The main driver (`JosephJason3of9.cpp`) provides a user-friendly menu to interact with the system.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

