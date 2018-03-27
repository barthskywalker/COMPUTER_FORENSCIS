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
//address of MFT = (cluster_number_of_MFT * nfts.sectors_per_cluster * nfts.sectors_per_cluster)
nfts.address_of_MFT= nfts.cluster_number_of_MFT * nfts.Num_sectors * nfts.sectors_per_cluster +startsect;


//What is the type and length of the first two attributes in the $MFT record

char Standard_Information[400];
 fseek(fp, nfts.address_of_MFT, SEEK_SET); // Seek to the start $MFT
 fread(Standard_Information, 1, 400, fp);
 /*
 start of first MFT attribute
  */
 int first_MFT_attribute_offset= *(Standard_Information+0x14);
 //get Attribute type identifier of first attribute
 int Attribute_type_identifier= *(Standard_Information+first_MFT_attribute_offset);
 //copy its string value to NFTS structure
 MFT_attribute_type(Attribute_type_identifier,nfts.first_MFT_attribute_type);
 //get length of if offset got from Table N5: Data structure for a basic MFT record
 nfts.first_MFT_attribute_length=*(Standard_Information+first_MFT_attribute_offset+4);
 //first offset + first MFT attribute length = start of second
 int Second_MFT_attribute_offset =first_MFT_attribute_offset+nfts.first_MFT_attribute_length;
 //get value at offset
 int Second_Attribute_type_identifier= *(Standard_Information+Second_MFT_attribute_offset);
 MFT_attribute_type(Second_Attribute_type_identifier,nfts.second_MFT_attribute_type);
 nfts.second_MFT_attribute_length=*(Standard_Information+Second_MFT_attribute_offset+4);
}
