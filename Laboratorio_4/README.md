# Grupo-29

## Integrantes:
* Romina Aguilera - 202173572-0 - 201
* Geraldine Cornejo - 202173529-1 - 200

## Especificación de los nombres de los archivos:
* main.py : Archivo que contiene la simulacióm, junto a las funciones necesarias.
* clases.py : Archivo que contiene clases utilizadas en el main, explicadas dentro del mismo.

## Instrucciones generales de compilación y uso:
* Para compilar y usar el laboratorio se proporcionó un makefile.
* Usar los siguientes comandos en la terminal:
1. make run / make : para compilar y ejecutar el programa.
2. make clean run : para borrar archivos txt y volver a compilar y ejecutar el programa.

## Supuestos y notas de creador
* Laboratorio testeado en ubuntu 22.04.4
* Si bien en la sección anterios se da la opción de borrar los archivos txt, el programa de por sí escribe desde cero el archivo cada vez que se compila, aún así como medida de seguridad y correcto funcionamiento se utiliza el comando clean.
* Si se desea cambiar la cantidad de piratas, se debe cambiar la variable "totalPiratas" que se encuentra en el archivo main.py
