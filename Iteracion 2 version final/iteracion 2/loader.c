#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "parser.c"

//Machine
#include "Machine.c"



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



void print_file(int cant){

    printf("The content of the file is:\n\n");

    for (int i = 0; i < cant; i++) {

         printf("%d: %.10s %.10s %.10s %.10s \n", i,
            object_array[i].operation,
            object_array[i].registers,
            object_array[i].length,
            object_array[i].operand
        );
    }
}


int load_Code(int cant){

    int pos ;
 

    for (pos = 0; pos < cant; pos++) {

        
        code[pos].op = getOperationCode(object_array[pos].operation);
        code[pos].r = getRegisterCode(object_array[pos].registers);
        code[pos].n = atoi(object_array[pos].length);
        code[pos].d = atoi(object_array[pos].operand);


    }

    return pos;

}





