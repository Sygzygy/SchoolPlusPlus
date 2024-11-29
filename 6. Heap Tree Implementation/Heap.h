/*
 * Heap Tree by Jason Joseph
 * Created on October 28, 2024
 * Updated on November 01, 2021
 *
 * Node class: Defines the base interface for tree nodes, including methods for retrieving
 * the node's frequency and symbol.
 *
 * Branch class: Represents internal nodes that combine two sub-nodes. Contains the combined
 * symbol and frequency from both child nodes.
 *
 * Leaf class: Represents leaf nodes containing individual characters. Stores the character
 * symbol and its frequency.
 *
 * Less struct: Comparator for ordering nodes in the heap by frequency, using the total ASCII
 * sum of symbols if frequencies are equal.
 *
 * HeapTree class: Implements a min-heap-based tree structure with various utility methods for
 * managing nodes, including methods for inserting, removing, and printing the tree structure.
 */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <iomanip>
#include <functional>

using namespace std;

/* =========================== Node class =========================== */

class Node {
public:
    virtual float characterFrequency() = 0;  // Returns node frequency
    virtual string characterSymbol() = 0;    // Returns node symbol
    virtual int priority() = 0;
    virtual ~Node() = default;
}; // end of Node Class

/* ========================== Branch class ========================== */

class Branch : public Node {
public:
    // Combines the frequency and symbols of two nodes
    Branch(unique_ptr<Node>& leftNode, unique_ptr<Node>& rightNode)
        : combinedSymbol(leftNode->characterSymbol() + rightNode->characterSymbol()),
        combinedFrequency(leftNode->characterFrequency() + rightNode->characterFrequency()),
        nodePriority(calculateAsciiPriority(this->combinedSymbol)){}

    // Override methods to provide combined frequency and symbol
    float characterFrequency() override {
        return combinedFrequency;
    }

    string characterSymbol() override {
        return combinedSymbol;
    }

    int priority() override {
        return nodePriority;
    }

private:
    string combinedSymbol;
    float combinedFrequency;
    int nodePriority;

    int calculateAsciiPriority(const string& symbol) {
        int sum = 0;
        for (char ch : symbol) {
            sum += static_cast<int>(ch);
        }
        return sum;
    }
}; // end of Branch Class

/* =========================== Leaf class =========================== */

class Leaf : public Node {
public:
    Leaf(string symbol, float count)
        : symbol(move(symbol)), frequency(count), nodePriority(calculateASCIIPriority(this->symbol)) {}

    // Returns the frequency of the leaf node (individual character)
    float characterFrequency() override {
        return frequency;
    }

    // Returns the symbol of the leaf node (individual character)
    string characterSymbol() override {
        return symbol;
    }

    int priority() override {
        return nodePriority;
    }

private:
    string symbol;
    float frequency;
    int nodePriority;

    int calculateASCIIPriority(const string& symbol) {
        int sum = 0;
        for (char ch : symbol) {
            sum += static_cast<int>(ch);
        }
        return sum;
    }
}; // end of Leaf Class


/* =========================== HeapComparator Base Class =========================== */

template <class NodeType>
struct HeapComparator {
    virtual bool operator()(const unique_ptr<NodeType>& left, const unique_ptr<NodeType>& right) const = 0;
    virtual ~HeapComparator() = default;
};

/* =========================== MinHeap Struct =========================== */

template <class NodeType>
struct minHeap : public HeapComparator<NodeType> {
    bool operator()(const unique_ptr<NodeType>& left, const unique_ptr<NodeType>& right) const override {
        // First compare frequencies (BST property)
        if (left->characterFrequency() != right->characterFrequency()) {
            return left->characterFrequency() < right->characterFrequency();
        }
        // Use ASCII-based priority for heap property
        return left->priority() < right->priority();
    }
};

/* =========================== MaxHeap Struct =========================== */

template <class NodeType>
struct maxHeap : public HeapComparator<NodeType> {
    bool operator()(const unique_ptr<NodeType>& left, const unique_ptr<NodeType>& right) const override {
        // First compare frequencies (BST property)
        if (left->characterFrequency() != right->characterFrequency()) {
            return left->characterFrequency() > right->characterFrequency();
        }
        // Use ASCII-based priority for heap property
        return left->priority() < right->priority();
    }
};

/* ========================== HeapTree class ========================== */

template <class NodeType>
class HeapTree : public vector<unique_ptr<NodeType>> {
public:
    explicit HeapTree(vector<unique_ptr<NodeType>> nodes, bool isMinHeap = true)
        : vector<unique_ptr<NodeType>>(move(nodes)) {
        // Conditionally assign either minHeap or maxHeap based on `min` parameter
        if (isMinHeap) {
            comparator = minHeap<NodeType>();
        }
        else {
            comparator = maxHeap<NodeType>();
        }
        
        make_heap(this->begin(), this->end(), comparator);
        sort(this->begin(), this->end(), comparator);  // Ensures nodes are initially ordered by the comparator
        }

    // Pushes a node, maintains heap structure, and sorts nodes
    void pushBack(unique_ptr<NodeType> node) {
        this->push_back(move(node));  // Insert node
        push_heap(this->begin(), this->end(), comparator);  // Maintain heap property
        sort(this->begin(), this->end(), comparator);  // Ensure nodes are ordered by comparator
    }

    // Removes the smallest node from the heap
    void pop() {
        if (isEmpty()) {
            throw runtime_error("Heap is empty.");
        }
        pop_heap(this->begin(), this->end(), comparator);  // Move smallest node to the end
        this->pop_back();  // Remove the smallest node

    }

    // Returns the smallest node without removing it
    unique_ptr<NodeType>& front() {
        if (isEmpty()) {
            throw runtime_error("Heap is empty.");
        }
        return this->at(0);  // Access root node
    }

    // Check if the heap is empty
    bool isEmpty() const {
        return this->empty();
    }

    // Returns the number of nodes in the heap
    size_t heapSize() const {
        return this->size();
    }

    // Sorting function for the tree
    void sortTree() {
        sort(this->begin(), this->end(), comparator);
    }

    // Prints each tree level, replacing spaces with '^' for visualization
    void printLevelOrder() const {
        int levelSize = 1;
        int index = 0;
        cout << "Level Order Representation:\n";

        while (index < this->size()) {
            for (int i = 0; i < levelSize && index < this->size(); ++i) {
                string symbol = (*this)[index]->characterSymbol();
                for (char& ch : symbol) {
                    if (ch == ' ') ch = '^';  // Replace spaces with '^'
                }
                cout << symbol << " ";
                index++;
            }
            cout << "\n";  // Newline for each level
            levelSize *= 2;  // Next level size doubles
        }
    }

    // Recursively prints the tree with each level indented, replacing spaces with '^'
    void printTree(int index = 0, int depth = 0) const {
        if (index >= this->size()) return;

        // Print right subtree first for better visualization
        printTree(2 * index + 2, depth + 1);

        string symbol = (*this)[index]->characterSymbol();
        for (char& ch : symbol) {
            if (ch == ' ') ch = '^';
        }
        cout << setw(4 * depth) << "" << symbol << "\n";

        // Print left subtree
        printTree(2 * index + 1, depth + 1);
    }

private:
    function<bool(const unique_ptr<NodeType>&, const unique_ptr<NodeType>&)> comparator;
}; // end of HeapTree class
