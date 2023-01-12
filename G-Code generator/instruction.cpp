/**
 * instruction.cpp
 *
 * Created: 23/06/2022
 *  Author: Ali Emad
 */

using namespace std;

#include "instruction.h"
#include <iostream>
#include "config.h"
#include "bitmap_image.hpp"
#include "file_interface.h"
#include "subPath.h"
#include "path.h"


instruction::instruction()
{
	type = '\0';
	points = NULL;
	pointCount = 0;
	isInit = false;
}

instruction::~instruction()
{
	if (isInit)
	{
		if (type == 'C' || type == 'L')
		{
			delete[] points[0];
			delete[] points[1];
			delete[] points;
			points = NULL;
		}
		type = '\0';
		pointCount = 0;
		isInit = false;
	}
}

void instruction::init(char _type)
{
	type = _type;
	points = new float* [2];
	switch (type)
	{
	case 'L':
		points[0] = new float[1];
		points[1] = new float[1];
		break;
	case 'C':
		points[0] = new float[MAX_SEGMENTS_NUMBER_IN_ONE_CURVE];
		points[1] = new float[MAX_SEGMENTS_NUMBER_IN_ONE_CURVE];
		break;
	}
	pointCount = 0;
	isInit = true;
}

void instruction::addPoint(float x, float y)
{
	points[0][pointCount] = x;
	points[1][pointCount++] = y;
}

void instruction::print()
{
	cout << type << endl;
	if (type == 'L')
		cout << points[0][0] << ", " << points[1][0] << endl;
	else if (type == 'C')
	{
		cout << points[0][0] << ", " << points[1][0] << endl;
		cout << points[0][pointCount-1] << ", " << points[1][pointCount-1] << endl;
	}
	cout << endl;
}

void instruction::copy(instruction* instructionPtr)
{
	type = instructionPtr->type;
	points = new float* [2];
	pointCount = instructionPtr->pointCount;
	points[0] = new float[pointCount];
	points[1] = new float[pointCount];
	for (int i = 0; i < pointCount; i++)
	{
		points[0][i] = instructionPtr->points[0][i];
		points[1][i] = instructionPtr->points[1][i];
	}
	isInit = true;
}

void instruction::chop_empty_memory()
{
	float* tempX = new float[pointCount];
	float* tempY = new float[pointCount];
	for (int i = 0; i < pointCount; i++)
	{
		tempX[i] = points[0][i];
		tempY[i] = points[1][i];
	}
	delete[] points[0];
	delete[] points[1];
	points[0] = tempX;
	points[1] = tempY;
}

bool are_points_adjacent(float x1, float y1, float x2, float y2)
{
	static float toolDiameterSquared = TOOL_DIAMETER * TOOL_DIAMETER;
	float dx = x1 - x2;
	float dy = y1 - y2;
	float distance12Squared = dx * dx + dy * dy;
	return (distance12Squared <= toolDiameterSquared) ? true : false;
}

bool are_there_original_white_pixels_on_line(float x1, float y1, float x2, float y2)
{
	float xCurrent = x1;
	float yCurrent = y1;

	float deltaX = x2 - x1;
	float deltaY = y2 - y1;
	int dxSign = find_sign_of(deltaX);
	int dySign = find_sign_of(deltaY);
	float dx, dy;

	if (deltaX == 0.0f && deltaY == 0.0f)
		return false;
	else if (abs(deltaX) > abs(deltaY))
	{
		dx = dxSign;
		dy = (float)abs(deltaY / deltaX) * dySign;
	}
	else
	{
		dx = (float)abs(deltaX / deltaY) * dxSign;
		dy = dySign;
	}

	float remainingX = (float)abs(deltaX);
	float remainingY = (float)abs(deltaY);

	const bitmap_image originalInputImg(CONST_TEMP_BMP_FILE_DIR);

	rgb_t color;

	while (remainingX > 0.0f || remainingY > 0.0f)
	{
		originalInputImg.get_pixel((int)xCurrent, (int)yCurrent, color);
		
		if (color.red > 200)	// white
			return true;

		if (remainingX > 0.0f)
		{
			xCurrent += dx;
			remainingX -= (float)abs(dx);
		}

		if (remainingY > 0.0f)
		{
			yCurrent += dy;
			remainingY -= (float)abs(dy);
		}
	}

	return false;
}

