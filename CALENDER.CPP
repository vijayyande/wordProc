#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>
#define MenuLength 30

int far Pop_up_menu(int menuno,const char menu[][MenuLength],int x,int y,int fc,int bc);
void far add_item();
void far remove_item();
void far remove_item(int);
void far list_item();
void far list_today();
void far get_today();


struct Item
{
	 struct time t;
	 struct date d;
	 char message[120];
};


struct Item *ToDay;
unsigned no_of_item;

void far Calender()
{
   int choice;
   char menu[5][MenuLength] = {
					{" Add item     "},
					{" Remove item  "},
					{" List items   "},
					{" List Today   "},
					{" Return       "}
				   };

	choice = Pop_up_menu(5, menu , 20, 10, 15, 0);
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
		   list_today();
		   break;
	   case 5:
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
	 int x, y;

	 app.t.ti_min   =  100;
	 app.t.ti_hour  =  100;
	 app.t.ti_sec   =  100;

	 printf("\nEnter time => \n");
	 x = wherex(); y = wherey();
	 while( app.t.ti_min < 0 || app.t.ti_min > 60)
	 {
		 gotoxy(x,y);
		 printf("\n Enter minute :     \b\b\b\b");scanf("%d", &app.t.ti_min  );
	 }

	 x = wherex(); y = wherey();
	 while( app.t.ti_hour < 1  ||  app.t.ti_hour > 24)
	 {
		   gotoxy(x,y);
		   printf  (" Enter hour   :     \b\b\b\b");scanf("%d", &app.t.ti_hour );
	 }

	 x = wherex(); y = wherey();
	 while( app.t.ti_sec < 1  ||  app.t.ti_sec > 60)
	 {
		   gotoxy(x,y);
		   printf  (" Enter second :     \b\b\b\b");scanf("%d", &app.t.ti_sec  );
	 }


	 printf("\n\n Enter date => \n");
	 printf(" Enter year   : ");scanf("%d",  &app.d.da_year );
	 printf(" Enter day    : ");scanf("%d",  &app.d.da_day  );
	 printf(" Enter month  : ");scanf("%d",  &app.d.da_mon  );

	 printf("\n\n\a Enter your message : \n");
	 fflush(stdin);
	 gets(app.message);

	 FILE *fp;
	 fp = fopen("calender.vay","a+b");
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
   remove_item(i);
}


void far remove_item(int i)
{
   FILE *fp1,*fp2;
   struct Item app;

   fp1 = fopen("calender.vay", "r+b");
   fp2 = fopen("calender.baj", "w+b");
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
			fread (&app, sizeof(Item), 1, fp1);
	  }
	  else
	  {
			sz = fread (&app, 1, sizeof(Item), fp1);

			if( sz != sizeof(Item) )
			{
				//printf("\n\aRead failure. ");
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

   fp = fopen("calender.vay","r+b");
   if( fp == 0 )
   {
	  printf("\n\aError : Can't open file. ");
	  return;
   }

   while( ! feof(fp) )
   {
		read = fread((void*) &app, 1, sizeof(Item), fp);

		if( read != (sizeof(Item)) )
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

void far get_today()
{
  struct date today;
  FILE *fp;
  struct Item app;
  long read;

  fp = fopen("calender.vay","r+b");
  ToDay = (Item*) malloc(sizeof(Item));

  getdate(&today);
   while( ! feof(fp) )
   {
		read = fread((void*) &app, 1, sizeof(Item), fp);

		if( read != (sizeof(Item)) )
		{
			printf("\n\n\aEnd of File encountered. Get_Today\n");
			break;
		}

		if( (today.da_year == app.d.da_year)  &&  (today.da_day == app.d.da_day)  &&  ( today.da_mon == app.d.da_mon )  )
		{
		   no_of_item++;

		   ToDay = (Item*) realloc( ToDay,  no_of_item * sizeof(Item) );

		   ToDay[no_of_item].d.da_year = app.d.da_year;
		   ToDay[no_of_item].d.da_day  = app.d.da_day;
		   ToDay[no_of_item].d.da_mon  = app.d.da_mon;
		   ToDay[no_of_item].t.ti_hour = app.t.ti_hour;
		   ToDay[no_of_item].t.ti_min  = app.t.ti_min;
		   ToDay[no_of_item].t.ti_sec  = app.t.ti_sec;

		   strcpy(ToDay[no_of_item].message, app.message);

		   printf("\nDate : %d/%d/%d \t\t Time : %d:%d:%d",ToDay[no_of_item].d.da_year, ToDay[no_of_item].d.da_day, ToDay[no_of_item].d.da_mon, ToDay[no_of_item].t.ti_hour, ToDay[no_of_item].t.ti_min, ToDay[no_of_item].t.ti_sec );
		   printf("\nMessage : %s ",ToDay[no_of_item].message);
		   printf("\nno of items %d\n ",no_of_item);

		}
   }
   fclose(fp);
return;
}

void far list_today()
{

   clrscr();
   for( int i = 1 ; i <= no_of_item ; i++)
   {
		   printf("\nDate : %d/%d/%d \t\t Time : %d:%d:%d",ToDay[i].d.da_year, ToDay[i].d.da_day, ToDay[i].d.da_mon, ToDay[i].t.ti_hour, ToDay[i].t.ti_min, ToDay[i].t.ti_sec );
		   printf("\nMessage : %s ",ToDay[i].message);

   }
return;
}
void main()
{
	no_of_item = 0;
	clrscr();
	get_today();
	Calender();
}
