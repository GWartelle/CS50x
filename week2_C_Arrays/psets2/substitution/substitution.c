#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool all_letters(string key);
string cipher(string text, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!all_letters(argv[1]))
    {
        printf("Key must contain 26 unique letters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    string ciphertext = cipher(plaintext, argv[1]);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool all_letters(string key)
{
    int len_key = strlen(key);

    if (len_key != 26)
    {
        return false;
    }

    for (int i = 0; i < len_key; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        for (int j = i + 1; j < len_key; j++)
        {
            if (toupper(key[j]) == toupper(key[i]))
            {
                return false;
            }
        }
    }

    return true;
}

string cipher(string text, string key)
{
    int len_text = strlen(text);

    for (int k = 0; k < len_text; k++)
    {
        if (isalpha(text[k]))
        {
            if (islower(text[k]))
            {
                int index_low = text[k] - 'a';
                text[k] = tolower(key[index_low]);
            }
            else if (isupper(text[k]))
            {
                int index_up = text[k] - 'A';
                text[k] = toupper(key[index_up]);
            }
        }
    }
    return text;
}