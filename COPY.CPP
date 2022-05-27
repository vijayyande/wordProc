#include <alloc.h>
#include <stdio.h>
#include <conio.h>
#include <fcntl.h>
#include <io.h>

int main(void)
{
   int handle,hdl;
   char msg[] = "Hello world";
   char buf[1000],fn1[125],fn2[125];
   long filesize;
   long bkread = 0;
   int times = 0,col = 10;

   long buffersize;
   char buffer[1000];

   clrscr();

   printf("Enter Source file path & name : ");
   scanf("%s",fn1);
   printf("Enter destination file path & name ");
   scanf("%s",fn2);

   filesize = filelength(handle);
   buffersize = (long) filelength / 10 ;
    buffer = (char *)farmalloc(buffersize);

   if ((handle = open(fn1, O_RDONLY | O_BINARY)) == -1)
   {
      perror("Error:");
      return 1;
   }
   if ((hdl = open(fn2, O_CREAT | O_BINARY)) == -1)
   {
      perror("Error:");
      return 1;
   }

     while( !eof(handle))
     {
	   read(handle, buffer, buffersize);
	   write(hdl, buffer, buffersize);
     }

     printf("times %d ",times);
   close(handle);
   close(hdl);

   return 0;
}
