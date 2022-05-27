#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include <mouse.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BEEP sound(1000);delay(100);nosound();
#define BEEP1 sound(1000);delay(200);nosound();

#include "c:\turbo-c\vijay\pushbotn.cpp"
#include "c:\turbo-c\vijay\message.cpp"

#define ScrollWindowWidth 25
#define HEIGHT 16
#define FALSE 0
#define TRUE  1


class POPUPMENU
{
	private :
		void far reverse(int x1,int y1,int x2,int y2, char far*prompt,int fc,int bc, int ENABLED_YN = 1 );
		int far *State;
		int Titems;

	public :
		POPUPMENU(int ti);
		POPUPMENU() { State = NULL ; };
		char far Popup(int x1,int y1,int x2,int y2, char cont[][ScrollWindowWidth] ,int fc = 15, int bc = 0 );
		void Enable( int No, int TRUE_FALSE );
};

void POPUPMENU::Enable( int No, int TRUE_FALSE )
{
	State[No-1] = TRUE_FALSE ;
}

POPUPMENU::POPUPMENU(int ti)
{
	State = (int far *) farcalloc( sizeof(int),  ti );
	Titems = ti ;// no of items
	if( State == NULL )
	{
		printf("\nInsufficient memory!");
		exit(1);
	}
	for( int i = 0 ; i < ti ; i++)
		State[i] = TRUE ;
}

void far POPUPMENU::reverse(int x1,int y1,int x2,int y2, char far*prompt,int fc,int bc, int EN)
{
	 char text[100] = "";
	 HideMouse();char a;
	 a = getcolor();
	 if( EN == TRUE )
	 {
		 setfillstyle( 1, bc );
		 bar(x1, y1, x2, y2);
	 }
	 setcolor(fc);
	 //settextstyle(2,0,6);
	 if( strcmp( prompt, "-") == 0 )
	 {
		setfillstyle( 1, bc );
		setcolor( 0 );
		line( x1, y1+HEIGHT/2, x2, y1+HEIGHT/2 );
		setcolor( 15 ) ;
		line( x1, y1+HEIGHT/2+1, x2, y1+HEIGHT/2+1 );
	}
	else
	{
		for( int i = 0 ; prompt[i] != NULL ; i++ )
		{
			if( prompt[i] != '&' )
			{
				text[i] = prompt[i] ;
			}
			else
			{
				text[i] = NULL ;
				break ;
			}
		}
		moveto( x1, y1 );
		outtext(text);
		line( getx(), gety()+HEIGHT-2, getx()+5, gety()+HEIGHT-2 );
		i++;

		for( int j = 0 ; prompt[i] != NULL ; i++, j++ )
		{
			text[j] = prompt[i] ;
		}

		text[j] = NULL ;
		setcolor( fc );
		outtext(text) ;
	}
		ShowMouse();
		setcolor(a);
}

