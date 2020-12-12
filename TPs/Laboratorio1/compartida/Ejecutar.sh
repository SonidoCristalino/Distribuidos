#!/bin/sh

# Propósito:
# 	ejecutar MPI pero haciendo un refresco de la pantalla
# 	Input nº 1: Directorio a buscar
# 	Input nº 2: Palabra clave a buscar en los PDF

if [ $# -ne 2 ]; then

	echo "Se requieren dos parametros "
	exit 10

else

	clear
	nombreEjecutable="$1"
	procesos="$2"

	mpiexec -f host -n "$2" ./"$1" | less

fi

# =========================================================================================================

# 	nombreCodigo="$1.c"
# 	nProcesos="$2"

# 	directorio_mnt="../mnt/"


# 	if [ -d "$directorio_mnt" ]; then

# 		# Hacemos un clear screeen
# 		clear

# 		# Copiamos el archivo a utilizar en el directorio compartido
# 		cp "$directorio_mnt$nombreCodigo" .

# 		# echo "$directorio_mnt$nombreCodigo" .

# 		if [ $? -eq 0 ]; then

# 			# Si sale bien, procedemos a compilar el archivo
# 			mpicc "$NombreCodigo" -o "$1"

# 			if [ $? -eq 0]; then

# 				# Si compila correctamente, procedemos a ejecutar el proceso en el cluster
# 				mpiexec -f host -n "$2" ./"$1" | less
# 			else
# 				# Error de compilacion
# 				echo "Error al copiar el directorio. Codigo: $?"
# 			fi

# 		else
# 			# Error en la copia de archivos
# 			echo "Error al copiar el directorio. Codigo: $?"
# 		fi

# 	else

# 		echo "El directorio $directorio NO existe o contiene un error"
# 		exit 10

# 	fi

