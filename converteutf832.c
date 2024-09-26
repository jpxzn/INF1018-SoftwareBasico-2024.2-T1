/* João Pedro Zaidman dos Santos Gonçalves 2320464*/
/* Davi Cirne Donato 2320399*/
#define _CRT_SECURE_NO_DEPRECATE
#include "converteutf832.h"


void convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida){
    unsigned char byte;
    while(fread(&byte, sizeof(byte),1,arquivo_entrada)==1){
        printf("%x\n",byte);
    }
}
