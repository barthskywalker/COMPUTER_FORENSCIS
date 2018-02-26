#include "Scanner.h"
/**
 * Pass the structure array that is the MBR and returns the details of FAT Partition
 * as the structure FAT
 * @param  a place holder for the partition type array
 * @return   The FAT info is returned as a structure
 */
void getFatinfo(){
        char buf_part_table[100];
        int startsect = part_entry[0].start_sect*512;
        fseek(fp, startsect, SEEK_SET); // Seek to the start of the part_entry list
        fread(buf_part_table, 1, 100, fp);
        fat.Num_sectors = *(buf_part_table + 0x0D);
        /*code to get the total size of fat Area*/
        int Num_copys_of_FAT= *(buf_part_table + 0x10);
        char temp_buff[2];
        fseek(fp, startsect+0x16, SEEK_SET); // Seek to the start of the part_entry list
        fread(temp_buff, 1, 2, fp);
        short size_of_FAT_in_Sectors1= *(int*)(temp_buff);
        int size_of_FAT_in_Sectors= size_of_FAT_in_Sectors1;
        /*FAT Area size = (size of FAT in sectors) * (number of FAT copies)*/
        fat.FAT_size=Num_copys_of_FAT * size_of_FAT_in_Sectors;
        /*code to get the total size of Root Directory*/
        char temp_buff1[2];
        fseek(fp, startsect+0x11, SEEK_SET); // Seek to the start of the part_entry list
        fread(temp_buff1, 1, 2, fp);
        int Max_num_root_enteries1=*(int*)(temp_buff1);
        //returns the max number of root directory entries
        fat.Max_root_enteries=Max_num_root_enteries1;
        //get size of a sector in bytes
        char temp_buff2[2];
        fseek(fp, startsect+0x0B, SEEK_SET); // Seek to the start of the part_entry list
        fread(temp_buff2, 1, 2, fp);
        int size_of_a_sector1 =*(int*)(temp_buff2);
        fat.sector_size = size_of_a_sector1;

        /*Root dir size = ( max no. of dir entries) * (dir entry size in bytes) / sector size*/
        fat.rootSize=fat.Max_root_enteries*32/fat.sector_size;
        fat.OEM_Name=getOEM(buf_part_table);
}
/**
 * print out headers
 * @param s [description]
 */
void print_Header(char* s){

        printf("///////////////////////////////////////////////////////\n");
        printf("//            %s                //\n",  s);
        printf("///////////////////////////////////////////////////////\n");

}
