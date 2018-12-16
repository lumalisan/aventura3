#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "my_lib.h"

void funcion_hilo();

static struct my_stack *stack;
static struct my_stack_node *data;

pthread_t hilos[10];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Funciones asociadas a la libreria pthread

    pthread_mutex_lock()    --> Bloqueamos el semáforo mutex pasandole como parámetro su dirección
    pthread_mutex_unlock()  --> Desbloqueamos el semáforo mutex pasandole como parámetro su dirección
    pthread_exit()          --> Salimos de la función
    pthread_join()          --> Espera a que los hilos acabaen

*/

int main(int argc, char *argv[]) {

    char nom_stack[100];
    int num_elems = 10;
    int debug_num_elems = 15;   // Mayor nùmero para verificar si se añaden los elementos que faltan
                                // Cuando se crea el fichero, se ponen 10 elementos. Intentando abrir el mismo
                                // fichero, el programa intentarà llevar ese nùmero a 15. Lo he hecho para verificar
                                // si efectivamente se añadìan los elementos que faltaban

    data = malloc(sizeof(struct my_stack_node));    // Reservamos memòria para un nodo
    data->data = 0;                                 // Valor del nodo: 0

    printf("Nombre del fichero de pila: ");

    char *ptr = fgets(nom_stack, 100, stdin);   // El usuario introduce el nombre de fichero
    if (!ptr && !feof(stdin)) {
        ptr = nom_stack;
        ptr[0] = 0;
    }

    fflush(stdin);
    strtok(nom_stack, "\t\n\r");    // Limpiamos nom_stack de los caràcteres indeseados

    stack = my_stack_read(nom_stack);   // Leemos el file especificado

    if (stack != NULL) {    // Si el fichero existe, leemos la pila
        printf("Fichero %s encontrado!)\n",nom_stack);

        if (my_stack_len(stack) < debug_num_elems) {     // Si la pila leida contiene menos de num_elems elementos, añadimos los restantes
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
            my_stack_write(aux_stack,nom_stack);    // Substituimos la pila auxiliaria a la pila original
            stack = my_stack_read(nom_stack);       // Leemos la pila auxiliaria
        }
    }

    else {                                  // Si el fichero no existe, llenamos la pila de (num_elems) elementos y la escribimos
        printf("Fichero \"%s\" no encontrado! Creando...\n", nom_stack);
        stack = my_stack_init(num_elems);

        for (int i=0; i<num_elems; i++) {
            my_stack_push(stack,data);
        }

        my_stack_write(stack,nom_stack);
    }

    // Comprobaciòn final: Leemos el fichero desde el disco y vemos cuàntos elementos contiene
    stack = my_stack_read(nom_stack);
    printf("DEBUG - Stack length: %d\n",my_stack_len(stack));



    for (int i=0; i<10; i++) {
      pthread_create(hilos[i], NULL, funcion_hilo, NULL);
    }




    return 0;


}

void funcion_hilo() {

  printf("Test hilo\n");

}
