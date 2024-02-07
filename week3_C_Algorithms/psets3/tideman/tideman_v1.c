#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9
#define MAX_PAIRS (MAX * (MAX - 1) / 2)

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX_PAIRS];

int pair_count;
int candidate_count;

// Function prototypes
string to_up(string name);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    //
    printf("Candidates: ");

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
        //
        printf("%i-%s, ", i, candidates[i]);
    }

    //
    printf("\n");

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        //
        printf("Vote %i: ", i + 1);
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i, ", ranks[j]);
        }
        printf("\n");

        record_preferences(ranks);

        //
        printf("Preferences: ");
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                printf("%i-%i:%i; ", j, k, preferences[j][k]);
            }
        }

        printf("\n");
    }

    add_pairs();
    //
    printf("Pairs: ");
    for (int l = 0; l < MAX_PAIRS; l++)
    {
        printf("%i-%i; ", pairs[l].winner, pairs[l].loser);
    }
    printf("\n");

    sort_pairs();
    //
    printf("Sorted pairs: ");
    for (int m = 0; m < MAX_PAIRS; m++)
    {
        printf("%i-%i; ", pairs[m].winner, pairs[m].loser);
    }
    printf("\n");

    lock_pairs();
    //
    printf("Locked pairs: ");
    for (int n = 0; n < candidate_count; n++)
    {
        for (int o = 0; o < candidate_count; o++)
        {
            printf("%i-%i:%d; ", n, o, locked[n][o]);
        }
    }
    printf("\n");

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int i = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (preferences[j][k] > preferences[k][j])
            {
                pairs[i].winner = j;
                pairs[i].loser = k;
                i++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < MAX_PAIRS - 1; i++)
    {
        for (int j = MAX_PAIRS; j > i + 1; j--)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[j - 1].winner][pairs[j - 1].loser])
            {
                pair tampon = pairs[j - 1];
                pairs[j - 1] = pairs[j];
                pairs[j] = tampon;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    bool losers[candidate_count];
    int last = candidate_count + 1;

    for (int i = 0; i < candidate_count; i++)
    {
        losers[i] = false;
    }

    for (int i = 0; i < MAX_PAIRS; i++)
    {
        if (pairs[i].winner == 0 && pairs[i].loser == 0)
        {
            break;
        }

        losers[pairs[i].loser] = true;
        int count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (losers[j] == true)
            {
                count ++;
            }
        }

        if (count < candidate_count)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

        if (count == candidate_count - 1)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (losers[j] == false)
                {
                    last = j;
                }
            }
        }

        if (count == candidate_count && pairs[i].loser != last)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool losers[candidate_count];
    int winner = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        losers[i] = false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                losers[j] = true;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (losers[i] == false)
        {
            winner = i;
        }
    }

    printf("%s\n", candidates[winner]);

    return;
}