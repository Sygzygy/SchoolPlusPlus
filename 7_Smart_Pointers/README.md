# Assignment: Heap Implementation with Smart Pointers

## Description
This assignment involves implementing a heap structure (`Heap` struct) with the replacement of all raw pointers by smart pointers (`unique_ptr` and `shared_ptr`). The project showcases heap operations such as insertion, extraction, and heapify, using smart pointers for better memory management. Additionally, console colors are used to illustrate recursive calls and heap structures for improved visualization.

## Features
- **Smart Pointers**:
  - Converted all raw pointers to `shared_ptr` and `unique_ptr` for better memory management.
  - Heap nodes and data are now stored using smart pointers to ensure automatic memory cleanup and prevent memory leaks.
- **Heap Structure** (`Heap` struct):
  - Implements both max-heap and min-heap operations using smart pointers.
  - Functions include `insertMax`, `insertMin`, `heapifyMax`, `heapifyMin`, `extractRoot`, and `OutputHeap`.
- **Console Colors** (`ConsoleColor.h`):
  - Uses Windows API to change console text color for visualization purposes.
  - Functions like `red()`, `green()`, `yellow()`, and `cyan()` are used to set different text colors to enhance readability.
- **Recursive Visualization** (`BitShow` function):
  - Displays the recursive calls and stack popping sequence for better understanding.
  - Uses colors to visually distinguish between different stages of recursion.
- **STL Heap Demonstration** (`stlHeap` function):
  - Demonstrates usage of the standard C++ library heap operations (`make_heap`).

## File Structure
- `HeapC.cpp`: Contains the heap implementation using smart pointers, including all heap operations and console color integration.
- `ConsoleColor.h`: Defines various console color functions using the Windows API for setting text color in the console.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile the source file along with color support. Note that Windows-specific headers are used, so the code needs to be compiled on a Windows environment.
   ```sh
   g++ HeapC.cpp -o heap_with_colors -I. -lgdi32
   ```
2. **Run the Executable**:
   ```sh
   ./heap_with_colors
   ```

## Example Output
- **Heap Operations**:
  - The heap is built using random values and displayed as both a max-heap and a min-heap.
  - Heap extraction is performed, showing the root value and the remaining heap.
- **Colored Console Output**:
  - Recursion in `BitShow` is highlighted with different colors to visualize stack operations.
  - Heap nodes are printed in different colors for better visualization.
- **STL Heap**:
  - Demonstrates standard heap operations using the C++ standard library.

## Requirements
- **C++11 or later**: Required for features like smart pointers and lambda functions.
- **Windows Platform**: The use of Windows API for console color output means this program is intended to run on Windows systems.

## Notes
- **Memory Management**: Converting raw pointers to smart pointers helps prevent common memory management errors like leaks and dangling pointers.
- **Console Colors**: The use of colors makes it easier to trace and visualize the steps of heap operations, especially during recursion.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

