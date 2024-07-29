#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void count(bool countLine, bool countWord, bool countChar, FILE *fp, char *filename)
{
    int lines, words, chars;
    lines = words = chars = 0;
    int IN = false;

    int c = getc(fp);
    while (c != EOF)
    {
        chars++;

        if (c == '\n')
        {
            lines++;
        }

        if (c == ' ' || c == '\t' || c == '\n')
        {
            IN = false;
        }
        else if (IN == false)
        {
            words++;
            IN = true;
        }

        c = getc(fp);
    }
    if (countLine == true)
    {
        printf("%d ", lines);
    }
    if (countWord == true)
    {
        printf("%d ", words);
    }
    if (countChar == true)
    {
        printf("%d ", chars);
    }
    printf("%s\n", filename);
}

int main(int argc, char **argv)
{
    int totalFlags = 0;
    struct list *head = NULL;

    bool countLineFlag, countWordFlag, countCharFlag;

    char *fileStack[10];
    int top = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            char *flag = argv[i];
            if (strcmp(flag, "-w") == 0)
            {
                countWordFlag = true;
                totalFlags++;
            }
            else if (strcmp(flag, "-c") == 0)
            {
                countCharFlag = true;
                totalFlags++;
            }
            else if (strcmp(flag, "-l") == 0)
            {
                countLineFlag = true;
                totalFlags++;
            }
            else if (strcmp(flag, "-h") == 0)
            {
                printf("Show help\n");
            }
            else
            {
                printf("Invalid flag: %s\n", flag);
            }
        }
        else
        {
            if (top == 10)
            {
                continue;
            }
            else
            {
                fileStack[top++] = argv[i];
            }
        }
    }

    if (totalFlags == 0)
    {
        countCharFlag = countLineFlag = countWordFlag = true;
    }

    if (top == 0)
    {
        count(countLineFlag, countWordFlag, countCharFlag, stdin, "");
    }
    else
    {
        for (int i = 0; i < top; i++)
        {
            FILE *fp = fopen(fileStack[i], "r");
            if (fp == NULL)
            {
                printf("Error opening file %s", fileStack[i]);
            }
            else
            {
                count(countLineFlag, countWordFlag, countCharFlag, fp, fileStack[i]);
            }
        }
    }

    return 0;
}