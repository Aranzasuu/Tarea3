#ifndef defFunciones_h
#define defFunciones_h 
#include "list.h"
#include "Map.h"
#include "TreeMap.h"

typedef struct Libreria{
    Map *nomTitulo;
    size_t totalLibros;
} Libreria;

typedef struct Libros{
    char titulo[100];
    char id[100];
    Map *palLibro;
    size_t totalPalabras;
    size_t totalCaracteres;
} Libro;

typedef struct Palabra{
    char palabra[100];
    size_t ocurrencia;
    float frecuencia;
    float relevancia;
} Palabra;

int is_equal_string(void * key1, void * key2);
int lower_than_string(void* key1, void* key2);

Libreria *crearLibreria();
Libro *crearLibro();

void Menu();
void impresion();
void cargarDocumento(Libreria *librero);
void MostrarDocumentos(Libreria *librero);
void BuscarPorPalabra(Libreria *books);
void MayorFrecuencia(Libreria *librero);
/*void MostrarPalabracontx(Libreria *librero);*/
void BuscarPorTitulo(Libreria *lib);
void MostrarRelevantes(Libreria *librero);

char* removedor(char* text, const char* subText);
char *quitar_caracteres(char* string, char* c);
int hayQueEliminar(char c, char* string_chars);
char *filtro(char *p);
size_t contCaract(char *p);
int pal_in_list(List *palabras, char *title);
void mayorFrec(List *palabras, int contador);
size_t calcularRelevancia(Libreria *librero, Palabra *pal);

#endif