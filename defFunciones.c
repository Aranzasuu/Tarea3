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

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}

Libreria *crearLibreria(){
    Libreria *Librero = (Libreria *) malloc(sizeof(Libreria));
    if(Librero == NULL){
        printf("No se pudo reservar memoria para la variable :c\n");
        return NULL;
    }
    Librero->libros = createTreeMap(lower_than_string);
    Librero->totalLibros = 0;
    return Librero;
}

Libros *crearLibro(){
    Libros *libro = (Libros *) malloc(sizeof(Libros));

    if(libro == NULL){
        printf("No se pudo reservar memoria para la variable :c\n");
        return NULL;
    }

    libro->nomTitulo = createTreeMap(lower_than_string);
    libro->palLibro = createTreeMap(lower_than_string);
    libro->totalPalabras = 0;

    return libro;
}

void Menu(){

    Libreria *librero = crearLibreria();
    int opcion;

    impresion();
    printf("Ingrese una opcion valida entre el 0 - 7\n\n-> ");
    scanf("%d", &opcion);
    printf("\n");

    while(opcion != 0){
        switch(opcion){
            case 1:
                cargarDocumento(librero);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                printf("Ingrese una opcion valida\n-> ");
                scanf("%d", &opcion);
        }

        printf("\n\nDesea realizar otra operacion?\n");
        printf("NO -> ingrese 0\n");
        printf("SI -> ingrese el numero de la operacion a realizar\n\n");
        scanf("%d", &opcion);
        if(opcion == 0) break;
        impresion();
    }
}


// FUNCIÓN OPCIÓN 1 

void cargarDocumento(Libreria *lib)
{
    FILE *archivo;
    char espacio[2] = " ";
    char documento[500];

    printf("Ingrese los nombres de los archivos que desea cargar, debe separarlos por espacios y escribirlos con .txt\n");
    //fgets(documento, 500, stdin);   

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
        //imprimirInfo(aux);
        return;
    }
    aux = nextMap(mapBooks);
  }
}

void impresion(){

    printf("\n\n\n *************** MENU ***************\n\n");
    printf("    1. Cargar Documentos\n");
    printf("    2. Mostrar Documentos\n");
    printf("    3. Buscar libro por titulo\n");
    printf("    4. Palabras frecuentes libro\n");
    printf("    5. Palabras mas relevantes\n");
    printf("    6. Buscar por palabra\n");
    printf("    7. Buscar contexto de palabra\n");
    printf("    0. Salir\n");
    printf("---------------------------------------\n\n");
}




















