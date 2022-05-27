#include <stdio.h>
#include <conio.h>

void CheckBox(int *check,char prompt[][CheckLength],int TotalCheckBoxItems,int col,int row);

void main()
{
   int a[5];
   char prompt[5][CheckLength] = {
		       {" File    "},
		       {" Edit    "},
		       {" Search  "},
		       {" Run     "},
		       {" Compile "}
		   };

   clrscr();
   CheckBox(a,prompt,5,25,11);
return;
}
/*
void CheckBox(int *check,char prompt[][CheckLength],int cn,int col,int row)
{
     text_info ti;
     gettextinfo(&ti);
     char c1 = 1,flag = 1;

     textcolor(0);
     textbackground(15);
     _setcursortype(0);

    for(int i = 0 ; i < cn ; i++)
    {
        gotoxy(col,row+i);
        cprintf(" [ ] %s ",prompt[i]);
    }
    char c1 = 0 , c2 = 0 ;
    i = 0;

  while( c1 != 27 || c1 != 9 )
  {
     c1 = getch();
     switch(c1)
     {
        case 0:
        c2 = getch();
        switch(c2)
        {
              case 80:
	  textcolor(11);
	  textbackground(0);
	  gotoxy(col,row+i);
	  cprintf(" [%c] %s ",prompt[i]);

	  i++;

	  textcolor(0);
	  textbackground(15);
	  gotoxy(col,row+i);
	  cprintf(" [%c] %s ",prompt[i]);
	  break;

             case 72:
	 textcolor(11);
	 textbackground(

     c1 = getch();
     if( c1 == 32 )
     {
        switch(flag)
        {
         case 1:
           gotoxy(col,row);
           cprintf(" [X] %s ",prompt);
           *check = 1;
           flag = 0;
           break;

         case 0:
           gotoxy(col,row);
           cprintf(" [ ] %s ",prompt);
           *check = 0;
           flag = 1;
           break;
        }
     }
  }
  textcolor(11);
  textbackground(0);
  gotoxy(col,row);
  cprintf(" [%c] %s ",flag == 0 ? 'X' : ' ',prompt);

  textattr(ti.attribute);
  gotoxy(ti.curx,ti.cury);
  return;
}
