#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "my_lib.h"

#define THREADS 10
#define N 1000000

void *funcion_hilo();

static struct my_stack *stack;

pthread_t hilos[THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Funciones asociadas a la libreria pthread

    pthread_mutex_lock()    --> Bloqueamos el semáforo mutex pasandole como parámetro su dirección
    pthread_mutex_unlock()  --> Desbloqueamos el semáforo mutex pasandole como parámetro su dirección
    pthread_exit()          --> Salimos de la función
    pthread_join()          --> Espera a que los hilos acabaen

*/

int main(int argc, char *argv[]) {

  if (argv[1] == NULL || strlen(argv[1]) == 0) {
    fprintf(stderr, "USAGE: ./av3 <filename>\n");
    exit(1);
  }

  stack = my_stack_read(argv[1]);

  int num_elems = 10;
  //int debug_num_elems = 10;
  int *data_int;

/*
  Mayor nùmero para verificar si se añaden los elementos que faltan.
  Cuando se crea el fichero, se ponen 10 elementos. Intentando abrir el mismo
  fichero, el programa intentarà llevar ese nùmero a 15. Lo he hecho para verificar
  si efectivamente se añadìan los elementos que faltaban
*/

    if (stack != NULL) {    // Si el fichero existe, leemos la pila
        printf("Fichero %s encontrado!)\n",argv[1]);

        if (my_stack_len(stack) < num_elems) {

            int diff = num_elems - my_stack_len(stack);
            for (int i=0; i<diff; i++) {
                data_int = malloc(sizeof(int));
                *data_int = 0;
                my_stack_push(stack,data_int);
            }
            my_stack_write(stack,argv[1]);
        }

    } else {                                  // Si el fichero no existe, llenamos la pila de (num_elems) elementos y la escribimos
        printf("Fichero \"%s\" no encontrado! Creando...\n", argv[1]);
        stack = my_stack_init(num_elems);

        for (int i = 0; i < num_elems; i++) {
            data_int = malloc(sizeof(int));
            *data_int = 0;
            my_stack_push(stack,data_int);
            free(data_int);
        }

        my_stack_write(stack,argv[1]);
    }

  printf("Threads: %d. Iterations: %d\n", THREADS, N);
  for(int i = 0; i < THREADS; i++) {
     pthread_create(&hilos[i], NULL, funcion_hilo, NULL);
  }

  /* Wait on the other threads */
  for(int i = 0; i < THREADS; i++) {
    pthread_join(hilos[i], NULL);
  }

  my_stack_write(stack,argv[1]);
  my_stack_purge(stack);

  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);

}

void *funcion_hilo() {

  printf("Starting thread\n");
  int *data_int;

  for (size_t i = 0; i < N; i++) {
    pthread_mutex_lock(&mutex);
    data_int = my_stack_pop(stack);
    pthread_mutex_unlock(&mutex);

    (*data_int)++;

    pthread_mutex_lock(&mutex);
    my_stack_push(stack, data_int);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);

}
