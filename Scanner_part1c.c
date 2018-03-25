#include "Scanner.h"

/**
 * ########### REQUIEMENTS ################
 * - How many bytes per sector for this NTFS volume
 * - How many sectors per cluster for this NTFS volume
 * - What is the sector address for the $MFT file record
 * - What is the type and length of the first two attributes in the $MFT record
 * #######################################################
 */


void getNFTS_INFO(){

  char buf_part_table[100];
  int startsect = part_entry[2].start_sect * 512; //get starting piont of NTFS sector
  fseek(fp, startsect, SEEK_SET); // Seek to the start of the part_entry list
  fread(buf_part_table, 1, 100, fp);
  char temp_buff[2];
  for(int i=0x0B; i< 0x0D;i++){
    sprintf(temp_buff, "%d",*(buf_part_table +i));
  }
  nfts.Num_sectors = (atoi(temp_buff))<<8;
  nfts.sectors_per_cluster = *(buf_part_table+0x0D);

/**
 * code to get bit address of MFT
 */
  char $MFT_temp_buff[10];
  long int num=0;
  int temp;
  //gets the cluster number of MFT
  for(int i=0x37; i>= 0x30;i--){
      int count=0x30;
      $MFT_temp_buff[i-count]=*(buf_part_table +i);
      temp =(int)$MFT_temp_buff[i-count];
      num+=temp;
      if(i>0x30)
      num=num*10;

  }
nfts.cluster_number_of_MFT=num;
//address of MFT = (cluster_number_of_MFT * 8 * 512)
nfts.address_of_MFT= nfts.cluster_number_of_MFT * 8 *512 +startsect;


//What is the type and length of the first two attributes in the $MFT record
/**
 * (1)Standard Information	- Includes information such as timestamp and link count.= 64b
 * (2)Attribute List	- Lists the location of all attribute records that do not fit in the MFT record.
 */
char Standard_Information[64];
 fseek(fp, nfts.address_of_MFT, SEEK_SET); // Seek to the start $MFT
 fread(Standard_Information, 1, 64, fp);
 long unsigned int test=0;
 for(int i=7;i>-1;i--){
   int a =(*(Standard_Information+i))>>4;
   int b= *(Standard_Information+i)^(a<<4);
   printf("%d", b<<4 |a );
   test|=((int)Standard_Information[i])<<8;
   test<<=4;
 }

  printf("\n\n%lx\n\n",test);
 for(int i=8;i<15;i++){
   printf("%d", Standard_Information[i]);
 }

}
