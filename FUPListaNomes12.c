#include <stdio.h>
#include <string.h>
#include <math.h>

#define TOTAL_NOMES 12

char nomes[12][100];
int  ocorrencias[12];

int verificarPosicaoNome(char nome[100])
{
    char nomeArmazenado[100];

    for (int posicao = 0; posicao < TOTAL_NOMES; posicao++)
    {
        strcpy(nomeArmazenado, nomes[posicao]);

        if(strcmp(nomeArmazenado, nome) == 0) {
            return posicao;
        }
    }

    return -1;
}

int main ()
{
  
  // FILE* fp = fopen("dados.txt", "w");
  // if(!fp) {
  //   perror("File opening failed");
  //   return EXIT_FAILURE;
  // }

    bool   terminou = false;
    int    cont = 0, posicao, ocorrenciaAtual;
    float  percentualAtual;
    char   nome[100], nomeAtual[100];

    while(!terminou) {

        printf("Informe um nome: ");
        scanf("%s", &nome);

        posicao = verificarPosicaoNome(nome);

        if(posicao == -1) {
            ocorrencias[cont] = 1;
            strcpy(nomes[cont], nome);
        } else {
            ocorrencias[posicao] = ocorrencias[posicao] + 1;
        }

        if ((cont+1) == TOTAL_NOMES) {
            terminou = true;
        }

        cont++;
    }

    printf("\n");
    printf("\n");
    printf("Total de nomes: %i", TOTAL_NOMES);
    for (int i = 0; i < TOTAL_NOMES; i++)
    {
        strcpy(nomeAtual, nomes[i]);
        ocorrenciaAtual = ocorrencias[i];
        percentualAtual = ((float)ocorrenciaAtual / (float)TOTAL_NOMES) * 100.0;
        // percentualAtual = roundf(percentualAtual);

        if(ocorrenciaAtual == 0) {
            continue;
        }

        printf("\nNome atual: %s, ocorrencias: %i, percentual: %.2f%%", nomeAtual, ocorrenciaAtual, percentualAtual);
    }
    printf("\n");

    return 0;
}
