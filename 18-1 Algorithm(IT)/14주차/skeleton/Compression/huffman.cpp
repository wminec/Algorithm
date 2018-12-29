#include <stdlib.h>
#include "binaryheap.h"
#define MAX 10000

Run *runs[MAX];
int numberRuns = 0;
Heap *theHeap;
Run *theRoot = NULL;
long long fileSize = 0;
Run *chars[256] = { 0 };

void addRun(unsigned char sym, int len);
void printHeaps();
void assignCodeWords(Run *pRun, int i, int i1);
void insertToArray(Run *pRun);

void collectRuns(FILE *file)
{
  // Binary 파일이므로 fread 함수를 이용하여 파일을 읽는다.
}


void createHuffmanTree()
{


}

void preOrderTraverse(Run *node, int depth) {
    for (int i=0; i<depth; i++)
        printf(" ");
    if (node == NULL) {
        printf("null\n");
    }
    else {
        printRun(node);
        preOrderTraverse(node->left, depth + 1);
        preOrderTraverse(node->right, depth + 1);
    }
}

void printHuffmanTree() {
    preOrderTraverse(theRoot, 0);
}

void assignCodewords(Run *p, unsigned int codeword, unsigned int length) {



}


void insertToArray(Run *r) {



}


void storeRunsIntoArray(Run *p) {

}

Run *findRun(unsigned char sym, int len)
{



    return NULL;
}


void outputFrequencies(FILE *fOut)  {


}

void encode(FILE *fIn, FILE *fOut) {

}

void compressFile(FILE *fp, FILE *fout)
{
    collectRuns(fp);
    printAllRuns();
    createHuffmanTree();
    assignCodewords(theRoot, 0, 0);
    storeRunsIntoArray(theRoot);
    printArray();

    outputFrequencies(fout);

    fseek(fp, 0, SEEK_SET);
    encode(fp, fout);

    fclose(fout);
}

void inputFrequencies(FILE *fIn) {


}

void decode(FILE *fin, FILE *fout) {

}

void decompressFile(FILE *fin, FILE *fout)
{
    inputFrequencies(fin);
    createHuffmanTree();
    assignCodewords(theRoot, 0, 0);
    decode(fin, fout);
}

char *fileToCompress = "ldr3_1101.gif";

int main() {   // for compressing
   FILE *fp = fopen(fileToCompress, "rb");
   if (fp == NULL) {
       printf("Open failed.\n");
       return 1;
   }
   FILE *fout = fopen("compressed.cmp", "wb");
   compressFile(fp, fout);
   fclose(fout);
   fclose(fp);
}

// int main() {   // for decompressing
//     FILE *fp = fopen("compressed.cmp", "rb");
//     if (fp == NULL) {
//         printf("Open failed.\n");
//         return 1;
//     }
//     FILE *fout = fopen("decompressed.gif", "wb");
//     decompressFile(fp, fout);
//     fclose(fout);
//     fclose(fp);
// }
