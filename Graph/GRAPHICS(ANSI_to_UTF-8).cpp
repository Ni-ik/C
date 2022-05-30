#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#undef   abs
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

//Функция позволяет выводить значения пеерменных
void outtextxyNUM(int x, int y, float var) {
   char buf[20];
   snprintf(buf, sizeof(buf), "%5.1f", var);
   outtextxy(x, y, buf);}
void outtextxyNUM2(int x, int y, float var) {
   char buf[20];
   snprintf(buf, sizeof(buf), "%5.2f", var);
   outtextxy(x, y, buf);}
void outtextxy(int x, int y, float var) {
   char buf[20];
   snprintf(buf, sizeof(buf), "%f", var);
   outtextxy(x, y, buf);}
   
//Функция рисования графиков
void DrawFunction (int color, int type, int fat, double*Y, 
double stepy, double step, double MaxF, int param)
{setlinestyle(type, 1, fat);                      
setcolor(color);
int i;
for(i=param ;i<199;i++)
{delay(10);//задержка анимации
if(Y[i]<MaxF)
{moveto(50+i*400/100,550-Y[i]*stepy/step);
lineto(50+(i+1)*400/100,550-Y[i+1]*stepy/step);}}}


//Основная функця
int main()
{
int Wx=900; int Wy=650; int i; double Ox=0; double MaxCp=0, MinCp=999, MinX,
log, step, a, param=1;
float stepy;
//для вычисления функции

double Y[200];
float U, Sn, Tnb, T, Rl, Rt, cosf, Pxx, Kt, Kl, Pt, Pl, Bx, Bn;
float dW, dWx, dWl, dWt;
char s[80];

//Чтение информации
FILE*input;
input=fopen("input.txt","rt");
if ( input == NULL )
{printf("CAN'T FIND ANY INPUT FILE\n");}//проверка на чтение

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &U);//printf("U=%.3f kV\n",U);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Sn);//printf("Sn=%.3f kVA\n",Sn);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Tnb);//printf("Tnb=%.3f h\n",Tnb);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &T);//printf("T=%.3f h\n",T);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Rl);//printf("Rek=%.3f Ohm\n",Rek);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Rt);//printf("Rek=%.3f Ohm\n",Rek);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &cosf);//printf("cosf=%.3f \n",cosf);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Pxx);//printf("dPxx=%.3f kVt\n",Pxx);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Kt);//printf("Kt=%.3f y.g.e.\n",Kt);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Kl);//printf("Kl=%.3f y.g.e. \n",Kl);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Pt);//printf("Pt=%.3f \n",Pt);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Pl);//printf("Pl=%.3f \n",Pl);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Bx);//printf("bxx=%.3f y.g.e./kVt*h\n",Bx);

fgets ( s, 80, input );fgets ( s, 80, input );
fscanf( input, "%f", &Bn);//printf("bn=%.3f y.g.e./kVt*h\n",Bn);

fclose (input); 

double kFor=(0.34*T/Tnb+0.66);//определяем коэффициент формы
double A=(Pl*Kl+Pt*Kt)/(Sn*Tnb*cosf);
double B=(Pxx*Bx*T)/(Sn*Tnb*cosf);
double C=Sn*Sn*Tnb*Tnb*kFor*(Rl+Rt)*Bn/(T*Sn*Tnb*cosf*U*U);
double FA[200], FB[200], FC[200];

//находим массив значения функции
for(i=1;i<=200;i++)
{Y[i]=A/(0.01*i)+B/(0.01*i)+C*(0.01*0.01*i*i)/(0.01*i*1000);
FA[i]=A/(0.01*i);
FB[i]=B/(0.01*i);
FC[i]=C*(0.01*0.01*i*i)/(0.01*i*1000);
if(MinCp>=Y[i]){MinCp=Y[i];MinX=i;}}//Находим минимальное значение
MaxCp=Y[200];//максимальнам принимаем крайнее правое (посмотреть массивы)

