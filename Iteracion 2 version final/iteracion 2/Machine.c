#include <stdio.h>

#include "Instruction.c"

static const int maxRoutineLevel = 7;

enum machine_operation {
LOADop = 0,
LOADAop = 1,
LOADIop = 2,
LOADLop = 3,
STOREop = 4,
STOREIop = 5,
CALLop = 6,
CALLIop = 7,
RETURNop = 8,
PUSHop = 10,
POPop = 11,
JUMPop = 12,
JUMPIop = 13,
JUMPIFop = 14,
HALTop = 15
};



static struct instruction code[1024];
    
    
// CODE STORE REGISTERS
static const int CBs = 0;
static const int PB = 1024;  // = upper bound of code array + 1
static const int PT = 1052;  // = PB + 28

// REGISTER NUMBERS

enum registers  {
CBr = 0,
CTr = 1,
PBr = 2,
PTr = 3,
SBr = 4,
STr = 5,
HBr = 6,
HTr = 7,
LBr = 8,
L1r = LBr + 1,
L2r = LBr + 2,
L3r = LBr + 3,
L4r = LBr + 4,
L5r = LBr + 5,
L6r = LBr + 6,
CPr = 15
};




// DATA REPRESENTATION

static const int booleanSize = 1;
static const int characterSize = 1;
static const int integerSize = 1;
static const int addressSize = 1;
//static const int closureSize = 2 * addressSize;
static const int closureSize = 2 * 1;

//static const int linkDataSize = 3 * addressSize;
static const int linkDataSize = 3 * 1;
static const int falseRep = 0;
static const int trueRep = 1;
static const int maxintRep = 32767;


// ADDRESSES OF PRIMITIVE ROUTINES

enum primitive_routines_address{
idDisplacement = 1,
notDisplacement = 2,
andDisplacement = 3,
orDisplacement = 4,
succDisplacement = 5,
predDisplacement = 6,
negDisplacement = 7,
addDisplacement = 8,
subDisplacement = 9,
multDisplacement = 10,
divDisplacement = 11,
modDisplacement = 12,
ltDisplacement = 13,
leDisplacement = 14,
geDisplacement = 15,
gtDisplacement = 16,
eqDisplacement = 17,
neDisplacement = 18,
eolDisplacement = 19,
eofDisplacement = 20,
getDisplacement = 21,
putDisplacement = 22,
geteolDisplacement = 23,
puteolDisplacement = 24,
getintDisplacement = 25,
putintDisplacement = 26,
newDisplacement = 27,
disposeDisplacement = 28
};
typedef int Primitive_Routine;



void print_code(int size){

for (int i  = 0; i < size; i ++){

    printf("opcode: %d, registercode: %d , length: %d, value: %d\n",code[i].op,code[i].r,code[i].n,code[i].d);
    
} 


}