#include <stdio.h>
#include <dirent.h>

/*
Descripcion: 
Distribuye los pokemones según su letra inicial

Parametros:
DIR *dir: directorio donde estan los datos a ordenar

Retorno: 
No retorna nada
*/

void Alfabetico(DIR* dir){
    struct dirent *read;
    while ((read = readdir(dir)) != NULL){
        if (strcmp(read->d_name, ".") == 0 || strcmp(read->d_name, "..") == 0) {
            continue;
        }
        char path[1024];
        snprintf(path, sizeof(path), "./Sprites/%s", read->d_name);
        FILE *original = fopen(path, "rb");

        if (original == NULL){
            perror("Error al abrir el archivo original\n");
            continue;
        }

        char path2[1024];
        snprintf(path2, sizeof(path2), "./%s", read->d_name);
        FILE *duplicado = fopen(path2, "wb");

        if (duplicado == NULL){
            perror("Error al crear el arch duplicado");
            fclose(original);
            continue;
        }
        
        char temp[1024];
        size_t BytesLeidos;

        //Copia de archivos
        while((BytesLeidos = fread(temp, 1, sizeof(temp), original)) > 0){
            fwrite(temp, 1, BytesLeidos, duplicado);
        }

        char path3 [1024];
        char inicial = toupper(read ->d_name[0]);
        snprintf(path3, sizeof(path3), "./Alfabetico/%c/%s", inicial, read->d_name);
        rename(path2, path3);
        fclose(original);
        fclose(duplicado);
        //printf("Archivo duplicado creado exitosamente: %s\n", read->d_name);
    }

}