//создаем окно
initwindow(Wx,Wy);
setcolor(YELLOW);//установим цвет текста
outtextxy(300,10,"Программа GRAPH");
setcolor(WHITE);//установим цвет текста
outtextxy(10,30,"Проверьте правильность исходных данных!!!");
outtextxy(10,70,"Номинальное напряжение сети ( Uном ), кВ");
outtextxy(10,90,"Суммарная установленная мощность трансформаторов ( Sном ), КВА");
outtextxy(10,110,"Время использования наибольшей нагрузки ( Tнаиб ), ч");
outtextxy(10,130,"Время расчета ( T ),ч");
outtextxy(10,150,"Эквивалентное активное сопротивление линий ( Rл ), Ом");
outtextxy(10,170,"Эквивалентное активное сопротивление трансформаторов ( Rт ), Ом");
outtextxy(10,190,"Коэффициент мощности ( cosf )");
outtextxy(10,210,"Потери мощности холостого хода ( dPxx ), кВА");
outtextxy(10,230,"Капитальные затраты на трансформаторы ( Kт ), у.д.е.");
outtextxy(10,250,"Капитальные затраты на линии ( Kл ), у.д.е.");
outtextxy(10,270,"Коэффициент отчислений от стоимости трансформаторов ( Pт ), у.д.е.");
outtextxy(10,290,"Коэффициент отчислений от стоимости линий ( Pл ), у.д.е.");
outtextxy(10,310,"Стоимость потерь холостого хода ( Bхх ), у.д.е./кВт*ч");
outtextxy(10,330,"Стоимость нагрузочных потерь ( Bнагр ), у.д.е./кВт*ч");
outtextxy(10,370,"Формула для определения оптимального коэффициента загрузки");
outtextxy(10,390,"по критерию минимума стоимости передачи ЭЭ:");

readimagefile("form/koef.bmp",10,410,253,461 );
readimagefile("form/POT.bmp",10,470,351,561 );
outtextxy(10,570,"Для продолжения работы нажмите любую клавишу");
outtextxy(10,600,"Для выхода из программы нажмите ESC");

setcolor(RED);//установим цвет текста
outtextxy(500,70,U);
outtextxy(500,90,Sn);
outtextxy(500,110,Tnb);
outtextxy(500,130,T);
outtextxy(500,150,Rl);
outtextxy(500,170,Rt);
outtextxy(500,190,cosf);
outtextxy(500,210,Pxx);
outtextxy(500,230,Kt);
outtextxy(500,250,Kl);
outtextxy(500,270,Pt); 
outtextxy(500,290,Pl);
outtextxy(500,310,Bx);
outtextxy(500,330,Bn);

int x=50, y=Wy-100;

