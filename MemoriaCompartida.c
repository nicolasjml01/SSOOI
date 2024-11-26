#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// PROTOTIPO MANEJADORES
void sigusrHandler1(int sig);
void sigusrHandler2(int sig);
void sigchld_handler(int sig);

// VARIABLE GLOBAL
typedef struct {
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
} info;

info *pids;  // Apuntador a la estructura de memoria compartida

int main() {

    // Crear archivo temporal para proyectarlo en memoria
    int fd = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("Error abriendo archivo temporal");
        exit(EXIT_FAILURE);
    }
    // Ajustar el tamaño del archivo
    if (ftruncate(fd, sizeof(info)) == -1) {
        perror("Error ajustando tamaño del archivo");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Mapear el archivo en memoria
    pids = mmap(NULL, sizeof(info), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (pids == MAP_FAILED) {
        perror("Error al proyectar archivo en memoria");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);  // Ya no necesitamos el descriptor de archivo
    
    // CREACION DE MANEJADORES Y CONFIGURACION

    struct sigaction susr1;
    susr1.sa_handler = &sigusrHandler1;
    susr1.sa_flags = SA_RESTART;  // NO LETAL

    struct sigaction susr2;
    susr2.sa_handler = &sigusrHandler2;
    susr2.sa_flags = SA_RESTART;  // NO LETAL

    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART;

    // MASCARA DE SEÑALES
    sigset_t mask;
    sigfillset(&mask);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)  // MASCARA DEFAULT
    {
        perror("Error en sigprocmask");
        exit(-1);
    }

    // MASKS DE SUSPEND PARA SIGTERM (INFINITO)
    sigset_t maskusr1;
    sigfillset(&maskusr1);
    sigdelset(&maskusr1, SIGTERM);
    sigdelset(&maskusr1, SIGUSR1);
    sigdelset(&maskusr1, SIGCHLD);
    sigdelset(&maskusr1, SIGINT);

    // MASKS DE SUSPEND PARA SIGTERM (KILL FINAL)
    sigset_t maskusr2;
    sigfillset(&maskusr2);
    sigdelset(&maskusr2, SIGUSR2);
    sigdelset(&maskusr2, SIGTERM);
    sigdelset(&maskusr2, SIGINT);

    // ASIGNACION DE MANEJADORES

    if (sigaction(SIGTERM, &susr1, NULL) == -1) {
        perror("Error en sigaction usr1");
        exit(-1);
    }

    if (sigaction(SIGUSR2, &susr2, NULL) == -1) {
        perror("Error en sigaction usr2");
        exit(-1);
    }

    // CREACION DE PROCESOS
    pids.pid37 = getpid();
    printf("|_37: %d\n", pids.pid37);
    pids.pid38 = fork();  // Creacion de 38

  switch (pids.pid38) {
    case -1:
        perror("Error en el fork 38");
        kill(pids.pid37, SIGKILL);  // Mata el proceso anterior en caso de error
        exit(-1);

    case 0:
        printf("|_38: %d\n", getpid());
        pids.pid39 = fork();  // Creación de 39
        switch (pids.pid39) {
            case -1: perror("Error en el fork 39"); exit(-1);
            case 0:
                printf("|_39: %d\n", getpid());
                pids.pid40 = fork();  // Creación de 40
                switch (pids.pid40) {
                    case -1: perror("Error en el fork 40"); exit(-1);
                    case 0:
                        printf("|_40: %d\n", getpid());
                        pids.pid42 = fork();  // Creación de 42
                        switch (pids.pid42) {
                            case -1: perror("Error en el fork 42"); exit(-1);
                            case 0:
                                printf("|_42: %d\n", getpid());
                                pids.pid46 = fork();  // Creación de 46
                                switch (pids.pid46) {
                                    case -1: perror("Error en el fork 46"); exit(-1);
                                    case 0:
                                        printf("|_46: %d\n", getpid());
                                        pids.pid50 = fork();  // Creación de 50
                                        switch (pids.pid50) {
                                            case -1: perror("Error en el fork 50"); exit(-1);
                                            case 0:
                                                printf("|_50: %d\n", getpid());
                                                pids.pid54 = fork();  // Creación de 54
                                                switch (pids.pid54) {
                                                    case -1: perror("Error en el fork 54"); exit(-1);
                                                    case 0:
                                                        printf("|_54: %d\n", getpid());
                                                        pids.pid56 = fork();  // Creación de 5
                                                        switch (pids.pid56) {
                                                            case -1: perror("Error en el fork 56"); exit(-1);
                                                            case 0:
                                                                printf("|_56: %d\n", getpid());
                                                                pids.pid57 = fork();  // Creación de 57
                                                                switch (pids.pid57) {
                                                                    case -1: perror("Error en el fork 57"); exit(-1);
                                                                    case 0:
                                                                        printf("|_57: %d\n", getpid());
                                                                        pids.pid58 = fork();  // Creación de 58
                                                                        switch (pids.pid58) {
                                                                            case -1: perror("Error en el fork 58"); exit(-1);
                                                                            case 0:
                                                                                printf("|_58: %d\n", getpid());
                                                                                sigsuspend(&maskusr1);  // Proceso hoja
                                                                                exit(0);
                                                                            default:
                                                                                sigsuspend(&maskusr1);
                                                                                kill(pids.pid58, SIGTERM);
                                                                                exit(0);
                                                                        }
                                                                    default:
                                                                        sigsuspend(&maskusr1);
                                                                        kill(pids.pid57, SIGTERM);
                                                                        exit(0);
                                                                }
                                                            default:
                                                                sigsuspend(&maskusr1);
                                                                //kill(pids.pid56, SIGTERM);
                                                                exit(0);
                                                        }
                                                    default:
                                                        sigsuspend(&maskusr1);
                                                        exit(0);
                                                }
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
                                pids.pid43 = fork();  // Creación de 43
                                switch (pids.pid43) {
                                    case -1: perror("Error en el fork 43"); exit(-1);
                                    case 0:
                                        printf("|_43: %d\n", getpid());
                                        pids.pid47 = fork();  // Creación de 47
                                        switch (pids.pid47) {
                                            case -1: perror("Error en fork 47"); exit(-1);
                                            case 0:
                                                printf("|_47: %d\n", getpid());
                                                pids.pid51 = fork();  // Creación de 51
                                                switch (pids.pid51) {
                                                    case -1: perror("Error en el fork 51"); exit(-1);
                                                    case 0:
                                                        printf("|_51: %d\n", getpid());
                                                        sigsuspend(&maskusr1); 
                                                        kill(pids.pid54, SIGTERM);
                                                        exit(0);
                                                    default:
                                                        sigsuspend(&maskusr1);
                                                        kill(pids.pid51, SIGTERM);
                                                        exit(0);
                                                }
                                            default:
                                                sigsuspend(&maskusr1);
                                                kill(pids.pid47, SIGTERM);
                                                exit(0);
                                        }
                                    default:
                                        sigsuspend(&maskusr1);
                                        kill(pids.pid42, SIGTERM);
                                        kill(pids.pid43, SIGTERM);
                                        exit(0);
                                }
                        }
                    default:
                        pids.pid41 = fork();  // Creación de 41
                        switch (pids.pid41) {
                            case -1: perror("Error en el fork 41"); exit(-1);
                            case 0:
                                printf("|_41: %d\n", getpid());
                                pids.pid45 = fork();  // Creación de 45
                                switch (pids.pid45) {
                                    case -1: perror("Error en el fork 45"); exit(-1);
                                    case 0:
                                        printf("|_45: %d\n", getpid());
                                        pids.pid49 = fork();  // Creación de 49
                                        switch (pids.pid49) {
                                            case -1: perror("Error en fork 49"); exit(-1);
                                            case 0:
                                                printf("|_49: %d\n", getpid());
                                                pids.pid53 = fork();  // Creación de 53
                                                switch (pids.pid53) {
                                                    case -1: perror("Error en el fork 53"); exit(-1);
                                                    case 0:
                                                        printf("|_53: %d\n", getpid());
                                                        sigsuspend(&maskusr1);
                                                        kill(pids.pid55, SIGTERM);
                                                        exit(0);
                                                    default:
                                                        sigsuspend(&maskusr1);
                                                        kill(pids.pid53, SIGTERM);
                                                        exit(0);
                                                }
                                            default:
                                                sigsuspend(&maskusr1);
                                                kill(pids.pid49, SIGTERM);
                                                exit(0);
                                        }
                                    default:
                                        
                                          pids.pid44 = fork();  // Creación de 44
                                          switch (pids.pid44) {
                                              case -1: perror("Error en el fork 44"); exit(-1);
                                              case 0:
                                                  printf("|_44: %d\n", getpid());
                                                  pids.pid48 = fork();  // Creación de 48
                                                  switch (pids.pid48) {
                                                      case -1: perror("Error en fork 48"); exit(-1);
                                                      case 0:
                                                          printf("|_48: %d\n", getpid());
                                                          pids.pid52 = fork();  // Creación de 52
                                                          switch (pids.pid52) {
                                                              case -1: perror("Error en el fork 52"); exit(-1);
                                                              case 0:
                                                                  printf("|_52: %d\n", getpid());
                                                                  pids.pid55 = fork();  // Creación de 55
                                                                  switch (pids.pid55) {
                                                                      case -1: perror("Error en el fork 55"); exit(-1);
                                                                      case 0:
                                                                          printf("|_55: %d\n", getpid());
                                                                          sigsuspend(&maskusr1); 
                                                                          kill(pids.pid56, SIGTERM);
                                                                          exit(0);
                                                                      default:
                                                                          sigsuspend(&maskusr1);  
                                                                          //kill(pids.pid55, SIGTERM);  
                                                                          exit(0);
                                                                  }
                                                              default:
                                                                  sigsuspend(&maskusr1);  
                                                                  kill(pids.pid52, SIGTERM);  
                                                                  exit(0);
                                                          }
                                                      default:
                                                          sigsuspend(&maskusr1);  
                                                          kill(pids.pid48, SIGTERM);  
                                                          exit(0);
                                                  }
                                              default:
                                                  sigsuspend(&maskusr1);  
                                                  kill(pids.pid44, SIGTERM);  
                                                  kill(pids.pid45, SIGTERM);
                                                  exit(0);
                                          }
                                           
                                           
                                           
                                       // sigsuspend(&maskusr1);
                                       // kill(pids.pid45, SIGTERM);
                                        
                                        //exit(0);
                                }
                            default:
                                sigsuspend(&maskusr1);
                                kill(pids.pid40, SIGTERM);
                                kill(pids.pid41, SIGTERM);
                                exit(0);
                        }
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


}


// MANEJADORES DE SIGTERM
void sigusrHandler1(int sig) { 
    printf("Terminando proceso %d...\n", getpid()); 
}

// MANEJADORES DE SIGUSR2 (MATAR A N2 Y N3)
void sigusrHandler2(int sig) { 
    printf("Terminando proceso...");
}

// Manejador para SIGCHLD
void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        // Recolecta todos los hijos que hayan terminado
    }
}
