#include "PixelProcessor.h"

void colorShiftPixels(struct Pixel **pArr, int width, int height, int rShift, int gShift, int bShift)
{
    int r = 0, g = 0, b = 0;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int r = pArr[h][w].r;
            int g = pArr[h][w].g;
            int b = pArr[h][w].b;
            
            r += rShift;
            b += bShift;
            g += gShift;

            if( r > 255 )
                r = 255;
            if( r < 0 )
                r = 0;

            if( g > 255 )
                g = 255;
            if( g < 0 )
                g = 0;

            if( b > 255 )
                b = 255;
            if( b < 0 )
                b = 0;

            pArr[h][w].r = r;
            pArr[h][w].g = g;
            pArr[h][w].b = b;
        }
    }
}