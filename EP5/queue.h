#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "structs.h"
#define QUEUE_SIZE 14

/*Returns a pointer to a queue, with all of its components initialized.*/
queue *createQueue();

/*Receives a pointer to a queue and returns it, but with its component v now
 *twice the original size and still containing the same data.
 *If the memory reallocation fails, frees the memory allocated for the queue
 *and exits the program with an error*/
void reallocQueue(queue *my_queue);

/*Receives a pointer to a queue.
 *Returns 1 if the queue contains no enqueued elements and 0 otherwise.*/
int isEmptyQueue(queue my_queue);

/*Receives a pointer to a queue and a cell.
 *Inserts the cell at the end of the queue.*/
void pushQueue(queue *my_queue, cell my_cell);

/*Receives a pointer to a non-empty queue.
 *Removes the first element of the queue and returns it.*/
cell popQueue(queue *my_queue);

/*Receives a pointer to a queue and removes all of its enqueued elements.*/
void resetQueue(queue *my_queue);

/*Receives a pointer to a queue and frees the space alocated for it.*/
void destroyQueue(queue *my_queue);

#endif