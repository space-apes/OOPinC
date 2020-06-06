/*
    Header for implementation of binary heap that allows
    for different datatype payloads in the nodes
    and for either min or max heap property/operations.

    Notable qualities of the implementation include
    the requirement to specify min or max heap when 
    initializing the heap and undefined abstract functions 
    for many node operations. 
    Because we do not know the datatype of the payload
    we will have to define those operations each time we work
    with a new datatype of our payload. 

    Relies on us to provide node.h which defines 
        -initializing a Node
        -getting the key value of a Node
        -swapping 2 Nodes

*/

#ifndef GENERICHEAP_H
#define GENEICRHEAP_H

#define MIN 0
#define MAX 1
#define HEAPCAPACITY 20
#include <stdbool.h>
#include "HeapNode.h"

struct GenHeap{
    int capacity;
    int heapSize;
    int min_max;
    HeapNode* data[];
};

typedef struct GenHeap GenHeap;

GenHeap* buildHeap(HeapNode* inputArray[], int _size, int _capacity, int min_max);
HeapNode** heapSort(HeapNode* inNodeArr[], int size);
int getKey(GenHeap* h, int i);
HeapNode* getRootHeapNode(GenHeap* h);
void swapHeapIndexes(GenHeap* h, int a, int b);
bool heapifyUp(GenHeap* h, int index);
bool heapifyDown(GenHeap* h, int index);
HeapNode* extractRootHeapNode(GenHeap* theHeap);
bool insertHeapNode(GenHeap* h, HeapNode* inNode);

//void deleteNode(GenHeap theHeap, int index);
//int changeKey(GenHeap theHeap, int index, void* newValue);

//need to check heap bounds in other functions that
//use these
int getLChild(int index);
int getRChild(int index);
int getParent(int index);

void isMaxHeap(GenHeap* h);
void isMinHeap(GenHeap* h);

#endif
