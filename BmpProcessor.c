
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BmpProcessor.h"

#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

void readBMPHeader(FILE *file, struct BMP_Header *header)
{

    printf("*****BMP HEADER*****\n");

    fread(&header->signature, sizeof(char) * 2, 1, file);
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
    fwrite(&header->signature, sizeof(char)*2, 1 , file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserved1, sizeof(short), 1, file);
    fwrite(&header->reserved2, sizeof(short), 1, file);
    fwrite(&header->offset_pixel_array, sizeof(int), 1, file);
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
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->width, sizeof(int), 1, file);
    fwrite(&header->height, sizeof(int), 1, file);
    fwrite(&header->planes, sizeof(short), 1, file);
    fwrite(&header->bits, sizeof(short), 1, file);
    fwrite(&header->compression, sizeof(int), 1, file);
    fwrite(&header->imagesize, sizeof(int), 1, file);
    fwrite(&header->xresolution, sizeof(int), 1, file);
    fwrite(&header->yresolution, sizeof(int), 1, file);
    fwrite(&header->ncolours, sizeof(int), 1, file);
    fwrite(&header->importantcolours, sizeof(int), 1, file);  
}

void makeBMPHeader(struct BMP_Header *header, int width, int height)
{
    strcpy(header->signature, "BM");
    header->reserved1 = 0;
    header->reserved2 = 0;

    int paddedRowSize = width * 3;
    if( width % 4 != 0)
        paddedRowSize = (width / 4 + 1) * 3;

    int fileSize = paddedRowSize*height + HEADER_SIZE + INFO_HEADER_SIZE;
    header->size = fileSize;

    header->offset_pixel_array = HEADER_SIZE + INFO_HEADER_SIZE;
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
    header->size = INFO_HEADER_SIZE;
    header->width = width;
    header->height = height;    
    header->planes = 1;
    header->bits = 24;
    header->compression = 0;        
    header->imagesize = width * height * 3;
    header->xresolution = 11811;
    header->yresolution = 11811;
    header->ncolours = 0;
    header->importantcolours = 0;
}

void readPixelsBMP(FILE *file, struct Pixel **pArr, int width, int height)
{
    int i, j;
    
    int paddedRowSize = width * 3;
    if( width % 4 != 0)
        paddedRowSize = (width / 4 + 1) * 3;

    int unpaddedRowSize = width * 3;
    int padding = paddedRowSize - unpaddedRowSize;

    char *temp = NULL;
    if (padding != 0)
    {
        temp = (char *) malloc(padding * sizeof(char));
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fread(&pArr[height - i - 1][j].b, 1, 1, file);
            fread(&pArr[height - i - 1][j].g, 1, 1, file);
            fread(&pArr[height - i - 1][j].r, 1, 1, file);
        }
        if (padding != 0)
        {
            fwrite(temp, padding, 1, file);
        }
    }

    if( padding != 0 )
        free(temp);
}

void writePixelsBMP(FILE *file, struct Pixel **pArr, int width, int height)
{
    int i, j;
    
    int paddedRowSize = width * 3;
    if( width % 4 != 0)
        paddedRowSize = (width / 4 + 1) * 3;

    int unpaddedRowSize = width * 3;
    int padding = paddedRowSize - unpaddedRowSize;

    char *temp = NULL;
    if (padding != 0)
    {
        temp = (char *) malloc(padding * sizeof(char));
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fwrite(&pArr[height - i - 1][j].b, 1, 1, file);
            fwrite(&pArr[height - i - 1][j].g, 1, 1, file);
            fwrite(&pArr[height - i - 1][j].r, 1, 1, file);
        }
        if (padding != 0)
        {
            fwrite(temp, padding, 1, file);
        }
    }

    if( padding != 0 )
        free(temp);
}