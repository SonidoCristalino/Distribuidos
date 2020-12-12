
# Clase nº 7:
Consistencia: Mantenimiento de copias de la información en múltiples computadoras. Esto puede ser por redundancia de datos, por
necesidad de movilidad, etc.

Los recursos que se utiliza en los SD son:
	- Servidores Web
	- DNS
	- Google data centers: todo lo de google se guardan en distintos servidores, y se replican para tener redundancia o sólo
	  por tener un acceso más cercano a la zona que se la requiera.

Ayuda a mejorar los Sistemas Distribuidos:
	- Mejora el rendimiento
	- Alta disponibilidad
	- Tolerancia fallos: robustes a la falla, sino también darle robustes para recuperarse ante la falla.
	- Mejorar el balance de carga: si se tienen muchos usuarios tratando de acceder al mismo dato, en este caso los usuarios
	  acceden sin saberlo a distintas máquinas.

 # Mejora el rendimiento
 A través de chaché de clientes, mejoran el acceso rápido. Reduce el costo de llamadas idénticas.

 # Alta disponibilidad:
 El tiempo que un servicio está accesible con tiempos de respuesta razonables debe ser cercana al 100%.

 Fallos en un servidor
 	Disponibilidad 1-p^n


# Tolerancia de fallas
	Una alta disponibiliad no implica necesariamente corrección

Requisitos:
	Replicación se debe llevar a cabo teniendo en cuenta:
		- Transparencia: lso clientes no se pueden dar cuenta de esto
			Existen recursos lógicos individuales.
		- Consistencia: Sincronizar datos. Operaciones sobre un conjunto replicado deben dar resultados sigan siendo igual
		  como si fuera 1.
			Puede ser más o menos estricta según la aplicación

# Modelo de consistencia centrada en datos
	Continua: La más flexible de todas. Cuando existe un cierto grado de tolerancia entre valor real y la réplica (ej: clima,
	valor de la bolsa).
	Conit: es la unidad con la que se medirá la consistencia.

Minuto 26
















