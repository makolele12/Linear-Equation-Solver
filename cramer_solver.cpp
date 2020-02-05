#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <iostream>
#define tam 10
#define PI acos(-1.0)

using namespace std;

//Formato
void gotoxy(int x, int y);

//Funciones para manipular los complejos en las matrices//
void fillmatrix(double real[tam][tam],double complejo[tam][tam],int c,int y);
void fillmatrix2(double pol[tam][tam],double angulo[tam][tam],int c,int y);
void printmatrix(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n);
void topolar(double *real,double *complejo,double *pol,double *angulo);
void torectangular(double *real,double *complejo,double *pol,double *angulo);

//Funciones de Cramer//
void cramer(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],double xdet[tam],double a[tam][tam],int n,int m);
void fillmatrixdet(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],double real1[tam][tam],double complejo1[tam][tam],double pol1[tam][tam],double angulo1[tam][tam],int n,int m);
void fillmaster(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n,int m);
void determinant(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n,double det[tam]);
void settings(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n,int m,double xdet[tam],double a[tam][tam],double real1[tam][tam],double complejo1[tam][tam],double pol1[tam][tam],double angulo1[tam][tam]);
void d2(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],double det[tam]);

//Funciones Básicas//
void sumar(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3);
void restar(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3);
void multi(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3);
void divi(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3);

//Calculadora//
void calculadora();
void sumacalc(double res[tam]);
void restacalc(double res[tam]);
void multicalc(double res[tam]);
void divicalc(double res[tam]);

//Reactancias//
void resist();


void main(void)
{
	gotoxy(8,0);
	printf("Programa para resolver sistema de ecuaciones con numeros complejos \n");
	gotoxy(23,10);
	printf("Autor: Marco Antonio Peredo Tiburcio \n");
	gotoxy(0,23);
	printf("Version: 1.1 (16/04/2013)\n");
	system("pause");
	double xdet[tam];
	double real[tam][tam],complejo[tam][tam],pol[tam][tam],angulo[tam][tam],a[tam][tam];
	double real1[tam][tam],complejo1[tam][tam],pol1[tam][tam],angulo1[tam][tam];
	int c,n,m,o;
	double grads=0;
	int menu=0;
	int select=0;
	while(select==0)
	{
		
		system("cls");		
		printf("Seleccione la opcion requerida:\n");
		printf("\n1.\t Introducir numero de incognitas.\n");
		printf("\n2.\t Introducir todas las incognitas.\n");
		printf("\n3.\t Introducir cierta incognita.\n");
		printf("\n4.\t Mostrar el sistema de ecuaciones.\n");
		printf("\n5.\t Calcular las incognitas.\n\n");
		printf("\n8.\t Calculadora de complejos.\n\n");
		printf("\n9.\t Salir.\n\n Seleccion: ");
		scanf("%i",&menu);
		if(menu==7)
		{
			resist();
		}
		if(menu==8) // agregar cada opcion de menu nueva al if de "diferente a..." del final para que funcione
		{
			calculadora();
		}
		if(menu==1) 
		{
			system("cls");
			printf("Numero de variables a calcular: ");
			scanf("%i",&n);
			m=n+1;
		}
		if(menu==2)	
		{
			fillmaster(real,complejo,pol,angulo,n,m);
			fillmatrixdet(real,complejo,pol,angulo,real1,complejo1,pol1,angulo1,n,m);
		}
		if(menu==3)
		{
			int q,p,op,in=0;
			system("cls");
			printf("Ecuacion numero: ");
			scanf("%i",&q);
			q=q-1;
			printf("Incognita numero: ");
			scanf("%i",&p);
			p=p-1;
			while(in==0)
			{
				system("cls");
				printf("\n Para la posicion %i,%i Ingresar valor en forma:\n1.\tRectangular \n2.\tPolar\nR:\t",q+1,p+1);
				scanf("%i",&op);
				if(op==1) 
				{
					fillmatrix(real,complejo,q,p);
					topolar(&real[q][p],&complejo[q][p],&pol[q][p],&angulo[q][p]);
					in=1;

				}
				if(op==2) 
				{
					fillmatrix2(pol,angulo,q,p);
					torectangular(&real[q][p],&complejo[q][p],&pol[q][p],&angulo[q][p]);
					in=1;
				}
				if(op!=1 && op!=2) 
				{
					printf("Opcion no valida");
					system("pause");
				}			
			}
			fillmatrixdet(real,complejo,pol,angulo,real1,complejo1,pol1,angulo1,n,m);
		}
		if(menu==4) printmatrix(real,complejo,pol,angulo,n);
		if(menu==5)	
		{
			fillmatrixdet(real,complejo,pol,angulo,real1,complejo1,pol1,angulo1,n,m);	//Determinante del denominador para Cramer
			for(c=0;c<4;c++)
				{
					xdet[c]=0;
				}
			settings(real,complejo,pol,angulo,n,m,xdet,a,real1,complejo1,pol1,angulo1);
			if(xdet[2]!=0)
			{
				system("cls");
				printf("Mostrar resultados en:\n1.\tRectangular\n2.\tPolar\nSeleccion:\t");
				scanf("%i",&o);
				system("cls");
				if(o==1)
				{
					for(c=0;c<n;c++)
					{	
						printf(" Incognita #%i Real: %10.6lf Complejo: %10.6lf \n",c+1,a[c][0],a[c][1]);
					}
				}
				if(o==2)
				{
					for(c=0;c<n;c++)
					{
						grads=(a[c][3]*180)/PI;
						printf(" Incognita #%i Polar: %10.6lf Angulo: %10.6lf \n",c+1,a[c][2],grads);
					}
				}
				if(o!=1 && o!=2) printf("Opcion no valida");
				system("pause");
			}
		}
		if(menu==9) 
		{
			select=1;
			/*system("cls");
			printf("Agradecimientos especiales para Ser-gio St. Anne Moss Village sir\n");*/
		}
		if(menu!=1 && menu!=2 && menu!=3 && menu!=4 && menu!=5 && menu!=9 && menu!=8 && menu!=7)
		{
			system("cls");
			printf("Opcion no valida");
		}


	}

	


}

