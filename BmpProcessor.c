
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BmpProcessor.h"

void readBMPHeader(FILE *file, struct BMP_Header *header)
{

    printf("*****BMP HEADER*****\n");

    fread(&header->signature, sizeof(short), 1, file);
    printf("signature: %.2s\n", header->signature);

    fread(&header->size, sizeof(int), 1, file);
    printf("size: %d\n", header->size);

    fread(&header->reserved1, sizeof(short), 1, file);
    printf("reserved1: %d\n", header->reserved1);

    fread(&header->reserved2, sizeof(short), 1, file);
    printf("reserved2: %d\n", header->reserved2);

    fread(&header->offset_pixel_array, sizeof(int), 1, file);
    printf("offset_pixel_array: %d\n", header->offset_pixel_array);
}

void writeBMPHeader(FILE *file, struct BMP_Header *header)
{
    fwrite(header, sizeof(struct BMP_Header), 1, file);
}

void readDIBHeader(FILE *file, struct DIB_Header *header)
{
    printf("*****DIB HEADER*****\n");
    fread(&header->size, sizeof(int), 1, file);
    printf("DIB header size: %d\n", header->size);

    fread(&header->width, sizeof(int), 1, file);
    printf("Image Width size: %d\n", header->width);

    fread(&header->height, sizeof(int), 1, file);
    printf("Image Height size: %d\n", header->height);

    fread(&header->planes, sizeof(short), 1, file);
    printf("Image Planes: %d\n", header->planes);

    fread(&header->bits, sizeof(short), 1, file);
    printf("Image Bits: %d\n", header->bits);

    fread(&header->compression, sizeof(int), 1, file);
    printf("Image Compression: %d\n", header->compression);

    fread(&header->imagesize, sizeof(int), 1, file);
    printf("Image Size: %d\n", header->imagesize);

    fread(&header->xresolution, sizeof(int), 1, file);
    printf("Image X Resolution: %d\n", header->xresolution);

    fread(&header->yresolution, sizeof(int), 1, file);
    printf("Image Y Resolution: %d\n", header->yresolution);

    fread(&header->ncolours, sizeof(int), 1, file);
    printf("Image Colors in Table: %d\n", header->ncolours);

    fread(&header->importantcolours, sizeof(int), 1, file);
    printf("Image Important Colors: %d\n", header->importantcolours);
}

void writeDIBHeader(FILE *file, struct DIB_Header *header)
{
    fwrite(header, sizeof(struct DIB_Header), 1, file);
}

void makeBMPHeader(struct BMP_Header *header, int width, int height)
{
    strcpy(header->signature, "BM");
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->size = width * height;
}

// unsigned int size;
// int width, height;
// unsigned short int planes;
// unsigned short int bits;
// unsigned int compression;
// unsigned int imagesize;
// int xresolution, yresolution;
// unsigned int ncolours;
// unsigned int importantcolours;
void makeDIBHeader(struct DIB_Header *header, int width, int height)
{
    header->size = width * height;
    header->planes = 1;
    header->compression = 3780;
    header->xresolution = 3780;
    header->planes = 1;
    header->importantcolours = 0;
}

void readPixelsBMP(FILE *file, struct Pixel **pArr, int width, int height)
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

void writePixelsBMP(FILE *file, struct Pixel **pArr, int width, int height)
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