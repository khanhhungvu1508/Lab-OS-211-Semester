#include "factorial.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

char* factorial (const int aNumber)
{
    char *res = malloc(SIZE * sizeof(char));
    res[0] = '1';
    int resSize = 1, carry = 0;
    for (int i = 2; i <= aNumber; i++)
    {
        for (int j = 0; j < resSize; j++)
        {
            int prod = (res[j] - '0') * i + carry;
            res[j] = prod % 10 + '0';
            carry = prod / 10;
        }
        while (carry != 0) 
        {
            res[resSize] = carry % 10 + '0';
            carry /= 10;
            resSize++;
        }
    }
    res[resSize] = '\0';
    for (int i = 0; i < resSize / 2; i++)
    {
        char tmp = res[i];
        res[i] = res[resSize - 1 - i];
        res[resSize - 1 - i] = tmp;
    }
    return res;
}
