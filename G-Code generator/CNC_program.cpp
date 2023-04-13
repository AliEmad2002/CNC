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

using namespace std;

static float CNC_x = 0.0f;
static float CNC_y = 0.0f;
static float CNC_z = 0.0f;

void CNC_auto_leveling(gLine* gLineArr, int& gLineCount, serialib* sPtr)
{
    // send G29 command:
    string cmd = "G29 L";
    cmd += to_string(AUTO_LEVELING_X_START);
    cmd += " R";
    cmd += to_string(AUTO_LEVELING_X_END);
    cmd += " F";
    cmd += to_string(AUTO_LEVELING_Y_START);
    cmd += " B";
    cmd += to_string(AUTO_LEVELING_Y_END);
    cmd += " N";
    cmd += to_string(AUTO_LEVELING_N_x - 3);    // V = N - 3
    cmd += " N";
    cmd += to_string(AUTO_LEVELING_N_y - 3);    // V = N - 3
    send_string_ack(sPtr, cmd.c_str());
}

void CNC_send_G_code(serialib* sPtr)
{
    ifstream GCodefile(G_CODE_OUTPUT_FILE_DIR);
    string line;
    while (getline(GCodefile, line))
    {
        send_string_ack(sPtr, line.c_str());
    }
}

void send_parameters_to_microcontroller(serialib* sPtr)
{
    string GCodeMsg;
    // send maximum feed rate value to microcontroller:
    // so far it's assumed that all x, y, z axis have the same.
    GCodeMsg = "M203 X";
    GCodeMsg += to_string(MAX_FEED_RATE);
    send_string_ack(sPtr, GCodeMsg.c_str());

    // send feed and rapid accleration value to microcontroller:
    GCodeMsg = "M204 P";
    GCodeMsg += to_string(ACCELERATION);
    GCodeMsg += " T";
    GCodeMsg += to_string(ACCELERATION_RAPID);
    send_string_ack(sPtr, GCodeMsg.c_str());
}

void go_to(serialib* sPtr, float x, float y, float z, float feedRate)
{
    string GCodeMsg;

    // if rapid:
    if (feedRate == -1.0)
    {
        GCodeMsg = "G0 X";
        GCodeMsg += to_string(x);
        GCodeMsg += " Y";
        GCodeMsg += to_string(y);
        GCodeMsg += " Z";
        GCodeMsg += to_string(z);
    }
    // else feed:

    else
    {
        GCodeMsg = "G1 X";
        GCodeMsg += to_string(x);
        GCodeMsg += " Y";
        GCodeMsg += to_string(y);
        GCodeMsg += " Z";
        GCodeMsg += to_string(z);
        GCodeMsg += " F";
        GCodeMsg += to_string(feedRate);
    }

    send_string_ack(sPtr, GCodeMsg.c_str());

    CNC_x = x;
    CNC_y = y;
    CNC_z = z;
}

void drill_double_layer_four_holes(serialib* sPtr, float PCBwidth, float PCBheight)
{
    // tool up:
    go_to(sPtr, 0, 0, 10);

    // first hole:
    // go to it rapid:
    go_to(sPtr, -10.0, -10.0, 10.0);
    go_to(sPtr, -10.0, -10.0, 1.0);
    // drill (feed):
    go_to(sPtr, -10.0, -10.0, -15.0, 1.0);
    // tool up (rapid):
    go_to(sPtr, -10.0, -10.0, 10.0);

    // second hole:
    // go to it rapid:
    go_to(sPtr, PCBwidth + 10.0, -10.0, 10.0);
    go_to(sPtr, PCBwidth + 10.0, -10.0, 1.0);
    // drill (feed):
    go_to(sPtr, PCBwidth + 10.0, -10.0, -15.0, 1.0);
    // tool up (rapid):
    go_to(sPtr, PCBwidth + 10.0, -10.0, 10.0);

    // third hole:
    // go to it rapid:
    go_to(sPtr, PCBwidth + 10.0, PCBheight + 10.0, 10.0);
    go_to(sPtr, PCBwidth + 10.0, PCBheight + 10.0, 1.0);
    // drill (feed):
    go_to(sPtr, PCBwidth + 10.0, PCBheight + 10.0, -15.0, 1.0);
    // tool up (rapid):
    go_to(sPtr, PCBwidth + 10.0, PCBheight + 10.0, 10.0);

    // fourth hole:
    // go to it rapid:
    go_to(sPtr, -10.0, PCBheight + 10.0, 10.0);
    go_to(sPtr, -10.0, PCBheight + 10.0, 1.0);
    // drill (feed):
    go_to(sPtr, -10.0, PCBheight + 10.0, -15.0, 1.0);
    // tool up (rapid):
    go_to(sPtr, -10.0, PCBheight + 10.0, 10.0);

    // back home:
    go_to(sPtr, 0, 0, 10);
    go_to(sPtr, 0, 0, 0);
}

