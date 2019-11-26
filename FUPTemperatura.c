#include <stdio.h>
#include <string.h>

#define TEMPERATURAS_DIA 6
#define DIAS_SEMANA 7
#define TEMPERATURA_LIMITE 60.0
#define TOLERANCIA 5.0

float temperaturas[7][6];
bool  diasInformados[7];
bool  diasTemperaturaSuperior[7];

float calcularMediaSemana();
float maiorTemperaturaInformada();
float menorTemperaturaInformada();
void  imprimirTemperaturasSuperiores();
void  diaSemanaExtenso(char texto[100], int dia);

int main ()
{
    bool   terminou = false, leitura = false;
    int    diaInformado;
    float  temperatura, mediaSemana, maiorTemperatura, menorTemperatura;

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

            printf("\n");
            printf("\n");
            diaSemanaExtenso("Dia da semana: ", (i+1));

            for (int j = 0; j < TEMPERATURAS_DIA; j++)
            {
                printf("\nTemperatura: %f", temperaturas[i][j]);
            }
        }
        
        printf("\n");
        printf("\n");

        printf("Media da Semana: %f", mediaSemana);
        printf("\nMaior Temperatura Informada: %f", maiorTemperatura);
        printf("\nMenor Temperatura Informada: %f", menorTemperatura);

        printf("\n");
        printf("\n");

        printf("Temperatura limite: %.2f", TEMPERATURA_LIMITE);
        printf("\nTolerancia: %.0f%%", TOLERANCIA);
        
        printf("\n");
        printf("\n");

        imprimirTemperaturasSuperiores();
    }

    return 0;
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

        printf("Temperaturas Superiores a tolerancia:");

        for (int ii = 0; ii < DIAS_SEMANA; ii++)
        {
            if(!diasTemperaturaSuperior[ii]) {
                continue;
            }
                    
            diaSemanaExtenso("\nDia: ", (ii+1));

            for (int jj = 0; jj < TEMPERATURAS_DIA; jj++)
            {
                temperatura = temperaturas[ii][jj];

                if(temperatura <= limiteUltrapassado) {
                    continue;
                }

                printf("\nTemperatura: %f", temperatura);
            }
        }
    }

    printf("\n");
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

    printf("%s %s", texto, diaSemana);
}
