#!/bin/bash

#Primera prueba evaluable

# Función para mostrar la ayuda del programa
mostrarAyuda() {
    echo "Uso: ./citas.sh [opciones]"
    echo ""
    echo "Opciones:"
    echo "  -f datos.txt                     Muestra el contenido del fichero de citas."
    echo "  -a                               Añade una cita."
	echo "  -d <día_mes_año>                 Lista todas las citas de un día específico."
    echo "  -id <identificador>              Muestra una cita según su identificador."
	echo "  -n <Nombre del paciente>         Especifica el nombre del paciente para añadir o buscar citas."
    echo "  -i <Hora inicio>                 Especifica la hora de inicio de la cita."
    echo "  -h                               Muestra esta ayuda de uso del programa."
    echo ""
    echo "Ejemplos de uso:"
    echo "  ./citas.sh -f datos.txt                       		
																Muestra el contenido del archivo de citas."
    echo "  ./citas.sh -f datos.txt -a -n <Nombre Paciente> -i <Hora_Incio> -f <Hora_Fin>    
																Añade una cita con el nombre, hora de inicio y hora de fin."
    echo "  ./citas.sh -f datos.txt -d <Dia_Mes_Ano>            
																Lista todas las citas del dia seleccionado."
    echo "  ./citas.sh -f datos.txt -id <Identificador>         
																Muestra la cita con ID dado."
    echo "  ./citas.sh -f datos.txt -n <Nombre Paciente>        
																Muestra una cita del paciente solicitado."
    echo "  ./citas.sh -f datos.txt -i <Hora_Inicio>            
																Muestra todas las citas que comienzan a las hora dada."
    exit 0
}

# Función para mostrar mensajes de error y ayuda básica
mensajeError() {
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

# Verificar que el primer argumento sea '-f' y que el segundo sea el nombre del fichero
# -z comprueba que no este vacío el fichero
if [ "$1" != "-f" ] || [ -z "$2" ]; then
    mensajeError
fi

# Comprobar si el archivo tiene permisos de lectura
if [ ! -r "$2" ]; then
    echo "Error: El fichero '$2' no existe o no se puede leer."
    exit 1
fi

# Guardar el nombre del archivo en una variable
citas="$2"

# Si solo se pasa el argumento '-f' con el nombre del fichero, mostramos su contenido
# ESTO PODEMOS MODIFICARLO COMIENDONOS ARGUMENTOS EN EL WHILE PARA QUE VAYA EN CUALQUIER ORDEN (PREGUNTAR)###
if [ "$#" -eq 2 ]; then
    echo "Mostrando el contenido del fichero '$citas':"
    cat "$citas"
    exit 0
fi

# Nos comemos los 2 primeros argumentos -f y datos.txt para empezar a trabajar
shift 2 # Saltamos el '-f' y el nombre del fichero

# $# -> Numeros de argumentos que se le pasa
while [ "$#" -gt 0 ]; do
	case "$1" in
	-a)
		echo 'Entra en -a'
		shift
	;;
	-n)
		echo 'Entra en -n'
		shift
		nombre="$1"
		# Hay que controlar comerse el nombre etc
	;;
	-i)
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
	*)
		mensajeError
	;;
esac

done