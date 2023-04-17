/**
 * G-code.cpp
 *
 * Created: 06/07/2022
 *  Author: Ali Emad
 */

using namespace std;

#include <iostream>
#include <string>
#include<ctime>
#include "config.h"
#include "serialib.h"
#include "file_interface.h"
#include "subPath.h"
#include "path.h"
#include <Windows.h>
#include "instruction.h"
#include "bitmap_image.hpp"
#include "G-code.h"
#include <conio.h>
#include <math.h>
#include <ctime>


void gLine::init(int _codeIndex, float _x, float _y, float _z, float _feedRate)
{
	codeIndex = _codeIndex;
	x = _x;
	y = _y;
	z = _z;
	feedRate = _feedRate;
}

void gLine::print()
{
	cout << 'G' << codeIndex << " X" << x << " Y" << y << " Z" << z;
	if (codeIndex == FEED_MOVEMENT)
		cout << " F" << feedRate;
	cout << endl;
}

void find_G_code(gLine* gLineArr, int& gLineCount, instruction* instructionArr, int instructionCount)
{
	for (int passCount = 0; passCount < PASSES; passCount++)
	{
		for (int i = 0; i < instructionCount; i++)
		{
			if (instructionArr[i].type == 'U')
			{
				if (gLineCount > 0)
				{
					// get the head up at the previous x, y coordinate
					float xPrevious = gLineArr[gLineCount - 1].x;
					float yPrevious = gLineArr[gLineCount - 1].y;
					gLineArr[gLineCount++].init(RAPID_MOVMENT, xPrevious, yPrevious, Z_AXIS_UP, 0.0f);
				}

				// go to the next instruction's point in with a rapid move
				i++;
				float x = instructionArr[i].points[0][0];
				float y = instructionArr[i].points[1][0];
				gLineArr[gLineCount++].init(RAPID_MOVMENT, x, y, Z_AXIS_UP, 0.0f);

				// at the very beginning of the instructions, there is a 'U' instruction followed 
				// by two 'L' instructions, after doung the first one, do the second one

				if (instructionArr[i + 1].type == 'L')
				{
					i++;
					x = instructionArr[i].points[0][0];
					y = instructionArr[i].points[1][0];
					gLineArr[gLineCount++].init(RAPID_MOVMENT, x, y, Z_AXIS_UP, 0.0f);
				}
				continue;
			}

			else if (instructionArr[i].type == 'D')
			{
				float xPrevious = instructionArr[i - 1].points[0][0];
				float yPrevious = instructionArr[i - 1].points[1][0];
				float z = Z_AXIS_DOWN;

				gLineArr[gLineCount++].init(FEED_MOVEMENT, xPrevious, yPrevious, z, 0.0f);
				optimzie_feed_rates(gLineArr, gLineCount - 1);
			}

			else if (instructionArr[i].type == 'L')
			{
				// reaching down here, means that instructionArr[i] has point/s which are all head down at.

				float x = instructionArr[i].points[0][0];
				float y = instructionArr[i].points[1][0];
				float z = Z_AXIS_DOWN;		// to be changed when applying level map

				// if the next instruction is head up ('U'), then feed rate at this point should be 0.0
				if (instructionArr[i + 1].type == 'U')
				{
					gLineArr[gLineCount++].init(FEED_MOVEMENT, x, y, z, 0.0f);
					optimzie_feed_rates(gLineArr, gLineCount - 1);
					continue;
				}

				// if not, the feed rate at this point must be of a certain value that depends on:
				// 1. angle between the two lines: {pointPreevious, pointThis}, {pointThis, pointNext}.
				// 2. length of line: {pointPreevious, pointThis}, and feed rate at pointPreevious.
				// 3. length of line: {pointThis, pointNext}, and feed rate at it, could modify this point's feed rate later on.
				// 
				// find the angle between the previous line and this i-th line
				float xPrevious = gLineArr[gLineCount - 1].x;
				float yPrevious = gLineArr[gLineCount - 1].y;
				float zPrevious = gLineArr[gLineCount - 1].z;

				int isFollowingInstructionNotDown;
				if (i < instructionCount - 1)
					isFollowingInstructionNotDown = (instructionArr[i + 1].type == 'D') ? 0 : 1;
				else
					isFollowingInstructionNotDown = 0;

				float xNext = instructionArr[i + isFollowingInstructionNotDown].points[0][0];
				float yNext = instructionArr[i + isFollowingInstructionNotDown].points[1][0];
				float zNext = Z_AXIS_DOWN;

				float cosAngle = find_cos_angle_between_two_lines(
					xPrevious, yPrevious, zPrevious,
					x, y, z,
					xNext, yNext, zNext);

				float feedRate;
				if (cosAngle == 2.0f)
					feedRate = gLineArr[gLineCount - 1].feedRate;
				else
					feedRate = MAX_FEED_RATE * (1.0f + cosAngle) / 2.0f;

				gLineArr[gLineCount++].init(FEED_MOVEMENT, x, y, z, feedRate);
				optimzie_feed_rates(gLineArr, gLineCount - 1);
			}

			else // if (instructionArr[i].type == 'C')
			{
				for (int j = 0; j < MAX_SEGMENTS_NUMBER_IN_ONE_CURVE - 1; j += MAX_SEGMENTS_NUMBER_IN_ONE_CURVE / CURVE_SEGMENTS_NUMBER_IN_GCODE)
				{
					float x = instructionArr[i].points[0][j];
					float y = instructionArr[i].points[1][j];
					float z = Z_AXIS_DOWN;

					float xPrevious = gLineArr[gLineCount - 1].x;
					float yPrevious = gLineArr[gLineCount - 1].y;
					float zPrevious = gLineArr[gLineCount - 1].z;

					float xNext = instructionArr[i].points[0][j + 1];
					float yNext = instructionArr[i].points[1][j + 1];
					float zNext = Z_AXIS_DOWN;

					float cosAngle = find_cos_angle_between_two_lines(
						xPrevious, yPrevious, zPrevious,
						x, y, z,
						xNext, yNext, zNext);

					float feedRate;
					if (cosAngle == 2.0f)
						feedRate = gLineArr[gLineCount - 1].feedRate;
					else
						feedRate = MAX_FEED_RATE * (1.0f + cosAngle) / 2.0f;

					gLineArr[gLineCount++].init(FEED_MOVEMENT, x, y, z, feedRate);
					optimzie_feed_rates(gLineArr, gLineCount - 1);
				}

				// do the last segment
				float x = instructionArr[i].points[0][MAX_SEGMENTS_NUMBER_IN_ONE_CURVE - 1];
				float y = instructionArr[i].points[1][MAX_SEGMENTS_NUMBER_IN_ONE_CURVE - 1];
				float z = Z_AXIS_DOWN;

				// if the next instruction is head up ('U'), then feed rate at this point should be 0.0
				if (instructionArr[i + 1].type == 'U')
				{
					gLineArr[gLineCount++].init(FEED_MOVEMENT, x, y, z, 0.0f);
					continue;
				}

				float xPrevious = gLineArr[gLineCount - 1].x;
				float yPrevious = gLineArr[gLineCount - 1].y;
				float zPrevious = gLineArr[gLineCount - 1].z;

				int isFollowingInstructionNotDown = (instructionArr[i + 1].type == 'D') ? 0 : 1;

				float xNext = instructionArr[i + isFollowingInstructionNotDown].points[0][0];
				float yNext = instructionArr[i + isFollowingInstructionNotDown].points[1][0];
				float zNext = Z_AXIS_DOWN;

				float cosAngle = find_cos_angle_between_two_lines(
					xPrevious, yPrevious, zPrevious,
					x, y, z,
					xNext, yNext, zNext);

				float feedRate;
				if (cosAngle == 2.0f)
					feedRate = gLineArr[gLineCount - 1].feedRate;
				else
					feedRate = MAX_FEED_RATE * (1.0f + cosAngle) / 2.0f;

				gLineArr[gLineCount++].init(FEED_MOVEMENT, x, y, z, feedRate);
				optimzie_feed_rates(gLineArr, gLineCount - 1);
			}
		}
	}
}

