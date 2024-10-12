#include <stdio.h>
#include "converteutf832.h"

int main(){
    FILE* fEntrada   = fopen("UTF8_pequeno.txt","rb");
    FILE* fSaida     = fopen("_UTF32_Convertido_pequeno.txt", "wb");
    FILE* fEntrada02 = fopen("UTF32_pequeno_LittleEndian.txt","rb");
    FILE* fSaida02   = fopen("_UTF8_Convertido_pequeno.txt",  "wb");

    convUtf8p32(fEntrada, fSaida);
    convUtf32p8(fEntrada02, fSaida02);

    fclose(fEntrada);
    fclose(fSaida);
    fclose(fEntrada02);
    fclose(fSaida02);

    return 0;
}
 