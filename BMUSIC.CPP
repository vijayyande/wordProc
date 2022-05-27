#include <dos.h>
int f = 50;
void interrupt (*old)(...);
void interrupt music(...)
{
      old();
      sound(f);
      if( f > 300)
	  f = 50;
      else f += 30;
}

void main()
{
   old = getvect(8);
   setvect(8,old);
   keep(0, (_SS + (_SP/16) - _psp));
}

