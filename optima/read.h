#include <graphics.h>
#include <stdio.h>


int read(char*a,int*Nu,int*Ku,int*Sust,float*length,float*Kzagr,
float*Cos,float*Tnb,char*type)
{
int i=200;
int NU;
char A[i];
FILE*input;
input=fopen(a,"rt");
if ( input == NULL )
{printf("CAN'T FIND ANY INPUT FILE\n");}//проверка на чтение

for(i=1;i<=61;i++)
{fscanf ( input, "%c", &A[i]);
//printf ( "%c", A[i]);
}

for(i=1;i<200;i++)
{fscanf ( input, "%d%d%s%d%f%f%f%f", &Nu[i],&Ku[i],&type[i],&Sust[i],&length[i],
&Kzagr[i],&Cos[i],&Tnb[i]);
if (Nu[i] == 9999 ){break;}//проверка на окончание списка
//printf ( "%d %d %c %d %f %f %f %f\n", Nu[i],Ku[i],type[i],Sust[i],length[i],
//Kzagr[i],Cos[i],Tnb[i]);
}
NU=i-1;//число участков в исследуемой сети
return NU;
}
