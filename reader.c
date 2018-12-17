#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "my_lib.h"

struct my_data {
  int value;
};

int main(int argc, char *argv[]) {

	if (strlen(argv[1]) == 0) {
		printf("USAGE: ./reader <filename>\n");
		exit(1);
	}

	struct my_stack *stack = my_stack_read(argv[1]);

	if (stack == NULL) {
		printf("Couldn't open stack file %s\n", argv[1]);
		exit(1);
	}

	int contador = 0;
	int suma = 0;
	int min = INT_MAX;
	int max = 0;

	struct my_data *data_int;
	data_int = malloc(sizeof(struct my_data));

	int stack_length = my_stack_len(stack);

	while (contador < stack_length) {
		contador++;

		data_int = my_stack_pop(stack);
		printf("Elemento número %d --> %d\n", contador, data_int->value);
		//Suma
		suma += data_int->value;
		//Min
		if (data_int->value < min) {
			min = data_int->value;
		}
		//Max
		if (contador == 1) {
			max = data_int->value;
		} else if (data_int->value > max) {
			max = data_int->value;
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
