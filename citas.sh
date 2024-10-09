#!/bin/bash

#Primera prueba evaluable

case $1 in
-f)
;;
-a)
;;
-d)
;;
-id)
;;
-n)
;;
-i)
;;

-h)	#Ayuda en la salida estandar

	echo  "--------------------------------------------------------------------------------"
	echo  "|                                  FUNCION DE AYUDA                            |"
	echo  "--------------------------------------------------------------------------------"

	echo -e "--------------------------------------------------------------------------------"
	echo -e "|Opcion -f (citas.sh -f)  : Muestra el contenido del fichero.                  |"
	echo -e "|Opcion -a (citas.sh -a)  : Anade una cita por hora inicio, fin y nombre       |"
	echo -e "|Opcion -d (citas.sh -d)  : Lista las citas del dia introducido                |"
	echo -e "|Opcion -id (citas.sh -id): Muestra una cita por su identificador              |"
	echo -e "|Opcion -n (citas.sh -n)  : Muestra una cita por el nombre del paciente        |"
    echo -e "|Opcion -i (citas.sh -i)  : Muestra todas las citas según una hora de inicio   |"
	echo -e "--------------------------------------------------------------------------------"
;;
	esac