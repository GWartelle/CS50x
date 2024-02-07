#include <cs50.h>
#include <stdio.h>

long get_size(string prompt);
long get_year(long x, long y);

int main(void)
{
    long x = get_size("Start size: ");
    long y;
    do
    {
        y = get_size("End size: ");
    }
    while (y < x);
    long z = get_year(x, y);
    printf("Years: %li\n", z);
}

long get_size(string prompt)
{
    long n;
    do
    {
        n = get_long("%s", prompt);
    }
    while (n < 9);
    return n;
}

long get_year(long x, long y)
{
    long z = 0;
    while (x < y)
    {
        x = x + (double) (x / 3) - (double) (x / 4);
        z++;
    }
    return z;
}