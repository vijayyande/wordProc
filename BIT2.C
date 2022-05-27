















































































































































































































































#include <stdio.h>
#include <graphics.h>
#include <math.h>
main()
{
   struct BITMAPFILEHEADER
   {
	 int  bfType;
	 long bfSize;
	 int  bfReserved1;
	 int  bfReserved2;
	 long bfOffBits;
   } head;
   struct BITMAPINFOHEADER
   {
	 long biSize;
	 long biWidth;
	 long biHeight;
	 int  biPlanes;
	 int  biBitCount;
	 long biCompression;
	 long biSizeImage;
	 long biXPelsPerMeter;
	 long biYPelsPerMeter;
	 long biClrUsed;
	 long biClrImportant;
   } info;
   struct RGBQUAD
   {
	 char rgbBlue;
	 char rgbGreen;
	 char rgbRed;
	 char rgbReserved;
   };
   struct RGBQUAD color_table[256];
   char bitmap[600];
   FILE *fp;
   char fname[40];
   int i, j, gdriver=DETECT, gmode=EGAHI;
   printf("Give the filename ");
   gets(fname);
   if ((fp = fopen(fname,"rb")) == NULL)
   {
	  printf("Cannot open bmp file\n");
	  exit(0);
   }
   printf("%d\n", fread(&head, 1, sizeof(struct BITMAPFILEHEADER), fp));
   printf("%d\n", fread(&info, 1, sizeof(struct BITMAPINFOHEADER), fp));
   printf("%d\n",fread(color_table, 1, sizeof(struct RGBQUAD) * 256, fp));

   printf("Offset %ld Width %ld Height %ld bit count %d\n",
		   head.bfOffBits, info.biWidth, info.biHeight,
		   info.biBitCount);
   getchar();

   initgraph(&gdriver, &gmode,"");
   for (j=0; j<info.biHeight; j++)
   {
	  fread(bitmap, 1, info.biWidth+1, fp);
	  for (i=0; i<info.biWidth; i++)
	  {
		   putpixel(i,info.biHeight-j,(color_table[bitmap[i]].rgbBlue +
			 color_table[bitmap[i]].rgbRed +
			 color_table[bitmap[i]].rgbGreen));
	  }
   }
   getchar();
   closegraph();
/*   printf("\n\n\n\nPress any key ...");*/

}