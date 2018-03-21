#include <stdlib.h>
#include "strategy.h"
#include "boardManipulation.h"
#include "queue.h"
#include "linkedList.h"

cell *findNextLink(cell board[N][N], char my_color, char opponent_color, link *first_link)
{
    int i, j;
    link *last_link;
    for (last_link = first_link; last_link->next != NULL; last_link = last_link->next);
    if (my_color == 'b') {
        if (last_link->data->neighbors[4] && last_link->data->neighbors[4]->color != opponent_color &&
            last_link->data->neighbors[5] && last_link->data->neighbors[5]->color != opponent_color &&
            last_link->data->neighbors[4]->i + 1 < N &&
            board[last_link->data->neighbors[4]->i+1][last_link->data->neighbors[4]->j].color == '-')
            return &board[last_link->data->neighbors[4]->i+1][last_link->data->neighbors[4]->j];
        else if (last_link->data->neighbors[3] && last_link->data->neighbors[3]->color != opponent_color &&
                 last_link->data->neighbors[4] && last_link->data->neighbors[4]->color != opponent_color &&
                 last_link->data->neighbors[4]->j - 1 >= 0 &&
                 board[last_link->data->neighbors[3]->i+1][last_link->data->neighbors[3]->j-1].color == '-')
            return &board[last_link->data->neighbors[3]->i+1][last_link->data->neighbors[3]->j-1];
        else if (last_link->data->neighbors[0] && last_link->data->neighbors[0]->color != opponent_color &&
                 last_link->data->neighbors[5] && last_link->data->neighbors[5]->color != opponent_color &&
                 last_link->data->neighbors[0]->j + 1 < N &&
                 board[last_link->data->neighbors[5]->i][last_link->data->neighbors[5]->j+1].color == '-')
            return &board[last_link->data->neighbors[0]->i+1][last_link->data->neighbors[0]->j];
        else {
            destroyLinkedList(first_link);
            for (j = 11; j >= 0; j--)
                if (board[0][j].color == '-')
                    return &board[0][j];
        }
    }
    else {
        if (last_link->data->neighbors[0] != NULL && last_link->data->neighbors[0]->color != opponent_color &&
            last_link->data->neighbors[1] != NULL && last_link->data->neighbors[1]->color != opponent_color &&
            last_link->data->neighbors[1]->j + 1 < N &&
            board[last_link->data->neighbors[1]->i][last_link->data->neighbors[1]->j+1].color == '-')
            return &board[last_link->data->neighbors[1]->i][last_link->data->neighbors[1]->j+1];
        else if (last_link->data->neighbors[0] != NULL && last_link->data->neighbors[0]->color != opponent_color &&
                 last_link->data->neighbors[5] != NULL && last_link->data->neighbors[5]->color != opponent_color &&
                 last_link->data->neighbors[0]->i + 1 < N &&
                 board[last_link->data->neighbors[5]->i][last_link->data->neighbors[5]->j+1].color == '-')
            return &board[last_link->data->neighbors[5]->i][last_link->data->neighbors[5]->j+1];
        else if (last_link->data->neighbors[4] != NULL && last_link->data->neighbors[4]->color != opponent_color &&
                 last_link->data->neighbors[5] != NULL && last_link->data->neighbors[5]->color != opponent_color &&
                 last_link->data->neighbors[4]->i + 1 < N &&
                 board[last_link->data->neighbors[4]->i+1][last_link->data->neighbors[4]->j].color == '-')
            return &board[last_link->data->neighbors[4]->i+1][last_link->data->neighbors[4]->j];
        else if (last_link->data->neighbors[1] != NULL && last_link->data->neighbors[1]->color != opponent_color &&
                 last_link->data->neighbors[2] != NULL && last_link->data->neighbors[2]->color != opponent_color &&
                 last_link->data->neighbors[1]->i - 1 >= 0 &&
                 board[last_link->data->neighbors[1]->i-1][last_link->data->neighbors[1]->j].color == '-')
            return &board[last_link->data->neighbors[1]->i-1][last_link->data->neighbors[1]->j];   
        else {
            destroyLinkedList(first_link);
            for (i = 13; i >= 0; i--)
                if (board[i][0].color == '-')
                    return &board[i][0];
        }
    }
    return NULL;
}
link *checkBridges(link *first_link, char my_color, char opponent_color)
{
    link *p;
    for (p = first_link; p != NULL && p->next != NULL; p = p->next) {
        if (p->upper_bridge != NULL && p->upper_bridge->color != my_color && p->lower_bridge->color != my_color) {
            if (p->upper_bridge->color == opponent_color || p->lower_bridge->color == opponent_color)
                return p;
        }
    }
    return NULL;
}

