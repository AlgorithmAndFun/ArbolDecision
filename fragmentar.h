
/*LEER LINEA DE TEXTO
 * char linea[100];
 * scanf("%["^\n]",linea);*/
//ejecutamos en la minishel fragmenta() con el interior lo que introducimos como entrada, el string.
//primero, averiguar cuatos comandos tiene el string.
//luego vamos a memoria y creamos un array de x elemenots siendo el ultimo null
//cada una de esas posiciones tienen un puntero a caracter que apuntan a otra zona de memoria donde si que esten dichos comandos.

char **fragmenta(char*);
void borrarg(char **arg);
