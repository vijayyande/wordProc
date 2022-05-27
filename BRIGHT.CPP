#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <process.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <mouse.h>

void far map();

void main(int argc, char *argv[])
{
   struct BITMAPFILEHEADER  			// File Header
   {
	 int  bfType;
	 long bfSize;
	 int  bfReserved1;
	 int  bfReserved2;
	 long bfOffBits;
   } head;
   struct BITMAPINFOHEADER  			// BitMap Header
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
   struct RGBQUAD    				// color description
   {
	 char rgbBlue;
	 char rgbGreen;
	 char rgbRed;
	 char rgbReserved;
   };
   struct RGBQUAD color_table[256];
   char bitmap[1000];
   FILE *fp;
   char fname[120] = "\\windows\\winlogo.bmp";
   int  gdriver=DETECT, gmode=EGAHI, colors;

   if( argc < 2)
   {
	  printf("Give the filename ");
	  fflush(stdin);
	  gets(fname);					// Get file bit map file name
   }
   else strcpy(fname, argv[1] );

   if ((fp = fopen(fname,"rb")) == NULL)
   {
	  printf("Cannot open bmp file\n");
	  exit(0);
   }

	 printf("%d\n", fread(&head, 1, sizeof(struct BITMAPFILEHEADER), fp));
	 /**********  Get file header from file ********/

	 printf("%d\n", fread(&info, 1, sizeof(struct BITMAPINFOHEADER), fp));
	 /**********  Get Bitmap Header  **************/

	 colors = pow(2, info.biBitCount);	// BitMap of how much colors ?

   printf("%d\n",fread(color_table, 1, sizeof(struct RGBQUAD) * colors, fp));
   /**** Read the color values [ colors * sizeof( struct RGBQUAD ) ] ******/

   printf("Offset %ld Width %ld Height %ld bit count %d colors %d\n",
		   head.bfOffBits, info.biWidth, info.biHeight,
		   info.biBitCount, colors);
   printf("Size %ld X %ld Y %ld\n", info.biSizeImage, info.biXPelsPerMeter, info.biYPelsPerMeter);
   printf("\ Size %ld    Width %ld    Height %ld   Compression %ld ",  info.biSize, info.biWidth, info.biHeight, info.biCompression );
   printf("\n Clrused %ld \t  Clrimportant %ld ", info.biClrUsed, info.biClrImportant);
   getch();
   ////////////////////////// Print image parameters values

   initgraph(&gdriver, &gmode,"c:\\turbo-c\\bgi");

	  map();   // important function call

   unsigned cl;
   int br;
   printf("\nEnter brightness value : ");
   scanf( "%d", &br );

   for(int j = 0 ; j < info.biHeight ; j++)
   {
	  fread(bitmap, (size_t)info.biWidth, 1, fp);
	  for ( int i = 0 ; i < info.biWidth ; i++)
	  {
		 cl = (unsigned) ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64  ;

		 if( br > 0 )
		 {
			 cl += br;
			 if( cl > 12 )
				cl = 12;
		 }

		 if( br < 0 )
		 {
			 cl += br;
			 if( cl < 3 )
				cl = 1;
		 }

		 putpixel( i ,  info.biHeight - j , cl );

	  }
   }

 getch();
 return ;
}


void far map()
{
   struct palettetype pal;
   getpalette(&pal);

   for ( int i = 0 ; i < pal.size ; i++)
	  setrgbpalette( pal.colors[i], i*4, i*4, i*4 );

   return ;
}
