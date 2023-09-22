/* Andronache Madalina-Georgiana - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// initializeaza coada
Queue *initQ(void) {
    Queue *q = NULL;
    q = (Queue *)malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;

    return q;
}

// introducere elementul de tip nod al arborelui in coada
void enqueue(Queue **q, Node *data) {
    Queue *k = *q;
    Node_q *newNode = (Node_q *)malloc(sizeof(Node_q));

    newNode->data = data;
    newNode->next = NULL;

    if (!k->first) {
        k->first = newNode;
    }

    if (k->last) {
        k->last->next = newNode;
    }

    k->last = newNode;
}

// scoatere elementul de tip nod al arborelui din coada
Node *dequeue(Queue **q) {
    Queue *k = *q;
    Node_q *ptr = k->first;
    Node *value = NULL;

    if (ptr) {
        k->first = k->first->next;
        value = ptr->data;
        free(ptr);
        ptr = NULL;
    }

    if (!k->first) {
        k->last = NULL;
    }

    return value;
}

// scrie in fisierul binar fout, parcurgerea pe nivel a arborelui pornind
// din radacina acestuia
void bfs(Node *root, FILE *fout) {
    int i;
    Node *node;
    Queue *q = initQ();

    // adaugam radacina in coada
    enqueue(&q, root);
    
    while (q->first) {
        node = dequeue(&q);

        // scriem tipul nodului: 0 sau 1
        fwrite(&(node->type), sizeof(unsigned char), 1, fout);

        // daca nodul este terminal scriem valorile RGB corespunzatoare
        if (node->type == 1) {
            fwrite(&(node->data.red), sizeof(unsigned char), 1, fout);
            fwrite(&(node->data.green), sizeof(unsigned char), 1, fout);
            fwrite(&(node->data.blue), sizeof(unsigned char), 1, fout);
        }
        
        for (i = 0; i < 4; i++) {
            if (node->area[i]) {
                enqueue(&q, node->area[i]);
            }
        }
    }

    // eliberam memoria pentru coada creata
    free(q);
}
