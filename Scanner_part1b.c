#include "Scanner.h"
/**
 * Pass the structure array that is the MBR and returns the details of FAT Partition
 * as the structure FAT
 * @param  a place holder for the partition type array
 * @return   The FAT info is returned as a structure
 */
void getFatinfo()
{
        char buf_part_table[100];
        int startsect = part_entry[0].start_sect * 512;
        fseek(fp, startsect, SEEK_SET); // Seek to the start of the part_entry list
        fread(buf_part_table, 1, 100, fp);
        fat.Num_sectors = *(buf_part_table + 0x0D);
        /*code to get the total size of fat Area*/
        int Num_copys_of_FAT = *(buf_part_table + 0x10);
        char temp_buff[2];
        fseek(fp, startsect + 0x16, SEEK_SET); // Seek to the start of the part_entry list
        fread(temp_buff, 1, 2, fp);
        short size_of_FAT_in_Sectors1 = *(int *)(temp_buff);
        int size_of_FAT_in_Sectors = size_of_FAT_in_Sectors1;
        /*FAT Area size = (size of FAT in sectors) * (number of FAT copies)*/
        fat.FAT_size = Num_copys_of_FAT * size_of_FAT_in_Sectors;
        /*code to get the total size of Root Directory*/
        char temp_buff1[2];
        fseek(fp, startsect + 0x11, SEEK_SET); // Seek to the start of the part_entry list
        fread(temp_buff1, 1, 2, fp);
        int Max_num_root_enteries1 = *(int *)(temp_buff1);
        //returns the max number of root directory entries
        fat.Max_root_enteries = Max_num_root_enteries1;
        //get size of a sector in bytes
        char temp_buff2[2];
        fseek(fp, startsect + 0x0B, SEEK_SET); // Seek to the start of the part_entry list
        fread(temp_buff2, 1, 2, fp);
        int size_of_a_sector1 = *(int *)(temp_buff2);
        fat.sector_size = size_of_a_sector1;

        /*Root dir size = ( max no. of dir entries) * (dir entry size in bytes) / sector size*/
        fat.rootSize = fat.Max_root_enteries * 32 / fat.sector_size;
        fat.OEM_Name = getOEM(buf_part_table);
        /*
                 Sector address (Data Area)
                 = (first sector of volume) + (size of reserved area) + (size of FAT Area)
         */
        //get size of reserved Area
        int reserved_Area = *(buf_part_table + 0x0E);
        fat.Sector_address_Data_Area = part_entry[0].start_sect + reserved_Area + fat.FAT_size;
        /*
                 Cluster #2 address = ( first sector of data area ) + ( size of root directory)
         */
        fat.address_of_Cluster_2 = fat.Sector_address_Data_Area + fat.rootSize;
}



void getFileFromFatInfo()
{
        int start = fat.Sector_address_Data_Area*fat.sector_size; // get starting point of root directory
        int buff_size= part_entry[0].size; //get size of root directory in bytes
        char root_buff[buff_size]; //buffer to hold root directory contents
        fseek(fp, start, SEEK_SET); // Seek to the start of the root directory
        fread(root_buff, 1, buff_size, fp); //read contents of root directory into buffer
        int location_of_deleted_file_name;
        //find deleted file 0xE5
        for (int i = 0; i < buff_size; i++) {
              //  printf("%x\n",*root_buff+i);
                if(*root_buff+i==0xE5){
                location_of_deleted_file_name=i;
                printf("%d\n%d\n", location_of_deleted_file_name,start);
              }
        }
        //root_buff+location_of_deleted_file_name-(11*8) to return to the start of the filename
        int start_point=location_of_deleted_file_name-(11*8);
        DelFile.name=root_buff+start_point;
        /*
        get starting cluster
         */
        int Starting_cluster1 = *(root_buff+start_point+0x1A);
        DelFile.Starting_cluster=Starting_cluster1;
        /*
        CSA = (sector address for Cluster #2) + ( (cluster number – 2) * 8 )
         */
        int CSA =fat.address_of_Cluster_2 +((DelFile.Starting_cluster-2)*8);
        int start_of_deleted_data=fat.sector_size*CSA;
        //create temperory buffer to store first 16 characters
        char temp_buff2[16];
        fseek(fp, start_of_deleted_data, SEEK_SET); // Seek to first 16 characters
        fread(temp_buff2, 1, 16, fp);//read in first 16 characters
        DelFile.contents=malloc(strlen(temp_buff2)+1);//make sure structure can hold data
        DelFile.contents=strcpy(DelFile.contents,temp_buff2);//copy data to structure
      }
