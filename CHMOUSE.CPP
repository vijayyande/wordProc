#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include <graphics.h>
#include <mouse.h>
void put_image(int ,int);

void main()
{

    int a,b;
    detectgraph(&a,&b);
    initgraph(&a,&b,"\\turbo-c\\bgi");

    line(1,15,30,15);
    line(15,1,15,30);

    void *mp,*mp1;
    mp  = malloc(imagesize(0,0,30,30));
    mp1 = malloc(imagesize(0,0,30,30));

    getimage(0,0,30,30,mp);

    settextstyle(4,0,10);
    outtextxy(50,50,"VIJAY");
    bar(100,300,400,400);

	int x,y, x1, y1;
	while(!kbhit())
	{

	x = GetMX(); y = GetMY();


		x1 = x, y1 = y;
		getimage(x, y, x+30, y+30, mp1);
		//put_image(x,y);
		putimage(x, y, mp, 1);
		delay(150);
		putimage(x, y, mp1, 0);

    }
    put_image(100,100);

    getch();

}

void put_image(int x,int y)
{

   char image[10][10] = {
	{ 1,1,1,1,1,1,0,0,0,0 },
	{ 1,1,1,1,1,0,0,0,0,0 },
	{ 1,1,1,1,0,0,0,0,0,0 },
	{ 1,1,1,1,1,0,0,0,0,0 },
	{ 1,1,1,1,1,1,0,0,0,0 },
	{ 1,0,0,1,1,1,1,0,0,0 },
	{ 0,0,0,0,1,1,1,1,0,0 },
	{ 0,0,0,0,0,1,1,1,1,0 },
	{ 0,0,0,0,0,0,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,0 }
       };

       for(int i = 0 ; i < 10 ; i++)
       for(int j = 0 ; j < 10 ; j++)
	  if(image[j][i] == 1)
	     putpixel(x+j,y+i,getpixel(x+j,y+i)+2);

}