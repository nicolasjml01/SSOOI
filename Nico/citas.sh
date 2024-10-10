#!/bin/bash

#Primera prueba evaluable

# Función para mostrar la ayuda del programa
function mostrarAyuda {
    echo "Uso: ./citas.sh [opciones]"
    echo ""
    echo "Opciones:"
    echo "  -f datos.txt                     Muestra el contenido del fichero de citas."
    echo "  -a                               Añade una cita."
	echo "  -d <día_mes_año>                 Lista todas las citas de un día específico."
    echo "  -id <identificador>              Muestra una cita según su identificador."
	echo "  -n <Nombre del paciente>         Especifica el nombre del paciente para añadir o buscar citas."
    echo "  -i <Hora inicio>                 Especifica la hora de inicio de la cita."S
    echo "  -h                               Muestra esta ayuda de uso del programa."
    echo ""
    echo "Ejemplos de uso:"
    echo "Muestra el contenido del archivo de citas:  
			./citas.sh -f datos.txt"
    echo "Añade una cita con el nombre, hora de inicio y hora de fin:
			./citas.sh -f datos.txt -a -n <Nombre Paciente> -i <Hora_Incio> -f <Hora_Fin>"
    echo "Lista todas las citas del dia seleccionado:
			./citas.sh -f datos.txt -d <Dia_Mes_Ano>"
    echo "Muestra la cita con ID dado:
			./citas.sh -f datos.txt -id <Identificador>"
    echo "Muestra una cita del paciente solicitado.  
			./citas.sh -f datos.txt -n <Nombre Paciente>"
    echo "Muestra todas las citas que comienzan a las hora dada:
			./citas.sh -f datos.txt -i <Hora_Inicio>"
    exit 0
}

# Función para mostrar mensajes de error y ayuda básica
function mensajeError {
	echo ""
	echo "Error: Parámetros incorrectos."
	echo "Para ver la ayuda de uso, ejecuta:"
	echo "  ./citas.sh -h"
	exit 1
}

# Verificación inicial: Si no hay argumentos, mostrar el mensaje de error
if [ "$#" -eq 0 ]; then
    mensajeError
fi

# Verificar si se ha pasado la opción de ayuda (-h)
if [ "$1" == "-h" ]; then 
    mostrarAyuda
fi

# Inicializamos las variables
archivo=""
nombre=""
inicio=""
fin=""
dia=""
id_cita=""

# $# -> Numeros de argumentos que se le pasan (Borrar)
while [ "$#" -gt 0 ]; do
	case "$1" in
	-f)
		shift
		citas="$1"  # Guardar el nombre del archivo
		if [ -z "$citas" ]; then # -z comprueba que el argumento no este vacio (Borrar). No comprueba si el fichero esta vacio
			mensajeError
		fi
		if [ ! -r "$citas" ]; then # -r Comprueba que se pueda leer (Borrar)
			echo "Error: El fichero '$citas' no existe o no se puede leer."
			exit 1
		fi
		shift
		if [ -z "$1" ]; then
			echo "Mostrando el contenido del fichero '$citas':"
			cat "$citas"
			exit 0
		fi
	;;
	-a)
		# Podemos comprobar que el numeros de argumentos sea 6 (Para añadir archivos si no no se añade nada)
		# Sin contar (-f datos.txt -a)
		shift
		if  [ -z "$1" ]; then
			mensajeError
		fi
	;;
	-n)
		shift
		nombre="$1"
		shift
	;;
	-i)
		echo 'Entra en i'
		shift
		inicio="$1"
	;;
	-f)
		shift
		fin="$1"
	;;
	-d)
		shift
		dia="$1"
	;;
	-id)
		shift
		id_cita="$1"
	;;
	# Podemos añadir una especialidad al final para añadir al fichero la especialidad. Puede ser un mensaje
	*)
		mensajeError
	;;
esac
# echo "$nombre" Comprobar a futuro (Borrar)
done
