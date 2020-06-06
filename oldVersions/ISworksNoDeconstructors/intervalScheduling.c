#include <stdbool.h>
#include "GenHeap.h"
#include "IntervalListNode.h"
#include "HeapNode.h"

IntervalListNode* getOptimalSchedule(HeapNode** intervalScheduleHeapNodeArray, int size)
{
    HeapNode** sortedHeapNodeArray = heapSort(intervalScheduleHeapNodeArray, size);
    IntervalListNode* head = intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedHeapNodeArray[0]), getEndFromIntervalHeapNode(sortedHeapNodeArray[0]));
    for(int i = 1; i<size; i++)
    {
        IntervalListNode* current = intervalListNodeConstructor(getStartFromIntervalHeapNode(sortedHeapNodeArray[i]), getEndFromIntervalHeapNode(sortedHeapNodeArray[i]));
        if (intervalListNodeIsCompatible(intervalListGetLast(head), current))
        {
            intervalListAppend(head, current);
        }
    }
    return head;
}
