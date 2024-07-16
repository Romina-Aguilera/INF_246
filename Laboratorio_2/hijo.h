#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#include "jugador.h"

/*
Descripcion:
Dependiendo de la instruccion que ha solicitado el padre, el hijo le envía una cadena
con los datos solicitados, a través de la tubería

Parametros:

int i: numero_hijo
int escritura_p: donde el hijo envía los datos al padre (envia padre)
int lectura_p: donde el hijo lee los datos solicitados por el padre (escucha padre)

Retorno:
No retorna nada
*/

void hijo(int i, int escritura_p, int lectura_p){
    int datos_lectura;
    //Designar datos de los procesos
    srand(time(NULL) + i);
    Jugador jugador_actual;
    jugador_actual.vida = 100;
    jugador_actual.ataque = rand() %11+30;
    jugador_actual.defensa = rand()%16+10;
    jugador_actual.evasion = 60 - jugador_actual.defensa;
    jugador_actual.estado = 1;
    jugador_actual.numero = i;

    while(1){
        //escuchar Instrucción a realizar
        read(lectura_p, (char*)&datos_lectura, sizeof(datos_lectura));
        char buffer [1024];

        if (datos_lectura == 1){
            //Entregar stats de los jugadores
            sprintf((char*)&buffer,"Jugador: %d\n vida: %d\n ataque: %d\n defensa: %d\n evasion: %d\n-------\n", i, jugador_actual.vida, jugador_actual.ataque, jugador_actual.defensa, jugador_actual.evasion);
            write(escritura_p, buffer, sizeof(buffer));

        } else if (datos_lectura == 2){
            //Obtener ataque
            sprintf((char*)&buffer, "%d", jugador_actual.ataque);
            write(escritura_p, buffer, sizeof(buffer));

        } else if(datos_lectura ==3 ){
            //Obtener datos de jugador atacado
            sprintf((char*)&buffer,"%d %d %d",jugador_actual.evasion,jugador_actual.defensa,jugador_actual.vida);
            write(escritura_p, buffer, sizeof(buffer));

        } else if (datos_lectura == 4){
            //Actualizar vida después de un ataque
            read(lectura_p, (char*)&datos_lectura, sizeof(datos_lectura));
            jugador_actual.vida = datos_lectura;
            sprintf((char*)&buffer,"%d", jugador_actual.vida);
            write(escritura_p, buffer, sizeof(buffer));

        } else if (datos_lectura == 5){
            //Obtener estado del jugador (vivo = 1/muerto = 0)
            sprintf((char*)&buffer, "%d", jugador_actual.estado);
            write(escritura_p, buffer, sizeof(buffer));

        } else if(datos_lectura == 6){
            //Actualizar estado de jugador (vivo = 1/muerto = 0)
            read(lectura_p, (char*)&datos_lectura, sizeof(datos_lectura));
            jugador_actual.estado = datos_lectura;
            sprintf((char*)&buffer, "%d", jugador_actual.estado);
            write(escritura_p, buffer, sizeof(buffer));

        } else if (datos_lectura == 7){
            //Obtener número de jugador
            sprintf((char*)&buffer, "%d", jugador_actual.numero);
            write(escritura_p, buffer, sizeof(buffer));

        } else if (datos_lectura == 8){
            //Obtener vida de jugador
            sprintf((char*)&buffer, "%d", jugador_actual.vida);
            write(escritura_p, buffer, sizeof(buffer));
        }
    }
}
