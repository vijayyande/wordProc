#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include <mem.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>

#define D delay(30);
#define BEEP sound(600);delay(100);nosound();

#define LC if( i >= 27 || j >= 27 )\
				continue;

// This is latest file than calci4.cpp works properly
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
void far Calculator();
void far Write(char *string,int fc,int bc,int x,int y);
int  far strlen(char *);

volatile char far *dosbusy;
volatile char far stack[4001];
unsigned want = 0,key,ss,sp,active = 0;
void far *buf[4];
int x,y;
char screen[4002];
char vijay[16] = {"UHI@X@-X@MCD"};
unsigned char far *kb = ( unsigned char far*) 0x417 ;

union REGS i,o;
struct SREGS s;

void far Calculator()
{
	i.h.ah = 0x0F;
	int86(0x10, &i, &o);
  if( o.h.al >=0x04 && o.h.al <= 0x13 )
  {
	 sound(500);delay(300);
	 sound(700);delay(100);
	 sound(1000);delay(200);
	 sound(500);delay(300);
	 sound(700);delay(100);
	 sound(1000);delay(200);
	 sound(500);delay(300);
	 sound(700);delay(100);
	 sound(1000);delay(200);
	 nosound();
	 want = 0;
	 return;
  }

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
	textmode(3);
	x = wherex();
	y = wherey();

	window(20, 5, 60, 22);
	clrscr();
	window(1, 1, 80, 25);

	Box(20, 5, 60, 22, 3, 15, 0);
	Box(22, 6, 57, 8 , 1, 15, 0);
	Box(22, 9, 57, 19, 1, 15, 0);

//	gotoxy(33,20);textcolor(15+128);textbackground(0);
//	cprintf("%s", vijay);

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

	write_string(" + ", 10, 45, 0x0f);
	write_string(" - ", 10, 50, 0x0f);
	write_string(" * ", 12, 45, 0x0f);
	write_string(" / ", 12, 50, 0x0f);
	write_string(" Í ", 14, 45, 0x0f);
	write_string(" % ", 14, 50, 0x0f);

	gotoxy(x,y);
	cprintf(" \b");
	Perform(); // call actual calculator

	want = 0;
	active = 0;

	textmode(-1);
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
  row++;col++;
	struct text_info ti;
	gettextinfo(&ti);

	textattr(attb);
	gotoxy(col, row);
	cprintf("%c", ch);

	textattr(ti.attribute);
	gotoxy(ti.curx, ti.cury);
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

//////////////////////////////////////////

void Perform()
{
	 float first = 0,second = 0;
	 char Res[50];
	 char Ssign = 0, Fsign = 0;

	 while(Ssign != 27 || Fsign != 27)
	 {


		if( Fsign == 0  &&  Ssign == 0)
			first = Getno(&Fsign);
			if(first == 0)
			{
			   second = 0;
			   if( Fsign == 27)
				   return;
			   Fsign = 0;
			   Ssign = 0;
			   continue;
			}

		second = Getno(&Ssign);
			if(second == 0)
			{
			   first = 0;
			   Fsign = 0;
			   Ssign = 0;
			   if(Ssign == 27)
				  return;
			   continue;
			}
		if( Fsign != 0)
		{
			write_char(Fsign, 6, 26, 0x70);
			switch(Fsign)
			{
				 case '+':
					 first = first + second;
					 Fsign = 0;
					 break;

				 case '-':
					 first = first - second;
					 Fsign = 0;
					 break;

				 case '*':
					 first = first * second;
					 Fsign = 0;
					 break;

				 case '/':
					 first = first / second;
					 Fsign = 0;
					 break;

				 case 'c':
					 first = 0;
					 second = 0;
					 Ssign = 0;
					 Fsign = 0;
					 continue;

				 case '%':
					 first = first * (second / 100);
					 Fsign = 0;
					 break;

				 case 27:
					 return;

			}

		sprintf(Res, "%.2f", first);

		//if((strlen(Res)) > 29)
		if((strchr(Res, '.')- Res) > 27)
		{
			 write_string("Result is too large,Resseting",6,25,239);
			 while(!kbhit());
			 first = 0;
			 second = 0;
			 Fsign = 0;
			 Ssign = 0;
			 continue;
		}

		write_string("                             ",6,25,122);
		write_string(Res, 6, 25, 0x70);
		while(!kbhit());

		Fsign = Ssign; // Very Important statment

	   if( Fsign == 13  ||  Ssign == 13 )
	   {
					sprintf(Res, "%.2f", first);
					write_string("                             ",6,25,122);
					write_string(Res, 6, 25, 0x70);
					while(! kbhit());
					first = 0;
					second = 0;
					Fsign = 0;
					Ssign = 0;
	   }


		continue;
	   }// End IF

		if( Fsign == 0)
		{
			write_char(Ssign, 6, 23, 0x70);
			switch(Ssign)
			{
				 case '+':
					 first = first + second;
					 break;

				 case '-':
					 first = first - second;
					 break;

				 case '*':
					 first = first * second;
					 break;

				 case '/':
					 first = first / second;
					 break;

				 case 'c':
					first = 0;
					second = 0;
					Fsign = 0;
					Ssign = 0;
					continue;

				 case '%':
					 first = first * (second * 100);
					 break;

				 case 27:
					 return;

			}

		sprintf(Res, "%.2f", first);
		if(strlen(Res) > 29)
		{
			 write_string("Result is too large,Resseting",6,25,239);
			 while(!kbhit());
			 first = 0;
			 second = 0;
			 Fsign = 0;
			 Ssign = 0;
			 continue;
		}
		write_string("                              ",6,25,122);
		write_string(Res, 6, 25, 0x70);
		while(!kbhit());
	   }
	   if( Fsign == 13  ||  Ssign == 13)
	   {
					sprintf(Res, "%.2f", first);
					write_string("                             ",6,25,122);
					write_string(Res, 6, 25, 0x70);
					while(! kbhit());
					first = 0;
					second = 0;
					Fsign = 0;
					Ssign = 0;
	   }

	 }//while

return;
}
//####################################################
float Getno(char *sign)
{

	 char no[120] = "";
	 int i = 0,j;char ch1 = 1,ch2;
	 struct text_info ti;
	 gettextinfo(&ti);
	 int x = 26, y = 7;
	 textcolor(0);textbackground(15);
	 gotoxy(x,y);
	 fflush(stdin);
	 write_string("                              ",6,25,122);

	for( i = 0, j = 0 ; i < 120 && ch1 != '*' || ch1 != '/' || ch1 != '+' || ch1 != '-'; i++ )
	{
		fflush(stdin);
		if( i >= 27 )
		{
			i = 27;
		}
		if( j >= 27)
		{

		   BEEP;
		   j = 27;
		   gotoxy(26,7);
		   cprintf("%s  \b\b\b", no);
		}

		ch1 = getch();
		switch(ch1)
		{
			case 0:
				ch2 = getch();
				switch(ch2)
				{

					 case 77:      //  ->
						  if( j >= i )
						  {
							  i--;
							  BEEP;
							  break;
						  }
						  else
						  {
							  j++;
							  i--;
							  gotoxy(x+j, y);
						  }
						  break;

					 case 75:    //   <-
						  if( j == 0 )
						  {
							  i--;
							  BEEP;
							  break;
						  }
						  else
						  {
							  j--;
							  i--;
							  gotoxy(x+j, y);
						  }
						  break;

					 case 59:
						i--;
						gotoxy( 1, 1);
						printf( "Programmed by..VIJAY A. Yande");
						break;
					 case 83:  // Del
						  if( j >= i)
						  {
							  BEEP;
							  i--;
							  break;
						  }
						  else
						  {
							   memmove(no+j, no+j+1, i-j+1 );
							   gotoxy(26, 7);
							   cprintf("%s  \b\b", no);
							   gotoxy(x+j, y);
							   i--;
							   i--;
						  }
						  break;

				}
				break;

			//******************************
			case '0':
				LC;
				if( j == i )
				{
					no[i] = '0';
					gotoxy(x+j, y);
					cprintf("0");
					j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '0';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '1':
				LC;
				if( i == j )
				{
				   no[i] = '1';
				   gotoxy(x+j, y);
				   cprintf("1");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '1';
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   j++;
				}
				break;

			case '2':
				LC;
				if( i == j )
				{
				   no[i] = '2';
				   gotoxy(x+j, y);
				   cprintf("2");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '2';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '3':
				LC;
				if( i == j )
				{
				   no[i] = '3';
				   gotoxy(x+j, y);
				   cprintf("3");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '3';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '4':
				LC;
				if( i == j )
				{
				   no[i] = '4';
				   gotoxy(x+j, y);
				   cprintf("4");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '4';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '5':
				LC;
				if( i == j )
				{
				   no[i] = '5';
				   gotoxy(x+j, y);
				   cprintf("5");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '5';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '6':
				LC;
				if( i == j )
				{
				   no[i] = '6';
				   gotoxy(x+j, y);
				   cprintf("6");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '6';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '7':
				LC;
				if( i == j )
				{
				   no[i] = '7';
				   gotoxy(x+j, y);
				   cprintf("7");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '7';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '8':
				LC;
				if( i == j )
				{
				   no[i] = '8';
				   gotoxy(x+j, y);
				   cprintf("8");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '8';
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   j++;
				}
				break;

			case '9':
				LC;
				if( i == j )
				{
				   no[i] = '9';
				   gotoxy(x+j, y);
				   cprintf("9");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '9';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case '%':
				no[i] = 0;
				write_char('%', 6, 21, 0x70+127);
				textattr(ti.attribute);
				*sign = '%';
				return atof(no);

			case '.':
				if( i == j )
				{
				   no[i] = '.';
				   gotoxy(x+j, y);
				   cprintf(".");
				   j++;
				}
				else
				{
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				   i++;
				   memmove(no+j+1, no+j, i-j );
				   no[j] = '.';
				   j++;
				   gotoxy(26,7);cprintf("%s",no);gotoxy(x+j, y);
				}
				break;

			case 'c':
			case 'C':
				*sign = 'c';
				write_char(240, 6, 21, 0x70+127);
				write_string("All Cancelled                ",6,25,239);
				while(!kbhit());
				return 0;

			case '=':
			case 13 :
				no[i] = 0;
				write_char('=', 6, 21, 0x70+127);
				textattr(ti.attribute);
				*sign = 13;
				return atof(no);

			case 8:
				  if( j == 0 || i == 0)
				  {
					  write_char('E', 6, 21, 239);
					  sound(500);delay(200);nosound();
					  write_char(*sign, 6, 21, 239);
					  i--;
					  break;
				  }
				  else
				  {
					   no[i] = 0;
					   memmove(no+j-1, no+j, i-j+1 );
					   i -= 2;
					   j--;
					   gotoxy(26,7);
					   cprintf("%s  \b\b\b", no);
					   gotoxy(x+j, y);
				  }
				break;


		case '+':
			no[i] = 0;
			*sign = '+';
			write_char('+', 6, 21, 239);
			textattr(ti.attribute);
			return atof(no);

		case '-':
			no[i] = 0;
//			write_string(" -                           ",6,25, 0);
			*sign = '-';
			write_char('-', 6, 21, 239);
			textattr(ti.attribute);
			return atof(no);

		case '*':
			no[i] = 0;
//			write_string(" *                           ",6,25,0x70);
			*sign = '*';
			write_char('*', 6, 21, 239);
			textattr(ti.attribute);
			return atof(no);

		case '/':
			no[i] = 0;
//			write_string(" /                           ",6, 25, 239);
			*sign = '/';
			write_char('/', 6, 21, 239);
			textattr(ti.attribute);
			return atof(no);

		case 27:
			*sign = 27;
			textattr(ti.attribute);
			return 0;

		default :
		   sound(800);delay(400);nosound();
		   i--;
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

   if( active == 0 && key == 47 && (*kb & 8) == 8 ) // Alt+V pressed
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

void far Help()
{
printf("\n                                Pop-up  Calculator\n\t\t\t\t\t\t\t%s",vijay);
printf("\nThis is a TSR (Terminate and stay resident) Calculator.");
printf("\nThis program requires MS-DOS operating system.");
printf("\nThis program works fine with monochrome mode or color mode.");
printf("\nFor this program a VGA monitor is recomanded.");
printf("\nPressing a F12 key will call this calculator ");
printf("\nPress Esc to deactivate calculator.");
printf("\nUse arrow keys, backspace, Del keys freely.");
printf("\nWhen you makes some mistake Calculator will Beep.");
printf("\nTo reset Calculator Press `C' (All Cancel) key on your keyboard.");
printf("\nPercentage-> e.g. What is 20 Percentage of 300? answer is 60.");
printf("\nWarning! , This program don't work in graphics mode.");
printf("\nWhen graphics mode is active it simply beeps and refuses to popup.");
printf("\n\Programmed by %s ", vijay);
return;
}

int  far strlen(char*str)
{
	for( int i = 0 ; str[i] != 0 ; i++);
	   return (++i);
}

void main(int argc, char *argv[])
{
	  for(int t = 0 ; vijay[t] != 0 ; t++)
		vijay[t] += 1;

   if( argc > 1 )
	  if(argv[1][0] == '-' || argv[1][0] == '/' && argv[1][1] == '?')
	  {
		  Help();
		  return;
	  }


		textmode(3);
		textcolor(15);textbackground(0);

	 cprintf("\aA TSR Calculator by %s", vijay);
	  normvideo();
	  printf("\nPress F12 to activate Calculator.");
	  printf("\nEsc  to deactivate calculator.");
	  printf("\nThis program requires at least 50 KB bytes of memory ");
	  printf("\nFor Help type CALCI /?\n");


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

	 if( farcoreleft() < 51000L )
	 {
		 printf("\n\a\aInsufficient memory.");
		 printf("\nThis program requiresat least 50 KB memory ");
		 return;
	 }

	 keep(0, (_SS + (_SP/16) - _psp) + 100);


//	 clrscr();
//	 Calculator();

	 return;
}

