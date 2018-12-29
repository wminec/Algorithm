#ifndef COMPRESSION_RUN_H
#define COMPRESSION_RUN_H
#include <stdio.h>

typedef struct run Run;
struct run {
    unsigned char symbol;
    int runLen;
    int freq;
    Run *left, *right;

    unsigned int codeword;
    unsigned int codewordLen;
};

int compare(Run *, Run *);
Run *create_run(unsigned char sym, int len, int freq, int code, int codeLen, Run *left, Run *right);
void printRun(Run *p);
#endif //COMPRESSION_RUN_H
