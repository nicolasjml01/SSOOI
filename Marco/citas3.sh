#!/bin/bash

# Primera prueba evaluable
# Nicolás Joaquín Miranda Lizondo Y0676614Z
# Marco Antonio Tovar Soto 70970286Z

# Función para mostrar la ayuda del programa
## CAMBIAR FUNCION DE AYUDA (BORRAR)
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

# Función para convertir y validar la hora exacta, HH
function convertirHora() {
    hora_recibida="$1"

    # Aceptamos solo formato HH (de 1 o 2 dígitos, sin minutos)
    if [[ "$hora_recibida" =~ ^([0-9]{1,2})$ ]]; then
        hora="${BASH_REMATCH[1]}"

        # Comprobamos que la hora esté entre 7 y 21
        if [ "$hora" -ge 7 ] && [ "$hora" -le 21 ]; then
            return 0 # Indica éxito
        else
            echo "Error: La hora debe estar entre las 7 y las 21."
            return 1 # Indica fallo
        fi
    else
        echo "Error: Formato de hora incorrecto. Usa el formato HH (por ejemplo, 7 o 13)."
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

        dia_formateado=$(echo "$dia" | sed 's/^0*//')   #quitar el primer 0 si existe
        mes_formateado=$(echo "$mes" | sed 's/^0*//')   #en formato del .txt aparece sin 0

        # Validar que el mes esté entre 01 y 12
        if (( $mes_formateado < 1 || $mes_formateado > 12 )); then
            echo "Error: El mes debe estar entre 01 y 12."
            return 1
        fi

        # Validar que el día esté entre 01 y 31
        if (( $dia_formateado < 1 || $dia_formateado > 31 )); then
            echo "Error: El día debe estar entre 01 y 31."
            return 1
        fi

        # Validar que febrero tenga 28 o 29 días
        if (( $mes_formateado == 2 )); then  #si el mes es febrero

            if (( $dia_formateado == 29 )); then  #si el día es 29
                if !(( $anio % 4 == 0 && $anio % 100 != 0 )) || (( $anio % 400 == 0 )); then  #si el año es divisible entre 4 o 400
                    echo "Error: El mes de febrero no tiene 29 días este año."   #si no es divisible entre 4 o 400 se muestra el error
                    return 1  #sale
                fi
            elif (( $dia_formateado > 28 )); then  #si el día es mayor a 28
                echo "Error: El mes de febrero no tiene más de 28 días."   #si no es mayor a 28 se muestra el error
                return 1  #sale
            fi

        fi

        #validar si un mes tiene 30 o 31 dias
        if !(( $mes_formateado % 2 == 0 )); then  #si el mes es impar
            if (( $dia_formateado == 31 )); then
                echo "Error: El mes impar no tiene 31 días."   
                return 1  #sale
            fi
        fi
        
        fecha_normalizada="${dia_formateado}_${mes}_${anio}"
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
            grep "$nombre" "$citas" -A 5

			exit 0
		fi
	;;
	-i)
        shift
        comprobarArgumentoVacio "$1"

        # Convertir y validar la hora de inicio
        convertirHora "$1"  # Ejecutamos la función sin capturar la salida para mostrar errores
        if [ $? -ne 0 ]; then
            exit 1  # Sale si la hora es inválida
        fi

        # Si la función convertirHora tuvo éxito, capturamos la hora
        hora_inicio="$1"
        shift
        
        # Comprobar si no hay más argumentos y la bandera de -a no está activada
        if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
            echo "Aquí mostraríamos las citas a partir de la hora de inicio: $hora_inicio"
            grep "HORA_INICIAL: $hora_inicio" "$citas" -A 3 -B 2
            exit 0  # Finalizamos si no hay más opciones
        fi
        ;;
	-fi)
		shift
		comprobarArgumentoVacio "$1"

		# Convertir y validar la hora de inicio
        convertirHora "$1"  # Ejecutamos la función sin capturar la salida para mostrar errores
        if [ $? -ne 0 ]; then
            exit 1  # Sale si la hora es inválida
        fi

        # Si la función convertirHora tuvo éxito, capturamos la hora
        hora_fin="$1"
        shift
	;;
	-d)
		shift
		comprobarArgumentoVacio "$1"

		# Validar y normalizar la fecha
		validarFecha "$1"
		# Comprobar si hubo un error en la validación de la fecha
		if [ $? -ne 0 ]; then
			exit 1  # Sale si la fecha es inválida
		fi
        # Si la funcion validarFecha tuvo éxito, capturamos la fecha
        fecha="$1"
		shift

		# Comprobar si no hay más argumentos y la bandera de -a no está activada
		if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
			echo "Aquí mostraríamos las citas del día: $fecha_normalizada"
            grep  "$fecha_normalizada" "$citas" -A 1 -B 5
			exit 0  # Finalizamos si no hay más opciones
		fi
	;;
	-id)
		shift
		comprobarArgumentoVacio "$1"

		id_cita="$1"
        
		if [ $? -ne 0 ]; then
			echo "Id introducido incorrectamente"
			exit 1  # Sale si el id es inválida
		fi
		shift

		# Comprobar si no hay más argumentos y la bandera de -a no está activada
		if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
			echo "Aquí mostraríamos las citas del id: $id_citas"
		    grep  "$id_cita" "$citas" -B 5
			exit 0  # Finalizamos si no hay más opciones
		fi
	;;
	# Podemos añadir una especialidad al final para añadir al fichero la especialidad. Puede ser un mensaje
	*)
        mensajeError
	;;
