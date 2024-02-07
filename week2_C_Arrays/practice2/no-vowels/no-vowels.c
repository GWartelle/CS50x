// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string before);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        printf("%s\n", replace(argv[1]));
    }
    else
    {
        printf("You must enter one and only word after the command './no-vowel'.\n");
        return 1;
    }
}

string replace(string before)
{
    int len = strlen(before);
    for (int i = 0; i < len; i++)
    {
        switch (before[i])
        {
            case 'a':
                before[i] = '6';
                break;

            case 'e':
                before[i] = '3';
                break;

            case 'i':
                before[i] = '1';
                break;

            case 'o':
                before[i] = '0';
                break;
        }
    }
    return before;
}