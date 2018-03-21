#include <stdio.h>
#include <stdlib.h>
#include "boardManipulation.h"
#include "strategy.h"
#include "linkedList.h"
#define N 14

cell board[N][N];
link *first_link;

int main(int argc, char *argv[])
{ 
    int i, j, print_mode = 0;
    char my_color, opponent_color;
    cell aux_cell;
    link *first_link = malloc(sizeof(link));
    first_link->data = NULL;
    first_link->next = NULL;
        if (argc < 2 || argc > 3) {
        printf("Error: Wrong number of arguments. "
               "Expected <player_color> or <player_color> <d>\n");
        free(first_link);
        exit(1);
    }
    if (*argv[1] != 'p' && *argv[1] != 'b') {
        printf("Error: Invalid first argument. Expected <p> or <b>\n");
        free(first_link);
        exit(1);
    }
    my_color = *argv[1];
    if (argc == 3) {
        if (*argv[2] != 'd') {
            printf("Error: Invalid second argument. Expected <d>\n");
            free(first_link);
            exit(1);
        }
        print_mode = 1;
    }

    fillBoard(board, my_color);
    /*(Begin) First moves, deals with pie rule*/
    if (my_color == 'b') {
        opponent_color = 'p';
        aux_cell = chooseMove(board, my_color, opponent_color, first_link);
        makeMove(board, aux_cell.i, aux_cell.j, my_color, my_color, first_link);
        printMove(aux_cell.i, aux_cell.j);
        if (print_mode) printBoard(board);
        if (!scanf("%d %d", &i, &j)) exit(1);
        while (checkMove(board, i, j) == 0) {
            printf("Jogada invalida\n");
            if (!scanf("%d %d", &i, &j)) exit(1);
        }
        if (checkMove(board, i, j) == -1) {
            wipeBoardEvaluation(board);
            destroyLinkedList(first_link);
            board[7][0].score = 2;
            my_color = 'p';
            opponent_color = 'b';
        }
        makeMove(board, i, j, opponent_color, my_color, first_link);
    }
    else {
        opponent_color = 'b';
        if (!scanf("%d %d", &i, &j)) exit(1);
        while (checkMove(board, i, j) != 1) {
            printf("Jogada invalida\n");
            if (!scanf("%d %d", &i, &j)) exit(1);
        }
        makeMove(board, i, j, opponent_color, my_color, first_link);
        if (pieRule(i, j)) {
            wipeBoardEvaluation(board);
            printMove(i, j);
            if (print_mode) printBoard(board);
            my_color = 'b';
            opponent_color = 'p';
            board[i][j].score = 2;
            makeMove(board, i, j, my_color, my_color, first_link);
            if (!scanf("%d %d", &i, &j)) exit(1);
            while (checkMove(board, i, j) != 1) {
                printf("Jogada invalida\n");
                if (!scanf("%d %d", &i, &j)) exit(1);
            }
            makeMove(board, i, j, opponent_color, my_color, first_link);
        }
    }   
    /*(End) First moves, deals with pie rule*/
    while (1) {
        aux_cell = chooseMove(board, my_color, opponent_color, first_link);
        makeMove(board, aux_cell.i, aux_cell.j, my_color, my_color, first_link);
        printMove(aux_cell.i, aux_cell.j);
        if (print_mode) printBoard(board);
        if (my_color == 'b' && hasWonWhite(board)) {
            destroyLinkedList(first_link);
            free(first_link);
            printf("branco ganhou\n");
            return 0;
        }
        else if (hasWonBlack(board)) {
            destroyLinkedList(first_link);
            free(first_link);
            printf("preto ganhou\n");
            return 0;
        }
        if (!scanf("%d %d", &i, &j)) exit(1);
        while (checkMove(board, i, j) != 1) {
            printf("Jogada invalida\n");
            if (!scanf("%d %d", &i, &j)) exit(1);
        }
        makeMove(board, i, j, opponent_color, my_color, first_link);
        if (opponent_color == 'b' && hasWonWhite(board)) {
            destroyLinkedList(first_link);
            free(first_link);
            printf("branco ganhou\n");
            return 0;
        }
        else if (hasWonBlack(board)) {
            destroyLinkedList(first_link);
            free(first_link);
            printf("preto ganhou\n");
            return 0;
        }
    }
}