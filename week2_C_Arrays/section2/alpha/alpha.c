#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string word;
    int lower;
    bool lowercase = false;

    do
    {
        word = get_string("Word: ");
        lower = 0;

        for (int i = 0, len = strlen(word); i < len; i++)
        {
            if (islower(word[i]))
            {
                lower++;
            }
        }

        if (lower == strlen(word))
        {
            lowercase = true;
        }

        else
        {
            printf("Only lowercase\n");
        }
    }
    while (lowercase == false);

    for (int i = 0, len = strlen(word); i < len - 1; i++)
    {
        if (word[i] > word[i + 1])
        {
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");
    return 0;
}