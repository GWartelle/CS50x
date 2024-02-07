#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? ");
    int age = get_int("How old are you? ");
    string phone = get_string("What's your phone number? ");

    printf("Your name is %s,\nYou are %i years old,\nAnd your phone number is %s.\n", name, age, phone);

    return 0;
}