void evaluateBoard(cell board[N][N], char my_color, char opponent_color, link *first_link)
{
    int i, j;
    link *aux_link_ptr = NULL;
    link *last_link = NULL;
    cell *aux_cell;
    wipeBoardEvaluation(board);
    if (first_link->data != NULL) {
        for (last_link = first_link; last_link->next != NULL; last_link = last_link->next);
        aux_link_ptr = checkBridges(first_link, my_color, opponent_color);
    }
    if (aux_link_ptr) {
        if (aux_link_ptr->upper_bridge->color == opponent_color && aux_link_ptr->lower_bridge->color == '-')
            board[aux_link_ptr->lower_bridge->i][aux_link_ptr->lower_bridge->j].score = 3;
        else if (aux_link_ptr->lower_bridge->color == opponent_color && aux_link_ptr->upper_bridge->color == '-')
            board[aux_link_ptr->upper_bridge->i][aux_link_ptr->upper_bridge->j].score = 3;
        else {
            aux_cell = findNextLink(board, my_color, opponent_color, first_link);
            if (aux_cell)
                aux_cell->score = 2;
        }
    }
    else {
        if (my_color == 'p' && last_link->data->j == 12) {
            if (board[last_link->data->i][last_link->data->j+1].color == '-') {
                board[last_link->data->i][last_link->data->j+1].score = 3;
            }
            else if (board[last_link->data->i-1][last_link->data->j+1].color == '-')
                board[last_link->data->i-1][last_link->data->j+1].score = 3;
            else if (board[last_link->data->i][last_link->data->j+1].color == my_color ||
                    board[last_link->data->i-1][last_link->data->j+1].color == my_color) {
                while (board[first_link->lower_bridge->i][first_link->lower_bridge->j].color == my_color ||
                    board[first_link->upper_bridge->i][first_link->upper_bridge->j].color == my_color) {
                    aux_link_ptr = first_link;
                    first_link = first_link->next;
                }
                board[first_link->upper_bridge->i][first_link->upper_bridge->j].score = 3;
            }
        }
        else if (my_color == 'b' && last_link->data->i == 12) {
            if (board[last_link->data->i+1][last_link->data->j].color == '-') {
                board[last_link->data->i+1][last_link->data->j].score = 3;
            }
            else if (board[last_link->data->i+1][last_link->data->j-1].color == '-')
                board[last_link->data->i+1][last_link->data->j-1].score = 3;
            else if (board[last_link->data->i+1][last_link->data->j].color == my_color ||
                    board[last_link->data->i+1][last_link->data->j-1].color == my_color) {
                while (board[first_link->lower_bridge->i][first_link->lower_bridge->j].color == my_color ||
                    board[first_link->upper_bridge->i][first_link->upper_bridge->j].color == my_color) {
                    aux_link_ptr = first_link;
                    first_link = first_link->next;
                }
                board[first_link->upper_bridge->i][first_link->upper_bridge->j].score = 3;
            }
        }
        else { 
            aux_cell = findNextLink(board, my_color, opponent_color, first_link);
            if (aux_cell)
                aux_cell->score = 2;
        }
    }
    for (i = 2, j = 2; i < N - 2; i++) {
        if (opponent_color == 'p') {
            if (board[i][j].color == opponent_color) {
                if (board[i-1][j+2].color == '-')    
                    board[i-1][j+2].score = 1;
                if (board[i+1][j+1].color == '-')    
                    board[i+1][j+1].score = 1;
            }
            else if (board[i][j].color == '-') {
                if (board[i-1][j+2].color == opponent_color)    
                    board[i][j].score = 3;
                if (board[i+1][j+1].color == opponent_color)    
                    board[i][j].score = 3;
                if (board[i][j+1].color == opponent_color)    
                    board[i][j].score = 3;
            }
        }
        else {
            if (board[j][i].color == opponent_color) {
                if (board[j+2][i].color == '-')
                    board[j+2][i].score = 1;
                if (board[j+1][i+1].color == '-')
                    board[j+1][i+1].score = 1;
                if (board[j+1][i-2].color == '-')
                    board[j+1][i-2].score = 1;
            }
            else if (board[j][i].color == '-') {
                if (board[j+2][i].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j+1][i+1].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j+1][i-2].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j+1][i].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j+1][i-1].color == opponent_color)
                    board[j][i].score = 3;
            }
        }
    }
    for (i = 11, j = 11; i >= 2; i--) {
        if (opponent_color == 'p') {
            if (board[i][j].color == opponent_color){
                if (board[i-1][j-1].color == '-')
                    board[i-1][j-1].score = 1;
                if (board[i+1][j-1].color == '-')    
                    board[i+1][j-1].score = 1;
            }
            else if (board[i][j].color == '-') {
                if (board[i-1][j-1].color == opponent_color)    
                    board[i][j].score = 3;
                if (board[i+1][j-1].color == opponent_color)    
                    board[i][j].score = 3;
                if (board[i][j-1].color == opponent_color)    
                    board[i][j].score = 3;
            }
        }
        else {
            if (board[j][i].color == opponent_color) {
                if (board[j-2][i].color == '-')
                    board[j-2][i].score = 1;
                if (board[j-1][i-1].color == '-')
                    board[j-1][i-1].score = 1;
                if (board[j-1][i+2].color == '-')
                    board[j-1][i+2].score = 1;
            }
            else if (board[i][j].color == '-')
                if (board[j-2][i].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j-1][i-1].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j-1][i+2].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j-1][i].color == opponent_color)
                    board[j][i].score = 3;
                if (board[j-1][i+1].color == opponent_color)
                    board[j][i].score = 3;
        }
    }
}

cell chooseMove(cell board[N][N], char my_color, char opponent_color, link *first_link)
{
    cell temp_cell;
    int i, j;
    if (first_link && first_link->data)
        evaluateBoard(board, my_color, opponent_color, first_link);
    temp_cell.score = -1;
    for (i = 13; i >= 0; i--) {
        for (j = 0; j < N; j++) {
            if (my_color == 'b') {
                if (board[i][j].color == '-' &&
                    board[i][j].score > temp_cell.score) {
                    temp_cell.i = i;
                    temp_cell.j = j;
                    temp_cell.score = board[i][j].score;
                }
            }
            else { 
                if (board[j][i].color == '-' &&
                    board[j][i].score > temp_cell.score) {
                    temp_cell.i = j;
                    temp_cell.j = i;
                    temp_cell.score = board[j][i].score;
                }
            }
        }
    }    
    return temp_cell;
}