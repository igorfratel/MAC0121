#include <stdio.h>
#include <stdlib.h>
#include "boardManipulation.h"
#include "queue.h"
#include "linkedList.h"

void printMove(int i, int j)
{
    printf("%d %d\n", i, j);
}

void fillBoard(cell board[N][N], char color)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            board[i][j].score = 0;
            board[i][j].color = '-';
            board[i][j].i = i;
            board[i][j].j = j;
            if (j + 1 < N)
                board[i][j].neighbors[0] = &board[i][j+1];
            if (i - 1 >= 0 && j + 1 < N)
                board[i][j].neighbors[1] = &board[i-1][j+1];
            if (i - 1 >= 0)
                board[i][j].neighbors[2] = &board[i-1][j];
            if (j - 1 >= 0)
                board[i][j].neighbors[3] = &board[i][j-1];
            if (i + 1 < N && j - 1 >= 0)
                board[i][j].neighbors[4] = &board[i+1][j-1];
            if (i + 1 < N)
                board[i][j].neighbors[5] = &board[i+1][j];
        }
    }
    if (color == 'p')
        board[10][0].score = 2;
    else
        board[0][7].score = 2;
}

void wipeBoardEvaluation(cell board[N][N])
{

    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (board[i][j].color == '-')
                board[i][j].score = 0;

}

void printBoard(cell board[N][N])
{
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (k = i; k > 0; k--)
            fprintf(stderr, " ");
        for (j = 0; j < N; j++)
            fprintf(stderr, "%c ", board[i][j].color);
        fprintf(stderr, "\n");
    }
}

void makeMove(cell board[N][N], int i, int j, char move_color, char my_color,
              link *first_link)
{
    board[i][j].color = move_color;
    if (board[i][j].score == 2)
        insertLink(board, first_link, &board[i][j]);
    board[i][j].score = -1;
}

int checkMove(cell board[N][N], int i, int j)
{
    if (i >= 0 && i <= 13 && j >= 0 && j <= 13 && board[i][j].color == '-')
        return 1;
    else if (i >= 0 && i <= 13 && j >= 0 && j <= 13 && board[i][j].color != '-')
        return -1;
    else
        return 0;
}

int hasWonWhite(cell board[N][N])
{
    int i, j, k;
    queue *my_queue = createQueue();
    cell aux_cell;
    int visited[N][N];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            visited[i][j] = 0;
    for (i = 0, j = 0; j < N; j++) {
        if (board[i][j].color == 'b') {
            pushQueue(my_queue, board[i][j]);
            visited[i][j] = 1;
            while (!isEmptyQueue(*my_queue)) {
                aux_cell = popQueue(my_queue);
                for (k = 0; k < 6; k++) { 
                    if (aux_cell.neighbors[k] != NULL && 
                        (aux_cell.neighbors[k])->color == 'b' && 
                        !visited[(aux_cell.neighbors[k])->i][(aux_cell.neighbors[k])->j]) {
                        if ((aux_cell.neighbors[k])->i == 13) {
                            destroyQueue(my_queue);
                            return 1;
                        }
                        pushQueue(my_queue, *aux_cell.neighbors[k]);
                        visited[(aux_cell.neighbors[k])->i][(aux_cell.neighbors[k])->j] = 1;
                    }
                }
            }
        }
    }
    destroyQueue(my_queue);
    return 0;
}

int hasWonBlack(cell board[N][N])
{
    int i, j, k;
    queue *my_queue = createQueue();
    cell aux_cell;
    int visited[N][N];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            visited[i][j] = 0;
    for (i = 0, j = 0; i < N; i++) {
        if (board[i][j].color == 'p') {
            pushQueue(my_queue, board[i][j]);
            visited[i][j] = 1;
            while (!isEmptyQueue(*my_queue)) {
                aux_cell = popQueue(my_queue);
                for (k = 0; k < 6; k++) { 
                    if (aux_cell.neighbors[k] != NULL &&
                        (aux_cell.neighbors[k])->color == 'p' &&
                        !visited[(aux_cell.neighbors[k])->i][(aux_cell.neighbors[k])->j]) {
                        if ((aux_cell.neighbors[k])->j == 13) {
                            destroyQueue(my_queue);
                            return 1;
                        }
                        pushQueue(my_queue, *aux_cell.neighbors[k]);
                        visited[(aux_cell.neighbors[k])->i][(aux_cell.neighbors[k])->j] = 1;
                    }
                }
            }
        }
    }
    destroyQueue(my_queue);
    return 0;
}

int pieRule(int i, int j)
{
    if ((i == 0 && j == 0) || (i == 13 && j == 13))
        return 0;
    return 1;
}