#include "matematica.h"
#include "gotoxy.h"
#include <stdio.h>

void mostrarPorcentajeCargado( int actual, int total ){
    int porcentaje = actual * 100 / total;
    switch(porcentaje % 4){
    case 0:
        printf( "Cargado el %3d %% /", porcentaje);
        break;
    case 1:
        printf( "Cargado el %3d %% -", porcentaje);
        break;
    case 2:
        printf( "Cargado el %3d %% |", porcentaje);
        break;
    case 3:
        printf( "Cargado el %3d %% \\", porcentaje);
        break;
    }
    if( porcentaje == 100 ){
        gotoxy( whereX() -1, whereY() );
        printf(" \n\n");
    }else{
        gotoxy( 0, whereY() );
    }
}
