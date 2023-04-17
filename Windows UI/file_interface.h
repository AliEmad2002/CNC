/**
 * svg_interface.h
 *
 * Created: 19/06/2022
 *  Author: Ali Emad
 */

#pragma once

using namespace std;

#include "bitmap_image.hpp"

void create_folder(const char* folderDirStr);							//
void create_temp_folder();												//
void make_temp_input_bmp_copy();										//
void delete_temp_folder();
void bmp_to_svg(const char* bmpFileDir, const char* svgFileDir);		//
string* get_SVG_data(const char* svgFileDir);							//
float str_to_float(string* strPtr, int start, int end);					//
int str_to_int(string* strPtr, int start, int end);						//
bool is_number(char ch);												//
bool is_in_str(char ch, const char* str);								//
bool has_black_pixels(const char* imgDir);								//
bool is_svg_empty(const char* svgFileDir);								//
string get_drag_directory();
void take_input_dir(void);