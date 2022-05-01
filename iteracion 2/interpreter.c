#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "loader.c"

#define TRUE 1
#define FALSE 0

static int data[1024];

//Data stores registers

//final
static int CB = 0;
static int SB = 0;
static int HB = 1024;  //uper bound of data array

static int CT;
static int CP;
static int ST;
static int HT;
static int LB;
static int status;

static int isNumber = 1;


//Status values

//final
enum status_values{
running = 0,
halted = 1,
failedDataStoreFull = 2,
failedInvalidCodeAddress = 3,
failedInvalidInstruction = 4,
failedOverflow = 5,
failedZeroDivide = 6,
failedIOError = 7
};


//static
static long accumulator;

int content(int r){ //Returns ...
    switch(r){
      case CBr:
        return CB;
      case CTr:
        return CT;
      case PBr:
        return PB;
      case PTr:
        return PT;
      case SBr:
        return SB;
      case STr:
        return ST;
      case HBr:
        return HB;
      case HTr:
        return HT;
      case LBr:
        return LB;
      case L1r:
        return data[LB];
      case L2r:
        return data[data[LB]];
      case L3r:
        return data[data[data[LB]]];
      case L4r:
        return data[data[data[data[LB]]]];
      case L5r:
        return data[data[data[data[data[LB]]]]];
      case L6r:
        return data[data[data[data[data[data[LB]]]]]];
      case CPr:
        return CP;
      default:
        return 0;
    }
}

//Program status
void dump(){ //Writes
    int addr;
    int staticLink;
    int dynamicLink;
    int localRegNum;

    printf("\nState of data store and registers\n\n");

    if(HT == HB){
        printf("            |--------|          (heap is empty)\n");
    }
    else{
        printf("       HB-->\n");
        printf("            |--------|\n");

        for(addr = HB - 1; addr >= HT; addr--){
            printf("%d:\n", addr);
            if (addr == HT)
                printf(" HT-->");
            else
                printf("      ");

            printf("|%d|\n", data[addr]);
        }
        printf("            |--------|\n");
    }
    printf("            |////////|\n");
    printf("            |////////|\n");
    if (ST == SB){
        printf("            |--------|          (stack is empty)\n");
    } 
    else{
        dynamicLink = LB;
        staticLink = LB;
        localRegNum = LBr;
        printf("      ST--> |////////|\n");
        printf("            |--------|\n");

        for(addr = ST - 1; addr >= SB; addr--){
            printf("%d:", addr);
            if (addr == SB)
                printf(" SB-->");
            else if (addr == staticLink){
                    switch (localRegNum) {
                        case LBr:
                        printf(" LB-->");
                        break;
                        case L1r:
                        printf(" L1-->");
                        break;
                        case L2r:
                        printf(" L2-->");
                        break;
                        case L3r:
                        printf(" L3-->");
                        break;
                        case L4r:
                        printf(" L4-->");
                        break;
                        case L5r:
                        printf(" L5-->");
                        break;
                        case L6r:
                        printf(" L6-->");
                        break;
                    }
                    staticLink = data[addr];
                    localRegNum++;
            } else{
                printf("      ");
            }
            if ((addr == dynamicLink) && (dynamicLink != SB))
                printf("|SL= %d|",data[addr]);
            else if ((addr == dynamicLink + 1) && (dynamicLink != SB))
                printf("|DL=%d|",data[addr]);
            else if ((addr == dynamicLink+2)&&(dynamicLink != SB))
                printf("|RA=%d|",data[addr]);
            else
                printf("|%d|",data[addr]);
            printf("\n");
            if (addr == dynamicLink){
                printf("            |--------|\n");
                dynamicLink = data[addr + 1];
            }
        }
    }
    printf("\n");
}

void showStatus(){ // Writes an indication of whether and why the program has terminated.

    printf("\n");
    switch (status) {
      case running:
        printf("Program is running.\n");
        break;
      case halted:
        printf("Program has halted normally.\n");
        break;
      case failedDataStoreFull:
        printf("Program has failed due to exhaustion of Data Store.\n");
        break;
      case failedInvalidCodeAddress:
        printf("Program has failed due to an invalid code address.\n");
        break;
      case failedInvalidInstruction:
        printf("Program has failed due to an invalid instruction.\n");
        break;
      case failedOverflow:
        printf("Program has failed due to overflow.\n");
        break;
      case failedZeroDivide:
        printf("Program has failed due to division by zero.\n");
        break;
      case failedIOError:
        printf("Program has failed due to an IO error.\n");
        break;
    }
    if (status != halted)
      dump();

}


//Interpretation

