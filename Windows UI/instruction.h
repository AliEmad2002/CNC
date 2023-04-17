/**
 * instruction.h
 *
 * Created: 23/06/2022
 *  Author: Ali Emad
 */

#pragma once

using namespace std;

#include "path.h"

struct instruction
{
	char type;
	float** points;
	int pointCount;
	bool isInit;

	instruction();
	~instruction();
	void init(char _type);
	void addPoint(float x, float y);
	void print();
	void copy(instruction* instructionPtr);
	void chop_empty_memory();
};

void find_path_only_instruction_array(instruction* instructionArr, int& instructionCount, path* pathPtr);
void find_instructions_for_path_list(instruction* instructionArr, int& instructionCount, path* pathList);
void instructions_to_bmp(instruction* instructionArr, int instructionCount, const char* fileNameStr);
bool are_there_original_white_pixels_on_line(float x1, float y1, float x2, float y2);
void convert_instructions_to_mm(instruction* instructionArr, int instructionCount);