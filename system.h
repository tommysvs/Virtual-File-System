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
        static void get_input();
        static void get_input(string);
        static void menu();
        static void create_disk(string, int);
        static void mkdir();
        static void cd();
        static void ls();
        static void rm();
        static void import_file();
        static void export_file();
    private:
        static void redirect(string, string);
        static void view_disk_info(string);
        static string get_date();
};

#endif