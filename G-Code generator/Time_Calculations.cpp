#include <iostream>
#include <stdio.h>

#include "Time_Calculations.h"

using namespace std;

void print_time(double seconds)
{
    unsigned long int hrs = (unsigned long int)seconds / 3600;
    unsigned long int mins = (unsigned long int)seconds / 60 - hrs * 60;
    unsigned long int secs = (unsigned long int)seconds - hrs * 3600 - mins * 60;

    if (hrs > 0)
        cout << hrs << "h ";
    if (mins > 0)
        cout << mins << "min ";
    cout << secs << "sec" << endl;
}