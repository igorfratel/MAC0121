#ifndef __BOARDMANIPULATION_H__
#define __BOARDMANIPULATION_H__

#include "structs.h"
#define N 14

/*Receives coordinates 0 <= i < N and 0 <= j < N and prints them.*/
void printMove(int i, int j);

/*Receives a NxN cell board and the player's color ('p' or 'b').
 *Fills each cell's "color" with '-' and each cell's "score" with 0, then
 *lets all cells know where are their neighbors 
 *(through the adj1...adj6 pointers).
 *Finally, gives a special score to the preferred starting move,
 *given the player's color.*/
void fillBoard(cell board[N][N], char color);

/*Receives a NxN cell board and sets the score of every empty cell to 0,
 *where an empty cell is a cell containing '-' instead of 'p' or 'b' in its
 *color component.*/
void wipeBoardEvaluation(cell board[N][N]);

/*Receives a NxN cell board and prints it to the stderr.*/
void printBoard(cell board[N][N]);

/*Receives a NxN cell board, the coordinates 0 <= i < N and 0 <= j < N and
 *the player's color ('p' or 'b').
 *Marks the cell board[i][j] as occupied by a piece of the specified color and,
 *if the cell is a new link, adds it to the main chain.*/
void makeMove(cell board[N][N], int i, int j, char move_color, char my_color,
              link *first_link);

/*Receives a NxN cell board and the coordinates 0 <= i < N and 0 <= j < N.
 *Returns 1 if the move to (i, j) is valid, -1 if the move is within the bounds
 *of the table but the specified cell is already filled and 0 otherwise.*/
int checkMove(cell board[N][N], int i, int j);

/*Receives a NxN cell board.
 *Returns 1 if the white player has won the game and 0 otherwise.
 *Winning the game is defined as having a chain of connected cells
 *of the same color spanning from two opposite sides of the board.
 *White must span from line 0 to line 13.*/
int hasWonWhite(cell board[N][N]);

/*Receives a NxN cell board.
 *Returns 1 if the black player has won the game and 0 otherwise.
 *Winning the game is defined as having a chain of connected cells
 *of the same color spanning from two opposite sides of the board.
 *Black must span from column 0 to column 13.*/
int hasWonBlack(cell board[N][N]);

/*Receives a NxN cell board and the coordinates 0 <= i < N and 0 <= j < N.
 *Decides if it is best to apply the pie rule on the opponent's move (i, j)
 *Returns 1 if the pie rule is to be applied and 0 otherwise*/
int pieRule(int i, int j);

#endif