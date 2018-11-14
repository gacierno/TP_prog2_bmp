#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "menu.h"
/*int main()
{

    int i=0;
    int ancho_total, bytes_relleno;
    system("MODE 500,500");
    imagen imag;
    //imag = leerImagen( "muerteninja.bmp");
    //imag = leerImagen( "sucutrule.bmp");
    imag = leerImagen( "soyjudio.bmp");
    nodoPixel *fafa;

    masterlist* master;


    //printf("El tamanyo imagen es %d \n", imag.tamanyoImagen );

    //printf("El ancho de la columna es %d bytes incluido el relleno\n", imag.tamanyoImagen /imag.alto );
    //printf("El relleno es %d bytes \n", (imag.tamanyoImagen /imag.alto) - imag.ancho *3 );


    imag=recortarImagen(imag,16,14,45,55);

    mostrarImagen(imag);
    imag = rotarALaDerecha( imag );
    mostrarImagen(imag);
    guardarImagen(imag,"salidamuerte2.bmp");


    return 0;
}*/

int main()
{
    imagen img;
    system("MODE 500,500");
    renderMenu(img);
}
