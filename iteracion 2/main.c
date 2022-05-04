
#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

//Library used to parse the JSON file
#include "interpreter.c"

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
   // load the TAM instructions from a JSON file into code memory
    
    int result = load_Code(File_Name);

    if (result > 0){

        printf ("\n");
        print_file(File_Name);
        printf ("\n");

        printf( "\nDo you wish to interpret the program? Y/N \n\n");

        char response[5];
        fgets(response,5,stdin);
        printf("\n");

        if ( ( strcmp(response,"Y\n") == 0 ) || ( strcmp(response,"y\n") == 0 )  ){

            interprete(result);

        }else{

            if (( strcmp(response,"N\n") != 0 ) && ( strcmp(response,"n\n") != 0 ) )
                printf("You  entered an incorrect value\n\n");
        }

    }

    /* cleanup code */
    json_value_free(root_value);

    return 0;
}  