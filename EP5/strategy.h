#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "structs.h"
#define N 14

/*Receives a NxN cell board, the player's color ('p' or 'b'), the opponent's color
 *('p' or 'b') and a pointer to a link (the first link of the chain).
 *Searches for a cell that forms a bridge with the last element of the chain.
 *If not able, discards the chain and tries to form a new one from the borders.
 *If also not able, returns NULL.*/
cell *findNextLink(cell board[N][N], char my_color, char opponent_color, link *first_link);

/*Receives a pointer to a link (the first link of the chain), 
 *the player's color ('p' or 'b')and the opponent's color ('p' or 'b').
 *Checks if all the bridges of the chain are still bridges.
 *If a bridge is not valid anymore, returns it's first link.
 *If all the bridges are valid, returns NULL.*/
link *checkBridges(link *first_link, char my_color, char opponent_color);

/*Receives a NxN cell board, the player's color ('p' or 'b')
 *the opponent's color ('p' or 'b') and a pointer to a link (first of the chain).
 *Verifies the cells across the board and gives them scores based on
 *certain criteria (see report).*/
void evaluateBoard(cell board[N][N], char my_color, char opponent_color, link *first_link);

/*Receives a NxN cell board, the player's color ('p' or 'b'), 
 *the opponent's color ('p' or 'b') and a pointer to a link (first of the chain).
 *Calls evaluateBoard, finds a cell with the highest score in the board and returns it.*/
cell chooseMove(cell board[N][N], char my_color, char opponent_color, link *first_link);

#endif