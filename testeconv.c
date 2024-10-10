#include <stdio.h>
#include "converteutf832.h"

int main(){
  FILE* fEntrada = fopen("utf8_grande","rb");
  FILE* fSaida = fopen("utf32_peq_convertido.txt", "wb");

  convUtf8p32(fEntrada, fSaida);

  fclose(fEntrada);
  fclose(fSaida);
  return 0;
}
