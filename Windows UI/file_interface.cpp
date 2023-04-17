/**
 * svg_interface.cpp
 *
 * Created: 19/06/2022
 *  Author: Ali Emad
 */

using namespace std;

#include "file_interface.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <Windows.h>
#include "config.h"
#include <conio.h>
#include "bitmap_image.hpp"
#include <ctime>
#include <chrono>
#include <thread>

using namespace chrono;

WCHAR* c_str_to_LPCTSTR(const char* str)
{
    int len = strlen(str);
    WCHAR* winStr = new WCHAR[len + 1];
    for (int i = 0; i <= len; i++)
        winStr[i] = str[i];
    return winStr;
}

void create_folder(const char* folderDirStr)
{
    WCHAR* dir = c_str_to_LPCTSTR(folderDirStr);

    CreateDirectory(dir, NULL);

    delete[] dir;
}

void create_temp_folder()
{
    WCHAR* dir = c_str_to_LPCTSTR("temp");

    CreateDirectory(dir, NULL);
    SetFileAttributes(dir, FILE_ATTRIBUTE_HIDDEN);

    delete[] dir;
}

void make_temp_input_bmp_copy()
{
    WCHAR* inputDir = c_str_to_LPCTSTR(INPUT_BMP_FILE_DIR);

    WCHAR* tempInputDir = c_str_to_LPCTSTR(TEMP_BMP_FILE_DIR);

    CopyFile(inputDir, tempInputDir, FALSE);

    delete[] inputDir;
    delete[] tempInputDir;
}

void delete_temp_folder()
{
    WCHAR* dir = c_str_to_LPCTSTR("temp");

    WCHAR* dir2 = c_str_to_LPCTSTR("temp/*");
    WIN32_FIND_DATA data;
    HANDLE hFind = FindFirstFile(dir2, &data);  // FILES
    if ((int)hFind != (int)INVALID_HANDLE_VALUE)
    {
        while (FindNextFile(hFind, &data))
        {
            if ((char)data.cFileName[0] == '.')
                continue;

            char* fullDir = new char[64];
            
            for (int i = 0; dir[i] != '\0'; i++)
                fullDir[i] = (char)dir[i];

            fullDir[4] = '/';

            int i;
            for (i = 0; (char)data.cFileName[i] != '\0'; i++)
                fullDir[i + 5] = (char)data.cFileName[i];

            fullDir[i+5] = '\0';

            DeleteFileA(fullDir);

            delete[] fullDir;
        }
    }

    delete[] dir;

    RemoveDirectoryA("temp");
}

void bmp_to_svg(const char* bmpFileDir, const char* svgFileDir)
{
    string cmd = "potrace ";
    cmd = cmd + bmpFileDir;
    //cmd = cmd + " -s --flat -o ";
    //cmd = cmd + " -s --flat -k ";
    cmd = cmd + " -s -a 0 -k ";
    cmd = cmd + BLACK_CUT_OFF;
    cmd = cmd + " -o ";
    cmd = cmd + svgFileDir;
    system(cmd.c_str());
}

string* get_SVG_data(const char* svgFileDir)
{
    ifstream SVGfile(svgFileDir);

    if (!SVGfile.is_open())
    {
        cout << "Error in: subPath.cpp/string* get_SVG_data(const char* svgFileDir)" << endl;
        cout << "Unable to open file!" << endl;
        exit(-1);
    }

    // dataStrArr[0] is the translate and scale line
    // dataStrArr[1] is the svg paths data
    string* dataStrArr = new string[MAX_PATH_GROUPS_NUMBER_IN_WHOLE_FIG];
    string tempStr;

    // go to the 8th line in file (translate and scale line), and store it in dataStrArr[0]
    for (int i = 0; i < 10; i++)
        getline(SVGfile, dataStrArr[0]);
    // a quick recap on "getline()" function from https://www.geeksforgeeks.org/getline-string-c/ :
    // The C++ getline() is a standard library function that is used to read a string or
    // a line from an input stream.It is a part of the <string> header.The getline()
    // function extracts characters from the input stream and appends it to the string
    // object until the delimiting character is encountered.While doing so the previously
    // stored value in the string object str will be replaced by the input string if any.

    // skip the 11th line (read it into tempStr)
    getline(SVGfile, tempStr);
    
    // get the first line of the first path group, done only once, then its found in:
    // "for (getline(SVGfile, tempStr); tempStr[0] != '<'; getline(SVGfile, tempStr))"
    getline(SVGfile, tempStr);

    // for every path group in svg file
    int strCount;
    for (strCount = 1; tempStr[1] != '/'; strCount++)
    {
        // put space before z or Z chars (if any). (will save some eterations in finding subPaths)
        int len = tempStr.size();
        for (int lastZcharIndex = tempStr.find('z'); 0 <= lastZcharIndex && lastZcharIndex < len; lastZcharIndex = tempStr.find('z', lastZcharIndex + 2))
        {
            tempStr.insert(lastZcharIndex, " ");
            len++;
        }
        
        // first line of the paths group data needs special treatment, because of (<path d=") start
        // skip first 9 chars of this line
        dataStrArr[strCount] = "";
        dataStrArr[strCount] = dataStrArr[strCount] + tempStr.substr(9);

        // get the rest of lines
        for (getline(SVGfile, tempStr); tempStr[0] != '<'; getline(SVGfile, tempStr))
        {
            // put space before z or Z chars (if any). (will save some eterations in finding subPaths)
            int len = tempStr.size();
            for (int lastZcharIndex = tempStr.find('z'); 0 <= lastZcharIndex && lastZcharIndex < len; lastZcharIndex = tempStr.find('z', lastZcharIndex + 2))
            {
                tempStr.insert(lastZcharIndex, " ");
                len++;
            }

            dataStrArr[strCount] += " ";
            dataStrArr[strCount] += tempStr;
        }

        // remove last 3 chars of dataStrArr[1], which are ("/>)
        dataStrArr[strCount] = dataStrArr[strCount].substr(0, dataStrArr[strCount].size() - 3);
    }

    // chop:
    string* tempdataStrArr = new string[strCount+1];
    for (int i = 0; i < strCount; i++)
        tempdataStrArr[i] = dataStrArr[i];
    tempdataStrArr[strCount] = "";  // terminator

    delete[] dataStrArr;

    SVGfile.close();

    return tempdataStrArr;
}

