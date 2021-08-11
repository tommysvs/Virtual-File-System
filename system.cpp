#include "system.h"

#define DATABLOCK 4096

//PUBLIC

void System::get_input() {
    string text;

    cout << "user:$ ";
    getline(cin >> ws, text);

    get_input(text);
    get_input();
}

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

    redirect(command, parameter);
}

void System::menu() {
    system("cls");

    string input;
    int option;

    cout << "MENU\n\n";
    cout << "1. View disk info" << endl;
    cout << "Option > ";
    cin >> option;

    switch (option) {
        case 1:
            system("cls");
            cout << "Disk name: ";
            cin >> input;

            view_disk_info(input);
            break;
    }
}

void System::create_disk(string diskName, int fileEntries) {
    fstream disk(diskName + ".bin", ios::out | ios::binary | ios::app);
    
    if (!disk) {
        cout << "Error: Cannot open disk image.";
        return;
    }

    MetaData metadata;
    string date = get_date();
    int c_dn = 0, c_d = 0;


    for (int i = 0; i < diskName.size(); i++)
        metadata.diskName[i] = diskName[i];

    for (int i = diskName.size(); i < 20; i++)
        metadata.diskName[i] = ' ';
    
    for (int i = 0; i < date.size(); i++)
        metadata.diskDate[i] = date[i];

    for (int i = date.size(); i < 20; i++)
        metadata.diskDate[i] = ' ';

    metadata.sizeFileEntries = fileEntries;
    metadata.sizeDataBlock = DATABLOCK;
    metadata.bitSize = 0;

    disk.seekg(0, ios::beg);
    disk.write(reinterpret_cast<const char*>(&metadata), sizeof(MetaData));

    cout << "Disk image successfully created!\n\n";

    disk.close();
}

void System::mkdir() {

}

void System::cd() {

}

void System::ls() {

}

void System::rm() {

}

void System::import_file() {

}

void System::export_file() {

}

//PRIVATE

void System::redirect(string command, string parameter) {
    bool _error = false;

    if (command == "menu")
        menu();
    else if (command == "create disk") {
        if (!parameter.empty()) {
            int fileEntries;

            cout << "Data blocks > ";
            cin >> fileEntries;

            create_disk(parameter, fileEntries);
        }
        else
            _error = true;
    }
    else if (command == "mkdir") {
        if (!parameter.empty())
            mkdir();
        else
            _error = true;
    }
    else
        cout << command << ": command not found\n\n";

    if (_error)
        cout << command << ": missing operand\n\n";
}

void System::view_disk_info(string diskName) {
    system("cls");
    fstream disk(diskName + ".bin", ios::in | ios::binary);
    
    if (!disk) {
        cout << "Error: Cannot open disk.\n\n";
        return;
    }

    disk.seekg(0, ios::beg);

    MetaData actual;

    disk.read(reinterpret_cast<char*>(&actual), sizeof(MetaData));

    while (!disk.eof()) {
        cout << "Disk name: " << actual.diskName << "\n"
            << "Creation date: " << actual.diskDate << "\n"
            << "File entries: " << actual.sizeFileEntries << "\n"
            << "Data blocks: " << actual.sizeDataBlock << " \n"
            << "Bit size: " << actual.bitSize << " \n";
        disk.read(reinterpret_cast<char*>(&actual), sizeof(MetaData));
    }

    cout << "\n";
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