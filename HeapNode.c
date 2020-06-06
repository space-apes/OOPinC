/*
This file contains the implementation for the abstract data structure HeapNode 'class' to be used as nodes for the GenHeap abstract data structure 'class'. Also contains implementations for a couple derived classes of the HeapNode to be used in the 
interval scheduling and interval partitioning problems.

Each HeapNode is a struct with a void pointer and a standard set of function pointers: 
    -void* data: payload
    -int getKeyFromHeapNode(HeapNode*)
    -void swapHeapNodeData(HeapNode* a, HeapNode* b): maintains original pointers to nodes but swaps data. 
    -HeapNode* copyHeapNode(HeapNode* src): allocates and produces a second copy of source HeapNode
    -void heapNodeDestructor(HeapNode*)

    any actual actual instance of a HeapNode with some specified data as the payload
    needs to link the function pointers up to appropriate function definitions to be able to work with that
    particular kind of data. 

    the function names are standardized but the implementations are not so nodes with different payloads 
    can be used in the same heap implementation, they just have to define their particular ways to get key value, 
    swap, etc. 

    */


#include "HeapNode.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
HeapNode* heapNodeConstructor(HeapNode* derivedHeapNode)
{
    HeapNode* temp = malloc(sizeof(struct HeapNode));
    temp->data = derivedHeapNode->data;
    temp->getKeyFromHeapNode = derivedHeapNode->getKeyFromHeapNode; 
    temp->swapHeapNodeData = derivedHeapNode->swapHeapNodeData;
    temp->copyHeapNode = derivedHeapNode->copyHeapNode;
    temp->heapNodeDestructor = derivedHeapNode->heapNodeDestructor;
    return temp; 
}

int getKeyFromIntHeapNode(HeapNode* inHeapNode)
{
    return *((int*)inHeapNode->data); 
}

int getKeyFromIntervalSchedHeapNode(HeapNode* schedHeapNode)
{
    return ((int*)(schedHeapNode->data))[1]; 
}

int getKeyFromIntervalPartHeapNode(HeapNode* schedHeapNode)
{
    return ((int*)(schedHeapNode->data))[0]; 
}

int getStartFromIntervalHeapNode(HeapNode* heapNode)
{
    return ((int*)heapNode->data)[0];
}

int getEndFromIntervalHeapNode(HeapNode* heapNode)
{
    return ((int*)heapNode->data)[1];
}

void swapIntHeapNodeData(HeapNode* heapNodeA, HeapNode* heapNodeB)
{
    int temp = *((int*)heapNodeA->data);
    *((int*)(heapNodeA->data)) = *((int*)(heapNodeB->data));
    *((int*)(heapNodeB->data)) = temp; 
    return;  
}

void swapIntervalHeapNodeData(HeapNode* heapNodeA, HeapNode* heapNodeB)
{
    int tempS = 0;
    int tempE = 0;
 
    tempS = ((int*)(heapNodeA->data))[0];
    tempE = ((int*)(heapNodeA->data))[1];
        
    ((int*)(heapNodeA->data))[0] = ((int*)(heapNodeB->data))[0];
    ((int*)(heapNodeA->data))[1] = ((int*)(heapNodeB->data))[1];

    ((int*)(heapNodeB->data))[0] = tempS;
    ((int*)(heapNodeB->data))[1] = tempE;
    return;
}

HeapNode* copyIntHeapNode(HeapNode* src)
{
    HeapNode* temp = malloc(sizeof(HeapNode));
    temp->data = malloc(sizeof(int));
    *((int*)temp->data) = *((int*)src->data);
    temp->getKeyFromHeapNode = src->getKeyFromHeapNode;
    temp->swapHeapNodeData = src->swapHeapNodeData;
    temp->copyHeapNode = src->copyHeapNode;
    temp->heapNodeDestructor = src->heapNodeDestructor;

    return temp;
}

HeapNode* copyIntervalHeapNode(HeapNode* src)
{
    HeapNode* temp = malloc(sizeof(HeapNode));
    temp->data = malloc(2*sizeof(int));

    ((int*)(temp->data))[0] = ((int*)(src->data))[0];
    ((int*)(temp->data))[1] = ((int*)(src->data))[1];
    
    temp->getKeyFromHeapNode = src->getKeyFromHeapNode;
    temp->swapHeapNodeData = src->swapHeapNodeData;
    temp->copyHeapNode = src->copyHeapNode;
    temp->heapNodeDestructor = src->heapNodeDestructor;
    
    return temp;
    
}

