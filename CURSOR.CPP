#include <stdio.h>
#include <conio.h>
#include <dos.h>

void main()
{
    union REGS ri,ro;


    ri.h.ah = 0x01;
    ri.h.ch = 0x00;
    for( int i = 0 ; i < 20 ; i++)
    {
	     ri.h.cl = i;

	     clrscr();
	     int86(0x10,&ri,&ri);
	     while( getche() != 27);
    }
return;
}


