#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "TreeMap.h"
#include "Map.h"
#include "defFunciones.h"

int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2) == 0) return 1;
    return 0;
}

void ImprimirMenu(){
    printf("opcion 1. Cargar Documentos\n");
    printf("opcion 2. Mostrar Documentos ordenados\n");
    printf("opcion 3. Buscar libro por titulo\n");
    printf("opcion 4. Buscar palabras con mayor frecuencia de un libro\n");
    printf("opcion 5. Buscar palabras mas relevantes de un libro\n");
    printf("opcion 6. Buscar por palabra los libros\n");
    printf("opcion 7. Mostrar contexto de la palabra\n");
}

void cargarDocumento(Libreria *lib, Map *mapBooks)
{
    char archivo[1024];

    char *nomArch = (char *) malloc(sizeof(char));
    FILE *file;

    while(file == NULL)
    {
        printf("Ingresar nombre archivo: ");
        scanf("%s", &archivo);
        strcpy(nomArch, archivo);
        strcat(archivo, ".txt");
        file = fopen(archivo, "r");
    }

    Pair *doc = searchTreeMap(mapBooks, nomArch);
    if(doc != NULL)
    {
        fclose(file);
        cargarDocumento(lib, mapBooks);
    }
    else
    {
        (lib->totalLibros)++;
    }
}

char *quitar_caracteres(char* string, char* c){
    int i;
    int j;
    for(i = 0; i < strlen(string); i++){
        if(hayQueEliminar(string[i], c)){
            for(j = i; j < strlen(string) - 1; j++){
                string[j] = string[j+1];
        }
        string[j] = '\0';
        i--;
    }
}

    return string;
}

int hayQueEliminar(char c, char* string_chars){
    for(int i = 0; i < strlen(string_chars); i++){
        if(string_chars[i] == c) return 1;
    }
    return 0;
}

void BuscarPorPalabra(Map *mapBooks){
  printf("Ingrese la palabra que desea buscar: ");
  char *palabraBuscada = (char*)malloc(50 * sizeof(char));
  getchar();
  scanf("%s", palabraBuscada);
  char *aux = searchMap(mapBooks, palabraBuscada);
  if(aux != NULL){
    if(strcmp(palabraBuscada, aux) == 0){
        imprimirInfo(aux);
        return;
    }
    aux = nextMap(mapBooks);
  }
}




















