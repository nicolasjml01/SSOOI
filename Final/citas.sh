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
    echo "  -f  <Fichero>                    Muestra el contenido del fichero de citas."
    echo "  -a                               Añade una cita al registro de citas."
	echo "  -n  <Nombre del paciente>        Muestra una cita por el nombre del paciente o añade el nombre a la cita."
    echo "  -i  <Hora_inicio>                Lista las citas por hora de inicio o añade una cita a partir de cierta hora."
	echo "  -d  <día_mes_año>                Lista todas las citas de un día específico."
    echo "  -id <identificador>              Muestra una cita según su identificador."
	echo "	-fi <Hora_Fin>					 Especifica la hora fin de la cita a añadir."
    echo "  -h                               Muestra esta ayuda de uso del programa."
    echo ""
    echo "Ejemplos de uso:"
    echo "Muestra el contenido del archivo de citas:  
			./citas.sh -f datos.txt"
    echo "Añade una cita con el nombre, hora de inicio, hora de fin y dia:
			./citas.sh -f datos.txt -a -n Nicolas Marco Tovar Miranda -i 10 -fi 11 -d 15_07_24"
    echo "Lista todas las citas del dia seleccionado:
			./citas.sh -f datos.txt -d 15_07_24"
    echo "Muestra una cita con el ID dado:
			./citas.sh -f datos.txt -id 15724_1"
    echo "Muestra una cita del paciente solicitado.  
			./citas.sh -f datos.txt -n Nicolas Marco Tovar Miranda"
    echo "Muestra todas las citas que comienzan a la hora dada:
			./citas.sh -f datos.txt -i 10"
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

    if [[ "$fecha" =~ ^([0-9]{1,2})_([0-9]{1,2})_([0-9]{2})$ ]]; then
        dia="${BASH_REMATCH[1]}"
        mes="${BASH_REMATCH[2]}"
        anio="${BASH_REMATCH[3]}"

        # Eliminar ceros a la izquierda del día y el mes
        dia_formateado=$(echo "$dia" | sed 's/^0*//')
        mes_formateado=$(echo "$mes" | sed 's/^0*//')

        # Validaciones
        if (( mes_formateado < 1 || mes_formateado > 12 )); then
            echo "Error: El mes debe estar entre 1 y 12."
            return 1
        fi
        if (( dia_formateado < 1 || dia_formateado > 31 )); then
            echo "Error: El día debe estar entre 1 y 31."
            return 1
        fi
        if (( mes_formateado == 2 && dia_formateado > 28 )); then
            echo "Error: El mes de febrero no tiene más de 28 días."
            return 1
        fi

        # Asignar la fecha normalizada (sin ceros a la izquierda) a una variable global
        # Hacemos fehca como una variable global (Borrar)
        fecha="${dia_formateado}_${mes_formateado}_${anio}"
        return 0
    else
        echo "Error: Fecha no válida. Introduzca la fecha en formato d_m_aa, dd_m_aa, d_mm_aa o dd_mm_aa."
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
            # Aquí mostraríamos la primera cita a partir del nombre
            echo "Buscando la cita asignada a: $nombre"
            
            # Buscar el nombre en el archivo, limitar a la primera coincidencia
            cita=$(grep -m 1 "$nombre" "$citas" -A 5)

            # Verificar si se encontró alguna cita
            if [[ -n "$cita" ]]; then
                # Si se encuentra, mostrar la primera cita
                echo "$cita"
            else
                # Si no se encuentra, mostrar el mensaje de error
                echo "No hemos encontrado una cita asignada a ese nombre: $nombre"
            fi

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
            echo "Buscando citas con hora inicial mayor o igual a: $hora_inicio"

            # Usamos awk para buscar y comparar las horas iniciales y mostrar citas completas
            awk -v hora_inicio="$hora_inicio" '
            BEGIN { citas_encontradas = 0 }  # Inicializamos el contador de citas

            /PACIENTE:/ { paciente_line = $0 }
            /ESPECIALIDAD:/ { especialidad_line = $0 }
            /HORA_INICIAL:/ {
                split($0, arr, ": ");
                hora_actual = arr[2];

                # Comparar la hora actual con la hora proporcionada
                if (hora_actual >= hora_inicio) {
                    citas_encontradas++;  # Aumentamos el contador de citas encontradas
                    # Mostrar la cita completa (paciente, especialidad, hora inicial, hora final, día, ID)
                    print "";
                    print paciente_line;
                    print especialidad_line;
                    print $0;  # Línea con HORA_INICIAL
                    getline; print $0;  # HORA_FINAL
                    getline; print $0;  # DIA
                    getline; print $0;  # ID
                }
            }

            END {
                # Si no se encontraron citas
                if (citas_encontradas == 0) {
                    print "No se encontraron citas a partir de la hora inicial " hora_inicio ".";
                }
            }
            ' "$citas"

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
        
        shift
        # Comprobar si no hay más argumentos y la bandera de -a no está activada
        if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
            echo "Buscando citas del día: $fecha"
            
            # Contar cuántas coincidencias tiene grep para la fecha
            citas_encontradas=$(grep -c "$fecha" "$citas")

            if [ "$citas_encontradas" -gt 0 ]; then
                # Si hay citas, mostramos las citas encontradas
                echo "Citas encontradas:"
                grep "$fecha" "$citas" -A 1 -B 5
            else
                # Si no hay citas, mostrar el mensaje de error
                echo "No hay citas disponibles en la fecha: $fecha."
            fi

            exit 0  # Finalizamos si no hay más opciones
        fi
    ;;
    -id)
        shift
        comprobarArgumentoVacio "$1"

        id_cita="$1"

        # Comprobar si el ID fue introducido correctamente
        if [ $? -ne 0 ]; then
            echo "ID introducido incorrectamente"
            exit 1  # Sale si el ID es inválido
        fi
        shift

        # Comprobar si no hay más argumentos y la bandera de -a no está activada
        if [ "$#" -eq 0 ] && [ "$flag_a" = false ]; then
            echo "Buscando citas a partir del ID: $id_cita"

            # Contar cuántas coincidencias tiene grep para el ID
            citas_encontradas=$(grep -c "$id_cita" "$citas")

            if [ "$citas_encontradas" -gt 0 ]; then
                # Si hay citas, mostramos las citas encontradas
                echo "Citas encontradas:"
                grep "$id_cita" "$citas" -B 5
            else
                # Si no hay citas, mostrar el mensaje de error
                echo "No hay citas disponibles con el ID: $id_cita."
            fi

            exit 0  # Finalizamos si no hay más opciones
        fi
    ;;
	*)
        mensajeError
	;;
