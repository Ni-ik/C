#include <stdio.h>
#include<stdlib.h>
#include "calculate.h"
#include <math.h>

int main()
{
int i=200, j=200;
char a[]="c:\\11\\input.dat";//файл исходной информации 	
int Nu[i],Ku[i],Sust[i];//номера начала, конца, установленная мощность тр-ра	 
float Kzagr[i],Cos[i],Tnb[i];//коэф. загрузки, мощности, время исп. наиб. нагрузки	 
float length[i];//длина участка
char type[i];//тип (трансформатор или линия)
int NU,NK[i],KAT;//К-во участков, Номер тр-ра в каталоге, число тр-ров в каталоге
int Snom[i];//номинальная мощность трансформатора
float Pxx[i],Pkz[i],Ixx[i],Ukz[i],Qxx[i]; 
//потери холостого хода, нагрузочные, ток хх, напряжение кз
float Ztr[i], Xtr[i], Rtr[i];//сопротивления трансформатора
float Km[i], Kd[i],Kl[i],Stoim[i];//стоимость монтажа, демонтажа, ликвидная, покупки
double dWPxxSum=0, dWPnSum=0;//Суммарные потери хх и нагрузочные
double dW;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Чтение исходной информации
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
NU=read(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type);//чтение информации из исходного файла
//printf("At the scheme %d elements\n",NU);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Чтение каталога
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
KAT=RCTR(Snom,Km,Kd,Kl,Stoim,Pxx,Pkz,Ixx,Ukz,Ztr,Xtr,Rtr,Qxx);
//printf("In the catalog %d transforms\n",KAT);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Расчет режима
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
dW=calc(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type,NU,NK,Snom,Km,Kd,Kl,Stoim,Pxx,
Pkz,Ixx,Ukz,Ztr,Xtr,Rtr,Qxx,KAT,dWPxxSum,dWPnSum);//расчет режима
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Расчет экономических показателей
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Объявление переменных
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
float Tek=10;//Период экономического расчета
float E=0.12;//Коэффициент экономической эффенктивности
float EK=0;//Коэффициент приведения
for(i=0;i<=Tek;i++)
{EK=EK+pow(E+1,-i);}
float Pa=0.063;//Коэффициент амортизации
double Zatr[200][200];//затраты
double WW;
int nk[200];
int uu;
double pp;
float tt;
for(i=1;i<=NU;i++)
{//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Чтение исходной информации
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//NU=read(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type);//чтение информации из исходного файла
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Расчет режима
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
dW=calc(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type,NU,NK,Snom,Km,Kd,Kl,Stoim,Pxx,
Pkz,Ixx,Ukz,Ztr,Xtr,Rtr,Qxx,KAT,dWPxxSum,dWPnSum);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Расчет экономических показателей
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if(type[i]=='T')
{Zatr[i][0]=(dW*0.12+Pa*Stoim[NK[i]])*EK;
printf("%d-%d change %d\n",Nu[i],Ku[i],Snom[NK[i]]);
for(j=1;j<=KAT;j++)
{if((Sust[i]*Kzagr[i]/2)<=Snom[j])//ограничение по загрузке трансформатора
{
NU=read(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type);
//чтение информации из исходного файла и обнуление результатов
dW=calc(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type,NU,NK,Snom,Km,Kd,Kl,Stoim,Pxx,
Pkz,Ixx,Ukz,Ztr,Xtr,Rtr,Qxx,KAT,dWPxxSum,dWPnSum);
Kzagr[i]=Kzagr[i]*Sust[i]/Snom[j];
Sust[i]=Snom[j];
nk[j]=NK[i];
WW=calc(a,Nu,Ku,Sust,length,Kzagr,Cos,Tnb,type,NU,NK,Snom,Km,Kd,Kl,Stoim,Pxx,
Pkz,Ixx,Ukz,Ztr,Xtr,Rtr,Qxx,KAT,dWPxxSum,dWPnSum);
//printf("Kz=%f Sust=%d Snom=%d Km=%f Kd=%f Kl=%f ST=%f\n",Kzagr[i],Snom[nk[j]],Snom[j],Km[j],Kd[nk[j]],Kl[nk[j]],Stoim[j]);
pp=(WW*0.12+Pa*Stoim[j])*EK+Km[j]+Kd[nk[j]]-Kl[nk[j]]+Stoim[j];
if(Snom[nk[j]]==Snom[j]){pp=Zatr[i][0];}
Zatr[i][j]=pp;
printf("WW=%f Z=%f pp=%f Sstar=%d Snov=%d\n",WW,Zatr[i][j],Zatr[i][0]-Zatr[i][j],Snom[nk[j]],Snom[j]);
}
}}}
}

