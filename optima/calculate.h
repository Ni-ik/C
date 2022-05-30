#include <graphics.h>
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include "read.h"
#include "sort.h"
#include "RCTR.h"
#include "RCLI.h"
#include "nuzl.h"
#include "VAO.h"

double calc(char*a,int*Nu,int*Ku,int*Sust,float*length,float*Kzagr,
float*Cos,float*Tnb,char*type,int NU, int*NK,int*Snom,float*Km,float*Kd,
float*Kl,float*Stoim,float*Pxx,float*Pkz,float*Ixx,float*Ukz,float*Ztr,
float*Xtr,float*Rtr,float*Qxx, int KAT, double dWPxxSum, double dWPnSum)
{
int i=200,j=200, k=200;//переменные цикла
int NKL[i];//номер линии в каталогах
int KAL;
//число трансформаторов и линий в каталоге и в схеме
float X0[i], R0[i];//сопротивления линий
float XU[i], RU[i];//сопротивления участков
int Fnom[i];//номинальное сечение линии
float Id[i],Iq[i];//токи допустимый и емкостной
int NUZL;//число узов в сети
sort(NU,Nu,Ku,type,Sust,length,Kzagr,Cos,Tnb);//сортировка инфы
KAL=RCLI(Fnom,R0,X0,Id,Iq); 
//printf("In the catalog %d lines\n",KAL);
NUZL=NUZ(Ku,NU);//определим количество узлов в сети
//printf("At the scheme %d points\n",NUZL);

//Поиск соответствия в каталоге и расчет сопротивлений участков
for(j=1;j<=NU;j++)
{if(type[j]=='T')//если это трансформатор, то поиск в каталоге тр-ров
{for(i=1;i<=KAT;i++)
{if (Sust[j]==Snom[i])
{NK[j]=i;
RU[j]=Rtr[i];
XU[j]=Xtr[i];
Pxx[j]=Pxx[i];
Qxx[j]=Qxx[i];
break;}}}
if(type[j]=='A')//если это провод, то поиск в каталоге проводов
{for(i=1;i<=KAL;i++)
{if (Sust[j]==Fnom[i])
{NKL[j]=i;
RU[j]=R0[i]*length[j];
XU[j]=X0[i]*length[j];
Pxx[j]=0;
Qxx[j]=0;
break;}}}
}

int VAO[NU];//построение массива вторых адресных отображений
vao(VAO,Ku,Nu,NU);

//объявление переменных для рассчета нагрузки
double Pnagr[NU], Qnagr[NU];//акт. и реакт. мощность нагрузки
double WPnagr[NU],WQnagr[NU];//акт. и реакт. энергия нагрузки
double WPku[NU], WQku[NU];//акт. и реакт. энергия в конце участка
float Pku[NU], Qku[NU];//акт. и реакт. мощность в конце участка
double Pnu[NU], Qnu[NU];//акт. и реакт. мощность в начале участка
double dPxx[NU],dQxx[NU],dPkz[NU],dQkz[NU];//потери хх и кз, аткивные и реакт
double dP[NU],dQ[NU];//потери аткивные и реакт
double PnuT[NU], QnuT[NU];//поток в начале участка
double WPnuT[NU], WQnuT[NU];//потоки электроэнергии
double U[NUZL];//напряжение в узлах
double Unom=10;//номинальное напряжение
double Ugu=10;//напряжение питающего узла
double dU[NU];//падение напряжения на участках
double dPgu;
double e;
//+++++++++++++++++++++++++++++++++++++++++++
//с этого момента будет производиться расчет режима
//+++++++++++++++++++++++++++++++++++++++++++

//задаем напряжение в узах равное номинальному
for(i=1;i<=NUZL;i++)
{U[i]=Unom;}
U[1]=Ugu;

for(i=1;i<=20;i++)//итерационный расчет режима
{
//+++++++++++++++++++++++++++++++++++++++++++
//Расчет параметров нагрузки
//+++++++++++++++++++++++++++++++++++++++++++
for(j=1;j<=NU;j++)
{if(type[j]=='T')
{Pnagr[j]=Snom[NK[j]]*Kzagr[j]*Cos[j];
Qnagr[j]=Snom[NK[j]]*Kzagr[j]*sqrt(1-Cos[j]*Cos[j]);
WPnagr[j]=Pnagr[j]*Tnb[j];
WQnagr[j]=Qnagr[j]*Tnb[j];}
if(type[j]=='A')
{Pnagr[j]=0;Qnagr[j]=0;WPnagr[j]=0;WQnagr[j]=0;}
Pku[j]=Pnagr[j];Qku[j]=Qnagr[j];WPku[j]=WPnagr[j];WQku[j]=WQnagr[j];
}
//+++++++++++++++++++++++++++++++++++++++++++
//прямой ход, расчет потоков мощности по напряжению
//+++++++++++++++++++++++++++++++++++++++++++
for(j=NU;j>0;j--)
{
dP[j]=Pxx[j]*U[Nu[j]]*U[Nu[j]]*1000/(Unom*Unom)+//расчет акт.потерь
(Pku[j]*Pku[j]+Qku[j]*Qku[j])*RU[j]/(U[Ku[j]]*U[Ku[j]]);// в ваттах
dQ[j]=Qxx[j]*U[Ku[j]]*U[Ku[j]]/(Unom*Unom)+//расчет реак. потерь				
(Pku[j]*Pku[j]+Qku[j]*Qku[j])*XU[j]/(U[Ku[j]]*U[Ku[j]]);// в ваттах			 
Pku[VAO[j]]=Pku[VAO[j]]+Pku[j]+dP[j]/1000;//расчет акт. потока в конце участка
Qku[VAO[j]]=Qku[VAO[j]]+Qku[j]+dQ[j]/1000;//расчет реакт. потока в конце участка
Pnu[j]=Pku[j]+dP[j]/1000;//расчет акт. потока в начале участка
Qnu[j]=Qku[j]+dQ[j]/1000;//расчет реакт. потока в начале участка
}
//+++++++++++++++++++++++++++++++++++++++++++
//Обратный ход
//Расчет напряжения узлов
//+++++++++++++++++++++++++++++++++++++++++++
for(j=1;j<=NU;j++)
{dU[j]=(Pnu[j]*RU[j]+Qnu[j]*XU[j])*0.001/U[Nu[j]];//потери в киловольтах
U[Ku[j]]=U[Nu[j]]-dU[j];}
//+++++++++++++++++++++++++++++++++++++++++++
//Расчет погрешностей
//По потерям на головном участке
//+++++++++++++++++++++++++++++++++++++++++++
dPgu=(Pnu[1]*Pnu[1]+Qnu[1]*Qnu[1])*RU[1]/(Ugu*Ugu);
e=fabs((dPgu-dP[1])/dPgu);
if(e<0.01){break;}
//+++++++++++++++++++++++++++++++++++++++++++
}//конец итерационного расчета наибольших мощностей
//+++++++++++++++++++++++++++++++++++++++++++
//расче режима средних нагрузок
//+++++++++++++++++++++++++++++++++++++++++++
//Объявление переменных
//+++++++++++++++++++++++++++++++++++++++++++
double Pnagrsr[NU], Qnagrsr[NU];//акт. и реакт. мощность нагрузки
double WPnagrsr[NU],WQnagrsr[NU];//акт. и реакт. энергия нагрузки
double WPkusr[NU], WQkusr[NU];//акт. и реакт. энергия в конце участка
double Pkusr[NU], Qkusr[NU];//акт. и реакт. мощность в конце участка
double Pnusr[NU], Qnusr[NU];//акт. и реакт. мощность в начале участка
double dPsr[NU],dQsr[NU];//потери аткивные и реакт
double Usr[NUZL];//напряжение в узлах
double dUsr[NU];//падение напряжения на участках
double T=8760; //Время расчета
//задаем напряжение в узах равное номинальному
for(i=1;i<=NUZL;i++)
{Usr[i]=Unom;}
Usr[1]=Ugu;
for(i=1;i<=20;i++)//итерационный расчет режима средних нагрузок
{
//+++++++++++++++++++++++++++++++++++++++++++
//Расчет параметров нагрузки
//+++++++++++++++++++++++++++++++++++++++++++
for(j=1;j<=NU;j++)
{if(type[j]=='T')
{Pnagrsr[j]=WPnagr[j]/T; //Расчет средней акт. мощности нагрузки
Qnagrsr[j]=WQnagr[j]/T; //Расчет средней peакт. мощности нагрузки
}
if(type[j]=='A')
{Pnagrsr[j]=0;Qnagrsr[j]=0;}
Pkusr[j]=Pnagrsr[j];Qkusr[j]=Qnagrsr[j];WPku[j]=WPnagr[j];WQku[j]=WQnagr[j];
}
//+++++++++++++++++++++++++++++++++++++++++++
//прямой ход, расчет потоков мощности по напряжению
//+++++++++++++++++++++++++++++++++++++++++++
for(j=NU;j>0;j--)
{
dPsr[j]=Pxx[j]*Usr[Nu[j]]*Usr[Nu[j]]*1000/(Unom*Unom)+//расчет акт.потерь
(Pkusr[j]*Pkusr[j]+Qkusr[j]*Qkusr[j])*RU[j]/(Usr[Ku[j]]*Usr[Ku[j]]);// в ваттах
dQsr[j]=Qxx[j]*Usr[Ku[j]]*Usr[Ku[j]]/(Unom*Unom)+//расчет реак. потерь				
(Pkusr[j]*Pkusr[j]+Qkusr[j]*Qkusr[j])*XU[j]/(Usr[Ku[j]]*Usr[Ku[j]]);// в ваттах			 
Pkusr[VAO[j]]=Pkusr[VAO[j]]+Pkusr[j]+dPsr[j]/1000;//расчет акт. потока в конце участка
Qkusr[VAO[j]]=Qkusr[VAO[j]]+Qkusr[j]+dQsr[j]/1000;//расчет реакт. потока в конце участка
Pnusr[j]=Pkusr[j]+dPsr[j]/1000;//расчет акт. потока в начале участка
Qnusr[j]=Qkusr[j]+dQsr[j]/1000;//расчет реакт. потока в начале участка
}
//+++++++++++++++++++++++++++++++++++++++++++
//Обратный ход
//Расчет напряжения узлов
//+++++++++++++++++++++++++++++++++++++++++++
for(j=1;j<=NU;j++)
{dUsr[j]=(Pnusr[j]*RU[j]+Qnusr[j]*XU[j])*0.001/Usr[Nu[j]];//потери в киловольтах
Usr[Ku[j]]=Usr[Nu[j]]-dUsr[j];}
//+++++++++++++++++++++++++++++++++++++++++++
}//конец итерационного расчета средних мощностей
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Расчет потоков электроэнергии
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Объявление переменных
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double dWPxx[NU], dWQxx[NU], dWPn[NU], dWQn[NU];//потери энергии
double WPnu[NU], WQnu[NU];//акт. и реакт. энергия в начале участка
double KforP[NU],KforQ[NU];//Коэффициент формы графика нагрузки акт и реакт.
dWPxxSum=0; dWPnSum=0;

for(j=NU;j>0;j--)
{
KforP[j]=(0.16*T*Pku[j]/WPku[j]+0.84)*(0.16*T*Pku[j]/WPku[j]+0.84);
KforQ[j]=(0.16*T*Qku[j]/WQku[j]+0.84)*(0.16*T*Qku[j]/WQku[j]+0.84);
dWPxx[j]=T*Pxx[j]*Usr[Nu[j]]*Usr[Nu[j]]/(Unom*Unom);//Потери акт.хх в кВт*ч
dWQxx[j]=T*Qxx[j]*Usr[Nu[j]]*Usr[Nu[j]]/(Unom*Unom);//Потери реакт.хх в кВт*ч
dWPn[j]=(WPku[j]*WPku[j]+WQku[j]*WQku[j])*RU[j]*KforP[j]/
(Usr[Ku[j]]*Usr[Ku[j]]*T*1000);//Потери акт.нагрузочные в кВт*ч
dWQn[j]=(WPku[j]*WPku[j]+WQku[j]*WQku[j])*XU[j]*KforQ[j]/
(Usr[Ku[j]]*Usr[Ku[j]]*T*1000);	//Потери реакт.нагрузочные в кВт*ч
WPku[VAO[j]]=WPku[VAO[j]]+WPku[j]+dWPn[j]+dWPxx[j];//расчет акт. потока в конце участка
WQku[VAO[j]]=WQku[VAO[j]]+WQku[j]+dWQn[j]+dWQxx[j];//расчет реакт. потока в конце участка
WPnu[j]=WPku[j]+dWPn[j]+dWPxx[j];//расчет акт. потока в начале участка
WQnu[j]=WQku[j]+dWQn[j]+dWQxx[j];//расчет реакт. потока в начале участка
dWPxxSum=dWPxxSum+dWPxx[j];//Потери хх
dWPnSum=dWPnSum+dWPn[j];//Потери нагрузочные
}

/*for(k=1;k<=NU;k++)
{printf ( "%d %d %d VAO=%d SUST=%d \nRU=%f XU=%f PKU=%f PNU=%f dP=%f\n\n",k, 
Nu[k],Ku[k],VAO[k],Sust[k],RU[k],XU[k],Pku[k],Pnu[k], dP[k]/1000);}

/*for(k=1;k<=NU;k++)
{printf("%d Unu=%f dU=%f Uku=%f\n",k,U[Nu[k]],dU[k],U[Ku[k]]);}
printf("%d pogresh %f\n",i, e);

for(k=1;k<=NU;k++)
{printf ( "%d %d %d VAO=%d SUST=%d \nRU=%f XU=%f PKUsr=%f PNUsr=%f dPsr=%f\n\n",k, 
Nu[k],Ku[k],VAO[k],Sust[k],RU[k],XU[k],Pkusr[k],Pnusr[k], dPsr[k]/1000);}

for(k=1;k<=NU;k++)
{printf("%d Unusr=%f dUsr=%f Ukusr=%f\n",k,Usr[Nu[k]],dUsr[k],Usr[Ku[k]]);}

for(k=1;k<=NU;k++)
{printf("%d %f Wn=%f dW=%f dWk=%f\n",k, KforP[k],WPnu[k],dWPxx[k]+dWPn[k],WPku[k]);}
*/

return (dWPxxSum+dWPnSum);
}
