/*
 * Sumbitted by Jason Joseph
 * Submitted on November 2, 2024
 * 
 * I took the time to finally figure out why the code was not working from the last attempt and am resubmitting an
 * implementation that produces the proper result. I figured out what was wrong with the comparisons and sorting
 * 
 * createHeapTree: Constructs a HeapTree by counting character frequencies from the input string
 * and creating Leaf nodes for each unique character with a non-zero frequency.
 *
 * buildTree: Constructs a tree by combining nodes from the HeapTree, using a min-heap structure
 * to iteratively combine nodes with the lowest frequencies, maintaining alphabetical order among nodes
 * with equal frequency. Returns the root node of the fully combined tree.
 *
 * See Heap.H for HeapTree class implementation
 */

#include "Heap.h"

auto createHeapTree = [](const string& input, bool max = true) -> HeapTree<Node> {
   minHeap<Node> minComparator;
   maxHeap<Node> maxComparator;

   if (!max) {
        // Count character frequencies for all ASCII values
        int frequency[256] = { 0 };
        for (char ch : input) {
            frequency[static_cast<unsigned char>(ch)]++;  // Increment count for each character in input
        }

        vector<unique_ptr<Node>> nodes;
        for (int i = 0; i < 256; ++i) {
            if (frequency[i] > 0) {
                string symbol(1, static_cast<char>(i));  // Convert ASCII value to character
                nodes.push_back(make_unique<Leaf>(symbol, frequency[i]));
                //cout << "Creating Leaf: Symbol = " << symbol << ", Frequency = " << frequency[i] << endl;
            }
        }

        // Sort nodes first by frequency, then alphabetically by character
        sort(nodes.begin(), nodes.end(), minComparator);
        return HeapTree<Node>(move(nodes));  // Create HeapTree with sorted nodes
    }
   else {
       // Count character frequencies for all ASCII values
       int frequency[256] = { 0 };
       for (char ch : input) {
           frequency[static_cast<unsigned char>(ch)]++;  // Increment count for each character in input
       }

       vector<unique_ptr<Node>> nodes;
       for (int i = 0; i < 256; ++i) {
           if (frequency[i] > 0) {
               string symbol(1, static_cast<char>(i));  // Convert ASCII value to character
               nodes.push_back(make_unique<Leaf>(symbol, frequency[i]));
               //cout << "Creating Leaf: Symbol = " << symbol << ", Frequency = " << frequency[i] << endl;
           }
       }

       // Sort nodes first by frequency, then alphabetically by character
       sort(nodes.begin(), nodes.end());
       return HeapTree<Node>(move(nodes), false);  // Create HeapTree with sorted nodes
   }
};

auto buildTree(const string& input, bool branchOutput = true) {
    HeapTree<Node> heap = createHeapTree(input, false);  // Initialize HeapTree from character frequencies
    HeapTree<Node> heapTree = createHeapTree(input);
    maxHeap<Node> maxComparator;

    if (!branchOutput) {
        // Combine nodes iteratively until only one root node remains
        while (heap.heapSize() > 1) {
            // Access and remove the two smallest nodes from the heap
            unique_ptr<Node> left = move(heap.front());  // Smallest node
            heap.pop();
            unique_ptr<Node> right = move(heap.front());  // Next smallest node
            heap.pop();

            // Create a new Branch node combining the two smallest nodes
            unique_ptr<Branch> newBranch = make_unique<Branch>(left, right);

            // Output symbol and frequency for debugging and visualization
            cout << "Made Branch with symbol: " << newBranch->characterSymbol()
                << " and frequency: " << newBranch->characterFrequency() << endl;

            // Insert the new branch back into the heap to maintain order
            heap.pushBack(move(newBranch));
        }

        // Return the final root node representing the fully combined tree
        return heap;
    }
    else {
        // Combine nodes iteratively until only one root node remains
        while (heap.heapSize() > 1) {
            // Access and remove the two smallest nodes from the heap
            unique_ptr<Node> left = move(heap.front());  // Smallest node
            heap.pop();
            unique_ptr<Node> right = move(heap.front());  // Next smallest node
            heap.pop();

            // Create a new Branch node combining the two smallest nodes
            unique_ptr<Branch> newBranch = make_unique<Branch>(left, right);
            unique_ptr<Branch> branch = make_unique<Branch>(left, right);

            // Output symbol and frequency for debugging and visualization
            cout << "Made Branch with symbol: " << newBranch->characterSymbol()
                << " and frequency: " << newBranch->characterFrequency() << endl;

            // Insert the new branch back into the heap to maintain order
            heap.pushBack(move(branch));
            // Insert the new branch back into the heap to maintain order
            heapTree.pushBack(move(newBranch));
        }

        heapTree.sortTree();
        return heapTree;
    }
}

int main() {
    string river{ "MISSISSIPPI RIVER" };

    HeapTree<Node> heap = buildTree(river, false);
    HeapTree<Node> finalHeap = buildTree(river);

    // Retrieve the character symbol of the root and modify it for display
    unique_ptr<Node> rootSymbol = move(heap.front());
    for (char& ch : rootSymbol->characterSymbol()) {
        if (ch == ' ') {
            ch = '^';  // Replace spaces with '^'
        }
    }

    // Output the modified root symbol
    cout << "Heap root: " << rootSymbol->characterSymbol() << endl;

    finalHeap.printLevelOrder();

    cout << "\nTree diagram: \n";
    finalHeap.printTree();

    return 0;
}