/**
 * path.cpp
 *
 * Created: 19/06/2022
 *  Author: Ali Emad
 */

using namespace std;

#include "path.h"
#include <iostream>
#include <fstream>
#include "config.h"
#include "subPath.h"
#include "bitmap_image.hpp"
#include "pixArr.h"
#include<sstream>


path::path()
{
    subPathArr = NULL;
    subPathCount = 0;
    pixArr = NULL;
    innerPathPtrArr = NULL;
    innerPathCount = 0;
    firstOrderChildPtrArr = NULL;
    firstOrderChildCount = 0;
    firstOrderParentPtr = NULL;
    isFilled = false;
    isInit = false;
    nextPathPtr = NULL;
    previousPathPtr = NULL;
    xCenter = 0.0f;
    yCenter = 0.0f;
    xMin = 0.0f;
    yMin = 0.0f;
    xMax = 0.0f;
    yMax = 0.0f;
    maxLen = 0.0f;
    maxLenSquared = 0.0f;
    xCheckArr = NULL;
    xCheckRowLengths = NULL;
    yCheckArr = NULL;
    yCheckRowLengths = NULL;
    generationIndex = 0;
}

path::~path()
{
    if (isInit)
    {
        delete[] subPathArr;
        subPathArr = NULL;
        subPathCount = 0;
        #if FILL:
        int yPosMin = (int)round((float)NUMBER_OF_SEGMENTS * yMin / MAX_Y);
        int yPosMax = (int)round((float)NUMBER_OF_SEGMENTS * yMax / MAX_Y);
        int yLen = yPosMax - yPosMin + 1;
        for (int i = 0; i < yLen; i++)
            delete[] pixArr[i];
        delete[] pixArr;
        pixArr = NULL;
        delete[] innerPathPtrArr;
        innerPathPtrArr = NULL;
        innerPathCount = 0;
        delete[] firstOrderChildPtrArr;
        firstOrderChildPtrArr = NULL;
        firstOrderChildCount = 0;
        firstOrderParentPtr = NULL;
        isFilled = false;
        #endif
        isInit = false;
        nextPathPtr = NULL;
        previousPathPtr = NULL;
        #if FILL:
        xCenter = 0.0f;
        yCenter = 0.0f;
        xMin = 0.0f;
        yMin = 0.0f;
        xMax = 0.0f;
        yMax = 0.0f;
        maxLen = 0.0f;
        maxLenSquared = 0.0f;
        for (int y = 0; y < yLen; y++)
            if (xCheckRowLengths[y] > 0)
                delete[] xCheckArr[y];
        delete[] xCheckArr;
        xCheckArr = NULL;
        delete[] xCheckRowLengths;
        xCheckRowLengths = NULL;
        int xPosMin = (int)round((float)NUMBER_OF_SEGMENTS * xMin / MAX_X);
        int xPosMax = (int)round((float)NUMBER_OF_SEGMENTS * xMax / MAX_X);
        int xLen = xPosMax - xPosMin + 1;
        for (int x = 0; x < xLen; x++)
            if (yCheckRowLengths[x] > 0)
                delete[] yCheckArr[x];
        delete[] yCheckArr;
        yCheckArr = NULL;
        delete[] yCheckRowLengths;
        yCheckRowLengths = NULL;
        #endif
    }
}

