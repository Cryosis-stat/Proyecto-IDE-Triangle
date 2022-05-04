#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

struct Data{
    char * operation;
    char * registers;
    char * length;
    char * operand;
};

struct Data object_array[1024];

FILE *fp;
int amount_instructions_read = 0;
int error = 0;

//Remove whitespaces in a string
void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

// Function to delete whitespaces and new lines
void clean_string(char * text){
    text[strcspn(text, "\r\n")] = 0;
    remove_spaces(text);
}

//parse a element and store it in the object_array array
void parse_element(char * line){

    int pos = strcspn(line, ":") -2;
    char field [pos];
    strncpy(field , line + 1, pos);

    field[pos] = 0;

    char * value;
    value = strchr( line,':') + 1 ;

    if (strcmp(field,"operation") == 0){

        if (strcspn(value, ",") == strlen(value)){
            error = 1;
        }
        else{

            value = value + 1;
            pos = strcspn(value, "\"");
            char value_aux[pos];
            strncpy(value_aux , value , pos);
            value_aux[pos] = 0;
            
            int size = strlen(value_aux);
            object_array[amount_instructions_read].operation = (char *)malloc(sizeof(char)*size);
            strncpy(object_array[amount_instructions_read].operation , value_aux ,size);
            object_array[amount_instructions_read].operation[size] = 0;
        }

    }
    else if(strcmp(field,"register") == 0){

        if (strcspn(value, ",") == strlen(value)){
            error = 1;
        }
        else{

            value = value + 1;
            pos = strcspn(value, "\"");
            char value_aux[pos];
            strncpy(value_aux , value , pos);
            value_aux[pos] = 0;

            int size = strlen(value_aux);
            object_array[amount_instructions_read].registers = (char *)malloc(sizeof(char)*size);
            strncpy(object_array[amount_instructions_read].registers , value_aux ,size);
            object_array[amount_instructions_read].registers[size] = 0;
        }
    }
    else if(strcmp(field,"length") == 0){

        if (strcspn(value, ",") == strlen(value)){
            error = 1;
        }

        pos = strcspn(value, ",");
        char value_aux[pos];
        strncpy(value_aux , value , pos);
        value_aux[pos] = 0;

        int size = strlen(value_aux);
        object_array[amount_instructions_read].length = (char *)malloc(sizeof(char)*size);
        strncpy(object_array[amount_instructions_read].length , value_aux ,size);
        object_array[amount_instructions_read].length[size] = 0;
    }
    else if(strcmp(field,"operand") == 0){

        if (strcspn(value, ",")!= strlen(value)){
            error = 1;
        }
        else {
        
        int size = strlen(value);
        object_array[amount_instructions_read].operand = (char *)malloc(sizeof(char)*size);
        strncpy(object_array[amount_instructions_read].operand , value ,size);
        object_array[amount_instructions_read].operand[size] = 0;

        }

    }
    else{
        error = 1;
    }

}

//open the file, parse the json structure and save the values on the object_array array 
int parse_file(const char *  filename){

    if ( (fp = fopen(filename, "r")) == NULL ){

        printf("Error trying to open the file\n\n");

    }
    else{
        char line[100];

        // read the first line
        fgets(line,100,fp);
        clean_string(line);

        if ( (strcmp(line,"[") == 0) ){   //parse first left bracket "[" 

            fgets(line,100,fp);
            clean_string(line);

        } else {
            printf("Error with the file \n");
            fclose(fp);
            return 0;
        }

        if (strcmp(line,"{") == 0) {  //parse first left  brace "{" 

            while( (strcmp(line,"}")) != 0  && (error !=1 ) ){ // loop to parse objects in the array
                
                
                fgets(line,100,fp);
                clean_string(line);

                if ( strcmp(line,"},") == 0  ){

                    amount_instructions_read ++;
                    fgets(line,100,fp);
                    clean_string(line);


                    if (strcmp(line,"{") != 0)
                        error = 1;

                }
                    
                else{
                    if ( strcmp(line,"}") != 0 ){

                        parse_element(line);  //parse elements of a object

                    }
                }

            }

            fgets(line,100,fp);
            clean_string(line);
        }

        if ( (strcmp(line,"]") == 0) && (error != 1)) {    //parse the right  bracket "]"     
            amount_instructions_read ++;
        }

        else {
            printf("Error with the file \n");
        }

       fclose(fp);

    }
    if (error){
        amount_instructions_read = 0;
    }
    return amount_instructions_read;
}