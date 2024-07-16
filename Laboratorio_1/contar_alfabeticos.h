#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

/*
Descripcion: 
Cuenta la cantidad de archivos por cada directorio de la carpeta "Alfabetico"

Parametros:
No posee parametros

Retorno: 
No retorna nada
*/

void contar_alfabeticos(){
    FILE *registro = fopen("RegistroPokemon.txt", "w");
    fprintf(registro,"Alfabético\n");
    int cantidad;
    struct dirent *read;
    char info[1024];
    for (char a ='A'; a <= 'Z'; a++){
        cantidad = 0;
        char path[256];
        snprintf(path, sizeof path,"./Alfabetico/%c",a);
        DIR *dir;
        dir = opendir(path);
        while ((read = readdir(dir)) != NULL){
            if (strcmp(read ->d_name, ".") == 0 || strcmp(read ->d_name, "..") == 0){
                continue;
            }
            cantidad ++;
        }
        snprintf(info, sizeof(info), "%c - %i\n", a, cantidad);
        fprintf(registro,"%s",info);
    }
    fclose(registro);
}
