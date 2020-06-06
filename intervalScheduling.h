#ifndef INTERVALSCHEDULING_H
#define INTERVALSCHEDULING_H
#include "IntervalListNode.h"
#include "HeapNode.h"

IntervalListNode* getOptimalSchedule(HeapNode** intervalScheduleHeapNode, int size);

#endif
