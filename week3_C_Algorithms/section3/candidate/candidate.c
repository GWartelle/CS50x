#include <stdio.h>
#include <cs50.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate get_candidate(string prompt);

int main(void)
{
    int size = get_int("How many candidates are there? ");

    candidate candidates_array[size];

    for (int i = 0; i < size; i++)
    {
        candidates_array[i] = get_candidate("Enter a candidate: ");
    }

    printf("Here is the total list of candidates: \n");
    for (int i = 0; i < size; i++)
    {
        printf("Candidate n°%i: %s with %i votes.\n", i + 1, candidates_array[i].name, candidates_array[i].votes);
    }

    return 0;
}

candidate get_candidate(string prompt)
{
    printf("%s\n", prompt);

    candidate c;
    c.name = get_string("Enter a name: ");
    c.votes = get_int("Enter a number a votes: ");
    return c;
}