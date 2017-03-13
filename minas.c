#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct casilla {
	char etiq;
	char tipo;
	int nMinas;
	char o;
};
typedef struct casilla tipoCasilla;
tipoCasilla **matriz;

tipoCasilla **CrearMatriz(int filas, int cols){
	int i,j;
	tipoCasilla **matriz=(tipoCasilla**) malloc (filas*sizeof(tipoCasilla*));
	for (i=0;i<filas;i++){
		matriz[i]=(tipoCasilla*) malloc (cols*sizeof(tipoCasilla));
		for(j=0;j<cols;j++){
			matriz[i][j].etiq='x';
			matriz[i][j].tipo='c';
			matriz[i][j].nMinas=0;
			matriz[i][j].o='o';
		}
	}
	return matriz;
}


void PonerMinas (int filas,int cols,tipoCasilla **matriz,int numeroMinas){
	int posFil,posCol,n;
	srand(time (NULL));
	n=0;
	while (n<numeroMinas){
		posFil=rand ()%filas;
		posCol=rand ()%cols;
		matriz[posFil][posCol].tipo='m';
		n++;
	}
}


void dibujarTablero(int filas, int cols, tipoCasilla **matriz){
	int i,j;
	for (i=0;i<filas;i++){
		for(j=0;j<cols;j++){
			printf ("|%c|",matriz[i][j].tipo);
		}
	printf ("\n");	
	}
	
}

void ColocarNumero(int filas,int cols, tipoCasilla **matriz){
	int i,j;
	for (i=0;i<filas;i++){
		for(j=0;j<cols;j++){
			if (i=0){
				
			}
		}
	}

	
}
void main(int argc, char*argv[]){
	int filas=atoi (argv [1]);
	int cols=atoi (argv [2]);	
	int minas=atoi (argv [3]);	
	tipoCasilla **matriz=CrearMatriz (filas,cols);
	PonerMinas(filas,cols,matriz,minas);	
	dibujarTablero(filas,cols,matriz);
	
}
