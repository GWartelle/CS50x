#include "helpers.h"
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = (BYTE) (((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0) + 0.5);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
BYTE valid(DWORD x)
{
    if (x >= 255)
    {
        x = 255;
    }

    return (BYTE) x;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            DWORD newBlue =
                (DWORD) (0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue + 0.5);
            DWORD newGreen =
                (DWORD) (0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue + 0.5);
            DWORD newRed =
                (DWORD) (0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue + 0.5);

            image[i][j].rgbtBlue = valid(newBlue);
            image[i][j].rgbtGreen = valid(newGreen);
            image[i][j].rgbtRed = valid(newRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j <= k; j++, k--)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            DWORD tot_bl = 0;
            DWORD tot_gr = 0;
            DWORD tot_re = 0;
            int neighbors = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        neighbors++;
                        tot_bl += image[k][l].rgbtBlue;
                        tot_gr += image[k][l].rgbtGreen;
                        tot_re += image[k][l].rgbtRed;
                    }
                }
            }

            temp[i][j].rgbtBlue = (BYTE) ((tot_bl / (float) neighbors) + 0.5);
            temp[i][j].rgbtGreen = (BYTE) ((tot_gr / (float) neighbors) + 0.5);
            temp[i][j].rgbtRed = (BYTE) ((tot_re / (float) neighbors) + 0.5);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
