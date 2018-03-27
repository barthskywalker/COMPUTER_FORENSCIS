/**
 * Header file for Computer Forensics Project
 * StudentName&ID: Barth O'Keeffe    14180847
 *                 Mark O’Neill      14117711
 *                 Lina Albay        14118432
 * Lecturer:       Dr. Jacqueline Walker

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
FILE *fp;

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
struct FAT
{
        int Num_sectors;
        int sector_size;
        int FAT_size;
        int Max_root_enteries;
        int rootSize;
        char *OEM_Name;
        int Sector_address_Data_Area;
        int address_of_Cluster_2;

} fat;
/**
 * structure to store deleted file info
 */
struct Deleted_file
{
        char* name;
        char* contents;
        int file_size;
        int Starting_cluster;
} DelFile;

/**
 * struct NFTS FILEsystem
 */
struct NFTS
{
        int Num_sectors;
        int sectors_per_cluster;
        int cluster_number_of_MFT;
        int address_of_MFT;
        char first_MFT_attribute_type[24];
        int first_MFT_attribute_length;
        char second_MFT_attribute_type[24];
        int second_MFT_attribute_length;

} nfts;

/**
 * Function declarations;
 */
void getFatinfo();
char *concat(const char *s1, const char *s2);
void print_Header(char *s);
char *getOEM(const char *s1);
void getFileFromFatInfo();
void getNFTS_INFO();
void MFT_attribute_type(int type, char strtype[24]);
#endif
