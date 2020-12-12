#include "mpi.h"
#include <math.h>
#include <stdio.h>

/* El programa main recibe dos argumentos:
	* la cantidad de argumentos que se le pasa
	* un vector a los parámetros, para que pueda accederlos */

int main(int argc, char *argv[]) {

    int done = 0, n, myid, numprocs, i, namelen;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    char nombre_procesador[MPI_MAX_PROCESSOR_NAME];

    /* Se inicializa el entorno de ejecucion para MPI.
    Requiere un puntero a la cantidad de argumentos y otro punteo al vector de argumentos
    (siendo ambos los parametros de main */
    MPI_Init(&argc,&argv);

    /* Determina el tamanio del grupo de los nodos asociados con el programa main
	INPUT: Recibe el parametro de entrada que vendria a ser el controlador de seniales
	OUTPUT: numero de los proceso en el grupo del controlador de seniales */

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    /* Determina el rango del proceso de llamada en el controlador de seniales
	INPUT: recibe el controlador de seniales
	OUTPUT: el rango del proceso de llamada el el grupo del controlador de seniales */

    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    MPI_Get_processor_name(nombre_procesador, &namelen);

    /* Se ejecuta mientras n sea distinto de cero */
    while (!done) {

	if (myid == 0) {
	    printf("Ingrese el numero de intervalos para calcular pi: (0 para salir) ");
	    scanf("%d",&n);
	}

	/* Transmite un mensaje del proceso con rango superusuario a todos los demás procesos del comunicador */
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	/* Si el valor n es igual a cero, entonces el proceso finaliza */
	if (n == 0) break;

	h   = 1.0 / (double) n;
	sum = 0.0;

	for (i = myid + 1; i <= n; i += numprocs) {
	    x = h * ((double)i - 0.5);
	    sum += 4.0 / (1.0 + x*x);
	}

	mypi = h * sum;

	/* Reduce los valores de todos los procesos a un solo valor */
	MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);

	/* fabs permite obtener el valor absoluto de un numero flotante */
	if (myid == 0)
	    printf("pi es aproximadamente: %.16f, siendo el porcentaje de error: %.16f\n",
		   pi, fabs(pi - PI25DT));
    }

    /* Finaliza la entorno de ejecución MPI */
    MPI_Finalize();
    return 0;
}
