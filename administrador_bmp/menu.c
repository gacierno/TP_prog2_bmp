#include "bmp.h"
#include <string.h>
void renderMenu( imagen img ){
    int opcion=0,exit=-1;
    char nombre[20];
    system("dir *.bmp");
    printf("Por favor indique el la imagen que desea abrir ");
    scanf("%s",&nombre);
    img=leerImagen(nombre);
    mostrarImagen(img);
    while(exit==-1)
    {
        printf("Que desea hacer con la imagen?\n 1 Pasar a Blanco y Negro\n 2 Cortar\n 3 Espejar Horizonalmente\n 4 Espejar Verticalmente\n 5 Guardar Cambios\n 6 Salir\n");
        scanf("%i",&opcion);
        switch(opcion)
        {
        case 1:
            {
                img=pasarAByN(img);
                mostrarImagen(img);
                break;
            }
        case 2:
            {
                int x1=0,y1=0,x2=0,y2=0;
                printf("ingrese las coordenada de x1\n");
                scanf("%i",&x1);
                printf("ingrese las coordenada de y1\n");
                scanf("%i",&y1);
                printf("ingrese las coordenada de x2\n");
                scanf("%i",&x2);
                printf("ingrese las coordenada de y2\n");
                scanf("%i",&y2);
                img=recortarImagen(img,x1,y1,x2,y2);
                mostrarImagen(img);
                break;
            }
        case 3:
            {
                img=espejarHorizontal(img);
                mostrarImagen(img);
                break;
            }
        case 4:
            {
                img=espejarVertical(img);
                mostrarImagen(img);
                break;
            }
        case 5:
            {
                char nuevoNombre[20];
                printf("ingrese nombre de la imagen a guardar\n");
                scanf("%s",nuevoNombre);
                printf("nombre es: %s",nuevoNombre);
                guardarImagen(img,nuevoNombre);
                break;
            }
        case 6:
            {
                exit=0;
                break;
            }

        }
    }

}
