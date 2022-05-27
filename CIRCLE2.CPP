#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <mouse.h>

void dopixel(int,int);


void Circle(int h,int k,int r);
void StartCircle();
void PrintCircle(int h,int k,int r);
void RestoreCircle();
//void pts(int &x,int &y,int h,int k);


int xx[2000],yy[2000],c[2000],i=0,mx1,my1,mx2,my2;

void main()
{
   int i,gm,gd,d;
   unsigned h,k,r,y,x;
   float t;

   detectgraph(&gd,&gm);
   initgraph(&gd,&gm,"\\turbo-c\\bgi");
   ShowMouse();

   for( i = 0 ; i < 2000 ; i++)
   {
      xx[i] = 0;
      yy[i] = 0;
      c[i]  = 0;
   }
   i = 0;

   settextstyle(10,0,5);
   outtextxy(10,100,"Vijay");

   StartCircle();
   getchar();
   return;
}

void StartCircle()
{
  int r;
  int mx3,my3;

/*  while( !Clicked(0, 0, 639, 479));
	  mx1 = GetMX(); my1 = GetMY();

  i = 0;
  delay(100);
  while(  Clicked(0, 0, 639, 479))
  {
      mx2 = GetMX();
      my2 = GetMY();

	 r = abs(mx2-mx1) > abs(my2-my1) ?  mx2-mx1 : my2-my1;

       if(mx2 != mx3 || my2 != my3 )
       {
	  RestoreCircle();
	  PrintCircle(mx1,my1,r);
       }

      mx3 = mx2;
      my3 = my2;

  }     */

  PrintCircle( 100,100,100);

}


void PrintCircle(int h,int k ,int r)
{
   int x,y,d;
   x = 1;
   y = r;
   d = 3-2*r;
do{

c[i] = getpixel( x+h, y+k);    dopixel( x+h, y+k); xx[i] = x+h;  yy[i] =  y+k;i++;
c[i] = getpixel(-x+h,-y+k);    dopixel(-x+h,-y+k); xx[i] =-x+h;  yy[i] = -y+k;i++;
c[i] = getpixel( y+h, x+k);    dopixel( y+h, x+k); xx[i] = y+h;  yy[i] =  x+k;i++;
c[i] = getpixel(-y+h,-x+k);    dopixel(-y+h,-x+k); xx[i] =-y+h;  yy[i] = -x+k;i++;

c[i] = getpixel(-y+h, x+k);    dopixel(-y+h, x+k); xx[i] =-y+h;  yy[i] =  x+k;i++;
c[i] = getpixel( y+h,-x+k);    dopixel( y+h,-x+k); xx[i] = y+h;  yy[i] = -x+k;i++;
c[i] = getpixel(-x+h, y+k);    dopixel(-x+h, y+k); xx[i] =-x+h;  yy[i] =  y+k;i++;
c[i] = getpixel( x+h,-y+k);    dopixel( x+h,-y+k); xx[i] = x+h;  yy[i] = -y+k;i++;




      if( d < 0)
	  d += 4 * x + 6;
      else
      {
	  d += 4 * (x -y )+10;
	  y--;
      }
      x++;

}while( x < y);
return;
}

void RestoreCircle()
{
   disable();
   for(int j = 0 ; j <= i ; j++)
   {
       putpixel(xx[j],yy[j],c[j]);
       if( i > 1950)
	{
	   perror("End of allocated memory. ");
	   return;
	}
   }
 i = 0;
 enable();
 return;
}

void dopixel(int xx,int yy)
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
	delay(10);
   }
   for( int j = 0 ; j <= 20 ; j++)
   {
	   putpixel(xx + x[j], yy + y[j], pts[j] );
   }



/*	 p1 = getpixel(x   , y   );
	 p2 = getpixel(x+1 , y+1 );
	 p3 = getpixel(x   , y+1 );
	 p4 = getpixel(x+1 , y   );

	 putpixel(x   , y  , 15);
	 putpixel(x+1 , y+1, 15);
	 putpixel(x   , y+1, 15);
	 putpixel(x+1 , y  , 15);
	 delay(20);

	 ////////////////////
	 a1 = getpixel(x + 10  , y   );
	 a2 = getpixel(x+1+10 , y+1 );
	 a3 = getpixel(x +10  , y+1 );
	 a4 = getpixel(x+1+10 , y   );

	 putpixel(x +10  , y  , 15);
	 putpixel(x+1+10 , y+1, 15);
	 putpixel(x +10 , y+1, 15);
	 putpixel(x+1+10 , y  , 15);
	 delay(20);

	 //////////////////////
	 b1 = getpixel(x   , y +10  );
	 b2 = getpixel(x+1 , y+1+10 );
	 b3 = getpixel(x   , y+1+10 );
	 b4 = getpixel(x+1 , y +10  );

	 putpixel(x   , y +10 , 15);
	 putpixel(x+1 , y+1+10, 15);
	 putpixel(x   , y+1+10, 15);
	 putpixel(x+1 , y  +10, 15);
	 delay(20);

	 ////////////////////////
	 c1 = getpixel(x +10  , y +10  );
	 c2 = getpixel(x+1+10 , y+1+10 );
	 c3 = getpixel(x +10  , y+1+10 );
	 c4 = getpixel(x+1+10 , y +10  );

	 putpixel(x +10  , y +10 , 15);
	 putpixel(x+1+10 , y+1+10, 15);
	 putpixel(x +10  , y+1+10, 15);
	 putpixel(x+1+10 , y +10 , 15);
	 delay(20);


//////////////////////////////////////////////////////////
	 putpixel(x   , y  , p1);
	 putpixel(x+1 , y+1, p2);
	 putpixel(x   , y+1, p3);
	 putpixel(x+1 , y  , p4);
	 delay(20);

	 putpixel(x +10  , y  , a1);
	 putpixel(x+1+10 , y+1, a2);
	 putpixel(x  +10 , y+1, a3);
	 putpixel(x+1+10 , y  , a4);
	 delay(20);

	 putpixel(x   , y +10 , b1);
	 putpixel(x+1 , y+1+10, b2);
	 putpixel(x   , y+1+10, b3);
	 putpixel(x+1 , y +10 , b4);
	 delay(20);

	 putpixel(x +10  , y +10 , c1);
	 putpixel(x+1+10 , y+1+10, c2);
	 putpixel(x  +10 , y+1+10, c3);
	 putpixel(x+1+10 , y +10 , c4);
	 delay(20);
*/
}

