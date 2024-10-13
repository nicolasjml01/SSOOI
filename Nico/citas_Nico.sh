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
			echo "$hora_normalizada" # Imprime la hora para capturarla (Borrar)
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
function validarFecha() {
    fecha="$1"

    # Expresión regular para los formatos:
    # 1. d/mm/aa (un dígito para el día y dos para el mes)
    # 2. dd/mm/aa (dos dígitos para el día y dos para el mes)
    # 3. d_mm_aa (un dígito para el día y dos para el mes, guiones bajos)
    # 4. dd_mm_aa (dos dígitos para el día y mes, guiones bajos)
    # 5. ddmmaño (sin separadores, pero el mes y el año son siempre de 2 dígitos)
    if [[ "$fecha" =~ ^([0-9]{1,2})[-/_]?([0-9]{2})[-/_]?([0-9]{2})$ ]]; then
        dia="${BASH_REMATCH[1]}"
        mes="${BASH_REMATCH[2]}"
        anio="${BASH_REMATCH[3]}"

        # Validar que el mes esté entre 01 y 12
        if (( $mes < 1 || $mes > 12 )); then
            echo "Error: El mes debe estar entre 01 y 12."
            return 1
        fi

        # Validar que el día esté entre 01 y 31
        if (( $dia < 1 || $dia > 31 )); then
            echo "Error: El día debe estar entre 01 y 31."
            return 1
        fi

        # Convertimos la fecha al formato dd_mm_aa
        # Aseguramos que el día tenga siempre dos dígitos
        printf -v dia_formateado "%02d" "$dia"
        fecha_normalizada="${dia_formateado}_${mes}_${anio}"
        echo "$fecha_normalizada"
        return 0
    else
        echo "Error: Fecha no válida. Introduzca la fecha en formato d/mm/aa, dd/mm/aa, d_mm_aa, dd_mm_aa, o ddmmaño."
        return 1
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
fecha=""
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
		# Hay que ver que pasa si -a es la ultima de las opciones (Borrar)
		flag_a="true"
		shift
		comprobarArgumentoVacio "$1"
	;;
	-n)
		shift
		comprobarArgumentoVacio "$1"

		# Concatenamos todos los argumentos del nombre hasta que llegue otro argumento
		while [[ "$#" -gt 0 && "$1" != -* ]]; do
			nombre="$nombre $1"
			shift
		done

		# Comprobar si no hay más argumentos y la bandera de -a no está activada
		if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
			# Aquí tendriamos que mostrar la cita con el nombre
			echo "Aqui mostrariamos la cita a partir del nombre: $nombre"
			exit 0
		fi
	;;
	-i)
		shift
		comprobarArgumentoVacio "$1"

		# Convertir y validar la hora de inicio
		hora_inicio=$(convertirHora "$1")
		if [ $? -ne 0 ]; then
			exit 1  # Sale si la hora es inválida
		fi
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
		hora_fin="$(convertirHora "$1")"		
		if [ $? -ne 0 ]; then
			exit 1  # Sale si la hora es inválida
		fi
		shift

	;;
	-d)
		shift
		comprobarArgumentoVacio "$1"

		# Validar y normalizar la fecha
		fecha=$(validarFecha "$1")
		# Comprobar si hubo un error en la validación de la fecha
		if [ $? -ne 0 ]; then
			echo "Fecha introducida incorrectamente"
			exit 1  # Sale si la fecha es inválida
		fi
		shift

		# Comprobar si no hay más argumentos y la bandera de -a no está activada
		if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
			echo "Aquí mostraríamos las citas del día: $fecha"
			exit 0  # Finalizamos si no hay más opciones
		fi
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

done

# Verificar si ambos flags están en true
if [[ "$flag_a" == "true" && "$flag_f" == "true" ]]; then

    # Verificar si las variables están rellenadas
    if [[ -n "$nombre" && -n "$hora_inicio" && -n "$hora_fin" && -n "$fecha" ]]; then

        # Preguntar al usuario la especialidad
        echo "Selecciona el motivo de la consulta (introduce el número correspondiente):"
        echo "1. Enfermería"
        echo "2. Atención primaria"
        echo "3. Cardiología"
        echo "4. Dermatología"
        echo "5. Ginecología"
        read -p "Opción: " opcion_especialidad

        # Asignar la especialidad en base a la elección del usuario
        case $opcion_especialidad in
            1) especialidad="Enfermería" ;;
            2) especialidad="Atención primaria" ;;
            3) especialidad="Cardiología" ;;
            4) especialidad="Dermatología" ;;
            5) especialidad="Ginecología" ;;
            *) echo "Opción no válida. Saliendo..."; exit 1 ;;
        esac

        # Obtener el último ID del archivo documentos.txt y calcular el nuevo ID
        if [[ -f documentos.txt ]]; then
            ultimo_id=$(grep -oP 'ID: \K\d+' documentos.txt | tail -n 1)
            if [[ -z "$ultimo_id" ]]; then
                nuevo_id=1
            else
                nuevo_id=$((ultimo_id + 1))
            fi
        else
            nuevo_id=1
        fi

        # Extraer el día, mes y año de la fecha para el formato de ID
        dia=$(echo "$fecha" | cut -d'_' -f1)
        mes=$(echo "$fecha" | cut -d'_' -f2)
        anio=$(echo "$fecha" | cut -d'_' -f3)
        id="${dia}${mes}${anio}_${nuevo_id}"

        # Formatear la información de la cita
        cita="
PACIENTE: $nombre
ESPECIALIDAD: $especialidad
HORA_INICIAL: $hora_inicio
HORA_FINAL: $hora_fin
DIA: $fecha
ID: $id
"
        # Añadir la cita al archivo datos.txt
        echo "$cita" >> "$citas"
        echo "Cita añadida correctamente a datos.txt."
    else
        echo "Error: Las variables nombre, hora_inicio, hora_fin o fecha no están inicializadas."
        exit 1
    fi
else
    echo "Error: Los flags flag_a o flag_f no están en true."
    exit 1
fi
