#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 100

#define MIN_ANO 1743
#define MAX_ANO 2013
#define MES_MIN_ANO 11
#define MES_MAX_ANO 6
#define JANEIRO 1
#define DEZEMBRO 12

//TODO
//#define LIMITE_ANOS_STRING
//#define DOUBLECAT(a,b,c) a##0-2018##c

//Le o que o utilizador escreveu e devolve o numero da alinea. Caso seja invalido devolve -1
//TODO qual é o xxxh destas funções?
int perguntar_menu_choice()
{
    int alinea = 0;
    char buf[BUFFER_SIZE];

    fgets(buf, BUFFER_SIZE, stdin);
    if (sscanf(buf, "%d", &alinea) == 0)
    {
        //TODO veriricar se o utilizador escrever algo do genero de "2 5" (isto deveria dar invalido)
        alinea = -1;
    }
    return alinea;
}

int perguntar_anos_a_analisar()
{
    char buf[BUFFER_SIZE];
    int numAnos = -1, intervalo = 0;

    intervalo = MAX_ANO-MIN_ANO;

    printf("Qual o periodo que pretende analisar [1-%d]: ", intervalo);

    do
    {
        fgets(buf, BUFFER_SIZE, stdin);
        if (sscanf(buf, "%d", &numAnos) == 0)
        {
            numAnos = -1;
        }
    } while (numAnos < 1 || intervalo < numAnos);

    return numAnos;
}

//esta função permite selecionar um ano a analisar ou um ano apartir do qual se vai analisar
int perguntar_ano_a_analisar()
{
    char buf[BUFFER_SIZE];
    int _ano = 0;
    bool primeiraTentativa = true;

    do
    {
        if(!primeiraTentativa) {
            printf("Tem de estar dentro dos limites!\n");
        }

        printf("Qual o ano a partir do qual pretende analisar [%d-%d]:\t", MIN_ANO, MAX_ANO);

        fgets(buf, BUFFER_SIZE, stdin);
        if (sscanf(buf, "%d", &_ano) != 1)
        {
            _ano = -1;
        }
        primeiraTentativa = false;
    } while (_ano < MIN_ANO || MAX_ANO < _ano);

    printf("\n");
    return _ano;
}

int calulo_intervalos(int _periodo)
{
    int intervalo = 0;
    intervalo = (MAX_ANO-MIN_ANO)/_periodo;
    return intervalo;
}


