# Grupo-29

## Integrantes:
* Romina Aguilera - 202173572-0 - 201
* Geraldine Cornejo - 202173529-1 - 200

## Especificación de los nombres de los archivos:
* main.c : Archivo principal del programa, donde se llaman a otras funciones (resto de archivos).
* directorio_letra.h : Función utilizada en main. Crea las carpetas de /Alfabetico/ desde la A a la Z.
* Alfabetico.h : Función utilizazda en main. Recorre la carpeta Sprites y duplica los archivos ubicándolos en la carpeta correspondiente (Ejemplo: /Alfabetico/A).
* Generacion.h : Función utilizada en main. Recorre la carpeta Sprites, identifica el número dentro del nombre de cada archivo y según la clasificación los mueve al directorio correspondiente (Ejemplo: /Generacion/I).
* contar_alfabeticos.h : Función utilizada en main. Recorre el directorio /Alfabetico/ y por cada carpeta cuenta los archivos en su interior, para luego escribir la información en RegistroPokemon.txt.
* contar_generacion.h : Función utilizada en main. Similar a contar_alfabeticos.h, pero en el directorio /Generacion/.

## Instrucciones generales de compilación y uso
* El programa debe ser ejecutado en un directorio junto a la carpeta Sprites y no dentro de esta última.
* El programa solo se puede ejecutar una vez, si se desea volver a ejecutar, se deben borrar las carpetas Sprites, Alfabético y Generación; luego copiar la carpeta Sprites original dentro del directorio, ya que una vez ejecutado el programa la carpeta queda vacía y por terminal se imprimen errores de que no se pueden crear las carpetas solicitadas ni duplicar/mover los archivos.
* El programa fue creado y probado en Ubuntu 22.04 (VirtualBox).
* Desde la terminal, abrir directorio donde se encuentra el programa, escribir "make run" y este se ejecutará.

## Supuestos y notas de creador
* Los archivos en la carpeta Sprites seguiran el siguiente formato: nombre_número.png, con número entre los valores 1 y 493, incluyéndolos.
* Para efecto de la creación de las sub carpetas tanto en Alfabetico como en Generacion, si una no cuenta con algún archivo esta igual será creada y quedará vacía.
