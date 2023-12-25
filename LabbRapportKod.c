#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAT_LEN 100
#define MAX_TEXT_LEN 100

char text[MAX_TEXT_LEN];
char pattern[MAX_PAT_LEN];
int* skip_table;

int horspool_search(char* text, int text_len, char* pattern, int pat_len, int* skip_table, int* op);
void gen_skip_table(int* skip_table, char* pattern);
int NaiveSolution(char* text, char* pattern, int text_len, int pat_len, int* op);

void displayMainMenu()
{
    printf("1)Try horspool with your own text & pattern\n");
    printf("2)Randomized text&pattern, Choose length and position of pattern (beginning,middle,end)\n");
    printf("3)Everything randomized except length\n");
    printf("4)Everything random (pattern may or may not be in text)\n");
    printf("5)Display main menu\n");
    printf("6)Exit\n");
}
//The code below lets the user choose between four options with switch case
//The first option lets the user choose their own text and pattern, The user finds out how many basic operations was performed.
//The second option the text and pattern is generated randomly but the user gets to choose the length, The user also gets to choose wether the pattern ends up in the beginning,middle or end of the text, The user finds out how many basic operations was performed.
//The third option the pattern and text shall be generated randomly but also the length. The user gets the option to choose how many iterations is performed, For every iteration the pattern and the text is generated randomly, The pattern must always be in the text. THe user gets an average on how many critical operations was performed.
//The fourth option is like the third but here the pattern may or may not exist in the text.
int main(int argc, char* argv[])
{
    srand(time(NULL));
    int pos = 0;
    int text_len = 0;
    int pat_len = 0;
    int choice = 0;
    int iterations = 0;
    int position = 0;
    int sum = 0;
    int sumBrute = 0;
    int i = 0;
    int j = 0;
    int critical = 0;

    int critical2 = 0;
    int critical3 = 0;
    int criticalBrute2 = 0;
    int criticalBrute3 = 0;

    int critical4 = 0;
    int critical5 = 0;
    int criticalBrute4 = 0;
    int criticalBrute5 = 0;

    puts("Option 4&5 let you choose how many iterations you desire and based on the result get an average basic operations performed\n");

    displayMainMenu();

    while (1)
    {
        printf("Choose your option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Choose a text: ");
            scanf("%s", text);
            text_len = strlen(text);
            printf("Choose a pattern: ");
            scanf("%s", pattern);
            pat_len = strlen(pattern);
            skip_table = (int*)malloc(sizeof(int) * 256);
            gen_skip_table(skip_table, pattern);
            pos = horspool_search(text, text_len, pattern, pat_len, skip_table, &critical);
            if (pos == -1) puts("Pattern not found in text");
            else printf("Pattern found at pos: %d\n", pos);

            printf("Horspool Basic operations performed: %d\n", critical);
            NaiveSolution(text, pattern, text_len, pat_len, &critical);
            printf("BruteForce Basic operations performed: %d\n", critical);

            printf("\nSkip Table\n");
            printf("----------\n");
            for (int i = 0; i < 256; i++)
            {
                //printf("%3d|", skip_table[i]);
                if (skip_table[i] != pat_len)
                {
                    printf("%c   | %d\n", i, skip_table[i]);
                }
            }
            printf("%c   | %d\n", pattern[pat_len - 1], pat_len);
            printf("*   | %d\n", pat_len);
            printf("\n----------\n");
            break;
        case 2:
            printf("Choose length of text: ");
            scanf("%d", &text_len);
            printf("Choose length of pattern: ");
            scanf("%d", &pat_len);
            printf("Choose a position(1-3): \n");
            printf("1)Begin\n");
            printf("2)Middle\n");
            printf("3)End\n");
            scanf("%d", &position);

            for (i = 0; i < text_len; i++)
            {
                if (i < pat_len)
                {
                    pattern[i] = (rand() % 26) + 'a';
                }
                if (i < text_len)
                {
                    text[i] = (rand() % 26) + 'a';
                }
            }
            text[text_len] = '\0';
            pattern[pat_len] = '\0';
            if (position == 1)
            {
                for (i = 0; i < pat_len; i++)
                {
                    text[i] = pattern[i];
                }
            }
            if (position == 2)
            {
                for (i = 0; i < pat_len; i++)
                {
                    text[text_len / 2 + i] = pattern[i];
                }
            }
            if (position == 3)
            {
                for (i = 0; i < pat_len; i++)
                {
                    text[text_len - pat_len + i] = pattern[i];
                }
            }
            skip_table = (int*)malloc(sizeof(int) * 256);
            gen_skip_table(skip_table, pattern);
            pos = horspool_search(text, text_len, pattern, pat_len, skip_table, &critical);
            if (pos == -1) puts("Pattern not found in text");
            else printf("Pattern found at pos: %d\n", pos);

            printf("Text: %s\nPattern: %s\n", text, pattern);
            printf("Horspool Basic operations performed: %d\n", critical);
            NaiveSolution(text, pattern, text_len, pat_len, &critical);
            printf("BruteForce Basic operations performed: %d\n", critical);

            printf("\nSkip Table\n");
            printf("----------\n");
            for (int i = 0; i < 256; i++)
            {
                //printf("%3d|", skip_table[i]);
                if (skip_table[i] != pat_len)
                {
                    printf("%c   | %d\n", i, skip_table[i]);
                }
            }
            printf("%c   | %d\n", pattern[pat_len - 1], pat_len);
            printf("*   | %d\n", pat_len);
            printf("\n----------\n");

            break;
        case 3:
            printf("Choose length of text: ");
            scanf("%d", &text_len);
            printf("Choose length of pattern: ");
            scanf("%d", &pat_len);
            printf("Choose number of iterations: ");
            scanf("%d", &iterations);
            for (int i = 0; i < iterations; i++)
            {
                for (int j = 0; j < text_len; j++)
                {
                    if (j < pat_len)
                    {
                        pattern[j] = (rand() % 26) + 'a';
                    }
                    if (j < text_len)
                    {
                        text[j] = (rand() % 26) + 'a';
                    }
                }
                text[text_len] = '\0';
                pattern[pat_len] = '\0';

                //Infuse the pattern at a random position in the text but make sure the pattern doesn't exceed the texts length, Code below!
                int random = (rand() % text_len - pat_len) + 1;
                for (int k = 0; k < pat_len; k++)
                {
                    text[random + k] = pattern[k];
                }

                skip_table = (int*)malloc(sizeof(int) * 256);
                gen_skip_table(skip_table, pattern);
                horspool_search(text, text_len, pattern, pat_len, skip_table, &critical2);
                sum += critical2;
                NaiveSolution(text, pattern, text_len, pat_len, &criticalBrute2);
                sumBrute += criticalBrute2;
            }
            critical3 = sum / iterations;
            criticalBrute3 = sumBrute / iterations;
            printf("Horspool Average basic operations performed: %d\n", critical3);
            printf("BruteForce Average basic operations performed: %d\n", criticalBrute3);
            break;
        case 4:
            /*
            printf("Choose length of text: ");
            scanf("%d", &text_len);
            printf("Choose length of pattern: ");
            scanf("%d", &pat_len);
            */

            printf("Choose number of iterations: ");
            scanf("%d", &iterations);

            for (int i = 0; i < iterations; i++)
            {
                text_len = rand() % MAX_TEXT_LEN;
                pat_len = rand() % (MAX_PAT_LEN - text_len);
                for (int j = 0; j < text_len; j++)
                {
                    if (j < pat_len)
                    {
                        pattern[j] = (rand() % 26) + 'a';
                    }
                    if (j < text_len)
                    {
                        text[j] = (rand() % 26) + 'a';
                    }
                }
                text[text_len] = '\0';
                pattern[pat_len] = '\0';
                for (int j = 0; j < text_len; j++)
                {
                    if (j < pat_len)
                    {
                        pattern[j] = (rand() % 26) + 'a';
                    }
                    if (j < text_len)
                    {
                        text[j] = (rand() % 26) + 'a';
                    }
                }
                text[text_len] = '\0';
                pattern[pat_len] = '\0';
                if (rand() % 2 == 0) //The pattern may or may not exist in the text
                {
                    //Infuse the pattern at a random position in the text but make sure the pattern doesn't exceed the texts length, Code below!
                    int random = rand() % (text_len - pat_len);
                    for (int k = 0; k < pat_len; k++)
                    {
                        text[random + k] = pattern[k];
                    }
                }

                skip_table = (int*)malloc(sizeof(int) * 256);
                gen_skip_table(skip_table, pattern);
                horspool_search(text, text_len, pattern, pat_len, skip_table, &critical4);
                sum += critical4;
                NaiveSolution(text, pattern, text_len, pat_len, &criticalBrute4);
                sumBrute += criticalBrute4;

            }
            critical5 = sum / iterations;
            printf("Horspool Average basic operations performed: %d\n", critical5);
            criticalBrute5 = sumBrute / iterations;
            printf("BruteForce Average basic operations performed: %d\n", criticalBrute5);
            break;
        case 5:
            displayMainMenu();
            break;
        case 6:
            exit(0);
        }
    }
    return 0;
}

