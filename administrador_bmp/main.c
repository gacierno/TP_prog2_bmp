#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
    masterlist* master;

    imagen imag;
    //imag = leerImagen( "muerteninja.bmp");
    imag = leerImagen( "soyjudio.bmp");


    printf("El ancho es %d \n", imag.ancho );
    printf("El alto es %d \n", imag.alto );
    printf("El tamanyo imagen es %d \n", imag.tamanyoImagen );

    printf("El ancho de la columna es %d bytes incluido el relleno\n", imag.tamanyoImagen /imag.alto );
    printf("El relleno es %d bytes \n", (imag.tamanyoImagen /imag.alto) - imag.ancho *3 );

    printf("%d\n", sizeof(ui_1bytes));
    printf("%d\n", sizeof(ui_2bytes));
    printf("%d\n", sizeof(ui_4bytes));
    printf("Hello world!\n");
    //mostrarLista( imag.datos_imagen );
    master=ArmarListaDeListas(imag);
    printf("sdfasdfa %i",master->pxl->dato.azul);
    return 0;
}