void optimzie_feed_rates(gLine* gLineArr, int gLineIndex)
{
	if (gLineIndex == 0)
		return;		// nothing previous to optimize.

	float x = gLineArr[gLineIndex].x;
	float y = gLineArr[gLineIndex].y;
	float z = gLineArr[gLineIndex].z;

	float xPrevious = gLineArr[gLineIndex - 1].x;
	float yPrevious = gLineArr[gLineIndex - 1].y;
	float zPrevious = gLineArr[gLineIndex - 1].z;

	float feedRate = gLineArr[gLineIndex].feedRate;

	float feedRatePrevious = gLineArr[gLineIndex - 1].feedRate;
	
	float a = (feedRate > feedRatePrevious) ? ACCELERATION : DECELERATION;

	// check if when starting from previous feed rate on the line: {pointPreevious, pointThis},
	// there would be enough distance to accelerate/decelerate

	//tex:
	//$$∵ distance = (V_2^2 - V_1^2) / (2*a)$$
	float distanceMin;
	distanceMin = (feedRate * feedRate - feedRatePrevious * feedRatePrevious) / (2.0f * a);

	float distance = find_distance_between_two_points(
		xPrevious, yPrevious, zPrevious,
		x, y, z);

	if (distance < distanceMin)
	{
		// hence machine won't have enough distance to accelerate/decelerate

		// if it won't have enough distance to accelerate
		if (feedRate > feedRatePrevious)
		{
			// so feed rate should be minimized to the maximum value which makes it able to reach
			// starting from pointPrevious at feedRatePrevious.
			//tex:
			//$$∵ V_2 = \sqrt{V_1^2 + 2*a*distance}$$
			feedRate = pow(feedRatePrevious * feedRatePrevious + 2.0f * a * distance, 0.5f);
			gLineArr[gLineIndex].feedRate = feedRate;
		}

		else
		{
			// hence feedRatePrevious must be minimized, so that its new value allows the machine to
			// decelerate from pointPrevious to pointThis.
			//tex:
			//$$∵ V_1 = \sqrt{V_2^2 - 2*a*distance}$$
			feedRatePrevious = pow(feedRate * feedRate - 2.0f * a * distance, 0.5f);
			gLineArr[gLineIndex - 1].feedRate = feedRatePrevious;

			// But what if the feed rate of the post previous gLine was of a value which machine can't fit to work with feedRatePrevious?
			// check recursively
			optimzie_feed_rates(gLineArr, gLineIndex - 1);
		}
	}
}

