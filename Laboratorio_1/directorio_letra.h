#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>

/*
Descripcion: 
Crea los directorios de cada letra del abecedario

Parametros:
No posee parametros

Retorno: 
No retorna nada
*/

void crear_directorio_letra (){
    for (char a ='A'; a <= 'Z'; a++){

            //"recorrer" todo el abc para crear cada directorio
            char path[256];
                //en path se guarda la "ruta"
            snprintf(path, sizeof path,"./Alfabetico/%c",a);

            if (mkdir(path, 0777) == 0) {
                //printf("Carpeta %s creada exitosamente \n", path);
            } else {
                printf("Error al crear la carpeta\n");
            }
    }
}
