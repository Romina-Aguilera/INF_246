#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/*
Descripcion: 
Distribuye los pokemones según su generación

Parametros:
DIR *dir: directorio donde estan los datos a ordenar

Retorno: 
No retorna nada
*/

void Generacion(DIR* dir){
    struct dirent *read;

    while((read = readdir(dir))!= NULL){
        char path [1024];
        snprintf(path, sizeof(path), "./Sprites/%s", read->d_name);
        
        char path3[1024];
        char nombre[256];
        int numero;
        char *buscador;
        strncpy(nombre, read->d_name, sizeof(nombre)-1);
        nombre[sizeof(nombre)-1] = '\0';

        buscador = strchr(nombre, '_');

        if (buscador != NULL){
            buscador++;
            char *numero_str = buscador;
            buscador = strchr(numero_str, '.');

            if (buscador != NULL){
                *buscador = '\0';
            }
            numero = atoi(numero_str);
        }

        if (1 <= numero && numero <= 151){
            snprintf(path3, sizeof(path3), "./Generacion/I/%s", read->d_name);
            rename(path, path3);

        }else if (151 < numero && numero <= 251){
            snprintf(path3, sizeof(path3), "./Generacion/II/%s", read->d_name);
            rename(path, path3);
            
        }else if (251 < numero && numero <= 386){
            snprintf(path3, sizeof(path3), "./Generacion/III/%s", read->d_name);
            rename(path, path3);
            
        }else{
            snprintf(path3, sizeof(path3), "./Generacion/IV/%s", read->d_name);
            rename(path, path3);
            
        }

        
        //printf("Archivo duplicado2 creado exitosamente: %s\n", read->d_name);
    }
}
