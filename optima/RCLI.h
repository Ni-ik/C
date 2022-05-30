#include <graphics.h>
#include <stdio.h>


int RCLI(int*Fnom,float*R0,float*X0,float*Id,float*Iq)
{
int i=200;
int KAL;
char A[i];

FILE*catalog;
catalog=fopen("C:\\11\\line.dll","rt");
if ( catalog == NULL )
{printf("CAN'T FIND ANY DATA FILE\n");}//проверка на чтение

for(i=1;i<=17;i++)
{fscanf ( catalog, "%c", &A[i]);
//printf ( "%c", A[i]);
}

for(i=1;i<100;i++)
{fscanf ( catalog, "%d%f%f%f%f", &Fnom[i],&R0[i],&X0[i],&Id[i],&Iq[i]);
if (Fnom[i] >= 999999){KAL=i-1;break;}//проверка на окончание списка
//printf ("%d %f %f\n", Fnom[i],R0[i],X0[i]);
}

return KAL;
}
