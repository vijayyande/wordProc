#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <io.h>

void main()
{
   int ip, op;
   char buf[300];
   unsigned bread=0, ind=0, i,j;
   long btoread=0;

   ip = open("\\dos\\scandisk.exe", O_RDONLT | O_BINARY );
   if( ip == 0 )
   {
	   printf("\nunable to open input files. ");
	   return;
   }
   op = open("\\scan.exe", O_WRONLY | O_CREAT | O_BINARY );
   {
	   printf("Destination not found. ");
	   return;
   }

   btoread = filelength(ip);
   ind = (int) btoread / 15;

   while( ! eof(ip) )
   {
	   bread = read(ip, buf, 500);
	   i += bread;
	   if( i >= ind )
	   {


