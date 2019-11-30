/*
 * AUTORES: Ane Zubillaga, Ian Recke, Ivan Sorbet, Alejandro Meza
 */

#include <stdio.h>
#include <stdlib.h>
#include "fragmenta.h"
#include <sys/errno.h>
#include <wchar.h>
#include <math.h>
#include <unistd.h>
#define clear() printf("\n")


typedef struct datos{
	float ir;
	float na;
	float mg;
	float al;
	float si;
	float k;
	float ca;
	float va;
	float fe;
	int tipo;
}Datos;

typedef struct tablaentropia{
	double entr;
	int pos;
}Tablaentropia;

void quicksort(Datos cadena[], int izq, int der, float determinante[]);

void start_arbol_decision(){
	clear();
	printf("\033[1;31m");
	printf("\n\n\n\n******************""************************");
	printf("\n\n\n\t****ARBOL DE DECISION****");
	printf("\n\n\n\n******************""************************");
	char *name = getenv("USER");
	printf("\n\n\n\tUSUARIO ES: @%s", name);
	printf("\033[0m");
	printf("\n");
	sleep(1);
	clear();
}
/*Tablaentropia entropia(int tipo[], int longitud)
{
	Tablaentropia t[longitud];
	int i = 0, postabla = 0;
	int veces3 = 4; */
	/*while (i < longitud)
	{
		if (datos[i].tipo != datos[i+1].tipo)
		{
			//Calcular entropia.
			//double entrizq = entropiaizquierda(tabla, i, longitud);
			//double entrdech = entropiaderecha(tabla, i, longitud);
			//t[postabla].entr =(i/longitud) entrizq + (longitud-i/longitud) entrdech;
			//t[postabla].pos = i;
		}
		i++;
	}	
		}
	}*/
/*	return t;
} */

int main(void)
{
	start_arbol_decision;
	FILE *f;
	char dats[400];
    int r;
	char inutil[100];
	f = fopen("problem_glass.csv", "r+");
	fgets(inutil, 100, f); //lee los valores que no van a servir de la primera fila
	int j = 0;
	Datos datos[300]; //vector de tipo datos-->cada elemento, contiene un valor de todos los campos
	while (!feof(f)) //mientras no se acabe el fichero
	{
		fgets(dats, 400, f);
        if(feof(f))//si cuando lee el fgets es nulo, es decir es fin de fichero, da error y entra aqui, porque es feof y sale del buccle.
            break;
		char **frasefragmentada = fragmenta(dats); //dats contiene la linea
		datos[j].ir = atof(frasefragmentada[0]);
		datos[j].na = atof(frasefragmentada[1]);
		datos[j].mg = atof(frasefragmentada[2]);
		datos[j].al = atof(frasefragmentada[3]);
		datos[j].si = atof(frasefragmentada[4]);
		datos[j].k = atof(frasefragmentada[5]);
		datos[j].ca = atof(frasefragmentada[6]);
		datos[j].va = atof(frasefragmentada[7]);
		datos[j].fe = atof(frasefragmentada[8]);
		datos[j].tipo = atoi(frasefragmentada[9]);
		j++;
	}
	int tipo[j];
	for (int i=0; i<j; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	float ir[j];
	for (int i=0; i<j; i++)
	{
		ir[i] = datos[i].ir;
	}	
	quicksort(datos, 0, j-1, ir);
	//ENTROPIA
	/////////
	float na[j];
	for (int i=0; i<j; i++)
	{
		na[i] = datos[i].na;
	}
	quicksort(datos, 0, j-1, na);
	//ENTROPIA
	/////
	/*for (int i=0; i<j; i++)
	{
		printf("%f\n", datos[i].na);
	}*/
	float mg[j];
	for(int i =0; i<j; i++){
		mg[j]=datos[i].mg;
	}
	quicksort(datos,0, j-1, mg);
	//ENTROPIA
	/////////////////// 
	float al[j];
	for(int i =0; i<j; i++){
		al[j] = datos[i].al;
	}
	quicksort(datos,0, j-1, al);
	//ENTROPIA
	///////////////////// 
    float si[j];
    for(int i=0; i<j; i++){
		si[j]=datos[i].si;
	}
	quicksort(datos,0, j-1, si);
	//ENTROPIA
	/////////////////////
	float k[j];
	for(int i=0; i<j; i++){
		k[j] = datos[i].k;
	}
	quicksort(datos,0, j-1, k);
	//ENTROPIA
	float ca[j];
	for(int i =0; i<j; i++){
		ca[j] = datos[i].ca;
	}
	quicksort(datos,0, j-1, ca);
	//ENTROPIA
	float va[j];
	for(int i=0; i<j; i++){
		va[j]= datos[i].va;
	}
	quicksort(datos,0, j-1, va);
	//ENTROPIA
	float fe[j];
	for(int i=0; i<j; i++){
		fe[j] = datos[i].fe;
	}
	quicksort(datos,0, j-1, fe);
	//ENTROPIA
	//Tablaentropia t = entropia(tipo, j-1);
	fclose(f);
	return 0;
}

void quicksort(Datos cadena[], int izq, int der, float determinante[])
{
  int i=izq;
  int d=der;
  float centro=determinante[(i+d)/2];
  do {
    while (determinante[i]<centro && i<der)
    {
      i++;
    }
    while (centro<determinante[d] && d>izq)
    {
      d--;
    }
    if (i<=d)
    {
      Datos aux=cadena[i];
      cadena[i]=cadena[d];
      cadena[d]=aux;
      float auxi=determinante[i];
      determinante[i] = determinante[d];
      determinante[d] = auxi;
      i++;
      d--;
    }
  } while(i<=d);
  if (izq < d)
  {
    quicksort(cadena, izq, d, determinante);
  }
  if(der > i)
  {
    quicksort(cadena, i, der, determinante);
  }
}
