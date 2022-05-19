#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "Map.h"
#include "TreeMap.h"
#include "defFunciones.h"

int main(){

    Libreria *librero;
    Map *mapBooks = createMap(is_equal_string);
    cargarDocumento(librero, mapBooks);
    
    return 0;
}