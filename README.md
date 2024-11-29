# SchoolPlusPlus

## Overview
This repository contains a series of school assignments that demonstrate various programming concepts in C++, such as template classes, file handling, heap-based tree structures, Huffman coding, and more. Each assignment is organized into its respective numbered folder, with each folder containing the relevant files and a detailed README. This comprehensive README provides an overview of all assignments and links to their individual READMEs.

## Table of Contents
1. [Matrix Class Template](#matrix-class-template)
2. [File Reader](#file-reader)
3. [Regex File Handler](#regex-file-handler)
4. [Morse Decryptor](#morse-decryptor)
5. [Code39 Cipher](#code39-cipher)
6. [Heap Tree Implementation](#heap-tree-implementation)
7. [Smart Pointers](#smart-pointers)
8. [Tuple Manager](#tuple-manager)
9. [Bit Trail](#bit-trail)

## Assignment Descriptions

### 1. Matrix Class Template
**Description**: This assignment involves refactoring a `Matrix` class into a class template to allow it to work with various data types, including a custom `Jason` class. The assignment covers matrix operations such as addition, multiplication, rotation, and element insertion.
- **Files**: `JosephJasonTemplates.cpp`
- [Detailed README](./1.-Matrix-Class-Template/README.md)

### 2. File Reader
**Description**: The `FileReader` class reads and processes different types of files (text, binary, CSV), providing methods for accessing the contents based on the file format.
- **Files**: `FileReader.cpp`
- [Detailed README](./2.-File-Reader/README.md)

### 3. Regex File Handler
**Description**: The `FileHandler` class reads files and performs case-insensitive keyword searches using regular expressions. This assignment highlights text processing capabilities using regex.
- **Files**: `JosephJasonRegEX.cpp`
- [Detailed README](./3.-Regex-File-Handler/README.md)

### 4. Morse Decryptor
**Description**: The `MorseDecryptor` class decodes Morse code from a binary format, using custom hash tables and a tuple manager for efficient encoding and decoding. This assignment demonstrates how to work with Morse code and custom data structures.
- **Files**: `JosephJasonBinary.cpp`
- [Detailed README](./4.-Morse-Decryptor/README.md)

### 5. Code39 Cipher
**Description**: The `Code39Cipher` system implements a method to encrypt and decrypt data using the Code 39 encoding scheme. The assignment focuses on handling data using custom comparators and class design.
- **Files**: `Code39Cryptograph.h`, `JosephJason3of9.cpp`
- [Detailed README](./5.-Code39-Cipher/README.md)

### 6. Heap Tree Implementation
**Description**: This assignment implements a `HeapTree` class using `Branch` and `Leaf` nodes to create a heap-based tree structure. The heap supports various operations such as insertion, removal, and traversal.
- **Files**: `Heap.h`, `JosephJasonExerciseHeapTree.cpp`
- [Detailed README](./6.-Heap-Tree-Implementation/README.md)

### 7. Smart Pointers
**Description**: A new version of the `HeapTree` assignment that replaces all raw pointers with smart pointers (`unique_ptr` and `shared_ptr`). Console colors are added to enhance visualization during heap operations.
- **Files**: `HeapC.cpp`, `ConsoleColor.h`
- [Detailed README](./7.-Smart-Pointers/README.md)

### 8. Tuple Manager
**Description**: This assignment involves testing the `TupleManager` and `HashTable` classes, which store and manage tuples with binary keys, string identifiers, and ASCII characters. The tests use Google Test to verify the functionality of constructors, mutators, equality operators, and more.
- **Files**: `TupleManager.h`, `test.cpp`
- [Detailed README](./8.-Tuple-Manager/README.md)

### 9. Bit Trail
**Description**: An extension of the `HeapTree` assignment, this project implements a Huffman coding system for text compression. Character frequencies are used to create a Huffman tree, which is then used to encode text into binary format and decode it back into text.
- **Files**: `Heap.h`, `HuffmanCoder.h`, `JosephJasonBItTrail.cpp`
- [Detailed README](./9.-Bit-Trail/README.md)

## License
This repository is licensed under the MIT License. See the `LICENSE` file for more information.

## Contact
If you have any questions or need more information, please contact me at [jjoseph@westmont.edu].

