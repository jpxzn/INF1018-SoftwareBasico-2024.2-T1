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

 int UTF32toUTF8(unsigned int utf32, unsigned char * utf8) {
    if (utf32 <= 0x7F) {
        utf8[0] = utf32 & 0x7F;
        return 1;
    } else if (utf32 <= 0x7FF) {
        utf8[0] = 0xC0 | ((utf32 >> 6) & 0x1F);
        utf8[1] = 0x80 | (utf32 & 0x3F);
        return 2;
    } else if (utf32 <= 0xFFFF) {
        utf8[0] = 0xE0 | ((utf32 >> 12) & 0x0F);
        utf8[1] = 0x80 | ((utf32 >> 6) & 0x3F);
        utf8[2] = 0x80 | (utf32 & 0x3F);
        return 3;
    } else if (utf32 <= 0x10FFFF) {
        utf8[0] = 0xF0 | ((utf32 >> 18) & 0x07);
        utf8[1] = 0x80 | ((utf32 >> 12) & 0x3F);
        utf8[2] = 0x80 | ((utf32 >> 6) & 0x3F);
        utf8[3] = 0x80 | (utf32 & 0x3F);
        return 4;
    } else {
        return -1;
    }
}

int convUtf32p8(FILE *arquivoEntrada, FILE *arquivoSaida) {
    unsigned int BOM;
    fread(&BOM, 4, 1, arquivoEntrada);
    unsigned int TamanhoUTF8;
    unsigned int U32;
    unsigned char * UTF8 = (unsigned char*) malloc(4);

    while ( fread(&U32, 4, 1, arquivoEntrada) == 1 ) {
        TamanhoUTF8 = UTF32toUTF8(U32, UTF8);

        fwrite(UTF8, TamanhoUTF8, 1, arquivoSaida);
        }

    return 0;
    }
