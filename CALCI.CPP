#include <stdlib.h>
#include <mem.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>

#define D delay(30);
#define BL write_string("                             ",6,25,0x70);\
		   write_string(no, 6, 25, 0x70);

void interrupt (*prv_9)(...);
void interrupt (*prv_8)(...);
void interrupt (*prv_28)(...);
void interrupt (*prv_15)(...);

void interrupt our_9(...);
void interrupt our_8(...);
void interrupt our_28(...);
void interrupt our_15(...);

void Box(int x1,int y1,int x2,int y2,int sd,int fc,int bc);
void write_char(char ch,int row,int col,int attb);
void write_string(char *str,int row,int col,int attr);
float Getno(char *);
void Perform();
void Calculator();

volatile char far *dosbusy;
volatile char far stack[4001];
unsigned want = 0,key,ss,sp,active = 0;
   int x,y;
   char screen[4002];
   char vijay[16] = {"UHI@X@-X@MCD"};

union REGS i,o;
struct SREGS s;

void Calculator()
{
   active = 1;
   want = 0;
   ss = _SS;
   sp = _SP;

    disable();
    _SS = FP_SEG (stack);
    _SP = FP_OFF( stack + 3998 );
    enable();

	sound(1000);delay(200);nosound();
	if( gettext(1,1,80,25,screen) != 1)
    {
	   printf("Unable to collect screen.");
	   abort();
    }
    x = wherex();
	y = wherey();

	window(20, 5, 60, 22);
	clrscr();
	window(1, 1, 80, 25);

	Box(20, 5, 60, 22, 3, 15, 0);
	Box(22, 6, 57, 8 , 1, 15, 0);
	Box(22, 9, 57, 19, 1, 15, 0);

	gotoxy(33,20);textcolor(15+128);textbackground(0);
	cprintf("%s", vijay);

	write_string("                             ",6,25,122);

	write_string(" 9 ", 10, 23, 0x0f);
	write_string(" 8 ", 10, 28, 0x0f);
	write_string(" 7 ", 10, 33, 0x0f);
	write_string(" 6 ", 12, 23, 0x0f);
	write_string(" 5 ", 12, 28, 0x0f);
	write_string(" 4 ", 12, 33, 0x0f);
	write_string(" 3 ", 14, 23, 0x0f);
	write_string(" 2 ", 14, 28, 0x0f);
	write_string(" 1 ", 14, 33, 0x0f);
	write_string(" 0 ", 16, 23, 0x0f);
	write_string(" . ", 16, 28, 0x0f);

	write_string(" + ", 11, 45, 0x0f);
	write_string(" - ", 11, 50, 0x0f);
	write_string(" * ", 13, 45, 0x0f);
	write_string(" / ", 13, 50, 0x0f);
	write_string(" = ",16, 47, 0x0e);

	gotoxy(x,y);
	Perform(); // call actual calculator

	want = 0;
	active = 0;

	if( puttext(1,1,80,25,screen) == 0)
	{
	   printf("unable to restore screen. ");
	   abort();
	}
	gotoxy(x,y);

	disable();
	_SS = ss;
	_SP = sp;
	enable();
	return;
}


void Box(int x1,int y1,int x2,int y2,int sd,int fc,int bc)
{
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
}

void write_char(char ch,int row,int col,int attb)
{
  char far *scr = (char far *) 0xB8000000L;
    *(scr + row * 160 + col * 2 ) = ch;
    *(scr + row * 160 + col * 2 + 1) = attb;
}

void write_string(char *str,int row,int col,int attr)
{
    while(*str)
    {
	write_char(*str,row,col,attr);
	str++;
	col++;
    }
}



void Perform()
{
     float first,second,result;
     char Res[50];
     char sign = 0;

   while( sign != 27)
   {

     write_string("                             ",6,25,122);
     first = Getno(&sign);
     if(sign == 27)
     {
		printf("\a");
		return;
     }

     second = Getno(&sign);

     switch(sign)
     {
	case '+':
	     result = first + second;
	     break;
	case '-':
	     result = first - second;
	     break;
	case '*':
	     result = first * second;
	     break;
	case '/':
	     if( second == 0 || first == 0)
		 result = 0;
	     else
		 result = first / second;
	     break;
	case 27:
	     printf("\a");
	     return ;

	default :
	     printf("\a");
	     break;
     }
	sprintf(Res, "%f",result);
	write_string(Res, 6, 25, 0x70);
	first = result;
	while(!kbhit());

   }

return;
}

