/*
 * Submitted by Jason Joseph
 * Submitted on November 1, 2024
 * 
 * Converted all Raw Pointers to Smart Pointers
 * And converted Heap objects into Smart Pointers
 */


#include <cstdio>
#include <bitset>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <memory>
#include "ConsoleColor.h"

using namespace std;

#define MAX 100

struct Heap
{
    shared_ptr<int> data[MAX];
    int size=0;
};


void swap(shared_ptr<int>& a, shared_ptr<int>& b)
{
    shared_ptr<int> temp = move(a);
    a = move(b);
    b = move(temp);
}

void heapifyMax(unique_ptr<Heap>& heap, int index) 
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // There was no bounds check so I added one
    if (left < heap->size && *heap->data[left] > *heap->data[largest])
        largest = left;
    if (right < heap->size && *heap->data[right] > *heap->data[largest])
        largest = right;

    if (largest != index) 
    {
        swap(heap->data[index], heap->data[largest]);
        heapifyMax(heap, largest);
    }
}

void heapifyMin(unique_ptr<Heap>& heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && *heap->data[left] < *heap->data[smallest])
        smallest = left;
    if (right < heap->size && *heap->data[right] < *heap->data[smallest])
        smallest = right;

    if (smallest != index) 
    {
        swap(heap->data[index], heap->data[smallest]);
        heapifyMin(heap, smallest);
    }
}


void insertMax(unique_ptr<Heap>& heap, int value) 
{
    if (heap->size == MAX) 
    {
        printf("Heap is full!\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = make_shared<int>(value);

    while (i != 0 && *heap->data[(i - 1) / 2] < *heap->data[i])
    {
        swap(heap->data[i], heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insertMin(unique_ptr<Heap>& heap, int value)
{
    if (heap->size == MAX)
    {
        printf("Heap is full!\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = make_shared<int>(value);

    while (i != 0 && *heap->data[(i - 1) / 2] > *heap->data[i])
    {
        swap(heap->data[i], heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

shared_ptr<int> extractRoot(unique_ptr<Heap>& heap,bool bmax)
{
    if (heap->size <= 0)
        return nullptr; // or some other error code
    if (heap->size == 1) 
    {
        heap->size--;
        return heap->data[0];
    }
    shared_ptr<int> root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->data[heap->size - 1] = nullptr;
    heap->size--;
    if (bmax)
        heapifyMax(heap, 0);
    else
        heapifyMin(heap, 0);
    return root;
}

void OutputHeap(unique_ptr<Heap>& heap)
{
    for (int i = 0; i < heap->size; i++)
        printf("heap[%d] = %d\n", i, *heap->data[i]);
}

void stlHeap(vector<int>& hvec)
{
    make_heap(hvec.begin(), hvec.end());
}

void BitShow(int number)
{
    if (number)
    {
        cout << red << "Recursion: " << number << endl;
        BitShow(number >> 1);  // recursion
        cout << green << "\nPopping stackframe: " << number << endl;
        if (number % 2)
            cout << cyan << "<1> ";
        else
            cout << yellow << "<0> ";
    }
}

void main()
{
    // recursion
    {
        int limit = 10;
        cout << cyan << bitset<4>(limit).to_string() << endl;
        BitShow(10);
        cout << endl;
    }

    // fill vector with random data
    int size = 10;
    vector<int> vheap;
    for (int i = 0; i < size; i++)
        vheap.push_back(rand() % MAX + 1);

    // max Heap
    {
        /*
        79
        70                               68
        42              63              65              25
        35	    01      59
        */
        cout << blue;

        unique_ptr<Heap> heapMax(new Heap());

        int size = 10;
        for (int h = 0; h < size; h++)
            insertMax(heapMax, vheap[h]);

        printf("\nHeap root: %d\n", *extractRoot(heapMax,1));
        OutputHeap(heapMax);
    }

    // min Heap
    {
        /*
        1
        25		                        35
        42		        59	            65	            70
        79	    68  	63
        */
        cout << red;

        unique_ptr<Heap> heapMin(new Heap());

        int size = 10;
        for (int h = 0; h < size; h++)
            insertMin(heapMin, vheap[h]);

        printf("\nHeap root: %d\n", *extractRoot(heapMin,0));
        OutputHeap(heapMin);
    }

    // stl heap
    {
        /*
            79
            70                                42
            63              68              25               35
            59      01    65
        */

        cout << yellow << endl;
        stlHeap(vheap);
        for (int v = 0; v<vheap.size(); v++)
            printf("vheap[%d] = %d\n", v, vheap[v]);
    }
    cout << white;
}
