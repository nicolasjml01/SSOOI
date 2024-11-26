#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

// PROTOTIPO MANEJADORES
void sigusrHandler1(int sig);
void sigusrHandler2(int sig);
void sigchld_handler(int sig);


// VARIABLE GLOBAL
typedef struct
{
    pid_t pid37;
    pid_t pid38;
    pid_t pid39;
    pid_t pid40;
    pid_t pid41;
    pid_t pid42;
    pid_t pid43;
    pid_t pid44;
    pid_t pid45;
    pid_t pid46;
    pid_t pid47;
    pid_t pid48;
    pid_t pid49;
    pid_t pid50;
    pid_t pid51;
    pid_t pid52;
    pid_t pid53;
    pid_t pid54;
    pid_t pid55;
    pid_t pid56;
    pid_t pid57;
    pid_t pid58;
    int mediavuelta;
} info;

info pids;

int main()
{
    // CREACION DE MANEJADORES Y CONFIGURACION
    struct sigaction susr1;
    susr1.sa_handler = &sigusrHandler1;
    susr1.sa_flags = SA_RESTART; // NO LETAL

    struct sigaction susr2;
    susr2.sa_handler = &sigusrHandler2;
    susr2.sa_flags = SA_RESTART; // NO LETAL

    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART ;

    // MASCARA DE SEÑALES
    sigset_t mask;
    sigfillset(&mask);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1) // MASCARA DEFAULT
    {
        perror("Error en sigprocmask");
        exit(-1);
    }

    // MASKS DE SUSPEND PARA SIGTERM (INFINITO)
    sigset_t maskusr1;
    sigfillset(&maskusr1);
    sigdelset(&maskusr1, SIGTERM);
    sigdelset(&maskusr1, SIGUSR1);
    sigdelset(&maskusr1,SIGCHLD);
    sigdelset(&maskusr1, SIGINT);

    // MASKS DE SUSPEND PARA SIGTERM (KILL FINAL)
    sigset_t maskusr2;
    sigfillset(&maskusr2);
    sigdelset(&maskusr2, SIGUSR2);
    sigdelset(&maskusr2, SIGTERM);
    sigdelset(&maskusr2, SIGINT);

    // ASIGNACION DE MANEJADORES
    if (sigaction(SIGTERM, &susr1, NULL) == -1)
    {
        perror("Error en sigaction usr1");
        exit(-1);
    }

    if (sigaction(SIGUSR2, &susr2, NULL) == -1)
    {
        perror("Error en sigaction usr2");
        exit(-1);
    }

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("Error en sigaction sa");
        exit(-1);
    }


    // CREACION DE PROCESOS
    pids.pid37 = getpid();
    printf("|_37: %d\n", pids.pid37);
    pids.pid38 = fork(); // Creacion de 38

    // Código modificado para asegurar la terminación de procesos hoja y evitar creación infinita

switch (pids.pid38) {
    case -1:
        perror("Error en el fork 38");
        exit(-1);
    
    case 0:
        printf("|_38: %d\n", getpid());
        pids.pid39 = fork();
        
        switch (pids.pid39) {
            case -1:
                perror("Error en el fork 39");
                exit(-1);
            
            case 0:
                printf("|_39: %d\n", getpid());
                pids.pid40 = fork();
                
                switch (pids.pid40) {
                    case -1:
                        perror("Error en el fork 40");
                        exit(-1);
                    
                    case 0:
                        printf("|_40: %d\n", getpid());
                        pids.pid42 = fork();
                        
                        switch (pids.pid42) {
                            case -1:
                                perror("Error en el fork 42");
                                exit(-1);
                            
                            case 0:
                                printf("|_42: %d\n", getpid());
                                pids.pid46 = fork();
                                
                                switch (pids.pid46) {
                                    case -1:
                                        perror("Error en el fork 46");
                                        exit(-1);
                                    
                                    case 0:
                                        printf("|_46: %d\n", getpid());
                                        pids.pid50 = fork();
                                        
                                        switch (pids.pid50) {
                                            case -1:
                                                perror("Error en el fork 50");
                                                exit(-1);
                                            
                                            case 0:
                                                printf("|_50: %d\n", getpid());
                                                sigsuspend(&maskusr1); // Espera de señal
                                                exit(0);  // Termina el proceso hoja
                                            
                                            default:
                                                sigsuspend(&maskusr1);
                                                kill(pids.pid50, SIGTERM);
                                                exit(0);
                                        }
                                    
                                    default:
                                        sigsuspend(&maskusr1);
                                        kill(pids.pid46, SIGTERM);
                                        exit(0);
                                }
                            
                            default:
                                sigsuspend(&maskusr1);
                                kill(pids.pid42, SIGTERM);
                                exit(0);
                        }
                    
                    default:
                        sigsuspend(&maskusr1);
                        kill(pids.pid40, SIGTERM);
                        exit(0);
                }
            
            default:
                sigsuspend(&maskusr1);
                kill(pids.pid39, SIGTERM);
                exit(0);
        }
    
    default:
        sigsuspend(&maskusr1);
        kill(pids.pid38, SIGTERM);
        exit(0);
}


// MANEJADORES DE SIGTERM
void sigusrHandler1(int sig)
{
                printf("Terminando proceso %d...\n", getpid());

    
        
       
}


void sigusrHandler2(int sig)
{
    // Si es necesario manejar SIGUSR2, puedes hacerlo aquí.
    // En este caso, no hay lógica implementada para SIGUSR2.

            puts("Terminando proceso...");
        
}

// Manejador para SIGCHLD
void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        // Recolecta todos los hijos que hayan terminado
    }
}



/*
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Manejador para SIGCHLD
void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        // Recolecta todos los hijos que hayan terminado
    }
}

int main() {
    // Configurar el manejador para SIGCHLD
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid = fork();
    if (pid == 0) {
        // Código del hijo
        printf("Soy el hijo con PID %d, terminando...\n", getpid());
        exit(0);
    } else if (pid > 0) {
        // Código del padre
        printf("Soy el padre con PID %d, esperando...\n", getpid());
        sleep(5);  // Simular trabajo del padre
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
*/