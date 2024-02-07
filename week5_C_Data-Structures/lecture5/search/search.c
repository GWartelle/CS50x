#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node
{
    int number;
    struct node *right;
    struct node *left;
}
node;

bool search(node *tree, int number);

int main(void)
{
    int number = get_int("Choose a number to search for in the tree: ");

    node *tree = NULL;



    bool answer = false;
    answer = search(tree, number);

    if (answer == true)
    {
        printf("The number %i is indeed in this tree.\n", number);
    }
    else
    {
        printf("The number %i is not in this tree.\n", number);
    }

    return 0;
}

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else
    {
        return true;
    }
}