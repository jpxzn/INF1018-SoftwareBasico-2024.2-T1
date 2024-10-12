#include <stdio.h>
#include "converteutf832.h"

int main(){
    FILE* fEntrada   = fopen("UTF8_pequeno.txt","rb");
    FILE* fSaida     = fopen("_UTF32_Convertido_pequeno.txt", "wb");
    FILE* fEntrada02 = fopen("UTF32_pequeno_LittleEndian.txt","rb");
    FILE* fSaida02   = fopen("_UTF8_Convertido_pequeno_LittleEndian.txt",  "wb");
    FILE* fEntrada03 = fopen("UTF32_pequeno_BigEndian.txt","rb");
    FILE* fSaida03   = fopen("_UTF8_Convertido_pequeno_BigEndian.txt",  "wb");

    convUtf8p32(fEntrada, fSaida);
    convUtf32p8(fEntrada02, fSaida02);
    convUtf32p8(fEntrada03, fSaida03);

    fclose(fEntrada);
    fclose(fSaida);
    fclose(fEntrada02);
    fclose(fSaida02);
    fclose(fEntrada03);
    fclose(fSaida03);


    return 0;
}
 