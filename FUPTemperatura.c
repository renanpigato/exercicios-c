#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEMPERATURAS_DIA 6
#define DIAS_SEMANA 7
#define TEMPERATURA_LIMITE 60.0
#define TOLERANCIA 5.0

/**
 * @author Renan Pigato Silva
 * @author Lunior Pereira Marques
 */

float temperaturas[7][6];
bool  diasInformados[7];
char  caracter[1000];

float  calcularMediaSemana();
float  maiorTemperaturaInformada();
float  menorTemperaturaInformada();
void   imprimirTemperaturasSuperiores();
char * diaSemanaExtenso(int dia);
int    imprimirSaida(char ch[1000]);
int    exibirErro(FILE* fp);

int main ()
{
    bool   terminou = false, leitura = false, error = false;
    int    diaInformado, codigoRetornado;
    float  temperatura, mediaSemana, maiorTemperatura, menorTemperatura;

    FILE* fp = fopen("temperaturas.txt", "w");

    if(!fp) {
        perror("Falhou ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    if(fputs((char*)"", fp) == EOF)
        return exibirErro(fp);

    while(!terminou) {

        printf("------------------------------------------");
        printf("\n0) SAIR e VISUALIZAR RESULTADO");
        printf("\n1) Domingo");
        printf("\n2) Segunda");
        printf("\n3) Terca");
        printf("\n4) Quarta");
        printf("\n5) Quinta");
        printf("\n6) Sexta");
        printf("\n7) Sabado");
        printf("\nSelecione o dia da semana para informar as temperaturas: ");
        scanf("%i", &diaInformado);

        if(diaInformado == 0) {

            terminou = true;

        } else {

            switch(diaInformado) {

                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    leitura = true;
                    diasInformados[diaInformado-1] = true;

                    printf("Informe as 6 temperaturas do dia:\n");
                    for (int t = 0; t < TEMPERATURAS_DIA; t++)
                    {
                        printf("Temperatura (%i): ", (t+1));
                        scanf("%f", &temperatura);

                        temperaturas[diaInformado-1][t] = temperatura;
                    }
                    break;

                default:
                    leitura = false;
                    printf(">>> -------------------------------------- <<<\n");
                    printf(">>> DEVE SELECIONAR UMA DAS OPCOES ABAIXO! <<<\n");-
                    printf(">>> -------------------------------------- <<<\n");
                    break;
            }
        }
    }

    if(leitura) {

        mediaSemana = calcularMediaSemana();
        maiorTemperatura = maiorTemperaturaInformada();
        menorTemperatura = menorTemperaturaInformada();

        printf(">>> -------------------------------------- <<<\n");
        printf(">>>               RESULTADO                <<<\n");-
        printf(">>> -------------------------------------- <<<\n");
        
        sprintf(caracter, "\nMedia da Semana: %.2f", mediaSemana);
        imprimirSaida(caracter);
        
        sprintf(caracter, "\nMaior Temperatura Informada: %.2f", maiorTemperatura);
        
        imprimirSaida(caracter);
        
        sprintf(caracter, "\nMenor Temperatura Informada: %.2f", menorTemperatura);
        imprimirSaida(caracter);

        printf((char*)"\n");
        imprimirSaida((char*)"\n");

        sprintf(caracter, "\nTemperatura limite: %.2f", TEMPERATURA_LIMITE);
        imprimirSaida(caracter);

        sprintf(caracter, "\nTolerancia: %.0f%%", TOLERANCIA);
        imprimirSaida(caracter);
        
        printf((char*)"\n");
        imprimirSaida((char*)"\n");

        imprimirTemperaturasSuperiores();
    }

    return 0;
}

int imprimirSaida(char ch[1000])
{
    FILE* fp = fopen("temperaturas.txt", "a");

    if(!fp) {
        perror("Falhou ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    if(fputs(ch, fp) == EOF)
        return exibirErro(fp);

    printf("%s", ch);
    
    fclose(fp);
}

int exibirErro(FILE* fp)
{
    if (ferror(fp)) {
        printf("Ocorreu um erro ao gravar em arquivo");
        return EXIT_FAILURE;
    }
}

float calcularMediaSemana()
{
    float qtdeTemperaturas, media, temperatura;
    qtdeTemperaturas = media = temperatura = 0.0;

    for (int i = 0; i < DIAS_SEMANA; i++)
    {
        if(!diasInformados[i]) {
            continue;
        }
                
        for (int j = 0; j < TEMPERATURAS_DIA; j++)
        {
            temperatura = temperaturas[i][j];
            qtdeTemperaturas++;
            media += temperatura;
        }
    }

    return (media / qtdeTemperaturas);
}

float maiorTemperaturaInformada()
{
    float maiorTemperatura, temperatura;
    maiorTemperatura = temperatura = 0.0;

    for (int i = 0; i < DIAS_SEMANA; i++)
    {
        if(!diasInformados[i]) {
            continue;
        }
                
        for (int j = 0; j < TEMPERATURAS_DIA; j++)
        {
            temperatura = temperaturas[i][j];

            if(temperatura > maiorTemperatura) {
                maiorTemperatura = temperatura;
            }
        }
    }

    return maiorTemperatura;
}

float menorTemperaturaInformada()
{
    float menorTemperatura, temperatura;
    menorTemperatura = temperatura = 0.0;

    for (int i = 0; i < DIAS_SEMANA; i++)
    {
        if(!diasInformados[i]) {
            continue;
        }
                
        for (int j = 0; j < TEMPERATURAS_DIA; j++)
        {
            temperatura = temperaturas[i][j];

            if(temperatura < menorTemperatura || menorTemperatura == 0.0) {
                menorTemperatura = temperatura;
            }
        }
    }

    return menorTemperatura;
}

void imprimirTemperaturasSuperiores()
{
    float limiteUltrapassado, temperatura;
    char * diaDaSemana;

    limiteUltrapassado = (TEMPERATURA_LIMITE * TOLERANCIA/100.0) + TEMPERATURA_LIMITE;

    imprimirSaida((char*)"\nTemperaturas:\n");

    for (int i = 0; i < DIAS_SEMANA; i++)
    {           
        diaDaSemana = diaSemanaExtenso((i+1));

        sprintf(caracter, "%s", diaDaSemana);
        imprimirSaida(caracter);

        imprimirSaida((char*)" => ");

        for (int j = 0; j < TEMPERATURAS_DIA; j++)
        {
            imprimirSaida((char*)"|");

            temperatura = temperaturas[i][j];

            if(!diasInformados[i]) {
                temperatura = 00.0;
            }

            sprintf(caracter, " %2.2f ", temperatura);
            imprimirSaida(caracter);

            if(temperatura > limiteUltrapassado) {
                imprimirSaida((char*)"*");
            } else {
                imprimirSaida((char*)" ");
            }
                
            if((j+1) == TEMPERATURAS_DIA) {
                imprimirSaida((char*)"|");
            }
        }

        imprimirSaida((char*)"\n");
    }

    imprimirSaida((char*)"\n");
}

char * diaSemanaExtenso(int dia) {

    static char diaSemana[7];

    // printf("debug------------: dia: %i\n", dia);

    switch(dia)
    {
        case 1:
            sprintf(diaSemana, "%s", "Domingo");
            break;

        case 2:
            sprintf(diaSemana, "%s", "Segunda");
            break;

        case 3:
            sprintf(diaSemana, "%s", "Terca  ");
            break;

        case 4:
            sprintf(diaSemana, "%s", "Quarta ");
            break;

        case 5:
            sprintf(diaSemana, "%s", "Quinta ");
            break;

        case 6:
            sprintf(diaSemana, "%s", "Sexta  ");
            break;

        case 7:
            sprintf(diaSemana, "%s", "Sabado ");
            break;
    }
    // printf("debug------------: diaSemana: %s\n", diaSemana);

    return diaSemana;
}
