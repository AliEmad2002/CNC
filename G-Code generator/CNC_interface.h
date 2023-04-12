#pragma once

using namespace std;

void CNC_auto_leveling(gLine* gLineArr, int& gLineCount, serialib* sPtr);

void CNC_change_tool(serialib* sPtr);

void CNC_send_G_code(serialib* sPtr);

void send_parameters_to_microcontroller(serialib* sPtr);

void drill_double_layer_four_holes(serialib* sPtr, float PCBwidth, float PCBheight);

void go_to(serialib* sPtr, float x, float y, float z, float feedRate = -1.0);

void manual_move(serialib* sPtr);

void change_RAM_pos(serialib* sPtr);

void reset_RAM_pos(serialib* sPtr);

void probe(serialib* sPtr);