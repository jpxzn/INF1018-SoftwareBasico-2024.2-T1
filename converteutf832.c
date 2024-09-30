/* João Pedro Zaidman dos Santos Gonçalves 2320464*/
/* Davi Cirne Donato 2320399*/
#include "converteutf832.h"


void convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida){
    unsigned char byte;
    unsigned int bom = 0x0000FEFF;
    fwrite(&bom, sizeof(unsigned int), 1,arquivo_saida);
    while(fread(&byte, sizeof(byte),1,arquivo_entrada)==1){
        //Carecter de 1 byte
        if(!(byte & 0x80)){
            unsigned int utf32 = byte;
            fwrite(&utf32, sizeof(unsigned int), 1,arquivo_saida);
        }
        //Carecter de 2 bytes
        if((byte >= 0xC0) && (byte < 0xE0)){
            unsigned int utf32 = (byte & 0x1F);
            fread(&byte, sizeof(byte),1,arquivo_entrada);
            utf32 = (utf32 << 6) | (byte & 0x3F);
            fwrite(&utf32, sizeof(unsigned int), 1,arquivo_saida);
        }
        //Carecter de 3 bytes
        if((byte >= 0xE0) && (byte < 0xF0)){
            unsigned int utf32 = (byte & 0x0F);
            for(int i = 0; i < 2; i ++){
                fread(&byte, sizeof(byte),1,arquivo_entrada);
                utf32 = (utf32 << 6) | (byte & 0x3F);
            }
            fwrite(&utf32, sizeof(unsigned int), 1,arquivo_saida);
        }
        //Carecter de 4 bytes
        if((byte >= 0xF0) && (byte < 0xF8)){
            unsigned int utf32 = (byte & 0x07);
            for(int i = 0; i < 3; i ++){
                fread(&byte, sizeof(byte),1,arquivo_entrada);
                utf32 = (utf32 << 6) | (byte & 0x3F);
            }
            fwrite(&utf32, sizeof(unsigned int), 1,arquivo_saida);
        }
    }
}
