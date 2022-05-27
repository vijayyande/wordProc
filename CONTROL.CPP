#include <iostream.h>
#include <conio.h>
class Control
{
	public :
		Control();
};
Control::Control()
{
	static int index = 0;
	index++;
}
class Form : public Control
{
		int x1,x2,y1,y2;
		char *caption;
	public :
		void box();

};
void main()
{
	abc s,d;
	s.a();
}

