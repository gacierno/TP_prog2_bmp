#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

imagen leerImagen( char nombre_archivo[] ){
    imagen img;
    ui_1bytes aux_1;
    ui_2bytes aux_2;
    ui_4bytes aux_4;

    nodoPixel *nodo_aux;
    nodoPixel *listaPixeles;
    pixel datos_aux;

    int ancho_imagen = 0;
    int ancho_total = 0;
    int i = 0,
        j = 0;

    listaPixeles = iniciLista();

    FILE *img_file;
    img_file = fopen( nombre_archivo, "rb");

    //leer el header
    fread( &aux_1, 1, 1, img_file );
    img.identificacion[0] = aux_1;
    fread( &aux_1, 1, 1, img_file );
    img.identificacion[1] = aux_1;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.tamanyo = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.reservado1 = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.offset = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.bytesEnCabecera = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.ancho = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.alto = aux_4;
    fread( &aux_2, sizeof( ui_2bytes ), 1, img_file );
    img.planos = aux_2;
    fread( &aux_2, sizeof( ui_2bytes ), 1, img_file );
    img.bitsPorPixel = aux_2;
    //complemento
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.compresion = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.tamanyoImagen = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.h_resolucion = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.v_resolucion = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.n_indexados = aux_4;
    fread( &aux_4, sizeof( ui_4bytes ), 1, img_file );
    img.n_i_indexados = aux_4;

    //leer los datos de la imagen

    /*
    como sabemos que cada linea se rellena con bytes 00 para que quede en multiplos de 32
    la cantidad de lineas la sabemos porque es el alto
    columnas(ancho de la imagen incluido el relleno)

    columnas tamanyo del archivo divido el alto (cantidad de bytes de la linea)

    la cantidad de pixeles q hay en esa linea es el ancho de la imagen
    entonces la cantidad de bytes es los pixeles x 3(rgb 24bits)

    relleno es pixeles(ancho) por 3 menos la columna
    */

    ancho_imagen = img.ancho;
    ancho_total = img.tamanyoImagen / img.alto;

    img.datos_imagen = iniciLista();

    for( j=0; j < img.alto; j++){
        for( i=0; i < ancho_imagen; i++){
            fread( &aux_1, sizeof(ui_1bytes), 1, img_file);
            datos_aux.rojo = aux_1;
            fread( &aux_1, sizeof(ui_1bytes), 1, img_file);
            datos_aux.verde = aux_1;
            fread( &aux_1, sizeof(ui_1bytes), 1, img_file);
            datos_aux.azul = aux_1;
            mostrarUnPixel( datos_aux );
            nodo_aux = crearNodo( datos_aux );
            agregarAlFinal( &listaPixeles, nodo_aux );
        }
        printf("\n");
        fseek( img_file, (ancho_total-(ancho_imagen * 3)), SEEK_CUR );
    }
    img.datos_imagen = listaPixeles;
    fclose( img_file );
    return img;
};


nodoPixel *iniciLista( void ){
    return NULL;
}

nodoPixel *crearNodo( pixel data_in ){
    nodoPixel *pix;
    pix = ( nodoPixel* )malloc( sizeof(nodoPixel) );
    pix->dato = data_in;
    pix->siguiente = NULL;
    return pix;
}

nodoPixel *buscarUltimo( nodoPixel *lista ){
    if( lista != NULL){
        while( lista->siguiente != NULL ){
            lista = lista->siguiente;
        }
    }
    return lista;
}

void agregarAlFinal( nodoPixel **lista, nodoPixel *nodo ){
    nodoPixel *nodo_aux;
    if( *lista == NULL ){
        *lista = nodo;
    }else{
        nodo_aux = buscarUltimo( *lista );
        nodo_aux->siguiente = nodo;
    }
}

void mostrarUnPixel( pixel pix_in ){
    printf("%.3d_", (pix_in.rojo+pix_in.verde+pix_in.azul)/3);
}