float str_to_float(string* strPtr, int start, int end)
{
    float n = 0.0f;

    bool negative = false;
    if ((*strPtr)[start] == '-')
    {
        negative = true;
        start++;
    }

    bool point = false;
    int pointIndex;
    for (pointIndex = start; pointIndex <= end; pointIndex++)
    {
        if ((*strPtr)[pointIndex] == '.')
        {
            point = true;
            break;
        }
        else if ((*strPtr)[pointIndex] == 'e')
            break;
    }

    bool e = false;
    int eIndex;
    for (eIndex = end - 1; eIndex > start; eIndex--)
        if ((*strPtr)[eIndex] == 'e')
        {
            e = true;
            break;
        }
    if (!e)
        eIndex = end + 1;

    int decadeCounter = 1;
    for (int i = pointIndex - 1; i >= start; i--)
    {
        n += decadeCounter * (int)((*strPtr)[i] - '0');
        decadeCounter *= 10;
    }

    if (point)
    {
        float fDecadeCounter = 0.1f;
        for (int i = pointIndex + 1; i <= eIndex - 1; i++)
        {
            n += fDecadeCounter * (float)((*strPtr)[i] - '0');
            fDecadeCounter /= 10.0f;
        }
    }

    if (e)
    {
        float power = str_to_float(strPtr, eIndex + 1, end);
        n *= (float)pow(10.0, power);
    }
    
    return n * (negative ? -1.0f : 1.0f);
}

int str_to_int(string* strPtr, int start, int end)
{
    int n = 0;

    bool negative = false;
    if ((*strPtr)[start] == '-')
    {
        negative = true;
        start++;
    }

    int decadeCounter = 1;
    for (int i = end; i >= start; i--)
    {
        n += decadeCounter * (int)((*strPtr)[i] - '0');
        decadeCounter *= 10;
    }

    if (negative)
        return -n;

    return n;
}

bool is_number(char ch)
{
    return is_in_str(ch, "-0123456789");
}

bool is_in_str(char ch, const char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (ch == str[i])
            return true;
    return false;
}

bool has_black_pixels(const char* imgDir)
{
    bitmap_image img(imgDir);

    int yMax = img.height();
    int xMax = img.width();

    rgb_t color;
    for (int y=0; y<yMax; y++)
        for (int x = 0; x < xMax; x++)
        {
            img.get_pixel(x, y, color);
            
            // if this pix is black
            if (color.red == 0)
                return true;
        }
    return false;
}

bool is_svg_empty(const char* svgFileDir)
{
    string* strArr = get_SVG_data(svgFileDir);
    if (strArr[1].size() < 2)
    {
        delete[] strArr;
        return true;
    }
    delete[] strArr;
    return false;
}

string get_drag_directory()
{
    string str = "";

    long long int t0 = high_resolution_clock::now().time_since_epoch().count();
    long long int t1 = t0;

    bool gotFirstChar = false;

    while (1)
    {
        while (!_kbhit())
        {                   // 10ms timeout
            while (t1 - t0 < 100000000.0 || !gotFirstChar)
            {
                if (_kbhit())
                {
                    gotFirstChar = true;
                    str += _getch();
                    t0 = t1;
                    continue;
                }
                t1 = high_resolution_clock::now().time_since_epoch().count();
            }
            return str;
        }
    }
}

void take_input_dir(void)
{
    cout << "Drop input bmp file here:" << endl;
    string dd = get_drag_directory();
    int firstDoubleQoutationsIndex = (int)dd.find('\"');
    if (firstDoubleQoutationsIndex < 0 || firstDoubleQoutationsIndex >= (int)dd.size())
        firstDoubleQoutationsIndex = -1;
    INPUT_BMP_FILE_DIR = new char[256];
    for (int i = firstDoubleQoutationsIndex + 1; ; i++)
    {
        if (dd[i] == '\"')
        {
            INPUT_BMP_FILE_DIR[i - (firstDoubleQoutationsIndex + 1)] = '\0';
            break;
        }

        INPUT_BMP_FILE_DIR[i - (firstDoubleQoutationsIndex + 1)] = dd[i];

        if (dd[i] == '\0')
            break;
    }
}