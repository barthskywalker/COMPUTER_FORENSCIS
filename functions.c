
#include "Scanner.h"

/**
 * Function to concatanate two string values
 * @param  s1 first string
 * @param  s2
 * @return    return concatanated string
 */
char *concat(const char *s1, const char *s2)
{
        char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the null-terminator
        strcpy(result, s1);
        strcat(result, s2);
        return result;
}

/**
 * prints the OEM name to the screen
 * @param  s1 pointer to start of OEM
 * @return    returns full oem name
 */
char *getOEM(const char *s1)
{
        char *oem;
        oem = concat((s1 + 0x03), (s1 + 0x04));
        oem = concat(oem, (s1 + 0x05));
        oem = concat(oem, (s1 + 0x06));
        oem = concat(oem, (s1 + 0x07));
        oem = concat(oem, (s1 + 0x08));
        oem = concat(oem, (s1 + 0x09));
        oem = concat(oem, (s1 + 0x0A));
        return oem;
}

/**
 * print out headers
 * @param s [description]
 */
void print_Header(char *s)
{

        printf("///////////////////////////////////////////////////////\n");
        printf("//         %s        //\n", s);
        printf("///////////////////////////////////////////////////////\n");
}
/**
 * function to return the attribute type returned form MFT
 * @param type [description]
 */
void MFT_attribute_type(int type, char strtype[24]){
        switch (type)
        {
        case 0x10:
                strcpy(strtype, "$STANDARD_INFORMATION");
                break;
        case 0x20:
                strcpy(strtype, "$ATTRIBUTE_LIST");
                break;
        case 0x30:
                strcpy(strtype, "$FILE_NAME");
                break;
        case 0x40:
                strcpy(strtype, "$OBJECT_ID");
                break;
        case 0x60:
                strcpy(strtype, "$VOLUME_NAME");
                break;
        case 0x70:
                strcpy(strtype, "$VOLUME_INFORMATION");
                break;
        case 0x80:
                strcpy(strtype, "$DATA");
                break;
        case 0x90:
                strcpy(strtype, "$INDEX_ROOT");
                break;
        case 0xA0:
                strcpy(strtype, "$INDEX_ALLOCATION");
                break;
        case 0xB0:
                strcpy(strtype, "$BITMAP");
                break;
        case 0xC0:
                strcpy(strtype, "$REPARSE_POINT");
                break;
        default:
                strcpy(strtype, "NOT-DECODED CORRECTLY");
                break;
        }


}