int NaiveSolution(char* text, char* pattern, int text_len, int pat_len, int *op)
{
    int i, j, k, m, n;
    (*op) = 0;

    m = text_len;
    n = pat_len;

    for (i = 0; i <= m - n; i++)
     {
        j = 0;
        k = i;

        if (!(j < n && text[k] == pattern[j])) (*op)++;
        while (j < n && text[k] == pattern[j])
        {
            k++;
            j++;
            (*op)++;
        }
         if (j == n) return i;
    }

    return -1;
 
}

// Generate the skip table
void gen_skip_table(int* skip_table, char* pattern)
{
    int len = strlen(pattern);
    for (int i = 0; i < 256; i++)
    {
        skip_table[i] = len; //Set all default values to the length of the pattern
    }
    for (int i = 0; i < len - 1; i++)
    {
        skip_table[pattern[i]] = len - i - 1;
    }
}

// Search the text for the pattern and return the index of the first match
int horspool_search(char* text, int text_len, char* pattern, int pat_len, int* skip_table, int *op)
{
    (*op) = 0;
    int i = pat_len - 1;
    int j = pat_len - 1;

    while (i < text_len)
    {
        if(!(j >= 0 && text[i] == pattern[j])) (*op)++;
        while (j >= 0 && text[i] == pattern[j])
        {
            (*op)++;
            i--;
            j--;
        }
        if (j < 0)
        {
            return i;
        }
        i += skip_table[text[i]];
        j = pat_len - 1;
    }
    return -1;
}