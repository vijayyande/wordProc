#include <iostream.h>
#include <conio.h>
class Cursor
{
		int x,y;
	public :
		void Set_cursor(int,int);
		void Show_Hide(int i=1);
		void operator+(int d);
		void operator=(Cursor c);
};
void Cursor::Set_cursor(int i, int j)
{
	x = i; y = j;
}
void Cursor::Show_Hide(int i)
{
	gotoxy(x,y);
	if(i == 1)
		textbackground(15);
	else
		textbackground(0);
	cprintf(" ");
}
void Cursor::operator+(int d)
{
	switch(d)
	{
	case 1 :// left
			x--; break;
	case 2 :// right
			x++;break;
	case 3 :// up
			y--;break;
	case 4 :// down
			y++;break;
	}
}
void Cursor::operator=(Cursor c)
{
	x = c.x;
	y = c.y;
}
class Game
{
		int top,bottom;
		Cursor snake[10],t;
	public :
		void Set(int i,int j)
		{ top = i; bottom = j; }
		void Move(int=1);
		void Play();
};
void Game::Move(int d)// top = 0 bottom = 9;
{
		int i;
		if(d == 1)// for right arrow
			for(i = bottom; i >= top; i--)
				snake[i] = snake[i-1];// 9 = 8, 8 = 7,..
		else
			for(i = top; i <= bottom; i++)
				snake[i] = snake[i+1];
}
void Game::Play()
{
	char key1,key2;
	int i;
	t.Set_cursor(15,5);
	snake[0].Set_cursor(15,5);
	Move(0);
	for(i = 0;i<10;i++)
		snake[i].Show_Hide();
	do{
		key1 = getch();
		if(key1 == 0)
		{
			key2 = getch();
			switch(key2)
			{
			case 77 :// right arrow
					Move(1);
					snake[top].Show_Hide(0);
					snake[bottom].Show_Hide(1);
					break;
			case 75 :// left arrow
					Move(0);
					snake[top].Show_Hide(1);
					snake[bottom].Show_Hide(0);
					break;
			}
		}else if(key1 == 27)
			break;
	}while(1);
}
void main()
{
	textmode(BW80);
	Game game;
	game.Set(9,0);
	game.Play();
}


