#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;

// Set up constants for later use
const int BLOCK_SIZE = 512;
const int FILENAME_SIZE = 8;

int main(int argc, char *argv[])
{
    // Check for proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }

    // Open raw file and check for correct format
    FILE *raw_file = fopen(argv[1], "rb");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // Set up jpeg file names
    int jpeg_idx = 0;
    char jpeg_name[FILENAME_SIZE];

    // Set up the buffer the first 3 bytes comparison array
    BYTE jpeg_start[3] = {0xFF, 0xD8, 0xFF};
    BYTE buffer[BLOCK_SIZE];

    // Set up a temporary memory address for the jpeg files to extract
    FILE *output = NULL;

    // Loop through the raw file by 512B blocks
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Compares the first 3 bytes of the current block
        if (memcmp(buffer, jpeg_start, 3) == 0)
        {
            // Close the ouput file if it's not empty
            if (output != NULL)
            {
                fclose(output);
            }

            // Set up the file name of the jpeg to extract, and links it with the temporary output
            sprintf(jpeg_name, "%03i.jpg", jpeg_idx);
            output = fopen(jpeg_name, "wb");

            // Close the program if no file could be extracted
            if (output == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", jpeg_name);
                fclose(raw_file);
                return 3;
            }

            // Change the number for the next jpeg to extract
            jpeg_idx++;
        }

        // Write the jpeg file into the output file
        if (output != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }

    // Close the output file if it does not end up null
    if (output != NULL)
    {
        fclose(output);
    }

    // Close the raw file
    fclose(raw_file);
    return 0;
}