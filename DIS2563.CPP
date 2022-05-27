#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <alloc.h>
#include <process.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <mouse.h>

void far*img,far*img1;
int x,y,x1,y1,run=0;

void set_new_colors();
void set_new_colors_1();
void ccolor(unsigned creg, int r, int g, int b);

void main1();
void far map();

void interrupt (*old)(...);
void interrupt handler(...)
{
  if( run == 0)
  {
    run = 1;
    x = GetMX();y = GetMY();

    if( x != x1 || y != y1)
    {
	putimage(x1,y1,img1,0);

	getimage(x,y,x+34,y+34,img1);
	putimage(x,y,img,1);

    }
    x1 = x;
    y1 = y;
    run = 0;
  }
//  old();
}

main(int argc, char *argv[])
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
   int fp;
   char fname[120] = "\\windows\\winlogo.bmp";
   int  gdriver=DETECT, gmode=EGAHI, colors;

   if( argc < 2)
   {
	  printf("Give the filename ");
	  fflush(stdin);
	  gets(fname);					// Get file bit map file name
   }
   else strcpy(fname, argv[1] );

   if ((fp = open(fname, O_BINARY | O_RDONLY )) == -1)
   {
	  printf("Cannot open bmp file\n");
	  return 1;
   }

	 printf("%d\n", read(  fp,  &head, sizeof(struct BITMAPFILEHEADER) ));
	 /**********  Get file header from file ********/

	 printf("%d\n", read( fp, &info, sizeof(struct BITMAPINFOHEADER) ));
	 /**********  Get Bitmap Header  **************/

	 colors = pow(2, info.biBitCount);	// BitMap of how much colors ?

   printf("%d\n", read( fp, color_table, sizeof(struct RGBQUAD) * colors ));
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

   if( getch() == 27 )
		return 0;

   for(int j = 0 ; j < info.biHeight ; j++)
   {
 
	  read( fp, bitmap, (size_t)info.biWidth + 3);

	  for ( int i = 0 ; i < info.biWidth  ; i++)
	  {

		 putpixel( i ,  info.biHeight - j , (unsigned) ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64 );

/*		 putpixel( i ,  info.biHeight - j , (unsigned) ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64 );
*/
				   // Division by 64 is very important

	  }
   }

 getch();
 return 0;
}


void main1()
{

//    InitGraph();

//    line( 12,0,12,24);
//    line( 0,12,24,12);

    img  = farmalloc(imagesize(0,0,34,34));
    img1 = farmalloc(imagesize(0,0,34,34));

	getimage(0,0,34,34,img);

       settextstyle(4,0,10);
       outtextxy(50,100,"Vijay");
       bar(100,300,500,400);

    old = getvect(0x1c);
    setvect(0x1c,handler);

    getchar();

 return;
}


void ccolor(unsigned creg, int r, int g, int b)
{
   _AH = 0x10;
   _AL = 0x10;
   _BX = creg;
   _CH = g;
   _CL = b;
   _DH = r;

   geninterrupt(0x10);
}

void set_new_colors()
{
	   ccolor(BLACK  , 0x00, 0x00, 0x00);
	   ccolor(BLUE   , 0x2a, 0x00, 0x00);
	   ccolor(GREEN  , 0x00, 0x2a, 0x00);
	   ccolor(CYAN   , 0x2a, 0x2a, 0x00);
	   ccolor(RED    , 0x00, 0x00, 0x2a);
	   ccolor(MAGENTA, 0x2a, 0x00, 0x2a);
	   ccolor(BROWN  , 0x00, 0x15, 0x2a);
	   ccolor(WHITE  , 0x2a, 0x2a, 0x2a);
	   ccolor(DARKGRAY   , 0x15, 0x15, 0x15);

	   ccolor(LIGHTBLUE , 0x3f, 0x15, 0x15);
	   ccolor(LIGHTGREEN, 0x15, 0x3f, 0x15);
	   ccolor(LIGHTCYAN , 0x3f, 0x3f, 0x15);
	   ccolor(LIGHTRED  , 0x15, 0x15, 0x3f);
	   ccolor(LIGHTMAGENTA, 0x3f, 0x15, 0x3f);
	   ccolor(YELLOW, 0x15, 0x3f, 0x3f);
	   ccolor(WHITE, 0x3f, 0x3f, 0x3f);

}

void set_new_colors_1()
{
/*
	   setrgbpalette(BLACK  , 0x00, 0x00, 0x00);
	   setrgbpalette(BLUE   , 0x2a, 0x00, 0x00);
	   setrgbpalette(GREEN  , 0x00, 0x2a, 0x00);
	   setrgbpalette(CYAN   , 0x2a, 0x2a, 0x00);
	   setrgbpalette(RED    , 0x00, 0x00, 0x2a);
	   setrgbpalette(MAGENTA, 0x2a, 0x00, 0x2a);
	   setrgbpalette(BROWN  , 0x00, 0x15, 0x2a);
	   setrgbpalette(WHITE  , 0x2a, 0x2a, 0x2a);
	   setrgbpalette(DARKGRAY   , 0x15, 0x15, 0x15);

	   setrgbpalette(LIGHTBLUE , 0x3f, 0x15, 0x15);
	   setrgbpalette(LIGHTGREEN, 0x15, 0x3f, 0x15);
	   setrgbpalette(LIGHTCYAN , 0x3f, 0x3f, 0x15);
	   setrgbpalette(LIGHTRED  , 0x15, 0x15, 0x3f);
	   setrgbpalette(LIGHTMAGENTA, 0x3f, 0x15, 0x3f);
	   setrgbpalette(YELLOW, 0x15, 0x3f, 0x3f);
	   setrgbpalette(WHITE, 0x3f, 0x3f, 0x3f);

*/

	   setrgbpalette(0 , 0x0000, 0x0000, 0x0000);
	   setrgbpalette(1 , 0x2a00, 0x0000, 0x0000);
	   setrgbpalette(2 , 0x0000, 0x2a00, 0x0000);
	   setrgbpalette(3 , 0x2a00, 0x2a00, 0x0000);
	   setrgbpalette(4 , 0x0000, 0x0000, 0x2a00);
	   setrgbpalette(5 , 0x2a00, 0x0000, 0x2a00);
	   setrgbpalette(6 , 0x0000, 0x1500, 0x2a00);
	   setrgbpalette(7 , 0x2a00, 0x2a00, 0x2a00);
	   setrgbpalette(8 , 0x1500, 0x1500, 0x1500);

	   setrgbpalette(9 , 0x3f00, 0x1500, 0x1500);
	   setrgbpalette(10, 0x1500, 0x3f00, 0x1500);
	   setrgbpalette(11, 0x3f00, 0x3f00, 0x1500);
	   setrgbpalette(12, 0x1500, 0x1500, 0x3f00);
	   setrgbpalette(13, 0x3f00, 0x1500, 0x3f00);
	   setrgbpalette(14, 0x1500, 0x3f00, 0x3f00);
	   setrgbpalette(15, 0x3f00, 0x3f00, 0x3f00);

}


void far map()
{
   struct palettetype pal;

   getpalette(&pal);

   for (int i=0; i<pal.size; i++)
	  setrgbpalette(pal.colors[i], i*4, i*4, i*4);

   return ;
}
