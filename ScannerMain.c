/**
 * ScannerMain.c file for Computer Forensics Project
 * StudentName&ID: Barth O'Keeffe    14180847 
 *                 Mark O’Neill      14117711
 *                 Lina Albay        14118432
 * Lecturer:       Dr. Jacqueline Walker
 * Date  16/02/2018
 */
////////////////////////////////////////////////////////// 
//ScannerMain.c 
/////////////////////////////////////////////////////////

#include "Scanner.h"
int main(int argc, char *argv[])
{
        // Define some variables
        int i, offset = 16, not_exist = 0;
        char buf_part_table[64], vol_type[12];
        fp = fopen(argv[1], "rb");        // Open file for reading - binary mode. Should use error check!
        fseek(fp, 0x1BE, SEEK_SET);       // Seek to the start of the part_entry list
        fread(buf_part_table, 1, 64, fp); // Read the 64-byte block to memory buffer
        print_Header("Content of Master Boot Record");
        for (i = 0; i < 4; i++)
        {
                part_entry[i].type = *(char *)(buf_part_table + 0x04 + (i * offset));
                if (part_entry[i].type == 0)
                        not_exist++;
                part_entry[i].start_sect = *(int *)(buf_part_table + 0x08 + (i * offset));
                part_entry[i].size = *(int *)(buf_part_table + 0x0C + (i * offset));
                switch (part_entry[i].type)
                {
                case 00:
                        strcpy(vol_type, "NOT-VALID");
                        break;
                case 06:
                        strcpy(vol_type, "FAT-16");
                        break;
                case 07:
                        strcpy(vol_type, "NTFS");
                        break;
                case 0x0B:
                        strcpy(vol_type, "FAT-32");
                        break;
                default:
                        strcpy(vol_type, "NOT-DECODED");
                        break;
                }

                // Print out partition content
                printf("Partition %d: Type: %-12s Start: %-12d Size: %-12d\n", i, vol_type, part_entry[i].start_sect,
                       part_entry[i].size);
        }
        getFatinfo();
        getFileFromFatInfo();
        printf("\n\nThe total number of valid partitions is: %d\n\n", (4 - not_exist));
        print_Header("FAT file information");
        printf("\n");
        printf("Total number of sectors          :\t\t %d\n", fat.Num_sectors);
        printf("Sector size is                   :\t\t %d bytes\n", fat.sector_size);
        printf("Total Size of FAT area is        :\t\t %d bytes\n", fat.FAT_size);
        printf("Maxium number of root enteries is:\t\t %d\n", fat.Max_root_enteries);
        printf("Root directory size is           :\t\t %d sectors\n", fat.rootSize);
        printf("OEM Name is                      :\t\t %s\n", fat.OEM_Name);
        printf("first sector of data area        :\t\t %d\n", fat.Sector_address_Data_Area);
        printf("Address of Cluster #2            :\t\t %d\n", fat.address_of_Cluster_2);
        print_Header("File in root directory information");
        printf("Name of Deleted file             :\t\t %s\n", DelFile.name);
        printf("Starting cluster of Deleted file :\t\t %d\n", DelFile.Starting_cluster);
        printf("Data contained in deleted file   :\t\t%s\n", DelFile.contents);
        fclose(fp);
        return (0);
}
