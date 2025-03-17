# gpgpu-p1

Practico 1 - Patrones de acceso a memoria - GPGPU

Uso de ChatGPT e IA Generativa:
En este practico se permite el uso de estas herramientas para:
• Generar el codigo del ejercicio 1.
• Generar graficas y tablas a partir de los resultados, corregir ortografıa y redaccion, etc.
• Generar scripts que automaticen las pruebas a realizar.
NO se permite el uso de estas herramientas para:
• Generar el codigo del ejercicio 2.
• Generar una interpretacion de los resultados.

El objetivo de este practico es reflexionar sobre la jerarquıa de memoria, en especial la memoria principal
y los distintos niveles de cache, y sobre como distintos patrones de acceso a los datos hacen un uso distinto
de dicha jerarquıa. En los siguientes ejercicios se accedera a una estructura de datos realizando la misma
cantidad de operaciones, aunque en distinto orden. Para que los tiempos de ejecucion sean lo mas estables
posible se recomienda ejecutar en un sistema con poca carga, medir tiempos lo suficientemente grandes
(adaptando el tamaño de la entrada o la cantidad de repeticiones de las pruebas), y evitar la utilizacion de
maquinas virtuales.


## Ejercicio 1 Localidad espacial

1. Escriba un programa en C/C++ que reserve e inicialice un arreglo de char de gran tamaño (por
ejemplo 100MB). A continuacion el programa debe recorrer el arreglo (por ejemplo incrementando el
valor de cada posicion) de manera secuencial (primero la posicion 0, luego la 1, y ası sucesivamente).
Durante la recorrida, el siguiente ındice a visitar debe leerse de un arreglo inicializado previamente.
Registre el tiempo de ejecucion de la recorrida.  

2. Realice otra recorrida por el arreglo que visite la misma cantidad de elementos pero realizando saltos
aleatorios. Durante la recorrida, el siguiente ındice a visitar debe leerse de un arreglo inicializado
previamente. Mida el tiempo de ejecucion y reflexione sobre los resultados.
Ejercicio 2 Localidad temporal
Considere la siguiente funcion para multiplicar una matriz A por un vector B de gran tamaño:  

void matrix_mult ( float **A , float *B , float *C , size_t size ) {  
    for ( size_t i = 0; i < size ; i ++) C [i] = 0;  
    for ( size_t i = 0; i < size ; i ++)  
    for ( size_t j = 0; j < size ; j ++)  
    C[i ] += A [i ][ j ] * B[ j ];  
}  

Tal como esta el codigo, por cada fila de A se recorre todo el vector B. Si la matriz es suficientemente
grande, al pasar a la siguiente fila de A, los primeros elementos de B ya no se encuentran en la cache. Note
que cada elemento de A se accede solamente 1 vez (no es posible explotar la localidad temporal) pero cada
elemento de B se accede size veces.
Si se modifica el codigo de la siguiente forma:  

void matrix_mult ( float **A , float *B , float *C , size_t size ) {  
    for ( size_t i = 0; i < size ; i ++) C [i] = 0;  
    for ( size_t jj = 0; jj < size ; jj += TAM_BL )  
    for ( size_t i = 0; i < size ; i ++)  
    for ( size_t j = jj ; j < jj + TAM_BL ; j ++)  
    C[i ] += A [i ][ j ] * B[ j ];  
}  

se realizan todos los productos correspondientes a un pequeño bloque de B (de tamaño TAM BL) antes de
pasar al siguiente bloque, por lo que al cambiar de fila en A los elementos de B no deberıan haber sido
reemplazados en la cache.  

1. Escriba una funcion para el producto de matrices extendiendo la funcion anterior (ahora B y C tendran
size columnas). Mida el desempe˜no en MFLOPS1 para valores de size de distinto orden (comparables
al tamaño de los distintos niveles cache).  

2. Aplique la tecnica descrita para el producto matriz-vector al producto de matrices, explotando la
localidad temporal tanto en A como en B. Compare los tiempos de ejecucion y desempe˜no en MFLOPS
de ambas versiones para distintos tamaños de matriz y bloque. Reflexione acerca de los resultados.  

Entrega  
• Se debe entregar un informe en PDF con la solucion de los ejercicios que contenga, como maximo, 4
paginas.  
• No se entrega el codigo fuente.  
• Las secciones relevantes del codigo deben figurar en el informe.  
