#include <stdio.h>
#include <conio.h>

void main()
{
	double tp, sy1, sy;

	clrscr();
	for( double i = (double) 0XFFFFFFFFFFFFFFFF ; i > -99999 && ! kbhit() ; i-- )
	{
		sy  = i / 9999;
		sy1 = sy * 9999;
		printf("\n%f\t%f\t%f", i, sy , sy1 );
//		if( (long)i % 24 == 0 )
//			if( getch() == 27 )
//				return ;
	}

}