void find_path_only_instruction_array(instruction* instructionArr, int& instructionCount, path* pathPtr)
{
	subPath* subPathArr = pathPtr->subPathArr;

	float lastX = subPathArr[0].points[0][0];
	float lastY = subPathArr[0].points[1][0];
	int xPos = (int)round((float)NUMBER_OF_SEGMENTS * lastX / MAX_X);
	int yPos = (int)round((float)NUMBER_OF_SEGMENTS * lastY / MAX_Y);

	bool headDown;
	for (int i = instructionCount - 1; i > -1; i--)
	{
		if (instructionArr[i].type == 'D')
		{
			headDown = true;
			break;
		}
		else if (instructionArr[i].type == 'U')
		{
			headDown = false;
			break;
		}
	}

	// if head is down, and the very first point of this path is adjacent by a value of tool radious
	// to the last point in instructionArr, there's no need to head up at the begining of this path,
	// otherwise the head must go up.
	float xNew = subPathArr[0].points[0][0];
	float yNew = subPathArr[0].points[1][0];
	float xPrev = instructionArr[instructionCount - 1].points[0][instructionArr[instructionCount - 1].pointCount - 1];
	float yPrev = instructionArr[instructionCount - 1].points[1][instructionArr[instructionCount - 1].pointCount - 1];

	bool arePointsAdjacent = are_points_adjacent(xNew, yNew, xPrev, yPrev);

	if (!headDown)
	{
		instructionArr[instructionCount].init('L');
		instructionArr[instructionCount++].addPoint(xNew, yNew);
	}
	else
	{
		if (are_there_original_white_pixels_on_line(xPrev, yPrev, xNew, yNew))
		{
			instructionArr[instructionCount++].init('U');
			instructionArr[instructionCount].init('L');
			instructionArr[instructionCount++].addPoint(xNew, yNew);
			headDown = false;
		}
	}

	for (int i = 0; i < pathPtr->subPathCount; i++)
	{
		bool subPathHadIntersections = false;
		if (subPathArr[i].type == 'M' || subPathArr[i].type == 'L' || subPathArr[i].type == 'Z')
		{
			if (!headDown)
			{
				instructionArr[instructionCount++].init('D');
				headDown = true;
			}
			for (int j = 0; j < subPathArr[i].pointCounter; j++)
			{
				instructionArr[instructionCount].init('L');
				lastX = subPathArr[i].points[0][j];
				lastY = subPathArr[i].points[1][j];
				instructionArr[instructionCount++].addPoint(lastX, lastY);
			}
		}
		else
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
				// find cartesian points formed by the j'th group of four Bezier points in the "temp" points array:
				float** cartesianPoints = find_Bezier_points(temp, j, MAX_SEGMENTS_NUMBER_IN_ONE_CURVE);
				if (!headDown)
				{
					instructionArr[instructionCount++].init('D');
					headDown = true;
				}
				instructionArr[instructionCount].init('C');
				for (int k = 0; k < MAX_SEGMENTS_NUMBER_IN_ONE_CURVE; k++)
				{
					lastX = cartesianPoints[0][k];
					lastY = cartesianPoints[1][k];
					instructionArr[instructionCount].addPoint(lastX, lastY);
				}
				instructionArr[instructionCount++].chop_empty_memory();
				delete[] cartesianPoints[0];
				delete[] cartesianPoints[1];
				delete[] cartesianPoints;
			}
			delete[] temp[0];
			delete[] temp[1];
			delete[] temp;
		}
	}
}

