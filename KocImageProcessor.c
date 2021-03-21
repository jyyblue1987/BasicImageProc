#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "BmpProcessor.h" //BMP Processor
#include "PpmProcessor.h" //PPM Processor
#include <Windows.h>      //update

void main(int argc, char *argv[])
{

    const char *input = argv[1];
    int r = atoi(argv[2]);
    int b = atoi(argv[3]);
    int g = atoi(argv[4]);
    const char *output = argv[5];
    const char *format = argv[6];


    FILE *file = fopen(input, "rb");
    FILE *filewrite = fopen(output, "wb");
    struct BMP_Header *header = (struct BMP_Header *)malloc(sizeof(struct BMP_Header));
    struct DIB_Header *DIBheader = (struct DIB_Header *)malloc(sizeof(struct DIB_Header));
    readBMPHeader(file, header);
    readDIBHeader(file, DIBheader);
}