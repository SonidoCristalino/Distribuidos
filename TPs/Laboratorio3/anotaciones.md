
# Configuración personal:

	- NodoMaestro:
		Tipo de servicio: Servidor
		IP: 192.168.100.22

	- blockEsclavo (modificarle los archivos):
		Tipo de servicio: Cliente
		IP: 192.168.100.26

	- Navegador web:
		Se ingresa: 192.168.100.26:5000
		Se ingresa cualquier contenido, luego el nombre y se presiona "post".
		Nos lleva a la página del servidor donde se nos indica que fue minado el contenido enviado.
		Volvemos a la página principal donde presionamos Resync
		Aparece el minado


# Máquina de Cristian:

Primero iniciar la máquina 3 (la nueva), luego re apuntar la máquina 2 (front-end)

	- Servidor nº 1 (máquina nº 1):
	  	IP: 192.168.1.33:8000

	- Cliente nº 1 (máquina nº 2):
	  	IP: 192.168.1.36:8001

	- Servidor nº 2 (máquina nº 3):
	  	IP: 192.168.1.39:8001
	- Comando para lanzar (en la máquina nº 3)
	  	flask run --port 8001 --host=0.0.0.0


# Según el audio de Cristian (30/11/):

	1) Levantar la máquina nº 1 como Servidor_1
	2) Levantar la máquina nº 2 como Cliente
	3) Minar desde la página web para que quede un registro
	4) Levantar la máquina nº 3 como Servidor_2
	5) Se abre otra terminal en la máquina nº 3 (alt+f2) y se registra este nuevo nodo con CURL
		Tiene que tener la IP de la máquina 1 y la IP de la máquina 2, sirve para registrar el contenido de la IP nº 1 en
		el nº 2.
	6) Se baja el Cliente y se modifica el archivo view.py apuntando a la máquina nº 3
	7) Se vuelve a iniciar el cliente apuntando a la máquina nº 3
	8) Se baja el Servidor nº 1
	9) Se actualiza la página web para que vea que sigue en pie el sistema distribuido
	10) Se mina nuevamente para que la información siga siendo consistente

