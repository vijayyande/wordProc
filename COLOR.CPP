#include <graphics.h>
#include <conio.h>

void main()
{
   InitGraph();

   for( int i = 0 , j = 0;   i < 400  && j < 16  ; i++, j++)
   {
	  setfillstyle(1,j);
	  bar(0, i * 20, 200, i * 20 + 30 );
   }
   getch();
}