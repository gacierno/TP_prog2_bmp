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

void guardarImagen( imagen img_in, char nombre_salida[] ){
    FILE *archivo;
    archivo = fopen( nombre_salida, "wb");

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

    aux_1 = img_in.identificacion[0];
    fwrite(&aux_1, sizeof(ui_1bytes), 1, archivo);
    aux_1 = img_in.identificacion[1];
    fwrite(&aux_1, sizeof(ui_1bytes), 1, archivo);
    aux_4 = img_in.tamanyo;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.reservado1;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.offset;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.bytesEnCabecera;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.ancho;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.alto;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_2 = img_in.planos;
    fwrite(&aux_2, sizeof(ui_2bytes), 1, archivo);
    aux_2 = img_in.bitsPorPixel;
    fwrite(&aux_2, sizeof(ui_2bytes), 1, archivo);
    aux_4 = img_in.compresion;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.tamanyoImagen;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.h_resolucion;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.v_resolucion;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.n_indexados;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);
    aux_4 = img_in.n_i_indexados;
    fwrite(&aux_4, sizeof(ui_4bytes), 1, archivo);

    fclose( archivo );
}


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
    if( (pix_in.rojo+pix_in.verde+pix_in.azul)/3 < 50 ){
        printf("%c", 32);
    }else if( (pix_in.rojo+pix_in.verde+pix_in.azul)/3 > 200 ){
        printf("%c", 219);
    }else if( (pix_in.rojo+pix_in.verde+pix_in.azul)/3 < 100 ){
        printf("%c", 176);
    }else if( ( pix_in.rojo+pix_in.verde+pix_in.azul)/3 > 150 ){
        printf("%c", 178);
    }else{
        printf("%c", 177);
    }
}

void mostrarLista( nodoPixel *lista ){
    while( lista != NULL){
        mostrarUnPixel(lista->dato);
        lista = lista->siguiente;
    }
}

/////  FUNCIONES DE LISTA DE LISTAS

void mostrarListaDeListas( masterlist *lista ){
    while( lista != NULL){
        mostrarUnPixel(lista->pxl->dato);
        lista = lista->siguiente;
    }
}

masterlist *iniciMasterList( void ){
    return NULL;
}

masterlist *crearMasterList( nodoPixel* data_in ){
    masterlist *mL;
    mL = ( masterlist* )malloc( sizeof(masterlist) );
    mL->pxl = data_in;
    mL->siguiente = NULL;
    return mL;
}
masterlist *buscarUltimoMasterList( masterlist* lista ){
    if( lista != NULL){
        while( lista->siguiente != NULL ){
            lista = lista->siguiente;
        }
    }
    return lista;
}
masterlist* agregarPpioMasterList(masterlist* lista, masterlist* nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}
nodoPixel* movermeEnLista(nodoPixel* img,int num)
{
    int i=1;
    while(img!=NULL && i<num)
    {
        img=img->siguiente;
        i++;
    }
    return img;
}
masterlist* ArmarListaDeListas(imagen img)
{
    int i=0;
    int ancho=img.ancho;
    masterlist* pilar=iniciMasterList();
    masterlist* aux=iniciMasterList();
    nodoPixel* lista=img.datos_imagen;
    nodoPixel* seg=lista;
    //el primer nodo de la lista es el primer nodo a insertar en la masterlist
    pilar=crearMasterList(seg);

    //moverme en la lista, guardar el nodo siguiente y ponerlo NULL
    while(lista!=NULL)
    {
        lista=movermeEnLista(lista,ancho);
        seg=lista;
        lista=lista->siguiente;
        if(lista!=NULL)
        {
            seg->siguiente=NULL;
            aux=crearMasterList(lista);
            pilar=agregarPpioMasterList(pilar,aux);
        }

    }

    // ir agregando al principio los nodos de la lista a los nodos de la masterlist

    return pilar;
}
