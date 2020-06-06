/*
getOptimalSchedule:
This function takes in an array of IntervalScheduleHeapNode elements and an integer representing the number of elements in the array
and returns the head of an IntervalListNode linked list of the optimal intervals for a single partition.



   */

#include <stdbool.h>
#include "GenHeap.h"
#include "IntervalListNode.h"
#include "HeapNode.h"

IntervalListNode* getOptimalSchedule(HeapNode** intervalScheduleHeapNodeArray, int size)
{
    //sort input intervals in ascending order by their finish time
    HeapNode** sortedHeapNodeArray = heapSort(intervalScheduleHeapNodeArray, size);
    //interval with earliest finish time becomes first interval in partition
    IntervalListNode* head = intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedHeapNodeArray[0]), getEndFromIntervalHeapNode(sortedHeapNodeArray[0]));
    //for all remaining elements in sorted array
    for(int i = 1; i<size; i++)
    {
        IntervalListNode* current = intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedHeapNodeArray[i]), getEndFromIntervalHeapNode(sortedHeapNodeArray[i]));
        //if current element in sorted list has start time >= to finish time of last node in list, append current element to list. 
        if (intervalListNodeIsCompatible(intervalListGetLast(head), current))
        {
            intervalListAppend(head, current);
        }
    }
    return head;
}
