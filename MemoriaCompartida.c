#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// Biblioteca mmap
#include <sys/mman.h>
#include <fcntl.h>

// PROTOTIPO MANEJADORES
void sigusrHandler1(int sig);
void sigusrHandler2(int sig);

typedef struct {
    pid_t pids[3];              // Array para almacenar PIDs
    int count;                 // Número actual de PIDs almacenados
} shared_info;

// Variable global para la memoria compartida
shared_info *shared_data;

// VARIABLE GLOBAL
typedef struct {
    pid_t pid37;
    pid_t pid38;
    pid_t pid39;
    pid_t pid40;
    pid_t pid42;
    pid_t pid43;
    pid_t pid46;

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
    shared_data =(shared_info *) mmap(NULL, sizeof(shared_info), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
   close(fd);
    if (shared_data == MAP_FAILED) {
        perror("Error en mmap");
        exit(-1);
    }  

    

    // CREACION DE MANEJADORES Y CONFIGURACION
    struct sigaction susr1;
    susr1.sa_handler = &sigusrHandler1;
    susr1.sa_flags = SA_RESTART;  // NO LETAL

    struct sigaction susr2;
    susr2.sa_handler = &sigusrHandler2;
    susr2.sa_flags = SA_RESTART;  // NO LETAL


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

    // Inicializar la estructura compartida
    shared_data->count = 0;

    // CREACION DE PROCESOS
    pids.pid37 = getpid();
    printf("|_37: %d\n", pids.pid37);
    pids.pid38 = fork();  // Creación de 38

    switch (pids.pid38) {
        case -1:
            perror("Error en el fork 38");
            kill(pids.pid37, SIGKILL);  // Mata el proceso anterior en caso de error
            exit(-1);

        case 0:
            printf("|_38: %d\n", getpid());
            pids.pid39 = fork();  // Creación de 39
            pids.pid38 =getpid();
            switch (pids.pid39) {
                case -1: perror("Error en el fork 39"); exit(-1);
                case 0:
                    printf("|_39: %d\n", getpid());
                    
                    // Crear proceso 40 como hijo de 39
                    pids.pid40 = fork();
                    pids.pid39 = getpid();  
                    switch (pids.pid40) {
                        case -1: perror("Error en el fork 40"); exit(-1);
                        case 0:
                            printf("|_40: %d\n", getpid());
                            
                            // Crear el proceso 42 como hijo de 40
                            pids.pid42 = fork();
                            pids.pid40=getpid();  
                            switch (pids.pid42) {
                                case -1: perror("Error en el fork 42"); exit(-1);
                                case 0:
                                    printf("|_42: %d\n", getpid());
                                    
                                    // Crear el proceso 46 como hijo de 42
                                    pids.pid46 = fork();
                                    pids.pid42 = getpid();  
                                    switch (pids.pid46) {
                                        case -1: perror("Error en el fork 46"); exit(-1);
                                        case 0:
                                            printf("|_46: %d\n", getpid());
                                            shared_data->pids[shared_data->count++] = getpid();  // Registrar PID de 46
                                            //pids.pid46 = getpid(); 
                                            
                                        default:
                                            sigsuspend(&maskusr1);
                                            wait(NULL);
                                            
                                    }
                                default:
                                    // Volver a proceso 40 para crear el hijo adicional 43
                                    pids.pid43 = fork();  
                                    pids.pid43 = getpid();
                                    switch (pids.pid43) {
                                        case -1: perror("Error en el fork 43"); exit(-1);
                                        case 0:
                                            printf("|_43: %d\n", getpid());
                                        default:
                                            sigsuspend(&maskusr1);  
                                            wait(NULL);                                        
                                    }
                            }
                        default:  
                            sigsuspend(&maskusr1);
                            wait(NULL);
                    }
                default:
                    sigsuspend(&maskusr1);
                    wait(NULL);    
            }
        default:
            sigsuspend(&maskusr1);
            wait(NULL);
            
    }
    // Liberar la memoria compartida antes de salir
    if (getpid() == shared_data->pids[0]) {
        munmap((void *)shared_data, sizeof(shared_info));
    }

    return 0;

}



// MANEJADORES DE SIGTERM
void sigusrHandler1(int sig) { 
    
if(getpid()==pids.pid43)
{
    printf("muriendo %d...\n",getpid());
    printf("43 conoce el PID de 46: %d\n", shared_data->pids[0]);  // Accede directamente al PID de 46
    kill(shared_data->pids[1], SIGTERM);  // Matar al proceso 46
    exit(0);                                     
}

if(getpid()==pids.pid46)
{
    printf("muriendo %d...\n",shared_data->pids[0]);
    exit(0);
}

if(getpid()==pids.pid42)
{
    printf("muriendo %d...\n",getpid());
    exit(0);
}

if(getpid()==pids.pid40)
{
    printf("muriendo %d...\n",getpid());
    kill(pids.pid42,SIGTERM);
    kill(pids.pid43,SIGTERM);
    exit(0);
}
if(getpid()==pids.pid39)
{
    printf("muriendo %d...\n",getpid());
        kill(pids.pid40,SIGTERM);
        //kill(pids.pid40,SIGTERM);

    exit(0);


}
if(getpid()==pids.pid38)
{
    printf("muriendo %d...\n",getpid());
        kill(pids.pid39,SIGTERM);
        exit(0);

}
if(getpid()==pids.pid37)
{
    printf("muriendo %d...\n",getpid());
    kill(pids.pid38,SIGTERM);
    exit(0);
}

    

}

// MANEJADORES DE SIGUSR2 (MATAR A N2 Y N3)
void sigusrHandler2(int sig) { 
    printf("Terminando proceso...");
}

