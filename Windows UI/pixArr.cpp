/**
 * pixArr.cpp
 *
 * Created: 01/07/2022
 *  Author: Ali Emad
 */

using namespace std;

#include "pixArr.h"
#include <iostream>
#include <fstream>
#include "config.h"
#include "bitmap_image.hpp"


void pixArr_to_bmp(bool** pixArr, const char* fileNameStr)
{
    bitmap_image output(NUMBER_OF_SEGMENTS, NUMBER_OF_SEGMENTS);
    rgb_t white;
    white.blue = 255;
    white.red = 255;
    white.green = 255;
    rgb_t black;
    black.red = 0;
    black.green = 0;
    black.blue = 0;

    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
    {
        for (int j = 0; j < NUMBER_OF_SEGMENTS; j++)
        {
            if (pixArr[i][j])
                output.set_pixel(j, i, black);
            else
                output.set_pixel(j, i, white);
        }
    }
    output.save_image(fileNameStr);
}