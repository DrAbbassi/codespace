#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

// original pixel
#define Blue image[i][j].rgbtBlue
#define Green image[i][j].rgbtGreen
#define Red image[i][j].rgbtRed

//3x3 box pixel
#define p_blue image[row][column].rgbtBlue
#define p_green image[row][column].rgbtGreen
#define p_red image[row][column].rgbtRed

//border pixel: uppper left
#define upl_1 image[0][1]
#define upl_2 image[1][0]
#define upl_3 image[1][1]

//border pixel: uppper right
#define upr_1 image[0][width - 2]
#define upr_2 image[1][width - 2]
#define upr_3 image[1][width - 1]

//border row pixels: upper
#define ulp1 image[0][j - 1]
#define ulp2 image[0][j + 1]
#define ulp3 image[1][j - 1]
#define ulp4 image[1][j]
#define ulp5 image[1][j + 1]

//border pixel: down left
#define dwl_1 image[height - 2][0]
#define dwl_2 image[height - 2][1]
#define dwl_3 image[height - 1][1]

//border pixel: down right
#define dwr_1 image[height - 2][width - 1]
#define dwr_2 image[height - 2][width - 2]
#define dwr_3 image[height - 1][width - 2]

//border row pixels: down
#define dlp1 image[height - 1][j - 1]
#define dlp2 image[height - 1][j + 1]
#define dlp3 image[height - 2][j - 1]
#define dlp4 image[height - 2][j]
#define dlp5 image[height - 2][j + 1]

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

