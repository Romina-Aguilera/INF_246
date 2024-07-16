#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#include "jugador.h"
#include "hijo.h"
#include "padre.h"

int main(){
    int n_jugadores = 4;
    int escuchar[4];
    int pedir[4];

    for(int i = 0; i < n_jugadores ;i++){
        int fd_1[2]; //padre a hijo
        int fd_2[2]; // hijo al padre
        pipe(fd_1);
        pipe(fd_2);
        pid_t pid = fork();

        if(pid < 0){
            printf("Error al crear el proceso");
        } else if (pid == 0){
            close (fd_2[0]);
            close (fd_1[1]);
            hijo(i, fd_2[1], fd_1[0]);
            exit(0);
        }
        close(fd_2[1]);
        close(fd_1[0]);
        pedir[i] = fd_1[1];
        escuchar[i] = fd_2[0];
    }
    padre(n_jugadores, escuchar, pedir);
    return 0;
}