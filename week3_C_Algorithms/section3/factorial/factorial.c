#include <cs50.h>
#include <stdio.h>

long factorial(int number);

int main(void)
{
    // Prompt the user for a number
    int n = get_int("Type a number to be factored: ");
    printf("%li\n", factorial(n));
    return 0;
}

long factorial(int number)
{
    if (number == 1)
    {
        return 1;
    }

    return number * factorial(number - 1);
}