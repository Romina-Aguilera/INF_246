#include <stdio.h>
#include <sys/types.h>

#ifndef JUGADOR_H
#define JUGADOR_H

typedef struct{
    pid_t pid;
    int vida;
    int ataque;
    int defensa;
    int evasion;
    int estado;
    int numero;
} Jugador;

#endif