#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define thr 12
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

   int i, j, gdriver=DETECT, gmode, GX, GY, colors;
   int z1, z2, z3, z4, z5, z6, z7, z8, z9, half_width;
   float f;
   char fname[40];

   printf("Give the filename -> ");
   fflush(stdin);
   gets(fname);
   if ((fp = fopen(fname,"rb")) == NULL)
   {
	  printf("Cannot open bmp file\n");
	  exit(0);
   }

   fread(&head, 1, sizeof(struct BITMAPFILEHEADER), fp);
   fread(&info, 1, sizeof(struct BITMAPINFOHEADER), fp);
   colors = pow(2, info.biBitCount);
   printf("Width %ld Height %ld Colours %d\n", info.biWidth, info.biHeight,colors);
   fread(color_table, 1, sizeof(struct RGBQUAD) * colors, fp);

   initgraph(&gdriver, &gmode,"\\turbo-c\\bgi");

   half_width = info.biWidth/2;

   fread(prev_bitmap, 1, half_width, fp);
   fread(cur_bitmap, 1, half_width, fp);

   for (j = 1 ; j < info.biHeight - 1; j++)
   {
	  fread(next_bitmap, 1, half_width, fp);
	  for (i=1; i<half_width-1; i++)
	  {
		 z1 = color_table[prev_bitmap[i-1] & 0x0F].rgbBlue +
			  color_table[prev_bitmap[i-1] & 0x0F].rgbRed +
			  color_table[prev_bitmap[i-1] & 0x0F].rgbGreen;
		 z2 = color_table[prev_bitmap[i] & 0xF0].rgbBlue +
			  color_table[prev_bitmap[i] & 0xF0].rgbRed +
			  color_table[prev_bitmap[i] & 0xF0].rgbGreen;
		 z3 = color_table[prev_bitmap[i] & 0x0F].rgbBlue +
			  color_table[prev_bitmap[i] & 0x0F].rgbRed +
			  color_table[prev_bitmap[i] & 0x0F].rgbGreen;
		 z4 = color_table[cur_bitmap[i-1] & 0x0F].rgbBlue +
			  color_table[cur_bitmap[i-1] & 0x0F].rgbRed +
			  color_table[cur_bitmap[i-1] & 0x0F].rgbGreen;
		 z5 = color_table[cur_bitmap[i] & 0xF0].rgbBlue +
			  color_table[cur_bitmap[i] & 0xF0].rgbRed +
			  color_table[cur_bitmap[i] & 0xF0].rgbGreen;
		 z6 = color_table[cur_bitmap[i] & 0x0F].rgbBlue +
			  color_table[cur_bitmap[i] & 0x0F].rgbRed +
			  color_table[cur_bitmap[i] & 0x0F].rgbGreen;
		 z7 = color_table[next_bitmap[i-1] & 0x0F].rgbBlue +
			  color_table[next_bitmap[i-1] & 0x0F].rgbRed +
			  color_table[next_bitmap[i-1] & 0x0F].rgbGreen;
		 z8 = color_table[next_bitmap[i] & 0xF0].rgbBlue +
			  color_table[next_bitmap[i] & 0xF0].rgbRed +
			  color_table[next_bitmap[i] & 0xF0].rgbGreen;
		 z9 = color_table[next_bitmap[i] & 0x0F].rgbBlue +
			  color_table[next_bitmap[i] & 0x0F].rgbRed +
			  color_table[next_bitmap[i] & 0x0F].rgbGreen;
		 GX = 4 * z5 - (z2 + z4 + z6 + z8) ;
		 if (GX <= 0)
			f = 0.0;
		 else
			f = sqrt(GX);
/*		 if (f != 0)
			 printf("(%.2f)",f); */
		 if (f >= thr)
			putpixel(i*2-1,info.biHeight-j,z5);

		 z1 = color_table[prev_bitmap[i] & 0xF0].rgbBlue +
			  color_table[prev_bitmap[i] & 0xF0].rgbRed +
			  color_table[prev_bitmap[i] & 0xF0].rgbGreen;
		 z2 = color_table[prev_bitmap[i] & 0x0F].rgbBlue +
			  color_table[prev_bitmap[i] & 0x0F].rgbRed +
			  color_table[prev_bitmap[i] & 0x0F].rgbGreen;
		 z3 = color_table[prev_bitmap[i+1] & 0xF0].rgbBlue +
			  color_table[prev_bitmap[i+1] & 0xF0].rgbRed +
			  color_table[prev_bitmap[i+1] & 0xF0].rgbGreen;
		 z4 = color_table[cur_bitmap[i] & 0xF0].rgbBlue +
			  color_table[cur_bitmap[i] & 0xF0].rgbRed +
			  color_table[cur_bitmap[i] & 0xF0].rgbGreen;
		 z5 = color_table[cur_bitmap[i] & 0x0F].rgbBlue +
			  color_table[cur_bitmap[i] & 0x0F].rgbRed +
			  color_table[cur_bitmap[i] & 0x0F].rgbGreen;
		 z6 = color_table[cur_bitmap[i+1] & 0xF0].rgbBlue +
			  color_table[cur_bitmap[i+1] & 0xF0].rgbRed +
			  color_table[cur_bitmap[i+1] & 0xF0].rgbGreen;
		 z7 = color_table[next_bitmap[i] & 0xF0].rgbBlue +
			  color_table[next_bitmap[i] & 0xF0].rgbRed +
			  color_table[next_bitmap[i] & 0xF0].rgbGreen;
		 z8 = color_table[next_bitmap[i] & 0x0F].rgbBlue +
			  color_table[next_bitmap[i] & 0x0F].rgbRed +
			  color_table[next_bitmap[i] & 0x0F].rgbGreen;
		 z9 = color_table[next_bitmap[i+1] & 0xF0].rgbBlue +
			  color_table[next_bitmap[i+1] & 0xF0].rgbRed +
			  color_table[next_bitmap[i+1] & 0xF0].rgbGreen;
		 GX = 4 * z5 - (z2 + z4 + z6 + z8) ;
		 if (GX <= 0)
			f = 0.0;
		 else
			f = sqrt(GX);
/*		 if (f != 0)
			 printf("(%.2f)",f); */
		 if (f >= thr)
			putpixel(i*2,info.biHeight-j,z5);
	  }
	  for (i=0; i<half_width; i++)
	  {
		 prev_bitmap[i] = cur_bitmap[i];
		 cur_bitmap[i] = next_bitmap[i];
	  }
   }
/*   printf("\n\n\n\nPress any key ...");*/
}