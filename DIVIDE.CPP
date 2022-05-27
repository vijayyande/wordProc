#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <dos.h>

void main()
{
  int ip, op1, op2, op;
  long file_size, size=0;
  char buffer[100];
  char ext[4], name[125];
  int exts=0;
  int bytes_read, parts=0;
  ldiv_t abc;
  char file_name_given[125];
  char file_name[125];


  clrscr();

  printf("\nEnter file name : ");
  scanf("%s",file_name_given);
  printf("\nEnter how many parts to make : ");
  scanf("%d", &parts);

  ip = open( file_name_given, O_RDONLY | O_BINARY );
  if( ip == 0)
  {
	 printf("\nUnable to open input file. ");
	 return;
  }

  strcpy(ext, "0  ");
  for( int t = 0 ; file_name_given[t] != '.' ; t++)
	   name[t] = file_name_given[t];
	   name[t] = '.';
	   name[++t] = 0;
  strcpy(file_name, name);

  for( int s = 0 ; s < 3 ;s++,t++)
	   file_name[t] = ext[s];

  strcat(file_name, ext);
  printf("%s", file_name);

  op = open(  file_name, O_CREAT | O_BINARY | O_WRONLY );


  if( op == 0 )
  {
	  printf("\nUnable to open output files. ");
	  return;
  }

  file_size = filelength(ip);
  abc = ldiv(file_size, parts);
  file_size = abc.quot;

  while( ! eof(ip) )
  {
	 bytes_read = read(ip, buffer, 100);
	 size += bytes_read;

	 if( size >= file_size )
	 {
		close(op);
 /*		for( int t = 0 ; file_name_given[t] != '.' ; t++)
			name[t] = file_name_given[t];
			name[t] = '.';
			name[++t] = 0;
			strcpy( file_name, name);*/

		 exts++;
		 sprintf(ext, "%s", exts);
		 strcat(file_name, ext);
		 printf("\n%s", file_name);

		op = open(file_name, O_CREAT | O_BINARY | O_WRONLY );
	 }
	 else
		write( op, buffer, bytes_read );
  }
  close(ip);
  close(op);

  printf("\nOperation completed. ");
return;
}
