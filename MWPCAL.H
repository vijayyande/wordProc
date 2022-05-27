#include"mwpcalc.h"


    Window::Window(Window* ptro,int l,int r,int t,int b,int dc,int cc)
	{
	ptrOwner=ptro;left=l;top=t;right=r,bot=b;
	deltacolor=dc; centercolor=cc;

	delta = ((right-left)+(bot-top))/150+3;
	if( ptrOwner != SCREEN)
		{
		left += ptrOwner->left;
		right += ptrOwner->left;
		top += ptrOwner->top;
		bot += ptrOwner->top;
		}
	      }

 void Window :: Display(void)
	{
	setcolor(WHITE);

	int p[10];
	p[0]=left; p[1]=top;
	p[2]=right; p[3]=top;
	p[4]=right; p[5]=bot;
	p[6]=left; p[7]=bot;
	p[8]=left; p[9]=top;
	setfillstyle(SOLID_FILL,deltacolor);
	fillpoly(5,p);

	rectangle(left+delta+1,top+delta,right-delta-1,bot-delta);

	setfillstyle(SOLID_FILL,centercolor);

	floodfill(left+(right-left)/2,top+delta+1,WHITE);
	}
 void Button::Click(void)
	{
	bstatus=pushed;
	Button::Display();
	sound(500); delay(10); nosound();
	delay(250);
	bstatus = unpushed;
	Button::Display();
	sound(400); delay(10); nosound();
	}
void Button::Display(void)
	{
	Window::Display();

	moveto(left+(right-left)/2+1,top+(bot-top)/2);
	settextjustify(CENTER_TEXT,CENTER_TEXT );
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,USER_CHAR_SIZE);
	setusercharsize(5,8,2,3);
	setcolor(WHITE);
	outtext(text);

	moveto(left,top);
	lineto(left+delta,top+delta);
	moveto(right,top);
	lineto(right-delta,top+delta);
	moveto(left,bot);
	lineto(left+delta,bot-delta);
	moveto(right,bot);
	lineto(right-delta,bot-delta);

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	if(bstatus==unpushed)
		{
		floodfill (left+(right-left)/2,bot-1,WHITE);
		floodfill (right-1,top+(bot-top)/2,WHITE);
		}
       else
		{
		floodfill (left+(right-left)/2,bot-1,WHITE);
		floodfill (right-1,top+(bot-top)/2,WHITE);
		}
	      }

  void Output::Text(char *ptrstring)
	{
	Display();
	moveto(right-delta,top+(bot-top)/2);
	settextjustify(RIGHT_TEXT,CENTER_TEXT );
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,USER_CHAR_SIZE);
	setusercharsize(5,8,1,1);
	setcolor(BLACK);
	outtext(ptrstring);
	}

 void Output::Number(double d)
	{
	char buffer[80];
	sprintf(buffer,"%16.2lf",d);
	Output::Text(buffer);
	}














































