#include <graphics.h>
#include <stdio.h>
#include<stdlib.h>

int sort (int NU,int*Nu,int*Ku,char*type,int*Sust,float*length,
float*Kzagr,float*Cos,float*Tnb)
{
int i=1;
int j=1;
int a;
float b;
char c;

for(j=1;j<=NU;j++)
{
for(i=1;i<NU;i++)
{
if (Nu[i+1]<Nu[i])
{
a=Nu[i];
Nu[i]=Nu[i+1];
Nu[i+1]=a; 	
			
a=Ku[i];
Ku[i]=Ku[i+1];
Ku[i+1]=a; 		

c=type[i];
type[i]=type[i+1];
type[i+1]=c;

a=Sust[i];
Sust[i]=Sust[i+1];
Sust[i+1]=a; 	

b=length[i];
length[i]=length[i+1];
length[i+1]=b; 	   

b=Kzagr[i];
Kzagr[i]=Kzagr[i+1];
Kzagr[i+1]=b; 		

b=Cos[i];
Cos[i]=Cos[i+1];
Cos[i+1]=b;		   
			
b=Tnb[i];
Tnb[i]=Tnb[i+1];
Tnb[i+1]=b;}
}
}
return 0;
}
