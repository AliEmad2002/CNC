/**
 * config.h
 *
 * Created: 19/06/2022
 * Author: Ali Emad
 */

#pragma once

#include "bitmap_image.hpp"

using namespace std;

#define DEBUG_MODE								true

// __declspec(selectany) tells the linker to delclare this variable only once and for all. To avoid Linker Tools Error LNK2005. 
__declspec(selectany) float PIXELS_PER_MM;
__declspec(selectany) int INPUT_WIDTH;
__declspec(selectany) int INPUT_HEIGHT;

__declspec(selectany) string SERIAL_PORT;
__declspec(selectany) unsigned long int BAUD_RATE;



__declspec(selectany) char* INPUT_BMP_FILE_DIR;
#define TEMP_BMP_FILE_DIR						"temp/tempInput.bmp"
#define CONST_TEMP_BMP_FILE_DIR					"temp/constTempInput.bmp"
#define TEMP_SUB_BMP_FILE_DIR					"temp/subImg.bmp"
#define TEMP_SVG_FILE_DIR						"temp/temp.svg"
#define OUTPUT_BMP_FILE_DIR						"output/output.bmp"
#define G_CODE_OUTPUT_FILE_DIR					"output/output.gcode"

#define BLACK_CUT_OFF							"0.6"

#define FILL									0
__declspec(selectany) float MAX_X;															// pixels
__declspec(selectany) float MAX_Y;															// pixels
__declspec(selectany) float TOOL_DIAMETER;													// pixels

#define PASS_ON_PATH							true
#define DRILL									false

#define Z_AXIS_UP								3.0f
__declspec(selectany) float Z_AXIS_DOWN;				// mm


__declspec(selectany) float MAX_FEED_RATE;				// mm / min
__declspec(selectany) float MAX_RAPID_SPEED;			// mm / min

__declspec(selectany) float ACCELERATION;				// mm / min
__declspec(selectany) float DECELERATION;				// mm / min			// must be of a negative sign in this program!

__declspec(selectany) float ACCELERATION_RAPID;			// mm / min
__declspec(selectany) float DECELERATION_RAPID;			// mm / min			// must be of a negative sign in this program!						-90000.0f										// mm / min^2

__declspec(selectany) unsigned int STEPS_PER_MM_X;
__declspec(selectany) unsigned int STEPS_PER_MM_Y;
__declspec(selectany) unsigned int STEPS_PER_MM_Z;

__declspec(selectany) bool AUTO_LEVELING;
__declspec(selectany) int AUTO_LEVELING_N_x;
__declspec(selectany) int AUTO_LEVELING_N_y;
__declspec(selectany) float AUTO_LEVELING_X_START;
__declspec(selectany) float AUTO_LEVELING_X_END;
__declspec(selectany) float AUTO_LEVELING_Y_START;
__declspec(selectany) float AUTO_LEVELING_Y_END;

__declspec(selectany) int PASSES;

// memory lims :
#define MAX_POINTS_NUMBER_IN_ONE_SUBPATH		1000000
#define MAX_SUBPATHS_NUMBER_IN_ONE_SUBPATHARR	1000000
#define MAX_INNER_PATHS_NUMBER_IN_ONE_PATH		1000000
#define MAX_FOC_PATHS_NUMBER_IN_ONE_PATH		1000000
#define MAX_PATH_NUMBER_IN_WHOLE_FIG			1000000
#define MAX_Z_TYPE_NUMBER_IN_WHOLE_FIG			1000000
#define MAX_INTSTRUCTIONS_NUMBER_IN_WHOLE_FIG	1000000
#define MAX_INTSTRUCTIONS_NUMBER_IN_ONE_PATH	1000000
#define MAX_PATH_GROUPS_NUMBER_IN_WHOLE_FIG		1000000
#define MAX_GCODE_LINES_NUMBER_IN_WHOLE_FIG		10000000
#define CURVE_SEGMENTS_NUMBER_IN_GCODE			100

#define MSG_STACK_LEN							64

// only important when FILL mode is on:
// percision : NOTE⚠️: these two are relevent. Low MAX_SEGMENTS_NUMBER_IN_ONE_CURVE with high NUMBER_OF_SEGMENTS generates high percision error!
#define NUMBER_OF_SEGMENTS						(int)MAX_X // == MAX_Y, too.
#define MAX_SEGMENTS_NUMBER_IN_ONE_CURVE		3*(int)MAX_X


__declspec(selectany) rgb_t WHITE_COLOR;
__declspec(selectany) rgb_t BLACK_COLOR;

void init_config();