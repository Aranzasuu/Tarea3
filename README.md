# Tarea3
Estructuras:
1.-Libreria: tenemos mapTitulos: dentro de este mapa tenemos los libros ordenados, con su respectiva informacion. Size_t totalLibros: almacena la cantidad de libros cargados.

2.-Libro: en esta estructura tenemos titulo: el cual almacena el titulo del libro con una maximo de caracteres. id: en este guardamos el id del documento cargado. Map *palLibro: mapa el cual posee todas las palabras que existen en el libro, su key seria el id del libro y el value las palabras.
Size_t totalPalabras: almacena la cantidad de palabras que tiene el libro.
Size_t totalCaracteres: almacena la cantidad de caracteres que posee.

3.-Palabra: palabra:almacena la palabra. size_t ocurrencia: almacena el numero de la cantidad de veces que aparece esa palabra en el texto. float frecuencia: es la ocurrencia dividido en la cantidad total de palabras.

Instrucciones para correr el programa:

->Primero debemos abrir el terminal donde debemos escribir gcc *.c -o Tarea3 luego debemos poner ./Tarea3.exe para ejecutar el programa.
- Se nos motrara el menu y seleccionamos la primera que es cargar los documentos; esta opcion llama a la funcion:
- cargarDocumento():Esta funcion recibe como parametro la libreria, ingresamos los nombres de los archivos, los guardamos una linea despues de esto se crea lista de los documentos los cuales vamos separando cada id cortando los espacios,cada espacio significa que viene otro id, despues vamos guardando la indo en cada struct.
  
->Segunda opcion:
- MostrarDocumentos():Recibe como parametro la libreria, ingresamos al mapa titulos el cual tiene la info de los libros y luego vamos imprimiendo la informacion respectiva de cada libro.

->Tercera opcion:
- BuscarPorTitulo():

->Cuarta opcion:
- Mayorfrecuencia():Recibe como parametro la libreria, ingresas el id del libro y muestra las 10 palabras que se repiten con mayor frecuencia de mayor a menor. La frecuencia la sacamos con la cantidad de veces que aparece la palabra dividido la cantidad total de palabras en el libro.

->Quinta opcion:
- mayorRelevancia():Calcula la relevancia que tiene cada palabra, e imprime las palabras en orden (hay una parte que no funciona, por lo que la función no funciona).

->Sexta opcion
- BuscarPorPalabra():Recibe como parametro la libreria, ingresamos la palabra a buscar y vemos en que libros esta aquella palabra, buscamos la palabra dentro de un while que la busca dentro del mapa de palabras del libro si la encuentra dentro del libro, imprime el titulo y la id del libro.Si no se encuentra se imprime que no se encuentra la palabra.

->Septima opcion:
-Buscarpalabracontx(): Se ingresa el titulo que se desea buscar la palabra y luego la palabra, abrimos el archivo del titulo buscado y luego obtenemos la linea en la cual este la palabra, en este punto nos falto encontrar la posicion de la palabra para asi poder imprimir las 5 palabras anteriores y las 5 posteriores.

Comentarios:
El programa solo puede correr en windows 11, no aparece que todos hicimos cambios ya que hicimos las funciones que nos correspondian y se las pasamos a aranzasu para que ella las pegara en el codigo, por lo tanto no aparecen commits de los demas.