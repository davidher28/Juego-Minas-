#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct casilla {
	char etiq;
	char tipo;
	int nMinas;
	char o;
	char f;
};
typedef struct casilla tipoCasilla;
tipoCasilla **matriz;

tipoCasilla **CrearMatriz(int filas, int cols){
	int i,j;
	tipoCasilla **matriz=(tipoCasilla**) malloc (filas*sizeof(tipoCasilla*));
	for (i=0;i<filas;i++){
		matriz[i]=(tipoCasilla*) malloc (cols*sizeof(tipoCasilla));
		for(j=0;j<cols;j++){
			matriz[i][j].etiq='*';
			matriz[i][j].tipo='C';
			matriz[i][j].nMinas=0;
			matriz[i][j].o=0;
			matriz[i][j].f='F';

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
			printf ("|%c|",matriz[i][j].etiq);
		}
	printf ("\n");	
	}
	
}

int validar (int i, int j, int filas, int cols){
	if ((i)>=0 && (j)>=0 && (j)<cols && (i)<filas){
		return 1;
	}
	return 0;
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

void AbrirNumeros(int filas,int cols, tipoCasilla **matriz,int x, int y){
	int n=0,i,j;
	if (matriz[x][y].nMinas==0){
		if(validar (x,y-1,filas,cols) && matriz[x][y-1].nMinas==0 && matriz[x][y-1].tipo=='C' && matriz[x][y-1].etiq=='*'){
			matriz[x][y-1].etiq=matriz[x][y-1].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x,y-1);
		}
		if(validar (x,y+1,filas,cols) && matriz[x][y+1].nMinas==0 && matriz[x][y+1].tipo=='C' && matriz[x][y+1].etiq=='*'){
			matriz[x][y+1].etiq=matriz[x][y+1].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x,y+1);
		}		 
		if(validar (x-1,y-1,filas,cols) && matriz[x-1][y-1].nMinas==0 && matriz[x-1][y-1].tipo=='C' && matriz[x-1][y-1].etiq=='*' ){
			matriz[x-1][y-1].etiq=matriz[x-1][y-1].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x-1,y-1);
		}		
		if(validar (x-1,y,filas,cols) && matriz[x-1][y].nMinas==0 && matriz[x-1][y].tipo=='C' && matriz[x-1][y].etiq=='*'){
			matriz[x-1][y].etiq=matriz[x-1][y].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x-1,y);
		}
		if(validar (x-1,y+1,filas,cols)  && matriz[x-1][y+1].nMinas==0 && matriz[x-1][y+1].tipo=='C' && matriz[x-1][y+1].etiq=='*'){
			matriz[x-1][y+1].etiq=matriz[x-1][y+1].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x-1,y+1);
		}
		if(validar (x+1,y-1,filas,cols) && matriz[x+1][y-1].nMinas==0 && matriz[x+1][y-1].tipo=='C' && matriz[x+1][y-1].etiq=='*'){
			matriz[x+1][y-1].etiq=matriz[x+1][y-1].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x+1,y-1);
		}
		if(validar (x+1,y,filas,cols) && matriz[x+1][y].nMinas==0 && matriz[x+1][y].tipo=='C' && matriz[x+1][y].etiq=='*' ){
			matriz[x+1][y].etiq=matriz[x+1][y].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x+1,y);
		}
		if(validar (x+1,y+1,filas,cols) && matriz[x+1][y+1].nMinas==0 && matriz[x+1][y+1].tipo=='C' && matriz[x+1][y+1].etiq=='*'){
			matriz[x+1][y+1].etiq=matriz[x+1][y+1].nMinas+48;
			AbrirNumeros(filas,cols,matriz,x+1,y+1);
		}
		if(validar (x,y-1,filas,cols) && matriz[x][y-1].tipo=='C' && matriz[x][y-1].etiq=='*'){
			matriz[x][y-1].etiq=matriz[x][y-1].nMinas+48;

		}
		if(validar (x,y+1,filas,cols) && matriz[x][y+1].tipo=='C' && matriz[x][y+1].etiq=='*'){
			matriz[x][y+1].etiq=matriz[x][y+1].nMinas+48;
		}		 
		if(validar (x-1,y-1,filas,cols)  && matriz[x-1][y-1].tipo=='C' && matriz[x-1][y-1].etiq=='*' ){
			matriz[x-1][y-1].etiq=matriz[x-1][y-1].nMinas+48;
		}		
		if(validar (x-1,y,filas,cols) && matriz[x-1][y].tipo=='C' && matriz[x-1][y].etiq=='*'){
			matriz[x-1][y].etiq=matriz[x-1][y].nMinas+48;
		}
		if(validar (x-1,y+1,filas,cols)  && matriz[x-1][y+1].tipo=='C' && matriz[x-1][y+1].etiq=='*'){
			matriz[x-1][y+1].etiq=matriz[x-1][y+1].nMinas+48;
		}
		if(validar (x+1,y-1,filas,cols) && matriz[x+1][y-1].tipo=='C' && matriz[x+1][y-1].etiq=='*'){
			matriz[x+1][y-1].etiq=matriz[x+1][y-1].nMinas+48;
		}
		if(validar (x+1,y,filas,cols) && matriz[x+1][y].tipo=='C' && matriz[x+1][y].etiq=='*' ){
			matriz[x+1][y].etiq=matriz[x+1][y].nMinas+48;
		}
		if(validar (x+1,y+1,filas,cols)  && matriz[x+1][y+1].tipo=='C' && matriz[x+1][y+1].etiq=='*'){
			matriz[x+1][y+1].etiq=matriz[x+1][y+1].nMinas+48;
		}	

	}	
}

