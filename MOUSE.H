#ifndef __MOUSE_H
#define __MOUSE_H
union REGS mi,mo;
void SetSpeed(int speed)
  {
	     mi.x.ax = 0x13;
	     mi.x.dx = speed;
	     int86(0x33,&mi,&mo);
  }
inline void ResetMouse()
  {
	   mi.x.ax = 0;
	   int86(0x33,&mi,&mo);
  }
inline void ShowMouse()
  {
	  mi.x.ax = 1;
	  int86(0x33,&mi,&mo);
  }
inline void HideMouse()
  {
	   mi.x.ax = 2;
	   int86(0x33,&mi,&mo);
  }
int GetMX()
  {
	   mi.x.ax = 3;
	   int86(0x33,&mi,&mo);
	   return (mo.x.cx);
  }
int GetMY()
  {
	   mi.x.ax = 3;
	   int86(0x33,&mi,&mo);
	   return (mo.x.dx);
  }
int Clicked(int x1,int y1,int x2,int y2)
  {
	   mi.x.ax = 3;
	   int86(0x33,&mi,&mo);
	   if(mo.x.cx >= x1 && mo.x.cx <= x2 && mo.x.dx >= y1 && mo.x.dx <= y2)
		  return (mo.x.bx);
	   else return 0;
  }
void SetMousePossition(int x,int y)
  {
	   mi.x.ax = 0x04;
	   mi.x.cx = x;
	   mi.x.dx = y;
	   int86(0x33,&mi,&mo);
  }
void SetHorizontalLimit(int min,int max)
    {
		 mi.x.ax = 7;
	     mi.x.ax = min;
	     mi.x.ax = max;
	     int86(0x33,&mi,&mo);
   }
void SetVerticalLimit(int min,int max)
   {
	     mi.x.ax = 8;
	     mi.x.cx = min;
	     mi.x.dx = max;
	     int86(0x33,&mi,&mo);
   }
void ChangeShape(int x,int y,void far*ip)
  {
	  union SREGS sr;
	    mi.x.ax = 0x09;
	    mi.x.bx = x;
	    mi.x.cx = y;
	    sr.es   = FP_SEG(ip);
	    mi.x.dx = FP_OFF(ip);
	    int86x(0x33,&mi,&mo,&sr);
  }
void SetExclusionArea(int x1,int y1,int x2,int y2)
    {
	    mi.x.ax = 0x10;
	    mi.x.cx = x1;
	    mi.x.dx = y1;
	    mi.x.si = x2;
	    mi.x.di = y2;
	    int86(0x33,&mi,&mo);
  }
void ResetExclusionArea()
   {
	    mi.x.ax = 0x10;
	    mi.x.cx = 0;
	    mi.x.dx = 0;
	    mi.x.si = 1000;
	    mi.x.di = 1000;
	    int86(0x33,&mi,&mo);
  }
void SetSpeedThreshold(int threshold)
  {
	    mi.x.ax = 0x13;
	    mi.x.dx = threshold;
	    int86(0x33,&mi,&mo);
  }
#endif
