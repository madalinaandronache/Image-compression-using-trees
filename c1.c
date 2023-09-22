/* Andronache Madalina-Georgiana - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// creaza un nod nou al arborelui si aloca memorie pentru acesta
Node *newNode(void) {
    int i;

    Node *node = (Node *)malloc(sizeof(Node));
    node->type = 1;

    node->data.red = 0;
    node->data.green = 0;
    node->data.blue = 0;

    for (i = 0; i < 4; i++) {
        node->area[i] = NULL;
    }

    return node;
}

// citirea datelor din fisierul PPM
Pixel **read(int *size, FILE *fin) {
    int i, j, maxVal, dimension;
    char type[3];

    // citim tipul fisierului
    fgets(type, 3, fin);
    fseek(fin, 1, SEEK_CUR);

    // citim dimensiunile imaginii
    fscanf(fin, "%d\n%d\n", &dimension, &dimension);
    *size = dimension;

    // citim valoarea maximă a culorilor
    fscanf(fin, "%d", &maxVal);

    fseek(fin, 1, SEEK_CUR);

    Pixel **image = (Pixel **)malloc(dimension * sizeof(Pixel *));

    for (i = 0; i < dimension; i++) {
        image[i] = (Pixel *)malloc(dimension * sizeof(Pixel));
    }

    // citim maricea de pixeli si valorile RGB a fiecarui pixel
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            fread(&(image[i][j].red), sizeof(unsigned char), 1, fin);
            fread(&(image[i][j].green), sizeof(unsigned char), 1, fin);
            fread(&(image[i][j].blue), sizeof(unsigned char), 1, fin);
        }
    }

    return image;
}

// calculeaza scorul simiditatii pentru blocul care porneste de la coordonatele
// x si y si are dimensiunea size si returneaza prin intermediul parametrilor
// red_value, green_value si blue_value culoarea medie a blocului
int evaluate(Pixel **image, int x, int y, int size, int factor, int *red_value,
             int *green_value, int *blue_value) {
    int i, j;
    unsigned long long red = 0, green = 0, blue = 0, mean = 0;

    for (i = x; i < x + size; i++) {
        for (j = y; j < y + size; j++) {
            red += image[i][j].red;
            green += image[i][j].green;
            blue += image[i][j].blue;
        }
    }

    red = red / (size * size);
    blue = blue / (size * size);
    green = green / (size * size);

    for (i = x; i < x + size; i++) {
        for (j = y; j < y + size; j++) {
            mean += (red - image[i][j].red) * (red - image[i][j].red);
            mean += (green - image[i][j].green) * (green - image[i][j].green);
            mean += (blue - image[i][j].blue) * (blue - image[i][j].blue);
        }
    }

    mean = mean / (3 * size * size);

    if (mean <= (unsigned long long)factor) {
        *red_value = red;
        *green_value = green;
        *blue_value = blue;
        return 1;
    } else {
        return 0;
    }
}

// construieste recursiv arborele, verificand daca rezultatul functiei evaluate
// este 1, insemnand ca nodul este terminal, altfel, evaluand fiecare bloc
// corespunzator celor 4 copii ai nodului
void complete(Node **node, Pixel **image, int x, int y, int size, int factor) {
    int i, new_size, red, green, blue;
    Node *current = *node;

    if (evaluate(image, x, y, size, factor, &red, &green, &blue) == 1) {
        current->type = 1;
        current->data.red = red;
        current->data.green = green;
        current->data.blue = blue;

    } else {
        new_size = size / 2;

        current->type = 0;
        for (i = 0; i < 4; i++) {
            current->area[i] = newNode();
        }

        complete(&(current->area[0]), image, x, y, new_size, factor);
        complete(&(current->area[1]), image, x, y + new_size, new_size, factor);
        complete(&(current->area[2]), image, x + new_size, y + new_size,
                 new_size, factor);
        complete(&(current->area[3]), image, x + new_size, y, new_size, factor);
    }
}

// functia returneaza numarul de niveluri ale arborelui
int levels(Node *node) {
    int i, Max = 0;

    if (node == NULL) {
        return 0;
    } else if (node->type == 1) {
        return 1;
    } else {
        for (i = 0; i < 4; i++) {
            if (levels(node->area[i]) > Max) {
                Max = levels(node->area[i]);
            }
        }
        return Max + 1;
    }
}

// functia returneaza primul nivel unde se gaseste un nod terminal
int min_level(Node *node) {
    int i, current, Min = 0;

    if (node == NULL) {
        return -1;
    } else if (node->type == 1) {
        return 1;
    } else {
        for (i = 0; i < 4; i++) {
            current = min_level(node->area[i]);
            if (current > 0) {
                if(current < Min || Min == 0){
                    Min = current;
                }
            }
        }

        if (Min != 0) {
            return Min + 1;
        } else {
            return Min;
        }
    }
}

// returneaza numarul de blocuri din imagine pentru care scorul similitudinii
// este mai mic sau egal decat factorul furnizat
int blocks(Node *node) {
    int i, nr = 0;

    if (node == NULL) {
        return 0;
    } else if (node->type == 1) {
        return 1;
    } else {
        for (i = 0; i < 4; i++) {
            nr += blocks(node->area[i]);
        }
        return nr;
    }
}

// returneaza dimensiunea laturii patratului corespunzatoare nodului
// terminal de pe cel mai mic nivel
int max_dimension(int dimension, int levels) {
    int i;

    for (i = 0; i < levels - 1; i++) {
        dimension /= 2;
    }

    return dimension;
}
