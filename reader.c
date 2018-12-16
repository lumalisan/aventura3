#include <stdio.h>
#include <limits.h>
#include "my_lib.h"

int main(int argc, char *argv[]) {

	struct my_stack *stack = my_stack_read(argv[1]);
	int contador = 0;
	int suma = 0;
	int min = 0;
	int max = 0;
	int previo = 0;

	while (contador <= my_stack_len(stack)) {
		contador++;
		int value = my_stack_pop(stack);
		printf("Elemento número %d --> %d\n", contador, value);
		//Suma
		suma =+ value;
		//Min
		if (contador == 1) {
			min = value;
		} else if (value < min) {
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
