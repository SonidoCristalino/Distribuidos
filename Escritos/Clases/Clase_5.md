
# Sincronismo

## Relojes:

Motivación:
	* Protección de acceso a los recursos compartidos: (para lo que es consistencia y sincronismo) es necesario que el
	  conjunto de máquinas en un sistema distribuido, entienda que hay una hora global para todos, y con ello se resguarda que
	  el dato que se está modificando es posterior a determinado suceso, para que no haya errores a la hora de acceder a
	  determinado dato.
	* Orden de eventos: se requiere que haya un orden para que los nodos puedan sincronizar sus datos en forma conjunta; si el
	  cambio se realiza en los primeros nodos, es necesario que para que haya consistencia de datos, los segundos nodos tomen
	  este dato modificado y lo repliquen en ellos mismos, si los segundos entienden que los primeros terminaron de modificar
	  los datos, entonces existe un problema de consistencia de datos.
	* Los procesos necesitan sincronizarse: los datos requieren ser secuenciales, requieren de cierta secuencialidad.

Los relojes son importantes para que las máquinas puedan sincronizar los eventos que están sucediendo en otros nodos, para darle
un orden.

En una máquina normal, hay un Reloj central, que está asociado al microprocesador, y este último distribuye para los otros
periféricos. No es crítico si se llega a desfasar en hora, no genera conflictos, ya que existe una única referencia horaria.

En cambio,en los sistema distribuidos, existen múltiples relojes (muchos osciladores) por lo que se tienen muchas referencias
horarias distintas. Cada nodo tiene una referencia horaria distinta.

En el ejemplo del MAKE, ¿Cómo sabe que un archivo .c cambió? Porque mira la hora del modificación del archivo y los compara con
los que ya tiene hechos el código objeto.

## Reloj Físico

¿Qué es? Es un reloj de cilicio, ese cristal genera una oscilación periódica, con una frecuencia dada.
El kernel de Linux tiene manejadores que están basados en el timer, de alta velocidad. El contador lo que hace es ir contando
los ticks del procesador, que son los tiempos con los que se va a estar manejando el sistema operativo.

Con un oscilador local, la divergencia de tiempo se soluciona tomando tiempos relativos, es decir que puede bajar la frecuencia
del oscilador e ir "más lento" por lo que estaría retrasándose, pero el retraso siempre es con relación al oscilador local.
En cambio en los sistemas distribuidos, el retraso de tiempo o la baja en frecuencia del oscilador, supone un problema enorme.


# Estabilidad de largo y corto plazo
Cuando se calibra un oscilador se debe establecer el error en frecuencia (la variación de esa frecuencia ) con respecto a la
frecuencia nominal (que es la frecuencia que uno espera), lo cual determina su exactitud.

La estabilidad se expresa por el cambio de frecuencia entro de un intervalo de tiempo dado.
	* Estabilidad de largo plazo: Efecto de deriva, el reloj se va adelantando pero de forma continua.
	* Estabilidad de corto plazo: Fluctuaciones de frecuencias estocásticas (frecuencias aleatorias, ruido blanco o rosado por
	  ejemplo).

# Varianza de Allan:
Se utiliza para medir la calidad de los osciladores. Lo que mide es cuánto se desvía el oscilador de lo que uno esperaría.
Se debe garantizar tener un tiempo total de medición suficientemente grande.

	Permite mostrar 4 ruidos bien delimitados:
		* Ruido de cuantización: el ruido de cuando uno muestrea una señal.
		* Ruido Blanco, es un ruido continuo: es ruido térmico (todo los dispositivos que son resistencias lo tienen).
		* Ruido de Inestabilidad, son variaciones aleatorios de Offset. Esa variación viene dada por cómo está cortado el
		  cristal de cilicio.
		* Angle Random Walk: Drift de error de la señal que se tiene a lo largo del tiempo,

# UTC: Tiempo Universal Coordinado

Buscar UTC:

Se obtiene a partir de la coordinación de distintos relojes atómicos (Tiempo atómico Internacional - TAI)
Correcciones de segundos vacíos que permanece en fase con el movimiento aparente del sol.

# Sistemas de posicionamiento Global:
	- 29 satélites de 20000km.
	- Cada satélite tiene 4 relojes atómicos

