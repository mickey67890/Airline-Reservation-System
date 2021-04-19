/**
 *  minPriorityQueue.h
 *
 *  Header file defining the operations that one can
 *  do on a minimum priority queue. The elements of
 *  the list are pointers to structures. We also need to
 *  provide a comparison function during the initialization.
 *
 *  Created by Sally Goldin, 3 February for CPE113
 *
 */
/*
 *	Modified with permission by [Chayut Surathachaipong] on [19th April 2020]. Made the following changes:
 *	add a sort arguments on compare pointer to funtion, dequeueMin,
 *	queueMinInit and findMinimum fumctions.
 */
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

/**
 * Add a data item to the queue (end of the list)
 * Arguments:
 *   data      -   Pointer to string we want to add to queue   
 * Returns 1 if successful, 0 if we have run out of space.
 */
int enqueueMin(void* data);

/** Get the next item in the queue. This is the minimum 
 * element as defined by applying the compareFunction. 
 * Also removes that item from the queue.
 * Added argument - sort - the selected sorting criteria.
 * @return the data stored in the minimum item or  NULL if the queue is empty.
 */
void* dequeueMin(int sort);

/* Find out how many items are currently in the queue.
 * Return number of items in the queue (could be zero)
 */
int queueMinSize();

/** Clear so we can reuse, and reinitialize 
 * Added argument - sort - the selected sorting criteria.
 */
void queueMinInit(int (*compareFunction)(void* data1, void* data2,int sort));


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE QUEUE **/
void queueMinDebug();

#endif
