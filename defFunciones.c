#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
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
    setSortFunction(Librero->nomTitulo, lower_than_string);
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
                BuscarPorTitulo(librero);
                break;
            case 4:
                MayorFrecuencia(librero);
                break;
            case 5:
                MostrarRelevantes(librero);
                break;
            case 6:
                BuscarPorPalabra(librero);
                break;
            case 7:
                //MostrarPalabracontx(librero);
                break;
            default:
                printf("Ingrese una opcion valida\n-> ");
                scanf("%d", &opcion);
        }

        impresion();
        printf("\nDesea realizar otra operacion?\n");
        printf("NO -> ingrese 0\n");
        printf("SI -> ingrese el numero de la operacion a realizar\n\ningrese su opcion: ");
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
        const char s[2] = ",";
        char *token;
        if(strtok(libro->titulo, s) == NULL) continue;
        else
        {
            token = (strtok(libro->titulo, s));
            strcpy(libro->titulo, token);
        }
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
            }
        }

        aux = nextList(documentos);
        lib->totalLibros++;
        fclose(archivo);

        Palabra* pal = firstMap(libro->palLibro);
        while (pal != NULL)
        {
            pal->frecuencia = (float)pal->ocurrencia / libro->totalPalabras;
            pal = nextMap(libro->palLibro);
        }

        insertMap(lib->nomTitulo, libro->titulo, libro);
    }
    printf("\n\n*** Se han cargado %zd documento(s) correctamente ***\n", lib->totalLibros);
}

// FUNCIÓN OPCIÓN 2

