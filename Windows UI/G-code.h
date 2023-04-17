/**
 * G-code.h
 *
 * Created: 06/07/2022
 *  Author: Ali Emad
 */

#pragma once
#include "instruction.h"

#define RAPID_MOVMENT 00
#define FEED_MOVEMENT 01

using namespace std;

struct gLine
{
	int codeIndex;		// the number that comes after the 'G' in any G-code
	float x;
	float y;
	float z;
	float feedRate;		// the speed at which the machine should be operating when it reaches that point (x, y, z)

	void init(int _codeIndex, float _x, float _y, float _z, float _feedRate);
	void print();
};


void find_G_code(gLine* gLineArr, int& gLineCount, instruction* instructionArr, int instructionCount);

void optimzie_feed_rates(gLine* gLineArr, int gLineIndex);

float find_distance_between_two_points(float x1, float y1, float z1, float x2, float y2, float z2);

float find_cos_angle_between_two_lines(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

void save_G_code_file(gLine* gLineArr, int gLineCount, const char* fileNameStr);

float find_estimated_time(gLine* gLineArr, int gLineCount);

float find_time_of_movement(
	float xDisplacement, float yDisplacement, float zDisplacement,
	float speed1, float speed2,
	float speedMax, float acceleration, float deceleration
);

void MAIN_generate_G_code(gLine* gLineArr, int& gLineCount);