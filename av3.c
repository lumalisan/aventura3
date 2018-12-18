// Assembly Language Lovers - Aventura 3
// Castorina, Izar Maria Pietro
// Lòpez Cortés, Andreu
// Rocha, Lisandro

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "my_lib.h"

#define THREADS 10
#define N 100000     // Nùmero de iteraciones

void *funcion_hilo();

static struct my_stack *stack;

pthread_t hilos[THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {

  // Si el usuario no especifica un nombre de fichero, el programa devuelve la sintaxis correcta y se cierra
  if (argv[1] == NULL || strlen(argv[1]) == 0) {
    fprintf(stderr, "USAGE: ./av3 <filename>\n");
    exit(1);
  }

  stack = my_stack_read(argv[1]);   // Leemos la pila desde el fichero

  int num_elems = 10;               // Nùmero de elementos
  int *data_int;

/*
  Mayor nùmero para verificar si se añaden los elementos que faltan.
  Cuando se crea el fichero, se ponen 10 elementos. Intentando abrir el mismo
  fichero, el programa intentarà llevar ese nùmero a 15. Lo he hecho para verificar
  si efectivamente se añadìan los elementos que faltaban
*/

    if (stack != NULL) {    // Si la pila ha sido leida correctamente...
        printf("Fichero %s encontrado!)\n",argv[1]);

        if (my_stack_len(stack) < num_elems) {    // Comprobamos si hay menos elementos de lo esperado

            int diff = num_elems - my_stack_len(stack);
            for (int i=0; i<diff; i++) {          // Si hay menos, se añade la diferencia
                data_int = malloc(sizeof(int));
                *data_int = 0;
                my_stack_push(stack,data_int);
            }
            my_stack_write(stack,argv[1]);
        }

    } else {                // Si el fichero no existe, llenamos la pila de (num_elems) elementos y la escribimos
        printf("Fichero \"%s\" no encontrado! Creando...\n", argv[1]);
        stack = my_stack_init(num_elems);

        for (int i = 0; i < num_elems; i++) {   // Llenamos de elementos (0)
            data_int = malloc(sizeof(int));
            *data_int = 0;
            my_stack_push(stack,data_int);
            free(data_int);
        }

        my_stack_write(stack,argv[1]);
    }

  // Fin de la lectura de la pila

  // Creaciòn de los hilos de ejecuciòn
  printf("Threads: %d. Iterations: %d\n", THREADS, N);
  for(int i = 0; i < THREADS; i++) {
     pthread_create(&hilos[i], NULL, funcion_hilo, NULL);
  }

  // Esperamos a que los hilos acaben
  for(int i = 0; i < THREADS; i++) {
    pthread_join(hilos[i], NULL);
  }

  // Escribimos la pila
  my_stack_write(stack,argv[1]);
  //my_stack_purge(stack);

  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);

}

// Función a ejecutar por los hilos
void *funcion_hilo() {

  printf("Starting thread\n");
  int *data_int;

  for (size_t i = 0; i < N; i++) {
    pthread_mutex_lock(&mutex);
    data_int = my_stack_pop(stack);   // Pop desde la pila, secciòn critica #1
    pthread_mutex_unlock(&mutex);
    (*data_int)++;
    pthread_mutex_lock(&mutex);
    my_stack_push(stack, data_int);   // Push hacia la pila, secciòn critica #2
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);   // Salida dal thread

}
