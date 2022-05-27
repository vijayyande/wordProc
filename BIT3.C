#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define thr 6
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
   char cur_bitmap[600];
   char prev_bitmap[600];
   char next_bitmap[600];
   FILE *fp, *fpout;
   int i, j, gdriver=DETECT, gmode, GX, GY;
   int z1, z2, z3, z4, z5, z6, z7, z8, z9;
   float f;
   char fname[40];
   printf("Give the filename ");
   gets(fname);
   if ((fp = fopen(fname,"rb")) == NULL)
   {
	  printf("Cannot open bmp file\n");
	  exit(0);
   }
   fread(&head, 1, sizeof(struct BITMAPFILEHEADER), fp);
   fread(&info, 1, sizeof(struct BITMAPINFOHEADER), fp);
   fread(color_table, 1, sizeof(struct RGBQUAD) * 256, fp);

   initgraph(&gdriver, &gmode,"\\turbo-c\\bgi");

   fread(prev_bitmap, 1, info.biWidth, fp);
   fread(cur_bitmap, 1, info.biWidth, fp);

   for (j=1; j<info.biHeight-1; j++)
   {
	  fread(next_bitmap, 1, info.biWidth+1, fp);
	  for (i=1; i<info.biWidth; i++)
	  {
		 z1 = color_table[prev_bitmap[i-1]].rgbBlue +
			  color_table[prev_bitmap[i-1]].rgbRed +
			  color_table[prev_bitmap[i-1]].rgbGreen;
		 z2 = color_table[prev_bitmap[i]].rgbBlue +
			  color_table[prev_bitmap[i]].rgbRed +
			  color_table[prev_bitmap[i]].rgbGreen;
		 z3 = color_table[prev_bitmap[i+1]].rgbBlue +
			  color_table[prev_bitmap[i+1]].rgbRed +
			  color_table[prev_bitmap[i+1]].rgbGreen;
		 z4 = color_table[cur_bitmap[i-1]].rgbBlue +
			  color_table[cur_bitmap[i-1]].rgbRed +
			  color_table[cur_bitmap[i-1]].rgbGreen;
		 z5 = color_table[cur_bitmap[i]].rgbBlue +
			  color_table[cur_bitmap[i]].rgbRed +
			  color_table[cur_bitmap[i]].rgbGreen;
		 z6 = color_table[cur_bitmap[i+1]].rgbBlue +
			  color_table[cur_bitmap[i+1]].rgbRed +
			  color_table[cur_bitmap[i+1]].rgbGreen;
		 z7 = color_table[next_bitmap[i-1]].rgbBlue +
			  color_table[next_bitmap[i-1]].rgbRed +
			  color_table[next_bitmap[i-1]].rgbGreen;
		 z8 = color_table[next_bitmap[i]].rgbBlue +
			  color_table[next_bitmap[i]].rgbRed +
			  color_table[next_bitmap[i]].rgbGreen;
		 z9 = color_table[next_bitmap[i+1]].rgbBlue +
			  color_table[next_bitmap[i+1]].rgbRed +
			  color_table[next_bitmap[i+1]].rgbGreen;
		 GX = (z7 + 2 * z8 + z9) - (z1 + 2 * z2 + z3);
		 GY = (z3 + 2 * z6 + z9) - (z1 + 2 * z4 + z7);
		 if ((GX*GX)+(GY*GY) <= 0)
			f = 0.0;
		 else
			f = sqrt(GX*GX + GY*GY*1.0);
/*		 printf("(%.2f)",f);*/
		 if (f >= thr)
			putpixel(i,info.biHeight-j,z5);
	  }
	  for (i=0; i<info.biWidth; i++)
	  {
		 prev_bitmap[i] = cur_bitmap[i];
		 cur_bitmap[i] = next_bitmap[i];
	  }
   }
   getchar();
   closegraph();
/*   printf("\n\n\n\nPress any key ...");*/
}