#include <stdio.h>
#include <conio.h>

void main()
{

   FILE *fp1,*fp2;

   fp1 = fopen("bmp.cpp","rb");
   fp2 = fopen("compress.hmb","w");

   double i;
   float j;

   while( !feof( fp1 ) )
   {

       fread(&i, 8,1,fp1);
       j = (float)i / 32000;
       fwrite(&j,4,1,fp2);
   }

   return;
}