void find_path_fully_instruction_array(instruction* instructionArr, int& instructionCount, path* pathPtr, const char* tempImgDir, int deltaXPix, int deltaYPix)
{
	// since the path is related to the tmpImg, it's shifted by the same value tempImg is.
	// shift it back before drawing it.
	for (int i = 0; i < pathPtr->subPathCount; i++)
	{
		for (int j = 0; j < pathPtr->subPathArr[i].pointCounter; j++)
		{
			pathPtr->subPathArr[i].points[0][j] += deltaXPix;
			pathPtr->subPathArr[i].points[1][j] += deltaYPix;
		}
	}
	pathPtr->xMin += deltaXPix;
	pathPtr->xMax += deltaXPix;
	pathPtr->yMin += deltaYPix;
	pathPtr->yMax += deltaYPix;
	pathPtr->xCenter += deltaXPix;
	pathPtr->yCenter += deltaYPix;

	// draw the path its self (shifted back vesion):
	find_path_only_instruction_array(instructionArr, instructionCount, pathPtr);
	
	// whiten path and create a temp image of its filling (if filled):
	pathPtr->whiten_from_tmpImg_and_generate_selfTmpImg(tempImgDir, deltaXPix, deltaYPix);

	// if it was not filled, we're done here by just drawing it its self.
	if (!pathPtr->isFilled)
		return;

	string selfTmpImgDir = "temp/";
	string selfTmpSvgDir = "temp/";
	string IDStr = to_string(pathPtr->pathID);
	selfTmpImgDir += IDStr + ".bmp";
	selfTmpSvgDir += IDStr + ".svg";

	while (has_black_pixels(selfTmpImgDir.c_str()))
	{
		// get paths of it:
		bmp_to_svg(selfTmpImgDir.c_str(), selfTmpSvgDir.c_str());
		string* dataPtr = get_SVG_data(selfTmpSvgDir.c_str());

		// if svg file is empty:
		if (dataPtr[1].size() <= 2)
		{
			delete[] dataPtr;
			break;
		}

		for (int i = 1; dataPtr[i][0] != '\0'; i++)
		{
			void** voidPtrArr = find_subPathArr(dataPtr, dataPtr + i);
			subPath* subPathArr = (subPath*)voidPtrArr[1];
			int subPathCount = *(int*)voidPtrArr[0];

			path* pList = find_pathList(subPathArr, subPathCount);

			// find the most parent:
			path* mostParentPathPtr = find_most_parent(pList);

			// whiten it, and whatever it contains from selfTmpImg, and draw them:
			find_path_fully_instruction_array(instructionArr, instructionCount, mostParentPathPtr, selfTmpImgDir.c_str(), pathPtr->xMin, pathPtr->yMin);

			delete[](int*)voidPtrArr[0];
			delete[] subPathArr;
			delete[] voidPtrArr;
			delete[] pList;
		}
		delete[] dataPtr;
	}



	// remove the path its self and whatever it contains from the temp image, and create a temp image of its own:
	//pathPtr->create_filled_img_and_remove_it_from_bmp_temp_image()





	/*
	*											FILLING ALGO. TO BE MAINTAINED LATER...
	*
	// create an image of whatever the path currently contains,
	// and whiten it according to the tool diameter in the main temp input image.
	bitmap_image* filledImgPtr = pathPtr->create_filled_img_and_remove_it_from_bmp_temp_image();
	// if this path is not filled, there's no thing else to do after drawing it, and whitening from main temp input image
	
	if (!pathPtr->isFilled)
		return;

	// while that image has an undrawn pixel
	while (has_black_pixels(filledImgPtr))
	{
		// convert it to svg
		// (assuming and depending that it is already saved in "TEMP_SUB_BMP_FILE_DIR",
		// which should've happened in "create_filled_img_and_remove_it_from_bmp_temp_image()" function.
		bmp_to_svg(TEMP_SUB_BMP_FILE_DIR, TEMP_SVG_FILE_DIR);

		// some times there would be a single pixel, only one, which potrace will
		// ingore and generate an empty svg file, if that happens, just beak out of
		// this while loop, assuming that the "filledImgPtr" does not have any more
		// black pixels, which is very very approximatly right.
		if (is_svg_empty(TEMP_SVG_FILE_DIR))
			break;

		// find its most parent
		path* mostParent = find_most_parent_in_svg(TEMP_SVG_FILE_DIR);

		// whiten its place in the small temp sub image
		// (remember that it's been already whitened in the main temp input image)
		// since this sub image currently does not have any point outside this "mostParent",
		// there's no need to check for every pixel if it's inside or not, they all are.
		mostParent->whiten_path_from_img(filledImgPtr, TEMP_SUB_BMP_FILE_DIR);

		// shift it back:
		float xShift = round(pathPtr->xMin);
		float yShift = round(pathPtr->yMin);
		mostParent->shift_path(xShift, yShift);

		// draw it
		find_path_only_instruction_array(instructionArr, instructionCount, mostParent);

		// delete all non-needed memory
		delete[] mostParent;
	}
	// delete all non-needed memory
	delete[] filledImgPtr;
	*
	* 
	* 
	*/
}

