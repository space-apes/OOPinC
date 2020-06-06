#include "IntervalListNode.h"
#include "IntervalListHeapNode.h"




int getKeyFromIntervalListHeapNode(HeapNode* inNode)
{
    return intervalListGetLast(inNode->data)->end;
}

void swapIntervalListHeapNodeData(HeapNode* a, HeapNode* b)
{
    
    if(a==NULL || b==NULL)
    {
        printf("trying to swapIntervalListHeapNodes that are null\n");
        return;
    }
    IntervalListNode* temp = intervalListNodeCopy(a->data);
    
    a->data = intervalListNodeCopy(b->data);
    b->data = intervalListNodeCopy(temp);

    return;
}

HeapNode* copyIntervalListHeapNode(HeapNode* src)
{
    if (src == NULL)
    {
        HeapNode* blotto;
        printf("trying to copy empty node\n");
        return blotto;
    }

    HeapNode* temp = malloc(sizeof(HeapNode));
    
    //temp->data is head
    temp->data = intervalListNodeCopy(src->data);
     
    temp->getKeyFromHeapNode = src->getKeyFromHeapNode;
    temp->swapHeapNodeData = src->swapHeapNodeData;
    temp->copyHeapNode = src->copyHeapNode;
    temp->heapNodeDestructor = intervalListHeapNodeDestructor;

    return temp; 
}

HeapNode* intervalListHeapNodeConstructor(IntervalListNode* inNode)
{
    HeapNode* temp = malloc(sizeof(HeapNode));
    temp->data = intervalListNodeCopy(inNode);

    temp->getKeyFromHeapNode = getKeyFromIntervalListHeapNode;
    temp->swapHeapNodeData = swapIntervalListHeapNodeData;
    temp->copyHeapNode = copyIntervalListHeapNode;
    temp->heapNodeDestructor = intervalListHeapNodeDestructor;
    
    return temp;
}

//because our payload is more complicated than 2 integer array or single integer, 
//must have more complicated destructor. Use built-in IntervalListNodeDestructor for payload
//then free IntervalListHeapNode itself. 
void intervalListHeapNodeDestructor(HeapNode* self)
{
    intervalListNodeDestructor((IntervalListNode*)self->data);
    free(self);
    return; 
}

/*
int main(int argc, char** argv)
{
    IntervalListNode* head = intervalListNodeConstructor(4,5);
    IntervalListNode* next = intervalListNodeConstructor(10,20);
    HeapNode* intervalListHeapNode1 = heapNodeConstructor((HeapNode*)intervalListHeapNodeConstructor(head));
    printf("=====list before append=====\n");
    intervalListDisplay((IntervalListNode*)(intervalListHeapNode1->data));

    intervalListAppend(((IntervalListNode*)(intervalListHeapNode1->data)), next);

    printf("=====list after append=====\n");

    intervalListDisplay((IntervalListNode*)(intervalListHeapNode1->data));

    HeapNode* intervalListHeapNode2 = intervalListHeapNode1->copyHeapNode(intervalListHeapNode1);

    
    printf("=====list after copy=====\n");

    intervalListDisplay((IntervalListNode*)(intervalListHeapNode2->data));
    
    intervalListHeapNode1->heapNodeDestructor(intervalListHeapNode1);
    intervalListHeapNode2->heapNodeDestructor(intervalListHeapNode2);

    printf("=====list after destructor =====\n");

    //intervalListDisplay((IntervalListNode*)(intervalListHeapNode2->data));
    return 0;
}

*/
