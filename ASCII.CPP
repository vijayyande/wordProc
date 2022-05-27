#include <conio.h>
#include <stdio.h>

void main()
{
   char a,b;
   printf("Hit a key ");
   a = getch();
   b = getch();
   clrscr();
   printf("\t%d\t\t\a%d\t",a,b);
}