void settings(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n,int m,double xdet[tam],double a[tam][tam],double real1[tam][tam],double complejo1[tam][tam],double pol1[tam][tam],double angulo1[tam][tam])
{
	//Determina si el sistema de ecuaciones es mayor a 3x2, de no ser así aplica el determinante de una funcion 2x2
	system("cls");
	if(n>2) determinant(real1,complejo1,pol1,angulo1,n,xdet); //Determinante de la matriz base
	else d2(real1,complejo1,pol1,angulo1,xdet);

	if(xdet[2]!=0) cramer(real,complejo,pol,angulo,xdet,a,n,m);
	else printf("Sistema de ecuaciones sin solucion\n ");
	
}

void cramer(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],double xdet[tam],double a[tam][tam],int n,int m)
{
	//Mediante ciclos va creando matrices de acuerdo al método de Gauss.
	//Cuando crea una matriz inmediatamente saca su determinante. Al obtenerlo lo divide sobre el determinante de la matriz principal.
	//El programa toma en cuenta todas las reglas del método de Gauss para determinantes de 3x3 en adelante.
	double adet[tam],realt[tam][tam],complejot[tam][tam],polt[tam][tam],angulot[tam][tam];
	
	int cty,h,c,y,u;
	
	for(h=0;h<=(n-1);h++)
	{
		for(u=0;u<4;u++)
		{
			adet[u]=0;
		}
		
		for(c=0;c<=(n-1);c++)
		{
			cty=0;
			
			for(y=0;y<=(m-2);y++)
			{
				if(y!=h)
				{
					realt[c][cty]=real[c][y];
					complejot[c][cty]=complejo[c][y];
					polt[c][cty]=pol[c][y];
					angulot[c][cty]=angulo[c][y];

					cty=cty+1;
				}
				else
				{
					realt[c][cty]=real[c][m-1];
					complejot[c][cty]=complejo[c][m-1];
					polt[c][cty]=pol[c][m-1];
					angulot[c][cty]=angulo[c][m-1];

					cty=cty+1;
				}
			}
		}
		if(n>2) determinant(realt,complejot,polt,angulot,n,adet);
		else d2(realt,complejot,polt,angulot,adet);
		
		divi(adet[0],adet[1],adet[2],adet[3],xdet[0],xdet[1],xdet[2],xdet[3],&a[h][0],&a[h][1],&a[h][2],&a[h][3]);
	}
}
void fillmaster(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n,int m)
{
	system("cls");
	int op,c,y=0;
	int in=0;
	while(in==0)
	{

		for(c=0;c<n;c++)
		{
			for(y=0;y<m;y++)
			{
				system("cls");
				printf("\n Para la posicion %i,%i Ingresar valor en forma:\n1.\tRectangular \n2.\tPolar\n3.\tSaltar\nSeleccion:\t",c+1,y+1);
				scanf("%i",&op);
				if(op==1) 
				{
					fillmatrix(real,complejo,c,y);
					topolar(&real[c][y],&complejo[c][y],&pol[c][y],&angulo[c][y]);
				}
				if(op==2) 
				{
					fillmatrix2(pol,angulo,c,y);
					torectangular(&real[c][y],&complejo[c][y],&pol[c][y],&angulo[c][y]);
				}
				if(op!=1 && op!=2 && op!=3) 
				{
					printf("Opcion no valida en %i,%i",c,y);
					system("pause");
				}
				if(op==3) in=1;
			}
		}
	}
}

