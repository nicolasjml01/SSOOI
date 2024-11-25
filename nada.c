                            pids.pid41 = fork();
                            switch (pids.pid41) {
                                case -1: perror("Error en el fork 41"); exit(-1);
                                case 0:
                                    printf("|_41: %d\n", getpid());
                                    pids.pid44 = fork();
                                    pids.pid41 = getpid();
                                    switch (pids.pid44) {
                                        case -1: perror("Error en el fork 44"); exit(-1);
                                        case 0:
                                            printf("|_44 %d\n", getpid());
                                            pids.pid48 = fork();
                                            pids.pid44 = getpid();
                                            switch (pids.pid48) {
                                                case -1: perror("Error en fork 48"); exit(-1);

                                                case 0:
                                                    printf("|_48: %d\n", getpid());
                                                    pids.pid52 = fork();
                                                    pids.pid48 = getpid();
                                                    switch (pids.pid52) {
                                                        case -1:
                                                            perror(
                                                                "Error en el "
                                                                "fork 52");
                                                            exit(-1);
                                                        case 0:
                                                            printf("|_52: %d\n", getpid());
                                                            pids.pid55 = fork();
                                                            pids.pid52 = getpid();
                                                            switch (pids.pid55) {
                                                                case -1:
                                                                    perror(
                                                                        "Error "
                                                                        "en el "
                                                                        "fork "
                                                                        "55");
                                                                    exit(-1);
                                                                case 0:
                                                                    printf(
                                                                        "|_55: "
                                                                        "%d\n",
                                                                        getpid());
                                                                    pids.pid55 = getpid();

                                                                    sigsuspend(&maskusr1);
                                                                    kill(pids.pid56,
                                                                         SIGTERM);  // Matar al proceso 38

                                                                    break;

                                                                default: sigsuspend(&maskusr1); kill(pids.pid52,
                                                                                                     SIGTERM);  // Proceso 48
                                                            }
                                                            break;

                                                        default:

                                                            sigsuspend(&maskusr1);
                                                            kill(pids.pid52,
                                                                 SIGTERM);  // PROCESO 48
                                                                            // al
                                                                            // proceso
                                                                            // 38
                                                    }

                                                default:

                                                    sigsuspend(&maskusr1);
                                                    kill(pids.pid48,
                                                         SIGTERM);  // Proceso 44
                                                                    //
                                            }

                                            break;

                                        default:
                                            pids.pid45 = fork();
                                            switch (pids.pid45) {
                                                case -1: perror("Error en el fork 45"); exit(-1);
                                                case 0:
                                                    printf("|_45: %d\n", getpid());
                                                    pids.pid49 = fork();
                                                    pids.pid45 = getpid();
                                                    switch (pids.pid49) {
                                                        case -1:
                                                            perror(
                                                                "Error en fork "
                                                                "49");
                                                            exit(-1);

                                                        case 0:
                                                            printf("|_49: %d\n", getpid());
                                                            pids.pid53 = fork();
                                                            pids.pid49 = getpid();
                                                            switch (pids.pid53) {
                                                                case -1:
                                                                    perror(
                                                                        "Error "
                                                                        "en el "
                                                                        "fork "
                                                                        "53");
                                                                    exit(-1);
                                                                case 0:
                                                                    printf(
                                                                        "|_53: "
                                                                        "%d\n",
                                                                        getpid());
                                                                    pids.pid53 = getpid();
                                                                    kill(pids.pid37, SIGUSR2);

                                                                    sigsuspend(&maskusr1);

                                                                    kill(pids.pid55, SIGTERM);

                                                                    break;

                                                                default: 
                                                                    sigsuspend(&maskusr1); 
                                                                    kill(pids.pid53, SIGTERM);  //proceso 49
                                                            }

                                                        default:
                                                            sigsuspend(&maskusr1);
                                                            kill(pids.pid49, SIGTERM);
                                                    }
                                                default: 
                                                    sigsuspend(&maskusr1); 
                                                    kill(pids.pid45, SIGTERM); 
                                            }
                                            kill(pids.pid44, SIGTERM);
                                    }
                                default: 
                                    sigsuspend(&maskusr1); 
                                    kill(pids.pid41, SIGTERM); // Matar proceso 41 del padre 39
                            }
                    