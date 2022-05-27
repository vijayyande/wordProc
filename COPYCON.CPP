#include <stdio.h>
#include <string.h>
#include <conio.h>

void main()
{
   FILE *fp;
   char fn[80],c;


   printf("\nEnter File name : ");
   scanf("%s",fn);

   fp = fopen(fn,"w");

   while( c != 26 )
     {
        c = getche();
        fn[0] = c;
        gets(&fn[1]);

        str
        fputs( fn , fp);
     }
}


