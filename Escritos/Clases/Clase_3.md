# Clase nº 3

# Diferencia entre Sistemas:
Sistemas operativos: Los procesos se va a concetrar en la administración y el Scheduler.
En Sistemas Distribuidos lo que se va a estar mirando la relación de Cliente-Servidor, y el uso de hilos.
	Los datos son en paralelo, por lo que se hace un poco más lento.

	Cuando se tiene un servidor, se virtualiza máquinas, que dentro tiene contenedores, que se ejecutan por SEPARADO, por lo
	que la falla en un contendor, no significa que se filtre hacia el otro. No comparten memoria entre ellos.

	Aislación de fallas, se pueden migrar si es que se cae, y se puede llevar a otro lado de forma caliente.

# Hilos en Sistemas Distribuidos
	* Todos los hilos comparten el mismo espacio de direcciones, por lo que el cambio de contexto entre hilos sea
	  independiente del SO.
	* La creación y destrucción de hilos es menos costosa.
	* La performance de un programa ejecutandose entre hilos, será mucho mayor que si se ejecutan en uno solo.

La parte difícil es programar en función de hilos.

Los hilos a nivel de kernel son más lentos.
Si un hilo de kernel se trava,entonces trava al kernel. Por lo que se hace es encapsularlos, para ejecutarse de forma más
amigable, se denominan LWP (procesos de peso ligero).

Los hilos son convenientes para permitir llamadas de bloqueo sin bloquear todo el proceso en el que se ejecuta el hilo.
En los SD son atractivos para expresar la comunicación mediante múltiples conexiones lógicas.

Si queremos que el usuario sienta que está avanzando lo que solicita
