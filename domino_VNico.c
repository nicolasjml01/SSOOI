#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

// PROTOTIPO MANEJADORES
void sigusrHandler1(int sig);
void sigusrHandler2(int sig);

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

    // CREACION DE PROCESOS
    pids.pid37 = getpid();
    printf("|_37: %d\n", pids.pid37);
    pids.pid38 = fork(); // Creacion de 38

    switch (pids.pid38)
    {
    case -1:

        perror("Error en el fork 38");
        kill(pids.pid37, SIGKILL);
        exit(-1);
        break;

    case 0:

        printf("|_38: %d\n", getpid());
        pids.pid39 = fork(); //Creacion de 39
        pids.pid38 = getpid();
        switch(pids.pid39)
        {
            case -1:
                perror("Error en el fork 39");
                exit(-1);
            case 0:
                printf("|_39: %d\n", getpid());
                pids.pid40 = fork();    //Creacion de 40
                pids.pid39 = getpid();
                switch(pids.pid40)
                {
                    case -1:
                        perror("Error en el fork 40");
                        exit(-1);
                    case 0:
                        printf("|_40 %d\n", getpid());
                        pids.pid42 = fork();    //Creacion de 42
                        pids.pid40 = getpid();
                        switch(pids.pid42)
                            {
                                case -1:
                                    perror("Error en el fork 42");
                                    exit(-1);
                                case 0:
                                    printf("|_42: %d\n", getpid());
                                    pids.pid46 = fork();    //Creacion de 46
                                    pids.pid42 = getpid();
                                    switch(pids.pid46)
                                    {
                                        case -1:
                                        perror("Error en el fork 46");
                                        exit(-1);
                                        case 0:
                                            printf("|_46: %d\n", getpid());
                                            pids.pid50 = fork(); //Creacion de 50
                                            pids.pid46 = getpid();
                                            switch(pids.pid50)
                                            {
                                                case -1:
                                                    perror("Error en el fork 50");
                                                    exit(-1);
                                                case 0:
                                                    printf("|_50: %d\n", getpid());
                                                    pids.pid54 = fork(); //Creacion de 54
                                                    pids.pid50 = getpid();
                                                    switch(pids.pid54)
                                                    {
                                                        case -1:
                                                            perror("Error en el fork 54");
                                                            exit(-1);
                                                        case 0:
                                                            printf("|_54: %d\n", getpid());
                                                            pids.pid56 = fork(); //Creacion de 56
                                                            pids.pid54 = getpid();
                                                        switch(pids.pid56)
                                                        {
                                                            case -1:
                                                                perror("Error en el fork 56");
                                                                exit(-1);
                                                            case 0:
                                                                printf("|_56: %d\n", getpid());
                                                                pids.pid57 = fork(); //creacion de 57
                                                                pids.pid56 = getpid();
                                                                switch(pids.pid57)
                                                                {
                                                                    case -1:
                                                                    perror("Error en el fork 57");
                                                                    exit(-1);
                                                                case 0:
                                                                    printf("|_57: %d\n", getpid());
                                                                    pids.pid58 = fork();    //creacion de 58
                                                                    pids.pid57 = getpid();
                                                                    switch(pids.pid58)
                                                                    {
                                                                        case -1:
                                                                            perror("Error en el fork 58");
                                                                            exit(-1);
                                                                        case 0:
                                                                            printf("|_58: %d\n", getpid());
                                                                            pids.pid58 = getpid();
                                                                        
                                                                            

                                                                            while (1)
                                                                            {
                                                                                sigsuspend(&maskusr1);
                                                                            }
                                                                        break;
                                                                        
                                                                        default:
                                                                            while (1)
                                                                            {   
                                                                                sigsuspend(&maskusr1);
                                                                                
                                                                            }
                                                                        break;


                                                                    }
                                                                default:
                                                                    while (1)
                                                                    {   
                                                                        sigsuspend(&maskusr1);
                                                                        
                                                                    }
                                                                break;
                                                                }
                                                            default:
                                                                while (1)
                                                                {   
                                                                    sigsuspend(&maskusr1);
                                                                    
                                                                }
                                                            break;
                                                        }
                                                    default:
                                                        while (1)
                                                        {   
                                                            sigsuspend(&maskusr1);
                                                            
                                                        }
                                                    break;
                                                    }
                                            default:
                                                while (1)
                                                {   
                                                    sigsuspend(&maskusr1);
                                                    
                                                }
                                            break;
                                            }
                                        default:
                                            while (1)
                                            {   
                                                sigsuspend(&maskusr1);
                                                
                                            }
                                            break;
                                    }
                                default:
                                    pids.pid43 = fork();
                                    switch(pids.pid43)
                                    {
                                        case -1:
                                            perror("Error en el fork 43");
                                            exit(-1);
                                        case 0:
                                            printf("|_43: %d\n", getpid());
                                            pids.pid47 = fork();
                                            pids.pid43 = getpid();
                                            switch(pids.pid47)
                                            {
                                                case -1:
                                                    perror("Error en fork 47");
                                                    exit(-1);

                                                case 0:
                                                    printf("|_47: %d\n", getpid());
                                                    pids.pid51 = fork();
                                                    pids.pid47 = getpid();
                                                    switch(pids.pid51)
                                                    {
                                                        case -1:
                                                        perror("Error en el fork 51");
                                                                exit(-1);
                                                        case 0:
                                                            printf("|_51: %d\n", getpid());
                                                            pids.pid51 = getpid();
                                                            while (1)
                                                            {   
                                                                sigsuspend(&maskusr1);
                                                                
                                                            }
                                                        break;

                                                        default:
                                                            while (1)
                                                            {   
                                                                sigsuspend(&maskusr1);
                                                                
                                                            }
                                                        break;                                   
                                                    }

                                                default:
                                                    while (1)
                                                    {   
                                                        sigsuspend(&maskusr1);
                                                        
                                                    }
                                                break;

                                            }
                                        default:
                                            while (1)
                                                {   
                                                    sigsuspend(&maskusr1);
                                                    
                                                }
                                           // wait(NULL);
                                        //break;
                                    }
                                //wait(NULL);
                                //break;
                            }
                    default:
                        pids.pid41 = fork();
                        switch(pids.pid41)
                        {
                            case -1:
                                perror("Error en el fork 41");
                                exit(-1); 
                            case 0:
                                printf("|_41: %d\n",getpid());
                                pids.pid44 = fork();
                                pids.pid41 = getpid();
                                switch(pids.pid44)
                                {
                                    case -1:
                                        perror("Error en el fork 44");
                                        exit(-1);
                                    case 0:
                                        printf("|_44 %d\n", getpid());
                                        pids.pid48 = fork();
                                        pids.pid44 = getpid();
                                        switch(pids.pid48)
                                                {
                                                    case -1:
                                                        perror("Error en fork 48");
                                                        exit(-1);

                                                    case 0:
                                                        printf("|_48: %d\n", getpid());
                                                        pids.pid52 = fork();
                                                        pids.pid48 = getpid();
                                                        switch(pids.pid52)
                                                        {
                                                            case -1:
                                                            perror("Error en el fork 52");
                                                                    exit(-1);
                                                            case 0:
                                                                printf("|_52: %d\n", getpid());
                                                                pids.pid55 = fork();
                                                                pids.pid52 = getpid();
                                                                switch(pids.pid55)
                                                                {
                                                                    case -1: 
                                                                        perror("Error en el fork 55");
                                                                        exit(-1);
                                                                    case 0:
                                                                        printf("|_55: %d\n", getpid());
                                                                        pids.pid55 = getpid();
                                                                        while (1)
                                                                        {   
                                                                            sigsuspend(&maskusr1);
                                                                            
                                                                        }
                                                                    break;

                                                                    default:
                                                                        while (1)
                                                                        {   
                                                                            sigsuspend(&maskusr1);
                                                                            
                                                                        }
                                                                    break;      
                                                                }
                                                            break;

                                                            default:
                                                                while (1)
                                                                {   
                                                                    sigsuspend(&maskusr1);
                                                                    
                                                                }
                                                            break;                                   
                                                        }

                                                    default:
                                                        while (1)
                                                        {   
                                                            sigsuspend(&maskusr1);
                                                            
                                                        }
                                                    break;

                                                }

                                        break;

                                    default:
                                       pids.pid45 = fork();
                                        switch(pids.pid45)
                                        {
                                            case -1:
                                                perror("Error en el fork 45");
                                                exit(-1);
                                            case 0:
                                                printf("|_45: %d\n", getpid());
                                                pids.pid49 = fork();
                                                pids.pid45 = getpid();
                                                switch(pids.pid49)
                                                {
                                                    case -1:
                                                        perror("Error en fork 49");
                                                        exit(-1);

                                                    case 0:
                                                        printf("|_49: %d\n", getpid());
                                                        pids.pid53 = fork();
                                                        pids.pid49 = getpid();
                                                        switch(pids.pid53)
                                                        {
                                                            case -1:
                                                            perror("Error en el fork 53");
                                                                    exit(-1);
                                                            case 0:
                                                                printf("|_53: %d\n", getpid());
                                                                pids.pid53 = getpid();

                                                                kill(pids.pid37, SIGUSR2);
                                                                
                                                                while (1)
                                                                {   
                                                                    sigsuspend(&maskusr1);
                                                                    
                                                                }
                                                            break;

                                                            default:
                                                                while (1)
                                                                {   
                                                                    sigsuspend(&maskusr1);
                                                                }
                                                            break;                                   
                                                        }

                                                    default:
                                                        while (1)
                                                        {   
                                                            sigsuspend(&maskusr1);
                                                            
                                                        }
                                                    break;

                                                }
                                            default:
                                                while (1)
                                                    {   
                                                        sigsuspend(&maskusr1);
                                                        
                                                    }

                                            break;
                                        }
                                        break;   
                                }

                            default:
                                while (1)
                                {   
                                    sigsuspend(&maskusr1);
                                }
                            //break;
                            //wait(NULL);


                        }

                }
            default:
                while(1)
                {
                    sigsuspend(&maskusr1);


                }

            //break;
            //wait(NULL);

        }

        while (1)
        {
            sigsuspend(&maskusr1);
            
        }
        break;

    default:


        while (1)
                {
                    sigsuspend(&maskusr2);
                }        

        //wait(NULL);

    }
}



