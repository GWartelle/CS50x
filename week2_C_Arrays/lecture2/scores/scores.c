#include <cs50.h>
#include <stdio.h>

const int N = 3;

float average(int len, int n[]);

int main(void)
{
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }
    printf("Average: %f\n", average(N, scores));
}

float average(int len, int n[])
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += n[i];
    }
    return sum / (float) len;
}