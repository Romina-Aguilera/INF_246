#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "directorio_letra.h"
#include "Alfabetico.h"
#include "Generacion.h"
#include "contar_alfabeticos.h"
#include "contar_generacion.h"

int main(){
    DIR *dir, *dir2, *dir4;
    //struct dirent *ent;

    //Creacion de directorio Alfabetico
    if (mkdir("Alfabetico", 0777) == 0){
    } else{
        printf("Error al crear la carpeta.\n");
    }

    //Creacion de directorio Generación
    if (mkdir("Generacion", 0777) == 0) {
    } else {
        printf("Error al crear la carpeta.\n");
    }

    //Creacion de cada directorios dentro de alfabetico
    crear_directorio_letra();

    //Creacion de cada directorio de generacion
    if (mkdir("./Generacion/I", 0777) == 0) {}
        //printf("Carpeta Generacion/I creada exitosamente \n");}
    if (mkdir("./Generacion/II", 0777) == 0) {}
        //printf("Carpeta Generacion/II creada exitosamente \n");}
    if (mkdir("./Generacion/III", 0777) == 0) {}
        //printf("Carpeta Generacion/III creada exitosamente \n");}
    if (mkdir("./Generacion/IV", 0777) == 0) {}
        //printf("Carpeta Generacion/IV creada exitosamente \n");}

    dir = opendir("./Sprites");

    //verificar que el archivo exista en el directorio
    if (dir == NULL){
        perror("Error al abrir el directorio");
        return 1;
    }
    // Ordenar los pokemones de manera alfabetica
    Alfabetico(dir);
    closedir(dir);

    // Ordenar los pokmemones según generación
    dir2 = opendir("./Sprites");
    if (dir2 == NULL){
        perror("Error al abrir el directorio");
        return 1;
    }
    Generacion(dir2);
    closedir(dir2);
    
    //Contar los archivos de cada carpeta
    contar_alfabeticos();
    
    dir4 = opendir("./Generacion");
    struct dirent *read;
    FILE *registro = fopen("RegistroPokemon.txt", "a");
    fprintf(registro,"Generación\n");
    fclose(registro);
    while((read = readdir(dir4)) != NULL){
        if (strcmp(read->d_name, ".") == 0 || strcmp(read->d_name, "..") == 0) {
            continue;
        }
        contar_generacion(read->d_name);}
    return 0;

}
