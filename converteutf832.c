/* João Pedro Zaidman dos Santos Gonçalves 2320464*/
/* Davi Cirne Donato 2320399*/
#define _CRT_SECURE_NO_DEPRECATE
#include "converteutf832.h"


int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida){
    char teste;
    while(fscanf(arquivo_entrada,'%c', &teste)==1){
        printf("%c",teste);
    }
    return 1;
}
