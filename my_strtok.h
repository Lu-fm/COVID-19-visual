#ifndef MY_STRTOK_H
#define MY_STRTOK_H

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

/*
*Function: my_strtok()
*Usage: string = my_strtok(str, delim);
*---------------------------------------------
*When you call this function in the first time, 
*the function will seek for the delimiter and
*return the token seperated from the str. After
*the first time, you should use NULL to replace str.
*if two delimiters are next to each other, it will 
*return "0". When the str come to an end, it will 
*return NULL;

*Example:
    char str[] = "this,is,,an,example";
    char delim[] = ",";
    char *token;
    token = my_strtok(str, delim);
    while(token != NULL)
    {
        printf("%s\n", token);
        token = my_strtok(NULL, delim);
    }

*Output:
    this
    is
    0
    an
    example
*/

char *my_strtok(char *str, const char *delim);

#endif