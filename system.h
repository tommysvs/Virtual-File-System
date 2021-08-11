#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>

using namespace std;

enum class EntryType {
    DISK, FOLDER, FILE
};

struct MetaData {
    char diskName[20];
    char diskDate[20];
    int sizeFileEntries;
    int sizeDataBlock;
    int bitSize;
};

struct FileEntry {
    char name[20];
    EntryType type;
    char date[20];
    unsigned int size;
    unsigned int directBlocks[12];
    unsigned int indirectBlocks[3];
};

class System {
    public:
        void get_input();
        void get_input(string);
        void menu();
        void create_disk(string, int);
        void mkdir();
        void cd();
        void ls();
        void rm();
        void importF();
        void exportF();
    private:
        void redirect(string, string);
        void view_disk_info(string);
        string get_date();
};

#endif