# Protocolo de tiempo de Red (NTP)
Los clientes se conecta a un servidor que tiene una base de tiempo sincronizada con algún reloj exacto. El servidor empleará todo
su poder de procesamiento para obtener un tiempo exacto.
Casi todos los sistemas linux tienen este tipo de prácticas, de conectarse con algún servidor que contenga la hora exacta.

	## Algoritmo de sincronización de Relojes
	Se debe tener en cuenta que el Algoritmo tiene determinados lineamientos:
		* No se puede corregir hacia atrás: Esto haría que se rompa el file system de Linux (por esto de los i-nodos y los
		  metadatos), por lo que siempre es para adelante las correciones.
		* Los cambios se deben realizar gradualmente: En caso por ejemplo de si el reloj se debe adelantar 3 minutos, no
		  se realizará un salto de 3 minutos, sino que se irá corrigiendo de a segundos, primero 2, luego otros 2 y así
		  hasta llegar a los 3 minutos.
		* El servidor NTP también ajustará su reloj con el cliente (siempre y cuando el cliente no seal el reloj de
		  referencia).
		* Estrategia de niveles o estratos: cada máquina podrá coordinarse con otra en forma estratificada, es decir que
		  una máquina cliente, podrá hacer de servidora para otras máquinas que le consulten la hora.

# Algoritmo de Berkeley:
Se propuso una forma de ideal, con preceptos donde no hubiera hora UTC y sólo habría que mantener las máquinas sincronizadas.
	Se tiene un demonio (proceso en background) que tiene una hora determinada, y le propaga esta hora a las otras máquinas,
	las demás máquinas le dicen la hora que tiene cada una, y con estas diferencias obtenidas, el demonio hace un promedio de
	tiempo para ajustarse su propia hora como el de las máquinas con las que se conecta.


# Relojes Lógicos:

Lo importante no es que todos los procesos coincidan exactamente en el tiempo,sino que coincidan en el orden en que ocurren los
eventos. Estos algoritmos se conocen como Relojes Lógicos.

El problema que existe es que cada uno de los nodos pueden tener su propio reloj pero con lo que vimos, los relojes al tener
errores propias de su composición física como de su construcción, es muy difícil mantenerlos en coordinación, entonces ¿Cómo se
hace?

## Relojes Lógicos de Lamport:
	Para ello existe lo que se denomina como Relojes lógicos de Lamport. Lo que se propone es que cuando tres procesos se
	comunican y tienen desfazados las frecuencias de sus relojes, siempre que los mensajes de comunicación caigan adelantados,
	no habría problemas (página nº 31 de la filmina); el problema es cuando el mensaje viene atrasado, por lo que se propone
	que a cada proceso que le llega un mensaje atrasado, este último ajuste su reloj, por lo que en promedio, luego de varios
	mensajes enviados entre los 3 procesos, comenzarían a tener EN PROMEDIO frecuencias similares.

	El problema de esto es que si los procesos comienzan a mandar más de un mensaje, es decir que si los mensajes no son
	lineales, sino que se envían varios mensajes y se reciben otros varios, se tiene un problema muy grande.

	Para solucionar esto se tienen los relojes Vectoriales.

	El problema que tienen los relojes de Lamport es que NO CAPTURAN la causalidad.

## Relojes vectoriales
	Capturan lo que es el ORIGEN de los mensajes que se envían entre procesos.
	Lo que se hace es armar un vector de datos, cada proceso va a llevar un vector y un índice de este vector de datos.
		Si V(A) < V(B) entonces se puede deducir que A -> B, es decir que A precede a B

	El vector está conformado tantas partes como procesos se esté comunicando:
		- La información del propio proceso (Proceso nº 1)
		- La información del proceso nº 2
		- La información del proceso nº n...

	A medida que va a pasando el tiempo, cada nodo va teniendo un contador propio, de su propio tiempo.


# Exclusión Mutua:
Para evitar que tales accesos concurrentes corrompan los recursos, o que los vuelvan inconsistentes, se necesita encontrar
soluciones que garanticen que los procesos tengan acceso mutuamente exclusivo.

## Solución Basadas en Token:
	Sólo hay un token disponible, y quien lo tenga puede acceder al recurso compartido. Cuando termina, el token pasa al
	siguiente proceso. Si un proceso tiene el token pero no está interesado en acceder al recurso, simplemente lo pasa.

	Lo que tienen de positivos este tipo de soluciones es que evitan la inanición (es decir, donde un proceso constantemente
	le niega un recurso a otro proceso), ya que garantiza que cada uno de los procesos tendrá la oportunidad de acceder a los
	recursos compartidos.
	También evita el interbloqueo (donde diversos procesos se esperan unos a otros para continuar) de manera fácil.

	# Desventajas:
		- El problema que tiene es que cuando falla el token (por una falla del proceso que lo tiene en su poder) es muy
		  costoso volver a crear otro token, se vuelve un proceso intrincado.
		- *Esto se puede solucionar con sistemas de Acknowledge (ACKs)*

	Otra alternativa basada en token, es que el proceso que requiera tomar un recurso, necesite de la aprobación de los demás.

