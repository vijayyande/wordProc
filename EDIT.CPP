#ifndef __EDIT_CPP
#define __EDIT_CPP

int far backspace(int flag)
{

if(flag == 1)
{// backsp
   if(counter == mh)
   {
	   counter--;
	   mh--;
   }
   if(counter < mh )
   {
	   _fmemcpy((mem+counter),(mem+counter+1),mh-counter);
   }
  if( row > 45 )
  {                                                      //mem[counter].size
	   scroll_horizontal(row,col-(5*FontSize),getmaxx()-32,col+(FontSize*20),FontSize*15,1,15);
	   row -= FontSize*15;
  }
  else BEEP;
}
else
{// delete
  if( row > 45 )
  {                                                      //mem[counter].size
	   scroll_horizontal(row,col-(5*FontSize),getmaxx()-32,col+(FontSize*20),FontSize*5,1,15);
	   row -= FontSize*5;
  }
  else BEEP;
}
   return 1;
}
/*________________________________________________________*/
void far scroll_horizontal(int x1,int y1,int x2,int y2,int pixel,int direction,int fillcolor)
{
     void far *prv;
     struct fillsettingstype fs;
     getfillsettings(&fs);
     prv = farmalloc(imagesize(x1,y1,x2,y2));
     if(prv == 0)
     {
			closegraph();
			printf("\n\a\ainsufficient memory");
			exit(1);
     }
		 HideMouse();
		 getimage(x1,y1,x2,y2,prv);
		 ShowMouse();

		 setfillstyle(1,fillcolor);
		 if(direction == 1)
		 {
			 HideMouse();
			 putimage(x1-pixel,y1,prv,0);
			 ShowMouse();
			 bar(x2-pixel,y1,x2,y2);
     }
     else
     {
			HideMouse();
			putimage(x1+pixel,y1,prv,0);
			bar(x1,y1,x1+pixel,y2);
			ShowMouse();
     }
     setfillstyle(fs.pattern,fs.color);
     farfree(prv);
     return;
}

void far PrintOut()
{
   union REGS ip;
   void far*buf[4];
   if( save_screen(buf) )
   {
	cleardevice();
	 Print(mh,4);

		int86(0x05,&ip,&ip);

	 getch();
	 restore_screen(buf);
   }
  else
	 MB.Message(200,200,400,350,"Insufficient memory");
return;
}

void far Box(int x1,int y1,int x2,int y2,int sd,int fc,int bc);
void far termination()
{
  closegraph();
  textbackground(11);
  window(1,1,80,15);
  clrscr();
  Box(1,1,79,15,2,15,11);
  Box(23,7,50,13,1,1,11);
  Box(23,2,50,5,3,1,11);

  textcolor(15+128);
  gotoxy(27,3);
  cprintf("Marathi WordProcessor");

  textcolor(4);

  gotoxy(25,8);
  cprintf(" 1. Vijay A. Yande ");

  gotoxy(25,9);
  cprintf(" 2. Parag Naik     ");

  gotoxy(25,10);
  cprintf(" 3. Mujjammil Tamboli ");

  gotoxy(25,11);
  cprintf(" 4. Dattatraya Baravakar ");

  gotoxy(25,12);
  cprintf(" 5. Ajay Patel   ");

  gotoxy(10,14);textcolor(15);
  cprintf("A third year project of Diploma Students...");
  window(1,1,80,25);
  gotoxy(1,16);
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

///  This function is for upward scrolling
void far up_scrolling()
{
   unsigned i = 0;
    for( i = mh ; i != 0 && scroller[mh] > 45 ; i--)
    {
	 scroll_down(LFont);
	 Print(scroller[i], col, mem[i].chr);
    }
}

#endif