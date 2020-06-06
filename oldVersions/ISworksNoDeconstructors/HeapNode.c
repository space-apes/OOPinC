//TODO DESTRUCTORS,
//TODO      YOU
//TODO          ASSHOLE!
//TODO




#include "HeapNode.h"
HeapNode* heapNodeConstructor(HeapNode* derivedHeapNode)
{
    HeapNode* temp = malloc(sizeof(struct HeapNode));
    temp->data = derivedHeapNode->data;
    temp->getKeyFromHeapNode = derivedHeapNode->getKeyFromHeapNode; 
    temp->swapHeapNodeData = derivedHeapNode->swapHeapNodeData;
    temp->copyHeapNode = derivedHeapNode->copyHeapNode;
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
}

IntHeapNode* intHeapNodeConstructor(int _payload)
{   
    IntHeapNode* tempIntHeapNode = malloc(sizeof(IntHeapNode)); 
    tempIntHeapNode->data = (int*)malloc(sizeof(int));
    *((int*)(tempIntHeapNode->data)) = _payload;
    tempIntHeapNode->getKeyFromHeapNode = getKeyFromIntHeapNode;
    tempIntHeapNode->swapHeapNodeData = swapIntHeapNodeData;
    tempIntHeapNode->copyHeapNode = copyIntHeapNode;

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

    return tempHeapNode;
}

IntervalSchedHeapNode* randIntervalSchedHeapNode(int earliest, int latest)
{
    int s = 0;
    int e = 0;
    do {
        s = earliest+(rand() % (latest - earliest+1)) ;
        e = earliest+(rand() % (latest - earliest + 1)) ;
    }while(s >= e);

    
    return intervalSchedHeapNodeConstructor(s, e);
}


/*
int main(int argc, char** argv)
{   
    HeapNode* intHeapNode1 = heapNodeConstructor((HeapNode*)intHeapNodeConstructor(7));
    HeapNode* intHeapNode2 = heapNodeConstructor((HeapNode*)intHeapNodeConstructor(85));
    printf("BEFORESWAP intHeapNode1's key: %d, intHeapNode2's key: %d\n", intHeapNode1->getKeyFromHeapNode(intHeapNode1), intHeapNode2->getKeyFromHeapNode(intHeapNode2));
    intHeapNode1->swapHeapNodeData(intHeapNode1,intHeapNode2);
    printf("AFTERSWAP intHeapNode1's key: %d, intHeapNode2's key: %d\n", intHeapNode1->getKeyFromHeapNode(intHeapNode1), intHeapNode2->getKeyFromHeapNode(intHeapNode2)); 
    HeapNode* intHeapNodeSrc = heapNodeConstructor((HeapNode*)intHeapNodeConstructor(7));
    HeapNode* intHeapNodeDst = intHeapNodeSrc->copyHeapNode(intHeapNodeSrc);
    printf("intHeapNodeDst's key is %d\n", intHeapNodeDst->getKeyFromHeapNode(intHeapNodeDst));
    

    
    HeapNode* intervalSchedHeapNode1 = heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(2,5));
    HeapNode* intervalSchedHeapNode2 = heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(33, 99));
    printf("BEFORESWAP intervalSchedHeapNode1's key is %d and intervalSchedHeapNode2's key is %d\n", intervalSchedHeapNode1->getKeyFromHeapNode(intervalSchedHeapNode1), intervalSchedHeapNode2->getKeyFromHeapNode(intervalSchedHeapNode2));
    intervalSchedHeapNode1->swapHeapNodeData(intervalSchedHeapNode1, intervalSchedHeapNode2);    
    printf("AFTERSWAP intervalSchedHeapNode1's key is %d and intervalSchedHeapNode2's key is %d\n", intervalSchedHeapNode1->getKeyFromHeapNode(intervalSchedHeapNode1), intervalSchedHeapNode2->getKeyFromHeapNode(intervalSchedHeapNode2));
    HeapNode* srcIntervalSchedHeapNode = heapNodeConstructor((HeapNode*)intervalSchedHeapNodeConstructor(2,5));
    HeapNode* dstIntervalSchedHeapNode = srcIntervalSchedHeapNode->copyHeapNode(srcIntervalSchedHeapNode);
    printf("dstIntervalSchedHeapNode's key is %d\n", dstIntervalSchedHeapNode->getKeyFromHeapNode(dstIntervalSchedHeapNode));
    

    
    HeapNode* intervalPartHeapNode1 = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(2,5));
    HeapNode* intervalPartHeapNode2 = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(33, 99));
    printf("BEFORESWAP intervalPartHeapNode1's key is %d and intervalPartHeapNode2's key is %d\n", intervalPartHeapNode1->getKeyFromHeapNode(intervalPartHeapNode1), intervalPartHeapNode2->getKeyFromHeapNode(intervalPartHeapNode2));
    intervalPartHeapNode1->swapHeapNodeData(intervalPartHeapNode1, intervalPartHeapNode2);    
    printf("AFTERSWAP intervalPartHeapNode1's key is %d and intervalPartHeapNode2's key is %d\n", intervalPartHeapNode1->getKeyFromHeapNode(intervalPartHeapNode1), intervalPartHeapNode2->getKeyFromHeapNode(intervalPartHeapNode2));
    HeapNode* srcIntervalPartHeapNode = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(2,5));
    HeapNode* dstIntervalPartHeapNode = srcIntervalPartHeapNode->copyHeapNode(srcIntervalPartHeapNode);
    printf("dstIntervalPartHeapNode's key is %d\n", dstIntervalPartHeapNode->getKeyFromHeapNode(dstIntervalPartHeapNode));
    

}
*/
