#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, string argv[])
{
    // Close the program if incorrect input
    if (argc != 2)
    {
        printf("Usage: ./pdf file\n");
        return 1;
    }

    // Open file
    string filename = argv[1];
    FILE *file = fopen(filename, "r");

    // Check if file exists
    if (file == NULL)
    {
        printf("No such file found.\n");
        return 2;
    }

    // Create a buffer and a comparison array
    uint8_t buffer[4];
    uint8_t test[] = {37, 80, 68, 70};

    // Read through the file
    fread(buffer, 1, 4, file);
    fclose(file);
    for (int i = 0; i < 4; i++)
    {
        if (buffer[i] != test[i])
        {
            printf("This is likely not a pdf file\n");

            return 0;
        }
    }
    
    printf("This is likely a pdf file\n");
    return 0;
}