#include <stdio.h>
#include <stdlib.h>
#include "fragmenta.h"
#include <sys/errno.h>
#include <wchar.h>
#include <math.h>

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

int main(void)
{
	FILE *f;
	
	char dats[400];
    int r;
	char inutil[100];
	f = fopen("problem_glass.csv", "r+");
	fgets(inutil, 100, f);
	int j = 0;
	Datos datos[300];
	while (!feof(f))
	{
		fgets(dats, 400, f);
        if(feof(f))//si cuando lee el fgets es nulo, es decir es fin de fichero, da error y entra aqui, porque es feof y sale del buccle.
            break;
		char **frasefragmentada = fragmenta(dats);
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
	float ir[j];
	for (int i=0; i<j; i++)
	{
		ir[i] = datos[i].ir;
	}	
	quicksort(datos, 0, j-1, ir);
	float na[j];
	for (int i=0; i<j; i++)
	{
		na[i] = datos[i].na;
	}
	quicksort(datos, 0, j-1, na);
	for (int i=0; i<j; i++)
	{
		printf("%f\n", datos[i].na);
	}
	int tipo[j];
	for (int i=0; i<j; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	//Tablaentropia t = entropia(tipo, j-1);
	fclose(f);
	return 0;
}