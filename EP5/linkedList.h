#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include "structs.h"
#define N 14

/*Receives a NxN cell board, a pointer to a link (first element of the chain),
 *and a pointer to a cell.
 *Inserts a new link to the chain and sets the bridges between them, if there
 *are any. If first_link does not have a cell on its data component, fills
 *the data component with new_cell.*/
void insertLink(cell board[N][N], link *first_link, cell *new_cell);

/*Receives a pointer to a link (first element of the chain).
 *Frees all the memory allocated for the chain, except for first_link,
 *which has all its components set to NULL.*/
void destroyLinkedList(link *first_link);

#endif
