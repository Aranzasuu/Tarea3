#ifndef defFunciones_h
#define defFunciones_h 
#include "list.h"
#include "Map.h"
#include "TreeMap.h"

typedef struct Libreria{
    List *libros;
    size_t totalLibros;
} Libreria;

typedef struct Libros{
    char titulo[100];
    char id[100];
    TreeMap *nomTitulo;
    TreeMap *palLibro;
    size_t totalPalabras;
} Libros;

typedef struct Palabra{
    char palabra[100];
    size_t ocurrencia;
    size_t frecuencia;
} Palabra;

int is_equal_string(void * key1, void * key2);
int lower_than_string(void* key1, void* key2);

Libreria *crearLibreria();
Libros *crearLibro();

void Menu();
void impresion();
void cargarDocumento(Libreria *librero);
void BuscarPorPalabra(Map *mapBooks);
char *quitar_caracteres(char* string, char* c);
int hayQueEliminar(char c, char* string_chars);

#endif