// Assembly Language Lovers - Aventura 3
// Castorina, Izar Maria Pietro
// Lòpez Cortés, Andreu
// Rocha, Lisandro

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "my_lib.h"

int main(int argc, char *argv[]) {

  //Si no se ha especificado fichero se notifica por consola
	if (argv[1] == NULL || strlen(argv[1]) == 0) {
    fprintf(stderr, "USAGE: ./reader <filename>\n");
		exit(1);
	}

  //Instanciamos el stack
	struct my_stack *stack = my_stack_read(argv[1]);

  //Si no existe el fichero especificado se notifica por consola
	if (stack == NULL) {
    char str[100];
    sprintf(str, "Couldn't open stack file %s\n", argv[1]);
    fprintf(stderr, str, NULL);
		exit(1);
	}

  //Variables que utilizaremos
	int contador = 0;
	int suma = 0;
	int min = INT_MAX;
	int max = 0;
  int *data_int;

  //Alocamos el puntero con valor sizeof(int)
	data_int = malloc(sizeof(int));

	int stack_length = my_stack_len(stack);

  printf("Stack length: %d\n", stack_length);

  //Bucle principal del programa donde se realizan todas las operaciones
	while (contador < stack_length) {
		contador++;
		data_int = my_stack_pop(stack);
		printf("Elemento número %d --> %d\n", contador, *data_int);
		//Suma
		suma += *data_int;
		//Min
		if (*data_int < min) {
			min = *data_int;
		}
		//Max
		if (contador == 1) {
			max = *data_int;
		} else if (*data_int > max) {
			max = *data_int;
		}

	}

  //Liberamos la memoria que previamente habíamos alocado con malloc()
	free(data_int);

	//Media
	int media = suma/contador;

  //Mostramos resultados por pantalla
	printf("La suma es: %d\n", suma);
	printf("El min es: %d\n", min);
	printf("El max es: %d\n", max);
	printf("La media es: %d\n", media);

  //Limpiamos la pila
	my_stack_purge(stack);

}
