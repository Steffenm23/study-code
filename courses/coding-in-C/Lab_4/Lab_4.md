/*
 * File: main.c
 * Description: Palindrome Detective
 */

 #include <stdio.h>
 #include <string.h>

 int string_as_input(char string[], char name2[]) 
 {
    *(string + 1) = 'c';
    return 0;
    
 }
 int main() 
 {
    char name[] = ("Curly bird catches the worm");
    char *p_name = &name;
    printf("\n%s", name);
    printf("\n%s", p_name );

    *p_name = 'E';
    *(p_name + 1) = 'a';
    
    char name2[] = ("AAtions speak louder than words");

    return 0;
 }