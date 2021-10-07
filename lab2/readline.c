#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int pos = 0, length = 0;
char letter;

int read_line (char* str)
{
    if (fgets(str, 50, stdin))
    {
        length = strlen(str);
        if (length == 1)
            return -1;
        pos += length;
        if (str[length - 1] == '\n')
            length--;
        for (int i = 0; i < length; i++)
        {
            if (str[i] < '0' || str[i] > '9')
                return -1;
        }
        return 0;
    }
    else
        return -2;
    return 0;
}
