
#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

//Library used to parse the JSON file
#include "parson.h"
#include "loader.h"

#define MAX_LENGTH 300

char File_Name[MAX_LENGTH];


int main(int argc, char **argv)  
{  

    if (argc < 2) {

        printf( "\nEnter the address of the file to use \n\n");

        fgets(File_Name,MAX_LENGTH,stdin);
        File_Name[strcspn(File_Name, "\r\n")] = 0;

        printf("\n");

    }
    else {
        strcpy(File_Name, argv[1]);

    }

    load_Code(File_Name);


    return 0;
}  