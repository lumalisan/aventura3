#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "my_lib.h"

void *funcion_hilo();

static struct my_stack *stack;
static struct my_stack_node *data;
static int num = 0;


pthread_t hilos[10];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Funciones asociadas a la libreria pthread

    pthread_mutex_lock()    --> Bloqueamos el semáforo mutex pasandole como parámetro su dirección
    pthread_mutex_unlock()  --> Desbloqueamos el semáforo mutex pasandole como parámetro su dirección
    pthread_exit()          --> Salimos de la función
    pthread_join()          --> Espera a que los hilos acabaen

*/

int main(int argc, char *argv[]) {

  if (strlen(argv[1]) == 0) {
    printf("USAGE: ./av3 <filename>");
    exit(1);
  }

  stack = my_stack_read(argv[1]);

  int num_elems = 10;
  int debug_num_elems = 15;

/*
  Mayor nùmero para verificar si se añaden los elementos que faltan.
  Cuando se crea el fichero, se ponen 10 elementos. Intentando abrir el mismo
  fichero, el programa intentarà llevar ese nùmero a 15. Lo he hecho para verificar
  si efectivamente se añadìan los elementos que faltaban
*/

  data = malloc(sizeof(struct my_stack_node));    // Reservamos memòria para un nodo
  data->data = 0;                                 // Valor del nodo: 0

    if (stack != NULL) {    // Si el fichero existe, leemos la pila
        printf("Fichero %s encontrado!)\n",argv[1]);

         // Si la pila leida contiene menos de num_elems elementos, añadimos los restantes
        if (my_stack_len(stack) < debug_num_elems) {
            printf("DEBUG - Hay menos de %d elementos en la pila! (stack length: %d)\n",debug_num_elems,my_stack_len(stack));

            struct my_stack *aux_stack = my_stack_init(debug_num_elems);    // Creaciòn de una pila auxiliaria
            int num_elems_read = my_stack_len(stack);                       // Nùmero de elementos en la pila leida

            for (int i=0; i<num_elems_read; i++) {
                printf("DEBUG - Copying data... (Remaining: %d)\n",my_stack_len(stack));
                struct my_stack_node *aux_data = my_stack_pop(stack);
                my_stack_push(aux_stack, aux_data);                 // Copiamos los contenidos de la pila en la auxiliaria
            }

            while (my_stack_len(aux_stack) != debug_num_elems) {    // Añadimos los elementos que faltan
                my_stack_push(aux_stack,data);
                printf("DEBUG - Adding 1 element... | ");
                printf("Current stack length: %d\n",my_stack_len(aux_stack));
            }
            my_stack_write(aux_stack,argv[1]);    // Substituimos la pila auxiliaria a la pila original
            stack = my_stack_read(argv[1]);       // Leemos la pila auxiliaria
        }

    } else {                                  // Si el fichero no existe, llenamos la pila de (num_elems) elementos y la escribimos
        printf("Fichero \"%s\" no encontrado! Creando...\n", argv[1]);
        stack = my_stack_init(num_elems);

        for (int i=0; i<num_elems; i++) {
            my_stack_push(stack,data);
        }

        my_stack_write(stack,argv[1]);
    }

/*
    // Comprobaciòn final: Leemos el fichero desde el disco y vemos cuàntos elementos contiene
    stack = my_stack_read(argv[1]);
    printf("DEBUG - Stack length: %d\n",my_stack_len(stack));
*/

    while (num != 10) {
      pthread_create(&hilos[num], NULL, funcion_hilo, NULL);
    }
    printf("Creados 10 threads, en teoría\n");

    return 0;

}

void *funcion_hilo() {
  // My boobs are veganas, fiol is fucking bitch lasagna bitch lasagna

  printf("Test hilo (num = %d)\n",num);
  num++;
  return 0;

}
