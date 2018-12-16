#include <stdio.h>
#include <limits.h>
#include "my_lib.h"

int main(int argc, char *argv[]) {

	struct my_stack *stack = my_stack_read(argv[1]);
	int contador = 0;
	int suma = 0;
	int min = 0;
	int max = 0;
	int media = 0;

	while (contador <= my_stack_len(stack)) {
		contador++;
		int value = my_stack_pop(stack);
		printf("Elemento número %d --> %d\n", contador, value);

		//TODO suma
		//TODO min
		//TODO max
		//TODO media
	}

	my_stack_purge(stack);

}
