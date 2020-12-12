#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX_NUM_THREADS 16
#define MAX_SIZE 2000

int size; /*tamaño de los vectores*/
int numThreads; /*numero de hilos*/
int a[MAX_SIZE], b[MAX_SIZE], c[MAX_SIZE];

int main(int argc, char* argv[]){

	int i;
        if (argc < 3){
	printf("Faltan parametros\n");
	return 0;
	}
	/*Lee parámetros de la línea de comando*/
	size = atoi(argv[1]);
	size = (size < MAX_SIZE ? size : MAX_SIZE);
	numThreads = atoi(argv[2]);
	numThreads = (numThreads < MAX_NUM_THREADS ? numThreads : MAX_NUM_THREADS);

	/* Inicializa vector */
	for (i= 0; i < size; i++){
		a[i]=i+1;
		b[i]=i+1;
		c[i]=0;

	}

	#pragma omp parallel default(none) private(i) shared(a,b,c,size) num_threads(numThreads)
	{
		#pragma omp for schedule(static)
		for(i=0; i<size; i++)
			c[i] = a[i] + b[i];
	printf("Openmp\n");
	}
	printf("El resultado es %d\n",c[1]);
	return 0;

}
