# Assignment: Matrix Class Template

## Description
This assignment involves refactoring a class called `Matrix` into a class template, enabling it to work with various data types. Additionally, a custom class `Jason` was implemented to test the generic behavior of the `Matrix` template. The project illustrates fundamental concepts of templates, operator overloading, and generic programming in C++.

## Features
- **Matrix Template**: The `Matrix` class was converted to a template, allowing it to work with any data type, such as `int` or a custom class like `Jason`.
- **Matrix Operations**:
  - **Addition** (`+` operator): Supports adding two matrices of the same size.
  - **Multiplication** (`*` operator): Supports matrix multiplication if the number of columns in the first matrix matches the number of rows in the second.
  - **Rotation**: Rotates the matrix by switching rows and columns.
  - **Insert Elements**: Allows insertion of elements at specified positions.
- **Custom Testing Class** (`Jason`): Includes operator overloading to enable matrix addition and multiplication using objects of the `Jason` class.

## File Structure
- `JosephJasonTemplates.cpp`: Contains the definition of the `Matrix` class template and the custom `Jason` class. This file also includes a main function demonstrating how the template works with different types.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile the program.
   ```sh
   g++ JosephJasonTemplates.cpp -o matrix_template
   ```
2. **Run the Executable**:
   ```sh
   ./matrix_template
   ```

## Example Output
- **Matrices for datatype `int`**:
  - Initial matrix of size 3x5 is generated with random integers.
  - Matrix is rotated, and the output is displayed.
- **Matrices for custom datatype `Jason`**:
  - Matrix of size 3x5 is created using `Jason` objects.
  - The operations supported by `Jason`, such as addition and multiplication, are demonstrated.

## Requirements
- **C++11 or later**: Required for features like uniform initialization and default data type compatibility.

## Notes
- **Error Handling**: The program includes simple error checks for mismatched matrix dimensions during operations such as addition and multiplication.
- **Custom Testing**: The `Jason` class demonstrates the flexibility of the template to accommodate user-defined types with overloaded operators.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

