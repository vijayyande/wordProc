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

int ShowBitmap(char *argv)
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

   strcpy( fname, "C:\\temp\\");
   strcat( fname, argv );

   if ((fp = fopen(fname,"rb")) == NULL)
   {
	  printf("Cannot open bmp file\n %s ", fname );
	  getch();
	  return 1;
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
   ////////////////////////// Print image parameters values

   //initgraph(&gdriver, &gmode,"c:\\turbo-c\\bgi");

   union REGS ip;
   unsigned clr;

   map();   // important function call
	  // check for extra bytes to read
	  int eb = 0, ans = 0;
	  if( (info.biWidth * info.biHeight) != info.biSizeImage )
	  {
			ans = info.biSizeImage - ( info.biWidth * info.biHeight ) ;
			eb = ans / info.biHeight ;
	  }


   for(int j = 0 ; j < info.biHeight ; j++)
   {
	  fread(bitmap, (size_t)info.biWidth + eb, 1, fp);
	  for ( int i = 0 ; i < info.biWidth ; i++)
	  {
 /*		 putpixel( i ,  info.biHeight - j , (unsigned) ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 128 );
*/

	  clr = (unsigned) ( (color_table[bitmap[i] ].rgbBlue + color_table[bitmap[i] ].rgbRed + color_table[bitmap[i] ].rgbGreen)) / 128 ;
	  ip.h.ah = 0x0C;
	  ip.h.al = clr;
	  ip.h.bh = 0;
	  ip.x.cx = i ;
	  ip.x.dx = info.biHeight-j ;

	  int86(0x10, &ip, &ip);

				   if( kbhit() )
				   {
						fclose( fp );
						return 1;
				   }

	  }
   }
   fclose( fp );
 closegraph();
 return 0;
}


void far map()
{

   union REGS ip;
   ip.h.ah = 0x00;
   ip.h.al = 0x12;

   int86(0x10, &ip, &ip);
	//getpalette(&pal);

   for ( int i = 0 ; i < 16 ; i++)
   {
	  //setrgbpalette( pal.colors[i], i*4, i*4, i*4);


	  int c = 9 ;
	  ip.h.ah = 0x10;
	  ip.h.al = 0x10;
	  ip.x.bx = i  ;
	  ip.h.ch = i * c;
	  ip.h.cl = i * c;
	  ip.h.dh = i * c;
	  //ip.h.dl = i * c;

	  int86( 0x10, &ip, &ip );

   }

   return ;
}
