/* João Pedro Zaidman dos Santos Gonçalves 2320464*/
#include "converteutf832.h"

//Calcula e retorna Quantidade de bytes de um caracter utf8
unsigned int qtdBytes(unsigned int byte){
        if(!(byte & 0x80)) return 1;
        else if((byte >= 0xC0) && (byte < 0xE0)) return 2;
        else if((byte >= 0xE0) && (byte < 0xF0)) return 3;
        else if((byte >= 0xF0) && (byte < 0xF8)) return 4;
        return -1;
}

void convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida){
    unsigned char byte;
    unsigned int utf32;

    unsigned int bom = 0x0000FEFF;
    fwrite(&bom, sizeof(unsigned int), 1,arquivo_saida);

    while(fread(&byte, sizeof(byte),1,arquivo_entrada)==1){
        unsigned int numBytes = qtdBytes(byte);

        //Salva apenas o codepoint do primeiro byte utf8
        if(numBytes == 1) utf32 = byte;
        else if(numBytes == 2) utf32 = (byte & 0x1F);
        else if(numBytes == 3) utf32 = (byte & 0x0F);
        else if(numBytes == 4) utf32 = (byte & 0x07);

        //salva o codepoint dos bytes de continuação
        for(int i = 0; i < numBytes - 1; i ++){
                fread(&byte, sizeof(byte),1,arquivo_entrada);
                utf32 = (utf32 << 6) | (byte & 0x3F);
            }
        fwrite(&utf32, sizeof(unsigned int), 1,arquivo_saida);
    }
}
