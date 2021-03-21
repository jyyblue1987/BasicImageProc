#include "PpmProcessor.h"
#include "PixelProcessor.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void readPPMHeader(FILE *file, struct PPM_Header *header)
{
    printf("**PPM HEADER**\n");

    // fread(&header->magic_number, sizeof(char), 1, file);
    // printf("Magic Number: %.2s\n", header->magic_number);

    char ch;
    int  maxval;

    if (fscanf(file, "P%c\n", &ch) != 1 || ch != '6') 
        return;

    header->magic_number[0] = ch;
    
    /* skip comments */
    ch = getc(file);
    while (ch == '#')
    {
        do {
            ch = getc(file);
        } while (ch != '\n');	/* read to the end of the line */

        ch = getc(file);            /* thanks, Elliot */
    }

    if (!isdigit(ch)) 
        return;

    ungetc(ch, file);		/* put that digit back */

    /* read the width, height, and maximum value for a pixel */
    fscanf(file, "%d%d%d\n", &(header->width), &(header->height), &(header->max_color_value));
    printf("Magic Number: %.2s\n", header->magic_number);
    printf("Width: %d\n", header->width);
    printf("Height: %d\n", header->height);
    printf("Max Color Value: %d\n", header->max_color_value);
}

void writePPMHeader(FILE *file, struct PPM_Header *header)
{
    fprintf(file, "P6\n%d %d\n%d\n", header->width, header->height, header->max_color_value);
}

void makePPMHeader(struct PPM_Header *header, int width, int height)
{
    strcpy(header->magic_number, "P6");
    header->max_color_value = 255;
    header->width = width;
    header->height = height;
}

void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height)
{
    int i, j;
    
    // read in data
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fread(&pArr[i][j].r, 1, 1, file);
            fread(&pArr[i][j].g, 1, 1, file);
            fread(&pArr[i][j].b, 1, 1, file);            
        }       
    }
}

void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height)
{    
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fwrite(&pArr[i][j].r, 1, 1, file);
            fwrite(&pArr[i][j].g, 1, 1, file);
            fwrite(&pArr[i][j].b, 1, 1, file);
        }
        
    }
}
