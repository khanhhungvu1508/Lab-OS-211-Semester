// main.c
#include <stdio.h>
#include "readline.h"
#include "factorial.h"
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
    char *str = (char*) malloc(50 * sizeof(char));
    int returnVal;
    while(1)
    {
        returnVal = read_line(str);
        if (returnVal == -2)
            break;
        if (returnVal == 0)
        {
            int length = strlen(str);
            if (str[length - 1] == '\n')
                length--;
            int number = 0;
            for (int j = 0; j < length; j++)
                number = number * 10 + str[j] - '0';
            printf("%s\n", factorial(number));
        }
        if (returnVal == -1)
            printf("-1\n");
    }
    return 0;
}
