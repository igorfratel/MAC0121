#include "queue.h"
#include <stdlib.h>

queue *createQueue()
{
    queue *my_queue;
    my_queue = malloc(sizeof(queue));
    my_queue->v = malloc(QUEUE_SIZE * sizeof(cell));
    my_queue->begin = 0;
    my_queue->end = 0;
    my_queue->size = QUEUE_SIZE;
    return my_queue;
}

void reallocQueue(queue *my_queue)
{
    cell *aux_pointer = realloc(my_queue->v, 2*(my_queue->size) * sizeof(cell));
    if (aux_pointer == NULL) {       
        destroyQueue(my_queue);
        exit(0);
    }
    my_queue->v = aux_pointer;
    my_queue->size *= 2;
}

int isEmptyQueue(queue my_queue)
{
    return my_queue.begin == my_queue.end;
}

void pushQueue(queue *my_queue, cell my_cell)
{
    if ((my_queue->end + 1) % my_queue->size == my_queue->begin)
        reallocQueue(my_queue);
    my_queue->v[my_queue->end] = my_cell;
    my_queue->end = (my_queue->end + 1) % my_queue->size;
}

cell popQueue(queue *my_queue)
{
    cell my_cell;
    my_cell = my_queue->v[my_queue->begin];
    my_queue->begin = (my_queue->begin + 1) % my_queue->size;
    return my_cell;
}

void resetQueue(queue *my_queue)
{
    while (!isEmptyQueue(*my_queue))
        popQueue(my_queue);
}

void destroyQueue(queue *my_queue)
{
    free(my_queue->v);
    free(my_queue);
}