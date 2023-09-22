/* Andronache Madalina-Georgiana - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// elibereaza recursiv nodurile arborelui
void freeTree(Node *node) {
    int i;
    if (node == NULL) {
        return;
    } else {
        for (i = 0; i < 4; i++) {
            freeTree(node->area[i]);
        }
        free(node);
    }
}

// rezolvarea cerintei 1
void resolve_C1(int factor, FILE *fin, FILE *fout) {
    int i, dimension;

    Pixel **image = read(&dimension, fin);
    Node *root = newNode();

    // construirea arborelui pornind din radacina
    complete(&root, image, 0, 0, dimension, factor);

    fprintf(fout, "%d\n%d\n%d\n", levels(root), blocks(root),
            max_dimension(dimension, min_level(root)));

    for (i = 0; i < dimension; i++) {
        free(image[i]);
    }
    free(image);
    freeTree(root);
}

// rezolvarea cerintei 2
void resolve_C2(int factor, FILE *fin, FILE *fout) {
    int i, dimension;
    unsigned int dimension2;

    Pixel **image = read(&dimension, fin);
    Node *root = newNode();

    // construirea arborelui pornind din radacina
    complete(&root, image, 0, 0, dimension, factor);

    dimension2 = dimension;
    fwrite(&dimension2, sizeof(unsigned int), 1, fout);

    // compresia imaginii PPM
    bfs(root, fout);

    for (i = 0; i < dimension; i++) {
        free(image[i]);
    }
    free(image);
    freeTree(root);
}

// rezolvarea cerintei 3
void resolve_D(FILE *fin, FILE *fout) {
    int i, dimension;
    fread(&dimension, sizeof(int), 1, fin);

    Node *root = read_bfs(fin);

    Pixel **image = (Pixel **)malloc(dimension * sizeof(Pixel *));
    for (i = 0; i < dimension; i++) {
        image[i] = (Pixel *)malloc(dimension * sizeof(Pixel));
    }

    fillImage(root, 0, 0, dimension, image);

    // decompresia imaginii PPM
    createPPM(fout, image, dimension);

    for (i = 0; i < dimension; i++) {
        free(image[i]);
    }
    free(image);
    freeTree(root);
}

int main(int argc, char const *argv[]) {
    FILE *fin, *fout;
    int factor;

    if (argc < 3 || argc > 5) {
        printf("Numarul de argumente este incorect!\n");
        return 1;
    }

    if (strcmp(argv[1], "-c1") == 0) {
        factor = atoi(argv[2]);
        fin = fopen(argv[3], "rb");
        fout = fopen(argv[4], "w");

        resolve_C1(factor, fin, fout);
    } else if (strcmp(argv[1], "-c2") == 0) {
        factor = atoi(argv[2]);
        fin = fopen(argv[3], "rb");
        fout = fopen(argv[4], "wb");

        resolve_C2(factor, fin, fout);
    } else if (strcmp(argv[1], "-d") == 0) {
        fin = fopen(argv[2], "rb");
        fout = fopen(argv[3], "wb");

        resolve_D(fin, fout);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}