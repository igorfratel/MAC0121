#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct adjacent {
    int i, j; /*line and column, respectively.*/
    int score; 
    char color;
    struct adjacent *neighbors[6];
} cell;

typedef struct node {
    cell *data; 
    cell *upper_bridge;
    cell *lower_bridge;
    struct node *next;
} link;

typedef struct {
    cell *v;
    int size, begin, end;
} queue;

#endif
