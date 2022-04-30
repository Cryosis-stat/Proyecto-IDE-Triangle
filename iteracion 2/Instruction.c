#include <stdio.h>

struct instruction{
    int op = 0;
    int r = 0;
    int n = 0;
    int d = 0;
};


struct instruction write(int op, int r, int n, int d){
    struct instruction inst;
    inst.op = op;
    inst.r = r
    inst.n = n;
    inst.d = d
    return inst;
}

//void read(){}
