#include <graphics.h>
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include "read.h"
#include "sort.h"
#include "RCTR.h"
#include "RCLI.h"

int main()
{
int i=20,j=100;
int Nu[i],Ku[i],Sust[i];
int KAT,KAL,NU;//число трансформаторов в каталоге и в схеме
float Kzagr[i],Cos[i],Tnb[i];
float Pxx[i],Pkz[i],Ixx[i],Ukz[i],Qxx[i]; 
//потери холостого хода, нагрузочные, ток хх, напряжение кз
float Ztr[i], Xtr[i], Rtr[i];//сопротивления трансформатора
float X0[i], R0[i];//сопротивления линий
float XU[i], RU[i];//сопротивления линий
float Km[i], Kd[i],Kl[i],Stoim[i];
//стоимость монтажа, демонтажа, ликвидная, покупки
int Snom[i];//номинальная мощность трансформатора
int Fnom[i];//номинальное сечение линии
float Id[i],Iq[i];
int NK[i],NKL[i];
char type[i];
float length[i];
char a[]="c:\\11\\input2.dat";

NU=read(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type); 
printf("At the scheme %d elements\n",NU);
sort(NU,Nu,Ku,type,Sust,length,Kzagr,Cos,Tnb);
KAT=RCTR(Snom,Km,Kd,Kl,Stoim,Pxx,Pkz,Ixx,Ukz,Ztr,Xtr,Rtr,Qxx);
printf("In the catalog %d transforms\n",KAT);
KAL=RCLI(Fnom,R0,X0,Id,Iq); 
printf("In the catalog %d lines\n",KAL);

for(j=1;j<=NU;j++)//Поиск соответствия в каталоге
{if(type[j]=='T')
{for(i=1;i<=KAT;i++)
{if (Sust[j]==Snom[i])
{NK[j]=i;
RU[j]=Rtr[i];
XU[j]=Xtr[i];break;}}}
if(type[j]=='A')
{for(i=1;i<=KAL;i++)
{if (Sust[j]==Fnom[i])
{NKL[j]=i;
RU[j]=R0[i]*length[j];
XU[j]=X0[i]*length[j];break;}}}
}


for(i=1;i<=NU;i++)
{printf ( "%d %d %d %c %d %f %d %f %f %f\n",i, Nu[i],Ku[i],type[i],
Sust[i],RU[i],Snom[NK[i]],Kzagr[i],Cos[i],Qxx[NK[i]]);}





















}
