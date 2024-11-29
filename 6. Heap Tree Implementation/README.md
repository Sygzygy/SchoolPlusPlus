# Assignment: Heap Tree Implementation

## Description
This assignment involves implementing a heap-based tree structure (`HeapTree`) along with supporting classes such as `Node`, `Leaf`, `Branch`, and comparator classes (`minHeap`, `maxHeap`). The `HeapTree` class supports common heap operations like insertion, removal, and traversal. The main driver program creates the heap tree based on character frequencies from an input string, combining nodes to form a complete heap tree structure.

## Features
- **Node Classes**:
  - **Node** (Abstract Base Class): Defines the interface for `Branch` and `Leaf` nodes.
  - **Branch**: Represents internal nodes that combine two child nodes with combined frequency and symbol.
  - **Leaf**: Represents leaf nodes containing individual characters and their frequencies.
- **HeapTree Class**:
  - Implements a min-heap or max-heap tree structure.
  - Supports inserting nodes (`pushBack`), removing nodes (`pop`), and retrieving nodes (`front`).
  - Provides methods to print the tree in different formats (`printLevelOrder`, `printTree`).
  - Inherits from `std::vector` for storage of nodes.
- **Heap Comparators**:
  - **minHeap** and **maxHeap** comparators used to maintain the heap property during node operations.
- **Tree Construction Functions**:
  - `createHeapTree`: Constructs a `HeapTree` by counting character frequencies from the input string and creating `Leaf` nodes for each character.
  - `buildTree`: Constructs a complete tree by iteratively combining nodes using the `HeapTree` structure.

## File Structure
- `Heap.h`: Contains the class definitions for `Node`, `Branch`, `Leaf`, and `HeapTree`, as well as the comparator structs for min and max heaps.
- `JosephJasonExerciseHeapTree.cpp`: Driver program to test the heap tree implementation and demonstrate its functionality.

## How to Run
1. **Compile the Code**: Use a C++ compiler like `g++` to compile both the header and the driver program.
   ```sh
   g++ JosephJasonExerciseHeapTree.cpp -o heap_tree -I.
   ```
2. **Run the Executable**:
   ```sh
   ./heap_tree
   ```

## Example Output
- **Heap Construction**:
  - Characters from the input string are counted and `Leaf` nodes are created.
  - Nodes are combined iteratively until a complete tree is formed.
- **Tree Representation**:
  - The tree is printed in both level-order and hierarchical formats, with spaces represented by `^` for visualization.
  - Output includes symbols, frequencies, and structure of the constructed heap.

## Requirements
- **C++11 or later**: Required for features such as smart pointers, lambda expressions, and other modern C++ syntax.

## Notes
- **Heap Operations**: The `HeapTree` class provides standard heap operations while allowing flexible use of comparators (`minHeap` or `maxHeap`) to control the structure of the heap.
- **Visualization**: The `printLevelOrder` and `printTree` methods provide a clear representation of the tree structure, which can help in understanding how nodes are combined.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