void fillmatrix(double real[tam][tam],double complejo[tam][tam],int c,int y)
{
	printf("Parte Real:\t");
	scanf("%lf",&real[c][y]);
	printf("Parte Imaginaria:\t");
	scanf("%lf",&complejo[c][y]);
}

void fillmatrix2(double pol[tam][tam],double angulo[tam][tam],int c,int y)
{
	printf("Valor Polar:\t");
	scanf("%lf",&pol[c][y]);
	printf("Angulo:\t");
	scanf("%lf",&angulo[c][y]);
	angulo[c][y]= PI*angulo[c][y]/180;
	
	
}

void printmatrix(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n)
{
	system("cls");
	int c,y,op;
	printf("Mostrar el sistema de ecuaciones en forma:\n1.\tRectangular\n2.\tPolar\nSeleccion:\t");
	scanf("%i",&op);
	if(op==1)
	{
		for(c=0;c<n;c++)
		{	
			printf("\nEcuacion #%i\n:",c+1);
			for(y=0;y<n+1;y++)
			{
				printf("\n Real: %lf e Imaginaria: %lf \n",real[c][y],complejo[c][y]);

			}
		}
	}
	else
	{
		double grads;
		if(op==2)
		{
			for(c=0;c<n;c++)
			{
				printf("\nEcuacion #%i\n:",c+1);
				for(y=0;y<n+1;y++)
				{
					grads=(angulo[c][y]*180)/PI;
					printf("\n Polar: %lf y Angulo: %lf \n",pol[c][y],grads);
				}
			}
		}
		else
		{
			printf("Opcion no valida\n");
		}
	}
	system("pause");
}

void topolar(double *real,double *complejo,double *pol,double *angulo)
{
	*pol= pow(pow(*complejo,2)+ pow(*real,2),0.5);
	if((*real)==0) 
	{
		if(*complejo>0)
		{
			*angulo=(90*PI)/180;

		}
		if(*complejo<0) *angulo = -(90*PI/180);
		if(*complejo==0) *angulo = 0;
	}
	else
	{
		if(*complejo==0)
		{
			if(*real>0) *angulo=0;
			else *angulo=PI;
		}
		else 
		{
			*angulo=atan(*complejo/(*real));
			if(*real<0 && *complejo<0) *angulo = (*angulo)-PI;
		}
	}	
}
void torectangular(double *real,double *complejo,double *pol,double *angulo)
{
	*real= (*pol) * cos(*angulo);

	*complejo = (*pol) * sin(*angulo);
	
}
void determinant(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],int n,double det[tam])
{
	int ct,ct2,m,c,y;
	double dett[tam],coef[tam]; //dett es una determinante temporal, coef el coeficiente por el que se multiplica el det de la matriz.
	double realt[tam][tam],complejot[tam][tam],polt[tam][tam],angulot[tam][tam];
	for(m=0;m<=(n-1);m++)
	{
		ct=0;
		ct2=0;
		
		for(c=1;c<=(n-1);c++) //Este ciclo for Arma matrices mas pequeñas dentro de la matriz, el det de cada matriz se agrega a la variable det
		{
			for(y=0;y<=(n-1);y++)
			{
				if(y!=m)
				{
					realt[ct][ct2]=real[c][y];
					complejot[ct][ct2]=complejo[c][y];
					polt[ct][ct2]=pol[c][y];
					angulot[ct][ct2]=angulo[c][y];
					ct2=ct2+1;
				}

			}
			ct=ct+1;
			ct2=0;
		}
		if(ct==2) d2(realt,complejot,polt,angulot,dett);  //Cuando la matriz armada ya es 2x2 se pued sacar su determinante.
		else 
		{
			for(c=0;c<4;c++)
			{
				dett[c]=0;
			}
			determinant(realt,complejot,polt,angulot,ct,dett); //Si al armar la nueva matriz esta es mayor a 2x2 entra de nuevo a este metodo
		}

		double t[tam];
		t[0]=pow(-1,m+2);
		t[1]=0;
		t[2]=1;
		if(t[0]>0) t[3]=0;
		else t[3]=PI;

		multi(real[0][m],complejo[0][m],pol[0][m],angulo[0][m],t[0],t[1],t[2],t[3],&coef[0],&coef[1],&coef[2],&coef[3]);
		multi(coef[0],coef[1],coef[2],coef[3],dett[0],dett[1],dett[2],dett[3],&t[0],&t[1],&t[2],&t[3]);
		sumar(t[0],t[1],t[2],t[3],det[0],det[1],det[2],det[3],&det[0],&det[1],&det[2],&det[3]);
	}
}

