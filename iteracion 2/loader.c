#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

//Library used to parse the JSON file
#include "parson.h"
#include "loader.h"


JSON_Value *root_value; // Value of reading the JSON file
JSON_Array *commits; //array with the objects of the JSON 
JSON_Object *commit; // Object with the information
size_t i;


void print_file(){

    printf("The content of the file is:\n\n");

    //iterate over the object array
    for (i = 0; i < json_array_get_count(commits); i++) {

        //get the object to read its data
        commit = json_array_get_object(commits, i);

         printf("%.10s %.10s %.0lf %.0lf \n",
            json_object_get_string(commit, "operation"),
            json_object_get_string(commit, "register"),
            json_object_get_number(commit, "length"),
            json_object_get_number(commit, "operand")
        );
    }

}


void load_Code(char * File_Name){

    //read JSON file and parse it
    root_value = json_parse_file(File_Name);
    if (json_value_get_type(root_value) != JSONArray) { // is necesary to check if the file was readed successfully

        printf( "\nError with the file\n\n");
    }
    else{

            /* getting array from root value and printing commit info */
        commits = json_value_get_array(root_value);

        print_file();

        /* cleanup code */
        json_value_free(root_value);
        printf( "\n\n");
    }
}


