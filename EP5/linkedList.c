#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"
#include "boardManipulation.h"

void insertLink(cell board[N][N], link *first_link, cell *new_cell)
{
    link *new_link;
    link *aux_next, *aux_prev;
    if (!first_link->data)
        first_link->data = new_cell;
    else {
        new_link = malloc(sizeof(link));
        new_link->data = new_cell;
        for (aux_next = first_link; aux_next != NULL; aux_prev = aux_next, aux_next = aux_next->next);
        aux_prev->next = new_link;
        new_link->next = aux_next;
        if (aux_prev->data->i - 1 == new_cell->i) {
            aux_prev->upper_bridge = &board[aux_prev->data->i-1][(aux_prev->data)->j+1];
            aux_prev->lower_bridge = &board[aux_prev->data->i][aux_prev->data->j+1];
        }
        else if ((aux_prev->data)->i - 2 == new_cell->i) {
            aux_prev->upper_bridge = &board[aux_prev->data->i-1][aux_prev->data->j];
            aux_prev->lower_bridge = &board[aux_prev->data->i-1][aux_prev->data->j+1];
        }
        else if ((aux_prev->data)->j - 2 == new_cell->j) {
            aux_prev->upper_bridge = &board[aux_prev->data->i][aux_prev->data->j-1];
            aux_prev->lower_bridge = &board[aux_prev->data->i+1][aux_prev->data->j-1];
        }
        else if ((aux_prev->data)->i + 2 == new_cell->i) {
            aux_prev->upper_bridge = &board[aux_prev->data->i+1][aux_prev->data->j];
            aux_prev->lower_bridge = &board[aux_prev->data->i+1][aux_prev->data->j-1];
        }
        else if (aux_prev->data->j + 1 == new_cell->j) {
            aux_prev->upper_bridge = &board[aux_prev->data->i][aux_prev->data->j+1];
            aux_prev->lower_bridge = &board[aux_prev->data->i+1][aux_prev->data->j];
        }
    }
}

void destroyLinkedList(link *first_link)
{
    link *aux_ptr, *aux_ptr_next;
    aux_ptr = first_link->next;
    while (aux_ptr != NULL) {
        aux_ptr_next = aux_ptr->next;
        free(aux_ptr);
        aux_ptr = aux_ptr_next;
    }
    first_link->data = NULL;
    first_link->next = NULL;
    first_link->upper_bridge = NULL;
    first_link->lower_bridge = NULL;
}

