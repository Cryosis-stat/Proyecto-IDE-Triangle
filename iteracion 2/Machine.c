#include <stdio.h>

#include <Instruction>

static const int maxRoutineLevel = 7;

static const int LOADop = 0,
static const int LOADAop = 1,
static const int LOADIop = 2,
static const int LOADLop = 3,
static const int STOREop = 4,
static const int STOREIop = 5,
static const int CALLop = 6,
static const int CALLIop = 7,
static const int RETURNop = 8,
static const int PUSHop = 10,
static const int POPop = 11,
static const int JUMPop = 12,
static const int JUMPIop = 13,
static const int JUMPIFop = 14,
static const int HALTop = 15;
    
//static Instruction[] code = new Instruction[1024];
    
    
    
    // CODE STORE REGISTERS
static const int CB = 0,
static const int PB = 1024,  // = upper bound of code array + 1
static const int PT = 1052;  // = PB + 28

// REGISTER NUMBERS


static const intCBr = 0,
static const intCTr = 1,
static const intPBr = 2,
static const intPTr = 3,
static const intSBr = 4,
static const intSTr = 5,
static const int HBr = 6,
static const int HTr = 7,
static const int LBr = 8,
static const int L1r = LBr + 1,
static const int L2r = LBr + 2,
static const int L3r = LBr + 3,
static const int L4r = LBr + 4,
static const int L5r = LBr + 5,
static const int L6r = LBr + 6,
static const int CPr = 15;


// DATA REPRESENTATION

static const int booleanSize = 1,
static const int characterSize = 1,
static const int integerSize = 1,
static const int addressSize = 1,
static const int closureSize = 2 * addressSize,

static const int linkDataSize = 3 * addressSize,
static const int falseRep = 0,
static const int trueRep = 1,
static const int maxintRep = 32767;


// ADDRESSES OF PRIMITIVE ROUTINES

static const int idDisplacement = 1,
static const int notDisplacement = 2,
static const int andDisplacement = 3,
static const int orDisplacement = 4,
static const int succDisplacement = 5,
static const int predDisplacement = 6,
static const int negDisplacement = 7,
static const int addDisplacement = 8,
static const int subDisplacement = 9,
static const int multDisplacement = 10,
static const int divDisplacement = 11,
static const int modDisplacement = 12,
static const int ltDisplacement = 13,
static const int leDisplacement = 14,
static const int geDisplacement = 15,
static const int gtDisplacement = 16,
static const int eqDisplacement = 17,
static const int neDisplacement = 18,
static const int eolDisplacement = 19,
static const int eofDisplacement = 20,
static const int getDisplacement = 21,
static const int putDisplacement = 22,
static const int  geteolDisplacement = 23,
static const int  puteolDisplacement = 24,
static const int  getintDisplacement = 25,
static const int putintDisplacement = 26,
static const int newDisplacement = 27,
static const int disposeDisplacement = 28;