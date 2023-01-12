/**
 * subPath.h
 *
 * Created: 19/06/2022
 *  Author: Ali Emad
 */

#pragma once

#include <string>

using namespace std;
//#include <string> //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
struct subPath
{
    char type;                          // would be one of: {'M', 'L', 'C', 'Z'}
    float** points;                     // {points[0][i], points[1][i]} are: {x[i], y[i]}, where the very first added points are the ones with lowest i's
    int pointCounter;                   // counts how many points are in "points"
    bool isInit;                        // indecates whether the object is initiallised or not, used when calling destructor, check it out

    subPath();                          // default constructor
    ~subPath();                         // destructor
    void init(char _type);
    void add_point(float x, float y);
    void chop_empty_memory(void);
    void print(void);
    void copy(subPath* spPtr);
};

void** find_subPathArr(string* transformStrPtr, string* pathStrPtr);                                //
void subPathArr_to_pixArr(bool** pixArr, subPath* subPathArr, int subPathCount, int sizeFactor);    //
int find_sign_of(float x);                                                                          //
float** find_Bezier_points(float** inPointsArr, int inPointsStart, int outPointsCount);             //
void subPathArr_to_bmp(subPath* subPathArr, int subPathCount, const char* fileName);                //