void d2(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],double det[tam])
{
	// 0 real	 1 complejo		2 polar	 3 angulo
	double t[tam];
	multi(real[0][0],complejo[0][0],pol[0][0],angulo[0][0],real[1][1],complejo[1][1],pol[1][1],angulo[1][1],&det[0],&det[1],&det[2],&det[3]);
	multi(real[0][1],complejo[0][1],pol[0][1],angulo[0][1],real[1][0],complejo[1][0],pol[1][0],angulo[1][0],&t[0],&t[1],&t[2],&t[3]);

	restar(det[0],det[1],det[2],det[3],t[0],t[1],t[2],t[3],&det[0],&det[1],&det[2],&det[3]);
	


}

void sumar(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3)
{
	*real3 = (real1) + (real2);
	*complejo3 = (complejo1) + (complejo2);
	
	
	topolar(*&real3,*&complejo3,*&pol3,*&angulo3);
}

void restar(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3)
{
	*real3 = (real1) - (real2);
	*complejo3 = (complejo1) - (complejo2);
	
	
	topolar(*&real3,*&complejo3,*&pol3,*&angulo3);
}

void multi(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3)
{
	
	*real3 = (real1*real2) - (complejo1*complejo2);
	*complejo3 = (real1*complejo2) + (complejo1*real2);
	
	topolar(*&real3,*&complejo3,*&pol3,*&angulo3);

}

void divi(double real1,double complejo1,double pol1, double angulo1,double real2,double complejo2,double pol2, double angulo2,double *real3,double *complejo3,double *pol3,double *angulo3)
{
	
	*real3 = ( (real1*real2) + (complejo1*complejo2) ) / ( pow(real2,2)+pow(complejo2,2) );
	*complejo3 =( (complejo1*real2 ) - (real1*complejo2) ) / ( pow(real2,2)+pow(complejo2,2) );

	topolar(*&real3,*&complejo3,*&pol3,*&angulo3);

}

void fillmatrixdet(double real[tam][tam],double complejo[tam][tam],double pol[tam][tam],double angulo[tam][tam],double real1[tam][tam],double complejo1[tam][tam],double pol1[tam][tam],double angulo1[tam][tam],int n,int m)
{
	int c,y;
	
	for(c=0;c<=(n-1);c++)
	{
		for(y=0;y<=(m-2);y++)
		{
			real1[c][y]=real[c][y];
			complejo1[c][y]=complejo[c][y];
			pol1[c][y]=pol[c][y];
			angulo1[c][y]=angulo[c][y];
		}
	}
}

void gotoxy(int x, int y)
{
COORD coord;
coord.X = x; coord.Y = y;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hStdOut, coord);
}


void calculadora()
{
	int op;
	int in=0;
	while(in==0)
	{

		system("cls");
		double res[tam];
		int c;
		for(c=0;c<4;c++)
		{
			res[c]=0;
		}
		gotoxy(20,0);
		printf("Calculadora de numeros complejos\n");
		printf("\n\nSeleccione la operacion a realizar:\n\n1.\tSuma\n2.\tResta\n3.\tMultiplicacion\n4.\tDivision\n\n9.\tSalir\nSeleccion:\t");
		scanf("%i",&op);
		if(op==9)//salir
		{
			in=1;
		}
		if(op==1)//suma
		{
			sumacalc(res);	
		}
		if(op==2)//resta
		{
			restacalc(res);
		}
		if(op==3)//multiplicacion
		{
			multicalc(res);
		}
		if(op==4)//division
		{
			divicalc(res);
		}
		if(op!=1 && op!=2 && op!=3 && op!=4 && op!=9)
		{
			printf("\n Opcion no valida\n");
		}
		system("pause");
	}
}

