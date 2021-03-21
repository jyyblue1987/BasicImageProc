#include "PpmProcessor.h"
#include "PixelProcessor.h"
#include <string.h>
#include <stdio.h>

void readPPMHeader(FILE *file, struct PPM_Header *header)
{
    printf("**PPM HEADER**\n");

    fread(&header->magic_number, sizeof(char), 1, file);
    printf("Magic Number: %.2s\n", header->magic_number);

    fread(&header->width, sizeof(int), 1, file);
    printf("Width: %d\n", header->width);

    fread(&header->height, sizeof(int), 1, file);
    printf("Height: %d\n", header->height);

    fread(&header->max_color_value, sizeof(int), 1, file);
    printf("Max Color Value: %d\n", header->max_color_value);
}

void writePPMHeader(FILE *file, struct PPM_Header *header)
{
    fwrite(header, sizeof(struct PPM_Header), 1, file);
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
    int i, j, padding;
    char temp[4];
    padding = width % 4;

    if (padding != 0)
    {
        padding = (4 - (3 * width) % 4) % 4;
    }
    // read in data
    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            fread(&pArr[i][j].b, 1, 1, file);
            fread(&pArr[i][j].g, 1, 1, file);
            fread(&pArr[i][j].r, 1, 1, file);
        }
        if (padding != 0)
        {
            if (fread(&temp, padding, 1, file) != 1)
                printf("\nError reading padding in row %d \n", i);
        }
    }
}

void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height)
{
    int i, j, padding;
    char temp[4];
    padding = width % 4;

    if (padding != 0)
    {
        padding = (4 - (3 * width) % 4) % 4;
    }

    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            fwrite(&pArr[i][j].b, 1, 1, file);
            fwrite(&pArr[i][j].g, 1, 1, file);
            fwrite(&pArr[i][j].r, 1, 1, file);
        }
        if (padding != 0)
        {
            fwrite(&temp, padding, 1, file);
        }
    }
}
