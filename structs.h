/* Andronache Madalina-Georgiana - 312CC */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>

// definire structura Pixel
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

// definire nod arbore cuaternal
typedef struct Node {
    Pixel data;
    unsigned char type;  
    struct Node *area[4];
} Node;

// definire nod coada
typedef struct Node_q {
    Node *data;
    struct Node_q *next;
} Node_q;

// definire structura coada
typedef struct Queue {
    Node_q *first;
    Node_q *last;
} Queue;


Node *newNode(void);
Node *dequeue(Queue **q);
Node *read_bfs(FILE *fin);

Queue *initQ(void);
Pixel **read(int *size, FILE *fin);

void bfs(Node *root, FILE *fout);
void enqueue(Queue **q, Node *data);
void fillImage(Node *node, int x, int y, int size, Pixel **image);
void createPPM(FILE *fout, Pixel **image, int dimension);
void complete(Node **node, Pixel **image, int x, int y, int size, int factor);

int levels(Node *node);
int min_level(Node *node);
int blocks(Node *node);
int max_dimension(int dimension, int levels);
int evaluate(Pixel **image, int x, int y, int size, int factor, int *red_value,
             int *green_value, int *blue_value);

#endif
