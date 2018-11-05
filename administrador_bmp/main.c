#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
    int i=0;
    system("MODE 500,500");
    imagen imag;
    //imag = leerImagen( "muerteninja.bmp");
    imag = leerImagen( "sucutrule.bmp");
    //imag = leerImagen( "soyjudio.bmp");
    nodoPixel *fafa;


    printf("El ancho es %d \n", imag.ancho );
    printf("El alto es %d \n", imag.alto );
    printf("El resolucion es %d bits\n", imag.bitsPorPixel );
    //printf("El tamanyo imagen es %d \n", imag.tamanyoImagen );

    //printf("El ancho de la columna es %d bytes incluido el relleno\n", imag.tamanyoImagen /imag.alto );
    //printf("El relleno es %d bytes \n", (imag.tamanyoImagen /imag.alto) - imag.ancho *3 );

    printf("%d\n", sizeof(ui_1bytes));
    printf("%d\n", sizeof(ui_2bytes));
    printf("%d\n", sizeof(ui_4bytes));
    printf("Hello world!\n");
    //mostrarLista( imag.datos_imagen );
    mostrarImagen( imag );

    for( i=0; i<16; i++){
        color( i );
        printf("%c", 32);
        printf("%c", 219);
        printf("%c", 176);
        printf("%c", 178);
        printf("%c", 177);
        printf("  %d", i);
        printf("\n");
    }


    //fafa = buscarNodoPorPosicion( imag.datos_imagen, 1, 1);
    //mostrarUnPixel( fafa->dato );
    return 0;
}
