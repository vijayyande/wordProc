#include <stdio.h>
#include <conio.h>
#include <alloc.h>

#define ChkMem(f1,f2) if(f1 == f2 )                                \
		      { printf("unable to allcate memory.");return;}

void far scroll();
void far Save_File();
void far left();
void far right();
void far up();
void far down();
char far keypress();

int x,y;
char far*buf;
char ch1,ch2;
long chars;

void main()
{
     x = 1; y = 1 ;

     buf = (char far*)farcalloc(5000,1);
     ChkMem(buf,0);

     clrscr();
     for(;;)
     {
     ch1 = keypress();
     switch(ch1)
     {
       case 0:
       ch2 = getch();
       //////////////////////////////////////////////////////
       switch(ch2)
       {
	    case 77:
	       left();
	       break;

	    case 75:
	       right();
	       break;

	    case 72:
	       up();
	       break;

	    case 80:
	       down();
	       break;

      }
      break;
      //?????????????????????????????????????????
       case 19:
	   Save_File();
	   break;

       case 27:
	    return;

       case 13:
	    buf[chars] = 13;
	    x = 1;
	    if( y == 25)
		scroll();
	    else y++;
	    gotoxy(x,y);
	    chars++;
	    break;

       default :
	   buf[chars] = ch1;
	   printf("%c",ch1);
	       if( x == 80)
	       {
		   x = 1;
		   y++;
	       }
	       else x++;
	   chars++;
	   break;
      }
    }
return;
}//********************************************

void far scroll()
{
   char buf[4000];
   gettext(1,2,80,25,buf);
   clrscr();
   puttext(1,1,80,24,buf);
}

void far Save_File()
{
}
void far left()
{
	if( x == 80)
	{
	   x = 1;
	   y++;
	}
	else x++;
	gotoxy(x,y);
}
void far right()
{
       if( x == 1)
       {
	   x = 1;
       }
       else x--;
       gotoxy(x,y);
}
void far up()
{
       if( y == 1)
       {
	   y = 1;
       }
       else y--;
       gotoxy(x,y);
}
void far down()
{
       if( y == 25)
       {
	   y = 25;
       }
       else y++;
       gotoxy(x,y);
}

char far keypress()
{
      char c;
      int key;
      while( !kbhit())
      {
	key = _bios_keybrd(2);
	if( key & 0x08 )
	    activate_menu();
      }

    c = getch();
    return c;
}

void far activate_menu()
{
