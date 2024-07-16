#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

/*
Descripcion: 
Cuenta la cantidad de archivos por cada directorio de la carpeta "Generacion"

Parametros:
No posee parametros

Retorno: 
No retorna nada
*/

void contar_generacion (char* carpeta){
    FILE *registro = fopen("RegistroPokemon.txt", "a");
    int cantidad = 0;
    DIR *dir;
    char path[1024];
    snprintf(path, sizeof(path), "./Generacion/%s", carpeta);
    dir = opendir(path);
    struct dirent *read;
    while((read = readdir(dir)) != NULL){
        if (strcmp(read->d_name, ".") == 0 || strcmp(read->d_name, "..") == 0) {
            continue;
        }
        cantidad++;
    }
    fprintf(registro,"%s - %i\n",carpeta,cantidad);
    fclose(registro);
}
