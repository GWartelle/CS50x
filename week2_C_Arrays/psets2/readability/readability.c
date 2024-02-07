#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = 100.0 * (float) (letters) / (float) (words);
    float S = 100.0 * (float) (sentences) / (float) (words);
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        for (int i = 1; i < 16; i++)
        {
            if (index >= i && index < i + 0.5)
            {
                printf("Grade %i\n", i);
            }
            else if (index >= i + 0.5 && index < i + 1)
            {
                printf("Grade %i\n", (i + 1));
            }
        }
    }
}

int count_letters(string text)
{
    int count = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    int len = strlen(text);
    bool word = false;

    for (int i = 0; i < len; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            word = true;
        }
        if (word == true)
        {
            if (text[i] == ' ')
            {
                count++;
                word = false;
            }
        }
    }
    if (word)
    {
        count++;
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}