#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#include "jugador.h"

/*
Descripcion: 
Se solicita ingresar una instruccion, 1 para obtener el estado de los jugadores
y 2 para atacarse entre jugadores, se ejecuta mientras exista más de un jugador vivo.
Cuando queda solamente un jugador, el programa termina señalando al ganador

Parametros:

int n_jugadores: cantidad de jugadores
int escuchar[]: donde el padre recibe lo que manda el hijo (escucha hijo)
int pedir[]: donde el padre pide informacion al hijo

Retorno: 
No retorna nada
*/

void padre(int n_jugadores, int escuchar[], int pedir[]){
    int vivos = 4;
    int a = 8;
    int contador_rondas = 0;
    while(1){
        int instruccion;
        char guardar_leido[1024];
        int guardar_leido_int;
        int ganador;

        printf("--------------- RONDA %d----------------------- \n", contador_rondas);
        printf("----------------------------------------------\n");
        printf("1: Mostrar stats de jugadores\n2: Atacar\n");
        scanf("%d", &instruccion);
        printf("----------------------------------------------\n");

        //Imprimir vida de jugadores en cada ronda
        for(int i=0; i<n_jugadores; i++){
            write(pedir[i], (char*)&a, sizeof(a));
            read(escuchar[i], guardar_leido, sizeof(guardar_leido));
            printf("La vida del jugador %d es %s\n",i,guardar_leido);
        }

        printf("----------------------------------------------\n");
        
        for(int i = 0; i < n_jugadores; i++){
            if (instruccion == 1){ //Mostrar datos jugadores
                write(pedir[i], (char*)&instruccion, sizeof(instruccion));
                read(escuchar[i], guardar_leido, sizeof(guardar_leido));
                printf("%s",guardar_leido);
            } else if (instruccion == 2){ //Ataques
                int jugador_atacado;
                int evasion_atacado;
                int defensa_atacado;
                int vida_atacado;
                int ataque_jugador_act;
                srand(time(NULL)+i);
                int aleatorio = rand() %101;
                
                while(i < n_jugadores){  //Verificar el estado (vivo = 1/muerto = 0) del leido antes de jugar
                    instruccion = 5;
                    write(pedir[i], (char*)&instruccion, sizeof(instruccion));
                    read(escuchar[i], guardar_leido, sizeof(guardar_leido));
                    guardar_leido_int = atoi(guardar_leido);
                    if(guardar_leido_int == 0){
                        i++; 
                    } else{
                        break;
                    }
                }
                
                if (i == 4){ //Caso en que el jugador 3 muera
                    break;
                }

                instruccion = 2;

                if(i == 0){    //Jugador controlado por consola
                    printf("elige a un jugador para atacar ");
                    scanf("%d", &jugador_atacado);
                } else {       //Jugador atacado elegido de manera aleatoria 
                    do {
                        jugador_atacado = rand() %4+0;
                        instruccion = 5;
                        write(pedir[jugador_atacado], (char*)&instruccion, sizeof(instruccion));
                        read(escuchar[jugador_atacado], guardar_leido, sizeof(guardar_leido));
                        guardar_leido_int = atoi(guardar_leido);
                    } while (!(jugador_atacado != i && guardar_leido_int == 1));
                }
                
                instruccion = 2;

                //pide ataque a jugador i
                write(pedir[i], (char*)&instruccion, sizeof(instruccion));
                read(escuchar[i],guardar_leido, sizeof(guardar_leido));

                printf("El jugador %d atacara al jugador %d\n", i, jugador_atacado);

                ataque_jugador_act = atoi(guardar_leido);
                
                //pide evasion, defensa y vida del jugador atacado
                instruccion = 3;
                write(pedir[jugador_atacado],(char*)&instruccion,sizeof(instruccion));
                read(escuchar[jugador_atacado],guardar_leido, sizeof(guardar_leido));
                sscanf(guardar_leido, "%d %d %d", &evasion_atacado, &defensa_atacado,&vida_atacado);

                if (evasion_atacado < aleatorio){   //Caso en que se esquiva el ataque
                    printf("el jugador ha esquivado tu ataque! \n----------------------------------\n");
                } else {                            //Caso en que se lleva a cabo el ataque
                    int daño = ataque_jugador_act - defensa_atacado;
                    vida_atacado = vida_atacado - daño;
                    instruccion = 4;
                    write(pedir[jugador_atacado], (char*)&instruccion, sizeof(instruccion));
                    write(pedir[jugador_atacado], (char*)&vida_atacado, sizeof(vida_atacado));
                    read(escuchar[jugador_atacado], guardar_leido, sizeof(guardar_leido));
                    //Vida del jugador atacado después de ser atacado
                    printf("la VIDA del jugador atacado es %s\n----------------------------------\n", guardar_leido);

                    guardar_leido_int = atoi(guardar_leido);
                    if (guardar_leido_int <= 0){    //Caso cuando el jugador atacado muere
                        instruccion = 6;
                        int estado_jugador = 0;
                        write(pedir[jugador_atacado], (char*)& instruccion, sizeof(instruccion));
                        write(pedir[jugador_atacado], (char*)&estado_jugador, sizeof(estado_jugador));
                        read(escuchar[jugador_atacado], guardar_leido, sizeof(guardar_leido));
                        printf("El jugador %d ha muerto\n--------------\n",jugador_atacado);
                        vivos--;
                        ganador = i; //Guarda último jugador que mató a otro
                    }
                }
                instruccion = 2;
            }
        }
        if (vivos == 1){            //Caso cuando gana un jugador
                        instruccion = 7;
                        write(pedir[ganador], (char*)&instruccion, sizeof(instruccion));
                        read(escuchar[ganador], guardar_leido, sizeof(guardar_leido));
                        guardar_leido_int = atoi(guardar_leido);
                        printf("El jugador %d ha ganado\n-------------\nEL JUEGO HA TERMINADO\n-------------\n", guardar_leido_int);
                        break;
        }else if (instruccion != 1){   //Aún quedan jugadores para continuar el juego
            printf("-------------- SIGUIENTE RONDA --------------- \n");
            contador_rondas ++;
        }
    }
}
