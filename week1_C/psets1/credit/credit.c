#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");

    int other = 0;
    int last_other = 0;
    int rest = 0;
    int last_rest = 0;
    int count = 0;

    for (long i = 10; i <= (10 * number); i *= 10)
    {
        count++;
        int x = 10 * (number % i) / i;
        int y = 2 * x;
        if ((count % 2) == 0)
        {
            if (y < 10)
            {
                other = other + y;
            }
            else
            {
                other = other + (y % 10) + 1;
            }
            last_other = x;
        }
        else
        {
            rest = rest + x;
            last_rest = x;
        }
        number = number - (number % i);
    }

    int first = 0;
    int second = 0;
    if (count >= 2)
    {
        if ((count % 2) > 0)
        {
            first = last_rest;
            second = last_other;
        }
        else
        {
            first = last_other;
            second = last_rest;
        }
    }

    int checksum = other + rest;
    if ((checksum % 10) == 0)
    {
        if (count == 13)
        {
            if (first == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (count == 15)
        {
            if (first == 3)
            {
                if (second == 4 || second == 7)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        else if (count == 16)
        {
            if (first == 4)
            {
                printf("VISA\n");
            }
            else if (first == 5)
            {
                if (second == 1 || second == 2 || second == 3 || second == 4 || second == 5)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}