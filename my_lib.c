// * Libreria my_lib.c *
// Aventura 1 - Sistemas Operativos (Grupo 1)
// Squad "Assembly Language Lovers"
// - Castorina, Izar Maria Pietro
// - López Cortés, Andreu
// - Rocha, Lisandro

#include <stdio.h>
#include "my_lib.h"

////////////////////////////////////////////////
///////////Funciones de Strings/////////////////
////////////////////////////////////////////////

// my_strlen: Devuelve un entero sin signo con la longitud
// del string que le pasamos como parámetro.
size_t my_strlen(const char *str)
{
	size_t longitud = 0;
	while (*str++ != '\0')
	{
		longitud++;
	}
	return longitud;
}

// my_strcmp: Compara los valores ASCII de los carácteres de
// las dos strings que pasamos como parámetro.
// Devuelve un entero negativo si el primer string es
// menor que el segundo, uno positivo si el primero
// es mayor, y cero si los dos son iguales.
int my_strcmp(const char *str1, const char *str2)
{
	int counter = 0;
	int strValue1 = +str1[counter];
	int strValue2 = +str2[counter];
	int final = 1;
	while (strValue1 == strValue2 && final == 1)
	{
		counter++;
		strValue1 += str1[counter];
		strValue2 += str2[counter];
		if ((char)str1[counter] == '\0')
		{
			final = 0; // Si el primer string ha terminado, salimos del bucle
		}
	}
	return strValue1 - strValue2;
}

// my_strcpy: Copia los contenidos del string fuente
// dentro del string de destino.
char *my_strcpy(char *dest, const char *src)
{
	int counter = 0;
	char c = src[counter];
	while (c != '\0')
	{
		dest[counter] = src[counter];
		counter++;
		c = src[counter];
	}
	dest[counter] = '\0';
	return dest;
}

// my_strncpy: Copia n caracteres del string fuente
// dentro del string de destino.
char *my_strncpy(char *dest, const char *src, size_t n)
{
	int counter = 0;
	while (counter < n)
	{
		dest[counter] = src[counter];
		counter++;
	}
	return dest;
}

// my_strcat: Adjunta los contenidos del string fuente
// al final del string de destino.
char *my_strcat(char *dest, const char *src)
{
	char *auxDest = dest;
	//Movemos el puntero al final de la palabra destino
	while (*auxDest != '\0')
	{
		auxDest++;
	}
	//Copiamos el contenido de src en la posicion de dest
	while (*src != '\0')
	{
		*auxDest++ = *src++;
	}
	//Copiamos el caracter terminal (\0)
	*auxDest++ = *src++;
	return dest;
}

////////////////////////////////////////////////
///////////Funciones de la pila/////////////////
////////////////////////////////////////////////

// Redefinimos el tipo my_stack_node como nodo, para que
// el código quede más limpio
typedef struct my_stack_node nodo;

// Inicialización de la pila
// El entero pasado como parámetro determina el tamaño de la pila
struct my_stack *my_stack_init(int size)
{
	struct my_stack *pila;
	pila = malloc(sizeof(struct my_stack));
	pila->size = size;
	pila->first = NULL;
	return pila;
}

// my_stack_push: creamos un nuevo nodo con una serie de datos que
// nos pasan por parámetro y los adjuntamos después del último nodo.
// Devuelve -1 si ha habido error y 0 si ha ido todo correcto.
int my_stack_push(struct my_stack *stack, void *data)
{
	if (stack == NULL || sizeof(data) <= 0 || (my_stack_len(stack) == stack->size))
	{
		return -1;
	}
	nodo *aux;
	aux = malloc(sizeof(nodo));
	aux->data = data;
	aux->next = stack->first;
	stack->first = aux;
	return 0;
}

// my_stack_pop: eliminamos el último nodo que se introdujo en la pila
// además de liberar la memoria en la que este era contenido.
// Devolvemos NULL si no hay elementos o el puntero en el caso
// de que haya algún elemento.
void *my_stack_pop(struct my_stack *stack)
{
	if (my_stack_len(stack) == 0)
	{
		return NULL;
	}
	nodo *aux1; // Nodo auxiliar: Top of Stack
	nodo *aux2; // Nodo auxiliar para devolver los datos del nodo eliminado
	aux1 = stack->first;
	aux2 = malloc(sizeof(nodo));
	aux2->data = stack->first->data;   // Cogemos los datos del T.O.S.
	stack->first = stack->first->next; // Asignamos el nuevo T.O.S.
	free(aux1);						   // Liberamos la memoria del T.O.S.
	return aux2->data;
}

