#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

imagen leerImagen( char nombre_archivo[] ){
    imagen img;
    ui_1bytes aux_1;
    ui_2bytes aux_2;
    ui_4bytes aux_4;

    pixel *datos_aux;

    FILE *fotoloca;
    fotoloca = fopen( nombre_archivo, "rb");

    //header
    fread( &aux_1, 1, 1, fotoloca );
    img.identificacion[0] = aux_1;
    fread( &aux_1, 1, 1, fotoloca );
    img.identificacion[1] = aux_1;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.tamanyo = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.reservado1 = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.offset = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.bytesEnCabecera = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.ancho = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.alto = aux_4;
    fread( &aux_2, sizeof( ui_2bytes ), 1, fotoloca );
    img.planos = aux_2;
    fread( &aux_2, sizeof( ui_2bytes ), 1, fotoloca );
    img.bitsPorPixel = aux_2;
    //complemento
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.compresion = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.tamanyoImagen = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.h_resolucion = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.v_resolucion = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.n_indexados = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, fotoloca );
    img.n_i_indexados = aux_4;

    //datos de la imagen

    /*

    como sabemos que cada linea se rellena con bytes 00 para que quede en multiplos de 32
    la cantidad de lineas la sabemos porque es el alto
    columnas(ancho de la imagen incluido el relleno)

    columnas tamanyo del archivo divido el alto (cantidad de bytes de la linea)

    la cantidad de pixeles q hay en esa linea es el ancho de la imagen
    entonces la cantidad de bytes es los pixeles x 3(rgb 24bits)

    relleno es pixeles(ancho) por 3 menos la columna

    */



    fclose( fotoloca );
    return img;
}
