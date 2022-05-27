#include <dos.h>
#include <conio.h>
#include <stdio.h>

void main()
{
	double input;
	double  output1 ;
	double  output2 ;
	double  output3 ;
	double  output4 ;
	double  output5 ;
	double div = (double)999999999;
	float output ;

	FILE  *ip, *op;

	ip = fopen( "bte.txt", "rb" );
	if( ip == NULL )
	{
		printf("\n Input file not found! ");
		return ;
	}
	op = fopen( "bte.tp", "wb" );
	if( op == NULL )
	{
		printf("\nUnable to open destination file.");
		return ;
	}

	clrscr();
	while( ! feof( ip ) )
	{
		fread( &input, sizeof( double ), 1, ip );

		output1 = input   / div ;
		output2 = output1 / div ;
		output3 = output2 / div ;
		output4 = output3 / div ;
		output5 = output4 / div ;

		output = output5 / div;

		//printf("\n%ld\t\t%f", input, output  );

		fwrite( &output, sizeof( float ), 1, op );

	}

	fclose( ip );
	fclose( op );

return;
}

