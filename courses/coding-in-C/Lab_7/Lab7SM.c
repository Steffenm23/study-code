#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int Number = 0;
    printf("Geben sie eine Zahl ein: ");
    if (scanf("%d", Number) !=1) {
        printf("Kein zulässiger Wert");
        free(Number);
        return 1;
    }
 int *pNumber = &Number;

    int *pNumber = malloc(sizeof *pNumber);
    if (pNumber == NULL) {
        printf("Speicherallokation fehlgeschlagen\n");
        return 1;
    }

 int *pNumber = calloc(Number, sizeof *pNumber);
    if (pNumber == NULL) {
        printf("Speicherallokation fehlgeschlagen\n");
        return 1;
    }

 for ( int i = 0; i<*pNumber; i++) {
        pNumber[i] = i*i; 
    }

int *pTemp = realloc(pNumber , 2* sizeof pNumber);







}