// MANEJADORES DE SIGTERM
void sigusrHandler1(int sig)
{
    
    if (sig == SIGTERM){ 
        if (getpid() == pids.pid58)
        {
            puts("Terminando proceso 58...");
            sleep(1);
            exit(0);

        }
                if (getpid() == pids.pid57)
        {
            puts("Terminando proceso 57...");
            kill(pids.pid58, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid56)
        {
            puts("Terminando proceso 56...");
            kill(pids.pid52, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid55)
        {
            puts("Terminando proceso 55...");
            kill(pids.pid56, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid53)
        {
            puts("Terminando proceso 53...");
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid49)
        {
            puts("Terminando proceso 49...");
            kill(pids.pid52, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid45)
        {
            puts("Terminando proceso 45...");
            kill(pids.pid49, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid52)
        {
            puts("Terminando proceso 52...");
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid48)
        {
            puts("Terminando proceso 48...");
            kill(pids.pid52, SIGTERM);
            sleep(1);
            exit(0);

        }if (getpid() == pids.pid44)
        {
            puts("Terminando proceso 44...");
            kill(pids.pid48, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid44)
        {
            puts("Terminando proceso 44...");
            kill(pids.pid48, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid41)
        {
            puts("Terminando proceso 41...");
            kill(pids.pid44, SIGTERM);
            kill(pids.pid45, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid54)
        {
            puts("Terminando proceso 54...");
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid51)
        {
            puts("Terminando proceso 51...");
            kill(pids.pid54, SIGTERM);
            sleep(1);
            exit(0);

        }
         if (getpid() == pids.pid47)
        {
            puts("Terminando proceso 47...");
            kill(pids.pid51, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid43)
        {
            puts("Terminando proceso 43...");
            kill(pids.pid47, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid50)
        {
            puts("Terminando proceso 50...");
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid46)
        {
            puts("Terminando proceso 46...");
            kill(pids.pid50, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid42)
        {
            puts("Terminando proceso 42...");
            kill(pids.pid46, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid40)
        {
            puts("Terminando proceso 40...");
            kill(pids.pid42, SIGTERM);
            kill(pids.pid43, SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid39)
        {
            puts("Terminando proceso 39...");
            kill(pids.pid41, SIGTERM);
            kill(pids.pid40,SIGTERM);
            sleep(1);
            exit(0);

        }
        if (getpid() == pids.pid38)
        {
            puts("terminando proceso 38...");
            kill(pids.pid39, SIGTERM);
            sleep(1);
            exit(0);

        }
        
        

    }
    else
    {
        puts("ERROR EN SIGTERM");
    }
}

// MANEJADORES DE SIGUSR2 (MATAR A N2 Y N3)
void sigusrHandler2(int sig)
{
     if (sig == SIGUSR2 && getpid() == pids.pid37)
    {
        puts("Terminando proceso 37...");
        kill(pids.pid38, SIGTERM);
        exit(0);


    }
    else
    {
        puts("ERROR EN SIGTERM");
    }

}
