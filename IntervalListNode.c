/*
IntervalListNode:
This is an implementation of a singly linked list where the payloads of the nodes represent 
intervals of time. 

MEMBERS:
    -Integer (IntervalListNode*)->start: start time of interval
    -Integer (IntervalListNode*)->end: end time of interval
    -IntervalListNode* (IntervalListNode*)->next: next node in list. 

FUNCTIONS: 
    -IntervalListNode* intervalListConstructor(int s, int e)
    -void intervalListNodeDestructor(IntervalListNode* head)
    -IntervalListNode* intervalListGetLast(IntervalListNode* head)
        *gets last IntervalListNode in the list
    -IntervalListNode* intervalListAppend(IntervalListNode* head, IntervalListNode* nodeToAdd)
        *adds nodeToAdd to end of head's list. 
    -void intervalListDisplay(IntervalListNode* head)
        *displays all start and end times of all elements of an IntervalListNode
    -bool intervalListiNodeIsCompatible(IntervalListNode* incumbent, IntervalListNode* challenger)
        *this function compares start time of challenger to end time of final node in list 
        *to determine if challenger can be added to interval without time conflict
    -IntervalListNode* intervalListNodeCopy(IntervalListNode* src)
        *this function makes a copy of an entire list and its contents 
   */


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

void intervalListNodeDestructor(IntervalListNode* inNode)
{
    if (inNode == NULL)
    {
        printf("trying to destruct IntervalListNode but gave NULL ptr\n");
        return;
    }

    IntervalListNode* curNode;
    while(inNode != NULL)
    {
        curNode = inNode;
        inNode = inNode->next;
        printf("freeing [%d. %d]\n", curNode->start, curNode->end);
        free(curNode);
    }
    return;
}

/*
int main(int argc, char** argv)
{
    IntervalListNode* head1 = intervalListNodeConstructor(1,2);
    intervalListAppend(head1, intervalListNodeConstructor(3,4));
    intervalListAppend(head1, intervalListNodeConstructor(5,6));
    intervalListAppend(head1, intervalListNodeConstructor(7,8));
    intervalListAppend(head1, intervalListNodeConstructor(9,10));
    printf("=====list before adding=====\n");
    intervalListDisplay(head1);
    IntervalListNode* test = intervalListNodeConstructor(10,20);    
    if (intervalListNodeIsCompatible(intervalListGetLast(head1), test))
    {
        intervalListAppend(head1, test);
    } 

    printf("=====list after adding=====\n");
    intervalListDisplay(head1);

    IntervalListNode* head2 = intervalListNodeCopy(head1);

    printf("=====list after copying=====\n");
    intervalListDisplay(head2);

    intervalListNodeDestructor(head1);
    intervalListNodeDestructor(head2);

    return 0;
}
*/

