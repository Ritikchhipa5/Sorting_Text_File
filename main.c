// Assignment N2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The name of the input file and output file
#define IN_FILE "quotes.txt"
#define OUT_FILE "output.txt"

// Defines how many quotes will be in the OUT_FILE
#define MAX_QUOTES 5

int maxNumberOfQuotes = 0;

// This function will be used in sorting to swap strings ("pointers").
void swap(char **ptr1, char **ptr2)
{
    char *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

// Selection Sort function here.
void selection_sort(char **quotes, size_t n)
{

    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (strlen(quotes[j]) < strlen(quotes[min_idx]))
                min_idx = j;
            else if (strlen(quotes[j]) == strlen(quotes[min_idx]))
            {
                if (strcoll(quotes[j], quotes[min_idx]) < 0)
                {
                    min_idx = j;
                }
            }

        // Swap the found minimum element with the first element
        swap(&quotes[min_idx], &quotes[i]);
    }
}

// Read quotes from file and add them to array of pointers.
// You also must user selection_sort inside this function!
void read_in(char **quotes)
{
    FILE *fptr;
    // Open file
    fptr = fopen("quotes.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read contents from file and count the length of longest string
    int longLength = 0; // length of longest string
    int tempLength = 0; // temp string
    char last;
    char c;
    c = fgetc(fptr);
    while (c != EOF)
    {
        if (c == '\n')
        {

            if (tempLength > longLength)
            {
                longLength = tempLength;
            }
            tempLength = 0;
        }
        last = c;
        c = fgetc(fptr);
        tempLength++;
    }
    fclose(fptr);

    // Open file again to read quotes one by one and create a pointer and store it in quotes array
    fptr = fopen("quotes.txt", "r+");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    char str[longLength];
    int i = 0;
    while (fgets(str, longLength, fptr))
    {
        // finc length of string
        int strLength = strlen(str);

        // check that is string is having only next line character or any other unnessarry character as first character
        // if yes then we will not count that string
        if ((strLength == 1 || strLength == 2) && ((int)str[0] >= 0 || (int)str[0] <= 32))
        {
        }
        else
        {
            // create a temp string and allocate it memory
            char *temp = (char *)malloc((strLength + 1) * sizeof(char));
            if (!temp)
            {
                printf("can not allocate memory \n");
                exit(1);
            }
            strcpy(temp, str);
            quotes[i] = temp;
            // do selection sort
            selection_sort(quotes, i + 1);

            if (i < MAX_QUOTES)
            {
                maxNumberOfQuotes++;
                i++;
            }
        }
    }
    fclose(fptr);
    // free(fptr) ; 
}

// Print the quotes using array of pointers.
void print_out(char **quotes)
{

    for (int k = 0; k < maxNumberOfQuotes; k++)
    {
        if (quotes[k][strlen(quotes[k]) - 1] != '\n')
        {
            printf("%s", quotes[k]);
            printf("\n");
        }
        else
        {
            printf("%s", quotes[k]);
        }
    }
}

// Save the sorted quotes in the OUT_FILE file.
void write_out(char **quotes)
{
    FILE *fptr2;
    // Open file
    fptr2 = fopen("output.txt", "w+");
    if (fptr2 == NULL)
    {
        printf("Cannot open file \n");
        exit(1);
    }
    for (int k = 0; k < maxNumberOfQuotes; k++)
    {
        if (quotes[k][strlen(quotes[k]) - 1] != '\n')
        {
            fputs(quotes[k], fptr2);
            fputs("\n", fptr2);
        }
        else
        {
            fputs(quotes[k], fptr2);
        }
    }
    fclose(fptr2);
    // free(fptr2);
}

// Free memory pointed by pointers in the array of pointers!
void free_memory(char **quotes)
{
    for (int k = 0; k < maxNumberOfQuotes; k++)
    {
        free(quotes[k]);
    }
}

int main()
{

    // Create array of pointers. Each pointer should point to heap memory where each quote is kept.
    // I.e. quotes[0] points to smallest string.
    // We need +1 to insert the new quote at the end of the array and then re-sort.
    char *quotes[MAX_QUOTES + 1] = {NULL};
    // Read quotes from file and place them into array quotes.
    // Also, sort as you add them
    // You also need to print how many lines were processed
    read_in(quotes);

    // Print MAX_QUOTES shortest quotes
    print_out(quotes);

    // Save MAX_QUOTES shortest quotes in the file OUT_FILE
    write_out(quotes);

    // Free memory allocated by array of pointers
    free_memory(quotes);

    return (0);
}


