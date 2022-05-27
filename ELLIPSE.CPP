#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <iostream.h>
#include <conio.h>

#define PI 3.141592654
void dopoints(int,int);

void main()
{
    int a,b;
    detectgraph(&a,&b);
    initgraph(&a,&b,"c:\\turbo-c");

    InitGraph();
    float xn,yn,mj,mn,x1,y1;

    cout << "\n Enter X & Y Co-ordinates... ";
    cin >> xn >> yn >> mj >> mn;

    dopoints(x1,y1);

    cout << "\n This is ok";
    rectangle(xn,yn,xn,yn);
    setviewport(xn,yn,xn + 1 ,yn + 1,0);

   // mj = xn;
   // mn = yn;

    for(float i = 0 ; i <= 360 ; i+= .1)
     {
	x1 = mj * cos( i * PI / 180) + yn * sin( i * PI / 180);
        y1 = mn * cos( i * PI / 180) - xn * sin( i * PI / 180);

        x1 += xn;
        y1 += yn;

//	putpixel(x1,y1,15);
	dopoints(x1,y1);
    }

    getch();
}



void dopoints(int xx,int yy)
{

   char pts[21];
   int x[21],y[21],i = 0;
   int x1,y1;

   for( i = 0 ; i <= 20 ; i++)
   {

	x1 = random(20);
	y1 = random(20);

	pts[i] = getpixel( xx + x1, yy + y1 );

	   x[i] = x1;
	   y[i] = y1;

	putpixel( xx + x1, yy + y1, 15);
//	delay(20);
   }
   for( int j = 20 ; j >= 0 ; j--)
   {
	   putpixel(xx + x[j], yy + y[j], pts[j] );
   }

}

