#include <graphics.h>
#include <stdio.h>
#include <mouse.h>
#include <math.h>
#include <conio.h>
#include <dos.h>

class CIRCLE
{

    private :
	unsigned h,k,r,y,x;
	float t;
	int xx[2000],yy[2000],c[2000],i,mx1,my1,mx2,my2;

    public :
       CIRCLE(){ i = 0;}

       void far StartCircle();
       void far PrintCircle(int ,int,int);
       void far RestoreCircle();

};




void far CIRCLE::StartCircle()
{
  int r;
  int mx3,my3;

  while( !Clicked(0, 0, 639, 479));
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

  }
}


void far CIRCLE::PrintCircle(int h,int k ,int r)
{
   int x,y,d;
   x = 1;
   y = r;
   d = 3-2*r;
do{

c[i] = getpixel( x+h, y+k);    putpixel( x+h, y+k,15); xx[i] = x+h;  yy[i] =  y+k;i++;
c[i] = getpixel(-x+h,-y+k);    putpixel(-x+h,-y+k,15); xx[i] =-x+h;  yy[i] = -y+k;i++;
c[i] = getpixel( y+h, x+k);    putpixel( y+h, x+k,15); xx[i] = y+h;  yy[i] =  x+k;i++;
c[i] = getpixel(-y+h,-x+k);    putpixel(-y+h,-x+k,15); xx[i] =-y+h;  yy[i] = -x+k;i++;

c[i] = getpixel(-y+h, x+k);    putpixel(-y+h, x+k,15); xx[i] =-y+h;  yy[i] =  x+k;i++;
c[i] = getpixel( y+h,-x+k);    putpixel( y+h,-x+k,15); xx[i] = y+h;  yy[i] = -x+k;i++;
c[i] = getpixel(-x+h, y+k);    putpixel(-x+h, y+k,15); xx[i] =-x+h;  yy[i] =  y+k;i++;
c[i] = getpixel( x+h,-y+k);    putpixel( x+h,-y+k,15); xx[i] = x+h;  yy[i] = -y+k;i++;

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

void far CIRCLE::RestoreCircle()
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





void main()
{
   CIRCLE cir;

   InitGraph();
   ShowMouse();
   cir.StartCircle();
}