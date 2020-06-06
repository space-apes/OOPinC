#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>

struct Node{
    void* data; 
    int (*getKeyFromNode)(struct Node* self);
};

typedef struct Node Node;


struct intNode{
    void* data;
    int (*getKeyFromNode)(struct Node* self); 
};

typedef struct intNode intNode;
/*
struct intervalNode{
    Node base;
    int (*getKeyFromNode)(struct Node self); 
}

typedef struct intervalNode intervalNode
*/
#endif
