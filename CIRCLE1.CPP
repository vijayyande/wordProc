#include <stdio.h>
#include <graphics.h>
#include <conio.h>

void main()
{

    clrscr();
    int i,d;
    unsigned h,k,r,y,x;
    float t;

    printf ("Enter Radious, X & Y ¯ ");
    scanf("%d%d%d",&r,&h,&k);

    InitGraph();
    x = 0;
    y = r;
    d = 3-2*r;

    do
    {
      putpixel(x + h,  y + k,15);
      putpixel(x + h,  y - k,15);
      putpixel(x - h,  y + k,15);
      putpixel(x - h,  y - k,15);

      if( d < 0)
	  d += x + 6;
	else
	   {
	      d+=4*(x-y)+10;
	      y--;
	   }
	   x++;
      }while( x <= y);
      getch();
return;
}