// Signals failure if there is not enough space to expand the stack or
// heap by spaceNeeded.
void checkSpace(int spaceNeeded){ 

    if (HT - ST < spaceNeeded){
        status = failedDataStoreFull;
    }
}


// Tests whether the given datum represents true.
int isTrue(int datum){ 
    if(datum == trueRep){
        return TRUE;
    } else{
        return FALSE;
    }
}

// Tests whether two multi-word objects are equal, given their common
// size and their base addresses.
int equal(int size, int addr1, int addr2){ 

    int eq = TRUE;
    int index = 0;

    while ((eq == 1) && (index < size)){
        if (data[addr1 + index] == data[addr2 + index])
            index = index + 1;
        else
            eq = FALSE;
    }
    return eq;
}


// Signals failure if the datum is too large to fit into a single word,
// otherwise returns the datum as a single word.
int overflowChecked(long datum){

    if ((-maxintRep <= datum) && (datum <= maxintRep))
      return (int) datum;
    else {
      status = failedOverflow;
      return 0;
    }
}

int toInt(int b){
    
    if (b)
        return trueRep;
    else
        return falseRep;
}


static int currentChar;


int readInt(){

    isNumber = 1;

    char input [50];
    char * characters;
    characters = input;

    int number = 0;
    int signal = 1;
    
    fgets(input,50,stdin);

    input[strcspn(input, "\r\n")] = 0;

    if (*characters == '-'){
        signal = -1;
        characters++;
    }
    if (*characters == '+'){
        characters++;
    } 

    while (*characters != '\0') {

        char symbol = *characters; 

        if (isdigit(*characters)){
            number = number * 10 + symbol - '0';

        }
        else{
            isNumber = 0;
            return 0;
        }       
        characters++; 
	}

    number = number * signal;
    return number;

}


// Invokes the given primitive routine.

void callPrimitive (int primitiveDisplacement) {

    int addr, size;
    char ch;

    switch (primitiveDisplacement) {
      case idDisplacement:
        break; // nothing to be done
      case notDisplacement:
        data[ST - 1] = toInt(!isTrue(data[ST - 1]));
        break;
      case andDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(isTrue(data[ST - 1]) & isTrue(data[ST]));
        break;
      case orDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(isTrue(data[ST - 1]) | isTrue(data[ST]));
        break;
      case succDisplacement:
        data[ST - 1] = overflowChecked(data[ST - 1] + 1);
        break;
      case predDisplacement:
        data[ST - 1] = overflowChecked(data[ST - 1] - 1);
        break;
      case negDisplacement:
        data[ST - 1] = -data[ST - 1];
        break;
      case addDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        data[ST - 1] = overflowChecked(accumulator + data[ST]);
        break;
      case subDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        data[ST - 1] = overflowChecked(accumulator - data[ST]);
        break;
      case multDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        data[ST - 1] = overflowChecked(accumulator * data[ST]);
        break;
      case divDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        if (data[ST] != 0)
          data[ST - 1] = (int) (accumulator / data[ST]);
        else
          status = failedZeroDivide;
        break;
      case modDisplacement:
        ST = ST - 1;
        accumulator = data[ST - 1];
        if (data[ST] != 0)
          data[ST - 1] = (int) (accumulator % data[ST]);
        else
          status = failedZeroDivide;
        break;
      case ltDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] < data[ST]);
        break;
      case leDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] <= data[ST]);
        break;
      case geDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] >= data[ST]);
        break;
      case gtDisplacement:
        ST = ST - 1;
        data[ST - 1] = toInt(data[ST - 1] > data[ST]);
        break;
      case eqDisplacement:
        size = data[ST - 1]; // size of each comparand
        ST = ST - 2 * size;
        data[ST - 1] = toInt(equal(size, ST - 1, ST - 1 + size));
        break;
      case neDisplacement:
        size = data[ST - 1]; // size of each comparand
        ST = ST - 2 * size;
        data[ST - 1] = toInt(! equal(size, ST - 1, ST - 1 + size));
        break;
      case eolDisplacement:
        data[ST] = toInt(currentChar == '\n');
        ST = ST + 1;
        break;
      case eofDisplacement:
        data[ST] = toInt(currentChar == -1);
        ST = ST + 1;
        break;
      case getDisplacement:
        ST = ST - 1;
        addr = data[ST];
        //try {
          currentChar = getchar( );
          //printf("got in getDisplacement\n");
        //} catch (java.io.IOException s) {
        //  status = failedIOError;
        //}
        data[addr] = (int) currentChar;
        break;
      case putDisplacement:
        ST = ST - 1;
        ch = (char) data[ST];
        printf("%c",ch);
        break;
      case geteolDisplacement:
        //try {
          while ((currentChar = getchar( )) != '\n');
          //printf("got in geteolDisplacement\n");
        //} catch (java.io.IOException s) {
        //  status = failedIOError;
        //}
        break;
      case puteolDisplacement:
        printf("\n");
        break;
      case getintDisplacement:
        ST = ST - 1;
        addr = data[ST];

        printf("entro en getintDisplacement\n");
        //cambio a la funcion de Java
        accumulator = readInt();

        if (isNumber == 0)
          status = failedIOError;

        data[addr] = (int) accumulator;
        break;
      case putintDisplacement:
        ST = ST - 1;
        accumulator = data[ST];
        printf("%ld",accumulator);
        break;
      case newDisplacement:
        size = data[ST - 1];
        checkSpace(size);
        HT = HT - size;
        data[ST - 1] = HT;
        break;
      case disposeDisplacement:
        ST = ST - 1; // no action taken at present
        break;
    }

}

    // Runs the program in code store.

