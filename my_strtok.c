/*------------------------------------------------------------------
*This file includes a function to replace the "strtok" function,
*it can recognize the empty value in .csv file and return "0"
*----------------------------------------------------------------------
*/

#include"my_strtok.h"

char *my_strtok(char *str, const char *delim)
{
    static char *start_ptr, *end_ptr;
    char *token = NULL;
    int token_size = 20;
    const int delim_size = strlen(delim);
    if (str)
        start_ptr = str;
    if (start_ptr && (end_ptr = strstr(start_ptr, delim)) != NULL)
    {
        token_size = end_ptr - start_ptr;
        token = (char *)calloc((token_size + 2) , sizeof(char));
        *end_ptr = '\0';
        if (token_size)
            strcpy_s(token, token_size+2,start_ptr);
        else
            strcpy_s(token,token_size+2, "0");
        start_ptr = end_ptr + delim_size;
    }
    else
        {
            if(start_ptr)
            {
                token = (char *)calloc((sizeof(start_ptr)+4) , sizeof(char));
                strcpy(token,  start_ptr);
                start_ptr = NULL;
            }
        }
    return token;
}
