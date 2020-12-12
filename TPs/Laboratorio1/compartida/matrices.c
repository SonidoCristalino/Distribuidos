/******************************************************************************
 * ARCHIVO: matrices.c
 * DESCRIPCION: Multiplicacion por Matrices - Implementado en Lenguaje C
 *	El nodo Maestro distribuye las operaciones para multiplicar las matrices.
 *	Las tareas se separan segun la cantidad de clusters asignados para la
 *	paralelizacion, que sera siempre n-1
 * AUTOR: Blaise Barney. Adaptado por Emiliano Salvatori
 * FECHA: 01/10/2020
 ******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define NCA 10 			/* Numero de Columnas en la Matriz A */
#define NFA 5                 /* Numero de Filas en la Matriz A <--*/
#define NCB 5                  /* Numero de Columnas en la Matriz B <-- */
#define MAESTRO 0               /* ID para la primer tarea */
#define DEL_MAESTRO 1          /* Se configura un tipo de mensaje del nodo maestro*/
#define DEL_NODO 2          /* Se configura un tipo de mensaje de los nodos*/

int main (int argc, char *argv[]) {

	int	numtareas,             /* Numero de tareas en ejecucion */
		taskid,                /* Identificador de las tareas */
		numprocesos,           /* Numero de procesadores que tomaran la tarea*/
		origen,                /* Id de la tarea segun el mensaje de origen */
		dest,                  /* Id de la tarea segun el mensaje destino */
		menstipo,              /* Tipo de mensaje */
		filas,                 /* Numero de filas de A enviadas a cada nodo */
		averow, extra, offset, /* Determina la cantidad de filas para cada nodo */
		i, j, k, rc;           /* Contadores */
	double	a[NFA][NCA],           /* Matriz A que sera multiplicada */
		b[NCA][NCB],           /* Matriz B que sera multiplicada */
		c[NFA][NCB];           /* Resultado de la matriz C */

	/* Permite instanciar una estructura que contiene informacion del mensaje enviado */
	MPI_Status status;

	/* Se inicializa el entorno de ejecucion para MPI. */
	MPI_Init(&argc,&argv);

	/* Determina el rango del proceso de llamada en el controlador de seniales
	INPUT: recibe el controlador de seniales
	OUTPUT: el rango del proceso de llamada el el grupo del controlador de seniales */
	MPI_Comm_rank(MPI_COMM_WORLD,&taskid);


	/* Determina el tamanio del grupo de los nodos asociados con el programa main
	INPUT: Recibe el parametro de entrada que vendria a ser el controlador de seniales
	OUTPUT: numero de los proceso en el grupo del controlador de seniales */
	MPI_Comm_size(MPI_COMM_WORLD,&numtareas);

	/* En caso que el numero de procesadores a ejecutar sea menor a 2, entonces abortar */
	if (numtareas < 2 ) {
		printf("Se requieren al menos 2 procesos para ejecutar el programa. Abortando...\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
		exit(1);
	}

	numprocesos = numtareas-1;

	/**************************** Proceso Maestro ************************************/

	if (taskid == MAESTRO) {

		printf("\n");
		printf("Se inicia MPI con un numero de %d de procesos.\n",numtareas);

		for (i=0; i<NFA; i++)
			for (j=0; j<NCA; j++)
				a[i][j]= i+j;
		for (i=0; i<NCA; i++)
			for (j=0; j<NCB; j++)
				b[i][j]= i*j;


		/* Se tratan de imprimir los datos por pantalla de las matrices */

		printf("\n");
		printf("Dimensiones de Matriz A: \t%dx%d\n",NFA, NCA);
		printf("Contenido de la Matriz A de :\n");

		for (i=0; i<NFA; i++){
			printf("\n");
			for (j=0; j<NCA; j++){
				a[i][j]= i+j;
				printf("%6.1f\t", a[i][j]);
			}
		}

		printf("\n");
		printf("\n");
		printf("Dimensiones de Matriz B: \t%dx%d\n",NCA, NCB);
		printf("Contenido de la Matriz B de :\n");

		for (i=0; i<NCA; i++){
			printf("\n");
			for (j=0; j<NCB; j++){
				b[i][j]= i*j;
				printf("%6.1f\t", b[i][j]);
			}
		}

		printf("\n");
		printf("\n");
		printf("******************************************************\n");
		printf("Estatus de la paralelizacion: \n");

		/* Se envia los datos de la matriz a los nodos */

		averow = NFA/numprocesos;
		extra = NFA%numprocesos;
		offset = 0;
		menstipo = DEL_MAESTRO;

		printf("\n");
		for (dest=1; dest<=numprocesos; dest++) {

			filas = (dest <= extra) ? averow+1 : averow;
			printf("Enviando %d filas al proceso nº %d offset=%d\n",filas,dest,offset);
			MPI_Send(&offset, 1, MPI_INT, dest, menstipo, MPI_COMM_WORLD);
			MPI_Send(&filas, 1, MPI_INT, dest, menstipo, MPI_COMM_WORLD);
			MPI_Send(&a[offset][0], filas*NCA, MPI_DOUBLE, dest, menstipo,
					MPI_COMM_WORLD);
			MPI_Send(&b, NCA*NCB, MPI_DOUBLE, dest, menstipo, MPI_COMM_WORLD);
			offset = offset + filas;
		}

		/* Se recibe los resultados de los nodos */

		menstipo = DEL_NODO;
		for (i=1; i<=numprocesos; i++) {

			origen = i;
			MPI_Recv(&offset, 1, MPI_INT, origen, menstipo, MPI_COMM_WORLD, &status);
			MPI_Recv(&filas, 1, MPI_INT, origen, menstipo, MPI_COMM_WORLD, &status);
			MPI_Recv(&c[offset][0], filas*NCB, MPI_DOUBLE, origen, menstipo,
					MPI_COMM_WORLD, &status);
			printf("Recibiendo resultado del proceso numero: %d\n",origen);
		}

		/* Se imprimen resultados */
		printf("\n");
		printf("******************************************************\n");
		printf("Resultado de la Matriz C de %dx%d:\n",NFA, NCB);

		for (i=0; i<NFA; i++) {
			printf("\n");
			for (j=0; j<NCB; j++)
				/* printf("%6.2f\t", c[i][j]); */
				printf("%6.1f\t", c[i][j]);
		}

		printf("\n");
		printf("\n******************************************************\n");
		printf ("Finalizado.\n");
		printf("\n");
	}

	/**************************** Nodos Esclavos ************************************/

	if (taskid > MAESTRO) {

		menstipo = DEL_MAESTRO;
		MPI_Recv(&offset, 1, MPI_INT, MAESTRO, menstipo, MPI_COMM_WORLD, &status);
		MPI_Recv(&filas, 1, MPI_INT, MAESTRO, menstipo, MPI_COMM_WORLD, &status);
		MPI_Recv(&a, filas*NCA, MPI_DOUBLE, MAESTRO, menstipo, MPI_COMM_WORLD, &status);
		MPI_Recv(&b, NCA*NCB, MPI_DOUBLE, MAESTRO, menstipo, MPI_COMM_WORLD, &status);

		for (k=0; k<NCB; k++)
			for (i=0; i<filas; i++) {
				c[i][k] = 0.0;
				for (j=0; j<NCA; j++)
					c[i][k] = c[i][k] + a[i][j] * b[j][k];
			}

		menstipo = DEL_NODO;

		MPI_Send(&offset, 1, MPI_INT, MAESTRO, menstipo, MPI_COMM_WORLD);
		MPI_Send(&filas, 1, MPI_INT, MAESTRO, menstipo, MPI_COMM_WORLD);
		MPI_Send(&c, filas*NCB, MPI_DOUBLE, MAESTRO, menstipo, MPI_COMM_WORLD);
	}

	/* Finaliza la entorno de ejecucion MPI */
	MPI_Finalize();
}
