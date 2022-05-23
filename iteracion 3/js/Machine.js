const maxRoutineLevel = 7;

const machine_operation = {
    LOADop: 0,
    LOADAop: 1,
    LOADIop: 2,
    LOADLop: 3,
    STOREop: 4,
    STOREIop: 5,
    CALLop: 6,
    CALLIop: 7,
    RETURNop: 8,
    PUSHop: 10,
    POPop: 11,
    JUMPop: 12,
    JUMPIop: 13,
    JUMPIFop: 14,
    HALTop: 15
};

var instruction = 1024;

// CODE STORE REGISTERS
const CBs = 0;
const PB = 1024;  // = upper bound of code array + 1
const PT = 1052;  // = PB + 28

const registers = {
    CBr: 0,
    CTr: 1,
    PBr: 2,
    PTr: 3,
    SBr: 4,
    STr: 5,
    HBr: 6,
    HTr: 7,
    LBr: 8,
    //L1r = LBr + 1,
    L1r: 8 + 1,

    //L2r = LBr + 1,
    L2r: 8 + 2,

    //L3r = LBr + 1,
    L3r: 8 + 3,

    //L4r = LBr + 1,
    L4r: 8 + 4,

    //L5r = LBr + 1,
    L5r: 8 + 5,

    //L6r = LBr + 1,
    L6r: 8 + 6,
    CPr: 15
};

// DATA REPRESENTATIONclea

const booleanSize = 1;
const characterSize = 1;
const integerSize = 1;
const addressSize = 1;
//static const int closureSize = 2 * addressSize;
const closureSize = 2 * 1;

//static const int linkDataSize = 3 * addressSize;
const linkDataSize = 3 * 1;
const falseRep = 0;
const trueRep = 1;
const maxintRep = 32767;

// ADDRESSES OF PRIMITIVE ROUTINES

const primitive_routines_address = {
    idDisplacement : 1,
    notDisplacement : 2,
    andDisplacement : 3,
    orDisplacement : 4,
    succDisplacement : 5,
    predDisplacement : 6,
    negDisplacement : 7,
    addDisplacement : 8,
    subDisplacement : 9,
    multDisplacement : 10,
    divDisplacement : 11,
    modDisplacement : 12,
    ltDisplacement : 13,
    leDisplacement : 14,
    geDisplacement : 15,
    gtDisplacement : 16,
    eqDisplacement : 17,
    neDisplacement : 18,
    eolDisplacement : 19,
    eofDisplacement : 20,
    getDisplacement : 21,
    putDisplacement : 22,
    geteolDisplacement : 23,
    puteolDisplacement : 24,
    getintDisplacement : 25,
    putintDisplacement : 26,
    newDisplacement : 27,
    disposeDisplacement : 28
    };


    console.log(primitive_routines_address.addDisplacement);
