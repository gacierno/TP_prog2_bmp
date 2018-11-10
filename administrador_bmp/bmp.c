#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "gotoxy.h"

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
        for( i=1; i < ancho_imagen +1; i++){
            fread( &aux_1, sizeof(ui_1bytes), 1, img_file);
            datos_aux.azul = aux_1;
            fread( &aux_1, sizeof(ui_1bytes), 1, img_file);
            datos_aux.verde = aux_1;
            fread( &aux_1, sizeof(ui_1bytes), 1, img_file);
            datos_aux.rojo = aux_1;
            mostrarUnPixel( datos_aux );
            datos_aux.xPos = i;
            datos_aux.yPos = img.alto - j;
            nodo_aux = crearNodo( datos_aux );
            agregarAlFinal( &listaPixeles, nodo_aux );
        }
        printf("\n");
        fseek( img_file, (ancho_total-(ancho_imagen * 3)), SEEK_CUR );
    }
    img.datos_imagen = listaPixeles;
    printf("ancho pix %i\n",img.ancho);
    printf("alto pix %i\n",img.alto);
    printf("tamanyo %i\n",img.tamanyo);
    printf("tamanyo imagen %i\n",img.tamanyoImagen);
    fclose( img_file );
    return img;
};

void guardarImagen( imagen img_in, char nombre_salida[] ){
    FILE *archivo;
    archivo = fopen( nombre_salida, "wb");

    ui_1bytes aux_1;
    ui_2bytes aux_2;
    ui_4bytes aux_4;
    pixel aux_pixel;

    nodoPixel *nodo_aux;
    nodoPixel *listaPixeles;
    pixel datos_aux;

    int ancho_imagen = 0;
    int ancho_total = 0;
    int bytes_relleno = 0;
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

    ancho_imagen = img_in.ancho;
    printf("ancho_imagen  %d\n", ancho_imagen);
    ancho_total = img_in.tamanyoImagen / img_in.alto;
    printf("ancho_tottal  %d\n", ancho_total);
    bytes_relleno = ancho_total - ancho_imagen*3;
    printf("bytes_relleno  %d\n", bytes_relleno);

    for( j=0; j < img_in.alto; j++){
        for( i=1; i < ancho_imagen +1; i++){
            nodo_aux = buscarNodoPorPosicion( img_in.datos_imagen, i, img_in.alto - j );
            aux_pixel = nodo_aux->dato;
            aux_1 = aux_pixel.azul;
            fwrite( &aux_1, sizeof(ui_1bytes), 1, archivo );
            aux_1 = aux_pixel.verde;
            fwrite( &aux_1, sizeof(ui_1bytes), 1, archivo );
            aux_1 = aux_pixel.rojo;
            fwrite( &aux_1, sizeof(ui_1bytes), 1, archivo );
        }
        aux_1 = 0;
        fwrite( &aux_1 , sizeof(ui_1bytes), bytes_relleno, archivo );
    }

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

void mostrarUnPixelRGB( pixel pix_in ){
    //http://dgabrielaparedes.blogspot.com/2007/08/cg-teora-tarea-1-estndares-de-video.html
    //DECLARO COLORES DE TIPO PIXEL PARA FACILITAR LAS FUNCIONES
    pixel NEGRO; //0
    NEGRO.rojo = 0;
    NEGRO.verde = 0;
    NEGRO.azul = 0;
    NEGRO.xPos = 0;
    NEGRO.yPos = 0;

    pixel AZUL; //1
    AZUL.rojo = 0;
    AZUL.verde = 0;
    AZUL.azul = 170;
    AZUL.xPos = 0;
    AZUL.yPos = 0;

    pixel VERDE; //2
    VERDE.rojo = 0;
    VERDE.verde = 170;
    VERDE.azul = 0;
    VERDE.xPos = 0;
    VERDE.yPos = 0;

    pixel CYAN; //3
    CYAN.rojo = 0;
    CYAN.verde = 0;
    CYAN.azul = 170;
    CYAN.xPos = 0;
    CYAN.yPos = 0;

    pixel ROJO; //4
    ROJO.rojo = 170;
    ROJO.verde = 0;
    ROJO.azul = 0;
    ROJO.xPos = 0;
    ROJO.yPos = 0;

    pixel MAGENTA; //5
    MAGENTA.rojo = 170;
    MAGENTA.verde = 0;
    MAGENTA.azul = 170;
    MAGENTA.xPos = 0;
    MAGENTA.yPos = 0;

    pixel MARRON; //6
    MARRON.rojo = 170;
    MARRON.verde = 85;
    MARRON.azul = 0;
    MARRON.xPos = 0;
    MARRON.yPos = 0;

    pixel GRIS_CLARO; //7
    GRIS_CLARO.rojo = 170;
    GRIS_CLARO.verde = 170;
    GRIS_CLARO.azul = 170;
    GRIS_CLARO.xPos = 0;
    GRIS_CLARO.yPos = 0;

    pixel GRIS_OSCURO; //8
    GRIS_OSCURO.rojo = 85;
    GRIS_OSCURO.verde = 85;
    GRIS_OSCURO.azul = 85;
    GRIS_OSCURO.xPos = 0;
    GRIS_OSCURO.yPos = 0;

    pixel AZUL_BRILLANTE; //9
    AZUL_BRILLANTE.rojo = 85;
    AZUL_BRILLANTE.verde = 85;
    AZUL_BRILLANTE.azul = 255;
    AZUL_BRILLANTE.xPos = 0;
    AZUL_BRILLANTE.yPos = 0;

    pixel VERDE_BRILLANTE; //10
    VERDE_BRILLANTE.rojo = 85;
    VERDE_BRILLANTE.verde = 255;
    VERDE_BRILLANTE.azul = 85;
    VERDE_BRILLANTE.xPos = 0;
    VERDE_BRILLANTE.yPos = 0;

    pixel CYAN_BRILLANTE; //11
    CYAN_BRILLANTE.rojo = 85;
    CYAN_BRILLANTE.verde = 255;
    CYAN_BRILLANTE.azul = 255;
    CYAN_BRILLANTE.xPos = 0;
    CYAN_BRILLANTE.yPos = 0;

    pixel ROJO_BRILLANTE; //12
    ROJO_BRILLANTE.rojo = 255;
    ROJO_BRILLANTE.verde = 85;
    ROJO_BRILLANTE.azul = 85;
    ROJO_BRILLANTE.xPos = 0;
    ROJO_BRILLANTE.yPos = 0;

    pixel MAGENTA_BRILLANTE; //13
    MAGENTA_BRILLANTE.rojo = 255;
    MAGENTA_BRILLANTE.verde = 85;
    MAGENTA_BRILLANTE.azul = 255;
    MAGENTA_BRILLANTE.xPos = 0;
    MAGENTA_BRILLANTE.yPos = 0;

    pixel AMARILLO; //14
    AMARILLO.rojo = 255;
    AMARILLO.verde = 255;
    AMARILLO.azul = 85;
    AMARILLO.xPos = 0;
    AMARILLO.yPos = 0;

    pixel BLANCO; //15
    BLANCO.rojo = 255;
    BLANCO.verde = 255;
    BLANCO.azul = 255;
    BLANCO.xPos = 0;
    BLANCO.yPos = 0;

    int i = 0;
    pixel colores[16] = { NEGRO, AZUL, VERDE, CYAN, ROJO, MAGENTA, MARRON, GRIS_CLARO, GRIS_OSCURO, AZUL_BRILLANTE, VERDE_BRILLANTE, CYAN_BRILLANTE, ROJO_BRILLANTE, MAGENTA_BRILLANTE, AMARILLO, BLANCO };
    float distancias[16];

    for( i=0; i<16; i++){
        distancias[i] = calcularDistanciaDosColores( pix_in, colores[i]);
    }
    color( buscarPosicionDelMenor( distancias, 16 ));
    printf("%c", 219);
}

float calcularDistanciaDosColores( pixel pix_i, pixel pix_f){
    float distancia;
    distancia = sqrt( pow(pix_f.rojo - pix_i.rojo, 2) + pow(pix_f.verde - pix_i.verde, 2) + pow(pix_f.azul - pix_i.azul, 2) );
    //printf("distancia %d \n", distancia);
    return distancia;
}

void mostrarImagen( imagen img ){
    int i, j;
    nodoPixel *pix_aux;
    printf("ancho : %d\n", img.ancho);
    printf("alto  : %d\n", img.alto);
    for( j=0; j<img.alto; j++){
        for(i=0; i<img.ancho; i++){
            pix_aux = buscarNodoPorPosicion( img.datos_imagen, i+1, j+1 );
            if(pix_aux != NULL){mostrarUnPixelRGB( pix_aux->dato );}

        }
        printf("\n");
    }
}

void mostrarLista( nodoPixel *lista ){
    while( lista != NULL){
        mostrarUnPixel(lista->dato);
        lista = lista->siguiente;
    }
}
void mostrarListaRecursiva( nodoPixel *lista, int ancho, int contador ){
    if( lista != NULL){
        contador = contador + 1;
        if(contador == ancho){
            printf("\n");
            contador = 0;
        }else{
            mostrarUnPixel( lista->dato );
        }
        mostrarListaRecursiva( lista->siguiente, ancho, contador );
    }
}

nodoPixel *buscarNodoPorPosicion( nodoPixel *lista, int x, int y ){
    nodoPixel *encontrado;
    encontrado = NULL;
    while(lista != NULL && encontrado == NULL){
        if( lista->dato.xPos == x && lista->dato.yPos == y ){
            encontrado = crearNodo( lista->dato);
        }else{
            lista = lista->siguiente;
        }
    }
    return encontrado;
}

int buscarPosicionDelMenor( float arr_in[], int validos ){
    int i = 0;
    float menor = arr_in[0];
    int posicionMenor = 0;

    for( i=0; i<validos; i++){
        if( menor > arr_in[i]){
            menor = arr_in[i];
            posicionMenor = i;
        }
    }
    return posicionMenor;
}

/////  FUNCIONES DE LISTA DE LISTAS

void mostrarListaDeListas( masterlist *master ){
    while(master!=NULL)
    {
        mostrarLista(master->pxl);
        printf("\n");
        master=master->siguiente;
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

nodoPixel* armarListaSecundaria(nodoPixel* lista, int ancho,int pos)
{
    nodoPixel *aux=iniciLista();
    nodoPixel *nueva=iniciLista();
    int i=0,j=0, movimientos=pos*ancho;
    while(lista!=NULL && j<movimientos)
    {
        lista=lista->siguiente;
        j++;
    }

    while(lista!=NULL && i<ancho)
    {
        aux=crearNodo(lista->dato);
        agregarAlFinal(&nueva,aux);
        lista=lista->siguiente;
        i++;
    }
    return nueva;
}
masterlist* ArmarListaDeListas(imagen img)
{
    int j=0;
    int ancho=img.ancho;
    masterlist* pilar=iniciMasterList();
    masterlist* aux=iniciMasterList();
    nodoPixel* seg=img.datos_imagen;
    nodoPixel* auxNodo=iniciLista();
    //el primer nodo de la lista es el primer nodo a insertar en la masterlist

    //moverme en la lista, guardar el nodo siguiente y ponerlo NULL
    /*while(lista!=NULL)
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

    }*/
    while(j<ancho && seg!=NULL)
    {
        auxNodo=armarListaSecundaria(seg,ancho,j);
        aux=crearMasterList(auxNodo);
        pilar=agregarPpioMasterList(pilar,aux);
        j++;

    }
    // ir agregando al principio los nodos de la lista a los nodos de la masterlist

    return pilar;
}
///// FUNCIONES CORTAR imagen

/*nodoPixel* recortarImagen(nodoPixel* lista,int x1,int y1, int x2,int y2)
{
    nodoPixel* nueva=iniciLista();
    nodoPixel* aux=iniciLista();
    int i=1,j=1,x,y;
    for(y=y2;y>=y1;y--)
    {
        for(x=x1;x<=x2;x++)
        {
            aux=buscarNodoPorPosicion(lista,x,y);
            if(aux!=NULL)
            {
                //mostrarUnPixel(aux->dato);
                aux->dato.xPos=i;
                aux->dato.yPos=j;
                agregarAlFinal(&nueva,aux);
                i++;
            }
        }
        j++;
    }
    return nueva;
}*/
imagen recortarImagen(imagen img,int x1,int y1, int x2,int y2)
{
    nodoPixel* nueva=iniciLista();
    nodoPixel* aux=iniciLista();
    int i=1,j=0,x,y;
    for(y=y2;y>=y1;y--)
    {
        i=1;
        for(x=x1;x<=x2;x++)
        {
            aux=buscarNodoPorPosicion(img.datos_imagen,x,y);
            if(aux!=NULL && i<=(x2-x1)+1)
            {
                //mostrarUnPixel(aux->dato);
                aux->dato.xPos=i;
                aux->dato.yPos=(y2-y1)-j+1;
                agregarAlFinal(&nueva,aux);
                i++;
            }
        }
        j++;
    }
    img.datos_imagen=nueva;
    img.alto=j;
    img.ancho=i-1;
    img.tamanyoImagen= buscarProximoMultiplo(img.ancho*3,8) *(img.alto);
    img.tamanyo=img.tamanyoImagen+54;
    return img;
}

int buscarProximoMultiplo(int valor,int multiplo)
{
    int i=1,rta=0;
    while(rta<valor)
    {
        rta=(multiplo*i);
        i++;
    }
    return rta;
}
