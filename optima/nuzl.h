#include <graphics.h>
#include <stdio.h>
#include<stdlib.h>

int NUZ(int*Ku, int NU)
{
int i=1,NUZ=Ku[i];
for(i=1;i<=NU;i++)
{if(Ku[i]>NUZ)
{NUZ=Ku[i];}
}
return NUZ;
}
