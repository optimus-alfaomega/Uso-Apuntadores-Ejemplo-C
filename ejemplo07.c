/* 
 * C BY 8 EXAMPLES
 * example07.c: arrays y memoria dinámica
 * 
 * Copyright (C) 2019 Ignacio Pérez Hurtado de Mendoza
 * http://www.cs.us.es/~ignacio
 * Copyright (C) 2020 Miguel Ángel Martínez del Amor
 * http://www.cs.us.es/~mdelamor
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h> // para funciones rand, malloc, realloc, calloc y free
#include <time.h> // para time
#include <string.h> // para memset

// TIPOS
typedef struct {
	double x;
	double y;
} PUNTO;

// A veces necesitamos dimensionar arrays en tiempo de ejecución,
// por ejemplo porque el tamaño no lo sabemos hasta que nos lo diga
// el usuario, lo leamos de un fichero o lo calcule una función.
// Para ello usaremos memoria dinámica, esto se hace mediante 
// las funciones malloc, realloc, calloc y free

void imprimePunto(PUNTO* a);

PUNTO* reservaMemoria(int n);

int main()
{
	int n;
	PUNTO* puntos = NULL; 
	// puntero para almacenar un array de puntos que crearemos de forma
	// dinámica, obteniendo su dimensión en tiempo de ejecución.
		
	printf("Cuantos puntos quieres? ");
	scanf("%d",&n);
	
	puntos = (PUNTO*) malloc(n * sizeof(PUNTO));
	
	// malloc sirve para reservar memoria, devuelve un puntero y es
	// necesario hacer un casting al tipo de puntero, ya que malloc
	// por defecto devuelve void* (puntero sin tipo, be void* my friend).
	// Como argumento debe recibir el NUMERO DE BYTES que se desean 
	// reservar. Para ello utilizaremos habitualmente la expresión 
	// n*sizeof(tipo). Por tanto, la sintaxis de malloc es:

	// tipo* p = (tipo*) malloc(N * sizeof(tipo));
	
	srand(time(NULL));
	for (int i=0;i<n;i++) {
		puntos[i].x = rand() % 16;
		puntos[i].y = rand() % 16;
		printf("Punto %d: ",i+1);
		imprimePunto(puntos+i);
		printf("\n");
	}
	printf("-------------------\n");

	// menos utilizado es el calloc y realloc

	// calloc tiene una funcionalidad parecida a malloc, salvo que inicializa a 0
	
	PUNTO* masPuntos = (PUNTO*) calloc(n,sizeof(PUNTO)); // obsérvese que recibe 2 argumentos en lugar de 1
	
	for (int i=0;i<n;i++) {
		imprimePunto(&masPuntos[i]);
		printf("\n");
		
	}
	
	// realloc servirá para redimensionar memoria reservada previamente
	
	masPuntos = (PUNTO*) realloc(masPuntos, 4*n*sizeof(PUNTO)); 
	
	// La memoria creada con malloc, calloc o realloc es persistente en el programa, se podria escribir 
	// una función que devuelva un puntero generado con malloc, calloc o realloc y no habría problema
	// de violación de segmento. De hecho es una práctica habitual inicializar punteros de memoria
	// dinámica en funciones y devolverlos
	
	PUNTO* aunMasPuntos = reservaMemoria(n); // elegante y seguro
	
	// MUY IMPORTANTE
	
	// Ya que la memoria reservada con malloc, calloc y realloc permanece, hay que LIBERAR MEMORIA cuando
	// ya no se necesiten las variables (aunque sea al final del programa, es buena costumbre).
	// C no dispone de "recolector de basura" como otros lenguajes tales como Java y es responsabilidad
	// del programador liberar la memoria que no se necesita. A cambio se obtiene una mayor eficiencia,
	// sobre todo si se minimiza el uso de malloc y free, reservando de una vez la memoria que haga falta.
		
	free(puntos);
	free(masPuntos);
	free(aunMasPuntos);
	
	return 0;
}


void imprimePunto(PUNTO* a) {
	printf("(%lf,%lf)",a->x,a->y);
}

PUNTO* reservaMemoria(int n)
{
	// reserva la memoria
	PUNTO* v = (PUNTO*)malloc(n*sizeof(PUNTO));
	// inicializa a 0 todas las posiciones de memoria con memset (se puede usar para 
	// inicializar a otro valor)
	memset(v,0,n*sizeof(PUNTO));
	// Devolvemos el puntero. Esta vez es memoria dinámica, y no depende
	// de la función, así que este puntero es válido.
	return v;
}
