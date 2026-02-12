/*
 * File: Lab5SM.c
 * Description: Section 1: Pointers
 */

#include <stdio.h>

int main(void) {
    int x = 10;
    int *p = &x;
    int **pp = &p;

    // TODO: complete the output statements
    printf("x = %d\n", x);
    printf("x via p = %d\n", *p);
    printf("x via pp = %d\n", **pp);

    int **pp = 42;
    printf("x = %d\n", x);

    return 0;
}