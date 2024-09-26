#include <stdio.h>
#include "converteutf832.h"

int main(){
  FILE* fEntrada = fopen("utf8_peq.txt","r");
  FILE* fSaida = fopen("teste1.txt", "w");

  convUtf8p32(fEntrada, fSaida);

  fclose(fEntrada);
  fclose(fSaida);
  return 0;
}
