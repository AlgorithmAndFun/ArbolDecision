/*
 * AUTORES: Ane Zubillaga, Ian Recke, Ivan Sorbet, Alejandro Meza
 *version del 30/11/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include "fragmenta.h"
#include <sys/errno.h>
#include <wchar.h>
#include <math.h>
#include <unistd.h>
#include "arbolBin.h"
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
    double tipos1 = 0,tipos2 = 0,tipos3 = 0,tipos4 = 0,tipos5 = 0,tipos6 = 0,tipos7 = 0;
    double entropia = 0;
    double total=(final-inicio+1);
    int i=inicio;
    while(i<=final){
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
    double tabla[7] = {tipos1, tipos2, tipos3, tipos4, tipos5, tipos6, tipos7};
     for (int h=0; h<7; h++)
     {
         if (tabla[h] != 0)
             entropia = entropia - ((tabla[h]/total)*log2(tabla[h]/total));
   //      printf("Dentro del for %f\n", entropia);
     }
     
    return entropia;
}
void entropia(int tipo[], int longitud, int *posicion, double *entropia)
{
	double menor=1000;
    int posmenor=0;
   // double entropia = 0;
	int i = 0; 
	while (i < longitud)
	{
		if (tipo[i]!= tipo[i+1])
		{
		
			double entrizq = entropialateral(tipo, 0, i);
			double entrdech = entropialateral(tipo, i+1, longitud);
            *entropia =(((double)((double)i/(double)longitud)*entrizq) + (((double)((double)longitud-(double)i)/(double)longitud)*entrdech));
            printf("%f\n", *entropia);
			if(*entropia<menor){
                posmenor=i;
                menor=*entropia;
            }
            
		}
		i++;
	}
	*posicion = posmenor;
	*entropia = menor;

}
     

int main(void)
{
	start_arbol_decision();
	FILE *f;
	char dats[400];
    int r;
	char aux[100];
	f = fopen("problem_glass.csv", "r+");
	fgets(aux, 100, f); //lee los valores que no van a servir de la primera fila
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
	fclose(f);
	return 0; 
}

int casoBase(Datos datos, int comienzo, int final){
    double probabilad = 0.8;
    double total = final -comienzo +1; 
    double tipos1 = 0,tipos2 = 0,tipos3 = 0,tipos4 = 0,tipos5 = 0,tipos6 = 0,tipos7 = 0;
    for(int i = comienzo; i<final; i++){
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
    }
    ///////////////////
    if((tipos1/total)>0.8){
        return 1;
    }
    else if((tipos2/total)>0.8){
        return 2;
    }
    else if((tipos3/total)>0.8){
        return 3;
    }
     else if((tipos4/total)>0.8){
        return 4;
    }
     else if((tipos5/total)>0.8){
        return 5;
    }
     else if((tipos6/total)>0.8){
        return 6;
    }
     else if((tipos7/total)>0.8){
        return 7;
    }
    else{
        return -1;
    }
    ////////////////
}


tipoArbol CreaArbol(Datos datos,int comienzo,int final){
    
   
	float ir[final];
	for (int i=comienzo; i<final; i++)
	{
		ir[i] = datos[i].ir;
	}	
	quicksort(datos, comienzo, final-1, ir);
    int tipo[final];
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posir=comienzo;
	double entroir;
    entropia(tipo,final-1, &posir, &entroir);
	//ENTROPIA NA
	/////////
	float na[final];
	for (int i=comienzo; i<final; i++)
	{
		na[i] = datos[i].na;
	}
	quicksort(datos, comienzo, final-1, na);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posna = comienzo;
	double entrona;
	entropia(tipo, final-1, &posna, &entrona);
	//ENTROPIA
	/////
	float mg[final];
	for(int i = comienzo; i<final; i++){
		mg[i]=datos[i].mg;
	}
	quicksort(datos,comienzo, final-1, mg);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posmg = comienzo;
	double entromg;
	entropia(tipo, &posmg, &entromg);
	//ENTROPIA
	/////////////////// 
	float al[final];
	for(int i =comienzo; i<final; i++){
		al[i] = datos[i].al;
	}
	quicksort(datos,comienzo, final-1, al);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posal;
	double entroal;
	 entropia(tipo, final-1, &posal, &entroal);
	//ENTROPIA
	///////////////////// 
    float si[final];
    for(int i=comienzo; i<final; i++){
		si[i]=datos[i].si;
	}
	quicksort(datos,comienzo, final-1, si);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int possi;
	double entrosi;
	entropia(tipo, final-1, &possi, &entrosi);
	//ENTROPIA
	/////////////////////
	float k[final];
	for(int i=comienzo; i<final; i++){
		k[i] = datos[i].k;
	}
	quicksort(datos,comienzo, final-1, k);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posk;
	double entrok;
	entropia(tipo, final-1, &posk, &entrok);
	//ENTROPIA
	float ca[final];
	for(int i =comienzo; i<final; i++){
		ca[i] = datos[i].ca;
	}
	quicksort(datos,comienzo, final-1, ca);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posca;
	double entroca;
	entropia(tipo, final-1, &posk, &entrok);
	//ENTROPIA
	float va[final];
	for(int i=comienzo; i<final; i++){
		va[i]= datos[i].va;
	}
	quicksort(datos,comienzo, final-1, va);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posva;
	double entrova;
	entropia(tipo, final-1, &posva, &entrova);
	//ENTROPIA
	float fe[final];
	for(int i=comienzo; i<final; i++){
		fe[i] = datos[i].fe;
	}
	quicksort(datos,comienzo, final-1, fe);
	for (int i=comienzo; i<final; i++)
	{
		tipo[i] = datos[i].tipo;
	}
	int posfe;
	double entrofe;
	entropia(tipo, final-1, &posfe, &entrofe);
	
	double menor = 1000;
	if (entroir < menor){
        elemento=11;
		menor = entroir;
    }
	if (entrona < menor){
        elemento=12;
		menor = entrona;
    }
	if (entromg < menor){
        elemento=13;
		menor = entromg;
    }
	if (entroal < menor){
        elemento=14;
		menor = entroal;
    }
	if (entrosi < menor){
        elemento=15;
		menor = entrosi;
    }
	if (entrok < menor){
        elemento=16
		menor = entrok;
    }
	if (entroca < menor){
        elemento=17;
		menor = entroca;
    }
	if (entrova < menor){
        elemento=18;
		menor = entrova;
    }
	if (entrofe < menor){
        elemento=19;
		menor = entrofe;
    }
    int posicion;
    if(elemento==11){
        quicksort(datos, comienzo, final, ir);
        umbral = datos[posir].ir;
        posicion = posir;
    }
    if(elemento==12){
        quicksort(datos, comienzo, final, na);
        umbral = datos[posna].na;
        posicion = posna;
    }
    if(elemento==13){
        quicksort(datos, comienzo, final, mg);
        umbral = datos[posmg].mg;
        posicion = posmg
    }
    if(elemento==14)
    {
        quicksort(datos, comienzo, final, al);
        umbral = datos[posal].al;
        posicion = posal;
    }
    if(elemento==15){
        quicksort(datos, comienzo, final, si);
        umbral = datos[possi].si;
        posicion = possi;
        
    }
    if(elemento==16){
        quicksort(datos, comienzo, final, k);
        umbral = datos[posk].k;
        posicion =posk;
    }
    if(elemento==17){
        quicksort(datos, comienzo, final, ca);
        umbral = datos[posca].ca;
        posicion = posca;
    }
    if(elemento==18){
        quicksort(datos, comienzo, final, va);
        umbral = datos[posva].va;
        posicion = posva;
    }
    if(elemento==19){
        quicksort(datos, comienzo, final, fe);
       umbral = datos[posfe].fe; 
       posicion = posfe;
    }
    
    
    
    int solucion = casoBase(datos, comienzo, final);
    if(solucion !=-1){
        tipoElementoArbol tip;
        tip.elemento="solucion";
        tip.umbral=0;
        tip.entropia=solucion;
        arbol1 = construir(tip, NULL, NULL);
    }
    else{
        tipoElementoArbol ti;
        ti.elemento=elemento;
        tip.umbral=umbral;
        tip.entropia=menor;
        arbol1 = construir(ti, CreaArbol(datos,comienzo,posicion-1),CreaArbol(datos,posicion+1,final));
    }
	return arbol1;
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
