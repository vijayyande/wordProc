#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <alloc.h>
#define color(fc,bc)     textcolor(fc);textbackground(bc);

void far write_char  (char  character, int row, int coloumn, int attribute);
void far write_string(char *character, int row, int coloumn, int attribute);
void far Box(int x1,  int y1,  int x2,  int y2,  int sd,  int fc,  int bc);

class PushButton
{
   private :
       char items[][10];
       int no_of_items;
       int x,y;
       int fc,bc;
       int direction;

   public :
      PushButton();
      void far set_char(char items[][10], int no_of_items, int dir, int x, int y, int fore_color, int back_color);
      void far say();



};///          End of Class PushButton

PushButton::PushButton()// Constructor
{
   return;
}

void far write_char(char ch,int row,int col,int attb)
{
  char far *scr = (char far *) 0xB8000000L;
    *(scr + row * 160 + col * 2 ) = ch;
    *(scr + row * 160 + col * 2 + 1) = attb;
}

void far write_string(char *str,int row,int col,int attr)
{
    while(*str)
    {
        write_char(*str,row,col,attr);
        str++;
        col++;
    }
}

void far Box(int x1,int y1,int x2,int y2,int sd,int fc,int bc)
{
   if( x1 > x2 )
   {
       int temps;
       temps = x1;
       x1 = x2;
       x2 = temps;
   }
   if( y1 > y2 )
   {
       int tempss;
       tempss = y1;
       y1 = y2;
       y2 = tempss;
   }

     text_info ti;
     int i,t;
     gettextinfo(&ti);
     window(1,1,80,25);
     textcolor(fc);textbackground(bc);
     t = _wscroll;
     _wscroll = 0;
     x1 = x1 < 1  ? 1  : x1;
     x2 = x2 > 80 ? 80 : x2;
     y1 = y1 < 1  ? 1  : y1;
     y2 = y2 > 25 ? 25 : y2;

  if(sd == 3)
  {
     gotoxy(x1,y1);
     cprintf("Û");
     for(int i = 1 ; wherex() != x2 ; i++)
     {
	 gotoxy(x1+i,y1);
	 cprintf("ß");
     }
     cprintf("Û");
     gotoxy(x1,y2-1);
     cprintf("Û");
     for( i = 0 ;  wherex() != x2 ; i++)
     {
	 gotoxy(x1+i,y2);
	 cprintf("ß");
     }
     gotoxy(x2,y2-1);
     cprintf("Û");gotoxy(1,1);

     for(i = 1 ; wherey() != y2 - 1 ; i++)
     {
	 gotoxy(x1,y1+i);
	 cprintf("Û");

	 gotoxy(x2,y1+i);
	 cprintf("Û");
     }
     gotoxy(x2,y2);
     cprintf("ß");

  }
  else
  {

     for(i = 0 ; wherex() != x2 ; i++)
     {
	   gotoxy(x1+i,y1);
	   cprintf("%c", sd == 1 ? 196 : 205);

	   gotoxy(x1+i,y2);
	   cprintf("%c", sd == 1 ? 196 : 205);
     }
     gotoxy(1,1);
     for( i = 0 ; wherey() != y2 ; i++)
     {
	 gotoxy (x1,y1+i);
	 cprintf("%c", sd == 1 ? 179 : 186);

	 gotoxy (x2,y1+i);
	 cprintf("%c", sd == 1 ? 179 : 186);
     }
     gotoxy(x1,y1);
     cprintf("%c",sd == 1 ? 218 : 201);
     gotoxy(x1,y2);
     cprintf("%c",sd == 1 ? 192 : 200);

     gotoxy(x2,y1);
     cprintf("%c", sd == 1 ? 191 : 187);
     gotoxy(x2,y2);
     cprintf("%c", sd == 1 ? 217 : 188);
  }
  gotoxy(1,1);
     window(ti.winleft,ti.wintop,ti.winright,ti.winbottom);
     textattr(ti.attribute);gotoxy(ti.curx,ti.cury);
     _wscroll = t;
 return;
}////       End of Box


void main()
{
     clrscr();
     Box( 1, 25, 45, 2, 2, 15, 0);
     char test[][10] = {
			 { "vijay" },
			 { "ajay "},
			 { "parag"},
			 { "mujju"}
		       };
    PushButton pb;
    pb.set_char(test, 4, 1, 10,10, 0, 15);
    pb.say();
    getch();

}

void far PushButton::set_char(char item[][10], int no_of_item, int dir, int xx, int yy, int fore_color, int back_color)
{
   for(int i = 0 ; i < no_of_items ; i++)
   for(int j = 0 ; j < 10 ; j++)
      items[i][j] = item[i][j];

      no_of_items = no_of_item ;
      x = xx;
      y = yy;
      direction = dir;
      fc = fore_color;
      bc = back_color;
}

void far PushButton::say ()
{
  for(int i = 0 ; i < no_of_items ; i++)
  {

	gotoxy(x+(i*10), y);
	color(fc,bc);
	cprintf("<%s>",items[i]);
  }
}
