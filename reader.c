#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "my_lib.h"

int main(int argc, char *argv[]) {

	if (strlen(argv[1]) == 0) {
		printf("USAGE: ./reader <filename>");
		exit(1);
	}

	struct my_stack *stack = my_stack_read(argv[1]);

	if (stack == NULL) {
		printf("Couldn't open stack file %s", argv[1]);
		exit(1);
	}

	int contador = 0;
	int suma = 0;
	int min = INT_MAX;
	int max = 0;

	while (contador <= my_stack_len(stack)) {
		contador++;
		int value = (int) my_stack_pop(stack);
		printf("Elemento número %d --> %d\n", contador, value);
		//Suma
		suma += value;
		//Min
		if (value < min) {
			min = value;
		}
		//Max
		if (contador == 1) {
			max = value;
		} else if (value > max) {
			max = value;
		}
	}

	//Media
	int media = suma/contador;

	printf("La suma es: %d\n", suma);
	printf("El min es: %d\n", min);
	printf("El max es: %d\n", max);
	printf("La media es: %d\n", media);

	my_stack_purge(stack);

}