IntHeapNode* intHeapNodeConstructor(int _payload)
{   
    IntHeapNode* tempIntHeapNode = malloc(sizeof(IntHeapNode)); 
    tempIntHeapNode->data = (int*)malloc(sizeof(int));
    *((int*)(tempIntHeapNode->data)) = _payload;
    tempIntHeapNode->getKeyFromHeapNode = getKeyFromIntHeapNode;
    tempIntHeapNode->swapHeapNodeData = swapIntHeapNodeData;
    tempIntHeapNode->copyHeapNode = copyIntHeapNode;
    tempIntHeapNode->heapNodeDestructor = genericHeapNodeDestructor;

    return tempIntHeapNode;
}

IntervalSchedHeapNode* intervalSchedHeapNodeConstructor(int s, int e)
{
    IntervalSchedHeapNode* tempHeapNode = malloc(sizeof(IntervalSchedHeapNode));
    tempHeapNode->data = (int*)malloc(2*sizeof(int));
    ((int*)(tempHeapNode->data))[0] = s;
    ((int*)(tempHeapNode->data))[1] = e;
    tempHeapNode->getKeyFromHeapNode = getKeyFromIntervalSchedHeapNode;
    tempHeapNode->swapHeapNodeData = swapIntervalHeapNodeData;
    tempHeapNode->copyHeapNode = copyIntervalHeapNode;
    tempHeapNode->heapNodeDestructor = genericHeapNodeDestructor;

    return tempHeapNode;
}


IntervalPartHeapNode* intervalPartHeapNodeConstructor(int s, int e)
{
    IntervalPartHeapNode* tempHeapNode = malloc(sizeof(IntervalSchedHeapNode));
    tempHeapNode->data = (int*)malloc(2*sizeof(int));
    ((int*)(tempHeapNode->data))[0] = s;
    ((int*)(tempHeapNode->data))[1] = e;
    tempHeapNode->getKeyFromHeapNode = getKeyFromIntervalPartHeapNode;
    tempHeapNode->swapHeapNodeData = swapIntervalHeapNodeData;
    tempHeapNode->copyHeapNode = copyIntervalHeapNode;
    tempHeapNode->heapNodeDestructor = genericHeapNodeDestructor;

    return tempHeapNode;
}

/*
   randIntervalSchedHeapNode     
   
   generates intervalSchedHeapNode 'object' with 
   random start and end time with the constraints:
        -start and end must fall within earliest and latest
        -start must be less than end

   seeds randomizer with time in microseconds from epoch.
*/


IntervalSchedHeapNode* randIntervalSchedHeapNode(int earliest, int latest)
{
    int s = 0;
    int e = 0;
    struct timeval curTime; 
    gettimeofday(&curTime, NULL);
    srand(curTime.tv_usec);
    do {
        s = earliest+rand() % (latest - earliest +1);
        e = earliest+rand() % (latest - earliest+ 1);

    }while(s>=e);
    
    return intervalSchedHeapNodeConstructor(s, e);
}

/*
    destructor for HeapNode elements and derived HeapNodes in most basic case that the payload requires only a single malloc. 
    for any heapnode with a more complicated payload, need to define a separate destructor. 
   */
void genericHeapNodeDestructor(HeapNode* derivedHeapNode)
{
    if(derivedHeapNode == NULL)
    {
        printf("trying to use destructor on null ptr\n");
        return;
    }

    free(derivedHeapNode->data);
    free (derivedHeapNode);
    return; 
}

