#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#define MenuLength 30

void interrupt (*prv_9)(...);
void interrupt (*prv_8)(...);
void interrupt (*prv_28)(...);
void interrupt (*prv_15)(...);

void interrupt our_9(...);
void interrupt our_8(...);
void interrupt our_28(...);
void interrupt our_15(...);

void far write_char(char ch,int row,int col,int attb);
void far write_string(char *str,int row,int col,int attr);
void far cal();

volatile char far *dosbusy;
volatile char far stack[4001];
unsigned want = 0,key,ss,sp,active = 0;

int x,y;
char screen[4002];

union REGS i,o;
struct SREGS s;
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
return;
}

int far Pop_up_menu(int menuno,const char menu[][MenuLength],int x,int y,int fc,int bc);
void far add_item();
void far remove_item();
void far list_item();

struct ttime
{
	  int ti_min;
	  int ti_hour;
	  int ti_hund;
	  int ti_sec;
};

struct tdate
{
	int da_year;
	int da_day;
	int da_mon;     /* month (1 = Jan) */
};

struct Item
{
	 struct ttime t;
	 struct tdate d;
	 char message[120];
};

void far Calender()
{
   int choice;
   char menu[4][MenuLength] = {
					{" Add item     "},
					{" Remove item  "},
					{" List items   "},
					{" Return       "}
				   };

	choice = Pop_up_menu(4, menu , 20, 10, 15, 0);
	switch(choice)
	{
	   case 1:
		   add_item();
		   break;
	   case 2:
		   remove_item();
		   break;
	   case 3:
		   list_item();
		   break;
	   case 4:
		   break;
	}
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
/*########################################################################*/

int far Pop_up_menu(int menuno,const char menu[][MenuLength],int x,int y,int fc,int bc)
{
	char c1,c2,screen[4002];
	text_info ti;gettextinfo(&ti);
	gettext(1,1,80,25,screen);

	window(x,y,x+MenuLength-1,y+menuno+1);
	textbackground(bc);
	clrscr();
	Box(x,y,x+MenuLength-1,y+menuno+1,1,fc,bc);
	window(1,1,80,25);

	x++;y++;
   _setcursortype(0);
   textcolor(fc);textbackground(bc);
   for(int i = 0 ; i < menuno ; i++)
   {
	  gotoxy(x,y+i);
	  cprintf("%s",menu[i]);
   }

  i = 0;
   textcolor(bc);textbackground(fc);
   gotoxy(x,y+i);
   cprintf("%s",menu[i]);

  for(;i != -10000;)
  {

   c1 = getch();
   if( c1 < menuno && c1 != 0)
   {
		 delay(100);
		 window(ti.winleft,ti.wintop,ti.winright,ti.winbottom);
		 textattr(ti.attribute);gotoxy(ti.curx,ti.cury);
		 puttext(1,1,80,25,screen);
		 return c1;
   }
   switch(c1)
   {
	 case 0:
	  c2 = getch();
	  switch(c2)
	  {
		case 80:
	  textcolor(fc);textbackground(bc);
	  gotoxy(x,y+i);
	  cprintf("%s",menu[i]);

	  if( i >= menuno-1)
		  i = 0;
	  else i++;

	  textcolor(bc);textbackground(fc);
	  gotoxy(x,y+i);
	  cprintf("%s",menu[i]);

	  break;

	   case 72:
	 gotoxy(x,y+i);
	 textcolor(fc);textbackground(bc);
	 cprintf("%s",menu[i]);
	 if(i <= 0)
	   i = menuno - 1;
	 else i--;

	 gotoxy(x,y+i);
	 textcolor(bc);textbackground(fc);
	 cprintf("%s",menu[i]);
	 break;
		  }
		  break;

	case 13:
		 puttext(1,1,80,25,screen);
		 window(ti.winleft,ti.wintop,ti.winright,ti.winbottom);
		 textattr(ti.attribute);gotoxy(ti.curx,ti.cury);

		 return i+1;

	case 27:
		 puttext(1,1,80,25,screen);
		 window(ti.winleft,ti.wintop,ti.winright,ti.winbottom);
		 textattr(ti.attribute);gotoxy(ti.curx,ti.cury);

		 return 0;

	default:cprintf("\a");
   }
  }
   return 0;
}

void far add_item()
{
	 struct Item app;

	 printf("\nEnter time => ");
	 printf("\n Enter minute : ");scanf("%d", &app.t.ti_min  );
	 printf  (" Enter hour   : ");scanf("%d", &app.t.ti_hour );
	 printf  (" Enter second : ");scanf("%d", &app.t.ti_sec  );

	 printf("\n\n Enter date => \n");
	 printf(" Enter year   : ");scanf("%d",  &app.d.da_year );
	 printf(" Enter day    : ");scanf("%d",  &app.d.da_day  );
	 printf(" Enter month  : ");scanf("%d",  &app.d.da_mon  );

	 printf("\n\n\a Enter your message : \n");
	 fflush(stdin);
	 gets(app.message);

	 FILE *fp;
	 fp = fopen("calender.vay","a+");
	 if( fp == 0)
	 {
		printf("\n\a\aUnable to create");
		return;
	 }
	 fwrite((void*)&app, sizeof(Item), 1, fp);
	 fclose(fp);
	 return;
}


void far remove_item()
{
   int i;
   printf("\n\a Enter Item no to be deleted. ");
   scanf("%d",&i);
   FILE *fp1,*fp2;
   struct Item app;

   fp1 = fopen("calender.vay", "r+");
   fp2 = fopen("calender.baj", "w+");
   if( fp1 == 0 || fp2 == 0)
   {
	  printf("\nunable to open file.\a\a");
	  return;
   }

   size_t sz;

   for( unsigned j = 0 ;  ! feof(fp1) ; j++)
   {
	  if( j == i - 1)
	  {
			fread (&app, sizeof(Item)-1, 1, fp1);
	  }
	  else
	  {
			sz = fread (&app, 1, sizeof(Item)-1, fp1);

			if( sz != sizeof(Item)-1 )
			{
				printf("\n\aRead failure. ");
				break;
			}
			fwrite(&app, sizeof(Item), 1, fp2);
	  }
	}
	fclose(fp1);
	fclose(fp2);
	if(remove("calender.vay") != 0)
	{
	   printf("\nunable to delete file. ");
	   return;
	}
	if( rename("calender.baj","calender.vay") != 0)
	{
	   printf("\nunable to delete file. ");
	   return;
	}

return;
}


void far list_item()
{
   FILE *fp;
   size_t read;
   struct Item app;

   fp = fopen("calender.vay","r+");
   if( fp == 0 )
   {
	  printf("\n\aError : Can't open file. ");
	  return;
   }

   while( ! feof(fp) )
   {
		read = fread((void*) &app, 1, sizeof(Item)-1, fp);

		if( read != (sizeof(Item)-1) )
		{
			printf("\n\n\aEnd of File encountered. \n");
			break;
		}

		printf("\nMin= %d/Hour= %d/ Sec= %d\t\t year= %d/ day= %d/ month= %d ",app.t.ti_min, app.t.ti_hour,  app.t.ti_sec,  app.d.da_year, app.d.da_day,  app.d.da_mon);
		printf("\n%s \n",app.message);
   }

  fclose(fp);
  return;
}



void interrupt our_9(...)
{
   key = inportb(0x60);

   if( active == 0 && key == 88 ) // F12 pressed
       want = 1;

   prv_9();
return;
}

void interrupt our_8(...)
{
   prv_8();

   if( want == 1 && active == 0 && *dosbusy == 0)
	   cal();
return;
}

void interrupt our_28(...)
{
   prv_28();
   if(want == 1 && active == 0 && *dosbusy == 0)
	  cal();
return;
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
return;
}

void far cal()
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


	gotoxy(x,y);

	// Call Here your Main Function
	Calender();

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


void main()
{
	 printf("\n\aA TSR Calculator by VIJAY A. YANDE");
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
	return;
}

