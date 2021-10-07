#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int divideBy2 (char *num)
{
    return ((num[strlen(num) - 1] - '0') % 2 == 0);
}

int divideBy3 (char *num)
{
    int sum = 0;
    for (int i = 0; i < strlen(num); i++)
        sum = (sum + num[i] - '0') % 3;
    return (sum == 0);
}

int divideBy5 (char *num)
{
    return ((num[strlen(num) - 1] - '0') % 5 == 0);
}

int main()
{
    FILE *file = freopen("number.txt", "r", stdin);
    char** num = malloc(100000 * 79 * sizeof(char));
    if (file == NULL)
    {
        printf("Can not open this file!");
        return 0;
    }
    else
    {
        char *tmp = malloc(79 * sizeof(char));
        int n = 0;
        while (fgets(tmp, 79, file))
        {
            int length = strlen(tmp);
            if (tmp[length - 1] == '\n')
                tmp[length - 1] = '\0';
            num[n] = malloc(79 * sizeof(char));
            strcpy(num[n], tmp);
            n++;
        }
        pid_t pid1, pid2;
    	pid1 = fork();
    	int count1 = 0, count2 = 0, count3 = 0;
    	if (pid1 == 0) 
    	{
    		for (int i = 0; i < n; i++)
    			if (divideBy2(num[i]))
    				count1++;
    		printf("%d\n", count1);	
    	}
    	else if (pid1 > 0)
    	{
    		wait(NULL);
    		pid2 = fork();
    		if (pid2 == 0)
    		{
        		for (int i = 0; i < n; i++) 
        			if (divideBy3(num[i]))
        				count2++;
        		printf("%d\n", count2);
    		}
    		else if (pid2 > 0)
    		{
    		    wait(NULL);
    		    for (int i = 0; i < n; i++) 
        			if (divideBy5(num[i]))
        				count3++;
        		printf("%d\n", count3);
    		}
    		else
    		    printf("Error!!!");
    	}
    	else
    		printf("Error!!!");
    }
    return 0;
}
