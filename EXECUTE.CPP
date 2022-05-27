#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <dos.h>
#include <conio.h>

void main()
{
	int exe, ovl, main_exe, op;
	char buffer[1000];

	exe = open("C:\\foxpro.exe", O_RDONLY | O_BINARY );
	ovl = open("C:\\foxpro.ovl", O_RDONLY | O_BINARY );
	if( exe == -1 || ovl == -1 )
	{
		printf("\n\aUnable to open input files.");
		return;
	}
	main_exe = open("main_exe.exe", O_RDONLY | O_BINARY );
	if( main_exe == -1)
	{
		printf("\nUnable to open input file.");
		return;
	}

	op = open("d:\\exe.exe", O_CREAT | O_WRONLY | O_BINARY );
	if( op == -1)
	{
		 printf("\nunable to open output file");
		 return;
	}
	////////////////////////////////////////////////////////
	int bytes_read = 0;
	printf("\nmain_exe");
	while( ! eof(main_exe) )
	{
		bytes_read = read(main_exe, buffer, 1000);
		write( op, buffer, bytes_read);
	}

	printf("\nexe");
	while( ! eof(exe) )
	{
		bytes_read = read(exe, buffer, 1000);
		write( op, buffer, bytes_read);
	}

	printf("\novl");
	while( ! eof(ovl) )
	{
		bytes_read = read(ovl, buffer, 1000);
		write( op, buffer, bytes_read);
	}
return;
}
// See GO.CPP