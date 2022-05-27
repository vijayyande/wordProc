#include<stdio.h>
#include<conio.h>
void add();// declaration
void sub();// declaration
void mult();// declaration
void div(); // declaration
void main()
{
	clrscr();
	add(); // call
	sub();//call
	mult();//call
	div();//call
}
void add()// definition
{
	int a,b,c;// local variables
	printf("\nEnter a number");
	scanf("%d",&a);
	printf("\nEnter a number");
	scanf("%d",&b);
	c = a + b;
	printf("%d",c);
	getch();
}
void sub() // definition
{
	int a,b,d;//local variables
	printf("\nEnter a number");
	scanf("%d",&a);
	printf("\nEnter a number");
	scanf("%d",&b);
	d = a - b;
	printf("%d",d);
	getch();
}
void mult() //definition
{      int a,b,e;//local variables
	 printf("\nEnter a number");
	scanf("%d",&a);
	printf("\nEnter a number");
	scanf("%d",&b);
	e = a * b;
	printf("%d",e);
	getch();
}
void div () //definition
{
   int a,b,f;//local variables
	 printf("\nEnter a number");
	scanf("%d",&a);
	printf("\nEnter a number");
	scanf("%d",&b);
	f = a / b;
	printf("%d",f);
	getch();
}