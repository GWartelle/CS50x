#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int height);

int main(void)
{
    int a = get_height();
    print_pyramid(a);
}

int get_height(void)
{
    int n;
    do
    {
        n = get_int("Size?: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void pyramid_space(int row, int space)
{
    for (int i = 0; i < (space - row); i++)
    {
        printf(" ");
    }
}

void pyramid_block(int block)
{
    for (int j = 0; j < block; j++)
    {
        printf("#");
    }
}

void print_pyramid(int height)
{
    for (int k = 1; k <= height; k++)
    {
        pyramid_space(k, height);
        pyramid_block(k);
        printf("\n");
    }
}