void path::init(subPath* spArr, int start, int end, path* _previousPathPtr)
{
    // copying "spArr"[start:end] to "subPathArr" :
    subPathCount = end - start + 1;
    subPathArr = new subPath[subPathCount];
    for (int i = 0; i < subPathCount; i++)
        subPathArr[i].copy(spArr + start + i);

    #if FILL || DRILL:
    // creating "pixArr", that contains the path only:
    pixArr = new bool* [NUMBER_OF_SEGMENTS];
    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
    {
        pixArr[i] = new bool[NUMBER_OF_SEGMENTS];
        for (int j = 0; j < NUMBER_OF_SEGMENTS; j++)
            pixArr[i][j] = false; // blank by default
    }
    subPathArr_to_pixArr(pixArr, subPathArr, subPathCount, 1);

    // finding critical points of the path:
    find_center_and_corners();

    // finding the xCheck and yCheck arrays:
    int yPosMin = (int)round((float)NUMBER_OF_SEGMENTS * yMin / MAX_Y);
    int yPosMax = (int)round((float)NUMBER_OF_SEGMENTS * yMax / MAX_Y);
    int xPosMin = (int)round((float)NUMBER_OF_SEGMENTS * xMin / MAX_X);
    int xPosMax = (int)round((float)NUMBER_OF_SEGMENTS * xMax / MAX_X);
    xCheckArr = new int* [NUMBER_OF_SEGMENTS];
    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
        xCheckArr[i] = new int[NUMBER_OF_SEGMENTS];
    xCheckRowLengths = new int[NUMBER_OF_SEGMENTS];
    yCheckArr = new int* [NUMBER_OF_SEGMENTS];
    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
        yCheckArr[i] = new int[NUMBER_OF_SEGMENTS];
    yCheckRowLengths = new int[NUMBER_OF_SEGMENTS];
    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
    {
        xCheckRowLengths[i] = 0;
        yCheckRowLengths[i] = 0;
    }
    for (int yPos = yPosMin; yPos <= yPosMax; yPos++)
    {
        for (int xPos = xPosMin; xPos <= xPosMax; xPos++)
            if (pixArr[yPos][xPos])
                xCheckArr[yPos][xCheckRowLengths[yPos]++] = xPos;
    }
    for (int xPos = xPosMin; xPos <= xPosMax; xPos++)
    {
        for (int yPos = yPosMin; yPos <= yPosMax; yPos++)
            if (pixArr[yPos][xPos])
                yCheckArr[xPos][yCheckRowLengths[xPos]++] = yPos;
    }

    // finding max distance that any points of this path makes from its center.
    // used in accelerating the determinition of inside/outside state of a point refered to this path object.
    maxLenSquared = find_max_len_squared_from_center();
    maxLen = pow(maxLenSquared, 0.5f);

    // now the whole NUMBER_OF_SEGMENTS * NUMBER_OF_SEGMENTS arrays are not needed, only part of them is
    // chopping:
    int yLen = yPosMax - yPosMin + 1;
    int xLen = xPosMax - xPosMin + 1;
    bool** tempPixArr = new bool* [yLen];
    for (int y = 0; y < yLen; y++)
    {
        tempPixArr[y] = new bool[xLen];
        
        for (int x = 0; x < xLen; x++)
            tempPixArr[y][x] = pixArr[y + yPosMin][x + xPosMin];
    }

    //print();
    for (int yPos = 0; yPos < NUMBER_OF_SEGMENTS; yPos++)
        delete[] pixArr[yPos];

    delete[] pixArr;

    pixArr = tempPixArr;

    int** tempXCheckArr = new int* [yLen];
    int* tempXCheckRowLengths = new int[yLen];
    for (int y = 0; y < yLen; y++)
    {
        tempXCheckRowLengths[y] = xCheckRowLengths[y + yPosMin];
        tempXCheckArr[y] = new int[tempXCheckRowLengths[y]];
        for (int x = 0; x < tempXCheckRowLengths[y]; x++)
            tempXCheckArr[y][x] = xCheckArr[y + yPosMin][x] - xPosMin;
    }

    delete[] xCheckRowLengths;
    xCheckRowLengths = tempXCheckRowLengths;

    for (int yPos = 0; yPos < NUMBER_OF_SEGMENTS; yPos++)
        delete[] xCheckArr[yPos];

    delete[] xCheckArr;

    xCheckArr = tempXCheckArr;


    int** tempYCheckArr = new int* [xLen];
    int* tempYCheckRowLengths = new int[xLen];
    for (int x = 0; x < xLen; x++)
    {
        tempYCheckRowLengths[x] = yCheckRowLengths[x + xPosMin];
        tempYCheckArr[x] = new int[tempYCheckRowLengths[x]];
        for (int y = 0; y < tempYCheckRowLengths[x]; y++)
            tempYCheckArr[x][y] = yCheckArr[x + xPosMin][y] - yPosMin;
    }

    delete[] yCheckRowLengths;
    yCheckRowLengths = tempYCheckRowLengths;

    for (int xPos = 0; xPos < NUMBER_OF_SEGMENTS; xPos++)
        delete[] yCheckArr[xPos];

    delete[] yCheckArr;

    yCheckArr = tempYCheckArr;

    #endif

    // link this new path to the previous one:
    previousPathPtr = _previousPathPtr;

    // if this is not the first path
    if (previousPathPtr != NULL)
        // declare this as a next to the previous
        previousPathPtr->nextPathPtr = this;

    static int ID = 0;

    pathID = ID;
    ID++;

    // declare path is initialized
    isInit = true;
}

