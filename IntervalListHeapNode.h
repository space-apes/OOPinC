#ifndef INTERVALLISTHEAPNODE_H
#define INTERVALLISTHEAPNODE_H

#include "HeapNode.h"
struct IntervalListHeapNode{
    void* data; 
    int (*getKeyFromHeapNode)(struct HeapNode* self);
    struct HeapNode* (*copyHeapNode)(struct HeapNode* src);
    void (*swapHeapNodeData)(struct HeapNode* heapNodeA, struct HeapNode* heapNodeb); 
    void (*heapNodeDestructor)(struct HeapNode*);
};

typedef struct IntervalListHeapNode IntervalListHeapNode;

HeapNode* intervalListHeapNodeConstructor(IntervalListNode*);
void intervalListHeapNodeDestructor(HeapNode* self);
int getKeyFromIntervalListHeapNode(HeapNode* inNode);
void swapIntervalListHeapNodeData(HeapNode* a, HeapNode* b);
HeapNode* copyIntervalListHeapNode(HeapNode* src);


#endif
