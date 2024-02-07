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
    if (input[0] == '\0')
    {
        return 0;
    }
    int n = strlen(input);

    long x = input[n - 1];
    x -= 48;
    input[n - 1] = '\0';
    return x + convert(input) * 10;
}