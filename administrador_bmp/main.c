#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{

    int i=0;
    int ancho_total, bytes_relleno;
    system("MODE 500,500");
    imagen imag;
    //imag = leerImagen( "muerteninja.bmp");
    imag = leerImagen( "sucutrule.bmp");
    //imag = leerImagen( "soyjudio.bmp");
    nodoPixel *fafa;

    masterlist* master;



    printf("El ancho es %d \n", imag.ancho );
    printf("El alto es %d \n", imag.alto );
    printf("El resolucion es %d bits\n", imag.bitsPorPixel );

    ancho_total = imag.tamanyoImagen / imag.alto;
    printf("ancho_tottal  %d\n", ancho_total);
    bytes_relleno = ancho_total - (imag.ancho)*3;
    printf("bytes_relleno  %d\n", bytes_relleno);
    //printf("El tamanyo imagen es %d \n", imag.tamanyoImagen );

    //printf("El ancho de la columna es %d bytes incluido el relleno\n", imag.tamanyoImagen /imag.alto );
    //printf("El relleno es %d bytes \n", (imag.tamanyoImagen /imag.alto) - imag.ancho *3 );

    printf("%d\n", sizeof(ui_1bytes));
    printf("%d\n", sizeof(ui_2bytes));
    printf("%d\n", sizeof(ui_4bytes));
    printf("Hello world!\n");
    master=ArmarListaDeListas(imag);
    mostrarListaDeListas(master);
    mostrarImagen(imag);

    imag=recortarImagen(imag,30,30,100,103);
    printf("El ancho es %d \n", imag.ancho );
    printf("El alto es %d \n", imag.alto );
    printf("El resolucion es %d bits\n", imag.bitsPorPixel );
    printf("El tamanyo de la imagen es %d\n", imag.tamanyoImagen );
    mostrarImagen(imag);
    guardarImagen(imag, "zzz-salida.bmp");
    imag = espejarVertical( imag );
    mostrarImagen( imag );

    return 0;
}

