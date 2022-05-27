#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define D delay(30);

void interrupt (*prv_9)(...);
void interrupt (*prv_8)(...);
void interrupt (*prv_28)(...);

void interrupt our_9(...);
void interrupt our_8(...);
void interrupt our_28(...);

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

    if( gettext(1,1,80,25,screen) != 1)
    {
	printf("Unable to collect screen.");
	abort();
    }
    x = wherex();
    y = wherey();


    clrscr();
    Box(20, 5, 60, 22, 3, 15, 0);
    Box(22, 9, 38, 19, 1, 8,  9);
    Box(43, 10,54, 18, 1, 8,  9);

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

     char input = 9,no1[30];
     int i = 0;

     while(input != '*' || input != '/' || input != '+' || input != '-')
     {

	input = getch();

	switch(input)
	{

	    case '0':
		no1[i] = '0';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);

		write_string(" 0 ", 16, 23, 122);D
		write_string(" 0 ", 16, 23, 0x0f);
		break;

	    case '1':
		no1[i] = '1';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 1 ", 14, 33, 122);D
		write_string(" 1 ", 14, 33, 0x0f);
		break;

	    case '2':
		no1[i] = '2';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 2 ", 14, 28, 122);D
		write_string(" 2 ", 14, 28, 0x0f);
		break;

	    case '3':
		no1[i] = '3';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 3 ", 14, 23, 122);D
		write_string(" 3 ", 14, 23, 0x0f);
		break;

	    case '4':
		no1[i] = '4';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 4 ", 12, 33, 122);D
		write_string(" 4 ", 12, 33, 0x0f);
		break;

	    case '5':
		no1[i] = '5';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 5 ", 12, 28, 122);D
		write_string(" 5 ", 12, 28, 0x0f);
		break;

	    case '6':
		no1[i] = '6';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 6 ", 12, 23, 122);D
		write_string(" 6 ", 12, 23, 0x0f);
		break;

	    case '7':
		no1[i] = '7';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 7 ", 10, 33, 122);D
		write_string(" 7 ", 10, 33, 0x0f);
		break;

	    case '8':
		no1[i] = '8';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 8 ", 10, 28, 122);D
		write_string(" 8 ", 10, 28, 0x0f);
		break;


	    case '9':
		no1[i] = '9';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" 9 ", 10, 23, 122);D
		write_string(" 9 ", 10, 23, 0x0f);
		break;
	    ///////////////////

	    case '.':
		no1[i] = '.';
		i++;
		no1[i] = 0;
		write_string(no1, 6, 25, 0x70);
		write_string(" . ", 16, 28, 122);D
		write_string(" . ", 16, 28, 0x0f);
		break;

	    case '+':
		no1[i] = 0;
		write_string(" +                    ", 6, 25, 0x70);
		*sign = '+';
		return atof(no1);

	    case '-':
		no1[i] = 0;
		write_string(" -                    ", 6, 25, 0x70);
		*sign = '-';
		return atof(no1);

	    case '*':
		no1[i] = 0;
		write_string(" *                    ", 6, 25, 0x70);
		*sign = '*';
		return atof(no1);

	    case '/':
		no1[i] = 0;
		write_string(" /                    ", 6, 25, 0x70);
		*sign = '/';
		return atof(no1);

	    case 13:
	    case '=':
		  return atof(no1);

	    case 27:
		*sign = 27;
		return 0;
	    default :
	       sound(1000);delay(200);nosound();
	       break;
	}
    }
return 0;
}

void interrupt our_9(...)
{
   key = inportb(0x60);

   if( active == 0 && key == 68 ) // F10 pressed
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

void main()
{

     prv_8 = getvect(8);
//     setvect(8,our_8);

     prv_9 = getvect(9);
     setvect(9,our_9);

     prv_28 = getvect(0x28);
     setvect(0x28, our_28);

     i.h.ah = 0x34;
     intdosx(&i,&o,&s);
     dosbusy = (char far*)MK_FP(s.es, o.x.bx);

     keep(0, (_SS + (_SP/16) - _psp) + 100);
    return;
}

