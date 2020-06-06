#include "HeapNode.h"
#include "GenHeap.h"
#include "IntervalListNode.h"
#include "intervalScheduling.h"
#include "intervalPartitioning.h"
#include "IntervalListHeapNode.h"
GenHeap* partitionIntervals(HeapNode** intervalPartHeapNodeArray, int _size)
{
         
    //sort intervalPartHeapNodes by finish time
    HeapNode** sortedPartHeapNodeArray = heapSort(intervalPartHeapNodeArray, _size);

    HeapNode* singleTon[1];
    
    singleTon[0] = heapNodeConstructor((HeapNode*) intervalListHeapNodeConstructor(intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedPartHeapNodeArray[0]), getEndFromIntervalHeapNode(sortedPartHeapNodeArray[0]))));
    
    GenHeap* partitionHeap = buildHeap(singleTon, 1, _size, MIN);
    for(int i = 1; i<_size; i++)
    {
        //if interval is compatible with root partition
        if(getKey(partitionHeap,1) <= getStartFromIntervalHeapNode(sortedPartHeapNodeArray[i]))
        {
            //append it to root partition
            intervalListAppend(getRootHeapNode(partitionHeap)->data, intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedPartHeapNodeArray[i]), getEndFromIntervalHeapNode(sortedPartHeapNodeArray[i])));
            //heapify root partition down
            heapifyDown(partitionHeap, 1);
        }
        //if interval is not compatible with root partition
        else
        {
            //create new partition
            HeapNode* newNode = heapNodeConstructor((HeapNode*)intervalListHeapNodeConstructor(intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedPartHeapNodeArray[i]), getEndFromIntervalHeapNode(sortedPartHeapNodeArray[i]))));
            //insert new intervalListHeapNode into heap
            insertHeapNode(partitionHeap, newNode);
        }
    }

    return partitionHeap;
}

void displayPartitions(GenHeap* intervalListNodeHeap, int intervalCount)
{
    printf("minimum partitions for our %d intervals is %d\n", intervalCount, intervalListNodeHeap->heapSize);
    int count = intervalListNodeHeap->heapSize;
    for(int i = 0; i<count; i++)
    {
        printf("partition %d\n", i);
        intervalListDisplay(extractRootHeapNode(intervalListNodeHeap)->data);
    }
}


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
  
    GenHeap* theHeap = buildHeap( schedHeapNodeArray, intervalCount, intervalCount, MIN);
   /*
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

    */
    HeapNode** sortedHeapNodeArray = heapSort(schedHeapNodeArray, intervalCount);
    /*
    printf("=====INTERVALS AFTER SORT FOR SCHEDULING=====\n");
    for (int i = 0; i<intervalCount; i++)
    {
        printf("interval %d: [%d, %d]\n", i, getStartFromIntervalHeapNode(sortedHeapNodeArray[i]), getEndFromIntervalHeapNode(sortedHeapNodeArray[i]));
    }
    */
    IntervalListNode* schedulingHead = getOptimalSchedule(schedHeapNodeArray, intervalCount);
    
    printf("=====INTERVAL SCHEDULING=====\n");
    
    intervalListDisplay(schedulingHead);
    
    HeapNode* partHeapNodeArray[intervalCount];
    for (int i = 0; i<intervalCount; i++)
    {   
        partHeapNodeArray[i] = heapNodeConstructor((HeapNode*)intervalPartHeapNodeConstructor(getStartFromIntervalHeapNode(schedHeapNodeArray[i]), getEndFromIntervalHeapNode(schedHeapNodeArray[i])));
    }

    GenHeap* partitionHeap = partitionIntervals(partHeapNodeArray, intervalCount);
    printf("=====INTERVAL PARTITIONING=====\n");
    
    isMinHeap(partitionHeap);
    
    displayPartitions (partitionHeap, intervalCount);
    
    return 0;
}