float Getno(char *sign)
{

	 char no[120];
	 int i = 0,j;char ch1 = 1,ch2;
	 struct text_info ti;
	 gettextinfo(&ti);
	 int x = 26, y = 7;
	 textcolor(0);textbackground(15);
	 gotoxy(x,y);

	for( i = 0, j = 0 ; i < 120 && ch1 != '*' || ch1 != '/' || ch1 != '+' || ch1 != '-'; i++ )
	{

		ch1 = getch();
		switch(ch1)
		{
			case 0:
				ch2 = getch();
				switch(ch2)
				{

					 case 77:      //  ->
						  if( j >= i )
							  break;
						  else
						  {
							  j++;
							  gotoxy(x+j, y);
						  }
						  break;

					 case 75:    //   <-
						  if( j == 0 )
							  break;
						  else
						  {
							  j--;
							  gotoxy(x+j, y);
						  }
						  break;

					 case 83:  // Del
						  char mem[180];

						  if( j == i)
						  {
							  sound(500);delay(100);nosound();
							  break;
						  }
						  else
						  {
							   gettext(x+j+1, y, x+i+1, y, mem);
							   BL;
							   puttext(x+j  , y, x+i, y, mem);
							   memmove(no+j, no+j+1, i-j );
							   i--;
						  }
						  break;

				}
				break;

			//******************************
			case '0':
				if( j == i )
				{
					no[i] = '0';
					gotoxy(x+j, y);
					cprintf("0");
					j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '0';
				   j++;
				   cprintf("0");
				   gotoxy(x+j, y);
				}
				break;

			case '1':
				if( i == j )
				{
				   no[i] = '1';
				   gotoxy(x+j, y);
				   cprintf("1");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '1';
				   j++;
				   cprintf("1");
				   gotoxy(x+j, y);
				}
				break;

			case '2':
				if( i == j )
				{
				   no[i] = '2';
				   gotoxy(x+j, y);
				   cprintf("2");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '2';
				   j++;
				   cprintf("2");
				   gotoxy(x+j, y);
				}
				break;

			case '3':
				if( i == j )
				{
				   no[i] = '3';
				   gotoxy(x+j, y);
				   cprintf("3");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '3';
				   j++;
				   cprintf("3");
				   gotoxy(x+j, y);
				}
				break;

			case '4':
				if( i == j )
				{
				   no[i] = '4';
				   gotoxy(x+j, y);
				   cprintf("4");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '4';
				   j++;
				   cprintf("4");
				   gotoxy(x+j, y);
				}
				break;

			case '5':
				if( i == j )
				{
				   no[i] = '5';
				   gotoxy(x+j, y);
				   cprintf("5");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '5';
				   j++;
				   cprintf("5");
				   gotoxy(x+j, y);
				}
				break;

			case '6':
				if( i == j )
				{
				   no[i] = '6';
				   gotoxy(x+j, y);
				   cprintf("6");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '6';
				   j++;
				   cprintf("6");
				   gotoxy(x+j, y);
				}
				break;

			case '7':
				if( i == j )
				{
				   no[i] = '7';
				   gotoxy(x+j, y);
				   cprintf("7");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '7';
				   j++;
				   cprintf("7");
				   gotoxy(x+j, y);
				}
				break;

			case '8':
				if( i == j )
				{
				   no[i] = '8';
				   gotoxy(x+j, y);
				   cprintf("8");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '8';
				   j++;
				   cprintf("8");
				   gotoxy(x+j, y);
				}
				break;

			case '9':
				if( i == j )
				{
				   no[i] = '9';
				   gotoxy(x+j, y);
				   cprintf("9");
				   j++;
				}
				else
				{
				   char mem[200];
				   gettext(x+j  , y, x+31-1, y, mem);
				   BL;
				   puttext(x+j+1, y, x+31, y, mem);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '9';
				   j++;
				   cprintf("9");
				   gotoxy(x+j, y);
				}
				break;

			case 13:
				no[i] = 0;
				textattr(ti.attribute);
				return atof(no);

			case 8:
				char mem[180];
				  if( j == 0)
				  {
					  sound(500);delay(100);nosound();
					  break;
				  }
				  else
				  {
					   gettext(x+j  , y, x+i  , y, mem);
					   BL;
					   puttext(x+j-1, y, x+i-1, y, mem);
					   memmove(no+j-1, no+j, i-j+1 );
					   i--;
					   j--;
					   gotoxy(x+j, y);
				  }
				break;


		case '+':
			no[i] = 0;
			write_string(" +                           ",6,25,0x70);
			*sign = '+';
			textattr(ti.attribute);
			return atof(no);

		case '-':
			no[i] = 0;
			write_string(" -                           ",6,25,0x70);
			*sign = '-';
			textattr(ti.attribute);
			return atof(no);

		case '*':
			no[i] = 0;
			write_string(" *                           ",6,25,0x70);
			*sign = '*';
			textattr(ti.attribute);
			return atof(no);

		case '/':
			no[i] = 0;
			write_string(" /                           ",6,25,0x70);
			*sign = '/';
			textattr(ti.attribute);
			return atof(no);

		case 27:
			*sign = 27;
			textattr(ti.attribute);
			return 0;

		default :
		   sound(1000);delay(200);nosound();
		   break;
	   }
	}
   no[i] = 0;
   textattr(ti.attribute);
   return atof(no);
}

void interrupt our_9(...)
{
   key = inportb(0x60);

   if( active == 0 && key == 88 ) // F12 pressed
       want = 1;

   prv_9();
}

void interrupt our_8(...)
{
   prv_8();

   if( want == 1 && active == 0 && *dosbusy == 0)
       Calculator();
}

void interrupt our_28(...)
{
   prv_28();
   if(want == 1 && active == 0 && *dosbusy == 0)
	  Calculator();
}

void interrupt our_15(...)
{
   if( _AH == 0x4f )
   {
	   key = inportb(0x60);
	   if( active == 0 && key == 88 ) // F12 pressed
	   {
		   want = 1;
	   }
   }

  prv_15();
}

void main()
{
	  for(int t = 0 ; vijay[t] != 0 ; t++)
		vijay[t] += 1;

/*	 printf("\n\aA TSR Calculator by %s", vijay);
	 printf("\n\nPress F12 to activate Calculator.");
	 printf("\nEsc  to deactivate calculator.\n");

	 prv_8 = getvect(8);
	 setvect(8,our_8);

	 prv_9 = getvect(9);
	 setvect(9,our_9);

	 prv_28 = getvect(0x28);
	 setvect(0x28, our_28);

	 prv_15 = getvect(0x15);
	 setvect(0x15, our_15);

	 i.h.ah = 0x34;
	 intdosx(&i,&o,&s);
	 dosbusy = (char far*)MK_FP(s.es, o.x.bx);

	 keep(0, (_SS + (_SP/16) - _psp) + 100);

*/	 Calculator();
	 return;
}