void path::print()
{
    cout << "printing path with address: " << this << ":" << endl;
    
    for (int i = 0; i < subPathCount; i++)
        subPathArr[i].print();

    cout << "inner paths are of adresses:" << endl;
    for (int i = 0; i < innerPathCount; i++)
        cout << innerPathPtrArr[i] << endl;

    cout << "first order children are of adresses:" << endl;
    for (int i = 0; i < firstOrderChildCount; i++)
        cout << firstOrderChildPtrArr[i] << endl;

    cout << "first order parent is of adresses:" << firstOrderParentPtr << endl;

    if (isFilled)
        cout << "path is filled" << endl;
    else
        cout << "path is not filled" << endl;

    cout << "next path in list is of adresses:" << nextPathPtr << endl;

    cout << "previous path in list is of adresses:" << previousPathPtr << endl;

    cout << "center of this path is: (" << xCenter << ", " << yCenter << ")" << endl;

    cout << "top left corner of this path's border is: (" << xMin << ", " << yMin << ")" << endl;

    cout << "bottom right corner of this path's border is: (" << xMax << ", " << yMax << ")" << endl;

    cout << "max len from center= " << maxLen << endl;
}

int is_point_inside_pixArr(bool** pixArr, int xPos, int yPos,int xPosMin, int yPosMin, int xPosMax,int yPosMax)
{
    // if point is outside of the rectangle surrounding the pixArr figure
    if (xPos < xPosMin || yPos < yPosMin || xPos > xPosMax || yPos > yPosMax)
        return 0;

    int xPosRelative = xPos - xPosMin;
    int yPosRelative = yPos - yPosMin;
    int yLen = yPosMax - yPosMin + 1;
    int xLen = xPosMax - xPosMin + 1;

    // if point ON the pixel array, it's considered to be NOT IN it
    if (pixArr[yPosRelative][xPosRelative])
        return 0;

    bool horizontalCheck, verticalCheck;
    int intersectionCount = 0;
    int lastIntersectionPos = -2;
    for (int i = 0; i < xPosRelative && i <= xLen; i++)
    {
        if (pixArr[yPosRelative][i])
        {
            if (i - lastIntersectionPos > 1)
                intersectionCount++;
            lastIntersectionPos = i;
        }
    }
    if (intersectionCount % 2 != 0) // odd
        horizontalCheck = true;
    else
        horizontalCheck = false;

    intersectionCount = 0;
    lastIntersectionPos = -2;
    for (int i = 0; i < yPosRelative && i <= yLen; i++)
    {
        if (pixArr[i][xPosRelative])
        {
            if (i - lastIntersectionPos > 1)
                intersectionCount++;
            lastIntersectionPos = i;
        }
    }
    if (intersectionCount % 2 != 0) // odd
        verticalCheck = true;
    else
        verticalCheck = false;

    // if point is not determined to be inside or outside, a deeper reseloution search would solve this!
    if (horizontalCheck != verticalCheck)
        return -1;  // undetermined (image percision error)
    return horizontalCheck ? 1 : 0;
}

int path::is_point_inside(int xPos, int yPos)
{
    int yPosMin = (int)round((float)NUMBER_OF_SEGMENTS * yMin / MAX_Y);
    int yPosMax = (int)round((float)NUMBER_OF_SEGMENTS * yMax / MAX_Y);
    int xPosMin = (int)round((float)NUMBER_OF_SEGMENTS * xMin / MAX_X);
    int xPosMax = (int)round((float)NUMBER_OF_SEGMENTS * xMax / MAX_X);

    // if point is outside of the rectangle surrounding the pixArr figure
    if (xPos < xPosMin || yPos < yPosMin || xPos > xPosMax || yPos > yPosMax)
        return 0;

    int xPosRelative = xPos - xPosMin;
    int yPosRelative = yPos - yPosMin;
    int yLen = yPosMax - yPosMin + 1;
    int xLen = xPosMax - xPosMin + 1;

    // if point ON the pixel array, it's considered to be NOT IN it
    if (pixArr[yPosRelative][xPosRelative])
        return 0;

    bool horizontalCheck, verticalCheck;
    int intersectionCount = 0;
    int lastIntersectionPos = -2;
    // doing yCheck:
    for (int i = 0; i < yCheckRowLengths[xPosRelative]; i++)
    {
        if (yCheckArr[xPosRelative][i] > yPosRelative)
            break;
        if (yCheckArr[xPosRelative][i] - lastIntersectionPos > 1)
            intersectionCount++;
        lastIntersectionPos = yCheckArr[xPosRelative][i];
    }
    if (intersectionCount % 2 != 0) // odd
        horizontalCheck = true;
    else
        horizontalCheck = false;


    intersectionCount = 0;
    lastIntersectionPos = -2;
    // doing xCheck:
    for (int i = 0; i < xCheckRowLengths[yPosRelative]; i++)
    {
        if (xCheckArr[yPosRelative][i] > xPosRelative)
            break;
        if (xCheckArr[yPosRelative][i] - lastIntersectionPos > 1)
            intersectionCount++;
        lastIntersectionPos = xCheckArr[yPosRelative][i];
    }
    if (intersectionCount % 2 != 0) // odd
        verticalCheck = true;
    else
        verticalCheck = false;

    // if point is not determined to be inside or outside, a deeper reseloution search would solve this!
    if (horizontalCheck != verticalCheck)
        return -1;  // undetermined (image percision error)
    return horizontalCheck ? 1 : 0;
}

