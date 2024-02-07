#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size;
    do
    {
        size = get_int("How far into the power of 2 do you want to go? ");
    }
    while (size < 1);

    long list[size];

    list[0] = 1;
    printf("%li\n", list[0]);

    for (int i = 1; i < size; i++)
    {
        list[i] = 2 * list[i - 1];
        printf("%li\n", list[i]);
    }

    return 0;
}