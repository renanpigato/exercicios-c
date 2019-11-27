#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEMPERATURAS_DIA 6
#define DIAS_SEMANA 7
#define TEMPERATURA_LIMITE 60.0
#define TOLERANCIA 5.0

float temperaturas[7][6];
bool  diasInformados[7];
bool  diasTemperaturaSuperior[7];
char  caracter[1000];

float calcularMediaSemana();
float maiorTemperaturaInformada();
float menorTemperaturaInformada();
void  imprimirTemperaturasSuperiores();
void  diaSemanaExtenso(char texto[100], int dia);
int   imprimirSaida(char ch[1000]);
int   exibirErro(FILE* fp);

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

        for (int i = 0; i < DIAS_SEMANA; i++)
        {
            if(!diasInformados[i]) {
                continue;
            }

            imprimirSaida((char*)"\n");
            diaSemanaExtenso((char*)"Dia da semana: ", (i+1));

            for (int j = 0; j < TEMPERATURAS_DIA; j++)
            {
                sprintf(caracter, "\nTemperatura: %.2f", temperaturas[i][j]);
                imprimirSaida(caracter);
            }
        }
        
        printf((char*)"\n");
        imprimirSaida((char*)"\n");

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
    bool  temTemperaturaSuperior = false;

    limiteUltrapassado = (TEMPERATURA_LIMITE * TOLERANCIA/100.0) + TEMPERATURA_LIMITE;    

    for (int i = 0; i < DIAS_SEMANA; i++)
    {
        if(!diasInformados[i]) {
            continue;
        }
                
        for (int j = 0; j < TEMPERATURAS_DIA; j++)
        {
            temperatura = temperaturas[i][j];

            if(temperatura <= limiteUltrapassado) {
                continue;
            }
                
            diasTemperaturaSuperior[i] = true;
            temTemperaturaSuperior = true;
        }
    }

    if(temTemperaturaSuperior) {

        sprintf(caracter, "\nTemperaturas Superiores a tolerancia:");
        imprimirSaida(caracter);

        for (int ii = 0; ii < DIAS_SEMANA; ii++)
        {
            if(!diasTemperaturaSuperior[ii]) {
                continue;
            }
                    
            diaSemanaExtenso((char*)"\nDia: ", (ii+1));

            for (int jj = 0; jj < TEMPERATURAS_DIA; jj++)
            {
                temperatura = temperaturas[ii][jj];

                if(temperatura <= limiteUltrapassado) {
                    continue;
                }

                sprintf(caracter, "\nTemperatura: %f", temperatura);
                imprimirSaida(caracter);
            }
        }
    }

    imprimirSaida((char*)"\n");
}

void diaSemanaExtenso(char texto[100], int dia) {

    char diaSemana[7];

    // printf("debug------------: dia: %i\n", dia);

    switch(dia)
    {
        case 1:
            strcpy(diaSemana, "Domingo");
            break;

        case 2:
            strcpy(diaSemana, "Segunda");
            break;

        case 3:
            strcpy(diaSemana, "Terca");
            break;

        case 4:
            strcpy(diaSemana, "Quarta");
            break;

        case 5:
            strcpy(diaSemana, "Quinta");
            break;

        case 6:
            strcpy(diaSemana, "Sexta");
            break;

        case 7:
            strcpy(diaSemana, "Sabado");
            break;
    }
    // printf("debug------------: diaSemana: %s\n", diaSemana);

    sprintf(caracter, (char*)"%s %s", texto, diaSemana);
    imprimirSaida(caracter);
}