void jugar (int filas,int cols, tipoCasilla **matriz,int x,int y,int z){
	if (z=='n' && matriz[x][y].tipo=='C'){
		matriz[x][y].etiq=matriz[x][y].nMinas+48;
		dibujarTablero(filas,cols,matriz);

	}
	if (z=='f' && (matriz[x][y].tipo=='M' || matriz[x][y].tipo=='C')){
		matriz[x][y].etiq=matriz[x][y].f;
		dibujarTablero(filas,cols,matriz);

	}
}

int ganar(int filas,int cols,tipoCasilla **matriz){
	int i,j,l=0;
	for (i=0;i<filas;i++){
		for(j=0;j<cols;j++){
			if (matriz[i][j].tipo=='M' && matriz[i][j].etiq=='F'){
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
	printf ("-- Si deseas colocar una bandera hazlo con la letra f.\n");
	printf ("-- De lo contrario usa la letra n como tercer comando.\n");
	printf ("-- Solo se gana cuando se colocan banderas sobre todas las minas.\n");
	printf ("-------------------------------------------------------------------\n");
	PonerMinas(filas,cols,matriz,minas);
	ColocarNumero(filas,cols,matriz);
	dibujarTablero(filas,cols,matriz);
	int x,y;
	char z;
	int n=0,p=0;
	while (n<=(filas*cols)){
		scanf("%d %d %c",&x,&y,&z);
		int o=ganar(filas,cols,matriz);
		if (matriz[x][y].tipo=='M' && z=='n'){
			printf ("PERDISTE HABIA UNA MINA EN ESA POSICION!!\n");
			printf ("M=Mina C=Normal\n");
			dibujarTablero2(filas,cols,matriz);
			break;
		}
		if (matriz[x][y].tipo=='C' && z=='n'){
			printf ("-------------------------------\n");
			p++;
			AbrirNumeros(filas,cols,matriz,x,y);
			jugar (filas,cols,matriz,x,y,z);
			ganar(filas,cols,matriz);


			
		}	
		if ((matriz[x][y].tipo=='C' || matriz[x][y].tipo=='M' ) && z=='f'){
			printf ("-------------------------------\n");
			p++;
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