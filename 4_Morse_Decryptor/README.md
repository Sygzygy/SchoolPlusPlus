# Assignment: Regex File Handler

## Description
This assignment involves creating a `FileHandler` class that reads from a file and searches for lines containing a specified keyword, regardless of the casing. The class uses regular expressions to perform case-insensitive searches, making it a practical example of using regex for text processing in C++.

## Features
- **FileHandler Class**: Manages file access and keyword searching with efficient stream handling.
- **Case-Insensitive Keyword Search** (`findKeyword` function): Utilizes regex with the `icase` flag to perform case-insensitive searches and return matching lines from the file.
- **File Management**: The `FileHandler` class properly handles file opening and closing to ensure resources are released.

## File Structure
- `JosephJasonRegEX.cpp`: Contains the `FileHandler` class definition, along with a `main` function demonstrating how to use the keyword search on a sample file.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile the program.
   ```sh
   g++ JosephJasonRegEX.cpp -o regex_file_handler
   ```
2. **Run the Executable**:
   ```sh
   ./regex_file_handler
   ```

## Example Output
- **Keyword Search**:
  - Searches for the keyword in the file, irrespective of case, and prints each line containing the keyword.
  - For example, when searching for "if", all lines containing "if" are printed to the console, regardless of their case.

## Requirements
- **C++11 or later**: Required for features like regex and modern C++ syntax.

## Notes
- **Regular Expressions**: The `findKeyword` function makes use of the `std::regex` library, with the `\b` word boundary anchor to match whole word occurrences only. The `icase` flag is used to ensure that the search is case-insensitive.
- **Error Handling**: The class checks for potential issues when opening files and provides error messages if files cannot be accessed.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

