#include <graphics.h>
#include <stdio.h>


int RCTR(int*Snom,float*Km,float*Kd,float*Kl,float*Stoim,float*Pxx,float
*Pkz,float*Ixx,float*Ukz,float*Ztr,float*Xtr,float*Rtr,float*Qxx)
{
int i=100;
int KAT;
char A[i];

FILE*catalog;
catalog=fopen("C:\\11\\trans.dll","rt");
if ( catalog == NULL )
{printf("CAN'T FIND ANY DATA FILE\n");}//проверка на чтение

for(i=1;i<=35;i++)
{fscanf ( catalog, "%c", &A[i]);
//printf ( "%c", A[i]);
}

for(i=1;i<100;i++)
{fscanf ( catalog, "%d%f%f", &Snom[i],&Km[i],&Kd[i]);
 fscanf ( catalog, "%f%f%f", &Kl[i],&Stoim[i],&Pxx[i]);
 fscanf ( catalog, "%f%f%f", &Pkz[i],&Ixx[i],&Ukz[i]);
Ztr[i]=(Ukz[i]/100)*10*10*1000/(Snom[i]);
Rtr[i]=Pkz[i]*1000*10*10/(Snom[i]*Snom[i]);
Xtr[i]=sqrt(Ztr[i]*Ztr[i]-Rtr[i]*Rtr[i]);
Qxx[i]=Ixx[i]*Snom[i]/100;
   		if (Snom[i] >= 999999){KAT=i-1;break;}//проверка на окончание списка
//printf ("%d %f %f\n", Snom[i],Km[i],Kd[i]);
//printf ("%d %f %f\n",Snom[i], Stoim[i],Pxx[i]);
//printf ("%f %f %f\n",Pkz[i],Ixx[i],Ukz[i]);
//printf ("**%f**\n",Pxx[i]);
}
//printf("%d\n",KAT);
return KAT;
}
