#include <stdio.h>

int retornarPosicaoMediana(int tamanhoInferiorArvore)
{
  int largura, posicaoMediana;

  largura = tamanhoInferiorArvore;
  largura--;
  largura = largura / 2;

  posicaoMediana = largura;
  posicaoMediana++;

  return posicaoMediana;
}

void imprimirBase(int base, int coluna, int posicaoMediana)
{
  if ((coluna >= (posicaoMediana - (base / 2))) && (coluna <= (posicaoMediana + (base / 2)))) {
    printf("=");
  } else {
    printf(" ");
  }
}

void imprimirTronco(int tamanhoInferiorArvore, int tamanhoTronco, int base)
{
  int posicaoMediana;

  posicaoMediana = retornarPosicaoMediana(tamanhoInferiorArvore);

  for (int linha = 1; linha <= 4; linha++) {
    for(int coluna = 1; coluna <= tamanhoInferiorArvore; coluna++) {
      if (coluna == posicaoMediana) {
        printf("|");
      } else {
        if (tamanhoTronco > 1) {
          if ((coluna >= (posicaoMediana - 1)) && (coluna <= (posicaoMediana + 1))) {
            printf("|");
          } else {
            if (linha == 4) {
              imprimirBase(base, coluna, posicaoMediana);
            } else {
              printf(" ");
            }
          }
        } else {
          if (linha == 4) {
            imprimirBase(base, coluna, posicaoMediana);
          } else {
            printf(" ");
          }
        }
      }
    }

    printf("\n");
  }
}


bool imprimirCaracter(int linha, int coluna, int posicaoMediana)
{
  if (coluna == posicaoMediana) {
    return true;
  }

  if (linha >= 1) {
    if ((coluna >= (posicaoMediana - linha)) && (coluna <= (posicaoMediana + linha))) {
      return true;
    }
  }
  
  return false;
}

void imprimirLinha(int linha, int tamanhoInferiorArvore)
{
  int posicaoMediana;

  posicaoMediana = retornarPosicaoMediana(tamanhoInferiorArvore);

  for (int coluna = 1; coluna <= tamanhoInferiorArvore; coluna++)
  {
    if (imprimirCaracter(linha, coluna, posicaoMediana)) {
      if(coluna == posicaoMediana) {
        if (linha == 0) {
          printf("*");
        } else {
          printf("|");
        }
      } else {
        printf("#");
      }
    } else {
      printf(" ");
    }
  }
  
  printf("\n");
}

int main()
{
  int base, tamanhoInferiorArvore, tamanhoMinimo = 4, tamanhoTronco = 1;

  printf("\nVamos desenhar uma arvore de natal na tela!");
  printf("\nPara isso preciso que informe um numero que servira de tamanho do pe da arvore.");
  printf("\nATENCAO esse numero deve ser:");
  printf("\n- Inteiro");
  printf("\n- Par");
  printf("\n- Maior que %i", tamanhoMinimo);
  printf("\nNumero: ");
  scanf("%i", &base);

  while(base < tamanhoMinimo || (base % (tamanhoMinimo / 2)) != 0)
  {
    printf("\nOlha so preciso que o numero seja maior que %i e tambem que seja par!", tamanhoMinimo);
    printf("\nOutra coisa precisa ser inteiro tambem!");
    printf("\nNumero: ");
    scanf("%i", &base);

    printf("\n\n");
  }

  if (base > (tamanhoMinimo * 2)) {
    tamanhoTronco += 2;
  }

  tamanhoInferiorArvore = (base * 2) + tamanhoTronco;

  printf("\n\n");

  for (int linha = 0; linha <= ((tamanhoInferiorArvore - 1) / 2); linha++)
  {
    imprimirLinha(linha, tamanhoInferiorArvore);
  }
  imprimirTronco(tamanhoInferiorArvore, tamanhoTronco, base);

  return 0;
}

