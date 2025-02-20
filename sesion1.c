/*Programa padre crea 5 procesos hijos y nada más crearse están dormidos. El padre despues de 7 
segundos (se puede usar sleep) realizará una señal para que cada uno de los hijos se despierte
e imprima por pantalla su número PID
Despues de ejecutar la práctica deben liberarse los IPC
El usuario se puede cansar antes de los 7 segundos y puede presionar la recla CTRL+C
(Necesitamos un semáforo)
El padre no puede terminar hasta que los hijos hayan terminado.
(jueves a las 2, viernes a la 1)*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


//MANEJADORA DE SIGINT
void sigintHandler(int sig);

pid_t hijos[5];

int main()
{

    struct sigaction sigint;
    sigint.sa_handler = &sigintHandler;
    sigint.sa_flags = SA_RESTART; // NO LETAL


    // MASCARA DE SEÑALES
    sigset_t mask;
    sigfillset(&mask);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1) // MASCARA DEFAULT
    {
        perror("Error en sigprocmask");
        exit(-1);
    }


    // MASKS DE SUSPEND PARA SIGINT
    sigset_t maskusr1;
    sigfillset(&maskusr1);
    sigdelset(&maskusr1, SIGINT);


    if (sigaction(SIGINT, &sigint, NULL) == -1)
    {
        perror("Error en sigaction usr1");
        exit(-1);
    }


    for (int i = 0; i < 5; i++)
    {
        hijos[i] = fork();
        
        if (hijos[i] == 0)
        {
            printf("Hola mundo mi PID es %d\n", getpid());
            sigsuspend(&maskusr1);
            exit(0);
        }
        else if(hijos[i] < 0)
        {
            printf("Error al crear el hijo %d\n", i);
            exit(1);
        }
    }

    sleep(7);
    
    for (int i = 0; i < 5; i++)
    {
        kill(hijos[i], SIGINT);
    }
    
    wait(NULL);

    return 0;
}


void sigintHandler(int sig)
{
    printf("Se ha recibido la señal %d\n", sig);
    exit(0);
}