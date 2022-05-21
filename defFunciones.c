#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "list.h"
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
    Librero->nomTitulo = createMap(is_equal_string);
    Librero->totalLibros = 0;
    return Librero;
}

Libro *crearLibro(){
    Libro *libro = (Libro *) malloc(sizeof(Libro));

    if(libro == NULL){
        printf("No se pudo reservar memoria para la variable :c\n");
        return NULL;
    }

    libro->palLibro = createMap(is_equal_string);
    setSortFunction(libro->palLibro, lower_than_string);
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
                MostrarDocumentos(librero);
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

        impresion();
        printf("\n\nDesea realizar otra operacion?\n");
        printf("NO -> ingrese 0\n");
        printf("SI -> ingrese el numero de la operacion a realizar\n\n");
        scanf("%d", &opcion);
        if(opcion == 0) break;
    }
}

char* removedor(char* text, const char* subText)
{
    size_t len = strlen(subText);
    if (len > 0)
    {
        char* p = text;
        while ((p = strstr(p, subText)) != NULL)
        {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return text;
}

// FUNCIÓN OPCIÓN 1 

void cargarDocumento(Libreria *lib)
{
    char documento[500];

    printf("Ingrese los nombres de los archivos que desea cargar, debe separarlos por espacios y escribirlos sin .txt\n");
    getchar();
    fgets(documento, 500, stdin);
    documento[strcspn(documento, "\n")] = 0;
    fflush(stdin);

    List* documentos = createList();
    char* documentoActual = strtok(documento, " ");
    while (documentoActual != NULL)
    {
        pushBack(documentos, documentoActual);
        documentoActual = strtok(NULL, " ");
    }

    //11
    char* aux = firstList(documentos);
    while (aux != NULL){
        char* nombreArchivo = (char*)malloc(strlen(aux) + 1);
        size_t contador = 0;
        strcpy(nombreArchivo, aux);
        strcat(nombreArchivo, ".txt");
        FILE* archivo = fopen(nombreArchivo, "r");
        free(nombreArchivo);

        if(archivo == NULL){
            printf("No se pudo abrir archivo %s\n", nombreArchivo);
            continue;
        }

        Libro* libro = crearLibro();
        strcpy(libro->id, aux);

        char* linea = (char*)malloc(sizeof(char) * 1024);
        fgets(linea, 1024, archivo);
        linea = linea + 3;
        linea[strcspn(linea, "\n")] = 0;
        strcpy(libro->titulo, removedor(linea, "The Project Gutenberg eBook of "));

        while(fgets(linea, 1024, archivo) != NULL)
        {
            linea[strcspn(linea, "\n")] = 0;

            char* p = strtok(linea, " ");
            while (p != NULL)
            {
                for (int i = 0; p[i]; i++)
                {
                    p[i] = tolower(p[i]);
                }

                p = filtro(p);
                contador += contCaract(p);

                Palabra* pal = searchMap(libro->palLibro, p);

                if (pal == NULL)
                {
                    pal = (Palabra*)malloc(sizeof(Palabra));
                    pal->ocurrencia = 1;
                    pal->frecuencia = 0;
                    strcpy(pal->palabra, p);
                    insertMap(libro->palLibro, pal->palabra, pal);
                }
                else
                {
                    pal->ocurrencia++;
                }

                p = strtok(NULL, " ");
                libro->totalPalabras++;
                libro->totalCaracteres = contador;
                //nextTreeMap(libro->palLibro)->value;
            }
        }

        aux = nextList(documentos);
        fclose(archivo);

        //Pair* pair = firstMap(libro->palLibro);
        Palabra* pal = firstMap(libro->palLibro);
        while (pal != NULL)
        {
            //Palabra* pal = (Palabra*) pair->value;
            //cantidad de veces que aparece una palabra dividida por el total de palabras en el libro.
            pal->frecuencia = (float)pal->ocurrencia / libro->totalPalabras;
            pal = nextMap(libro->palLibro);
        }

        insertMap(lib->nomTitulo, libro->titulo, libro);
    }

    //Libro* libro = firstMap(lib->nomTitulo);
    /*while (libro != NULL)
    {
        printf("Titulo: %s\n", libro->titulo);
        printf("ID: %s\n", libro->id);
        printf("Total Palabras: %d\n", libro->totalPalabras);
        Palabra* aux = searchMap(libro->palLibro, "ola");
        if (aux == NULL)
        {
            printf("ERROR\n");
        }
        else
        {
            printf("Palabra: %s\n", aux->palabra);
            printf("Ocurrencia: %i\n", aux->ocurrencia);
            printf("Frecuencia: %.2f\n", aux->frecuencia);
        }
        printf("Total caracteres: %zd\n\n\n", libro->totalCaracteres);
        libro = nextMap(lib->nomTitulo);
    }*/
}

// FUNCIÓN OPCIÓN 2
void MostrarDocumentos(Libreria *lib){
    Libro* libro = firstMap(lib->nomTitulo);
    while (libro != NULL)
    {
        printf("Titulo: %s\n", libro->titulo);
        printf("ID: %s\n", libro->id);
        printf("Total Palabras: %d\n", libro->totalPalabras);
        printf("Total caracteres: %zd\n\n\n", libro->totalCaracteres);
        libro = nextMap(lib->nomTitulo);
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
        //imprimirInfo(aux);
        return;
    }
    aux = nextMap(mapBooks);
  }
}

char *filtro(char *str)
{
    int i,j;

    for (i = 0; str[i] != '\0'; ++i) 
    {
        while (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9') && !(str[i] == '\0')) 
        {
            for (j = i; str[j] != '\0'; ++j)
            {
                str[j] = str[j + 1];
            }
            str[j] = '\0';
        }
    }

    return str;
}

size_t contCaract(char *palabra){
    size_t largo = strlen(palabra);
    size_t cont = 0;
    for(int i = 0; i < largo; i++){
        cont++;
    }
    return cont;
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




















