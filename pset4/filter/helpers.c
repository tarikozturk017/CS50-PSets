#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
// change all of the functions --> save org image otherwise it'll be changed.
    for (int i = 0; i < height; i++)                                                                                //i is to take each row
    {
        for (int j = 0; j < width; j++)                                                                             //j is to check each column within each row
        {
            int avrg = roundf(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);            //to do the math --> take each value of blue+green+red
            image[i][j].rgbtBlue = avrg;                                                                            //+++ then divide 3 to get the average. assign it to each bgr
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtRed = avrg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = roundf(image[i][j].rgbtRed * .393 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtBlue * .189);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            int sepiaGreen = roundf(image[i][j].rgbtRed * .349 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtBlue * .168);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            int sepiaBlue = roundf(image[i][j].rgbtRed * .272 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtBlue * .131);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if ((width % 2) == 0)
        {
            for (int j = 0, n = (float)(width / 2); j < n; j++)
            {
                RGBTRIPLE temppx = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temppx;
            }
        }
        else if ((width % 2) == 1)
        {
            for (int j = 0; j < (float)(width / 2); j++)
            {
                RGBTRIPLE temppx = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temppx;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];                                                     // global temporary value to store each row and column's filtered values.

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {

            int coord_row[] = {row - 1, row, row + 1};                                  // possible neighbor's row's locations
            int coord_column[] = {column - 1, column, column + 1};                      // possible neighbor's column's locations
            int count = 0;                                                              // set a counter to see to the number which we'll devide the total number for each color.
            float neig_red = 0, neig_green = 0, neig_blue = 0;                          // create a float to calculate total number of each color.

            for (int r = 0; r < 3; r++)                                                 // r -> row (to avoid misconception) && c - > column
            {
                for (int c = 0; c < 3; c++)                                             // loop them twice to see all possible neighboring rotations.
                {
                    int current_row = coord_row[r];                                     // the value of the row which we'll check + calculate if it's not on the edge.
                    int current_column = coord_column[c];                               // the value of the column.....

                    if (current_row >= 0 && current_row < height && current_column >= 0 && current_column < width)              //if the pixel, which belongs to the one we're filtering, is within the image
                    {
                        RGBTRIPLE pxl = image[current_row][current_column];             // then declare a temporary pxl which is copy of the one we're checking
                        neig_red += pxl.rgbtRed;                                        // calculate each color to find the total
                        neig_green += pxl.rgbtGreen;
                        neig_blue += pxl.rgbtBlue;
                        count++;                                                        // increase count each time we add a neigboring pixel's value to total
                    }
                }
            }
            temp[row][column].rgbtRed = round(neig_red / count);                        // after calculating each pixel's filterred value, store them into temp
            temp[row][column].rgbtGreen = round(neig_green / count);
            temp[row][column].rgbtBlue = round(neig_blue / count);
        }
    }

    for (int i = 0; i < height; i++)                                                    // copy temp to original image one by one
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
