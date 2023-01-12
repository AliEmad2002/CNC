/**
 * path.h
 *
 * Created: 19/06/2022
 *  Author: Ali Emad
 */

#pragma once

using namespace std;

#include "subPath.h"
#include "bitmap_image.hpp"

struct path
{
    subPath* subPathArr;            //
    int subPathCount;               //
    bool** pixArr;                  //
    path** innerPathPtrArr;         //
    int innerPathCount;             //
    path** firstOrderChildPtrArr;   //
    int firstOrderChildCount;       //
    path* firstOrderParentPtr;      //
    bool isFilled;                  //
    bool isInit;                    //
    path* nextPathPtr;              //
    path* previousPathPtr;          //
    float xCenter;                  //
    float yCenter;                  //
    float xMin;                     //
    float yMin;                     //
    float xMax;                     //
    float yMax;                     //
    float maxLen;                   //
    float maxLenSquared;            //
    int** xCheckArr;                //
    int* xCheckRowLengths;          //
    int** yCheckArr;                //
    int* yCheckRowLengths;          //
    int generationIndex;            // the most grand parent/s is/are indexed zero, and so on.
    int pathID;

    path();                                                                                 //
    ~path();                                                                                //
    void init(subPath* spArr, int start, int end, path* _previousPathPtr);                  //
    void print();                                                                           //
    int is_point_inside(int xPos, int yPos);                                                //
    bool is_path_inside(path* innerPathPtr);                                                //
    void find_inner_paths(path* pathList);                                                  //
    bool is_first_order_child(path* childPtr);                                              //
    void find_first_order_children_and_parent_them();                                       //
    void find_filling_states_and_generation_indexes_for_all_inner_paths();                  //
    void find_center_and_corners();                                                         //
    float find_max_len_squared_from_center();                                               //
    //bitmap_image* create_filled_img_and_remove_it_from_bmp_temp_image(const char* tempImgDir, int deltaXPix, int deltaYPix);
    void swap_with(path* pathPtr);                                                          //
    path* find_head_of_the_list_of_this();
    void shift_path(float xShift, float yShift);
    //void whiten_path_from_img(bitmap_image* imgPtr, const char* imgDir);
    void whiten_from_tmpImg_and_generate_selfTmpImg(const char* tmpImgDir, int xTmpImgMin, int yTmpImgMin);
};

int is_point_inside_pixArr(bool** pixArr, int xPos, int yPos, int xPosMin,
    int yPosMin, int xPosMax, int yPosMax);                                                 //
path* find_pathList(subPath* subPathArr, int subPathCount);                                 //
void find_all_children_and_parents(path* pathList);                                         //
void find_all_filling_states_and_generation_indexes(path* pathList);                        //
void pathList_to_bmp(path* pathList, const char* fileNameStr);                              //
bool** pathList_to_pixArr(path* pathList);                                                  //
void path_to_bmp(path* pathPtr, const char* fileNameStr);                                   //
path** find_sorted_ptrArr_of_paths(path* pathList);                                         //
path* find_most_parent(path* pList);