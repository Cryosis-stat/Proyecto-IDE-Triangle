#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

//Library used to parse the JSON file
#include "parson.h"

//Machine
#include "Machine.c"



static JSON_Value *root_value; // Value of reading the JSON file
static JSON_Array *commits; //array with the objects of the JSON 
static JSON_Object *commit; // Object with the information
size_t i;


int getOperationCode( const char * operation ){
   
   int opCode = 0;

    if( strcmp(operation,"LOAD") == 0)
        opCode = LOADop;
    else if( strcmp(operation,"LOADA") == 0)
        opCode = LOADAop;
    else if( strcmp(operation,"LOADI") == 0 )
        opCode = LOADIop;
    else if( strcmp(operation,"LOADL") == 0 )
        opCode = LOADLop;
    else if( strcmp(operation,"STORE") == 0 )
        opCode = STOREop;
    else if( strcmp(operation,"STOREI") == 0 )
        opCode = STOREIop;
    else if( strcmp(operation,"CALL") == 0 )
        opCode = CALLop;
    else if( strcmp(operation,"CALLI") == 0 )
        opCode = CALLIop;
    else if( strcmp(operation,"RETURN") == 0 )
        opCode = RETURNop;
    else if( strcmp(operation,"PUSH") == 0 )
        opCode = PUSHop;
    else if( strcmp(operation,"POP") == 0 )
        opCode = POPop;
    else if( strcmp(operation,"JUMP") == 0 )
        opCode = JUMPop;
    else if( strcmp(operation,"JUMPI") == 0 )
        opCode = JUMPIop;
    else if( strcmp(operation,"JUMPIF") == 0 )
        opCode = JUMPIFop;
    else if( strcmp(operation,"HALT") == 0 )
        opCode = HALTop;

   return opCode;
   }


int getRegisterCode( const char * registers ){
   

   int registerCode;
   
    if( strcmp(registers,"CB") == 0)
        registerCode = CBr;
    else if( strcmp(registers,"CT") == 0)
        registerCode = CTr;
    else if( strcmp(registers,"PB") == 0)
        registerCode = PBr;
    else if( strcmp(registers,"PT") == 0)
        registerCode = PTr;
    else if( strcmp(registers,"SB") == 0)
        registerCode = SBr;
    else if( strcmp(registers,"ST") == 0)
        registerCode = STr;
    else if( strcmp(registers,"HB") == 0)
        registerCode = HBr;
    else if( strcmp(registers,"HT") == 0)
        registerCode = HTr;
    else if( strcmp(registers,"LB") == 0)
        registerCode = LBr;
    else if( strcmp(registers,"L1") == 0)
        registerCode = L1r;
    else if( strcmp(registers,"L2") == 0)
        registerCode = L2r;
    else if( strcmp(registers,"L3") == 0)
        registerCode = L3r;
    else if( strcmp(registers,"L4") == 0)
        registerCode = L4r;
    else if( strcmp(registers,"L5") == 0)
        registerCode = L5r;
    else if( strcmp(registers,"L6") == 0)
        registerCode = L6r;
    else if( strcmp(registers,"CP") == 0)
        registerCode = CPr; 
    else
        registerCode = -1;
   
   return registerCode;
}






void print_file(){


    int size = json_array_get_count(commits);
    printf("The content of the file is:\n\n");

    //iterate over the object array
    for (i = 0; i < size; i++) {

        //get the object to read its data
        commit = json_array_get_object(commits, i);

         printf("%d: %.10s %.10s %.0lf %.0lf \n", i,
            json_object_get_string(commit, "operation"),
            json_object_get_string(commit, "register"),
            json_object_get_number(commit, "length"),
            json_object_get_number(commit, "operand")
        );
    }

}


int load_Code(char * File_Name){

    int istructions_amount = 0;
    //read JSON file and parse it
    root_value = json_parse_file(File_Name);
    if (json_value_get_type(root_value) != JSONArray) { // is necesary to check if the file was readed successfully

        printf( "\nError with the file\n\n");
    }
    else{
            /* getting array from root value and printing commit info */
        commits = json_value_get_array(root_value);

        int size = json_array_get_count(commits);

        for (istructions_amount = 0; istructions_amount < size; istructions_amount++) {

            commit = json_array_get_object(commits, istructions_amount);
           
            code[istructions_amount].op = getOperationCode(json_object_get_string(commit, "operation"));
            code[istructions_amount].r = getRegisterCode(json_object_get_string(commit, "register"));
            code[istructions_amount].n = json_object_get_number(commit, "length");
            code[istructions_amount].d = json_object_get_number(commit, "operand");


        }

        
    }
    return istructions_amount;

}





