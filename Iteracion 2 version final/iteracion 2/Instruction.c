#include <stdio.h>

struct instruction{
    int op;
    int r;
    int n;
    int d;
};


struct instruction write(int op, int r, int n, int d){
    struct instruction inst;
    inst.op = op;
    inst.r = r;
    inst.n = n;
    inst.d = d;
    return inst;
}

