#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct casilla {
	int etiq;
	char tipo;
	int nMinas;
	char o;
	int f;
};
typedef struct casilla tipoCasilla;
tipoCasilla **matriz;

tipoCasilla **CrearMatriz(int filas, int cols){
	int i,j;
	tipoCasilla **matriz=(tipoCasilla**) malloc (filas*sizeof(tipoCasilla*));
	for (i=0;i<filas;i++){
		matriz[i]=(tipoCasilla*) malloc (cols*sizeof(tipoCasilla));
		for(j=0;j<cols;j++){
			matriz[i][j].etiq=9;
			matriz[i][j].tipo='C';
			matriz[i][j].nMinas=0;
			matriz[i][j].o=0;
			matriz[i][j].f=7;

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
		if (matriz[posFil][posCol].tipo != 'M'){
			n++;
		}
		matriz[posFil][posCol].tipo='M';		
	}
}

void dibujarTablero2(int filas, int cols, tipoCasilla **matriz){
	int i,j;
	printf ("   ");
	for(j=0;j<cols;j++){
		printf ("-%d-",j);
	}
	printf ("\n");
	for (i=0;i<filas;i++){
		printf ("%d--",i);
		for(j=0;j<cols;j++){
			printf ("|%c|",matriz[i][j].tipo);
	 	}
	printf ("\n");	
	}
	
}

void dibujarTablero(int filas, int cols, tipoCasilla **matriz){
	int i,j;
	printf ("   ");
	for(j=0;j<cols;j++){
		printf ("-%d-",j);
	}
	printf ("\n");
	for (i=0;i<filas;i++){
		printf ("%d--",i);
		for(j=0;j<cols;j++){
			printf ("|%d|",matriz[i][j].etiq);
		}
	printf ("\n");	
	}
	
}

int validar (int i, int j, int filas, int cols){
	if ((i)>=0 && (j)>=0 && (j)<cols && (i)<filas){
		return 1;
	}else{
		return 0;
	}
}

void ColocarNumero(int filas,int cols, tipoCasilla **matriz){
	 int i,j;
	 for (i=0;i<filas;i++){
	 	for(j=0;j<cols;j++){
	 		if(validar (i,j-1,filas,cols) && matriz[i][j-1].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			if(validar (i,j+1,filas,cols) && matriz[i][j+1].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			 
			if(validar (i-1,j-1,filas,cols) && matriz[i-1][j-1].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			
			if(validar (i-1,j,filas,cols) && matriz[i-1][j].tipo=='M'){
				matriz[i][j].nMinas++;	
			}
			if(validar (i-1,j+1,filas,cols) && matriz[i-1][j+1].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			if(validar (i+1,j-1,filas,cols) && matriz[i+1][j-1].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			if(validar (i+1,j,filas,cols) && matriz[i+1][j].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			if(validar (i+1,j+1,filas,cols) && matriz[i+1][j+1].tipo=='M'){
				matriz[i][j].nMinas++;
			}
			
	 	}
	}	
}

int  AbrirNumeros(int filas,int cols, tipoCasilla **matriz,int x, int y){
	int n=0;
	if(validar (x,y-1,filas,cols) && matriz[x][y-1].tipo=='C'){
		n++;
		matriz[x][y-1].etiq=matriz[x][y-1].nMinas;
		
	}
	if(validar (x,y+1,filas,cols) && matriz[x][y+1].tipo=='C'){
		n++;
		matriz[x][y+1].etiq=matriz[x][y+1].nMinas;
		
	}
			 
	if(validar (x-1,y-1,filas,cols) && matriz[x-1][y-1].tipo=='C'){
		n++;
		matriz[x-1][y-1].etiq=matriz[x-1][y-1].nMinas;
		
	}
			
	if(validar (x-1,y,filas,cols) && matriz[x-1][y].tipo=='C'){
		n++;
		matriz[x-1][y].etiq=matriz[x-1][y].nMinas;
		
	}
	if(validar (x-1,y+1,filas,cols) && matriz[x-1][y+1].tipo=='C'){
		n++;
		matriz[x-1][y+1].etiq=matriz[x-1][y+1].nMinas;
		
	}
	if(validar (x+1,y-1,filas,cols) && matriz[x+1][y-1].tipo=='C'){
		n++;
		matriz[x+1][y-1].etiq=matriz[x+1][y-1].nMinas;
		
	}
	if(validar (x+1,y,filas,cols) && matriz[x+1][y].tipo=='C'){
		n++;
		matriz[x+1][y].etiq=matriz[x+1][y].nMinas;
		
	}
	if(validar (x+1,y+1,filas,cols) && matriz[x+1][y+1].tipo=='C'){
		n++;
		matriz[x+1][y+1].etiq=matriz[x+1][y+1].nMinas;
	}			
	return n;	
}

void jugar (int filas,int cols, tipoCasilla **matriz,int x,int y,int z){
	if (matriz[x][y].tipo=='C'){
		matriz[x][y].etiq=matriz[x][y].nMinas;
		dibujarTablero(filas,cols,matriz);
	}
	if (z==7 && matriz[x][y].tipo=='M'){
		matriz[x][y].etiq=matriz[x][y].f;
		dibujarTablero(filas,cols,matriz);
	}
}

int ganar(int filas,int cols,tipoCasilla **matriz){
	int i,j,l=0;
	for (i=0;i<filas;i++){
		for(j=0;j<cols;j++){
			if (matriz[i][j].tipo=='M' && matriz[i][j].etiq==7 ){
				l++;
			}
		} 	
	}
	return l;
}
	
void main(int argc, char*argv[]){
	int filas=atoi (argv [1]);
	int cols=atoi (argv [2]);	
	int minas=atoi (argv [3]);
	tipoCasilla **matriz=CrearMatriz (filas,cols);
	printf ("\n");;
	printf ("Instrucciones:\n");
	printf ("-- Primer valor es la fila.\n");
	printf ("-- Segundo valor es la columna.\n");
	printf ("-- Tercer valor es el tipo de casilla.\n");
	printf ("-- Si deseas colocar una bandera hazlo con el numero 7.\n");
	printf ("-- De lo contrario usa el 0 como tercer comando.\n");
	printf ("-- Solo se gana cuando se colocan banderas sobre todas las minas.\n");
	printf ("-------------------------------------------------------------------\n");
	PonerMinas(filas,cols,matriz,minas);
	ColocarNumero(filas,cols,matriz);
	dibujarTablero(filas,cols,matriz);
	int x,y,z;
	int n=0,p=0;
	while (n<=(filas*cols)){
		scanf("%d %d %d",&x,&y,&z);
		int k=AbrirNumeros(filas,cols,matriz,x,y);
		int o=ganar(filas,cols,matriz);
		if (matriz[x][y].tipo=='M' && z==0){
			printf ("PERDISTE HABIA UNA MINA EN ESA POSICION!!\n");
			printf ("M=Mina C=Normal\n");
			dibujarTablero2(filas,cols,matriz);
			break;
		}
		if (matriz[x][y].tipo=='C' || z==7){
			printf ("-------------------------------\n");
			p++;
			AbrirNumeros(filas,cols,matriz,x,y);
			jugar (filas,cols,matriz,x,y,z);
			ganar(filas,cols,matriz);
			
		}	
		n++;
		if(o==minas-1){
			printf("\n");
			printf("HAS GANADO EL JUEGO!!\n");
			printf ("MIRA LAS POSICIONES DE LAS MINAS:\n");
			printf ("M=Mina C=Normal\n");
			dibujarTablero2(filas,cols,matriz);
			break;
		}
	}

}