float find_distance_between_two_points(
	float x1, float y1, float z1,
	float x2, float y2, float z2)
{
	float X = x2 - x1;
	float Y = y2 - y1;
	float Z = z2 - z1;
	float distance = pow(X * X + Y * Y + Z * Z, 0.5f);

	return distance;
}

float find_cos_angle_between_two_lines(
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
{
	float X1 = x2 - x1;
	float Y1 = y2 - y1;
	float Z1 = z2 - z1;
	float magnitude1 = pow(X1 * X1 + Y1 * Y1 + Z1 * Z1, 0.5f);

	float X2 = x3 - x2;
	float Y2 = y3 - y2;
	float Z2 = z3 - z2;
	float magnitude2 = pow(X2 * X2 + Y2 * Y2 + Z2 * Z2, 0.5f);

	if (magnitude1 == 0.0f || magnitude2 == 0.0f)
		return 2.0f;	// error result

	float dotProduct = X1 * X2 + Y1 * Y2 + Z1 * Z2;

	float cosAngle = dotProduct / (magnitude1 * magnitude2);

	return cosAngle;
}

void save_G_code_file(gLine* gLineArr, int gLineCount, const char* fileNameStr)
{
	ofstream gCodeFile(fileNameStr);

	for (int i = 0; i < gLineCount; i++)
	{
		gCodeFile << 'G' << gLineArr[i].codeIndex << " X" << gLineArr[i].x << " Y" << gLineArr[i].y << " Z" << gLineArr[i].z;
		if (gLineArr[i].codeIndex == FEED_MOVEMENT)
			gCodeFile << " F" << gLineArr[i].feedRate;
		gCodeFile << endl;
	}

	gCodeFile.close();
}

float find_estimated_time(gLine* gLineArr, int gLineCount)
{
	float t = 0.0;
	float speedPrev = 0.0;

	float xPrev = gLineArr[0].x;
	float yPrev = gLineArr[0].y;
	float zPrev = gLineArr[0].z;

	float xCurrent = 0.0f, yCurrent = 0.0f, zCurrent = 0.0f, speedCurrent = 0.0f;
	float speedMax = 0.0f, acceleration = 0.0f, deceleration = 0.0f;


	for (int i = 1; i < gLineCount; i++)
	{
		if (gLineArr[i].codeIndex == 0)	// G0
		{
			// moving from previos point to current point, starting from previous speed
			// to 0.0 speed, with "MAX_RAPID_SPEED", "ACCELERATION_RAPID" and
			// "DECELERATION_RAPID"
			xCurrent = gLineArr[i].x;
			yCurrent = gLineArr[i].y;
			zCurrent = gLineArr[i].z;
			speedCurrent = 0.0;
			speedMax = MAX_RAPID_SPEED;
			acceleration = ACCELERATION_RAPID;
			deceleration = DECELERATION_RAPID;
		}

		else if (gLineArr[i].codeIndex == 1)	// G1
		{
			// moving from previos point to current point, starting from previous speed
			// to current speed, with "MAX_FEED_RATE", "ACCELERATION" and "DECELERATION"
			xCurrent = gLineArr[i].x;
			yCurrent = gLineArr[i].y;
			zCurrent = gLineArr[i].z;
			speedCurrent = gLineArr[i].feedRate;
			speedMax = MAX_FEED_RATE;
			acceleration = ACCELERATION;
			deceleration = DECELERATION;
		}

		/* there is a whole lot of codes, استنى عليا*/

		if (gLineArr[i].codeIndex == 0 || gLineArr[i].codeIndex == 1)	// movement happened
		{
			t += find_time_of_movement(
				xCurrent - xPrev,
				yCurrent - yPrev,
				zCurrent - zPrev,
				speedPrev, speedCurrent,
				speedMax, acceleration, abs(deceleration)
			);

			xPrev = xCurrent;
			yPrev = yCurrent;
			zPrev = zCurrent;
			speedPrev = speedCurrent;
		}
	}

	return t;
}

float find_time_of_movement(
	float xDisplacement, float yDisplacement, float zDisplacement,
	float speed1, float speed2,
	float speedMax, float acceleration, float deceleration
)
{
	float displacementMagnitude = (float)pow(
		xDisplacement * xDisplacement +
		yDisplacement * yDisplacement +
		zDisplacement * zDisplacement, 0.5
	);

	float d1 = (speedMax * speedMax - speed1 * speed1) / (2.0f * acceleration);
	float d3 = (speed2 * speed2 - speedMax * speedMax) / (-2.0f * deceleration);
	float d2 = displacementMagnitude - (d1 + d3);
	
	if (d2 < 0)
	{
		// d2 value is to be divided into two relative parts, each added to d1 or d3 as needed,
		// to shorten d1, d2.

		d1 = d1 + d2 * acceleration / (acceleration + deceleration);

		d3 = d3 + d2 * deceleration / (acceleration + deceleration);

		speedMax = (float)sqrt(2.0 * acceleration * d1 + speed1 * speed1);

		// this d2 can't ever be negative, as this is compensated in the windows program.
		//d2 = displacementMagnitude - (d1 + d3);	// it should be zero.
		d2 = 0;
	}

	float time1 = (speedMax - speed1) / acceleration;

	float time2 = (speedMax == 0.0f) ? 0.0f : d2 / speedMax;

	float time3 = (speedMax - speed2) / deceleration;
	
	return time1 + time2 + time3;
}

void MAIN_generate_G_code(gLine* gLineArr, int& gLineCount)
{
	string* dataPtr = get_SVG_data(TEMP_SVG_FILE_DIR);

	instruction* instructionArr = new instruction[MAX_INTSTRUCTIONS_NUMBER_IN_WHOLE_FIG];
	int instructionCount = 0;

	// initially head is up, go home.
	instructionArr[instructionCount++].init('U');
	instructionArr[instructionCount].init('L');
	instructionArr[instructionCount++].addPoint(0.0f, 0.0f);

	// find instructions of the draw:
	for (int i = 1; dataPtr[i][0] != '\0'; i++)
	{
		void** voidPtrArr = find_subPathArr(dataPtr, dataPtr + i);
		subPath* subPathArr = (subPath*)voidPtrArr[1];
		int subPathCount = *(int*)voidPtrArr[0];

		path* pList = find_pathList(subPathArr, subPathCount);

		delete[](int*)voidPtrArr[0];
		delete[] subPathArr;
		delete[] voidPtrArr;

		find_instructions_for_path_list(instructionArr, instructionCount, pList);

		delete[] pList;
	}

	// terminate with head up going home
	if (instructionArr[instructionCount - 1].type != 'U')
		instructionArr[instructionCount++].init('U');
	instructionArr[instructionCount].init('L');
	instructionArr[instructionCount++].addPoint(0.0f, 0.0f);

	// head down:
	instructionArr[instructionCount++].init('D');

	delete_temp_folder();

	cout << "done processing image" << endl;

	//instructions_to_bmp(instructionArr, instructionCount, OUTPUT_BMP_FILE_DIR);

	convert_instructions_to_mm(instructionArr, instructionCount);

	cout << "done finding instructions" << endl;

	create_folder("output");

	find_G_code(gLineArr, gLineCount, instructionArr, instructionCount);

	delete[] dataPtr;
	delete[] instructionArr;
}