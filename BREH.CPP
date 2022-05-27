#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

void BrLine( int x1, int y1, int x2, int y2 );

void main()
{
	int x1, y1, x2, y2;
	cout << "\nEnter co-ordinates ";
	cin >> x1 >> y1 >> x2 >> y2 ;

	InitGraph();
	line( x1, y1, x2, y2 );
	getch();
	cleardevice();
	BrLine( x1, y1 , x2, y2 );

	getch();
	return ;
}

void BrLine( int x1, int y1, int x2, int y2 )
{
	float e, dx, dy, x, y;
	dx = abs( x2 - x1 );
	dy = abs( y2 - y1 );
	if( dx == 0 )
		e = 1;
	else
		e = dy / dx - .5 ;

	if( (y2 - y1) < 0 || ( x2 - x1 ) < 0 )
		x = x2,	y = y2 ;
	else
		x = x1, y = y1 ;

	for( int i = 0 ; i < (dx <= 0 ? dy : dx) ; i++ )
	{
		putpixel( x, y, 15 );
		if( e > 0 )
		{
			y = y + 1;
			e = e - 1;
		}

		if( dx != 0 )
			x = x + 1;


		if( dx == 0 )
			e = e + 1;
		else
			e = e + ( dy / dx );

			//gotoxy( 2, 25);
			//cout << "\t\t" << x << "\t" << y << "\t\t";
	}

return ;
}

