/*
   struct definition and prototypes for generic heap node and operations on/between nodes

   */


#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>

struct HeapNode{
    void* data; 
    int (*getKeyFromHeapNode)(struct HeapNode* self);
    struct HeapNode* (*copyHeapNode)(struct HeapNode* src);
    void (*swapHeapNodeData)(struct HeapNode* heapNodeA, struct HeapNode* heapNodeb); 
    void (*heapNodeDestructor)(struct HeapNode* self);
};

typedef struct HeapNode HeapNode;


struct IntHeapNode{
    void* data;
    int (*getKeyFromHeapNode)(struct HeapNode* self);
    struct HeapNode* (*copyHeapNode)(struct HeapNode* src);
    void (*swapHeapNodeData)(struct HeapNode* heapNodeA, struct HeapNode* heapNodeb); 
    void (*heapNodeDestructor)(struct HeapNode* self);
};

typedef struct IntHeapNode IntHeapNode;

struct IntervalSchedHeapNode{
    void* data;
    int (*getKeyFromHeapNode)(struct HeapNode* self);
    struct HeapNode* (*copyHeapNode)(struct HeapNode* src);
    void (*swapHeapNodeData)(struct HeapNode* heapNodeA, struct HeapNode* heapNodeb); 
    void (*heapNodeDestructor)(struct HeapNode* self);
};

typedef struct IntervalSchedHeapNode IntervalSchedHeapNode;


struct IntervalPartHeapNode{
    void* data;
    int (*getKeyFromHeapNode)(struct HeapNode* self);
    struct HeapNode* (*copyHeapNode)(struct HeapNode* src);
    void (*swapHeapNodeData)(struct HeapNode* heapNodeA, struct HeapNode* heapNodeb); 
    void (*heapNodeDestructor)(struct HeapNode* self);
};

typedef struct IntervalPartHeapNode IntervalPartHeapNode;

//constructors
HeapNode* heapNodeConstructor(HeapNode* derivedHeapNode);
IntHeapNode* intHeapNodeConstructor(int);
IntervalSchedHeapNode* intervalSchedHeapNodeConstructor(int, int);
IntervalPartHeapNode* intervalPartHeapNodeConstructor(int, int);

//destructors
void genericHeapNodeDestructor(HeapNode* derivedHeapNode);

//key getters
int getKeyFromIntHeapNode(HeapNode*);
int getKeyFromIntervalSchedHeapNode(HeapNode*);
int getKeyFromIntervalPartHeapNode(HeapNode*);
int getStartFromIntervalHeapNode(HeapNode*);
int getEndFromIntervalHeapNode(HeapNode*);

//type specific copiers
HeapNode* copyIntHeapNode(HeapNode*);
HeapNode* copyIntervalSchedHeapNode(HeapNode*);
HeapNode* copyIntervalPartHeapNode(HeapNode*);

//type-specific value swappers
void swapIntHeapNodeData(HeapNode*, HeapNode*);
void swapIntervalSchedHeapNode(HeapNode*, HeapNode*);
void swapIntervalPartHeapNode(HeapNode*, HeapNode*);

//generic heap operations
void swapHeapNodeData(HeapNode*, HeapNode*);
HeapNode* copyHeapNode(HeapNode*);

//random scheduling heap node generator
IntervalSchedHeapNode* randIntervalSchedHeapNode(int earliest, int latest);
#endif
