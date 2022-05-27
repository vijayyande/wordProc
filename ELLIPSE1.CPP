#include <graphics.h>
#include <dos.h>
#include <math.h>

void swap(int *v1,int *v2)
{
    int temp;
    temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void points(int cx,int cy,int x,int y,int color,float asp_ratio,int i)
{
   int new_y;

   if(i)
      swap(&x,&y);
   new_y = (int)( y * asp_ratio + 0.5);

   putpixel( cx + x, cy + new_y, color);
   putpixel( cx + x, cy - new_y, color);
   putpixel( cx - x, cy + new_y, color);
   putpixel( cx - x, cy - new_y, color);
   delay(100);
return;
}


void _ellipse(int cx,int cy,int r1,int r2,int color)
{
 long int parameter,r1sq,r1sqx4,r2sqx2,limit;
 float asp_ratio;
 int x,y,i,switch_axes;

 getaspectratio(&x,&y);
 asp_ratio = (float) x / y;
 switch_axes = 0;

 if( r2 > r1)
 {
    switch_axes = !switch_axes;
    swap(&r1,&r2);
 }

 limit = (long int)((float)r1 * r1) / sqrt((float) r1 * r1 + (float) r2 * r2);

 for(i = 0 ; i < 2 ; i++)
 {
    r1sq = (long int)r1 * r1;
    r1sqx4 = r1sq << 2;
    r2sqx2 = ((long int) r2 *  r2) << 1;

    parameter = r2sqx2 + ( 1 - ( r2 << 1)) * r1sq;
    x = 0;
    y = r2;

    while( x < limit)
    {
       points(cx,cy,x,y,color,asp_ratio,switch_axes);

	 if( parameter >= 0)
	 {
	    --y;
	    parameter -= r1sqx4 * y;
	 }
	parameter += r2sqx2 * (3 + ( x << 1));
	++x;
    }
    points(cx,cy,x,y,color,asp_ratio,switch_axes);

    limit = y;
    switch_axes = ! switch_axes;
    swap( &r1,&r2);
   }
return;
}

void main()
{
  int a,b;
  detectgraph(&a,&b);
  initgraph(&a,&b,"\\turbo-c\\bgi");

   _ellipse(200,100,200,100,15);

}
