#ifndef defFunciones_h
#define defFunciones_h 
#include "list.h"
#include "Map.h"
#include "TreeMap.h"

typedef struct Libreria{
    TreeMap *libros;
    size_t totalLibros;
} Libreria;

typedef struct Libros{
    char titulo[100];
    char id[100];
    Map *nomTitulo;
    Map *palLibro;
} Libros;

typedef struct Palabra{
    char palabra[100];
    size_t ocurrencia;
    size_t frecuencia;
} Palabra;

void cargarDocumento(Libreria *librero, Map *mapBooks);
int is_equal_string(void * key1, void * key2);
void BuscarPorPalabra(Map *mapBooks);
char *quitar_caracteres(char* string, char* c);
int hayQueEliminar(char c, char* string_chars);

#endif