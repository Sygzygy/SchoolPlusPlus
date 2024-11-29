# Assignment: File Reader Class

## Description
This assignment involves implementing a `FileReader` class that can read and process various types of files, such as text, binary, and CSV files. The `FileReader` class is designed to provide different ways of accessing file data, depending on the format, while utilizing C++ features like file streams and regex. The assignment demonstrates key aspects of file handling, parsing, and error management in C++.

## Features
- **File Size Retrieval**: Provides a method to get the size of a file in bytes.
- **Text File Reading** (`txt` function): Reads a text file and returns the content line-by-line as a vector of strings.
- **Binary File Reading** (`bin` function): Reads binary data from a file and returns it as a string for further processing.
- **CSV File Parsing** (`csv` function): Uses regex to parse CSV files, returning the data as a 2D vector of strings.
- **Destructor**: Ensures the file stream is properly closed when the `FileReader` object is destroyed.

## File Structure
- `JosephJasonFIleReader.cpp`: Contains the definition of the `FileReader` class and a `main` function that demonstrates the usage of all file reading methods.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile the program.
   ```sh
   g++ JosephJasonFIleReader.cpp -o file_reader
   ```
2. **Run the Executable**:
   ```sh
   ./file_reader
   ```

## Example Output
- **File Size Retrieval**:
  - Displays the size of different files (e.g., text, binary, CSV) in bytes.
- **Text File Data**:
  - Reads and prints each line from a specified text file.
- **Binary File Data**:
  - Reads binary content and displays its hexadecimal representation.
- **CSV File Data**:
  - Parses CSV content and displays it row-by-row.

## Requirements
- **C++11 or later**: Required for features such as regex and modern C++ syntax.

## Notes
- **Error Handling**: The `FileReader` class includes error messages for cases where files cannot be opened, helping users quickly identify issues with file paths or permissions.
- **File Stream Management**: Proper file stream management ensures resources are released when operations are complete, preventing potential file lock issues.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

