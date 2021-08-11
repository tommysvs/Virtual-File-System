#include "system.h"

void System::get_input(string input) {
    string command, parameter;
    int counter = 0;

    for (int i = 0; i < input.size(); i++) {
        if (command == "create") {
            command += " disk";
            i += 5;
            counter++;
        }
        else if (input[i] != ' ' && counter == 0)
            command += input[i];
        else if (counter == 1 && input[i] != ' ')
            parameter += input[i];
        else if (input[i] == ' ')
            counter++;
    }

    create_disk(parameter);
}

void System::create_disk(string parameter) {
    fstream disk(parameter + ".bin", ios::out | ios::binary | ios::app);
    
    if (!disk) {
        cout << "Error: Cannot open disk image.";
        return;
    }

    disk.close();
}

string System::get_date() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    string date;
    int day, month, year;

    day = newtime.tm_mday;
    month = newtime.tm_mon + 1;
    year = 1900 + newtime.tm_year;
    date += to_string(day);
    date += '/';
    date += to_string(month);
    date += '/';
    date += to_string(year);

    return date;
}