void manual_move(serialib* sPtr)
{
    cout << "1. enter coordinates values to move to." << endl;
    cout << "2. use arrows (or W, S, A, D) to move." << endl;
    char in;
    while (1)
    {
        cin >> in;
        if (in == '1')
        {
            while (1)
            {
                float x, y, z;
                cout << "x: ";
                cin >> x;
                cout << "y: ";
                cin >> y;
                cout << "z: ";
                cin >> z;

                cout << "rapid(r)?   or   feed(else)? : ";
                cin >> in;
                if (in == 'r')
                    go_to(sPtr, x, y, z);
                else
                    go_to(sPtr, x, y, z, 0);

                cout << "enter another position? (y): ";
                cin >> in;
                if (in == 'y' || in == 'Y')
                    continue;
                else
                    break;
            }
            break;
        }
        else if (in == '2')
        {
            cout << "press \"esc\" to exit manual mode." << endl;
            cout << "press \"c + f\" to change speed." << endl;
            cout << "press \"c + s\" to change distance per press" << endl;
            cout << "default values: 10 mm/sec,   2 mm/press" << endl;
            float speed = 10.0;
            float dPerPress = 2.0;

            // prior to any thing, change speed while staying in same current position:
            go_to(sPtr, CNC_x, CNC_y, CNC_z, speed);

            bool isKeyPressed = false;
            while (1)
            {
                isKeyPressed = false;

                if (GetKeyState(VK_CONTROL) & 0x8000)
                {
                    if ((GetKeyState(VK_UP) | (GetKeyState('W'))) & 0x8000)
                    {
                        CNC_z += dPerPress;
                        isKeyPressed = true;
                    }

                    if ((GetKeyState(VK_DOWN) | (GetKeyState('S'))) & 0x8000)
                    {
                        CNC_z -= dPerPress;
                        isKeyPressed = true;
                    }
                }

                else
                {
                    if ((GetKeyState(VK_UP) | (GetKeyState('W'))) & 0x8000)
                    {
                        CNC_y += dPerPress;
                        isKeyPressed = true;
                    }

                    if ((GetKeyState(VK_DOWN) | (GetKeyState('S'))) & 0x8000)
                    {
                        CNC_y -= dPerPress;
                        isKeyPressed = true;
                    }
                }

                if ((GetKeyState(VK_RIGHT) | (GetKeyState('D'))) & 0x8000)
                {
                    CNC_x += dPerPress;
                    isKeyPressed = true;
                }

                if ((GetKeyState(VK_LEFT) | (GetKeyState('A'))) & 0x8000)
                {
                    CNC_x -= dPerPress;
                    isKeyPressed = true;
                }

                if (GetKeyState('C') & 0x8000)
                {
                    if (GetKeyState('F') & 0x8000)
                    {
                        cout << "enter new speed (mm/sec): ";
                        cin >> speed;

                        // prior to any thing, change speed while staying in same current position:
                        go_to(sPtr, CNC_x, CNC_y, CNC_z, speed);
                    }

                    else if (GetKeyState('S') & 0x8000)
                    {
                        cout << "enter new distance per press (mm): ";
                        cin >> dPerPress;
                    }
                }

                if (GetKeyState(VK_ESCAPE) & 0x8000)
                    break;

                if (isKeyPressed)
                    go_to(sPtr, CNC_x, CNC_y, CNC_z, speed);
            }
            
            break;
        }

        else
            continue;
    }

}

void change_RAM_pos(serialib* sPtr)
{
    cout << "enter new position values: " << endl;
    
    cout << "x: ";
    cin >> CNC_x;
    cout << "y: ";
    cin >> CNC_y;
    cout << "z: ";
    cin >> CNC_z;

    string cmd = "G92 X";
    cmd += to_string(CNC_x);
    
    cmd += " Y";
    cmd += to_string(CNC_y);

    cmd += " Z";
    cmd += to_string(CNC_z);

    send_string_ack(sPtr ,cmd.c_str());
}

void reset_RAM_pos(serialib* sPtr)
{
    send_string_ack(sPtr, "G92 X0 Y0 Z0");
}

void probe(serialib* sPtr, bool automatic)
{
    if (automatic)
    {
        send_string_ack(sPtr, "G30");
        return;
    }

    // clear console:
    system("cls");

    cout << "Manual probing mode\n";
    cout << "use up & down arrows for moving the z-axis,\n";
    cout << "use left & right arrows to change mm displacement per press,\n";
    cout << "press \'x\' to increase speed, \'z\' to decrease speed\n";
    cout << "press \'esc\' to exit\n";

    float speed = 10.0;
    float dPerPress = 2.0;

    bool isKeyPressed;

    while (1)
    {
        isKeyPressed = false;

        if ((GetKeyState(VK_UP) | (GetKeyState('W'))) & 0x8000)
        {
            CNC_z -= dPerPress;
            isKeyPressed = true;
        }

        if ((GetKeyState(VK_DOWN) | (GetKeyState('S'))) & 0x8000)
        {
            CNC_z += dPerPress;
            isKeyPressed = true;
        }


        if ((GetKeyState(VK_RIGHT) | (GetKeyState('D'))) & 0x8000)
        {
            dPerPress++;
            isKeyPressed = true;
        }

        if ((GetKeyState(VK_LEFT) | (GetKeyState('A'))) & 0x8000)
        {
            dPerPress--;
            isKeyPressed = true;
        }

        if (GetKeyState('X') & 0x8000)
        {
            speed++;
            isKeyPressed = true;
        }

        if (GetKeyState('Z') & 0x8000)
        {
            speed--;
            isKeyPressed = true;
        }

        if (GetKeyState(VK_ESCAPE) & 0x8000)
            break;

        if (isKeyPressed)
        {
            go_to(sPtr, CNC_x, CNC_y, CNC_z, speed);

            // update display:
            system("cls");

            cout << "Manual probing mode\n";
            cout << "use up & down arrows for moving the z-axis,\n";
            cout << "use left & right arrows to change mm displacement per press,\n";
            cout << "press \'x\' to increase speed, \'z\' to decrease speed\n";
            cout << "press \'esc\' to exit\n";
            cout << "============================================================\n";
            cout << "mm per press = " << dPerPress << endl;
            cout << "speed        = " << speed << endl;
        }
    }

}