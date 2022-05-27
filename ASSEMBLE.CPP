#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fcntl.h>
#include <dos.h>
#include <io.h>
#include <string.h>

void main()
{

	 char name[125];
	 char fname[125];
	 char dfile[125];
	 char ext[5] = "0  ";
	 char buffer[500];

	 int parts=0, bytes_read=0, extn = 0;
	 long file_size=0;
	 long each_file_size=0;
	 long ctr = 0;

	 int ip, op; // File Handles

	 clrscr();
	 printf("Enter file name of (.0) extension: ");
	 scanf("%s",name );
	 printf("Enter destination file name : ");
	 scanf("%s", dfile );

	 op = open( dfile, O_BINARY | O_WRONLY | O_CREAT);
	 if( op == -1 )
	 {
		perror("");
		printf("\n\aUnable to open output file. ");
		return;
	 }

	 for( int i = 0 ; name[i] != '.' ; i++);name[++i] = 0;

	 sprintf(ext, "%d", extn );
	 strcpy (fname, name);
	 strcat (fname, ext);
	 printf("\n%s ", fname);

	 ip = open( fname, O_BINARY | O_RDONLY );
	 if( op == 0 )
	 {
		 printf("\n\aUnable to open input file. ");
		 return;
	 }
//	 file_size = filelength(ip);
//	 each_file_size = (long) file_size / parts;

	 while( 1 )
	 {
		  bytes_read = read(ip, buffer, 500);
		  if( eof(ip) )
		  {
			 close(ip);
			 extn++;

			 sprintf(ext, "%d", extn );
			 strcpy (fname, name);
			 strcat (fname, ext);
			 printf("\n%s ", fname);

			 ip = open( fname, O_BINARY | O_RDONLY );
			 if( ip == -1 )
			 {
				 perror("");
				 printf("\n\aInput files over. ");
				 write( op, buffer, bytes_read );
				 close(op);
				 exit(0);
			 }
		  }
		  write( op, buffer, bytes_read );
	 }// End while

	 printf("\nAssembling completed.");
	 printf("\nTotal = %d files assembled.\n", extn+1);
	 close(op);

return;
}