int buttom;
buttom=getch();//считываем кнопки
if (buttom!=27)
{
/***********************************************/

/*******************************/


cleardevice( );//третий этап 
setlinestyle(1, 1, 1); 
setcolor(GREEN);
settextstyle(3, HORIZ_DIR, 1); //HORIZ_DIR - вывод текста слева-направо

double dWx=(Pxx*T)/(Sn*Tnb*cosf);
double dWn=Sn*Sn*Tnb*Tnb*kFor*(Rl+Rt)/(T*Sn*Tnb*cosf*U*U);
double dW[200], MindW=100, MaxdW=0;
double MinKdW=0;
int KdW;

//находим массив значения функции
for(i=4;i<200;i++)
{dW[i]=dWx/(0.0001*i)+dWn*(0.01*0.01*i*i)/(0.0001*i*1000);
if(MindW>=dW[i]){MindW=dW[i];MinKdW=i; KdW=i;}//Находим минимальное значение
if(MaxdW<=dW[i]){MaxdW=dW[i];}}//Находим минимальное значение

//определяем автомасштаб оси oy
log=floor(log10(MaxdW)); //логарифм округляем до меньшего
step=pow(10,log);//находим шаг построения сетки в нат. единицах
a=ceil(MaxdW/pow(10,log));//определяем количество делений
stepy=500/a; //определяем шаг построения в пикселях
 
 //Рисуем сетку OX
Ox=0;
for (x=50;x<=Wx-50;x=x+40,Ox=Ox+0.1)
{line(x,y+4,x,50);
outtextxyNUM(x-18,Wy-90,Ox);};
x=50, y=Wy-100;

//Рисуем сетку OY
for (i=1;i<=a;i++)
{line(x-4,550-(stepy*i),Wx-50,550-(stepy*i));
outtextxyNUM(x-40,543-(stepy*i),i);};   
setcolor(WHITE);
settextstyle(3, HORIZ_DIR, 2); //HORIZ_DIR - вывод текста слева-направо
outtextxy(175,20, "Зависимость относительных потерь ЭЭ от коэффициента загрузки сети");  
settextstyle(3, HORIZ_DIR, 1); //HORIZ_DIR - вывод текста слева-направо

//Рисуем оси          
setlinestyle(0, 1, 3);                      
setcolor(RED);
line(50,50,50,Wy-100); 
line(50,Wy-100,Wx-50,Wy-100);
outtextxy (Wx-70,Wy-120, "Kз, o.e.");
outtextxy(10,20, "dW,%*10");  
outtextxyNUM(75,15, log); 
  

DrawFunction (3, 0, 3, dW, stepy, step, MaxdW,5);

//рисуем линии минимума
setlinestyle(1, 1, 1);                      
setcolor(YELLOW);
line(x-4,550-MindW*stepy/step,50+MinKdW*400/100,550-MindW*stepy/step);
line(50+MinKdW*400/100,550-MindW*stepy/step,50+MinKdW*400/100,y+8);

//Выводим результаты расчета 
outtextxy(50,y+35,"MindW=");
outtextxy(115,y+35, MindW); //минимальная себестоимость
outtextxy(185,y+35,"%");
outtextxy(50,y+70,"Kз =");//коэффициент заполнения при минимальной себестоимости
outtextxy(115,y+70, MinKdW/100); 
readimagefile("form/kmp.bmp",347,587,468,639 );
setcolor(3);
float Kzy;
Kzy=sqrt(dWx*1000/dWn);
outtextxy(250,y+50, "По формуле"); 
outtextxy(470,y+50, Kzy); 

getch();             // ждать нажатия на любую клавишу



/*************************************/



cleardevice( );
//bar(0,0,Wx,Wy)

setlinestyle(1, 1, 1); 
setcolor(GREEN);

//Рисуем сетку OX
Ox=0;
for (x=50;x<=Wx-50;x=x+40,Ox=Ox+0.1)
{line(x,y+4,x,50);
outtextxyNUM(x-18,Wy-90,Ox);};
x=50, y=Wy-100;

//определяем автомасштаб оси oy
log=floor(log10(MaxCp)); //логарифм округляем до меньшего
step=pow(10,log);//находим шаг построения сетки в нат. единицах
a=ceil(MaxCp/pow(10,log));//определяем количество делений
stepy=500/a; //определяем шаг построения в пикселях
  
//Рисуем сетку OY
for (i=1;i<=a;i++)
{line(x-4,550-(stepy*i),Wx-50,550-(stepy*i));
outtextxyNUM(x-40,543-(stepy*i),i);};   

//Рисуем оси          
setlinestyle(0, 1, 3);                      
setcolor(RED);
line(50,50,50,Wy-100); 
line(50,Wy-100,Wx-50,Wy-100);
outtextxy (Wx-70,Wy-120, "Kз, o.e.");
outtextxy(10,20, "C, y.g.e. *10^");  
outtextxyNUM(94,20, log); 
setcolor(WHITE);
settextstyle(3, HORIZ_DIR, 2); //HORIZ_DIR - вывод текста слева-направо
outtextxy(200,20, "Зависимость стоимости передачи ЭЭ от коэффициента загрузки сети");  
settextstyle(3, HORIZ_DIR, 1); //HORIZ_DIR - вывод текста слева-направо

//Рисуем график
DrawFunction (2, 0, 3, FA, stepy, step, MaxCp,1);
DrawFunction (5, 0, 3, FB, stepy, step, MaxCp,1);
DrawFunction (15, 0, 3, FC, stepy, step, MaxCp,1);
DrawFunction (1, 0, 3, Y, stepy, step, MaxCp,1);

//рисуем линии минимума
setlinestyle(1, 1, 1);                      
setcolor(YELLOW);
line(x-4,550-MinCp*stepy/step,50+MinX*400/100,550-MinCp*stepy/step);
line(50+MinX*400/100,550-MinCp*stepy/step,50+MinX*400/100,y+8);


//Выводим результаты расчета 
outtextxy(50,y+35,"MinCp=");
outtextxy(100,y+35, MinCp); //минимальная себестоимость
outtextxy(175,y+35,"у.д.е.");
outtextxy(50,y+70,"Kз =");//коэффициент заполнения при минимальной себестоимости
outtextxy(100,y+70, MinX/100); 
//outtextxy(175,y+70, "o.e.");

readimagefile("form/form.bmp",220,580,803,617 );
setcolor(RED);
float Kz;
Kz=sqrt((A+B)*1000/C);
outtextxy(230,y+70, "По формуле Kз="); 
outtextxy(355,y+70, Kz); 
/**********/
getch();             // ждать нажатия на любую клавишу


setfillstyle(1,BLACK);
bar(0,580,900,650);

//рисуем линии минимума по потерям
setlinestyle(1, 1, 1);                      
setcolor(3);
line(x-4,550-Y[KdW]*stepy/step,50+KdW*400/100,550-Y[KdW]*stepy/step);
line(50+KdW*400/100,550-Y[KdW]*stepy/step,50+KdW*400/100,y+8);

setcolor(3);
outtextxy(50,y+40, "По критерию минимальных относительных потерь ЭЭ, Кз =");
outtextxy(500,y+40,Kzy);
setcolor(YELLOW);
outtextxy(50,y+70, "По критерию минимальной стоимости передачи ЭЭ,     Кз =");
outtextxy(500,y+70,Kz);

getch();             // ждать нажатия на любую клавишу
//********************добавление от 12 ноября 2013
m:
setcolor (YELLOW);
cleardevice( );
readimagefile("form/t.jpg",40,40,809,102 );
setlinestyle(0, 1, 1); 
settextstyle(3, HORIZ_DIR, 2); //HORIZ_DIR - вывод текста слева-направо
outtextxy(300,8, "Таблица результатов расчёта");
settextstyle(3, HORIZ_DIR, 1); //HORIZ_DIR - вывод текста слева-направо

for(i=0;i<20;i++){
dWx=Pxx*T;                  
dWl=Sn*Sn*Tnb*Tnb*kFor*Rl*((i+1)*0.1)*((i+1)*0.1)/(T*U*U*1000);  
dWt=Sn*Sn*Tnb*Tnb*kFor*Rt*((i+1)*0.1)*((i+1)*0.1)/(T*U*U*1000);                          
outtextxyNUM(45,102+i*22,(i*0.1+0.1));    
outtextxyNUM2(90,102+i*22, Sn*Tnb*cosf*((i+1)*0.1));               
outtextxyNUM2(370,102+i*22, dWx);
outtextxyNUM2(465,102+i*22, Pxx*T*100/(Sn*Tnb*cosf*((i+1)*0.1)));
outtextxyNUM2(520,102+i*22, dWl);
outtextxyNUM2(610,102+i*22, Sn*Sn*Tnb*Tnb*kFor*Rl*((i+1)*0.1)*((i+1)*0.1)*100/(Sn*Tnb*cosf*((i+1)*0.1)*T*U*U*1000));
outtextxyNUM2(667,102+i*22, dWt);
outtextxyNUM2(757,102+i*22, Sn*Sn*Tnb*Tnb*kFor*Rt*((i+1)*0.1)*((i+1)*0.1)*100/(Sn*Tnb*cosf*((i+1)*0.1)*cosf*T*U*U*1000));
outtextxyNUM2(220,102+i*22, dWx+dWl+dWt);
outtextxyNUM2(310,102+i*22, (dWx+dWl+dWt)*100/(Sn*Tnb*cosf*((i+1)*0.1)));
line (45,101+(i+1)*22, 803, 101+(i+1)*22);
} 
line (44,90,44,541);
line (85,90,85,541);
line (214,90,214,541);
line (305,90,305,541);
line (364,90,364,541);
line (462,90,462,541);
line (512,90,512,541);
line (608,90,608,541);
line (659,90,659,541);
line (754,90,754,541);
line (804,90,804,541);
setcolor(WHITE);
outtextxy(10,620, "Для продолжения нажмите любую клавишу"); 
getch();             // ждать нажатия на любую клавишу
//********************добавление от 17 ноября 2013
cleardevice( );
setcolor (YELLOW);
setlinestyle(0, 1, 1); 
settextstyle(3, HORIZ_DIR, 2); //HORIZ_DIR - вывод текста слева-направо
outtextxy(300,8, "Таблица результатов расчёта");
readimagefile("form/t.jpg",40,40,809,102 );
bar (214,46,800,96);
settextstyle(3, HORIZ_DIR, 1); //HORIZ_DIR - вывод текста слева-направо
readimagefile("form/form.bmp",221,52,804,88 );

for(i=0;i<20;i++){
outtextxyNUM(45,102+i*22,(i*0.1+0.1));   
outtextxyNUM2(90,102+i*22, Sn*Tnb*cosf*((i+1)*0.1));    
outtextxy(220,102+i*22, A/((i+1)*0.1));  
outtextxy(400,102+i*22, B/((i+1)*0.1));  
outtextxy(550,102+i*22, C*(0.1*0.1*(i+1)*(i+1))/(0.1*(i+1)*1000));
outtextxy(675,102+i*22, (C*(0.1*0.1*(i+1)*(i+1))/(0.1*(i+1)*1000))+(A/((i+1)*0.1))+(B/((i+1)*0.1)));
line (45,101+(i+1)*22, 803, 101+(i+1)*22);
} 
//********************добавление от 25 ноября 2013
line (44,46,44,541);
line (85,46,85,541);
line (214,46,214,541);
line (395,46,395,541);
line (545,46,545,541);
line (670,46,670,541);
line (804,46,804,541);

setcolor (WHITE);
outtextxy(10,600, "Для возврата на предыдущий экран нажмите ENTER"); 
outtextxy(10,620, "Для выхода нажмите ESC"); 


buttom=getch();//считываем кнопки
if (buttom!=27){
goto m;}
}
closegraph();        // закрыть окно с графикой
return 0;
}


