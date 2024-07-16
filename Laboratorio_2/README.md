# Grupo-29

## Integrantes:
* Romina Aguilera - 202173572-0 - 201
* Geraldine Cornejo - 202173529-1 - 200

## Especificación de los nombres de los archivos:
* main.c : Programa principal donde se crean los procesos hijos.
* hijo.h: Archivo con instrucciones a realizar por los procesos hijos.
* padre.h: Lo que ejecuta el proceso padre y le da estructura al juego
* jugador.h: Archivo con definicion de un struct Jugador con el fin de dar una estructura a cada hijo

## Instrucciones generales de compilación y uso
* El programa fue creado y probado en Ubuntu 22.04 (VirtualBox).
* Desde la terminal, abrir directorio donde se encuentra el programa, escribir "make" y este se ejecutará. Si es segunda vez ejecutando escribir "make clean && make".
* El programa funciona con dos instrucciones, 1 para ver los stats de los jugadores en cualquier momento del juego y 2 para que los jugadores se ataquen.

## Supuestos y notas de creador
* El jugador 0 es el controlado por terminal.
* Se asume que el jugador 0 no eligirá atacarse a si mismo.
* Se asume que el jugador controlado no atacará a jugadores muertos
