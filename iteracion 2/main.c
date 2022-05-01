
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
    //save the amount of instructions readed
    int result = load_Code(File_Name);

    if (result > 0){

        printf ("\n");
        print_file();
        printf ("\n");

        printf( "\nDo you wish to interprete the program? S/N \n\n");

        char response[5];
        fgets(response,5,stdin);
        printf("\n");

        if ( ( strcmp(response,"S\n") == 0 ) || ( strcmp(response,"s\n") == 0 )  ){

            interprete(result);

        }

    }

    /* cleanup code */
    json_value_free(root_value);

    return 0;
}  