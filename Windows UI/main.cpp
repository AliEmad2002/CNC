/*
 * main.cpp
 *
 * Created: 09/06/2022 03:00:28 م
 *  Author: Ali Emad
 */


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
#include "CNC_interface.h"
#include "Time_Calculations.h"

using namespace std;

void main_run_file(void);

// a byte to "cin" input into:
char in;

int main()
{
    while (1)
    {
        main_run_file();

        // make new operation?
        cout << "make new operation? (y): ";
        cin >> in;
        if (in == 'y' || in == 'Y')
            continue;
        else
            break;
    }

    return 0;
}

void main_run_file(void)
{
    // clear console:
    system("cls");

    // take input directory:
    take_input_dir();

    // create a temp folder to store temp data:
    create_temp_folder();

    // initialize all parameters:
    init_config();

    // connect to serial:
    serialib serial;
    connect_serial(&serial, SERIAL_PORT.c_str(), BAUD_RATE);
    cout << "connected to serial\n";

    // send parameters to microcontroller:
    send_parameters_to_microcontroller(&serial);

    // clear console:
    system("cls");

    // make manual movement (if wanted):
    cout << "make manual movement? (y): ";
    cin >> in;
    if (in == 'y' || in == 'Y')
        manual_move(&serial);

    // clear console:
    system("cls");

    // change RAM values of current position:
    cout << "change RAM values of current position? (y): ";
    cin >> in;
    if (in == 'y' || in == 'Y')
        change_RAM_pos(&serial);

    // clear console:
    system("cls");

    // convert input image to svg format:
    bmp_to_svg(TEMP_BMP_FILE_DIR, TEMP_SVG_FILE_DIR);

    // generate G-code:
    gLine* gLineArr = new gLine[MAX_GCODE_LINES_NUMBER_IN_WHOLE_FIG];
    int gLineCount = 0;
    MAIN_generate_G_code(gLineArr, gLineCount);

    // double layer 4 holes:
    cout << "make double layers 4 holes? (y): ";
    cin >> in;
    if (in == 'y' || in == 'Y')
    {
        // make manual movement (if wanted):
        cout << "make manual movement? (y): ";
        cin >> in;
        if (in == 'y' || in == 'Y')
            manual_move(&serial);

        cout << "prepare your machine for making the four holes and enter \'y\': ";
        while (1)
        {
            cin >> in;
            if (in == 'y' || in == 'Y')
                break;
        }
        drill_double_layer_four_holes(&serial, (float)INPUT_WIDTH / PIXELS_PER_MM, (float)INPUT_HEIGHT / PIXELS_PER_MM);
    }

    // clear console:
    system("cls");

    // auto leveling:
    if (AUTO_LEVELING)
    {
        // it could be done in previous operation, so ask user if they want to do it again:
        cout << "scan depth map? (y): ";
        cin >> in;
        if (in == 'y' || in == 'Y')
        {
            cout << "prepare your machine for auto leveling and enter \'y\': ";
            while (1)
            {
                cin >> in;
                if (in == 'y' || in == 'Y')
                    break;
            }
            CNC_auto_leveling(gLineArr, gLineCount, &serial);
        }
    }

    // clear console:
    system("cls");

    // tool changing:
    cout << "change tool? (y): ";
    cin >> in;
    if (in == 'y' || in == 'Y')
    {
        change_tool(&serial);
    }

    // clear console:
    system("cls");

    // save G-code to hard drive:
    save_G_code_file(gLineArr, gLineCount, G_CODE_OUTPUT_FILE_DIR);

    // count estimated time:
    double estimatedTime = find_estimated_time(gLineArr, gLineCount);
    cout << "estimated time= ";
    print_time(estimatedTime);

    // release memory:
    delete[] gLineArr;

    // send G-code:
    cout << "prepare your machine to start milling and enter \'y\': ";
    while (1)
    {
        cin >> in;
        if (in == 'y' || in == 'Y')
            break;
    }

    // clear console:
    system("cls");

    CNC_send_G_code(&serial);

    // tell I'm done!:
    cout << "operation successful." << endl;
}


