void menu_principal(criterios_filtragem *criterios)
{
    bool dentroDoMenu = true;
    int alinea = -1;

    while (dentroDoMenu)
    {
        printf("\n\n\tMenu Principal\n\nEscolha uma das opções seguintes:\n");
        printf("1. Filtragem de dados;\n2. Histórico de Temperaturas;\n");
        printf("3. Análise da temperatura por ano;\n4. Análise da temperatura global.\n");
        printf("\n0 ou Enter. Sair do programa.\n");

        alinea = perguntar_menu_choice();

        switch (alinea)
        {
        case 1:
            menu_filtragem_de_dados(criterios);
            break;
        case 2:
            menu_historico_de_temperaturas(criterios);
            break;
        case 3:
            menu_analise_da_temperatura_por_ano(criterios);
            break;
        case 4:
            menu_analise_da_temperatura_global();
            break;
        case 0:
            printf("Quit\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("\nOpção inválida\n");
            break;
        }
    }
}

void menu_historico_de_temperaturas(criterios_filtragem *criterios)
{
    bool dentroDoMenu = false;
    int alinea = -1;
    int periodo = -1;
    int nr_de_valores_por_intervalo = -1;
    int tmp = -1;

    printf("\n\tMenu Histórico de Temperaturas\n\n");

    periodo = perguntar_anos_a_analisar();
    //printf("período(num de anos) a analisar: %d\n", periodo);

    //VAI SER ÙLTIL PARA DPS    ???
    //calcula quantos anos temos por intervalo, caso normal
    nr_de_valores_por_intervalo = calulo_intervalos(periodo);

    tmp = MIN_ANO + periodo;
    //---cálculo dos intervalos---
    printf("[ %d , %d [\n" ,MIN_ANO, tmp);
    while(tmp + periodo < MAX_ANO)
    {
        printf("[ %d , %d [\n", tmp, tmp + periodo);
        tmp = tmp + periodo;
    }
    if(tmp != MAX_ANO)
    {
        printf("[ %d , %d ]\n" ,tmp, MAX_ANO);
    }
    //---fim---

    do
    {
        //Quando se escolhe qualquer opção ele sai logo do menu. No entanto se for opção
        // invalida ele deve fazer loop
        dentroDoMenu = false;

        printf("\n\nEscolha uma das opções seguintes:\n");
        printf("1. Global: aplica-se a todos os países;\n2. Por País: aplica-se a um único país;\n");
        printf("3. Por Cidade: aplica-se a uma única cidade.\n\n0 ou Enter. Volta ao Menu Principal.\n");

        alinea = perguntar_menu_choice();

        switch (alinea)
        {
        case 1:
            historico_de_temperaturas_global(periodo);
            break;
        case 2:
            historico_de_temperaturas_por_pais(periodo);
            break;
        case 3:
            historico_de_temperaturas_por_cidade(periodo);
            break;
        case 0:
            break;
        default:
            printf("\nOpção inválida\n");
            dentroDoMenu = true;
            break;
        }
    } while (dentroDoMenu);
}
void menu_analise_da_temperatura_por_ano(criterios_filtragem *criterios)
{
    bool dentroDoMenu = true;
    int alinea = -1;
    int ano;

    while (dentroDoMenu)
    {
        printf("\n\tMenu Análise da Temperatura por Ano\n\n");
        ano = perguntar_ano_a_analisar();

        printf("\n\nEscolha uma das opções seguintes:\n");
        printf("1. Análise por País;\n2. Análise por cidade.\n");
        printf("\n0 ou Enter. Volta ao Menu Principal.\n");

        alinea = perguntar_menu_choice();

        switch (alinea)
        {
        case 1:
            analise_por_pais(ano);
            break;
        case 2:
            analise_por_cidade(ano);
            break;
        case 0:
            dentroDoMenu = false;
            break;
        default:
            printf("\nOpção inválida\n");
            break;
        }
    }
}

//MENU Filtragem de dados
void menu_filtragem_de_dados(criterios_filtragem *criterios)
{
    bool dentroDoMenu = true;
    int alinea = -1;

    while (dentroDoMenu)
    {
        printf("\n\tMenu Filtragem de Dados\n\nEscolha uma das opções seguintes:\n");
        printf("1. Limpa critéritos;\n2. Escolhe intervalos para analise;\n");
        printf("3. Escolhe um mês.\n\n0 ou Enter. Volta ao Menu Principal.\n");

        alinea = perguntar_menu_choice();

        switch (alinea)
        {
        case 1:
            opcao_limpa_criteritos(criterios);
            break;
        case 2:
            opcao_escolhe_intervalos_para_analise(criterios);
            break;
        case 3:
            opcao_escolhe_mes(criterios);
            break;
        case 0:
            dentroDoMenu = false; //Sai do menu, voltando para o anterior
            break;
        default:
            printf("\nOpção inválida\n");
            break;
        }
    }
}
void opcao_limpa_criteritos(criterios_filtragem *criterios)
{
    limpar_criterios(criterios);
    printf("\n\n\t---Critéritos Limpos---\n\n");
}

//TODO função demaisada grande, +100 linhas
void opcao_escolhe_intervalos_para_analise(criterios_filtragem *criterios)
{
    printf("\n\n\t---Escolhe intervalos para análise---\n\n");
    printf("Os dados anteriores ao periodo que inserir não serão considerados.\n");

    char buf[BUFFER_SIZE];
    int mes = 0, ano = 0;
    bool primeiraTentativa = true;
    bool intervalo_valido = true;

    /*do
    {
        if(!primeiraTentativa) {
            printf("Tem de estar dentro dos limites!\n");
        }

        printf("Qual o ano a partir do qual pretende analisar [%d-%d]:\t", MIN_ANO, MAX_ANO);

        fgets(buf, BUFFER_SIZE, stdin);
        if (sscanf(buf, "%d", &ano) != 1)
        {
            ano = -1;
        }
        primeiraTentativa = false;
    } while (ano < MIN_ANO || MAX_ANO < ano);

    printf("\n");*/
    ano = perguntar_ano_a_analisar();

    //primeiraTentativa = true;
    do
    {
        if(!intervalo_valido || ano == MIN_ANO) {
            printf("Para o ano de %d só há valores apartir do mês %d !\n", MIN_ANO, MES_MIN_ANO);
            printf("Qual o mes a partir do qual pretende analisar [%d-12]:\t", MES_MIN_ANO);
            intervalo_valido = true;
        }
        else if(!primeiraTentativa) {
            printf("Tem de estar dentro dos limites!\n");
            printf("Qual o mes a partir do qual pretende analisar [1-12]:\t");
        }
        else
        {
            printf("Qual o mes a partir do qual pretende analisar [1-12]:\t");
        }

        fgets(buf, BUFFER_SIZE, stdin);
        if (sscanf(buf, "%d", &mes) != 1)
        {
            mes = -1;
        }
        //quando selecionado o ano minímo, podem não estar todos os meses disponíveis
        if(ano == MIN_ANO && mes < MES_MIN_ANO)
        {
            intervalo_valido = false;
        }
        primeiraTentativa = false;
        //printf("%d < %d || %d < %d || %d\n", criterios->intervaloMesMin, JANEIRO_NUM, DEZEMBRO_NUM,  criterios->intervaloMesMin, !intervalo_valido);
    } while ((mes < JANEIRO || DEZEMBRO < mes)
                || !intervalo_valido);


    criterios->filtraPorIntervalo = true;
    criterios->intervaloAnoMin = ano;
    criterios->intervaloMesMin = mes;

    printf("\n\n\t---Critério aplicado---\n\n");
}
void opcao_escolhe_mes(criterios_filtragem *criterios)
{
    printf("\n\n\t---Escolhe um mês---\n\n");
    printf("Apenas serão considerados os dados do periodo delimitado");

    char buf[BUFFER_SIZE];
    int mes_i = 0, mes_f = 0;
    bool primeiraTentativa = true;

    do
    {
        if(!primeiraTentativa) {
            printf("Tem de estar dentro dos limites!\n");
        }

        printf("Qual o periodo de meses que pertende analidar ao longo dos anos [%d-%d]:\t", JANEIRO, DEZEMBRO);

        fgets(buf, BUFFER_SIZE, stdin);
        if (sscanf(buf, "%d %d", &mes_i, &mes_f) == 1)
        {
            printf("Introduza os números do intervalo separado por pelo menos um espaço\n");
        }
        if (sscanf(buf, "%d %d", &mes_i, &mes_f) !=2)
        {
            mes_i = -1;
            mes_f = mes_i;
        }
        primeiraTentativa = false;
        //TODO pode haver intervalos de 1 mês??
    } while (mes_i < JANEIRO || DEZEMBRO < mes_i || mes_f < JANEIRO || DEZEMBRO < mes_f );

        criterios->filtraPorIntervalo = true;
        criterios->mesMin = mes_i;
        criterios->mesMax = mes_f;

    printf("\n\n\t---Critério aplicado---\n\n");

}


//
void historico_de_temperaturas_global(int periodo)
{
    printf("\n\n\t---Histórico de Temperaturas Global---\n\n");
}
void historico_de_temperaturas_por_pais(int periodo)
{
    printf("\n\n\t---Histórico de Temperaturas por País---\n\n");
}
void historico_de_temperaturas_por_cidade(int periodo)
{
    printf("\n\n\t---Histórico de Temperaturas por Cidade---\n\n");
}
void analise_por_pais(int ano)
{
    printf("\n\n\t---Análise por País---\n\n");
}
void analise_por_cidade(int ano)
{
    printf("\n\n\t---Análise por cidade---\n\n");
}

void menu_analise_da_temperatura_global()
{
    printf("\n\n\t---Análise da temperuta Global---\n\n");
}