for (int i = 0; i < height; i++)
    {
        for (int a, j = 0; j < width; j++)
        {
            a = (Blue + Green + Red) / 3;
            Blue = a;
            Green = a;
            Red = a;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int b, g, r, j = 0; j < width; j++)
        {
            b = round((0.131 * Blue) + (0.534 * Green) + (0.272 * Red));
            g = round((0.168 * Blue) + (0.686 * Green) + (0.349 * Red));
            r = round((0.189 * Blue) + (0.769 * Green) + (0.393 * Red));

            if      (b > 255) Blue = 255;
            else if (g > 255) Green = 255;
            else if (r > 255) Red = 255;
            else
            {
                Blue  = b;
                Green = g;
                Red   = r;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0, lastw = width - 1; j < lastw; j++, lastw--)
        {
            /*  using a famous function that swaps variables using bit operator XOR (^)
                given that x ^ x = 0.

                *y = *x ^ *y;
                *x = *x ^ *y;
                *y = *x ^ *y;

            */
            image[i][lastw].rgbtBlue = Blue ^ image[i][lastw].rgbtBlue;
            Blue                     = Blue ^ image[i][lastw].rgbtBlue;
            image[i][lastw].rgbtBlue = Blue ^ image[i][lastw].rgbtBlue;

            image[i][lastw].rgbtGreen = Green ^ image[i][lastw].rgbtGreen;
            Green                     = Green ^ image[i][lastw].rgbtGreen;
            image[i][lastw].rgbtGreen = Green ^ image[i][lastw].rgbtGreen;

            image[i][lastw].rgbtRed = Red ^ image[i][lastw].rgbtRed;
            Red                     = Red ^ image[i][lastw].rgbtRed;
            image[i][lastw].rgbtRed = Red ^ image[i][lastw].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

uint8_t *ptr_b = (uint8_t *)malloc( (width * height) * sizeof(image[0][0].rgbtBlue) );
uint8_t *ptr_g = (uint8_t *)malloc( (width * height) * sizeof(image[0][0].rgbtGreen) );
uint8_t *ptr_r = (uint8_t *)malloc( (width * height) * sizeof(image[0][0].rgbtRed) );

for (int i = 0; i < height; i++)
    {
       // int box[3][3];
        int average = 0; int av_blue = 0; int av_green = 0; int av_red = 0;
        float division = 0.0;

        for (int j = 0; j < width; j++) //itterating through the image pixels
        {
            // checking if boundaries exist.

            if (i == 0)
            {
                if (j == 0)
                {
                    // upper left corner
                    ptr_b[ (i * width) + j] = round((Blue + upl_1.rgbtBlue + upl_2.rgbtBlue + upl_3.rgbtBlue) / 4.0);
                    ptr_g[ (i * width) + j] = round((Green + upl_1.rgbtGreen + upl_2.rgbtGreen + upl_3.rgbtGreen) / 4.0);
                    ptr_r[ (i * width) + j] = round((Red + upl_1.rgbtRed + upl_2.rgbtRed + upl_3.rgbtRed) / 4.0);

                }
                else if (j == width - 1)
                {
                    // upper right corner

                    ptr_b[ (i * width) + j] = round((Blue + upr_1.rgbtBlue + upr_2.rgbtBlue + upr_3.rgbtBlue) / 4.0);
                    ptr_g[ (i * width) + j] = round((Green + upr_1.rgbtGreen + upr_2.rgbtGreen + upr_3.rgbtGreen) / 4.0);
                    ptr_r[ (i * width) + j] = round((Red + upr_1.rgbtRed + upr_2.rgbtRed + upr_3.rgbtRed) / 4.0);

                }
                else
                {
                    // upper loop of 5
                    ptr_b[ (i * width) + j] = round((Blue + ulp1.rgbtBlue + ulp2.rgbtBlue + ulp3.rgbtBlue + ulp4.rgbtBlue + ulp5.rgbtBlue) / 6.0);
                    ptr_g[ (i * width) + j] = round((Green + ulp1.rgbtGreen + ulp2.rgbtGreen + ulp3.rgbtGreen + ulp4.rgbtGreen + ulp5.rgbtGreen) / 6.0);
                    ptr_r[ (i * width) + j] = round((Red + ulp1.rgbtRed + ulp2.rgbtRed + ulp3.rgbtRed + ulp4.rgbtRed + ulp5.rgbtRed) / 6.0);
                }

            }
            else if (i == (height - 1))
            {
                if (j == 0)
                {
                    // down left corner
                    ptr_b[ (i * width) + j] = round((Blue + dwl_1.rgbtBlue + dwl_2.rgbtBlue + dwl_3.rgbtBlue) / 4.0);
                    ptr_g[ (i * width) + j] = round((Green + dwl_1.rgbtGreen + dwl_2.rgbtGreen + dwl_3.rgbtGreen) / 4.0);
                    ptr_r[ (i * width) + j] = round((Red + dwl_1.rgbtRed + dwl_2.rgbtRed + dwl_3.rgbtRed) / 4.0);

                }
                else if (j == width - 1)
                {
                    // down right corner
                    ptr_b[ (i * width) + j] = round((Blue + dwr_1.rgbtBlue + dwr_2.rgbtBlue + dwr_3.rgbtBlue) / 4.0);
                    ptr_g[ (i * width) + j] = round((Green + dwr_1.rgbtGreen + dwr_2.rgbtGreen + dwr_3.rgbtGreen) / 4.0);
                    ptr_r[ (i * width) + j] = round((Red + dwr_1.rgbtRed + dwr_2.rgbtRed + dwr_3.rgbtRed) / 4.0);

                }
                else
                {
                    // down loop of 5
                    Blue = round((Blue + dlp1.rgbtBlue + dlp2.rgbtBlue + dlp3.rgbtBlue + dlp4.rgbtBlue + dlp5.rgbtBlue) / 6.0);
                    Green = round((Green + dlp1.rgbtGreen + dlp2.rgbtGreen + dlp3.rgbtGreen + dlp4.rgbtGreen + dlp5.rgbtGreen) / 6.0);
                    Red = round((Red + dlp1.rgbtRed + dlp2.rgbtRed + dlp3.rgbtRed + dlp4.rgbtRed + dlp5.rgbtRed) / 6.0);

                }
            }

            else // box loop
            {
                for (int row = i - 1; row < i + 2; row++) //itterating through the box rows.
                {
                    for (int column = j - 1; column < j + 2; column++) //itterating through the row cells.
                    {
                            av_blue  += p_blue;
                            av_green += p_green;
                            av_red   += p_red;

                            division++;
                    }
                }

               // av_blue  -= Blue;
               // av_green -= Green;
               // av_red   -= Red;

                av_blue  = round(av_blue / division);
                av_green = round(av_green / division);
                av_red   = round(av_red / division);
/*
                if      (av_blue / division > 255)  av_blue  = 255;
                else if (av_blue / division < 0  )  av_blue  = 0  ;
                else if (av_green / division > 255) av_green = 255;
                else if (av_green / division < 0 )  av_green = 0  ;
                else if (av_red / division > 255)   av_red   = 255;
                else if (av_red / division < 0  )   av_red   = 0  ;
*/

                ptr_b[ (i * width) + j] = av_blue;
                ptr_g[ (i * width) + j] = av_green;
                ptr_r[ (i * width) + j] = av_red;

               // Blue = av_blue;
               // Green = av_green;
               // Red = av_red;

                av_blue  = 0;
                av_green = 0;
                av_red   = 0;
                division = 0.0;
            }
        }
    }

    for(int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            Blue  = ptr_b[ (i * width) + j];
            Green = ptr_g[ (i * width) + j];
            Red   = ptr_r[ (i * width) + j];
        }
    }

    free(ptr_b);
    free(ptr_g);
    free(ptr_r);

    return;
}
