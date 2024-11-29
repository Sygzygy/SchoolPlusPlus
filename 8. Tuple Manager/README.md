# Assignment: TupleManager and HashTable Testing

## Description
This assignment involves testing the functionality of two custom classes, `TupleManager` and `HashTable`. The `TupleManager` class is designed to encapsulate a tuple with three fields: a binary key, a string identifier, and an ASCII character. The `HashTable` class provides a vector-based map-like structure for storing `TupleManager` instances. The project focuses on testing the classes' constructors, accessors, mutators, and operations using Google Test.

## Features
- **TupleManager Class**:
  - Manages a tuple consisting of a binary key, string identifier, and ASCII character.
  - Provides accessor methods (`getBinaryKey`, `getString`, `getASCIIValue`) and mutator methods (`setBinaryKey`, `setString`, `setASCIIValue`) for each field.
  - Supports equality comparison (`operator==`) and a custom `swap` method for efficient tuple management.
- **HashTable Class**:
  - Implements a vector-based map-like structure to store `TupleManager` instances.
  - Supports insertion (`insert`), access (`operator[]`, `operator()`), and removal (`eraseByKey`, `eraseByString`) by both binary key and string identifier.
  - Provides methods for finding elements (`findByKey`, `findByString`) and handling missing keys through controlled exception handling.

## File Structure
- `TupleManager.h`: Contains the definitions for both `TupleManager` and `HashTable` classes.
- `test.cpp`: Contains unit tests for both `TupleManager` and `HashTable` classes using Google Test.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile the header file and test file. Ensure Google Test is set up in your environment.
   ```sh
   g++ test.cpp -o tuple_manager_tests -lgtest -lgtest_main -pthread
   ```
2. **Run the Tests**:
   ```sh
   ./tuple_manager_tests
   ```

## Example Tests
- **TupleManager Tests**:
  - **Constructor and Accessors**: Verify that the `TupleManager` constructor correctly initializes fields and that accessors retrieve the expected values.
  - **Mutators**: Verify that fields can be modified using the appropriate mutator methods.
  - **Equality Operator**: Check if two `TupleManager` instances are correctly determined to be equal or unequal.
  - **Swap Method**: Confirm that the `swap` function works as intended.
- **HashTable Tests**:
  - **Insert and Access**: Verify that elements can be inserted and accessed using both the binary key and string identifier.
  - **Access Non-Existent Key**: Confirm that attempting to access a non-existent key throws an `std::out_of_range` exception.
  - **Erase Elements**: Verify that elements can be removed by both binary key and string identifier, and that other elements remain unaffected.
  - **Find Elements**: Test the `findByKey` and `findByString` methods to confirm correct element lookup.

## Requirements
- **C++11 or later**: Required for features like tuples and lambda functions.
- **Google Test Framework**: Used for unit testing.

## Notes
- **Modular Data Handling**: The `TupleManager` and `HashTable` classes provide a flexible and efficient way to store and manage tuples, suitable for map-like behavior with custom data.
- **Testing with Google Test**: The use of Google Test ensures comprehensive verification of all features and functions, helping to identify potential issues early in the development process.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

