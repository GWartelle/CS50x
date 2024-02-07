#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

long convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%li\n", convert(input));
}

long convert(string input)
{
    // TODO
    long num = 0;
    int n = strlen(input);
    for (int i = n, j = 1; i > 0; i--, j *= 10)
    {
        num += (input[i - 1] - 48) * j;
    }
    return num;
}