#include <stdio.h>
#include <iostream.h>
#include <conio.h>



class DATE
{
   protected :

		 unsigned char day;
		 unsigned char month;
		 unsigned year;

  public :

	  DATE();
	  DATE(char d, char m, unsigned y);
	 ~DATE();
	  void   say( char c = '/' );
	  DATE   operator=(DATE &d);
	  DATE   operator++();
	  int    operator==(DATE &d);
	  int    operator< (DATE &d);
	  DATE   operator--();
	  friend ostream& operator<< ( ostream& os,DATE& b);
	  int    operator> (DATE &d);
	  DATE&  operator+=( unsigned d);
	  DATE&  operator+=( int d);
	  DATE&  operator+=( DATE &d);
	  int    operator!=( DATE& d);
	  DATE&  operator+( int d);//not working


};//========================================================

void DATE::DATE()
{
	day = 1;
	month = 1;
	year = 2000;
}
void DATE::~DATE(){   }

void DATE::DATE(char d, char m, unsigned y)
{
	  day = d;
	  month = m;
	  year = y;
}

void DATE::say( char c )
{
	 printf("%d%c%d%c%u",day, c, month, c, year);
}

DATE DATE::operator=(DATE &d)
{
	day = d.day;
	month = d.month;
	year = d.year;
}

DATE DATE::operator++()
{
   if( (day == 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)  )
   {
	   day = 1;
	   if( month == 12)
	   {
		   month = 1;
		   year++;
	   }
	   else month++;
	   return *this;
   }

   if( (day == 30) && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) )
   {
	   day = 1;
	   if( month == 12)
	   {
		   month = 1;
		   year++;
	   }
	   else month++;
	   return *this;
   }

   if( (year % 4 != 0) && (month == 2) && (day == 28) )
   {
	   day = 1;
	   month++;
	   return *this;
   }

   if( (year % 4 == 0) && (month == 2) && (day == 28) )
   {
		day++;
		return *this;
   }

   if( (day == 29) && (month == 2) && (year % 4 == 0) )
   {
	   day = 1;
	   month++;
	   return *this;
   }
	 day++;
	 return *this;
}

int DATE::operator==(DATE &d)
{
   return( (year == d.year) && ( month == d.month) && (day == d.day) );
}

DATE DATE::operator--()
{
	 if(  day == 1 )
	 {
		if( month == 1)
		{
		   month = 12;
		   year--;
		}
	 }
	 else day--;
	 return *this;
}

ostream& operator<< (ostream& os, DATE &d)
{
   if( (d.day > 9) && (d.month > 9) )
		printf("%d/%d/%u", d.day, d.month, d.year );
   if( (d.day < 10) && (d.month < 10) )
		printf("0%d/0%d/%u",d.day, d.month, d.year );
   if( (d.day < 10) && (d.month > 10) )
		printf("0%d/%d/%u",d.day, d.month, d.year );
   if( (d.day > 10) && (d.month < 10) )
		printf("%d/0%d/%u",d.day, d.month, d.year );

   return os;
}
int DATE::operator< (DATE &d)
{
	if( year < d.year )
		return 1;
	else if ( month < d.month )
		 return 1;
	else if( day < d.day )
		 return 1;
	else return 0;
}

int  DATE::operator> ( DATE &d)
{
   if( year > d.year )
	   return 1;
   else if ( month > d.month )
		return 1;
   else if ( day > d.day )
		return 1;
   else return 0;
}

DATE&  DATE::operator+= ( unsigned d)
{
   for( int i = 0 ; i < d ; i++ )
   {
		(*this)++;
   }
   return *this;
}
DATE&  DATE::operator+= ( int d)
{
	return ((*this)++);
}

DATE& DATE::operator+= ( DATE& d)
{
	while ( (*this) != d )
			(*this)++;
	return  (*this);
}

int DATE::operator!=( DATE& d)
{
   if( (year != d.year) && (month != d.month) && (day != d.day) )
		return 1;
   else return 0;
}

DATE& DATE::operator+( int d)
{
	int i = 0;
	while ( i < d )
		(*this) = (*this)++;
  return *this;
}

void main()
{
  DATE d1,  d2(31,12,1992);

  clrscr();
  d1.say();
  printf("\n");
  d2.say();

  d1 = d2;
  cout << endl;

  d1.say();
  cout << endl;

  d1++;
  cout << endl;
  d1.say();

  d1--;

  cout << endl << d1 << "\t" << d2;

  printf("\ncomparison \t %d %d %d ", (d1 == d2), (d1 < d2), d1 > d2);

  cout << endl << d2 << endl;
  cout << d1;

  DATE d3(1, 1, 1997);

  for( int i = 0 ; i < 1000 ; i++)
  {
	  d3++;
	  cout << endl ;//<< d3;
	  d3.say('-');
	  if( i % 24 == 0)
		 getch();
  }
return;
}
