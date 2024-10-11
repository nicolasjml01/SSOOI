#!/bin/bash

# Primera prueba evaluable
# Nicolás Joaquín Miranda Lizondo Y0676614Z
# Marco Antonio Tovar Soto 70970286Z

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
    echo "  -i <Hora inicio>                 Especifica la hora de inicio de la cita."
	echo "	-fi <Hora_Fin>					 Especifica la hora fin de la cita."
	echo "	-e <Especialidad>				 Especifica la especialidad de la consulta"
    echo "  -h                               Muestra esta ayuda de uso del programa."
    echo ""
    echo "Ejemplos de uso:"
    echo "Muestra el contenido del archivo de citas:  
			./citas.sh -f datos.txt"
    echo "Añade una cita con el nombre, hora de inicio, hora de fin- y especialidad:
			./citas.sh -f datos.txt -a -n <Nombre Paciente> -i <Hora_Incio> -f <Hora_Fin> -e <Especialidad>"
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
# Funcion utilizada para comprobar si el argumento $1 esta vacio
function comprobarArgumentoVacio {
	if [ -z "$1" ]; then
		echo "Error: Faltan valores/argumentos"
		mensajeError
    fi
}

# Función para convertir y validar la hora
function convertirHora() {
	hora_recibida="$1"

    # Normalizamos la hora
	# ^([0-9]{1,2})(:[0-9]{2})?$ -> Esto hace que se acepten formatos de 10 como 10:00 (Borrar)
	# ^([0-9]{1,2})(:[0-9]{2})?$ -> ^? (Inicio Fin cadena). ? -> Opcional que haya 2 argumento (Borrar)
    if [[ "$hora_recibida" =~ ^([0-9]{1,2})(:[0-9]{2})?$ ]]; then
        hora="${BASH_REMATCH[1]}" # Extraemos la hora
        minutos="${BASH_REMATCH[2]:-:00}" # Si no hay minutos, asumimos ":00"
        hora_normalizada="$hora$minutos"

        # Si la hora es de 1 digito le ponemos un 0 delante
        if [ "$hora" -lt 10 ]; then
            hora_normalizada="0$hora$minutos"
        fi

        # Comprobamos que la hora esté entre 07:00 y 21:00
        if [ "$hora" -ge 7 ] && [ "$hora" -le 21 ]; then
            return 0 # Indica éxito
        else
            echo "Error: La hora debe estar entre las 07:00 y las 21:00."
            return 1 # Indica fallo
        fi
    else
        echo "Error: Formato de hora incorrecto. Usa HH o HH:MM (por ejemplo, 10 o 10:00)."
        return 1 # Indica fallo
    fi
}


# Verificación inicial: Si no hay argumentos, mostrar el mensaje de error
if [ "$#" -eq 0 ]; then
    mensajeError
fi

# Verificar si se ha pasado la opción de ayuda (-h)
if [ "$1" == "-h" ]; then 
    mostrarAyuda
fi

# Inicializamos la variable booleana para las posibles opciones
flag_a="false"
flag_f="false"

# Inicializamos las variables a usar
citas=""
nombre=""
hora_inicio=""
hora_fin=""
dia=""
id_cita=""
especialidad=""

# $# -> Numeros de argumentos que se le pasan (Borrar)
while [ "$#" -gt 0 ]; do
	case "$1" in
	-f)
		flag_f="true"
		shift
		comprobarArgumentoVacio "$1"
		citas="$1"  # Guardar el nombre del archivo
		
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
		flag_a="true"
		shift
		comprobarArgumentoVacio "$1"
	;;
	-n)
		shift
		comprobarArgumentoVacio "$1"

		# Concatenamos todos los argumentos del nombre hasta que llegue otro argumento
		nombre="$1"
		shift
		while [[ "$#" -gt 0 && "$1" != -* ]]; do
			nombre="$nombre $1"
			shift
		done

		# Comprobamos que haya mas argumentos
		if [ "$#" -eq 0 ]; then
			# Aquí tendriamos que mostrar la cita con el nombre
			echo "Aqui mostrariamos la cita a partir del nombre"
		fi
	;;
	-i)
		shift
		comprobarArgumentoVacio "$1"

		# Convertir y validar la hora de inicio
		convertirHora "$1"  # Llamamos a la función directamente
		if [ $? -ne 0 ]; then
			exit 1  # Sale si la hora es inválida
		fi
		
		# Guardamos el valor devuelto por la función
		hora_inicio=$(convertirHora "$1")
		shift
		
		# Comprobar si no hay más argumentos y la bandera de -a no está activada
		if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
			echo "Aquí mostraríamos las citas a partir de la hora de inicio: $hora_inicio"
			exit 0  # Finalizamos si no hay más opciones
		fi
	;;
	-fi)
		shift
		comprobarArgumentoVacio "$1"

		# Convertir y validar la hora de fin
		convertirHora "$1"  # Llamamos a la función directamente
		if [ $? -ne 0 ]; then
			exit 1  # Sale si la hora es inválida
		fi
		# Voy por aqui
	;;
	-d)
		shift
		dia="$1"
	;;
	-id)
		shift
		id_cita="$1"
	;;
	-e)
		shift
		especialidad="$1"
	;;
	# Podemos añadir una especialidad al final para añadir al fichero la especialidad. Puede ser un mensaje
	*)
		mensajeError
	;;
esac
#If opcionA es true añadir no se que
# si no hacer otra 
# si no otra, etc
# Esto puede servir para introducir datos la verdad
done
