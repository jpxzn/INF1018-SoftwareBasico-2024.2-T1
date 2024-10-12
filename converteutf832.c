// João Pedro Zaidman dos Santos Gonçalves 2320464
// Davi Donato 2320399

#include "converteutf832.h"

//Calcula e retorna Quantidade de bytes de um caracter utf8, em caso de erro, retorna -1
unsigned int qtdBytes(unsigned int byte){
        if(!(byte & 0x80)) return 1;
        else if((byte >= 0xC0) && (byte < 0xE0)) return 2;
        else if((byte >= 0xE0) && (byte < 0xF0)) return 3;
        else if((byte >= 0xF0) && (byte < 0xF8)) return 4;
        return -1;
}

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida){
    unsigned char byte;
    unsigned int utf32;

    unsigned int bom = 0x0000FEFF;
    if (fwrite(&bom, sizeof(unsigned int), 1, arquivo_saida) != 1) {
        fprintf(stderr, "Erro ao escrever o BOM no arquivo de saída.\n");
        return -1;
    }

    while(fread(&byte, sizeof(byte),1,arquivo_entrada)==1){
        unsigned int numBytes = qtdBytes(byte);
        // Salva apenas o codepoint do primeiro byte do UTF8 em UTF32
        if(numBytes == 1) utf32 = byte;
        else if(numBytes == 2) utf32 = (byte & 0x1F);
        else if(numBytes == 3) utf32 = (byte & 0x0F);
        else if(numBytes == 4) utf32 = (byte & 0x07);

        // Salva o codepoint dos bytes de continuação
        for(int i = 0; i < numBytes - 1; i ++){
                if (fread(&byte, sizeof(byte), 1, arquivo_entrada) != 1) {
                fprintf(stderr, "Erro ao ler byte de continuação do arquivo de entrada.\n");
                return -1;
                }
                utf32 = (utf32 << 6) | (byte & 0x3F);
            }
        if (fwrite(&utf32, sizeof(unsigned int), 1, arquivo_saida) != 1) {
            fprintf(stderr, "Erro ao escrever no arquivo de saída.\n");
            return -1;
        }

    }
    return 0;
}


// Inverte os bytes do caractere UTF32 
unsigned int swapEndian(unsigned int value) { 
    return ((value >> 24) & 0xFF) | ((value << 8)  & 0xFF0000) | ((value >> 8)  & 0xFF00) | ((value << 24) & 0xFF000000); }

// Funcao que retorna o tamanho do caractere em UTF8 e configura o o formato do caractere big endian, em caso de erro retorna -1
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

    // Verificação do BOM
    if (fread(&BOM, 4, 1, arquivoEntrada) != 1) { 
        fprintf(stderr, "Erro ao ler o BOM do arquivo de entrada.\n"); return -1;  } 
    
    // Verificação little endian
    int isLittleEndian = 0;
    if      (BOM == 0xFFFE0000) isLittleEndian = 0;
    else if (BOM == 0x0000FEFF) isLittleEndian = 1;
    else { fprintf(stderr, "BOM inválido.\n"); return -1;  } 

    unsigned int TamanhoUTF8;
    unsigned int U32;
    unsigned char * UTF8 = (unsigned char*) malloc(4);

    if (UTF8 == NULL) { fprintf(stderr, "Erro de alocação de memória.\n"); return -1; }

    while ( fread(&U32, 4, 1, arquivoEntrada) == 1 ) {
        if (!isLittleEndian) U32 = swapEndian(U32); // Caso seja Big Endian o caractere tem seus bytes invertidos
        TamanhoUTF8 = UTF32toUTF8(U32, UTF8);

        if (fwrite(UTF8, TamanhoUTF8, 1, arquivoSaida) != 1) {
            fprintf(stderr, "Erro ao gravar no arquivo de saída.\n");
            free(UTF8);
            return -1; }
        }

    free(UTF8);

    return 0;
    }
