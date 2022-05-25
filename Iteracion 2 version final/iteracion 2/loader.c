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

   void writeR (char leftbracket, int r, char rightbracket) {

    printf("%c",leftbracket);
    switch (r) {
      case CBr:
        printf("CB");
        break;
      case CTr:
	printf("CT");
	break;
      case PBr:
	printf("PB");
	break;
      case PTr:
	printf("PT");
	break;
      case SBr:
	printf("SB");
	break;
      case STr:
	printf("ST");
	break;
      case HBr:
	printf("HB");
	break;
      case HTr:
	printf("HT");
	break;
      case LBr:
	printf("LB");
	break;
      case L1r:
	printf("L1");
	break;
      case L2r:
	printf("L2");
	break;
      case L3r:
	printf("L3");
	break;
      case L4r:
	printf("L4");
	break;
      case L5r:
	printf("L5");
	break;
      case L6r:
	printf("L6");
	break;
      case CPr:
	printf("CP");
	break;
    }

    printf("%c",rightbracket);
  }


 void blankN() {
    printf("      ");
  }


void writeN (int n) {
    printf("(%d) ",n);
    if (n < 10)
      printf("  ");
    else if (n < 100)
      printf(" ");
  }

void writeD (int d) {
    printf("%d",d);
  }

void writePrimitive (int d) {
    switch (d) {
      case idDisplacement:
        printf("id      ");
	break;
      case notDisplacement:
	printf("not     ");
	break;
      case andDisplacement:
	printf("and     ");
	break;
      case orDisplacement:
	printf("or      ");
	break;
      case succDisplacement:
	printf("succ    ");
	break;
      case predDisplacement:
	printf("pred    ");
	break;
      case negDisplacement:
	printf("neg     ");
	break;
      case addDisplacement:
	printf("add     ");
	break;
      case subDisplacement:
	printf("sub     ");
	break;
      case multDisplacement:
	printf("mult    ");
	break;
      case divDisplacement:
	printf("div     ");
	break;
      case modDisplacement:
	printf("mod     ");
	break;
      case ltDisplacement:
	printf("lt      ");
	break;
      case leDisplacement:
	printf("le      ");
	break;
      case geDisplacement:
	printf("ge      ");
	break;
      case gtDisplacement:
	printf("gt      ");
	break;
      case eqDisplacement:
	printf("eq      ");
	break;
      case neDisplacement:
	printf("ne      ");
	break;
      case eolDisplacement:
	printf("eol     ");
	break;
      case eofDisplacement:
	printf("eof     ");
	break;
      case getDisplacement:
	printf("get     ");
	break;
      case putDisplacement:
	printf("put     ");
	break;
      case geteolDisplacement:
	printf("geteol  ");
	break;
      case puteolDisplacement:
	printf("puteol  ");
	break;
      case getintDisplacement:
	printf("getint  ");
	break;
      case putintDisplacement:
	printf("putint  ");
	break;
      case newDisplacement:
	printf("new     ");
	break;
      case disposeDisplacement:
	printf("dispose ");
	break;
    }
  }

 void writeInstruction (struct Data instr) {

    switch (getOperationCode(instr.operation)) {
      case LOADop:
	printf("LOAD  ");
	writeN(atoi(instr.length));
	writeD(atoi(instr.operand));
	writeR('[', getRegisterCode(instr.registers), ']');
	break;

      case LOADAop:
        printf("LOADA ");
        blankN();
        writeD(atoi(instr.operand));
        writeR('[', getRegisterCode(instr.registers), ']');
        break;

      case LOADIop:
        printf("LOADI ");
        writeN(atoi(instr.length));
        break;

      case LOADLop:
        printf("LOADL ");
        blankN();
        writeD(atoi(instr.operand));
        break;

      case STOREop:
        printf("STORE ");
        writeN(atoi(instr.length));
        writeD(atoi(instr.operand));
        writeR('[', getRegisterCode(instr.registers), ']');
        break;

      case STOREIop:
        printf("STOREI");
        writeN(atoi(instr.length));
        break;

      case CALLop:
        printf("CALL  ");
        if (getRegisterCode(instr.registers) == PBr) {
          blankN();
          writePrimitive(atoi(instr.operand));
        } else {
          writeR('(', atoi(instr.length), ')');
          printf("  ");
          writeD(atoi(instr.operand));
          writeR('[', getRegisterCode(instr.registers), ']');
        }
        break;

      case CALLIop:
        printf("CALLI ");
	break;

      case RETURNop:
        printf("RETURN");
        writeN(atoi(instr.length));
        writeD(atoi(instr.operand));
        break;

      case PUSHop:
        printf("PUSH  ");
        blankN();
        writeD(atoi(instr.operand));
        break;

      case POPop:
        printf("POP   ");
        writeN(atoi(instr.length));
        writeD(atoi(instr.operand));
        break;

      case JUMPop:
        printf("JUMP  ");
        blankN();
        writeD(atoi(instr.operand));
        writeR('[', getRegisterCode(instr.registers), ']');
        break;

      case JUMPIop:
        printf("JUMPI ");
        break;

      case JUMPIFop:
        printf("JUMPIF");
        writeN(atoi(instr.length));
        writeD(atoi(instr.operand));
        writeR('[', getRegisterCode(instr.registers), ']');
        break;

      case HALTop:
        printf("HALT  ");
    }

        printf("\n");
  }



void print_file(int cant){

    printf("The content of the file is:\n\n");

    for (int i = 0; i < cant; i++) {

        printf("%d: ",i);
        writeInstruction(object_array[i]);

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





