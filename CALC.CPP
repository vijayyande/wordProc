#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define D delay(30);

void far Box(int x1,int y1,int x2,int y2,int sd,int fc,int bc);
void far write_char(char ch,int row,int col,int attb);
void far write_string(char *str,int row,int col,int attr);
float far Getno(char *);
void Perform();
void Calculator();

void Calculator()
{
	char vijay[] = {"UHI@X@-X@MCD"};
	clrscr();

	window(21, 6, 59, 21);
	clrscr();
	window(1,1,80,25);

//	Box(43, 10,54, 18, 1, 8,  9);
	Box(20, 5, 60, 22, 3, 15, 0);
	Box(22, 6, 57, 8 , 1, 15, 0);
	Box(22, 9, 57, 19, 1, 15, 0);

	gotoxy(30,20);textcolor(15+128);
	for(int t = 0 ; vijay[t] != 0 ; t++)
		vijay[t] = vijay[t] + 1;
	cprintf("%s",vijay);


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

    write_string(" ÍÍ ",16, 47, 0x0e);

    Perform(); // call calculator

    return;
}


void far Box(int x1,int y1,int x2,int y2,int sd,int fc,int bc)
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



void Perform()
{
	 float first,second = 0,result = 0;
	 char Res[50];
	 char sign = 0;

   while( sign != 27)
   {

	 write_string("							  ",6,25,122);

	 first = Getno(&sign);
	if( second != 0 )
	{
	 switch(sign)
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
			 if( first == 0 || second == 0)
			 first = 0;
			 else
			 first = first / second;
			 break;

		case 27:
			 return ;

		default :
			 printf("\a");
			 break;
	 }
	sprintf(Res, "%f",first);
	write_string(Res, 6, 25, 0x70);
//	first = result;
	while(!kbhit());
	continue;
   }
	 second = Getno(&sign);//Second number
	 switch(sign)
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
			 if( first == 0 || second == 0)
			 first = 0;
			 else
			 first = first / second;
			 break;

		case 27:
			 return ;

		default :
			 printf("\a");
			 break;
	 }
	sprintf(Res, "%f",first);
	write_string(Res, 6, 25, 0x70);
//	first = result;
	while(!kbhit());

/*
	 second = Getno(&sign);// Second number
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
			 if( first == 0 || second == 0)
			 result = 0;
			 else
			 result = first / second;
			 break;
		case 27:
			 return ;

		default :
			 printf("\a");
			 break;
	 }
	sprintf(Res, "%f",result);
	write_string(Res, 6, 25, 0x70);
	first = result;
	while(!kbhit());		*/

   }

return;
}

float far Getno(char *sign)
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
		case ' ':
			return 32;

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

		case 8:
		if( i > 0)
		{
			i--;
			no1[i] = 0;
			write_string("                        ", 6, 25, 122);
			write_string(no1, 6, 25, 0x70);
		}
		else printf("\a");
		break;

		case 13:
		case '=':
		  return atof(no1);

		case 27:
		*sign = 27;
		return 0;
		default :
		   printf("\a");
		   break;
	}
    }
return 0;
}


void main()
{
    Calculator();
    return;
}

