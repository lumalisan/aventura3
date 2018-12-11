#include <stdio.h>
#include "my_lib.h"

static struct my_stack *stack;

int main(int argc, char *argv[]) {

    FILE *nom_stack;
    fgets(nom_stack, 100, stdin);
    if (nom_stack)
        stack = my_stack_read(nom_stack);
    else {
        stack = my_stack_write(nom_stack);
    }

    stack = my_stack_init(10);
	
}