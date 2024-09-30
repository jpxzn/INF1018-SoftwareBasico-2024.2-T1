/* João Pedro Zaidman dos Santos Gonçalves 2320464*/
/* Davi Cirne Donato 2320399*/
#define _CRT_SECURE_NO_DEPRECATE
#include "converteutf832.h"


void convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida){
    unsigned char byte;
    while(fread(&byte, sizeof(byte),1,arquivo_entrada)==1){
        if(byte == 0x20){
            printf("\n");
            continue;
        }
        else printf("utf8:%x\n",byte);

        //Carecter de 1 byte
        if(!(byte & 0x80)){
            int utf32 = byte;
            utf32 <<= 24;
            printf("utf32:%08x\n",utf32);
        }
        //Carecter de 2 bytes
        if((byte >= 0xC0) && (byte < 0xE0)){
            int utf32 = (byte & 0x1F);
            printf("utf32:%08x\n",utf32);
            fread(&byte, sizeof(byte),1,arquivo_entrada);
            utf32 = (utf32 << 6) | (byte & 0x3F);
            printf("utf8:%x\n",byte);
            printf("utf32:%08x\n",utf32);
        }
        //Carecter de 3 bytes
        if((byte >= 0xE0) && (byte < 0xF0)){
            int utf32 = (byte & 0x0F);
            printf("utf32:%08x\n",utf32);
            for(int i = 0; i < 2; i ++){
                fread(&byte, sizeof(byte),1,arquivo_entrada);
                utf32 = (utf32 << 6) | (byte & 0x3F);
                printf("utf8:%x\n",byte);
                printf("utf32:%08x\n",utf32);
            }
        }
        //Carecter de 4 bytes
        if((byte >= 0xF0) && (byte < 0xF8)){
            int utf32 = (byte & 0x07);
            printf("utf32:%08x\n",utf32);
            for(int i = 0; i < 3; i ++){
                fread(&byte, sizeof(byte),1,arquivo_entrada);
                utf32 = (utf32 << 6) | (byte & 0x3F);
                printf("utf8:%x\n",byte);
                printf("utf32:%08x\n",utf32);
            }
        }
    }
}
