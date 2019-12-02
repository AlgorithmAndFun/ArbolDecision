/*
 * AUTORES: Ane Zubillaga, Ian Recke, Ivan Sorbet, Alejandro Meza
 *version del 30/11/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include "fragmentar.h"
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



/*typedef struct tablaentropia{
	double entr;
	int pos;
}Tablaentropia;*/

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
double entropialateral(int tipo[],int inicio, int final){
    double tipos1,tipos2,tipos3,tipos4,tipos5,tipos6,tipos7;
    double entropia;
    double total=final-inicio;
    int i=inicio;
    while(i<final){
        if(tipo[i]==1){
            tipos1++;
        }
        else if(tipo[i]==2){
            tipos2++;
        }
        else if(tipo[i]==3){
            tipos3++;
        }
        else if(tipo[i]==4){
            tipos4++;
        }
        else if(tipo[i]==5){
            tipos5++;
        }
        else if(tipo[i]==6){
            tipos6++;
        }
        else if(tipo[i]==7){
            tipos7++;
        }
        
        
        i++;
    }
    entropia=-(tipos1/total)*log2(tipos1/total)-(tipos2/total)*log2(tipos2/total)-(tipos3/total)*log2(tipos3/total)-(tipos4/total)*log2(tipos4/total)-(tipos5/total)*log2(tipos5/total)-(tipos6/total)*log2(tipos6/total)-(tipos7/total)*log2(tipos7/total);
    return entropia;
}
int entropia(int tipo[], int longitud)
{
	int menor=1000;
    int posmenor=0;
    double entropia;
	int i = 0; 
	while (i < longitud)
	{
		if (tipo[i]!= tipo[i+1])
		{
		
			double entrizq = entropialateral(tipo, 0, i);
			double entrdech = entropialateral(tipo, i, longitud);
        
            printf("Soy la izquierda: %f\n", entrizq);
			entropia =(i/longitud)*entrizq + ((longitud-i)/longitud)*entrdech;
           // printf("%f\n",entropia);
			if(entropia<menor){
                posmenor=i;
                menor=entropia;
            }
            
		}
		i++;
	}	return posmenor;

}
     

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
    int posicion = entropia(&(datos)->tipo,j);
    printf("posicion %d\n",posicion);
	//ENTROPIA
	/////////
	float na[j];
	for (int i=0; i<j; i++)
	{
		na[i] = datos[i].na;
	}
	quicksort(datos, 0, j-1, na);
    int posicion2 = entropia(&(datos)->tipo,j-1);
    printf("posicion %d",posicion2);
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