char far POPUPMENU::Popup(int x1,int y1,int x2,int y2, char contents[][ScrollWindowWidth], int fc, int bc )
// Checks Mouse Click for POPUP MENU
{
	char ch,i=0;
	int maxx = getmaxx(), maxy = getmaxy() ;
	int mx = 0, my = 0, mx1 = x1, my1 = y1;
	int Choice = 0 ;
	void far *ip;
	char far*HotKeys = (char far*) farcalloc( 1, Titems+1 );
	if( HotKeys == NULL )
	{
		MessageBox::Message( 200, 100, 400, 250, "Insufficient memory ! " );
		return 0;
	}

	for( int t = 0 ; t < Titems ; t++ )
	{
		int p ;
		if( strcmp( contents[i], "-" ) != 0 )
		for( p = 0 ; contents[t][p] != NULL ; p++ )
		{
			if( contents[t][p] == '&' )
			{
				HotKeys[t] = contents[t][p+1] ;
				break;
			}
		}
		if( contents[t][p] == NULL )
			HotKeys[t] = 1 ;
	}
	for( t = 0 ; t < Titems ; t++ )
		if( HotKeys[t] == NULL )
			HotKeys[t] =  1 ;

	ShowMouse();
	y2 = y1+(Titems*HEIGHT);
	ip = farmalloc(imagesize(x1-1-3,y1-1-3,x2+1+3,y2+1+3));
	if(ip==0)
	{
		MessageBox::Message(200,150,400,250,"Insufficient memory");
		farfree( HotKeys );
		return 0;
	}

	HideMouse();
	getimage(x1-1-3,y1-1-3,x2+1+3,y2+1+3,ip);

	setcolor( 15 );
	line( x1-1, y1-1, x2+1, y1-1 );
	line( x1-1, y1-1, x1-1, y2+1 );
	setcolor( 0 );
	line( x2+1, y1-1, x2+1, y2+1 );
	line( x1-1, y2+1, x2+1, y2+1 );
	ShowMouse();

	setcolor(fc);
	settextstyle( 2, 0, 5);

	for( i = 0 ; i < Titems ; i++)
	{
		//reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], fc, bc);
		if( State[i] == TRUE )
		{
			reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
			reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE);
		}
		else
		{
			reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
		}

	}
	i = 0;
	Choice = 0 ;

	while(1)
	{
	fflush(stdin);
	while( ! kbhit() && ! Clicked( 0, 0, maxx, maxy ) )
	{
		mx = GetMX();
		my = GetMY();

		if( mx != mx1 || my != my1 )
		if(!( mx >= x1 && mx <= x2 && my >= y1+(Choice*HEIGHT) && my <= y1+(Choice*HEIGHT)+HEIGHT) )
		// Mouse is on popup menu
		if( mx >= x1 && mx <= x2 && my >= y1 && my <= y2 )
		{
			mx1 = mx ;
			my1 = my ;
			for( int j = 0 ; j < Titems ; j++ )
			{
				if( ( mx >= x1 ) && ( mx <= x2 ) &&  ( my >= y1+(j*HEIGHT) ) && ( my <= y1+(j*HEIGHT)+HEIGHT ) )
				{
					if( State[Choice] == FALSE )
					{
						reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
					}
					else
					{
						reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
						reverse(x1+1, y1+(Choice*HEIGHT)+1, x2+1, y1+(Choice*HEIGHT)+HEIGHT+1, contents[Choice], 0, bc, FALSE);
					}
					//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], fc, bc );
					Choice = j ;
					if( strcmp( contents[Choice], "-") == 0 )
						reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], fc, bc );
					else
						if( State[Choice] == TRUE )
						{
							//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], bc, fc );
							reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], bc+1, fc+1 );
							reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc, FALSE );
							reverse(x1+1, y1+(Choice*HEIGHT)+1, x2+1, y1+(Choice*HEIGHT)+HEIGHT+1, contents[Choice], 0, bc, FALSE);
						}
				}
			}
		}// end if
	}// end while

	if( !kbhit() )
	{

	while( Clicked( 0, 0, maxx, maxy ) )
	{
		mx = GetMX();
		my = GetMY();

		if( mx != mx1 || my != my1 )
		if(!( mx >= x1 && mx <= x2 && my >= y1+(Choice*HEIGHT) && my <= y1+(Choice*HEIGHT)+HEIGHT) )
		// Mouse is on popup menu
		if( mx >= x1 && mx <= x2 && my >= y1 && my <= y2 )
		{
			mx1 = mx ;
			my1 = my ;
			for( int j = 0 ; j < Titems ; j++ )
			{
				if( ( mx >= x1 ) && ( mx <= x2 ) &&  ( my >= y1+(j*HEIGHT) ) && ( my <= y1+(j*HEIGHT)+HEIGHT ) )
				{
					if( State[Choice] == FALSE )
					{
						reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
					}
					else
					{
						reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
						reverse(x1+1, y1+(Choice*HEIGHT)+1, x2+1, y1+(Choice*HEIGHT)+HEIGHT+1, contents[Choice], 0, bc, FALSE);
					}
					//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], fc, bc );
					Choice = j ;
					if( strcmp( contents[Choice], "-" ) == 0 )
						reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], fc, bc );
					else
						if( State[Choice] == TRUE )
						{
							//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], bc, fc );
							reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
							reverse(x1+1, y1+(Choice*HEIGHT)+1, x2+1, y1+(Choice*HEIGHT)+HEIGHT+1, contents[Choice], 0, bc, FALSE);
						}
				}
			}
		}
	}// end while


			for( int j = 0 ; j < Titems ; j++ )
			{
				if( ( mx >= x1 ) && ( mx <= x2 ) &&  ( my >= y1+(j*HEIGHT) ) && ( my <= y1+(j*HEIGHT)+HEIGHT ) )
				{

					if( State[Choice] == TRUE ) // if menu item is enabled
					{
						//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], bc, fc );
						reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
						reverse(x1+1, y1+(Choice*HEIGHT)+1, x2+1, y1+(Choice*HEIGHT)+HEIGHT+1, contents[Choice], 0, bc, FALSE);
					}
					//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], fc, bc );
					Choice = j ;
					if( strcmp( contents[Choice], "-") == 0 )
						reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], fc, bc );
					else
						if( State[Choice] == TRUE ) // if menu item is enabled
						{
							//reverse( x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], bc, fc );
							reverse(x1, y1+(Choice*HEIGHT), x2, y1+(Choice*HEIGHT)+HEIGHT, contents[Choice], 15, bc );
							reverse(x1+1, y1+(Choice*HEIGHT)+1, x2+1, y1+(Choice*HEIGHT)+HEIGHT+1, contents[Choice], 0, bc, FALSE);
						}

					if( strcmp( contents[Choice], "-" ) == 0 )
						break;

					if( State[Choice] == TRUE )
					{
						HideMouse();
						putimage(x1-1-3, y1-1-3, ip, 0);
						ShowMouse();
						farfree( ip );
						farfree( HotKeys );
						return Choice+1;
					}
				}
				if( !( ( mx >= x1 ) && ( mx <= x2 ) &&  ( my >= y1+(Choice*HEIGHT) ) && ( my <= y1+(Choice*HEIGHT)+HEIGHT )) )
				{
					ch = 27;
				}

			}// end for
	}// end if

	if( kbhit() )
		ch = getch() ;

	for( t = 0 ; t < Titems ; t++ )
	{
		if( toupper( ch ) == toupper( HotKeys[t] ) )
		{
			if( State[t] == FALSE )
				break;
			HideMouse();
			putimage(x1-1-3, y1-1-3, ip, 0);
			ShowMouse();
			farfree( ip );
			farfree( HotKeys );
			return t+1;
		}
	}

	char c2 = 0 ;
	i = Choice;

	 switch(ch)
	 {
	 case 0:
	   if( kbhit() )
		   c2 = getch();
	   else
		   break;

	   switch(c2)
	   {
		case 80:
			//reverse(x1,y1+(i*HEIGHT),x2,y1+(i*HEIGHT)+HEIGHT,contents[i],fc,bc);
			if( State[i] == FALSE )
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
			}
			else
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
				reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE);
			}
			if( i >= Titems-1)
				i = 0;
			else i++;
			if( strcmp( contents[i], "-") == 0 )
			{
				if( i >= Titems-1 )
					i = 0 ;
				else
					i++;
			}

			if( State[i] == TRUE )
			{
				//reverse(x1,y1+(i*HEIGHT),x2,y1+(i*HEIGHT)+HEIGHT,contents[i],bc,fc);
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], bc+1, fc+1 );
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc, FALSE );
				reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE);
			}
			if( State[i] == FALSE )
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
				//reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE);
			}
			break;

		case 72:
			//reverse(x1,y1+(i*HEIGHT),x2,y1+(i*HEIGHT)+HEIGHT,contents[i],fc,bc);
			if( State[i] == FALSE )
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
			}
			else
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
				reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE );
			}
			if( i == 0)
				i = Titems-1;
			else i--;
			if( strcmp( contents[i], "-") == 0 )
			{
				if( i == Titems-1 )
					i = Titems-1;
				else
					i--;
			}
			if( State[i] == TRUE )
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], bc+1, fc+1 );
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc, FALSE );
				reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE );
			}

			if( State[i] == FALSE )
			{
				reverse(x1, y1+(i*HEIGHT), x2, y1+(i*HEIGHT)+HEIGHT, contents[i], 15, bc );
				//reverse(x1+1, y1+(i*HEIGHT)+1, x2+1, y1+(i*HEIGHT)+HEIGHT+1, contents[i], 0, bc, FALSE );
			}
			break;

		case 77:
			HideMouse();
			putimage(x1-1-3, y1-1-3, ip, 0);
			ShowMouse();
			farfree(ip);
			farfree( HotKeys );
			return -1;

		case 75:
			HideMouse();
			putimage(x1-1-3, y1-1-3, ip, 0);
			ShowMouse();
			farfree(ip);
			farfree( HotKeys );
			return -2;

		default :
			BEEP1;break;
	}
	break;//outer switch

	case 13:
		if( State[i] == FALSE )
			break;
		HideMouse();
		putimage(x1-1-3,y1-1-3,ip,0);
		ShowMouse();
		farfree(ip);
		farfree( HotKeys );
		return i+1;

	case 27:
		HideMouse();
		putimage(x1-1-3,y1-1-3,ip,0);
		ShowMouse();
		farfree(ip);
		farfree( HotKeys );
		return 0;

	}
	Choice = i;
	}//end while

	x1++;y1++;x2++;y2++;Titems++;
	farfree( ip );
	farfree( HotKeys );
	return  0;
}

/*
void main()
{
	char Menu[7][ScrollWindowWidth] = {
					{" F&irst  "},
					{" &Second "},
					{" &Third  "},
					{"-"},
					{" Fif&th  "},
					{"-"},
					{" Se&venth"}
				};


	InitGraph();
	int choice;
	POPUPMENU pm(7) ;


	pm.Enable( 7, FALSE );
	pm.Enable( 2, FALSE );
	choice = pm.Popup( 100, 100, 200, 300, Menu, 5, 10 );
	printf("\n%d", choice );

}
*/

