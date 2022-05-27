#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

void main()
{

    int x = 100,y = 100,mode,drive;
    detectgraph(&mode,&drive);
    initgraph(&mode,&drive,"c:\\turbo-c");

    cleardevice();
//    moveto(random(600),random(300));
    outtext("vijay");

    //x = getx() ;  y = gety();
    moveto(x,y);
      char o1,o2;
      short flag=0;
      int rectx1,rectx2,recty1,recty2;

           back : o1 = getch();
           switch(o1)
             {
              case 0:
	 o2 = getch();
	   switch(o2)
	    {
	      case 77:
	         moveto( ++x , y );break;
	      case 75:
	         moveto( --x , y );break;
	      case 80:
	         moveto( x , ++y );break;
	      case 72:
	         moveto( x , --y );break;
	      default :
	         cout << "\a";break;
	    }

              case 13:
	if(flag == 0)
	{
	  rectx1 = x; // store current values
	  recty1 = y;
	  flag = 1;goto back;
	}

	if(flag == 1)
	  {
	      rectx2 = x;
	      recty2 = y;
	      rectangle(rectx1,recty1,rectx2,recty2);
	      flag = 0;
	  }
	  goto back;

            default :
              cout << "\a";goto back;
          }  //end switch case

      cout << "\n End run \n";
return;
}
