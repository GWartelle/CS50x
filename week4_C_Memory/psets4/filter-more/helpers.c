#include "helpers.h"
#include <math.h>

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

// Detect edges
BYTE valid(DWORD x)
{
    if (x >= 255)
    {
        x = 255;
    }

    return (BYTE) x;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                copy[i][j].rgbtBlue = 0;
                copy[i][j].rgbtGreen = 0;
                copy[i][j].rgbtRed = 0;
            }

            else
            {
                copy[i][j] = image[i - 1][j - 1];
            }
        }
    }

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            DWORD Gx_bl = 0;
            DWORD Gx_gr = 0;
            DWORD Gx_re = 0;

            DWORD Gy_bl = 0;
            DWORD Gy_gr = 0;
            DWORD Gy_re = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    Gx_bl += copy[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gx_gr += copy[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_re += copy[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];

                    Gy_bl += copy[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    Gy_gr += copy[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_re += copy[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                }
            }

            image[i - 1][j - 1].rgbtBlue = valid((DWORD) (sqrt((DWORD) (Gx_bl * Gx_bl) + (DWORD) (Gy_bl * Gy_bl)) + 0.5));
            image[i - 1][j - 1].rgbtGreen = valid((DWORD) (sqrt((DWORD) (Gx_gr * Gx_gr) + (DWORD) (Gy_gr * Gy_gr)) + 0.5));
            image[i - 1][j - 1].rgbtRed = valid((DWORD) (sqrt((DWORD) (Gx_re * Gx_re) + (DWORD) (Gy_re * Gy_re)) + 0.5));
        }
    }

    return;
}