esac

done

# Añadir datos al fichero
if [[ "$flag_a" == "true" && "$flag_f" == "true" ]]; then
    # Verificar si las variables están rellenadas
    if [[ -n "$nombre" && -n "$hora_inicio" && -n "$hora_fin" && -n "$fecha" ]]; then
        # Verificar que la hora de inicio sea menor que la hora de fin
        if [[ $hora_inicio -ge $hora_fin ]]; then
            echo "Error: La hora de fin ($hora_fin) no puede ser menor que la de inicio ($hora_inicio)."
            exit 1
        fi

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
        hora_ic=$(grep "ESPECIALIDAD: $especialidad" "$citas" -A 3 | grep "DIA: $fecha" -B 2 | grep -oP 'HORA_INICIAL: \K\d+')
        hora_fc=$(grep "ESPECIALIDAD: $especialidad" "$citas" -A 3 | grep "DIA: $fecha" -B 1 | grep -oP 'HORA_FINAL: \K\d+')

        # Verificar si hay alguna coincidencia en el rango de horas
        if [[ -n "$hora_ic" && -n "$hora_fc" ]]; then
            if [[ ($hora_inicio -ge $hora_ic && $hora_inicio -lt $hora_fc) || ($hora_fin -gt $hora_ic && $hora_fin -le $hora_fc) || ($hora_inicio -le $hora_ic && $hora_fin -ge $hora_fc) ]]; then
                echo "Error: La cita coincide con otra cita existente en la misma fecha y especialidad."
                exit 1
            fi
        fi

        # Obtener el último ID del archivo documentos.txt y calcular el nuevo ID
        if [[ -f $citas ]]; then
            ultimo_id=$(grep "DIA: $fecha" -A 1 $citas | grep -oP 'ID: \d+_\K\d+' | tail -n 1)
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

        # Formatear la información de la cita con espacios en blanco correctamente
        cita="PACIENTE: $nombre
ESPECIALIDAD: $especialidad
HORA_INICIAL: $hora_inicio
HORA_FINAL: $hora_fin
DIA: $fecha
ID: $id"

        # Añadir la cita al archivo datos.txt sin líneas en blanco adicionales
        if [[ -s "$citas" ]]; then
            echo -e "\n$cita" >> "$citas"
        else
            echo "$cita" >> "$citas"
        fi
        
        echo "Cita añadida correctamente a datos.txt."
    else
        echo "Error: Las variables nombre, hora_inicio, hora_fin o fecha no están inicializadas."
        exit 1
    fi
else
    echo "Error: Los flags flag_a o flag_f no están en true."
    exit 1
fi