/*
int main(int argc, char** argv)
{
       
    //TESTING INTHEAPNODE
    HeapNode* intHeapNode1 = heapNodeConstructor((HeapNode*)intHeapNodeConstructor(7));
    HeapNode* intHeapNode2 = heapNodeConstructor((HeapNode*)intHeapNodeConstructor(85));
    printf("BEFORESWAP intHeapNode1's key: %d, intHeapNode2's key: %d\n", intHeapNode1->getKeyFromHeapNode(intHeapNode1), intHeapNode2->getKeyFromHeapNode(intHeapNode2));
    intHeapNode1->swapHeapNodeData(intHeapNode1,intHeapNode2);
    printf("AFTERSWAP intHeapNode1's key: %d, intHeapNode2's key: %d\n", intHeapNode1->getKeyFromHeapNode(intHeapNode1), intHeapNode2->getKeyFromHeapNode(intHeapNode2)); 
    HeapNode* intHeapNodeSrc = heapNodeConstructor((HeapNode*)intHeapNodeConstructor(7));
    HeapNode* intHeapNodeDst = intHeapNodeSrc->copyHeapNode(intHeapNodeSrc);
    printf("intHeapNodeDst's key is %d\n", intHeapNodeDst->getKeyFromHeapNode(intHeapNodeDst));
    intHeapNode1->heapNodeDestructor(intHeapNode1);
    intHeapNode2->heapNodeDestructor(intHeapNode2);
    intHeapNodeSrc->heapNodeDestructor(intHeapNodeSrc);
    intHeapNodeDst->heapNodeDestructor(intHeapNodeDst);
    //printf("==intHeapNode1's key after destructing is %d\n", intHeapNode1->getKeyFromHeapNode(intHeapNode1));

    //TESTING INTERVALSCHEDHEAPNODE
    HeapNode* intervalSchedHeapNode1 = heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(2,5));
    HeapNode* intervalSchedHeapNode2 = heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(33, 99));
    printf("BEFORESWAP intervalSchedHeapNode1's key is %d and intervalSchedHeapNode2's key is %d\n", intervalSchedHeapNode1->getKeyFromHeapNode(intervalSchedHeapNode1), intervalSchedHeapNode2->getKeyFromHeapNode(intervalSchedHeapNode2));
    intervalSchedHeapNode1->swapHeapNodeData(intervalSchedHeapNode1, intervalSchedHeapNode2);    
    printf("AFTERSWAP intervalSchedHeapNode1's key is %d and intervalSchedHeapNode2's key is %d\n", intervalSchedHeapNode1->getKeyFromHeapNode(intervalSchedHeapNode1), intervalSchedHeapNode2->getKeyFromHeapNode(intervalSchedHeapNode2));
    HeapNode* srcIntervalSchedHeapNode = heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(2,5));
    HeapNode* dstIntervalSchedHeapNode = srcIntervalSchedHeapNode->copyHeapNode(srcIntervalSchedHeapNode);
    printf("dstIntervalSchedHeapNode's key is %d\n", dstIntervalSchedHeapNode->getKeyFromHeapNode(dstIntervalSchedHeapNode));
    intervalSchedHeapNode1->heapNodeDestructor(intervalSchedHeapNode1);
    intervalSchedHeapNode2->heapNodeDestructor(intervalSchedHeapNode2);
    srcIntervalSchedHeapNode->heapNodeDestructor(srcIntervalSchedHeapNode);
    dstIntervalSchedHeapNode->heapNodeDestructor(dstIntervalSchedHeapNode);
    //printf("==intervalSchedHeapNode1's key after destructing is %d\n", intervalSchedHeapNode1->getKeyFromHeapNode(intervalSchedHeapNode1));

    //TESTING INTERVALPARTHEAPNODE
    HeapNode* intervalPartHeapNode1 = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(2,5));
    HeapNode* intervalPartHeapNode2 = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(33, 99));
    printf("BEFORESWAP intervalPartHeapNode1's key is %d and intervalPartHeapNode2's key is %d\n", intervalPartHeapNode1->getKeyFromHeapNode(intervalPartHeapNode1), intervalPartHeapNode2->getKeyFromHeapNode(intervalPartHeapNode2));
    intervalPartHeapNode1->swapHeapNodeData(intervalPartHeapNode1, intervalPartHeapNode2);    
    printf("AFTERSWAP intervalPartHeapNode1's key is %d and intervalPartHeapNode2's key is %d\n", intervalPartHeapNode1->getKeyFromHeapNode(intervalPartHeapNode1), intervalPartHeapNode2->getKeyFromHeapNode(intervalPartHeapNode2));
    HeapNode* srcIntervalPartHeapNode = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(2,5));
    HeapNode* dstIntervalPartHeapNode = srcIntervalPartHeapNode->copyHeapNode(srcIntervalPartHeapNode);
    printf("dstIntervalPartHeapNode's key is %d\n", dstIntervalPartHeapNode->getKeyFromHeapNode(dstIntervalPartHeapNode));
    intervalPartHeapNode1->heapNodeDestructor(intervalPartHeapNode1);
    intervalPartHeapNode2->heapNodeDestructor(intervalPartHeapNode2);
    srcIntervalPartHeapNode->heapNodeDestructor(srcIntervalPartHeapNode);
    dstIntervalPartHeapNode->heapNodeDestructor(dstIntervalPartHeapNode);
    //printf("==intervalPartHeapNode1's key after destructing is %d\n", intervalPartHeapNode1->getKeyFromHeapNode(intervalPartHeapNode1));
    
    return 0;
}

*/