void sumacalc(double res[tam])
{
	system("cls");
	double num1[tam],num2[tam];
	int op;
	int in=0;
	while(in==0)
	{
		system("cls");
		printf("Primer numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num1[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num1[1]);
			topolar(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num1[2]);
			printf("Angulo:\t");
			scanf("%lf",&num1[3]);
			torectangular(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}
	in=0;
	while(in==0)
	{
		system("cls");
		printf("Segundo numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num2[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num2[1]);
			topolar(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num2[2]);
			printf("Angulo:\t");
			scanf("%lf",&num2[3]);
			torectangular(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}

	sumar(num1[0],num1[1],num1[2],num1[3],num2[0],num2[1],num2[2],num2[3],&res[0],&res[1],&res[2],&res[3]);
	system("cls");
	printf("Resultado:\n\n");
	printf("Rectangular:\t%lf\n",res[0]);
	printf("Imaginario:\t%lf\n\n",res[1]);
	printf("Polar:\t%lf\n",res[2]);
	printf("Angulo:\t%lf\n",(res[3]*180)/PI);



	
	
}

void restacalc(double res[tam])
{
	system("cls");
	double num1[tam],num2[tam];
	int op;
	int in=0;
	while(in==0)
	{
		system("cls");
		printf("Primer numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num1[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num1[1]);
			topolar(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num1[2]);
			printf("Angulo:\t");
			scanf("%lf",&num1[3]);
			torectangular(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}
	in=0;
	while(in==0)
	{
		system("cls");
		printf("Segundo numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num2[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num2[1]);
			topolar(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num2[2]);
			printf("Angulo:\t");
			scanf("%lf",&num2[3]);
			torectangular(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}

	restar(num1[0],num1[1],num1[2],num1[3],num2[0],num2[1],num2[2],num2[3],&res[0],&res[1],&res[2],&res[3]);
	system("cls");
	printf("Resultado:\n\n");
	printf("Rectangular:\t%lf\n",res[0]);
	printf("Imaginario:\t%lf\n\n",res[1]);
	printf("Polar:\t%lf\n",res[2]);
	printf("Angulo:\t%lf\n",(res[3]*180)/PI);



	
	
}

void multicalc(double res[tam])
{
	system("cls");
	double num1[tam],num2[tam];
	int op;
	int in=0;
	while(in==0)
	{
		system("cls");
		printf("Primer numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num1[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num1[1]);
			topolar(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num1[2]);
			printf("Angulo:\t");
			scanf("%lf",&num1[3]);
			torectangular(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}
	in=0;
	while(in==0)
	{
		system("cls");
		printf("Segundo numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num2[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num2[1]);
			topolar(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num2[2]);
			printf("Angulo:\t");
			scanf("%lf",&num2[3]);
			torectangular(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}

	multi(num1[0],num1[1],num1[2],num1[3],num2[0],num2[1],num2[2],num2[3],&res[0],&res[1],&res[2],&res[3]);
	system("cls");
	printf("Resultado:\n\n");
	printf("Rectangular:\t%lf\n",res[0]);
	printf("Imaginario:\t%lf\n\n",res[1]);
	printf("Polar:\t%lf\n",res[2]);
	printf("Angulo:\t%lf\n",(res[3]*180)/PI);



	
	
}

void divicalc(double res[tam])
{
	system("cls");
	double num1[tam],num2[tam];
	int op;
	int in=0;
	while(in==0)
	{
		system("cls");
		printf("Primer numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num1[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num1[1]);
			topolar(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num1[2]);
			printf("Angulo:\t");
			scanf("%lf",&num1[3]);
			torectangular(&num1[0],&num1[1],&num1[2],&num1[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}
	in=0;
	while(in==0)
	{
		system("cls");
		printf("Segundo numero:\n\n1.\tRectangular\n2.\tPolar\n");
		printf("Seleccion:\t");
		scanf("%i",&op);
		if(op==1) 
		{
			printf("\nParte Real:\t");
			scanf("%lf",&num2[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&num2[1]);
			topolar(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op==2) 
		{
			printf("\nParte Polar:\t");
			scanf("%lf",&num2[2]);
			printf("Angulo:\t");
			scanf("%lf",&num2[3]);
			torectangular(&num2[0],&num2[1],&num2[2],&num2[3]);
			in=1;
		}
		if(op!=1 && op!=2) 
		{
			printf("Opcion no valida\n");
			system("pause");
		}
	}

	divi(num1[0],num1[1],num1[2],num1[3],num2[0],num2[1],num2[2],num2[3],&res[0],&res[1],&res[2],&res[3]);
	system("cls");
	printf("Resultado:\n\n");
	printf("Rectangular:\t%lf\n",res[0]);
	printf("Imaginario:\t%lf\n\n",res[1]);
	printf("Polar:\t%lf\n",res[2]);
	printf("Angulo:\t%lf\n",(res[3]*180)/PI);
	
}

void resist()
{
	system("cls");
	double z1[tam],z2[tam],t[tam];
	int op;
	int in=0;
	int in2,op2;
	while(in==0)
	{
		printf("Introduzca valores de la primera Resistencia");
		printf("\n1.\tRectangular\n2.\tPolar\nSeleccion:\t");
		scanf("%i",&op);
		if(op==1)
		{

			printf("\nParte Real:\t");
			scanf("%lf",&z1[0]);
			printf("Parte Imaginaria:\t");
			scanf("%lf",&z1[1]);
			topolar(&z1[0],&z1[1],&z1[2],&z1[3]);
			in=1;
		}
		if(op==2)
		{

			printf("\nPolar:\t");
			scanf("%lf",&z1[2]);
			printf("Angulo:\t");
			scanf("%lf",&z1[3]);
			torectangular(&z1[0],&z1[1],&z1[2],&z1[3]);
			in=1;
		}
		if(op!=1 && op!=2)
		{
			printf("\nOpcion no valida\n");
			system("pause");
			system("cls");
		}
	}
	in=0;
	op=0;

	while(in==0)
	{
		system("cls");
		printf("Resistencia a sumar en:\n1.\tSerie\n2.\tParalelo\n\n9.\tSalir\nSeleccion:\t");
		scanf("%i",&op);
		if(op!=1 && op!=2 && op!=9)
		{
			printf("\nOpcion no valida\n");
			system("pause");
			system("cls");
		}
		else
		{
			if(op==9) in=1;
			
			else
			{
				in2=0;
				op2=0;
				while(in2==0) //CHECAR WHILES
				{
					system("cls");
					printf("Introduzca valores de la segunda Resistencia");
					printf("\n1.\tRectangular\n2.\tPolar\nSeleccion:\t");
					scanf("%i",&op2);
					if(op2==1)
					{
	
						printf("\nParte Real:\t");
						scanf("%lf",&z2[0]);
						printf("Parte Imaginaria:\t");
						scanf("%lf",&z2[1]);
						topolar(&z2[0],&z2[1],&z2[2],&z2[3]);
						in2=1;
					}
					if(op2==2)
					{
	
						printf("\nPolar:\t");
						scanf("%lf",&z2[2]);
						printf("Angulo:\t");
						scanf("%lf",&z2[3]);
						torectangular(&z2[0],&z2[1],&z2[2],&z2[3]);
						in2=1;
					}
					if(op2!=1 && op2!=2)
					{
						printf("\nOpcion no valida\n");
						system("pause");
						system("cls");
					}
				}	
				if(op2==1) sumar(z1[0],z1[1],z1[2],z1[3],z2[0],z2[1],z2[2],z2[3],&z1[0],&z1[1],&z1[2],&z1[3]); //Serie
				
				if(op2==2) //Paralelo
				{
					multi(z1[0],z1[1],z1[2],z1[3],z2[0],z2[1],z2[2],z2[3],&z1[0],&z1[1],&z1[2],&z1[3]); //Multiplicación del 1ero por el 2do
					sumar(z1[0],z1[1],z1[2],z1[3],z2[0],z2[1],z2[2],z2[3],&t[0],&t[1],&t[2],&t[3]);	//Suma del 1ero más el 2do
					divi(z1[0],z1[1],z1[2],z1[3],t[0],t[1],t[2],t[3],&z1[0],&z1[1],&z1[2],&z1[3]); //Division de multi sobre la suma
				}
				system("cls");
				printf("Resultado:\n\n");
				printf("Rectangular:\t%lf\n",z1[0]);
				printf("Imaginario:\t%lf\n\n",z1[1]);
				printf("Polar:\t%lf\n",z1[2]);
				printf("Angulo:\t%lf\n",(z1[3]*180)/PI);
				system("pause");
			}
		}
	}
}