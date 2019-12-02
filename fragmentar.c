#include "fragmentar.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **fragmenta(char* cadena){

    char *arg2;
    char **arg;
    char *token;
    int comandos = 1;//cuenta los comandos/palabras que va a haber
    arg2 = (char*)malloc(strlen(cadena)+1);
    strcpy(arg2,cadena);//copiamos en arg2 la cadena.
    token = strtok((char*)cadena,",");
    while(token!=0){
        comandos++;
        token = strtok(NULL,",");
    }
    arg = (char**)malloc(comandos*sizeof(char*));//reservamos arg con todas las posiciones de memoria que necesitamos
    comandos = 0;
    token = strtok(arg2, ",");
    while(token!=NULL){
        arg[comandos] = (char *)malloc((strlen(token)+1)*sizeof(char));//reservamos su memoria del espacio del token.
        *(&arg[comandos]) = token;
        comandos = comandos + 1;
        token = strtok(NULL,",");
    }
    arg[comandos] = NULL;
    return arg;
}



void borrarg(char **arg){
    int i = 0;
    while(arg[i]!=NULL){
        free(arg[i]);
        i++;
    }
    free(arg);
}
/*
int main(){

    char cadena[150];
    char** fraseFragmentada;
    int i;
    
    strcpy(cadena,"esto es solamente un ejemplo\0"); //Suponemos que el usuario introduce esta frase
    
    printf("El usuario ha introducido la frase:\n%s\n",cadena);
    printf("Si le aplico la fragmentación, puedo recorrer el array mostrando cada token:\n");
    fraseFragmentada = fragmenta(cadena); // Fragmento mi cadena
    i = 0; // Comienzo leyendo el elemento 0 de mi array
    while(fraseFragmentada[i] != NULL){ // Recorro mi array fragmentado hasta que encuentre un NULL
        printf("Token nº %d: %s (Posición de memoria %p)\n", i, fraseFragmentada[i], fraseFragmentada[i]);
        i++;
    }
    printf("Encontrado fin de array, NULL\n");
    return 0;
}*/