## Algoritmo centralizado
	Se trata de emular un sistema de único procesador en un sistema distribuido, por lo que se elige un proceso como
	coordinador. Cuando un proceso quiere acceder a un recurso, manda una solicitud al coordinador solicitándolo, si no hay
	otro proceso operando con ese recurso, entonces el coordinador accede a la petición.
	En cambio, si existe previamente otro proceso utilizando ese recurso, lo que se hace es negarle el acceso (aunque los
	métodos pueden diferir dependiendo del sistema).

	Cuando el proceso deja de utilizar el recurso, envía un mensaje al coordinador para que libere el acceso. El coordinador
	permitirá el acceso al primero que tenga en cola de espera. Esto garantiza que las peticiones sean autorizadas en el orden
	en que se reciben; ningún proceso espera por siempre.
	Este tipo de operación es de fácil implementación ya que se requiere para ello sólo 3 mensajes (petición, autorización y
	liberación).

	# Desventajas:
		- También tiene fallas, ya que el coordinador sería un único punto de falla.
		- En sistemas grandes, un único coordinador puede volverse un cuello de botella.

## Algoritmo decentralizado:
	Tener un sólo coordinador es un mal método, por lo que para implementarse en un decentralizado, por cada recurso replicado
	n veces, tendrá su propio coordinador para ontrolar el acceso de procesos concurrentes.

	Cuando un proceso quiere ganar un recurso, debe ir a votación y ganar por mayoría. En caso de no obtener el recurso, en
	este caso SI se le envía un mensaje avisando que el recurso está ocupado (a diferencia del centralizado).

	# Desventaja
		- No previene la inanición, y tiene una baja eficiencia.

## Algoritmo Distribuido:

	Cuando un proceso quiere acceder a un recurso compartido, lo que hace es confeccionar un mensaje que contiene:
		- El recurso a utilizar
		- El nº del proceso que quiere utilizarlo
		- Su tiempo actual lógico (la hora)
	Este mensaje se envía a los demás procesos incluyéndose.

	Los procesos pueden responder:
		- Si no accede al recurso y no va a acceder, envía OK
		- Si ya tiene acceso al recurso, no contesta y coloca la petición en cola.
		- Si también quiere acceder al recurso, compara su tiempo con el proceso que envió la petición y el mayor gana.

	# Desventaja:
		- El problema que tiene es que insumen muchos mensajes.
		- Se tienen tantos puntos de falla como procesos haya. Si falla uno de los procesos, al no contestar se toma como
		  que el recurso está ocupado por lo que falla todo el sistema
		- Para Implementar este tipo de algoritmo se requiere multitransmisión

# Posicionamiento Global de Nodos:
	Para calcular la distancia entre A y B, lo que se hace es mensurar la latencia entre ellos dos. Esto se utiliza para
	localizar servidores de sitios web, ubicación de réplicas o enrutamiento bajo IP.

	Cada nodo puede calcular sus propias coordenadas aplicando Pitágoras.
	Las distancias medidas por diferentes nodos, no son consistentes.


# Algoritmos de elección:
	Muchos algoritmos distribuidos requieren que un proceso actúe como coordinador, iniciador, o que represente algún papel en
	especial. En general, no importa qué proceso tenga esta responsabilidad especial, pero alguno tiene que realizarla

	Lo importante es que si falla el coordinador,automáticamente debe nombrarse otro.

	Para seleccionar el proceso que actuará como coordinador será eligiendo números más grandes (como puede ser su dirección
	de red). Los algoritmos difieren en la forma en que efectúan la localización.

	Se supone que los procesos conocen el número de los demás procesos, pero no saben si están aumentando o disminuyendo.

## Algoritmo del Abusón:
	Un proceso P comienza el proceso de elección:
		- El mensaje de elección se envía a todos los procesos con números superiores a él.
		- Si ninguno responde, P queda como coordinador.
		- Si alguno de esos procesos superiores responde, entonces toma el mando.

	Si contesta un proceso que antes había fallado (que no había contestado a la elección) y tiene el número más grande,
	entonces asume el trabajo de coordinador.

	Para implementarlo se requieren 3 tipos de mensajes:
		- Elección: anuncia un proceso de elección
		- Respuesta: respuesta de un mensaje de elección
		- Coordinador: anuncia la identidad del proceso elegido.

# Algoritmo del anillo:
	 No utiliza token. Los procesos se suponen que están ordenados, por lo que cada uno sabe cuál es su sucesor. Cuando el
	 coordinador no funciona, entonces envía un mensaje de tipo ELECCION, que tiene su propio número de proceso a su sucesor.
	 Si no encuentra el sucesor, entonces lo saltea y sigue con la cadana. Cada uno de los procesos agrega su propio número a
	 la lista que va pasando entre sucesores.

	 Una vez que llega al proceso que inició la elección, el mensaje cambia a COORDINADOR y lo hace circular nuevamente para
	 informar quién es el coordinador (el de mayor número de proceso) y cuáles son los miembros del nuevo anillo. Una vez
	 realizado esto, todos se ponen a trabajar.
