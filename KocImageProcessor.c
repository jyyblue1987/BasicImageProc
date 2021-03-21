#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "BmpProcessor.h" //BMP Processor
#include "PpmProcessor.h" //PPM Processor
#include "PixelProcessor.h"

void main(int argc, char *argv[])
{
    const char *input = argv[1];


    if( argc < 2 )  // check if input file name is provided
    {
        printf("%s\n", "Please provide file name");
        return;
    }

    int opt; 
    
    int r = 0, g = 0, b = 0;
    char output[255] = "output.bmp";
    char format[10] = "BMP";

    while((opt = getopt(argc, argv, "o:t:r:g:b:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'o':                  
                printf("output file: %s\n", optarg);
                strcpy(output, optarg);
                break;
            case 't':                  
                printf("file format: %s\n", optarg);
                strcpy(format, optarg);
                break;
            case 'r':
                r = atoi(optarg);                
                break;
            case 'g':
                g = atoi(optarg);                
                break;
            case 'b':
                b = atoi(optarg);                
                break;
        }  
    }  

    printf("R = %d, G = %d, B = %d\n", r, g, b);

    FILE *file = fopen(input, "rb");
    if( file == NULL )
    {
        printf("%s", "Invalid File\n");
        return;
    }
    
    char *p = strrchr(input, '.');  // check extension
    if( p == NULL )
    if( file == NULL )
    {
        printf("%s", "Invalid File\n");
        return;
    }

    struct Pixel** img = NULL;
    int width = 0, height = 0;
    if( strcmp(p + 1, "bmp") == 0 )
    {
        struct BMP_Header *header = (struct BMP_Header *)malloc(sizeof(struct BMP_Header));
        struct DIB_Header *DIBheader = (struct DIB_Header *)malloc(sizeof(struct DIB_Header));
        readBMPHeader(file, header);
        readDIBHeader(file, DIBheader);

        free(header);
        free(DIBheader);
    }
    
    if( strcmp( p + 1, "ppm") == 0 )
    {
        struct PPM_Header *header = (struct PPM_Header *)malloc(sizeof(struct BMP_Header));        
        readPPMHeader(file, header);

        width = header->width;
        height = header->height;

        img = (struct Pixel**) malloc(height * sizeof(struct Pixel*));
        for(int i = 0; i < height; i++)
            img[i] = (struct Pixel*) malloc(width * sizeof(struct Pixel));

        readPixelsPPM(file, img, width, height);
        
        for(int i = 0; i < height; i++)
            free(img[i]);

        free(header);
    }

    fclose(file);

    FILE *filewrite = fopen(output, "wb");
    if( filewrite == NULL )
    {
        free(img);
        return;
    }

    if( strcmp(format, "BMP") == 0 )
    {   
        printf("Save Image To %s with BMP\n", output);
        struct BMP_Header *header = (struct BMP_Header *)malloc(sizeof(struct BMP_Header));
        struct DIB_Header *DIBheader = (struct DIB_Header *)malloc(sizeof(struct DIB_Header));
        
        makeBMPHeader(header, width, height);
        makeDIBHeader(DIBheader, width, height);
        
        writeBMPHeader(filewrite, header);
        writeDIBHeader(filewrite, DIBheader);

        writePixelsBMP(filewrite, img, width, height);

        free(header);
        free(DIBheader);        
    }

    if( strcmp(format, "PPM") == 0 )
    {   
        printf("Save Image To %s with PPM\n", output);
        struct PPM_Header *header = (struct PPM_Header *)malloc(sizeof(struct PPM_Header));

        makePPMHeader(header, width, height);        
        writePPMHeader(filewrite, header);
        writePixelsPPM(filewrite, img, width, height);

        free(header);
    }

    free(img);
    
}