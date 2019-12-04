#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define TOTAL_NOMES 12

/**
 * @author Renan Pigato Silva
 * @author Lunior Pereira Marques
 */

char nomes[12][100], caracter[1000];
int  ocorrencias[12];

int imprimirSaida(char ch[1000]);
int verificarPosicaoNome(char nome[100]);

int main ()
{
  
    bool   terminou = false;
    int    cont = 0, posicao, ocorrenciaAtual;
    float  percentualAtual;
    char   nome[100], nomeAtual[100];

    FILE* fp = fopen("temperaturas.txt", "w");

    if(!fp) {
        perror("Falhou ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    if(fputs((char*)"", fp) == EOF) {
        
        if (ferror(fp)) {

            printf("Ocorreu um erro ao gravar em arquivo");
            return EXIT_FAILURE;
        }
    }

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

        if(ocorrenciaAtual == 0) {
            continue;
        }

        sprintf(caracter, "\nNome atual: %s, ocorrencias: %i, percentual: %.2f%%", nomeAtual, ocorrenciaAtual, percentualAtual);
        imprimirSaida(caracter);
    }
    printf("\n");

    return 0;
}

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

int imprimirSaida(char ch[1000])
{
    FILE* fp = fopen("nomes.txt", "a");

    if(!fp) {
        perror("Falhou ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    if(fputs(ch, fp) == EOF) {

        if (ferror(fp)) {

            printf("Ocorreu um erro ao gravar em arquivo");
            return EXIT_FAILURE;
        }
    }

    printf("%s", ch);
    
    fclose(fp);
}