void find_instructions_for_path_list(instruction* instructionArr, int& instructionCount, path* pathList)
{
	#if FILL:
	path** sortedPathPtrArr = find_sorted_ptrArr_of_paths(pathList);

	for (int i = 0; sortedPathPtrArr[i] != NULL; i++)
		find_path_fully_instruction_array(instructionArr, instructionCount, sortedPathPtrArr[i], TEMP_BMP_FILE_DIR, 0, 0);

	// delete all non-needed memory
	delete[] sortedPathPtrArr;
	
	#elif PASS_ON_PATH:
	for (path* pathPtr = pathList->find_head_of_the_list_of_this(); pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
		find_path_only_instruction_array(instructionArr, instructionCount, pathPtr);

	#elif DRILL:
	// go to the center of every filled path only!, to avoid drilling same point twice which may waste time,
	// get the head down, then get it up gain, and go to the next center...
	for (path* pathPtr = pathList->find_head_of_the_list_of_this(); pathPtr != NULL; pathPtr = pathPtr->nextPathPtr)
	{
		if (!pathPtr->isFilled)
			continue;

		instructionArr[instructionCount].init('L');
		instructionArr[instructionCount++].addPoint(pathPtr->xCenter, pathPtr->yCenter);

		instructionArr[instructionCount++].init('D');

		instructionArr[instructionCount++].init('U');
	}
	#endif
}

void instructions_to_bmp(instruction* instructionArr, int instructionCount, const char* fileNameStr)
{
	int toolRadiousPos = TOOL_DIAMETER / 2.0f * ((float)NUMBER_OF_SEGMENTS) / MAX_X;

	rgb_t gray;
	gray.blue = 200;
	gray.red = 200;
	gray.green = 200;

	// create a white image:
	bitmap_image output(NUMBER_OF_SEGMENTS, NUMBER_OF_SEGMENTS);
	rgb_t white;
	white.blue = 255;
	white.red = 255;
	white.green = 255;
	for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
		for (int j = 0; j < NUMBER_OF_SEGMENTS; j++)
			output.set_pixel(j, i, white);

	// draw instructions:
	rgb_t black;
	black.red = 0;
	black.green = 0;
	black.blue = 0;
	bool headDown = false;
	float xCurrent = 0.0f;
	float yCurrent = 0.0f;
	for (int i = 0; i < instructionCount; i++)
	{
		if (instructionArr[i].type == 'U')
			headDown = false;
		else if (instructionArr[i].type == 'D')
			headDown = true;
		else if (instructionArr[i].type == 'L')
		{
			if (!headDown)
			{
				xCurrent = instructionArr[i].points[0][0];
				yCurrent = instructionArr[i].points[1][0];
			}
			else
			{
				float xDest = instructionArr[i].points[0][0];
				float yDest = instructionArr[i].points[1][0];
				
				float deltaX = xDest - xCurrent;
				float deltaY = yDest - yCurrent;
				int dxSign = find_sign_of(deltaX);
				int dySign = find_sign_of(deltaY);
				float dx, dy;
				if (deltaX == 0.0f && deltaY == 0.0f)
					continue;
				else if (abs(deltaX) > abs(deltaY))
				{
					dx = MAX_X / ((float)NUMBER_OF_SEGMENTS) * dxSign;
					dy = MAX_Y / ((float)NUMBER_OF_SEGMENTS) * (float)abs(deltaY / deltaX) * dySign;
				}
				else
				{
					dx = MAX_X / ((float)NUMBER_OF_SEGMENTS) * (float)abs(deltaX / deltaY) * dxSign;
					dy = MAX_Y / ((float)NUMBER_OF_SEGMENTS) * dySign;
				}
				float remainingX = (float)abs(deltaX);
				float remainingY = (float)abs(deltaY);
				while (remainingX > 0.0f || remainingY > 0.0f)
				{
					int xPos = (int)round((float)NUMBER_OF_SEGMENTS * xCurrent / MAX_X);
					int yPos = (int)round((float)NUMBER_OF_SEGMENTS * yCurrent / MAX_Y);
					for (int y = yPos - toolRadiousPos; y <= yPos + toolRadiousPos; y++)
						for (int x=xPos-toolRadiousPos; x<=xPos+toolRadiousPos; x++)
							output.set_pixel(x, y, gray);

					if (remainingX > 0.0f)
					{
						xCurrent += dx;
						remainingX -= (float)abs(dx);
					}
					if (remainingY > 0.0f)
					{
						yCurrent += dy;
						remainingY -= (float)abs(dy);
					}
				}
			}
		}
		else
		{
			for (int j = 0; j < instructionArr[i].pointCount; j++)
			{
				xCurrent = instructionArr[i].points[0][j];
				yCurrent = instructionArr[i].points[1][j];
				int xPos = (int)round((float)NUMBER_OF_SEGMENTS * xCurrent / MAX_X);
				int yPos = (int)round((float)NUMBER_OF_SEGMENTS * yCurrent / MAX_Y);
				for (int y = yPos - toolRadiousPos; y <= yPos + toolRadiousPos; y++)
					for (int x = xPos - toolRadiousPos; x <= xPos + toolRadiousPos; x++)
						output.set_pixel(x, y, gray);
			}
		}
	}

	headDown = false;
	xCurrent = 0.0f;
	yCurrent = 0.0f;
	for (int i = 0; i < instructionCount; i++)
	{
		if (instructionArr[i].type == 'U')
			headDown = false;
		else if (instructionArr[i].type == 'D')
			headDown = true;
		else if (instructionArr[i].type == 'L')
		{
			if (!headDown)
			{
				xCurrent = instructionArr[i].points[0][0];
				yCurrent = instructionArr[i].points[1][0];
			}
			else
			{
				float xDest = instructionArr[i].points[0][0];
				float yDest = instructionArr[i].points[1][0];

				float deltaX = xDest - xCurrent;
				float deltaY = yDest - yCurrent;
				int dxSign = find_sign_of(deltaX);
				int dySign = find_sign_of(deltaY);
				float dx, dy;
				if (deltaX == 0.0f && deltaY == 0.0f)
					continue;
				else if (abs(deltaX) > abs(deltaY))
				{
					dx = MAX_X / ((float)NUMBER_OF_SEGMENTS) * dxSign;
					dy = MAX_Y / ((float)NUMBER_OF_SEGMENTS) * (float)abs(deltaY / deltaX) * dySign;
				}
				else
				{
					dx = MAX_X / ((float)NUMBER_OF_SEGMENTS) * (float)abs(deltaX / deltaY) * dxSign;
					dy = MAX_Y / ((float)NUMBER_OF_SEGMENTS) * dySign;
				}
				float remainingX = (float)abs(deltaX);
				float remainingY = (float)abs(deltaY);
				while (remainingX > 0.0f || remainingY > 0.0f)
				{
					int xPos = (int)round((float)NUMBER_OF_SEGMENTS * xCurrent / MAX_X);
					int yPos = (int)round((float)NUMBER_OF_SEGMENTS * yCurrent / MAX_Y);
					output.set_pixel(xPos, yPos, black);

					if (remainingX > 0.0f)
					{
						xCurrent += dx;
						remainingX -= (float)abs(dx);
					}
					if (remainingY > 0.0f)
					{
						yCurrent += dy;
						remainingY -= (float)abs(dy);
					}
				}
			}
		}
		else
		{
			for (int j = 0; j < instructionArr[i].pointCount; j++)
			{
				xCurrent = instructionArr[i].points[0][j];
				yCurrent = instructionArr[i].points[1][j];
				int xPos = (int)round((float)NUMBER_OF_SEGMENTS * xCurrent / MAX_X);
				int yPos = (int)round((float)NUMBER_OF_SEGMENTS * yCurrent / MAX_Y);
				output.set_pixel(xPos, yPos, black);
			}
		}
	}
	output.save_image(fileNameStr);
}

void convert_instructions_to_mm(instruction* instructionArr, int instructionCount)
{
	for (int i = 0; i < instructionCount; i++)
	{
		if (instructionArr[i].type == 'D' || instructionArr[i].type == 'U')
			continue;

		for (int j = 0; j < instructionArr[i].pointCount; j++)
		{
			instructionArr[i].points[0][j] /= PIXELS_PER_MM;
			instructionArr[i].points[1][j] /= PIXELS_PER_MM;
		}
	}
}