/*Brian Reza Smith */ 

/*
This file contains the implementation for a a heap data structure that can be used with 
nodes containing payloads of different datatypes and levels of complexity by relying on a generic HeapNode 'class'.

By creating the abstract data structure HeapNode that provides a standardized set of Node operations no matter what the actual derived class payload is, the GenHeap class can do perform all heap operations on heaps using any derived HeapNode as a node type. 

the HeapNode node operations are: 
    -int getKeyFromNode(HeapNode*)
    -void swapHeapNodeData(HeapNode* a, HeapNode* b)
    -HeapNode* copyHeapNode(HeapNode* src)
    -HeapNodeDestructor(HeapNode *inNode)

The GenHeap itself is a struct with the follow data member:
    -int capacity: total capacity
    -int heapSize: number of currently inserted nodes
    -int min_max: (binary switch to determine if its a minheap or maxheap)
    -HeapNode* data[]: array of pointers to our actual nodes. 

The heap operations contained in this file are contained in the definitions of the following functions:
    -Genheap* buildHeap(HeapNode** inputArray, int _size, int _capacity, int min_max)
    -heapNode** heapSort(HeapNode* inNodeArr, int size)
    -int getKey (GenHeap* h, int index)
    -HeapNode* getRootHeapNode(GenHeap* h)
    -void swapHeapIndexes(GenHeap* h, int a, int b)
    -bool heapifyUp(GenHeap* h, int index)
    -bool heapifyDown(GenHeap* h, int index)
    -HeapNode* extractRootHeapNode(GenHeap* h)
    -insertHeapNode(GenHeap* h, HeapNode* inNode)




   */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "HeapNode.h"
#include "GenHeap.h"
#include "IntervalListNode.h"
#include "intervalScheduling.h"

int getKey(GenHeap* h, int i)
{
    return h->data[i]->getKeyFromHeapNode(h->data[i]);
}


//h is pointer to heap, n is index of heap element in question
//outputs boolean based off if any swaps occurred. 

bool heapifyDown(GenHeap* h, int n)
{
    bool overallSwap = false;
    //first iteration we will want to check n 
    bool iterSwap = true;
    int swapIndex = 0;
    //if heap type is min, search for smallest
    while(iterSwap == true)
    {
        iterSwap = false;
        int l = getLChild(n);
        int r = getRChild(n);
        int swapIndex = n;
        //if heap is a minheap, search for smallest of 3 keys
        if(h->min_max == MIN)
        {
            if((l <= h->heapSize) && (getKey(h, l) < getKey(h, n)))
            {
                swapIndex = l;
            }
            if((r <= h->heapSize) && (getKey(h, r) < getKey(h, swapIndex)))
            {
                swapIndex = r;
            }
        }
        //if heap is maxheap, search for largest of 3 keys
        else
        {

            if((l <= h->heapSize) && (getKey(h, l) > getKey(h, n)))
            {
                swapIndex = l;
            }
            if((r <= h->heapSize) && (getKey(h, r) > getKey(h, swapIndex)))
            {
                swapIndex = r;
            }
        }
        if (n != swapIndex)
        {
            h->data[n]->swapHeapNodeData(h->data[n], h->data[swapIndex]);
            n = swapIndex;
            iterSwap = true;
            overallSwap = true;
        }
    }
    return overallSwap; 
}

bool heapifyUp(GenHeap* h, int n)
{
    bool overallSwap = false; 
    //forcing at least 1 iteration
    bool iterSwap = true;
    while (iterSwap == true && n>1)
    {
        iterSwap = false; 

        if(h->min_max == MIN)
        {
            if (getKey(h, n) < getKey(h, getParent(n)))
            {
                iterSwap = true;
                overallSwap = true;
                swapHeapIndexes(h, n, getParent(n));
                n = getParent(n);
            }
        }
        else
        {
            if (getKey(h, n) > getKey(h, getParent(n)))
            {
                iterSwap = true;
                overallSwap = false;
                swapHeapIndexes(h, n, getParent(n));
                n = getParent(n);
            }
        }
    }
    return overallSwap;
}

bool insertHeapNode(GenHeap* h, HeapNode* inNode)
{
    if (h->heapSize + 1 > h->capacity)
    {
        printf("trying to insert into full heap \n");
        return 1;
    }
    
    h->heapSize++;
    h->data[h->heapSize] = inNode->copyHeapNode(inNode);
   
    return heapifyUp(h, h->heapSize);
}



GenHeap* buildHeap(HeapNode* inputArray[], int _size, int _capacity, int _min_max)
{
    GenHeap* temp = malloc(sizeof(GenHeap)+(_capacity+1)*sizeof(HeapNode*));
    temp->capacity = _capacity;
    temp->heapSize = 0;
    temp->min_max = _min_max;
    //temp->data[0] = initNode(-1,-1);
    for (int i = 0; i < _size; i++)
    {
        temp->data[i+1] = inputArray[i]->copyHeapNode(inputArray[i]); 
        temp->heapSize++;
    }

    for (int i = (int)floor(temp->heapSize/2); i>0; i--)
    {
        heapifyDown(temp, i);
    }
    
    return temp; 
}

