#include <stdlib.h>
#include "run.h"

int compare(Run *a, Run *b)
{
    return a->freq - b->freq;
}

Run *create_run(unsigned char sym, int len, int freq, int code, int codeLen, Run *left, Run *right)
{
    Run *run = (Run *)malloc(sizeof(Run));
    run->symbol = sym;
    run->runLen = len;
    run->freq = freq;
    run->codeword = code;
    run->codewordLen = codeLen;
    run->left = left;
    run->right = right;
    return run;
}

void printRun(Run *p)
{
    printf("%02x:%d:%d:%d:%x\n", p->symbol, p->runLen, p->freq, p->codewordLen, p->codeword);
}