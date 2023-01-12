/**
 * config.cpp
 *
 * Created: 08/07/2022
 * Author: Ali Emad
 */

#include "config.h"
#include <iostream>
#include <fstream>
#include "bitmap_image.hpp"
#include "windows.h"
#include <conio.h>
#include "file_interface.h"

using namespace std;


void init_config()
{
	#if DRILL && (PASS_ON_PATH || FILL) :
	cout << "drill is active, can't active PASS_ON_PATH or FILL\n";
	exit(-1);
	#endif

	bool useLastSettings;
	while (1)
	{
		cout << "use same settings used last time? (Y/N): " << endl;
		char in = _getch();
		if (in == 'y' || in == 'Y')
		{
			useLastSettings = true;
			break;
		}
		else if (in == 'n' || in == 'N')
		{
			useLastSettings = false;
			break;
		}
		else
			cout << "not a valid input, please try again!" << endl;
	}

	// declare vairables:
	float widthMM;
	float toolDiameterMM;

	// if user wants to enter new settings:
	if (!useLastSettings)
	{
		cout << "enter width in mm: ";
		cin >> widthMM;

		cout << "enter tool diameter in mm: ";
		cin >> toolDiameterMM;

		cout << "enter z axis depth value (i.e.: -0.1 mm): ";
		cin >> Z_AXIS_DOWN;

		cout << "enter maximum feed rate in mm/sec: ";
		cin >> MAX_FEED_RATE;

		cout << "enter maximum rapid movement speed in mm/sec: ";
		cin >> MAX_RAPID_SPEED;

		cout << "enter feed acceleration in mm/sec^2: ";
		cin >> ACCELERATION;

		// as std G-code does, it's assumed to be -ACCELERATION:
		//cout << "enter feed deceleration in mm/min²: ";
		//cin >> DECELERATION;
		//DECELERATION *= -1.0;
		DECELERATION = -ACCELERATION;

		cout << "enter rapid movement acceleration in mm/sec^2: ";
		cin >> ACCELERATION_RAPID;

		// as std G-code does, it's assumed to be -ACCELERATION_RAPID:
		//cout << "enter rapid movement deceleration in mm/min²: ";
		//cin >> DECELERATION_RAPID;
		//DECELERATION_RAPID *= -1.0;
		DECELERATION_RAPID = -ACCELERATION_RAPID;

		cout << "enter X-axis steps per mm: ";
		cin >> STEPS_PER_MM_X;

		cout << "enter Y-axis steps per mm: ";
		cin >> STEPS_PER_MM_Y;

		cout << "enter Z-axis steps per mm: ";
		cin >> STEPS_PER_MM_Z;

		cout << "enter number of passes: ";
		cin >> PASSES;

		while (1)
		{
			cout << "auto leveling? (Y/N): " << endl;
			char in = _getch();
			if (in == 'y' || in == 'Y')
			{
				AUTO_LEVELING = true;
				break;
			}
			else if (in == 'n' || in == 'N')
			{
				AUTO_LEVELING = false;
				break;
			}
			else
				cout << "not a valid input, please try again!" << endl;
		}

		if (AUTO_LEVELING)
		{
			cout << "enter auto leveling Nx: ";
			cin >> AUTO_LEVELING_N_x;

			cout << "enter auto leveling Ny: ";
			cin >> AUTO_LEVELING_N_y;

			cout << "enter x of point to start scanning from for auto leveling: ";
			cin >> AUTO_LEVELING_X_START;

			cout << "enter y of point to start scanning from for auto leveling: ";
			cin >> AUTO_LEVELING_Y_START;

			cout << "enter x of point to end scanning at for auto leveling: ";
			cin >> AUTO_LEVELING_X_END;

			cout << "enter y of point to end scanning at for auto leveling: ";
			cin >> AUTO_LEVELING_Y_END;
		}

		cout << "enter serial port: ";
		cin >> SERIAL_PORT;
		string fixedPort = "";
		fixedPort += '\\';
		fixedPort += '\\';
		fixedPort += '.';
		fixedPort += '\\';
		int i;
		for (i = 0; SERIAL_PORT[i] != '\0'; i++)
			fixedPort += SERIAL_PORT[i];
		SERIAL_PORT = fixedPort;

		cout << "enter serial baud rate: ";
		cin >> BAUD_RATE;

		// save all setting to last.config file:
		ofstream lastconfFile;
		lastconfFile.open("last.config");
		lastconfFile << widthMM << endl;
		lastconfFile << toolDiameterMM << endl;
		lastconfFile << Z_AXIS_DOWN << endl;
		lastconfFile << MAX_FEED_RATE << endl;
		lastconfFile << MAX_RAPID_SPEED << endl;
		lastconfFile << ACCELERATION << endl;
		lastconfFile << ACCELERATION_RAPID << endl;
		lastconfFile << STEPS_PER_MM_X << endl;
		lastconfFile << STEPS_PER_MM_Y << endl;
		lastconfFile << STEPS_PER_MM_Z << endl;
		lastconfFile << PASSES << endl;
		lastconfFile << AUTO_LEVELING << endl;
		if (AUTO_LEVELING)
		{
			lastconfFile << AUTO_LEVELING_N_x << endl;
			lastconfFile << AUTO_LEVELING_N_y << endl;
			lastconfFile << AUTO_LEVELING_X_START << endl;
			lastconfFile << AUTO_LEVELING_Y_START << endl;
			lastconfFile << AUTO_LEVELING_X_END << endl;
			lastconfFile << AUTO_LEVELING_Y_END << endl;
		}
		lastconfFile << SERIAL_PORT << endl;
		lastconfFile << BAUD_RATE << endl;
		lastconfFile.close();
	}

	else
	{
		// get data from last.config file:
		ifstream lastconfFile("last.config");
		string line;
		
		getline(lastconfFile, line);
		widthMM = str_to_float(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		toolDiameterMM = str_to_float(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		Z_AXIS_DOWN = str_to_float(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		MAX_FEED_RATE = str_to_float(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		MAX_RAPID_SPEED = str_to_float(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		ACCELERATION = str_to_float(&line, 0, line.size() - 1);

		DECELERATION = -ACCELERATION;

		getline(lastconfFile, line);
		ACCELERATION_RAPID = str_to_float(&line, 0, line.size() - 1);

		DECELERATION_RAPID = -ACCELERATION_RAPID;

		getline(lastconfFile, line);
		STEPS_PER_MM_X = str_to_int(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		STEPS_PER_MM_Y = str_to_int(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		STEPS_PER_MM_Z = str_to_int(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		PASSES = str_to_int(&line, 0, line.size() - 1);

		getline(lastconfFile, line);
		AUTO_LEVELING = (line[0] == '0') ? false : true;

		if (AUTO_LEVELING)
		{
			getline(lastconfFile, line);
			AUTO_LEVELING_N_x = str_to_int(&line, 0, line.size() - 1);

			getline(lastconfFile, line);
			AUTO_LEVELING_N_y = str_to_int(&line, 0, line.size() - 1);

			getline(lastconfFile, line);
			AUTO_LEVELING_X_START = str_to_int(&line, 0, line.size() - 1);

			getline(lastconfFile, line);
			AUTO_LEVELING_Y_START = str_to_int(&line, 0, line.size() - 1);

			getline(lastconfFile, line);
			AUTO_LEVELING_X_END = str_to_int(&line, 0, line.size() - 1);

			getline(lastconfFile, line);
			AUTO_LEVELING_Y_END = str_to_int(&line, 0, line.size() - 1);
		}

		getline(lastconfFile, SERIAL_PORT);

		getline(lastconfFile, line);
		BAUD_RATE = (unsigned long int)str_to_float(&line, 0, line.size() - 1);
	}

	// debug check:
	cout << "settings used last time: " << endl;
	cout << "widthMM = " << widthMM << endl;
	cout << "toolDiameterMM = " << toolDiameterMM << endl;
	cout << "MAX_FEED_RATE = " << MAX_FEED_RATE << endl;
	cout << "MAX_RAPID_SPEED = " << MAX_RAPID_SPEED << endl;
	cout << "ACCELERATION = " << ACCELERATION << endl;
	cout << "DECELERATION = " << DECELERATION << endl;
	cout << "ACCELERATION_RAPID = " << ACCELERATION_RAPID << endl;
	cout << "DECELERATION_RAPID = " << DECELERATION_RAPID << endl;
	cout << "STEPS_PER_MM_X= " << STEPS_PER_MM_X << endl;
	cout << "STEPS_PER_MM_Y= " << STEPS_PER_MM_Y << endl;
	cout << "STEPS_PER_MM_Z= " << STEPS_PER_MM_Z << endl;
	cout << "PASSES= " << PASSES << endl;
	cout << "AUTO_LEVELING = " << AUTO_LEVELING << endl;
	if (AUTO_LEVELING)
	{
		cout << "AUTO_LEVELING_N_x = " << AUTO_LEVELING_N_x << endl;
		cout << "AUTO_LEVELING_N_y = " << AUTO_LEVELING_N_y << endl;
		cout << "AUTO_LEVELING_X_START = " << AUTO_LEVELING_X_START << endl;
		cout << "AUTO_LEVELING_Y_START = " << AUTO_LEVELING_Y_START << endl;
		cout << "AUTO_LEVELING_X_END = " << AUTO_LEVELING_X_END << endl;
		cout << "AUTO_LEVELING_Y_END = " << AUTO_LEVELING_Y_END << endl;
	}
	cout << "SERIAL_PORT = " << SERIAL_PORT << endl;
	cout << "BAUD_RATE = " << BAUD_RATE << endl;

	bitmap_image inputImg(INPUT_BMP_FILE_DIR);

	INPUT_WIDTH = inputImg.width();
	INPUT_HEIGHT = inputImg.height();

	PIXELS_PER_MM = INPUT_WIDTH / widthMM;

	TOOL_DIAMETER = toolDiameterMM * PIXELS_PER_MM;
	
	if (INPUT_WIDTH > INPUT_HEIGHT)
	{
		MAX_X = INPUT_WIDTH;// +4.0f * TOOL_DIAMETER;
		MAX_Y = INPUT_WIDTH;// +4.0f * TOOL_DIAMETER;
	}
	else
	{
		MAX_X = INPUT_HEIGHT;// +4.0f * TOOL_DIAMETER;
		MAX_Y = INPUT_HEIGHT;// +4.0f * TOOL_DIAMETER;
	}

	bitmap_image tempImg((int)MAX_X, (int)MAX_Y);

	WHITE_COLOR.red = 225;
	WHITE_COLOR.green = 225;
	WHITE_COLOR.blue = 225;

	BLACK_COLOR.red = 0;
	BLACK_COLOR.green = 0;
	BLACK_COLOR.blue = 0;

	rgb_t color;

	float blackCutOff = 0.0f;
	for (int i = 2; BLACK_CUT_OFF[i] != '\0'; i++)
		blackCutOff += ((float)(BLACK_CUT_OFF[i] - '0')) / 10.0f;

	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
		{
			inputImg.get_pixel(x, y, color);

			int r = color.red;
			int g = color.green;
			int b = color.blue;
			float brightness = pow(((float)(r * r + g * g + b * b)) / 3.0f, 0.5f) / 255.0f;
			
			if (brightness <= blackCutOff)
				tempImg.set_pixel(x, y, BLACK_COLOR);
			else
				tempImg.set_pixel(x, y, WHITE_COLOR);
		}
	
	tempImg.save_image(TEMP_BMP_FILE_DIR);
	tempImg.save_image(CONST_TEMP_BMP_FILE_DIR);
}