// my_stack_len: recorremos toda la pila contando los
// nodos que hay en ella.
int my_stack_len(struct my_stack *stack)
{
	nodo *aux;
	int contador = 1;
	aux = stack->first;
	if (aux == NULL)
	{
		return 0;	// Si el TOS està vacio, no hay elementos en la pila
	}
	while (aux->next != NULL)
	{
		aux = aux->next;
		contador++;
	}
	return contador;
}

// my_stack_write: Almacenamos los datos de la pila en el fichero
// cuyo nombre se pasa por parametro
int my_stack_write(struct my_stack *stack, char *filename)
{
	// Creamos una pila auxiliar y un nodo auxiliar para la operación
	// de copia de datos
	struct my_stack *pila_aux;
	nodo *node_aux = stack->first;
	pila_aux = my_stack_init(stack->size);
	
	// copiamos la pila a pila aux

	while (node_aux != NULL)
	{
		my_stack_push(pila_aux, node_aux->data); // Añadimos nodos a la
		node_aux = node_aux->next;				 // pila auxiliaria
	}

	// comprueba filename si es null
	if (filename == NULL)
	{
		return -1; // Devolvemos un codigo de error si el nombre no es valido
	}
	else
	{
		// usamos nodo auxiliar en la pila auxiliar
		node_aux = pila_aux->first;
		void *data;
		
		// creamos array
		char buffer[sizeof(int)];

		// creamos fichero escritura con permisos correspondientes
		int fichero_escritura = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
		// guardamos size en buffer
		sprintf(buffer, "%d", pila_aux->size);
		// escribimos
		write(fichero_escritura, buffer, sizeof(int));

		int recorredor_pila = 0; // Contador de elementos escritos
		while (node_aux != NULL)
		{
			// escribimos recorriendo pila avanzando nodo y contador
			data = node_aux->data;
			write(fichero_escritura, data, pila_aux->size);
			node_aux = node_aux->next;
			recorredor_pila++;
		}
		// Cerramos
		close(fichero_escritura);
		return (recorredor_pila); // Devolvemos el n. de elementos escritos
	}
}

// my_stack_read: Leemos la pila almacenada en el file
// pasado por parametro
struct my_stack *my_stack_read(char *filename)
{
	// Abrimos fichero
	int fichero_lectura = open(filename, O_RDONLY);
	if (fichero_lectura == -1)
	{
		return NULL; // NULL si hay un error en abrir el fichero
	}
	else
	{
		// Creamos array
		char buffer[sizeof(int)];
		struct my_stack *pila_lectura;	// Pila auxiliar
		void *data1;

		// Lecutura
		read(fichero_lectura, buffer, sizeof(int));
		// Pasamos buffer a toint
		int buffer_toint = atoi(buffer);
		// Inicializamos con toint
		pila_lectura = my_stack_init(buffer_toint);
		// Reservamos memoria con malloc
		data1 = malloc(buffer_toint);

		// Comprobamos si data es null
		if ((data1) == NULL)
		{
			return NULL;
		}

		// while con condiciones de lectura mayor que 0
		while (read(fichero_lectura, data1, buffer_toint) > 0)
		{
			// Vamos metiendo datos en la pila
			my_stack_push(pila_lectura, data1);
			// Reservamos memoria
			data1 = malloc(buffer_toint);
			if ((data1) == NULL)
			{
				return NULL;
			}
		}
		// Cerramos
		close(fichero_lectura);
		return (pila_lectura);
	}
	return NULL;
}

// my_stack_purge: limpiamos la pila haciendo pop y finalmente
// liberando la memoria de la pila como tal. Devuelve el núm.
// de elementos eliminados.
int my_stack_purge(struct my_stack *stack)
{
	int contador = 0;
	void *data = my_stack_pop(stack);
	while (data)
	{
		contador++;
		free(data); // Liberamos la memoria de los datos de cada nodo
		data = my_stack_pop(stack);
	}
	free(stack);
	return contador;
}