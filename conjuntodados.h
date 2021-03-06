#ifndef _CONJUNTO_DADOS_H
#define _CONJUNTO_DADOS_H

#include <stdbool.h>
#include "lista.h"

typedef struct {
    bool filtraPorIntervalo;
    int intervaloMesMin, intervaloAnoMin;

    bool filtraPorMeses;
    bool mesesSelecionados[12];
} CRITERIOS_FILTRAGEM;

typedef struct {
    int countriesListSize;
    list_node_t* headCountriesOriginal;
    //Aponta para a dummy node de uma nova lista caso hajam critérios de filtragem
    // ou é igual a headCountriesOriginal caso não hajam criterios de filtragem
    list_node_t* headCountriesFiltrada;
    list_node_t* tailCountriesFiltrada;
    int countriesAnoMin, countriesAnoMax;
    int countriesMesMin, countriesMesMax;

    int citiesListSize;
    list_node_t* headCitiesOriginal;
    //Aponta para a dummy node de uma nova lista caso hajam critérios de filtragem
    // ou é igual a headCitiesOriginal caso não hajam criterios de filtragem
    list_node_t* headCitiesFiltrada;
    list_node_t* tailCitiesFiltrada;
    int citiesAnoMin, citiesAnoMax;
    int citiesMesMin, citiesMesMax;

    float citiesTempMin, citiesTempMax;

    CRITERIOS_FILTRAGEM criterios;
} DADOS;

void dados_init(DADOS *dados);
void dados_free(DADOS* dados);
void dados_apaga_listaFiltrada(DADOS* dados);
void dados_aplicar_novos_criterios(DADOS* dados, CRITERIOS_FILTRAGEM *novos_criterios);
int dados_get_mesmin_para_ano(DADOS* dados);

bool cumpre_criterios(dados_temp* valor, CRITERIOS_FILTRAGEM *criterios);
void limpar_criterios(CRITERIOS_FILTRAGEM *criterios);
void criacao_lista_filtrada(DADOS * dados, bool lista_paises, CRITERIOS_FILTRAGEM *novos_criterios);

#endif
