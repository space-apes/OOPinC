#include <stdlib.h>
#include<stdio.h>
#include "IntervalListNode.h"

IntervalListNode* intervalListNodeConstructor(int s, int e){
    IntervalListNode* temp = malloc(sizeof(IntervalListNode));
    temp->start = s;
    temp->end = e;
    temp->next = NULL;

    return temp;
}

IntervalListNode* intervalListGetLast(IntervalListNode* head)
{
    IntervalListNode* current = head;
    while(current->next != NULL)
    {
        current = current->next;
    }    

    return current;
}

int intervalListAppend(IntervalListNode* head, IntervalListNode* nodeToAdd)
{
    IntervalListNode* current = head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = nodeToAdd;
} 

void intervalListDisplay(IntervalListNode* head)
{
    IntervalListNode* current = head;
    while(current->next != NULL)
    {
        printf("[%d, %d] ", current->start, current->end);
        current = current->next;
    }
    
    printf("[%d, %d] ", current->start, current->end);
    
    printf("\n");
}

bool intervalListNodeIsCompatible(IntervalListNode* incumbent, IntervalListNode* challenger)
{
    return challenger->start >= incumbent->end;
}

IntervalListNode* intervalListNodeCopy(IntervalListNode* src)
{
    if(src == NULL)
    {
        printf("trying to copy empty IntervalListNode\n");
        return NULL;
    }
    
    IntervalListNode* dstHead = intervalListNodeConstructor(src->start, src->end);
    IntervalListNode* curDst = dstHead;
    IntervalListNode* curSrc = src; 

    curSrc = curSrc->next;
    while (curSrc != NULL)
    {
        curDst->next = intervalListNodeConstructor(curSrc->start, curSrc->end);
        curDst = curDst->next;
        curSrc = curSrc->next;
    }

    return dstHead;
}

/*
int main(int argc, char** argv)
{
    IntervalListNode* head = intervalListNodeConstructor(1,2);
    intervalListAppend(head, intervalListNodeConstructor(3,4));
    intervalListAppend(head, intervalListNodeConstructor(5,6));
    intervalListAppend(head, intervalListNodeConstructor(7,8));
    intervalListAppend(head, intervalListNodeConstructor(9,10));
    printf("=====list before adding=====\n");
    intervalListDisplay(head);
    IntervalListNode* test = intervalListNodeConstructor(10,20);    
    if (intervalListNodeIsCompatible(intervalListGetLast(head), test))
    {
        intervalListAppend(head, test);
    } 

    printf("=====list after adding=====\n");
    intervalListDisplay(head);

    IntervalListNode* head2 = intervalListNodeCopy(head);

    printf("=====list after copying=====\n");
    intervalListDisplay(head2);
    return 0;
}

*/
