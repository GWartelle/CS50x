// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = LENGTH * LENGTH;

// Hash table
node *table[N];

// Dictionary's number of words
unsigned int total = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to get its index
    unsigned int index = hash(word);

    // Create a cursor to access the nodes of the linked list
    node *cursor = table[index];

    // Traverse the linked list of the correct index
    while (cursor != NULL)
    {
        // Check for correspondance
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    // The word is not in the dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Set the index to the sum of character values times the number of characters
    unsigned int x = 0;
    unsigned int n = strlen(word);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(word[i]))
        {
            x += toupper(word[i]) - 'A';
        }
    }

    return (x * n) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary and check if valid
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Buffer to read dictionary's words
    char word[LENGTH + 1];

    // Adds dictionary's words into the hash table
    while (fscanf(dict, "%s", word) == 1)
    {
        // Create a new node to store the word and chesk if valid
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the buffer's word into the node
        strcpy(n->word, word);

        // Hash the word to find its index
        unsigned int index = hash(n->word);

        // Stack the new node into its corresponding index
        n->next = table[index];
        table[index] = n;

        // Add one to count of words in the dictionary
        total++;
    }

    // Close the dictionary file
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Return the total count of words of the dictionary
    return total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Create a cursor and temporary node to access and free each of the nodes
    node *cursor;
    node *tmp;

    // Loop through all of the hash table's indeces
    for (int i = 0; i < N; i++)
    {
        // Set the cursor to the first element of the current linked list
        cursor = table[i];

        while (cursor != NULL)
        {
            // Set tmp to the next node of the linked list
            tmp = cursor->next;

            // Free the current node
            free(cursor);

            // Move the cursor one step down the linked list
            cursor = tmp;
        }
    }

    return true;
}