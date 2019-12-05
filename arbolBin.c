/*Programa realizado por Alejandro Meza
 * Fecha: 1/10/2019
 * El programa se encarga de la implementacion de un arBin
 */
 
 #include "arbolBin.h"
 #include <stdio.h>
 #include <stdlib.h>
 
 void nuevoArbolBin(tipoArbolBin *a){
	 *a = NULL;
} 

void errorArbolBin(char s[]){
	printf("\n\n Error en arbol binario: %s \n", s);
}

tipoArbolBin construir(tipoElementoArbolBin elemento, tipoArbolBin i, tipoArbolBin d){
	tipoArbolBin nuevo;
	nuevo = (celdaArbolBin*)malloc(sizeof(celdaArbolBin)); 
	nuevo->elem = elemento; 
	nuevo->izda = i; //puntero izquierda de nuevo apunta a lo mismo que apunta i, 
	//puntero a celda arbol bin
	nuevo->dcha = d; //puntero derecha de nuevo a paunta a lo mismo que apunta d, 
	//puntero a celda de arbol bin
	return (nuevo); 
}

tipoElementoArbolBin devolverRaiz(tipoArbolBin a){
	if (esVacio(a)){
		errorArbolBin("El arbol es vacio"); 
	}
	return (a->elem); 
}	 
 
bool esVacio(tipoArbolBin a){
	return a == NULL; 
}
	

		 
