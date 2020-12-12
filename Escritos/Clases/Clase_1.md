# Sistemas distribuidos
# Profesor:
	Eduardo Kunitkz ( o algo así )

Todo está en la clase 0:
    Tanenbaum "Sistemas Distribuidos"
    Distributed System, Colorius

# Link para bibliografía:
    En el campus

# Evaluación:
    - 3 TP con defensa oral.
    - Hay que entregarlo cada 3 o 4 semanas.
    - La materia se puede promocionar de una, pero se tiene que aprobar todo.
    - Los TP tienen que ser todo en tiempo y horario.

Siempre lo utilizamos como usuarios finales.
Hay que entender por qué está hecho así, la arquitectura, la forma que tiene, etc.
Permite entende rdesde adentro cómo está diseñado, tenemos cierta libertad extra, capciadad extra para DISEÑAR el sistema.
Distintos tipos de sistempas distribuidos.

Equipos antiguos caros, en los años 1940, memoria microperforada, cocidas a tela, etc. SIstemas caros desentralizados, únicos,
todavía no se enentedía el concepto de interconectar
La computadora hogareña abarata los costos, accesible para todos, X86, conectividad mínima, pero no era una conectividad fuerte.
Accesorios eran cosas dedicadas para determinados equipos. Fines de los 80 conexión entre máquinas, conexión de redes.
Los sitemas distribuidos aparecen cuando llega internet y tiene una velocidad de comunicación muy alta. Hace que el sistema sea
transparente para el usuario. Tranpsarpencia es CENTRAL para este tema.

SD = Sistrma distribuido.
Equipos interconectados entre si, con muchos periféricos a los que se conectan y pueden ser, impresoras, BD, teléfonos celulares,
etc. Los dispositovos pueden ser equipos heterogeneos, un celulra, una computadora, un chip de un aire acondicionado, heladeras,
televisores, etc.

Dispositivos interneocnetando que conectado a internet y da un servicio.

# Ejemplo de SD:
    Industrias distribuidas (como las productoras de autos). Field bus, redes de alta confiabilidad, se onecta desde españa y
    puede ver la productividad de la fábrica de arngeinta por ejemplo.

    Sistemas vehículares: un auto tiene una red central que tiene conectado distitnas computadoras pequeñas que son
    microcontroladores y están conectados a una computadora central; sistema ABS tiene su propio microontrolador que le da
    información a la ocmputadora central.

    Satelites distribuidos: proveen internet a todo el mundo. Plagado de satelites girando alrededor del planteta. Costos
    amigables para todos, competitivos. Fin de este año todo USA y Europa y para el otro, a todo el planeta. Transmisión de datos
    con distintos sismteas distribuidos tanto en el espacio como en la tierra, tienen conexión.


Tanenmabum:
    Colección de computadoras independientes que dan al usuario la impresión de constituri un único sistema coherente. Hace
    hincapié en la transparencia.

Colorius:
    hincapié en el diseño "la forma es a partir de paso de mensajes". Memoria compartida y paso de mensajes, esas dos formas de
    comnuicación. La memoria compartida NO se puede tener en SD, sino la única forma de comunicación es por paso de mensajes. La
    comunicación a partir de paso de mensajes.

Lamport:
    Hincapie en la torleancia a fallas; SD tiene la capacidad de que cada equipo sea independiente y redundancia de información,
    redundancia de los caminos de acceso, por lo tanto tienen mucha redundancia.
    Si alguno de esos equipos cae, hay una PEQUEÑA degradación del sistema, SD son totalmente tolerancias a fallos.

Multiples ordenadores compartidos => se desea transparencia

# Varios campos de aplicación: (en la filmina).
    - Meteorología es el campo donde se usó desde el comienzo.
    - Google por ejemplo, todo intercomunicado en distintos lugares del planeta. Para manera estos Sistemas distribuidos tienen
    sistema Google File Sistema, que soporta grandes cantidades de información. Los archivos de GFS y tienen varios Teras cado,
    que tiene varisa computadoras entre si, el archivo está particionado entre distintos equipos, replicados y todos tienen
    coherencia. Infraestructura tremenda.

	- Juegos ONLINE tiene muchos datos infernales y al mismo tiempo los datos tienen que ser consistentes, todo tiene que ser
	  inmediato; desde el poder de cómputo es muy exigentes.

Computación de Alta Performance vs Procesmianeto masivo de datos.

Big data: procesar muchos datos, extraer información de muchos datos.

[Se hace un repaso de más ejemplos de SD: NEESGrid, telescopio global, Red de investigación, etc]

# Aspectos centrales:
Varias computadoras independientes (no sólo de escritorio, celulares, dispositivos embebidos, etc). Tiene cierta capacidad, de
tener una interfaz intermedia MIDLEWARE (hace la magia de la transparencia, es el que hace que todo se comporte como dice
Tanembaum, entre el usuario y todas las demás computadoras). El SO local de cada máquina NO interesa. Por debajo de este SO hay
red y el hardware de base para cada SO, que estas dos cosas no nos interesan mientras que el MIDLEWARE funcione y nos lo haga
transparante.

# Objetivos del SD:
    Disponibilidad de Recursos: Simplificar los usuarios el acceso a otros equipos remotos o a sus dispositivos. Disponibildad de
    recursos: datos, archivos, sensores, impresoras, etc.
    Al aumentar la conectividad entre todos aumenta también la seguridad.

    Transparencia: Ocultar el usuario qué hay detrás de todo esto, debe sentir que es un solo programa y que trabaja para él solo.
    HTML es una especie de MidleWare.
    Es lo más complejo de alcanzar.

    Dos niveles: de usuario y de programador (tener una API que permita acceder al sistema como a un todo)
        Tiene varios tipos:
            Acceso
		- ubicación: se oculta la localización del recurso. No importa dónde está el dispositivo
            	- Migración: oculta que que el recurso pudiera moverse a otra ubicación,
		- Reubicación: oculta que que el recurso pudiera moverse a otra ubicación mientras está en uso. Amazón lo maneja,
		  como las IP elásticas. Se tiene un servicio en la nube, se quiere probar el nuevo servicio en una IP nueva, se
		  prueba y cuando está todo OK, se cambia la vieja IP a la nueva y para el usuario es tranparente.
            - Replicación: Oculta el número de copias de un recurso
            - Concurrencia: Cantidad de uusairos que uqieren acceder al SD. Para leer no hay proeblama, el problema es cuando se quiere escribir.
            - Falla: ocultar la falla. Si se produce, el sistema lo que debe hacer es recuperse solo.

    Sistemas abiertos: Un sistema deben poder interactuar con otros sistemas sin importar el ambiente subyacente. Para esto
    aparecen las interfaces que se llaman IDL (lenguaje de definiciones de interfaz).

    Escalabilidad: es escalable si se mantiene efectivo cuando hya un incremento significativo en la cantida de recursos y usuarios.
        Se mide en tres dimensiones (están en la filmina).
        Minimizar la latencia

        Ver las técnicas de la escalabilidad, la parte del cliente y el servidor
        Ver los dominios IP.

        Una de las técnicas es que haya mucha replicación ¡pero todos los datos tiene que ser CONSISTENTES!

# Heterogeneidad:
    Seguridad
    Manejo de Errores: Tolerancia a Fallos, recuperación frente a fallos, Redundancia.

