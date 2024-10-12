#include <stdio.h>
#include "converteutf832.h"

int main(){
    FILE* fEntrada = fopen("utf8_peq.txt","rb");
    FILE* fSaida   = fopen("utf8to32_peq.txt", "wb");
    FILE* fEntrada02 = fopen("utf32_peq.txt","rb");
    FILE* fSaida02   = fopen("utf32to8_peq.txt", "wb");

    convUtf8p32(fEntrada, fSaida);
    convUtf32p8(fEntrada02, fSaida02);

    fclose(fEntrada);
    fclose(fSaida);
    fclose(fEntrada02);
    fclose(fSaida02);

    return 0;
}
 