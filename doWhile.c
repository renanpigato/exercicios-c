#include <stdio.h>

#define TAMANHO 10

int main(void)
{
  int vetor[TAMANHO], i, posicao;

  i = 0;
  posicao = i;
  do{
 
    posicao++;
    vetor[i] = i;

    printf("\nInforme o algarismo da posicao %i/%d: ", posicao, TAMANHO);
    scanf("%d", &vetor[i]);
    i++;

  } while(i < TAMANHO);

  printf("\n\nOs numeros informados foram:");

  i = 0;
  posicao = i;
  while (i < TAMANHO) {
  
    posicao++;

    printf("\nAlgarismo da posicao %i/%d: %i", posicao, TAMANHO, vetor[i]);
    
    i++;
  }

  printf("\n");
}
