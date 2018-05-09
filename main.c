#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"
#include "lista.h"
#include "menus.h"
#include "ficheiros.h"

#define CITIES_FILE "tempcities.csv"
#define COUNTRIES_FILE "tempcountries.csv"
#define STRING_SIZE 50
#define BUFFER 100
#define MAX_STRING 500

int main ( void )
{
    int ano_a_analisar = -1, periodo_a_analisar = -1;
    int size_countries_file = 0;
    list_node_t* headListaDados = NULL;

    printf("ola1\n");

    //-----------------poluição starts----------
    int i = 0;
    char nome_temp[MAX_STRING];
    char buffer[BUFFER];
    headListaDados = create_list();
    FILE * fileInput = NULL;
    fileInput = fopen(COUNTRIES_FILE, "r");
    if (fileInput == NULL) {
        //Caso haja um erro imprime-o e sai do programa
        perror("Erro a abrir o ficheiro");
        return EXIT_FAILURE;
    }
    while(fgets(buffer, BUFFER, fileInput) != NULL){
        dados_temp a;
        sscanf(buffer, "%d-%d-%d,%f,%f,%[^\n]",
        &a.dt.ano,
        &a.dt.mes,
        &a.dt.dia,
        &a.temp,
        &a.incerteza,
        nome_temp
        );
        strcpy(a.pais, nome_temp);
        insert_node(headListaDados, &a);
        i++;
    }
    fclose(fileInput);
    //-----------pouição ends

    //size_countries_file = read_file_countries (headListaDados);
    printf("ola2\n");
    print_list(headListaDados);
    printf("ola3\n");
    menu_principal(&periodo_a_analisar, &ano_a_analisar);

    printf("END\n");

    return EXIT_SUCCESS;
}