bool path::is_path_inside(path* innerPathPtr)
{
    int xPosInnerMin = innerPathPtr->xMin * NUMBER_OF_SEGMENTS / MAX_X;
    int yPosInnerMin = innerPathPtr->yMin * NUMBER_OF_SEGMENTS / MAX_Y;
    int xPosInnerMax = innerPathPtr->xMax * NUMBER_OF_SEGMENTS / MAX_X;
    int yPosInnerMax = innerPathPtr->yMax * NUMBER_OF_SEGMENTS / MAX_Y;

    int yLen = yPosInnerMax - yPosInnerMin + 1;
    int xLen = xPosInnerMax - xPosInnerMin + 1;

    for (int yPosRelative = 0; yPosRelative < yLen; yPosRelative++)
    {
        for (int xPosRelative = 0; xPosRelative < xLen; xPosRelative++)
        {
            if (innerPathPtr->pixArr[yPosRelative][xPosRelative])
            {
                int xPos = xPosRelative + xPosInnerMin;
                int yPos = yPosRelative + yPosInnerMin;

                int pointState = is_point_inside(xPos, yPos);
                if (pointState == 0) // if one point at least is surly out, then the whole path is out. Because paths don't intersect.
                    return false;
                else if (pointState == 1) // if one point at least is surly in, then the whole path is in. Because paths don't intersect.
                    return true;
            }
        }
    }
}

