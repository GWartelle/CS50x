// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol.\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool lower = false;
    bool upper = false;
    bool digit = false;
    bool punct = false;

    int len = strlen(password);
    for (int i = 0; i < len; i++)
    {
        char j = password[i];
        if (islower(j))
        {
            lower = true;
        }
        else if (isupper(j))
        {
            upper = true;
        }
        else if (isdigit(j))
        {
            digit = true;
        }
        else if (ispunct(j))
        {
            punct = true;
        }
    }

    if (lower && upper && digit && punct)
    {
        return true;
    }
    else
    {
        return false;
    }
}