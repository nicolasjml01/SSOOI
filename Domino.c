/*Nicolás Joaquín Miranda Lizondo Y0676614Z
 Marco Antonio Tovar Soto 70970286Z
*/


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// PROTOTIPO MANEJADORES
void sigusrHandler1(int sig);
void eliminarArchivo();

typedef struct {
    pid_t pids[4];              // Array para almacenar PIDs
} shared_info;

// Variable global para la memoria compartida
shared_info *shared_data;


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

info pids;

int main() {    
    const char *f="pids.txt";
    int fd;

    fd = open(f, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }
    if (ftruncate(fd, sizeof(shared_info)) == -1) {
        perror("Error al ajustar el tamaño del archivo");
        close(fd);
        return 1;
    }

    // Crear memoria compartida para almacenar múltiples PIDs
    shared_data =(shared_info *) mmap(NULL, sizeof(shared_info), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("Error en mmap");
        exit(-1);
    }  
   close(fd);

    // CREACION DE MANEJADORES Y CONFIGURACION
    struct sigaction susr1;
    susr1.sa_handler = &sigusrHandler1;
    susr1.sa_flags = SA_RESTART;  // NO LETAL

    // MASCARA DE SEÑALES
    sigset_t mask;
    sigfillset(&mask);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)  // MASCARA DEFAULT
    {
        perror("Error en sigprocmask");
        exit(-1);
    }

    // MASKS DE SUSPEND PARA SIGTERM
    sigset_t maskusr1;
    sigfillset(&maskusr1);
    sigdelset(&maskusr1, SIGTERM);
    sigdelset(&maskusr1, SIGINT);


    // ASIGNACION DE MANEJADORES
    if (sigaction(SIGTERM, &susr1, NULL) == -1) {
        perror("Error en sigaction usr1");
        exit(-1);
    }

  // CREACION DE PROCESOS
  pids.pid37 = getpid();
  pids.pid38 = fork();  // Creación de 38
  switch (pids.pid38) {
      case -1:
          perror("Error en el fork 38");
          kill(pids.pid37, SIGKILL);  // Mata el proceso anterior en caso de error
          exit(-1);
      case 0:
          pids.pid39 = fork();  // Creación de 39
          pids.pid38 =getpid();
          switch (pids.pid39) {
              case -1: perror("Error en el fork 39"); exit(-1);
              case 0:
                  pids.pid40 = fork();
                  pids.pid39 = getpid();  
                  switch (pids.pid40) {
                      case -1: perror("Error en el fork 40"); exit(-1);
                      case 0:
                          // Proceso 42 hijo del 40
                          pids.pid42 = fork();
                          pids.pid40=getpid();  
                          switch (pids.pid42) {
                              case -1: perror("Error en el fork 42"); exit(-1);
                              case 0:
                                  pids.pid46 = fork();
                                  pids.pid42 = getpid();  
                                  switch (pids.pid46) {
                                      case -1: perror("Error en el fork 46"); exit(-1);
                                      case 0:
                                          pids.pid50 = fork();
                                          pids.pid46 = getpid(); 
                                          switch (pids.pid50) {
                                              case -1: perror("Error en el fork 50"); exit(-1);
                                              case 0:
                                                  pids.pid54 = fork();
                                                  pids.pid50 = getpid();  
                                                  switch (pids.pid54) {
                                                      case -1: perror("Error en el fork 54"); exit(-1);
                                                      case 0:
                                                          pids.pid56 = fork();
                                                          pids.pid54 = getpid();  
                                                          switch (pids.pid56) {
                                                              case -1: perror("Error en el fork 56"); exit(-1);
                                                              case 0:
                                                                  pids.pid57 = fork();
                                                                  pids.pid56 = getpid();  
                                                                  switch (pids.pid57) {
                                                                      case -1: perror("Error en el fork 57"); exit(-1);
                                                                      case 0:
                                                                          pids.pid58 = fork();
                                                                          pids.pid57 = getpid();  
                                                                          switch (pids.pid58) {
                                                                              case -1: perror("Error en el fork 58"); exit(-1);
                                                                              case 0:
                                                                                    pids.pid58 = getpid();
                                                                                    sigsuspend(&maskusr1);  // Proceso hoja
                                                                                default:
                                                                                    sigsuspend(&maskusr1);  
                                                                            }
                                                                        default:
                                                                            shared_data->pids[2]=getpid();
                                                                            sigsuspend(&maskusr1);
                                                                    }
                                                                default:
                                                                    shared_data->pids[1]=getpid();
                                                                    sigsuspend(&maskusr1);
                                                            }
                                                        default:
                                                            sigsuspend(&maskusr1); 
                                                    }
                                                default:
                                                    sigsuspend(&maskusr1);
                                            }
                                        default:
                                            sigsuspend(&maskusr1);
                                    }
                                default:
                                    // Volver a proceso 40 para crear el hijo adicional 43
                                    pids.pid43 = fork();  
                                    switch (pids.pid43) {
                                        case -1: perror("Error en el fork 43"); exit(-1);
                                        case 0:
                                            pids.pid47 = fork();
                                            pids.pid43 = getpid();  
                                            switch (pids.pid47) {
                                                case -1: perror("Error en fork 47"); exit(-1);
                                                case 0:
                                                    pids.pid51 = fork();
                                                    pids.pid47 = getpid();  
                                                    switch (pids.pid51) {
                                                        case -1: perror("Error en el fork 51"); exit(-1);
                                                        case 0:
                                                            pids.pid51 = getpid();
                                                            sigsuspend(&maskusr1); 
                                                        default:
                                                            sigsuspend(&maskusr1);
                                                    }
                                                default:
                                                    sigsuspend(&maskusr1);
                                            }
                                        default:
                                            sigsuspend(&maskusr1);                                          
                                    }
                            }
                        default:
                            // Volver a proceso 39 para crear el hermano de 40, que es 41
                            pids.pid41 = fork();  
                            switch (pids.pid41) {
                                case -1: perror("Error en el fork 41"); exit(-1);
                                case 0:
                                    pids.pid44 = fork();
                                    pids.pid41 = getpid();  
                                    switch (pids.pid44) {
                                        case -1: perror("Error en el fork 44"); exit(-1);
                                        case 0:
                                            pids.pid48 = fork();  
                                            pids.pid44 = getpid();
                                            switch (pids.pid48) {
                                                case -1: perror("Error en fork 48"); exit(-1);
                                                case 0:
                                                    pids.pid52 = fork();
                                                    pids.pid48 = getpid();  
                                                    switch (pids.pid52) {
                                                        case -1: perror("Error en el fork 52"); exit(-1);
                                                        case 0:
                                                            pids.pid55 = fork();
                                                            pids.pid52 = getpid();  
                                                            switch (pids.pid55) {
                                                                case -1: perror("Error en el fork 55"); exit(-1);
                                                                case 0:
                                                                    pids.pid55 = getpid();
                                                                    shared_data->pids[3]=getpid();   
                                                                    sigsuspend(&maskusr1); 
                                                                    
                                                                default:
                                                                    sigsuspend(&maskusr1);  
                                                            }
                                                        default:
                                                            sigsuspend(&maskusr1);
                                                    }
                                                default:
                                                    sigsuspend(&maskusr1);           
                                            }
                                        default:
                                            // Hijo 45 de 41
                                            pids.pid45 = fork();  
                                            switch (pids.pid45) {
                                                case -1: perror("Error en el fork 45"); exit(-1);
                                                case 0:
                                                    pids.pid49 = fork();  
                                                    pids.pid45 = getpid();
                                                    switch (pids.pid49) {
                                                        case -1: perror("Error en fork 49"); exit(-1);
                                                        case 0:
                                                            pids.pid53 = fork();
                                                            pids.pid49 = getpid();  
                                                            switch (pids.pid53) {
                                                                case -1: perror("Error en el fork 53"); exit(-1);
                                                                case 0:
                                                                    pids.pid53 = getpid();
                                                                    char *mensaje = "Todos los procesos creados correctamente\n";
                                                                    write(STDOUT_FILENO, mensaje, 41);
                                                                    sigsuspend(&maskusr1);
                                                                    
                                                                default:
                                                                    sigsuspend(&maskusr1);   
                                                            }
                                                        default:
                                                            sigsuspend(&maskusr1);    
                                                    }
                                                default:
                                                    sigsuspend(&maskusr1);  
                                            }
                                    }
                                default:
                                    sigsuspend(&maskusr1);          
                            }
                        // Fin del default del proceso 39
                        sigsuspend(&maskusr1);
                    }
                // Default proceso 39
                default:
                    sigsuspend(&maskusr1);               
            }
        // Default proceso 38
        default:
            sigsuspend(&maskusr1);             
    }
    return 0;
}



