/**
 * subPath.cpp
 *
 * Created: 19/06/2022 12:07:12 am
 *  Author: Ali Emad
 */


#include "subPath.h"
#include <iostream>
#include <string>
#include "config.h"
#include "file_interface.h"
#include "pixArr.h"


using namespace std;


/**
 * default constructor. sets initial unused vales to the variables of this subPath object. foolish but used to uvoid warnings.
 */
subPath::subPath()
{
    type = '\0';
    points = NULL;
    pointCounter = -1;
    isInit = false;
}

/**
 * destructor, frees all the allocated memory in points array.
 */
subPath::~subPath()
{
    if (isInit)
    {
        delete[] points[0];
        delete[] points[1];
        delete[] points;
        isInit = false;
    }
}

/**
 * Initialize the sub path
 *
 * @param[in] _type the type of the subPath object
 */
void subPath::init(char _type)
{
    type = _type;
    points = new float* [2];
    points[0] = new float[MAX_POINTS_NUMBER_IN_ONE_SUBPATH]; // the huge oversize of allocation is to be chopped later, initially large for speed.
    points[1] = new float[MAX_POINTS_NUMBER_IN_ONE_SUBPATH]; // the huge oversize of allocation is to be chopped later, initially large for speed.
    pointCounter = 0;
    isInit = true;
}

/**
 * Appends a new point to points array
 *
 * @param[in] x the abslute x-coordinate of the new point
 * @param[in] y the abslute y-coordinate of the new point
 */
void subPath::add_point(float x, float y)
{
    points[0][pointCounter] = x;
    points[1][pointCounter] = y;
    pointCounter++;
    #if DEBUG_MODE
    if (pointCounter >= MAX_POINTS_NUMBER_IN_ONE_SUBPATH)
    {
        cout << "Error in: subPath.cpp/void subPath::add_point(float x, float y)" << endl;
        cout << "pointCounter > MAX_POINTS_NUMBER_IN_ONE_SUBPATH !" << endl;
        exit(-1);
    }
    #endif
}

/**
 * frees the un-used memory of points arr.
 * better be used just after completing the operation of adding new points to this subPath object.
 *
 *
 * for SMARTASSES only!:
 * why where they allocated in the first place?!... To fasten the operation of adding multiple new points without
 * having to copy whole array each few times of addition.
 *
 * why not use linked-list?!... That's one way to do it, but:
 * a) pointer size in windows-x64 C++ is 8-bytes, while float pointer size is only 4-bits!
 * b) leaving few unused pointers at each subPath would result in "foo" allocated mega-bytes of memory,
 *    worst case is a crach if the drawing input of the program is too large and detailed.
 *
 * SO SORRY FOR BEING AGRISSIVE, JUST HATE SMARTASSES, NOT YOU LOVE!...
 */
void subPath::chop_empty_memory(void)
{
    if (isInit)
    {
        float* tempXArr = new float[pointCounter];
        float* tempYArr = new float[pointCounter];
        for (int i = 0; i < pointCounter; i++)
        {
            tempXArr[i] = points[0][i];
            tempYArr[i] = points[1][i];
        }
        delete points[0];
        delete points[1];
        points[0] = tempXArr;
        points[1] = tempYArr;
    }
}

/**
 * prints type of the subPath object in a line, then prints all of its points, each in a line, too.
 */
void subPath::print(void)
{
    if (isInit)
    {
        cout << type << endl;
        if (type != 'Z')
            for (int i = 0; i < pointCounter; i++)
                cout << points[0][i] << "," << points[1][i] << endl;
    }
    else
        cout << "subPath is empty... nothing to print" << endl;
}

/**
 * delete this object's current data - if any -,
 * copies all variables of another subPath object to it, and states it initiallized.
 *
 * @param[in] spPtr pointer of the subPath object to be copied.
 */
void subPath::copy(subPath* spPtr)
{
    type = spPtr->type;
    pointCounter = spPtr->pointCounter;
    if (isInit)
    {
        delete points[0];
        delete points[1];
    }
    else
        points = new float* [2];
    points[0] = new float[pointCounter];
    points[1] = new float[pointCounter];
    for (int i = 0; i < pointCounter; i++)
    {
        points[0][i] = spPtr->points[0][i];
        points[1][i] = spPtr->points[1][i];
    }
    isInit = true;
}

/**
 * creates an array of subPaths from the raw file data.
 *
 * @param[out], an array of two pointers, first points at
 * the array of subPaths computed from the raw data 'dataPtr'. Second points at the number of them.
 * @param[in] dataPtr, pointer to raw data string.
 */