void path::find_inner_paths(path* pathList)
{
    innerPathPtrArr = new path*[MAX_INNER_PATHS_NUMBER_IN_ONE_PATH];

    for (path* pathPtr=pathList; pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
    {
        // skip self
        if (pathPtr == this)
            continue;

        if (is_path_inside(pathPtr))
            innerPathPtrArr[innerPathCount++] = pathPtr;
    }

    // chop innerPathPtrArr:
    path** temp = new path * [innerPathCount];
    for (int i = 0; i < innerPathCount; i++)
        temp[i] = innerPathPtrArr[i];
    delete[] innerPathPtrArr;
    innerPathPtrArr = temp;
}

bool path::is_first_order_child(path* childPtr)
{
    // for every other inner path in this path object
    for (int i = 0; i < innerPathCount; i++)
    {
        path* innerPathPtr = innerPathPtrArr[i];

        // no need to look in the child which is being already looked for
        if (innerPathPtr == childPtr)
            continue;

        // for every inner path in of "innerPath"
        for (int j = 0; j < innerPathPtr->innerPathCount; j++)
        {
            path* innerPathOfInnerPathPtr = innerPathPtr->innerPathPtrArr[j];
            
            // if the child: "childPtr" is a child of "innerPath"
            if (childPtr == innerPathOfInnerPathPtr)
                return false; // Hence it must be a grand child to "this"
        }
    }

    // if not a child of any inner path of this path object, hence it's a first order child
    return true;    
}

void path::find_first_order_children_and_parent_them()
{
    firstOrderChildPtrArr = new path * [MAX_FOC_PATHS_NUMBER_IN_ONE_PATH];
    
    // for every inner path in this path object
    for (int i = 0; i < innerPathCount; i++)
    {
        path* innerPathPtr = innerPathPtrArr[i];

        if (is_first_order_child(innerPathPtr))
        {
            firstOrderChildPtrArr[firstOrderChildCount++] = innerPathPtr;
            innerPathPtr->firstOrderParentPtr = this;
        }
    }

    // chop firstOrderChildPtrArr:
    path** temp = new path * [firstOrderChildCount];
    for (int i = 0; i < firstOrderChildCount; i++)
        temp[i] = firstOrderChildPtrArr[i];
    delete[] firstOrderChildPtrArr;
    firstOrderChildPtrArr = temp;
}

void find_all_children_and_parents(path* pathList)
{
    for (path* pathPtr = pathList; pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
        pathPtr->find_inner_paths(pathList);
    for (path* pathPtr = pathList; pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
        pathPtr->find_first_order_children_and_parent_them();
}

void path::find_filling_states_and_generation_indexes_for_all_inner_paths()
{
    // for every first order child of this path object
    for (int i = 0; i < firstOrderChildCount; i++)
    {
        path* childPtr = firstOrderChildPtrArr[i];
        
        // it must be inverse to that of parent
        childPtr->isFilled = !isFilled;

        // its generation index should be = (that of this parent) + 1
        childPtr->generationIndex = generationIndex + 1;
        
        // find filling states of all first order children of that child
        childPtr->find_filling_states_and_generation_indexes_for_all_inner_paths();
    }
}

void path::find_center_and_corners()
{
    // init them to minimum
    int xPosMax = 0;
    int yPosMax = 0;

    // init them to maximum
    int xPosMin = NUMBER_OF_SEGMENTS - 1;
    int yPosMin = NUMBER_OF_SEGMENTS - 1;

    for (int yPos = 0; yPos < NUMBER_OF_SEGMENTS; yPos++)
    {
        for (int xPos = 0; xPos < NUMBER_OF_SEGMENTS; xPos++)
        {
            if (pixArr[yPos][xPos])
            {
                if (yPos < yPosMin)
                    yPosMin = yPos;
                if (xPos < xPosMin)
                    xPosMin = xPos;
                if (yPos > yPosMax)
                    yPosMax = yPos;
                if (xPos > xPosMax)
                    xPosMax = xPos;
            }
        }
    }

    xCenter = ((float)(xPosMax + xPosMin)) / 2.0f * (float)MAX_X / (float)NUMBER_OF_SEGMENTS;
    yCenter = ((float)(yPosMax + yPosMin)) / 2.0f * (float)MAX_Y / (float)NUMBER_OF_SEGMENTS;
    xMax = (float)xPosMax * (float)MAX_X / (float)NUMBER_OF_SEGMENTS;
    yMax = (float)yPosMax * (float)MAX_Y / (float)NUMBER_OF_SEGMENTS;
    xMin = (float)xPosMin * (float)MAX_X / (float)NUMBER_OF_SEGMENTS;
    yMin = (float)yPosMin * (float)MAX_Y / (float)NUMBER_OF_SEGMENTS;
}

float path::find_max_len_squared_from_center()
{
    int xPosMin = xMin * NUMBER_OF_SEGMENTS / MAX_X;
    int yPosMin = yMin * NUMBER_OF_SEGMENTS / MAX_Y;
    int xPosMax = xMax * NUMBER_OF_SEGMENTS / MAX_X;
    int yPosMax = yMax * NUMBER_OF_SEGMENTS / MAX_Y;
    float maxLenSquared = 0.0f;
    for (int yPos = yPosMin; yPos <= yPosMax; yPos++)
    {
        for (int xPos = xPosMin; xPos <= xPosMax; xPos++)
        {
            if (pixArr[yPos][xPos])
            {
                float xDash = xPos * MAX_X / (float)NUMBER_OF_SEGMENTS - xCenter;
                float yDash = yPos * MAX_Y / (float)NUMBER_OF_SEGMENTS - yCenter;
                float lenSquared = pow(yDash, 2.0f) + pow(xDash, 2.0f);
                if (lenSquared > maxLenSquared)
                    maxLenSquared = lenSquared;
            }
        }
    }
    return maxLenSquared;
}

void path::shift_path(float xShift, float yShift)
{
    for (int i = 0; i < subPathCount; i++)
    {
        for (int j = 0; j < subPathArr[i].pointCounter; j++)
        {
            subPathArr[i].points[0][j] += xShift;
            subPathArr[i].points[1][j] += yShift;
        }
    }
}

//void path::whiten_path_from_img(bitmap_image* imgPtr, const char* imgDir)
//{
//    rgb_t white;
//    white.red = 225;
//    white.green = 225;
//    white.blue = 225;
//    int toolRadious = TOOL_DIAMETER / 2;
//    int yPosMin = int(round(yMin * ((float)NUMBER_OF_SEGMENTS) / MAX_Y));
//    int xPosMin = int(round(xMin * ((float)NUMBER_OF_SEGMENTS) / MAX_X));
//    int yPosMax = int(round(yMax * ((float)NUMBER_OF_SEGMENTS) / MAX_Y));
//    int xPosMax = int(round(xMax * ((float)NUMBER_OF_SEGMENTS) / MAX_X));
//
//    for (int yPos = yPosMin; yPos <= yPosMax; yPos++)
//    {
//        for (int xPos = xPosMin; xPos <= xPosMax; xPos++)
//        {
//            // if this is a point which the tool will pass on, remove it and its tool diameter surrounding pixles from the temp input file:
//            if (pixArr[yPos][xPos])
//            {
//                // convert this point to pixels dimentions:
//                int x = int(round(xPos * MAX_X / ((float)NUMBER_OF_SEGMENTS)));
//                int y = int(round(yPos * MAX_Y / ((float)NUMBER_OF_SEGMENTS)));
//                for (int yPix = y - toolRadious; yPix < y + toolRadious; yPix++)
//                {
//                    for (int xPix = x - toolRadious; xPix < x + toolRadious; xPix++)
//                        imgPtr->set_pixel(xPix, yPix, white);
//                }
//            }
//        }
//    }
//    imgPtr->save_image(imgDir);
//}
//
//bitmap_image* path::create_filled_img_and_remove_it_from_bmp_temp_image(const char* tempImgDir, int deltaXPix, int deltaYPix)
//{
//    // delete (whiten) this path (its main oter track only) from the temp input bmp file
//    // thickniss will be toolDiameter
//    // open that image
//    bitmap_image tempImg(tempImgDir);
//    //loop on this path's pixels, and remove thier surrounding square of TOOL_DIAMETER
//    int yPosMin = int(round(yMin * ((float)NUMBER_OF_SEGMENTS) / MAX_Y));
//    int xPosMin = int(round(xMin * ((float)NUMBER_OF_SEGMENTS) / MAX_X));
//    int yPosMax = int(round(yMax * ((float)NUMBER_OF_SEGMENTS) / MAX_Y));
//    int xPosMax = int(round(xMax * ((float)NUMBER_OF_SEGMENTS) / MAX_X));
//    int xLen = xPosMax - xPosMin + 1;
//    int yLen = yPosMax - yPosMin + 1;
//
//    rgb_t white;
//    white.red = 225;
//    white.green = 225;
//    white.blue = 225;
//
//    int toolRadious = TOOL_DIAMETER / 2;
//    for (int yPosRelative = 0; yPosRelative < yLen; yPosRelative++)
//    {
//        for (int xPosRelative = 0; xPosRelative < xLen; xPosRelative++)
//        {
//            // if this is a point which the tool will pass on, remove it and its tool diameter surrounding pixles from the temp input file:
//            if (pixArr[yPosRelative][xPosRelative])
//            {
//                // convert this point to pixels dimentions:
//                int x = int(round((xPosRelative + xPosMin) * MAX_X / ((float)NUMBER_OF_SEGMENTS))) - deltaXPix;
//                int y = int(round((yPosRelative + yPosMin) * MAX_Y / ((float)NUMBER_OF_SEGMENTS))) - deltaYPix;
//                for (int yPix = y - toolRadious; yPix < y + toolRadious; yPix++)
//                {
//                    for (int xPix = x - toolRadious; xPix < x + toolRadious; xPix++)
//                        tempImg.set_pixel(xPix, yPix, white);
//                }
//            }
//        }
//    }
//
//    // if this path is not filled, then there won't be a filledPixArr
//    // (it will be fully white, assuming all of this path's children had been erased/whitened previously)
//    if (!isFilled)
//    {
//        tempImg.save_image(TEMP_BMP_FILE_DIR);
//        return NULL;
//    }
//
//    // but if this path was filled, then filledPixArr would have data:
//    // it will be of the same size as the rectangle with:
//    // top left corner of:     xMin, yMin
//    // bottom right corner of: xMax, yMax
//    int newTempImgHeight = (int)(round(yMax)) - (int)(round(yMin)) + 1;
//    int newTempImgWidth = (int)(round(xMax)) - (int)(round(xMin)) + 1;
//    bitmap_image* filledImgPtr = new bitmap_image[1];
//    filledImgPtr->setwidth_height(newTempImgWidth, newTempImgHeight);
//
//    // copying the filling of this path and whatever is inside it from the tempImg file, and whitening these pixels in it, too.
//    rgb_t color;
//    rgb_t black;
//    black.red = 0;
//    black.green = 0;
//    black.blue = 0;
//    for (int yPix = (int)(round(yMin))-deltaYPix; yPix <= (int)(round(yMax)) - deltaYPix; yPix++)
//    {
//        for (int xPix = (int)(round(xMin)) - deltaXPix; xPix <= (int)(round(xMax)) - deltaXPix; xPix++)
//        {
//            tempImg.get_pixel(xPix, yPix, color);
//            // if this pix is black
//            if (color.red == 0)
//            {
//                // check if it's inside this path:
//                int xPos = ((xPix + deltaXPix) * NUMBER_OF_SEGMENTS) / ((int)MAX_X);
//                int yPos = ((yPix + deltaYPix) * NUMBER_OF_SEGMENTS) / ((int)MAX_Y);
//                if (is_point_inside(xPos, yPos))
//                {
//                    filledImgPtr->set_pixel(xPix - (int)(round(xMin) + deltaXPix), yPix - (int)(round(yMin)) + deltaYPix, black);
//                    for (int _yPix = yPix - toolRadious; _yPix < yPix + toolRadious; _yPix++)
//                    {
//                        for (int _xPix = xPix - toolRadious; _xPix < xPix + toolRadious; _xPix++)
//                            tempImg.set_pixel(xPix, yPix, white);
//                    }
//                    continue;
//                }
//            }
//            filledImgPtr->set_pixel((xPix - (int)(round(xMin))), (yPix - (int)(round(yMin))), white);
//        }
//    }
//    tempImg.save_image(tempImgDir);
//
//    //string thisTempDir = 
//
//    filledImgPtr->save_image(TEMP_SUB_BMP_FILE_DIR);
//    return filledImgPtr;
//}

bool is_black(rgb_t color)
{
    return color.red == 0;
}


void path::whiten_from_tmpImg_and_generate_selfTmpImg(const char* tmpImgDir, int xTmpImgMin, int yTmpImgMin)
{
    // open tmpImg
    bitmap_image tmpImg(tmpImgDir);

    // create selfTmpImg, which dimentions will be the same as the containing rectangle of self:
    int selfWidth = xMax - xMin + 1;
    int selfHeight = yMax - yMin + 1;
    bitmap_image selfTmpImg(selfWidth, selfHeight);

    int toolRadious = TOOL_DIAMETER / 2;

    // whiten self from tmpImg, and whiten selfTmpImg fully:
    for (int y = 0; y < selfHeight; y++)
    {
        for (int x = 0; x < selfWidth; x++)
        {
            if (pixArr[y][x])
            {
                int yRelativeInTmp = y + yMin - yTmpImgMin;
                int xRelativeInTmp = x + xMin - xTmpImgMin;
                for (int yTmp = yRelativeInTmp - toolRadious; yTmp <= yRelativeInTmp + toolRadious; yTmp++)
                    for (int xTmp = xRelativeInTmp - toolRadious; xTmp <= xRelativeInTmp + toolRadious; xTmp++)
                        tmpImg.set_pixel(xTmp, yTmp, WHITE_COLOR);
            }
            selfTmpImg.set_pixel(x, y, WHITE_COLOR);
        }
    }

    if (!isFilled)
    {
        tmpImg.save_image(tmpImgDir);
        return;
    }

    // copy whatever is inside self from tmpImg to selfTmpImg:
    rgb_t color;
    for (int y = yMin; y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {
            tmpImg.get_pixel(x - xTmpImgMin, y - yTmpImgMin, color);
            if (is_black(color))
            {
                if (is_point_inside(x, y))
                {
                    int yRelativeSelfTmp = y - yMin;
                    int xRelativeSelfTmp = x - xMin;
                    selfTmpImg.set_pixel(xRelativeSelfTmp, yRelativeSelfTmp, BLACK_COLOR);
                }
            }
        }
    }

    // whiten all what'h just been copied:
    for (int y = yMin; y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {
            tmpImg.get_pixel(x - xTmpImgMin, y - yTmpImgMin, color);
            if (is_black(color))
            {
                if (is_point_inside(x, y))
                    tmpImg.set_pixel(x - xTmpImgMin, y - yTmpImgMin, WHITE_COLOR);
            }
        }
    }

    tmpImg.save_image(tmpImgDir);

    string selfTmpImgDir = "temp/";
    string IDStr = to_string(pathID);
    selfTmpImgDir += IDStr + ".bmp";

    selfTmpImg.save_image(selfTmpImgDir.c_str());
}

void path::swap_with(path* pathPtr)
{
    path* tempThisPrevious = previousPathPtr;
    path* tempThisNext = nextPathPtr;

    path* tempPathPtrPrevious = pathPtr->previousPathPtr;
    path* tempPathPtrNext = pathPtr->nextPathPtr;

    bool isThisFollowingPathPtr = (pathPtr->nextPathPtr == this) ? true : false;
    bool isThisLeadingPathPtr = (pathPtr->previousPathPtr == this) ? true : false;


    if (tempThisPrevious != NULL)
        tempThisPrevious->nextPathPtr = pathPtr;
    if (tempThisNext != NULL)
        tempThisNext->previousPathPtr = pathPtr;

    if (tempPathPtrPrevious != NULL)
        tempPathPtrPrevious->nextPathPtr = this;
    if (tempPathPtrNext != NULL)
        tempPathPtrNext->previousPathPtr = this;

    if (isThisFollowingPathPtr)
    {
        pathPtr->nextPathPtr = tempThisNext;
        pathPtr->previousPathPtr = this;
        nextPathPtr = pathPtr;
        previousPathPtr = tempPathPtrPrevious;
    }
    else if (isThisLeadingPathPtr)
    {
        nextPathPtr = tempPathPtrNext;
        previousPathPtr = pathPtr;
        pathPtr->nextPathPtr = this;
        pathPtr->previousPathPtr = tempThisPrevious;
    }
    else
    {
        nextPathPtr = tempPathPtrNext;
        previousPathPtr = tempPathPtrPrevious;
        pathPtr->nextPathPtr = tempThisNext;
        pathPtr->previousPathPtr = tempThisPrevious;
    }
}

path* path::find_head_of_the_list_of_this()
{
    path* headPtr;
    for (headPtr = this; headPtr->previousPathPtr != NULL; headPtr = headPtr->previousPathPtr)
    {
        cout << headPtr << endl;
        cout << headPtr->previousPathPtr << endl;
        cout << endl;
    }
    
    return headPtr;
}

void find_all_filling_states_and_generation_indexes(path* pathList)
{
    // for every path in pathList
    for (path* pathPtr = pathList; pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
    {
        // if pathPtr has no parent
        if (pathPtr->firstOrderParentPtr == NULL)
        {
            // it must be filled
            pathPtr->isFilled = true;
            
            // its generation index is zero
            // no need to write it zero here, it's already done in the instructor function.
            //pathPtr->generationIndex = 0;
            
            // find filling states for all of its inner paths
            pathPtr->find_filling_states_and_generation_indexes_for_all_inner_paths();
        }
    }
}

path* find_pathList(subPath* subPathArr, int subPathCount)
{
    int pathCount = 0;
    int* zIndexes = new int[MAX_Z_TYPE_NUMBER_IN_WHOLE_FIG];
    for (int i = 1; i < subPathCount; i++)
        if (subPathArr[i].type == 'Z')
            zIndexes[++pathCount] = i;

    path* pathList = new path[pathCount];
    pathList[0].init(subPathArr, 0, zIndexes[1], NULL);

    for (int i = 1; i < pathCount; i++)
        pathList[i].init(subPathArr, zIndexes[i] + 1, zIndexes[i + 1], pathList + i - 1);

    #if FILL || DRILL:
    find_all_children_and_parents(pathList);
    find_all_filling_states_and_generation_indexes(pathList);
    #endif

    delete[] zIndexes;

    return pathList;
}

void path_to_bmp(path* pathPtr, const char* fileNameStr)
{
    pixArr_to_bmp(pathPtr->pixArr, fileNameStr);
}

bool** pathList_to_pixArr(path* pathList)
{
    bool** pixArr = new bool* [NUMBER_OF_SEGMENTS];
    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
    {
        pixArr[i] = new bool[NUMBER_OF_SEGMENTS];
        for (int j = 0; j < NUMBER_OF_SEGMENTS; j++)
            pixArr[i][j] = false;
    }

    for (path* pathPtr=pathList; pathPtr!=NULL; pathPtr = pathPtr->nextPathPtr )
    {
        for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
        {
            for (int j = 0; j < NUMBER_OF_SEGMENTS; j++)
                if (pathPtr->pixArr[i][j])
                    pixArr[i][j] = true;
        }
    }

    return pixArr;
}

void pathList_to_bmp(path* pathList, const char* fileNameStr)
{

    bool** pixArr = pathList_to_pixArr(pathList);
    pixArr_to_bmp(pixArr, fileNameStr);

    delete[] pixArr[0];
    delete[] pixArr[1];
    delete[] pixArr;
}

path** find_sorted_ptrArr_of_paths(path* pathList)
{
    // sort paths in an array, the most grand parent is indexed max, and to most grand child is indexed 0
    // if two paths have the same generation index, they are given two consecutive indexes no matter which is first.
    // sort paths in this pointer array, it's terminated with NULL pointer.
    path** pathPtrArr = new path * [MAX_PATH_NUMBER_IN_WHOLE_FIG];
    int n = 0;
    pathList = pathList->find_head_of_the_list_of_this();
    for (path* pathPtr = pathList; pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
        pathPtrArr[n++] = pathPtr;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (pathPtrArr[j]->generationIndex > pathPtrArr[i]->generationIndex)
            {
                path* temp = pathPtrArr[j];
                pathPtrArr[j] = pathPtrArr[i];
                pathPtrArr[i] = temp;
            }

    // chop
    path** temp = new path * [n+1];
    for (int i = 0; i < n; i++)
        temp[i] = pathPtrArr[i];
    temp[n] = NULL;
    delete[] pathPtrArr;
    
    return temp;
}

path* find_most_parent(path* pList)
{
    path** pathPtrArr = new path * [MAX_PATH_NUMBER_IN_WHOLE_FIG];
    int n = 0;
    pList = pList->find_head_of_the_list_of_this();
    for (path* pathPtr = pList; pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
        pathPtrArr[n++] = pathPtr;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (pathPtrArr[j]->generationIndex < pathPtrArr[i]->generationIndex)
            {
                path* temp = pathPtrArr[j];
                pathPtrArr[j] = pathPtrArr[i];
                pathPtrArr[i] = temp;
            }

    pList = pathPtrArr[0];
    delete[] pathPtrArr;
    return pList;
}