int getLChild(int index)
{
    return 2*index;
}

int getRChild(int index)
{
    return 2*index+1;
}

int getParent(int index)
{
    return (int) floor(index/2);
}

void isMinHeap(GenHeap* h)
{
    bool isHeap = true; 
    for(int i = h->heapSize; i>1; i--)
    {
        if (getKey(h, getParent(i)) > getKey(h, i))
        {
            isHeap = false; 
        } 
    }
    printf(isHeap ? "it's a minHeap\n" :"it's not a minHeap\n");
}

void isMaxHeap(GenHeap* h)
{
    bool isHeap = true; 
    for(int i = h->heapSize; i>1; i--)
    {
        if (getKey(h, getParent(i)) < getKey(h, i))
        {
            isHeap = false; 
        } 
    }
    printf(isHeap ? "it's a maxHeap\n" :"it's not a maxHeap\n");
}

HeapNode* extractRootHeapNode(GenHeap* h)
{
    if (h->heapSize < 1)
    {
        printf("ERROR: trying to extract from empty heap\n");
        HeapNode* blotto;
        return blotto;
    }
    else
    {
        HeapNode* tempNode = h->data[1]->copyHeapNode(h->data[1]);
        h->data[1]->swapHeapNodeData(h->data[1], h->data[h->heapSize]);
        h->heapSize--;
        heapifyDown(h, 1);

        return tempNode;
    }
}

HeapNode** heapSort(HeapNode** inHeapNodeArr, int size)
{
    HeapNode** tempHeapNodeArr = malloc(size*sizeof(HeapNode*));
    GenHeap* h = buildHeap(inHeapNodeArr, size, size, MIN);
    for(int i = 0; i <size; i++)
    {
        tempHeapNodeArr[i] = inHeapNodeArr[0]->copyHeapNode(extractRootHeapNode(h));
    }
    return tempHeapNodeArr; 
}

HeapNode* getRootHeapNode(GenHeap* h)
{
    return h->data[1];
}

void swapHeapIndexes(GenHeap* h, int a, int b)
{
    if (a > h->heapSize || a <1 || b > h->heapSize || b < 1 || a == b)
    {
        printf("invalid indexes on swap\n");
        return;
    }

    h->data[1]->swapHeapNodeData(h->data[a], h->data[b]);
    return; 
}

/*
int main(int argc, char** argv)
{
    int intervalCount, earliest, latest;
    printf("please enter number of intervals\n");
    scanf("%d", &intervalCount);
    printf("please enter earliest time for intervals\n");
    scanf("%d", &earliest);
    printf("please enter latest time for intervals\n");
    scanf("%d", &latest);
    HeapNode* schedHeapNodeArray[intervalCount];
    for (int i = 0; i < intervalCount; i++)
    {
        schedHeapNodeArray[i] = (HeapNode*)randIntervalSchedHeapNode(earliest, latest);
    }
    printf("=====INTERVALS BEFORE SORT=====\n");
    for (int i = 0; i<intervalCount; i++)
    {
        printf("interval %d: [%d, %d]\n", i, getStartFromIntervalHeapNode(schedHeapNodeArray[i]), getEndFromIntervalHeapNode(schedHeapNodeArray[i]));
    }

    GenHeap* theHeap = buildHeap( heapNodeArray, intervalCount, intervalCount, MIN);
   
    printf("=====HEAP KEYS BEFORE INSERTS=====\n");
    for (int i = 1; i< theHeap->heapSize; i++)
    {
        printf("HeapNode %d's key is: %d\n", i, getKey(theHeap, i));
    }
    
    insertHeapNode(theHeap, heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(12, 24)));
    insertHeapNode(theHeap, heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(12, 72)));

    
    printf("=====HEAP KEYS AFTER INSERTS=====\n");
    for (int i = 1; i<= theHeap->heapSize; i++)
    {
        printf("HeapNode %d's key is: %d\n", i, getKey(theHeap, i));
    }
    
    isMinHeap(theHeap); 


    HeapNode** sortedHeapNodeArray = heapSort(heapNodeArray, intervalCount);
    
    printf("=====INTERVALS AFTER SORT FOR SCHEDULING=====\n");
    for (int i = 0; i<intervalCount; i++)
    {
        printf("interval %d: [%d, %d]\n", i, getStartFromIntervalHeapNode(sortedHeapNodeArray[i]), getEndFromIntervalHeapNode(sortedHeapNodeArray[i]));
    }
    

    IntervalListNode* schedulingHead = getOptimalSchedule(schedHeapNodeArray, intervalCount);
    
    printf("=====INTERVAL SCHEDULING=====\n");
    
    intervalListDisplay(schedulingHead);
    
    HeapNode* partHeapNodeArray[intervalCount];
    for (int i = 0; i<intervalCount; i++)
    {
        partHeapNodeArray[i] = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(getStartFromIntervalHeapNode(schedHeapNodeArray[i]), getEndFromIntervalHeapNode(schedHeapNodeArray[i])));
    } 
    
    return 0;
}
*/


