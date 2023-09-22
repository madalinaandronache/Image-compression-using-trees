/* Andronache Madalina-Georgiana - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// construirea arborelui cuaternal corespunzator parcurgerii pe nivel a 
// arborelui din fisierul binar fin
Node *read_bfs(FILE *fin) {
    int i;
    unsigned char type;
    Node *node, *root;

    Queue *q = initQ();

    root = newNode();
    enqueue(&q, root);

    while (q->first) {
        node = dequeue(&q);

        // se citeste tipul nodului
        fread(&(node->type), sizeof(unsigned char), 1, fin);

        // daca nodul este terminal se citesc valorile RGB corespunzatoare,
        // altfel se creaza cei 4 copii ai sai si se adauga in coada
        if (node->type == 1) {
            fread(&(node->data.red), sizeof(unsigned char), 1, fin);
            fread(&(node->data.green), sizeof(unsigned char), 1, fin);
            fread(&(node->data.blue), sizeof(unsigned char), 1, fin);
        } else {
            for (i = 0; i < 4; i++) {
                node->area[i] = newNode();
                enqueue(&q, node->area[i]);
            }
        }
    }

    // eliberam memoria pentru coada creata
    free(q);

    return root;
}

// construirea matricei de pixeli rezultata din arborele cuaternal
void fillImage(Node *node, int x, int y, int size, Pixel **image) {
    int i, j, new_size;

    if (node->type == 1) {
        // nodul este de tip frunza, completam zona cu valorile RGB din nodul
        // curent
        for (i = x; i < x + size; i++) {
            for (j = y; j < y + size; j++) {
                image[i][j].red = node->data.red;
                image[i][j].green = node->data.green;
                image[i][j].blue = node->data.blue;
            }
        }
    } else {
        // nodul este de tip intern, parcurgem recursiv toti copiii nodului
        new_size = size / 2;

        fillImage(node->area[0], x, y, new_size, image);
        fillImage(node->area[1], x, y + new_size, new_size, image);
        fillImage(node->area[2], x + new_size, y + new_size, new_size, image);
        fillImage(node->area[3], x + new_size, y, new_size, image);
    }
}

// crearea imagini PPM corespunzatoare matricei de pixeli
void createPPM(FILE *fout, Pixel **image, int dimension) {
    int i = 0, j = 0;

    fprintf(fout, "P6\n");
    fprintf(fout, "%d %d\n", dimension, dimension);
    fprintf(fout, "255\n");

    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            fwrite(&(image[i][j].red), sizeof(unsigned char), 1, fout);
            fwrite(&(image[i][j].green), sizeof(unsigned char), 1, fout);
            fwrite(&(image[i][j].blue), sizeof(unsigned char), 1, fout);
        }
    }
}