esac

done

# CAMBIAR LO DEL ID, VER QUE NO COINCIDE EN UN MISMO DIA A LA MISMA HORA EN LA MISMA ESPECIALIDAD
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



        # Buscar las horas de las citas existentes en la misma especialidad y fecha
        hora_ic=$(grep "ESPECIALIDAD: $especialidad" "$citas" -A 3 | grep "DIA: $fecha_normalizada" -B 2 | grep -oP 'HORA_INICIAL: \K\d+')
        hora_fc=$(grep "ESPECIALIDAD: $especialidad" "$citas" -A 3 | grep "DIA: $fecha_normalizada" -B 1 | grep -oP 'HORA_FINAL: \K\d+')

        # Verificar si hay alguna coincidencia en el rango de horas
        if [[ -n "$hora_ic" && -n "$hora_fc" ]]; then
            if [[ ($hora_inicio -ge $hora_ic && $hora_inicio -lt $hora_fc) || ($hora_fin -gt $hora_ic && $hora_fin -le $hora_fc) || ($hora_inicio -le $hora_ic && $hora_fin -ge $hora_fc) ]]; then
                echo "Error: La cita coincide con otra cita existente en la misma fecha y especialidad."
                exit 1
            fi
        fi



        # Obtener el último ID del archivo documentos.txt y calcular el nuevo ID
        if [[ -f $citas ]]; then
            ultimo_id=$(grep "DIA: $fecha_normalizada" -A 1 $citas | grep -oP 'ID: \d+_\K\d+' | tail -n 1)
            if [[ -z "$ultimo_id" ]]; then
                nuevo_id=1
            else
                nuevo_id=$((ultimo_id + 1))
            fi
        else
            nuevo_id=1
        fi

        #Extraer el día, mes y año de la fecha para el formato de ID
        dia=$(echo "$fecha_normalizada" | cut -d'_' -f1)
        mes=$(echo "$fecha_normalizada" | cut -d'_' -f2)
        anio=$(echo "$fecha_normalizada" | cut -d'_' -f3)
        id="${dia}${mes}${anio}_${nuevo_id}"

        # Formatear la información de la cita
        cita="
PACIENTE: $nombre
ESPECIALIDAD: $especialidad
HORA_INICIAL: $hora_inicio
HORA_FINAL: $hora_fin
DIA: $fecha_normalizada
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