void MostrarDocumentos(Libreria *lib){
    Libro* libro = firstMap(lib->nomTitulo);
    size_t cont = 1;
    
    while (libro != NULL)
    {
        printf("\nInformacion documento %zd:", cont);
        printf("\n-------------------------\n\n");
        printf(" > Titulo: %s\n", libro->titulo);
        printf(" > ID: %s\n", libro->id);
        printf(" > Total Palabras: %d\n", libro->totalPalabras);
        printf(" > Total Caracteres: %zd\n", libro->totalCaracteres);
        libro = nextMap(lib->nomTitulo);
        cont++;
    }
    printf("\n-------------------------\n");
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

void mayorFrec(List *palabras, int cont){
    Palabra *aux = firstList(palabras);
    Palabra *mayorFrec = aux;
    while(aux != NULL){
        if(aux->frecuencia > mayorFrec->frecuencia)
            mayorFrec = aux;
        aux = nextList(palabras);
    }
    printf("%d. Palabra: %s\n   Frecuencia: %f\n\n", cont+1, mayorFrec->palabra, mayorFrec->frecuencia);
    Palabra *eliminar = firstList(palabras);
    while(eliminar != NULL){
        if(eliminar->frecuencia == mayorFrec->frecuencia){
            popCurrent(palabras);
            return;
        }
        eliminar = nextList(palabras);
    }
}

// FUNCIÓN OPCIÓN 4

void MayorFrecuencia(Libreria *librero){
    char identity[100];
    printf("Ingrese el id del libro a buscar: ");
    getchar();
    scanf("%[^\n]s", identity);
    printf("\n");

    Libro *lib = firstMap(librero->nomTitulo);
    List *aux = createList();
    while(lib != NULL){
        if(strcmp(lib->id,identity) == 0){
            Palabra *pal = firstMap(lib->palLibro);
            while(pal != NULL){
                pushBack(aux,pal);
                pal = nextMap(lib->palLibro);
            }
            for(int i = 0; i < 10; i++){
                mayorFrec(aux, i);
            }
            return;
        }
        lib = nextMap(librero->nomTitulo);
    }
}

void mayorRelevancia(List *palabras, int cont){
    Palabra *aux = firstList(palabras);
    Palabra *mayorRel = aux;
    while(aux != NULL){
        if(aux->relevancia > mayorRel->relevancia)
            mayorRel = aux;
        printf("relevancia: %zd\n", aux->relevancia);
        aux = nextList(palabras);
    }
    printf("%d. Titulo: %s\n   Relevancia: %f\n\n", cont+1, mayorRel->palabra, mayorRel->relevancia);
    Palabra *eliminar = firstList(palabras);
    while(eliminar != NULL){
        if(eliminar->relevancia == mayorRel->relevancia){
            popCurrent(palabras);
            return;
        }
        eliminar = nextList(palabras);
    }
}


// FUNCIÓN OPCIÓN 5
void MostrarRelevantes(Libreria *librero){
    size_t docPal = 0;
    List *listRel = createList();
    char title[100];
    printf("Ingrese el titulo del libro: ");
    getchar();
    scanf("%[^\n]s", title);
    printf("\n");

    Libro *libBuscado = firstMap(librero->nomTitulo);
    while(libBuscado != NULL){
        if(strcmp(libBuscado->titulo, title) == 0){
            Palabra *pal = firstMap(libBuscado->palLibro);
            while(pal != NULL){
                float relevan = calcularRelevancia(librero, pal);
                pal->relevancia = relevan;
                pal = nextMap(libBuscado->palLibro);
                
            }
            pushBack(listRel,pal);
        }
        libBuscado = nextMap(librero->nomTitulo);
    }

    //for(int i = 0; i < 10;i++) mayorRelevancia(listRel,i);
    
}

size_t calcularRelevancia(Libreria *librero, Palabra *pal){
    size_t contDoc = 0;
    float rel = 0;

    // calcular en cuantos documentos está la palabra
    Libro *lib = firstMap(librero->nomTitulo);
    while(lib != NULL){
        Palabra *pala = firstMap(lib->palLibro);
        while(pala != NULL){
            if(strcmp(pala->palabra,pal->palabra) == 0){
                contDoc++;
            }
            pala = nextMap(lib->palLibro);
        }
        lib = nextMap(librero->nomTitulo);
    }

    rel = (pal->frecuencia) * (librero->totalLibros/contDoc);
    return rel;

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
    for(int i = 0; i < largo; i++)
        cont++;
    return cont;
}

int pal_in_list(List *palabras, char *title)
{
    char *pal = firstList(palabras);
    char *aux = strtok(title, " ");
    while(pal != NULL){
        if (strcmp(aux, pal) != 0) return 1;
        pal = (NULL, " ");
    }
    
    return 0;
}

void BuscarPorTitulo(Libreria *lib){
    char linea[100];
    printf("Ingrese las palabras: ");
    getchar();
    fgets(linea,1024,stdin);
    linea[strcspn(linea, "\n")] = 0;
    fflush(stdin);

    printf("linea = %s\n",linea);
    List *palabras = createList();
    char *pal = strtok(linea, " ");

    while(pal != NULL){
        if(pal != NULL){
            pushBack(palabras, pal);
            char *pal = strtok(NULL, " ");
        }
    }
    List *libPal = createList();
    Libro *libro = firstMap(lib->nomTitulo);
    char *aux = firstList(palabras);

    while(libro != NULL){
        if(pal_in_list(palabras, libro->titulo) == 0){
            pushBack(libPal,libro->titulo);
        }
        libro = nextMap(lib->nomTitulo);
    }

    char *title = firstList(libPal);
    if(title == NULL){
        printf("\n  No se encontraron titulos relacionados\n");
    }
    else{
        printf("\n  Se encontraron los siguientes titulos relacionados: ");
        while(title != NULL){
            printf("-> %s\n",title);
            title = nextList(libPal);
        }
    }
}

/*
void BuscarPorTitulo(Libreria *lib)
{
    char titulo[100];
    printf("Ingrese titulo : "); // o mas bien palabra/s que pertenezca/n a uno o mas titulos
    getchar();
    fgets(titulo, 200, stdin);
    titulo[strcspn(titulo, "\n")] = 0;
    fflush(stdin);

    List *list_pal = createList(); // se crea una lista con las palabras
    char *pal = strtok(titulo, " ");
    while (pal != NULL)
    {
        pushBack(list_pal, pal);
        pal = strtok(NULL, " ");
    }
    Libro *libro = firstMap(lib->nomTitulo); // se crea una lista con las
    int cont = 0;                            // palabra de el titulo

    while (libro != NULL)
    {
        int flag = 1;
        // comparar palabras
        List *list_ti = createList();
        char *aux = strtok(libro->titulo, " ");
        while (aux != NULL)
        {
            pushBack(list_ti, aux);
            aux = strtok(NULL, " ");
        }
        pal = firstList(list_pal);
        while (pal != NULL) // comparamos las dos listas
        {
            if (pal_in_list(pal, list_ti) == 0)
            {
                flag = 0;
                break;
            }
            pal = nextList(list_pal);
        }
        if (flag == 1 && cont == 0)
        {
            printf("\n  Se encontraron los siguientes titulos relacionados : ");
            cont = 1;
        }
        if (flag == 1)
        {
            printf("\n ~ %s", libro->titulo);
        }

        lib = nextMap(lib->nomTitulo);
    }
    if (cont == 0)
    {
        printf("\n  No se encontraron titulos relacionados\n");
    }
}
*/

void BuscarPorPalabra(Libreria *books){    
    printf("Ingrese la palabra que desea buscar: ");
    char *palabraBuscada = (char *)malloc(50 * sizeof(char));
    getchar();
    scanf("%[^\n]s", palabraBuscada);
    Libro *aux = firstMap(books->nomTitulo);
    
    while(aux != NULL){
        Palabra *pal = (Palabra*) searchMap(aux->palLibro, palabraBuscada);
        if(pal != NULL){
            printf("Titulo: %s\n", aux->titulo);
            printf("ID: %s\n\n", aux->id); 
        }
        else{
            printf("No se encontro la palabra buscada\n");
        }
        aux = nextMap(books->nomTitulo);
    }
}

/*
void MostrarPalabracontx(Libreria *books){
    printf("Ingrese el titulo del libro: ");
    char *titulo = (char*)malloc(50 * sizeof(char));
    getchar();
    scanf("%s", titulo);
    printf("Ingrese la palabra que desea buscar: ");
    char *palabraBuscada = (char*)malloc(50 * sizeof(char));
    getchar();
    scanf("%s", palabraBuscada);
    Pair *lib = searchMap(books->nomTitulo, titulo);
    Libro *text = lib->value;
    char linea[1024];
    FILE *txt;
    strcat(titulo,".txt");
    txt = fopen(titulo, "r");
    Pair *pala = searchMap(text->palLibro, palabraBuscada);
    if(lib != NULL){
        if(pala!=NULL){
            while(fgets(linea, 1024, txt)!=NULL){
                Palabra *word = pala->value;
                //ftell(txt);
            }
        }
        else{
            printf("La palabra no se encuentra en el libro");
        }
    }
    else{
        printf("El libro que busca no se encuentra\n");
        return;
    }
}*/

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