// MANEJADORES DE SIGTERM
void sigusrHandler1(int sig) {
    if(getpid()==pids.pid58)
    {
        // Liberamos memoria compartida
        munmap((void *)shared_data, sizeof(shared_info));
        // Eliminamos el archivo
        eliminarArchivo();
        // Mensaje confirmacion
        char *mensaje = "Todos los procesos han sido liberados\n";
        write(STDOUT_FILENO, mensaje, 39);
        exit(0);
    }

    if(getpid()==pids.pid57)
    {
        kill(pids.pid58,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid56)
    {
        kill(pids.pid57,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid55)
    {
        kill(shared_data->pids[2],SIGTERM);
        exit(0);
    }  
    if(getpid()==pids.pid53)
    {
        kill(shared_data->pids[3],SIGTERM);
        exit(0);
    }
    if(getpid()==pids.pid49)
    {
        kill(pids.pid53,SIGTERM);
        exit(0);
    } 

    if(getpid()==pids.pid45)
    {
        kill(pids.pid49,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid52)
    {
        exit(0);
    }
    if(getpid()==pids.pid48)
    {
        kill(pids.pid52,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid44)
    {
        kill(pids.pid48,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid41)
    {
        kill(pids.pid44,SIGTERM);
        kill(pids.pid45,SIGTERM);

        exit(0);
    }
    if(getpid()==pids.pid54)
    {
        exit(0);
    }
    
    if(getpid()==pids.pid51)
    {
        kill(shared_data->pids[1],SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid47)
    {
        kill(pids.pid51,SIGTERM);
        exit(0);
    }
    if(getpid()==pids.pid43)
    {
        kill(pids.pid47,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid50)
    {
        exit(0);
    }
    if(getpid()==pids.pid46)
    {
        kill(pids.pid50,SIGTERM);
        exit(0);
    }
    if(getpid()==pids.pid42)
    {
        kill(pids.pid46,SIGTERM);
        exit(0);
    }

    if(getpid()==pids.pid40)
    {
        kill(pids.pid42,SIGTERM);
        kill(pids.pid43,SIGTERM);
        exit(0);
    }
    if(getpid()==pids.pid39)
    {
            kill(pids.pid40,SIGTERM);
            kill(pids.pid41,SIGTERM);
        exit(0);


    }
    if(getpid()==pids.pid38)
    {
        kill(pids.pid39,SIGTERM);
        exit(0);

    }
    if(getpid()==pids.pid37)
    {
        kill(pids.pid38,SIGTERM);
        exit(0);
    }
}

// MANEJADORES DE SIGUSR2 (MATAR A N2 Y N3)
void sigusrHandler2(int sig) { 
    printf("Terminando proceso...");
}

void eliminarArchivo() {
    const char *fileName = "pids.txt";
    if (remove(fileName) == 0) {
        char *mensaje = "Fichero eliminado correctamente\n";
        write(STDOUT_FILENO, mensaje, 33);

    } else {
        perror("Error al eliminar el archivo");
    }
}
