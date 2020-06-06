#ifndef INTERVALLISTNODE_H
#define INTERVALLISTNODE_H
#include <stdbool.h>
struct IntervalListNode {
    int start;
    int end; 
    struct IntervalListNode* next; 
};

typedef struct IntervalListNode IntervalListNode;

IntervalListNode* intervalListNodeConstructor(int s, int e);
void intervalListNodeDestructor(IntervalListNode*);
IntervalListNode* intervalListGetLast(IntervalListNode* head);
IntervalListNode* intervalListNodeCopy(IntervalListNode* src);
int intervalListAppend(IntervalListNode* head, IntervalListNode* toAdd);
bool intervalListNodeIsCompatible(IntervalListNode* incumbent, IntervalListNode* challenger);
void intervalListDisplay(IntervalListNode* head);

#endif
