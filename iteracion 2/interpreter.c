#include <stdio.h>

//#include machine

#define TRUE 1
#define False 0

static int[] data = [1024];

//Data stores registers

//final
static int CB = 0;
static int SB = 0;
static int HB = 1024;

static int CT;
static int CP;
static int ST;
static int HT;
static int LB;
static int status;

//Status values

//final
static int running = 0;
static int halted = 1;
static int failedDataaStoreFull = 2;
static int failedInvalidCodeAddres = 3;
static int failedInvalidInstruction = 4;
static int failedOverflow = 5;
static int failedZeroDivide = 6;
static int failedIOError = 7;

//static
static long accumulator;

int content(int r){ //Returns ...
    switch(r){
        //
    }
}

//Program status
void dump(){ //Writes
    int addr;
    int staticLink;
    int dynamicLink;
    int localRegNum;

    printf("State of data store and registers");

    if(HT == HB){
        printf("Heap is empty");
    } else{
        printf("HB-->");
        for(addr = HB-1; addr >= HT; addr--){
            printf("%d:", addr);
            if (addr == HT)
                printf("HT--.");
            else
                printf("   ");

            printf("|%d|", data[addr]);
        }
        printf("   |------|");
    }
    printf(" |///|");
    printf(" |///|");
    if (ST == SB){
        printf("   |----|  stack empty");
    } else{
        dynamicLink = LB;
        staticLink = LB;
        //localRegNum = machine...
        printf("   ST -->|////|");
        printf("   |------|");
        for(addr = ST-1; addr >= SB; addr--){
            printf("%d:", addr);
            if (addr == SB)
                printf("SB");
            else if (addr == staticLink){
                    //switch
                    staticLink = data[addr];
                    localRegNum++;
            } else{
                printf("   ");
            }
            if ((addr == dynamicLink)&&(dynamicLink != SB))
                printf("");
            else if ((addr == dynamicLink+1)&&(dynamicLink != SB))
                printf(" ");
            else if ((addr == dynamicLink+2)&&(dynamicLink != SB))
                printf(" ");
            else
                printf(" ");
            if (addr == dynamicLink){
                printf("   |--|");
                dynamicLink = data[addr+1];
            }
        }
    }
    printf("");
}

void showStatus(){ // Writes ...
}


//Interpretation

void checkSpace(int spaceNeeded){ //Signals...
    if (HT - St < spaceNeeded){
        status = failedDataaStoreFull;
    }
}

int isTrue(int datum){ //Tests ...
    /*if(datum == Machine){
        return TRUE;
    } else{
        return FALSE;
    }*/
}

int equal(int size, int addr1, int addr2){ //Tests ..
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

int overflowChecked(long datum){// Signals
    //
    return 0;
}

/*int toInt(boolean b){
    //
    return 0;
}*/

static int currentChar;

int readInt(){}
