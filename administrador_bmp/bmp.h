#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

typedef unsigned char   ui_1bytes;
typedef unsigned short  ui_2bytes;
typedef unsigned int    ui_4bytes;

typedef struct{
    ui_1bytes rojo;
    ui_1bytes verde;
    ui_1bytes azul;
}pixel;

typedef struct{
    pixel dato;
    struct nodoPixel *siguiente;
}nodoPixel;

typedef struct
{
    nodoPixel * pxl;
    struct masterlist *siguiente;
}masterlist;

typedef struct{
    ui_1bytes identificacion[2];    //BM
    ui_4bytes tamanyo;              //7601 0000	Tamanio del archivo
    ui_4bytes reservado1;           //0000 0000	Reservados
    ui_4bytes offset;               //3600 0000	Offset
    ui_4bytes bytesEnCabecera;      //2800 0000 Reservados
    ui_4bytes ancho;                //0a00 0000 Ancho
    ui_4bytes alto;                 //0a00 0000 Alto
    ui_2bytes planos;               //0100		Plano
    ui_2bytes bitsPorPixel;         //1800 	    Bits por pixel

    ui_4bytes compresion;           //0000 0000 Compresion
    ui_4bytes tamanyoImagen;        //4001 0000 Tamanyo
    ui_4bytes h_resolucion;         //0000 0000 Hresolucion
    ui_4bytes v_resolucion;         //0000 0000 Vresolucion
    ui_4bytes n_indexados;          //0000 0000 N indexados
    ui_4bytes n_i_indexados;        //0000 0000 n_i_indexados

    nodoPixel *datos_imagen;
}imagen;


//FUNCIONES
imagen leerImagen( char[] );
void guardarImagen( imagen, char[] );

nodoPixel *iniciLista( void );
nodoPixel *crearNodo( pixel );
void agregarAlFinal( nodoPixel**, nodoPixel* );
void mostrarUnPixel( pixel );
void mostrarLista( nodoPixel* );

//

masterlist *iniciMasterList(void);
masterlist *crearMasterList( nodoPixel* );
masterlist *buscarUltimoMasterList( masterlist*);
masterlist* agregarPpioMasterList(masterlist*, masterlist*);
nodoPixel* movermeEnLista(nodoPixel* ,int );
masterlist* ArmarListaDeListas(imagen );
#endif // BMP_H_INCLUDED
