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
        char* size_of_FAT_in_Sectors1= (buf_part_table + 0x16);
        char* size_of_FAT_in_Sectors2= (buf_part_table + 0x17);
        int size_of_FAT_in_Sectors= *(int *)(concat(size_of_FAT_in_Sectors1,size_of_FAT_in_Sectors2));
        /*FAT Area size = (size of FAT in sectors) * (number of FAT copies)*/
        fat.FAT_size=Num_copys_of_FAT * size_of_FAT_in_Sectors;
        /*code to get the total size of Root Directory*/
        char* Max_num_root_enteries1=(buf_part_table + 0x11);
        char* Max_num_root_enteries2=(buf_part_table + 0x12);
        //returns the max number of root directory entries
        fat.Max_root_enteries=*(concat(Max_num_root_enteries1,Max_num_root_enteries2));
        //get size of a sector in bytes
        char* size_of_a_sector1 =(buf_part_table + 0x0B);
        char* size_of_a_sector2 =(buf_part_table + 0x0C);
        fat.sector_size = *(concat(size_of_a_sector1,size_of_a_sector2));

        /*Root dir size = ( max no. of dir entries) * (dir entry size in bytes) / sector size*/
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
