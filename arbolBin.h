#include <stdbool.h>

typedef struct TipoElementoArbolBin
{
    int elemento;
    float umbral;
    double entropia;
}tipoElementoArbolBin;

typedef struct celdaABin{
	 tipoElementoArbolBin elem;
	 struct celdaABin *izda;
	 struct celdaABin *dcha;
 }celdaArbolBin; 
typedef celdaArbolBin *tipoArbolBin;

void nuevoArbolBin(tipoArbolBin *); //

void errorArbolBin(char s[]); // 

tipoArbolBin construir(tipoElementoArbolBin, tipoArbolBin, tipoArbolBin );

tipoElementoArbolBin devolverRaiz(tipoArbolBin);//

bool esVacio(tipoArbolBin); //
