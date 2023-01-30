#include "read_string.h"

#include <stdio.h>
#include <stdlib.h>

#define DEF_SIZE 10

char *read_string(int *n) {
    int iter = 1;
    char *string = (char *) malloc(iter * DEF_SIZE * sizeof(char));
    *n = 0;
    char c = 'a';
    while (c != '\n') {
        scanf("%c", &c);

        if (c != '\n') {
            if (*n == iter * DEF_SIZE - 1) {
                iter *= 2;
                char *tmp = (char *) malloc(iter * DEF_SIZE * sizeof(char));
                copy(tmp, string, *n);
                swap_pointers(&tmp, &string);
                free(tmp);
            }
            string[*n] = c;
            *n += 1;
        }
    }
    return string;
}

void copy(char *tmp, const char *string, int n) {
    for (int i = 0; i < n; i++) {
        tmp[i] = string[i];
    }
}

void swap_pointers(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}
