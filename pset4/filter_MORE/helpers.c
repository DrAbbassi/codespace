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

#define bxy ptr_bxy[ (i * width) + j]
#define gxy ptr_gxy[ (i * width) + j]
#define rxy ptr_rxy[ (i * width) + j]

//#define by ptr_by[ (i * width) + j]
//#define gy ptr_gy[ (i * width) + j]
//#define ry ptr_ry[ (i * width) + j]

#define sqb round(sqrt( (avx_blue * avx_blue) + (avy_blue * avy_blue)))
#define sqg round(sqrt( (avx_green * avx_green) + (avy_green * avy_green)))
#define sqr round(sqrt( (avx_red * avx_red) + (avy_red * avy_red)))

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
        int average    = 0;
        int av_blue    = 0;
        int av_green   = 0;
        int av_red     = 0;
        float division = 0.0;

        for (int j = 0; j < width; j++) //itterating through the image pixels
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

                av_blue  = round(av_blue / division);
                av_green = round(av_green / division);
                av_red   = round(av_red / division);

                ptr_b[ (i * width) + j] = av_blue;
                ptr_g[ (i * width) + j] = av_green;
                ptr_r[ (i * width) + j] = av_red;

                av_blue  = 0;
                av_green = 0;
                av_red   = 0;
                division = 0.0;

        }
    }

    for (int i = 0; i < height - 1; i++)
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
// dynamically allocating a set of arrays to store each pixels' new value.
// This had to be done to avoid altering values that need to be used to
// calculate next pixels and so on.

uint8_t *ptr_bxy = (uint8_t *)malloc( (width * height) * sizeof(image[0][0].rgbtBlue) );
uint8_t *ptr_gxy = (uint8_t *)malloc( (width * height) * sizeof(image[0][0].rgbtGreen) );
uint8_t *ptr_rxy = (uint8_t *)malloc( (width * height) * sizeof(image[0][0].rgbtRed) );

for (int i = 0; i < height; i++) //itterating through the image rows
    {
        // variables to store the averages of each channel.

        float  avx_blue  = 0.0;
        float avx_green  = 0.0;
        float   avx_red  = 0.0;

        float  avy_blue  = 0.0;
        float  avy_green = 0.0;
        float  avy_red   = 0.0;

        float xdiv       = 0.0; //div stands for division.
        float ydiv       = 0.0;

        for (int j = 0; j < width; j++) //itterating through the image pixels
        {
            // doing box x nd y indexes in the same loops to avoid additional malloc arrays.
            // processing power over memory use.

            // for the X index

            // variables kx and ky and the if conditions are the implementation of the kernels.

            for (int row = i - 1, ky = -1; row < i + 2; row++, ky++) //itterating through the box rows.
                {
                    //itterating through the row cells.
                    for (int column = j - 1, kx = -1; column < j + 2; column++, kx++)
                    {
                        // X index

                        if (ky == 0) //if box loop is in middle of Y index multiply by 2.
                        {
                            avx_blue  += (p_blue  * (kx * 2) );
                            avx_green += (p_green * (kx * 2) );
                            avx_red   += (p_red   * (kx * 2) );

                            xdiv++;
                        }

                        else if (ky != 0)
                        {
                            avx_blue  += (p_blue  * (kx) );
                            avx_green += (p_green * (kx) );
                            avx_red   += (p_red   * (kx) );

                            xdiv++;
                        }

                        // Y index

                        if (kx == 0) //if box loop is in middle of X index multiply by 2.
                        {
                            avy_blue  += (p_blue  * (ky * 2) );
                            avy_green += (p_green * (ky * 2) );
                            avy_red   += (p_red   * (ky * 2) );

                            ydiv++;
                        }

                        else if (kx != 0)
                        {
                            avy_blue  += (p_blue  * (ky) );
                            avy_green += (p_green * (ky) );
                            avy_red   += (p_red   * (ky) );

                            ydiv++;
                        }
                    }
                }

                // calculating the averages
                avx_blue  = avx_blue / xdiv; //avx will be large in horizontal borders? Yes
                avx_green = avx_green / xdiv; //maybe not round and use floats instead? Good idea.
                avx_red   = avx_red / xdiv;

                avy_blue  = avy_blue / ydiv; //avy will be large in vertical borders? Yes
                avy_green = avy_green / ydiv;
                avy_red   = avy_red / ydiv;

                // doing the math here before assigning values to the heap array
                bxy = (uint8_t) sqb;
                gxy = (uint8_t) sqg;
                rxy = (uint8_t) sqr;

                // assiging all helping variables to zero.
                avx_blue  = 0.0;
                avx_green = 0.0;
                avx_red   = 0.0;
                xdiv      = 0.0;

                avy_blue  = 0.0;
                avy_green = 0.0;
                avy_red   = 0.0;
                ydiv      = 0.0;
        }
    }


    //assigning the new channel values from the heap to the image file.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ( (bxy > 255) || (gxy > 255) || (rxy > 255) )
            {
                Blue  = 255;
                Green = 255;
                Red   = 255;
            }

            else
            {
                Blue  = bxy;
                Green = gxy;
                Red   = rxy;
            }
        }
    }

    free(ptr_bxy);
    free(ptr_gxy);
    free(ptr_rxy);

    return;
}