void** find_subPathArr(string* transformStrPtr, string* pathStrPtr)
{
    // get translate and scale data:
    int seperatorIndex = transformStrPtr->find(",");
    int closerIndex = transformStrPtr->find(")");
    float xTranslate = str_to_float(transformStrPtr, 24, seperatorIndex - 1);
    float yTranslate = str_to_float(transformStrPtr, seperatorIndex + 1, closerIndex - 1);

    int openerIndex = transformStrPtr->find("(", closerIndex + 6);
    seperatorIndex = transformStrPtr->find(",", openerIndex + 1);
    closerIndex = transformStrPtr->find(")", seperatorIndex + 1);
    float xScale = str_to_float(transformStrPtr, openerIndex + 1, seperatorIndex - 1);
    float yScale = str_to_float(transformStrPtr, seperatorIndex + 1, closerIndex - 1);
    
    subPath* subPathArr = new subPath[MAX_SUBPATHS_NUMBER_IN_ONE_SUBPATHARR];
    int subpathCount = 0;
    float currentX = 0.0f;
    float currentY = 0.0f;
    float prevPathX = 0.0f;
    float prevPathY = 0.0f;
    string* dataPtr = pathStrPtr;
    int iMax = (int)dataPtr->length();
    for (int i = 0; i < iMax; i++)
    {
        if (is_in_str((*dataPtr)[i], "LC"))
        {
            subPathArr[subpathCount].init((*dataPtr)[i]);
            i++;
            while (1)
            {
                int seperatorIndex = dataPtr->find(" ", i);
                int endOfYIndex = dataPtr->find(" ", seperatorIndex + 1) - 1;
                currentX = ((float)str_to_int(dataPtr, i, seperatorIndex - 1)) * xScale + xTranslate;
                currentY = ((float)str_to_int(dataPtr, seperatorIndex + 1, endOfYIndex)) * yScale + yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }

        else if ((*dataPtr)[i] == 'l')
        {
            subPathArr[subpathCount].init('L');
            i++;
            while (1)
            {
                int seperatorIndex = dataPtr->find(" ", i);
                int endOfYIndex = dataPtr->find(" ", seperatorIndex + 1) - 1;
                currentX += ((float)str_to_int(dataPtr, i, seperatorIndex - 1)) * xScale;// +xTranslate;
                currentY += ((float)str_to_int(dataPtr, seperatorIndex + 1, endOfYIndex)) * yScale;// +yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }
        else if ((*dataPtr)[i] == 'V')
        {
            subPathArr[subpathCount].init('L');
            i++;
            while (1)
            {
                int endOfYIndex = dataPtr->find(" ", i + 1) - 1;
                currentY = ((float)str_to_int(dataPtr, i, endOfYIndex)) * yScale + yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }
        else if ((*dataPtr)[i] == 'v')
        {
            subPathArr[subpathCount].init('L');
            i++;
            while (1)
            {
                int endOfYIndex = dataPtr->find(" ", i + 1) - 1;
                currentY += ((float)str_to_int(dataPtr, i, endOfYIndex)) * yScale;// + yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }

        else if ((*dataPtr)[i] == 'H')
        {
            subPathArr[subpathCount].init('L');
            i++;
            while (1)
            {
                int endOfXIndex = dataPtr->find(" ", i + 1) - 1;
                currentX = ((float)str_to_int(dataPtr, i, endOfXIndex)) * xScale + xTranslate;
                i = endOfXIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }
        else if ((*dataPtr)[i] == 'h')
        {
            subPathArr[subpathCount].init('L');
            i += 2;
            while (1)
            {
                int endOfXIndex = dataPtr->find(" ", i + 1) - 1;
                currentX += ((float)str_to_int(dataPtr, i, endOfXIndex)) * xScale;// + xTranslate;
                i = endOfXIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }


        else if ((*dataPtr)[i] == 'c')
        {
            subPathArr[subpathCount].init('C');
            i++;
            float prevX = currentX;
            float prevY = currentY;
            int cPointsCount = 0;
            while (1)
            {
                int seperatorIndex = dataPtr->find(" ", i);
                int endOfYIndex = dataPtr->find(" ", seperatorIndex + 1) - 1;
                currentX = ((float)str_to_int(dataPtr, i, seperatorIndex - 1)) * xScale + prevX;// + xTranslate;
                currentY = ((float)str_to_int(dataPtr, seperatorIndex + 1, endOfYIndex)) * yScale + prevY;// + yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                cPointsCount++;
                if (!(cPointsCount % 3))
                {
                    prevX = currentX;
                    prevY = currentY;
                }
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }

        else if ((*dataPtr)[i] == 'M')
        {
            bool firstM = true;
            subPathArr[subpathCount].init('M');
            i++;
            while (1)
            {
                int seperatorIndex = dataPtr->find(" ", i);
                int endOfYIndex = dataPtr->find(" ", seperatorIndex + 1) - 1;
                currentX = ((float)str_to_int(dataPtr, i, seperatorIndex - 1)) * xScale + xTranslate;
                currentY = ((float)str_to_int(dataPtr, seperatorIndex + 1, endOfYIndex)) * yScale + yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (firstM)
                {
                    prevPathX = currentX;
                    prevPathY = currentY;
                    firstM = false;
                }
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }

        else if ((*dataPtr)[i] == 'm')
        {
            bool firstM = true;
            subPathArr[subpathCount].init('M');
            i++;
            while (1)
            {
                int seperatorIndex = dataPtr->find(" ", i);
                int endOfYIndex = dataPtr->find(" ", seperatorIndex + 1) - 1;
                currentX += ((float)str_to_int(dataPtr, i, seperatorIndex - 1)) * xScale;// + xTranslate;
                currentY += ((float)str_to_int(dataPtr, seperatorIndex + 1, endOfYIndex)) * yScale;// + yTranslate;
                i = endOfYIndex + 2;
                subPathArr[subpathCount].add_point(currentX, currentY);
                if (firstM)
                {
                    prevPathX = currentX;
                    prevPathY = currentY;
                    firstM = false;
                }
                if (!is_number((*dataPtr)[i]))
                {
                    i--;
                    subPathArr[subpathCount].chop_empty_memory();
                    break;
                }
            }
            subpathCount++;
        }

        else if ((*dataPtr)[i] == 'Z' || (*dataPtr)[i] == 'z')
        {
            i++;
            subPathArr[subpathCount].init('Z');
            currentX = prevPathX;
            currentY = prevPathY;
            subPathArr[subpathCount].add_point(currentX, currentY);
            subPathArr[subpathCount].chop_empty_memory();
            subpathCount++;
        }   
    }
    // chop empty memory cells in "subPathArr":
    subPath* subPathArrChopped = new subPath[subpathCount];
    for (int i = 0; i < subpathCount; i++)
        subPathArrChopped[i].copy(subPathArr + i);
    delete[] subPathArr;

    void** voidPtrArr = new void* [2];
    int* subPathCountPtr = new int[1];
    *subPathCountPtr = subpathCount;
    voidPtrArr[0] = subPathCountPtr;
    voidPtrArr[1] = subPathArrChopped;
    return voidPtrArr;
}

void subPathArr_to_pixArr(bool** pixArr, subPath* subPathArr, int subPathCount, int sizeFactor)
{
    float lastX = subPathArr[0].points[0][0];
    float lastY = subPathArr[0].points[1][0];
    int numberOfSegments = NUMBER_OF_SEGMENTS * sizeFactor;
    int maxSegmentsNumberInOneCurve = MAX_SEGMENTS_NUMBER_IN_ONE_CURVE * sizeFactor;
    // init pixArr blank:
    for (int i = 0; i < numberOfSegments; i++)
        for (int j = 0; j < numberOfSegments; j++)
            pixArr[i][j] = false;
    
    int xPos = (int)((float)NUMBER_OF_SEGMENTS * lastX / MAX_X);
    int yPos = (int)((float)NUMBER_OF_SEGMENTS * lastY / MAX_Y);
    pixArr[yPos][xPos] = true;
    for (int i = 0; i < subPathCount; i++)
    {
        if (subPathArr[i].type == 'L' || subPathArr[i].type == 'M' || subPathArr[i].type == 'Z')
        {
            for (int j = 0; j < subPathArr[i].pointCounter; j++)
            {
                float currentX = subPathArr[i].points[0][j];
                float currentY = subPathArr[i].points[1][j];
                // moving from (lastX, lastY) to (currentX, currentY) :
                float deltaX = currentX - lastX;
                float deltaY = currentY - lastY;
                int dxSign = find_sign_of(deltaX);
                int dySign = find_sign_of(deltaY);
                float dx, dy;
                if (deltaX == 0.0f && deltaY == 0.0f)
                    continue;
                else if (abs(deltaX) > abs(deltaY))
                {
                    dx = MAX_X / ((float)numberOfSegments) * dxSign;
                    dy = MAX_Y / ((float)numberOfSegments) * (float)abs(deltaY / deltaX) * dySign;
                }
                else
                {
                    dx = MAX_X / ((float)numberOfSegments) * (float)abs(deltaX / deltaY) * dxSign;
                    dy = MAX_Y / ((float)numberOfSegments) * dySign;
                }
                float remainingX = (float)abs(deltaX);
                float remainingY = (float)abs(deltaY);
                while (remainingX > 0.0f || remainingY > 0.0f)
                {
                    xPos = (int)round((float)numberOfSegments * lastX / MAX_X);
                    yPos = (int)round((float)numberOfSegments * lastY / MAX_Y);
                    if (xPos >= NUMBER_OF_SEGMENTS || yPos >= NUMBER_OF_SEGMENTS)
                        continue;

                    pixArr[yPos][xPos] = true;
                    if (remainingX > 0.0f)
                    {
                        lastX += dx;
                        remainingX -= (float)abs(dx);
                    }
                    if (remainingY > 0.0f)
                    {
                        lastY += dy;
                        remainingY -= (float)abs(dy);
                    }
                }
            }
        }
        else // if (subPathArr[i].type == 'C')
        {
            float** temp = new float* [2];
            temp[0] = new float[subPathArr[i].pointCounter + 1];
            temp[1] = new float[subPathArr[i].pointCounter + 1];
            temp[0][0] = subPathArr[i - 1].points[0][subPathArr[i - 1].pointCounter - 1];
            temp[1][0] = subPathArr[i - 1].points[1][subPathArr[i - 1].pointCounter - 1];
            for (int j = 0; j < subPathArr[i].pointCounter; j++)
            {
                temp[0][j + 1] = subPathArr[i].points[0][j];
                temp[1][j + 1] = subPathArr[i].points[1][j];
            }
            for (int j = 0; j < subPathArr[i].pointCounter; j += 3)
            {
                float** cartesianPoints = find_Bezier_points(temp, j, maxSegmentsNumberInOneCurve);
                for (int k = 0; k < maxSegmentsNumberInOneCurve; k++)
                {
                    xPos = (int)round((float)numberOfSegments * cartesianPoints[0][k] / MAX_X);
                    yPos = (int)round((float)numberOfSegments * cartesianPoints[1][k] / MAX_Y);
                    if (xPos >= NUMBER_OF_SEGMENTS || yPos >= NUMBER_OF_SEGMENTS)
                        continue;

                    pixArr[yPos][xPos] = true;
                }
                delete[] cartesianPoints[0];
                delete[] cartesianPoints[1];
                delete[] cartesianPoints;
            }
            delete[] temp[0];
            delete[] temp[1];
            delete[] temp;
            lastX = subPathArr[i].points[0][subPathArr[i].pointCounter - 1];
            lastY = subPathArr[i].points[1][subPathArr[i].pointCounter - 1];
        }
    }
}

/*
 * finds cartezian points of a Bezier curve of degree n=3.
 * using "Explicit definition" in page: https://en.wikipedia.org/wiki/B%C3%A9zier_curve
 *
 * @param[out] outPointsArr, array of calculated cartezian points.
 * @param[in] inPointsArr, array of Bezier points.
 * @param[in] inPointsStart, index of the first Bezier point of the three to be used.
 * @param[in] outPointsCount, number of the output cartezian points. (percision)
 */
float** find_Bezier_points(float** inPointsArr, int inPointsStart, int outPointsCount)
{
    const int b[] = { 1, 3, 3, 1 }; //binomial coefficients array
    float dt = 1.0f / (float)outPointsCount;
    float t = 0.0f;
    float** outPointsArr = new float* [2];
    outPointsArr[0] = new float[outPointsCount];
    outPointsArr[1] = new float[outPointsCount];
    for (int i = 0; i < outPointsCount; i++)
    {
        outPointsArr[0][i] = 0.0f;
        outPointsArr[1][i] = 0.0f;
        for (int j = 0; j < 4; j++)
        {
            float d = (t == 1.0f && j == 3) ? 1.0f : (float)pow(1.0f - t, 3 - j);
            //int b = binomial_coefficient(3, j); // no need to calculate it every time, it is stored in "b[j]"
            float factor = ((float)b[j]) * d * ((float)pow(t, j));
            outPointsArr[0][i] += factor * inPointsArr[0][inPointsStart + j];
            outPointsArr[1][i] += factor * inPointsArr[1][inPointsStart + j];
        }
        t += dt;
    }
    return outPointsArr;
}

/**
 * finds sign of a float number.
 *
 * @param[out], returns -1 if the number is negative, 1 otherwise.
 * @param[in] x, the float number which sign is to be determined.
 */
int find_sign_of(float x)
{
    return (x < 0.0f) ? -1 : 1;
}

void subPathArr_to_bmp(subPath* subPathArr, int subPathCount, const char* fileName)
{
    bool** pixArr = new bool* [NUMBER_OF_SEGMENTS];
    for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
        pixArr[i] = new bool[NUMBER_OF_SEGMENTS];

    subPathArr_to_pixArr(pixArr, subPathArr, subPathCount, 1);
    pixArr_to_bmp(pixArr, fileName);
}