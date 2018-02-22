/**
 * Header file for Computer Forensics Project
 * Authour Barth O'Keeffe 14180847
 * Date  16/02/2018
 */


#ifndef Scanner_H
#define Scanner_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
   globals
 */
//File pionter
FILE * fp;

/**
 * structure declarations
 */
struct Partition
{
        char type;
        int start_sect;
        int size;
} part_entry[4]; // 4 x partition table entry
/**
 * struct fat FILEsystem
 */
struct FAT {
        int Num_sectors;
        int sector_size;
        int FAT_size;
        char * Max_root_enteries;
        int rootSize;
        char* OEM_Name;

} fat;
/**
 * Function declarations;
 */
void getFatinfo();
char* concat(const char *s1, const char *s2);
void print_Header(char* s);
char* getOEM(const char *s1);
#endif
