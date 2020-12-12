
Lo que se hizo fue agregar al usuario Linuxtest al grupo Sudo:
https://linoxide.com/linux-how-to/add-user-to-sudoers-on-debian/
	usermod -aG sudo linuxtest

Se modificó para el root el editor del visudo para que tome Vim:
	https://askubuntu.com/questions/531184/change-the-default-editor-when-sudo-visudo

Cambiamos el nombre de la máquina para que en las capturas sea evidente qué máquina es:
	https://www.tecmint.com/set-hostname-permanently-in-linux/

	$ sudo hostnamectl set-hostname NEW_HOSTNAME

# Configuración NTP
	- Lo que queda pendiente es modificar el archivo de configuración de NTP y ponerlo a andar
	- Falta la conclusión