void interpretProgram() {

    struct instruction currentInstr;
    int op, r, n, d, addr, index;

    // Initialize registers ...
    ST = SB;
    HT = HB;
    LB = SB;
    CP = CB;

    status = running;

    do {
      // Fetch instruction ...
      currentInstr = code[CP];
      // Decode instruction ...
      op = currentInstr.op;
      r = currentInstr.r;
      n = currentInstr.n;
      d = currentInstr.d;

      //printf("\n opcode: %d, registercode: %d , length: %d, value: %d\n",op,r,n,d);

      // Execute instruction ...
      switch (op) {
        case LOADop:
          addr = d + content(r);
          checkSpace(n);
          for (index = 0; index < n; index++)
            data[ST + index] = data[addr + index];
          ST = ST + n;
          CP = CP + 1;
          break;
        case LOADAop:
          addr = d + content(r);
          checkSpace(1);
          data[ST] = addr;
          ST = ST + 1;
          CP = CP + 1;
          break;
        case LOADIop:
          ST = ST - 1;
          addr = data[ST];
          checkSpace(n);
          for (index = 0; index < n; index++)
            data[ST + index] = data[addr + index];
          ST = ST + n;
          CP = CP + 1;
          break;
        case LOADLop:
          checkSpace(1);
          data[ST] = d;
          ST = ST + 1;
          CP = CP + 1;
          break;
        case STOREop:
          addr = d + content(r);
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          CP = CP + 1;
          break;
        case STOREIop:
          ST = ST - 1;
          addr = data[ST];
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          CP = CP + 1;
          break;
        case CALLop:
          addr = d + content(r);
          if (addr >= PB) {
            callPrimitive(addr - PB);
            CP = CP + 1;
          } else {
            checkSpace(3);
            if ((0 <= n) && (n <= 15))
              data[ST] = content(n); // static link
            else
              status = failedInvalidInstruction;
            data[ST + 1] = LB; // dynamic link
            data[ST + 2] = CP + 1; // return address
            LB = ST;
            ST = ST + 3;
            CP = addr;
          }
          break;
        case CALLIop:
          ST = ST - 2;
          addr = data[ST + 1];
          if (addr >= PB) {
            callPrimitive(addr - PB);
            CP = CP + 1;
          } else {
            // data[ST] = static link already
            data[ST + 1] = LB; // dynamic link
            data[ST + 2] = CP + 1; // return address
            LB = ST;
            ST = ST + 3;
            CP = addr;
          }
          break;
        case RETURNop:
          addr = LB - d;
          CP = data[LB + 2];
          LB = data[LB + 1];
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          ST = addr + n;
          break;
        case PUSHop:
          checkSpace(d);
          ST = ST + d;
          CP = CP + 1;
          break;
        case POPop:
          addr = ST - n - d;
          ST = ST - n;
          for (index = 0; index < n; index++)
            data[addr + index] = data[ST + index];
          ST = addr + n;
          CP = CP + 1;
          break;
        case JUMPop:
          CP = d + content(r);
          break;
        case JUMPIop:
          ST = ST - 1;
          CP = data[ST];
          break;
        case JUMPIFop:
          ST = ST - 1;
          if (data[ST] == n)
            CP = d + content(r);
          else
            CP = CP + 1;
          break;
        case HALTop:
          status = halted;
          break;
      }
      if ((CP < CB) || (CP >= CT))
        status = failedInvalidCodeAddress;
    } while (status == running);

}

void interprete(int amount){

printf("********** TAM Interpreter (C Version 1) **********\n\n");

    CT = amount;
    interpretProgram();
    showStatus();
    
}
