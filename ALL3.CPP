#include <stdio.h>
#include <alloc.h>
#include <process.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <mouse.h>
#include <string.h>

//#define ZOOM 3
int ZOOM = 3;

void far*img,far*img1;
int x,y,x1,y1,run=0;

void set_new_colors();
void set_new_colors_1();
void ccolor(unsigned creg, int r, int g, int b);

void main1();
void map();

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

int Height, Width;

main( int argc, char *argv[] )
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
   char bitmap[2000];
   FILE *fp;
   char fname[100] = "";
   int i, j, gdriver=DETECT, gmode=EGAHI, colors;
   int half_width;

   if( argc >= 2 )
   {
		strcpy( fname, argv[1] );
   }
   else
   {
	   printf("Give the filename ");
	   gets(fname);					// Get file bit map file name
   }

   if( ! strstr( fname, ".bmp" ) )
	   strcat( fname, ".bmp" );

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

		   Height = (int) info.biHeight ;   // Extract height and width
		   Width = (int) info.biWidth  ;
   printf("Size %ld X %ld Y %ld\n", info.biSizeImage, info.biXPelsPerMeter, info.biYPelsPerMeter);
   ////////////////////////// Print differant values

   initgraph(&gdriver, &gmode,"\\turbo-c\\bgi");

   half_width = info.biWidth ;

	  map();

		int k;
		int x1 = 70, x2 = 200, y1 = 20, y2 = 150;
		int horiz, vert;
		int tp ;

  while(1)
  {
		tp = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(struct RGBQUAD) * colors);
		fseek( fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(struct RGBQUAD) * colors), SEEK_SET );

   for (j = 0 ; j < info.biHeight ; j++)
   {
	  fread(bitmap, 1, half_width, fp);

	  for ( i = 0, k = 0 ; i < half_width ; i++, k++ )
	  {

		 putpixel( i ,  info.biHeight - j , (unsigned) ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64 );

/*
		 putpixel( i*ZOOM   ,  (info.biHeight - j)*ZOOM , ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64);

		 putpixel( i*ZOOM+1   ,  (info.biHeight - j)*ZOOM , ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64);

		 putpixel( i*ZOOM   ,  (info.biHeight - j)*ZOOM+1 , ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64);

		 putpixel( i*ZOOM+1   ,  (info.biHeight - j)*ZOOM+1 , ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64);
*/

	  }
   }

		gotoxy( 2, 25);
		printf("\nEnter zoomin constant " );
		scanf("%d", &ZOOM );
		if( ZOOM > 10 )
			return 1;

		ShowMouse();
		while( ! Clicked( 0, 0, info.biWidth, info.biHeight ) )
			fflush(stdin);

		x1 = GetMX();
		y1 = GetMY();

		while( Clicked( 0, 0, info.biWidth, info.biHeight ) )
			fflush(stdin);
		x2 = GetMX();
		y2 = GetMY();

		HideMouse();
		cleardevice();

		tp = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(struct RGBQUAD) * colors);
		fseek( fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(struct RGBQUAD) * colors), SEEK_SET );

   for (j = 0 ; j < info.biHeight ; j++)
   {
	  fread(bitmap, 1, half_width, fp );

	  for ( i = 0, k = 0 ; i < half_width ; i++, k++ )
	  {

	  if( i >= x1 && i <= x2 && (info.biHeight - j) >= y1 && (info.biHeight - j) <= y2 )
	  {
		 /*
		 putpixel( i ,  info.biHeight - j , (unsigned) ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64 );
		 */

		tp = ( (color_table[bitmap[i] ].rgbBlue +
				   color_table[bitmap[i] ].rgbRed +
				   color_table[bitmap[i] ].rgbGreen)) / 64 ;

		 if( ZOOM == 2 || ZOOM == 3 )
		 {
			 putpixel( i*ZOOM - x1*ZOOM   ,  (info.biHeight - j)*ZOOM - y1*ZOOM , tp );

			 putpixel( i*ZOOM+1 - x1*ZOOM    ,  (info.biHeight - j)*ZOOM - y1*ZOOM  ,  tp );

			 putpixel( i*ZOOM - x1*ZOOM   ,  (info.biHeight - j)*ZOOM+1 - y1*ZOOM  ,  tp );

			 putpixel( i*ZOOM+1 - x1*ZOOM   ,  (info.biHeight - j)*ZOOM+1 - y1*ZOOM  ,  tp );

		 }

		 if( ZOOM >= 3 )
		 {
			 putpixel( i*ZOOM+2 - x1*ZOOM   ,  (info.biHeight - j)*ZOOM - y1*ZOOM  , tp );

			 putpixel( i*ZOOM+2 - x1*ZOOM   ,  (info.biHeight - j)*ZOOM+1 - y1*ZOOM  , tp );

			 putpixel( i*ZOOM+2 - x1*ZOOM   ,  (info.biHeight - j)*ZOOM+2 - y1*ZOOM  , tp );


			 putpixel( i*ZOOM - x1*ZOOM   ,  (info.biHeight - j)*ZOOM+2 - y1*ZOOM  , tp );

			 putpixel( i*ZOOM+1 - x1*ZOOM   ,  (info.biHeight - j)*ZOOM+2 - y1*ZOOM  , tp );
		 }

	   }

	  }
   }

	 getch();
 }// while
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


void map()
{
   struct palettetype pal;
   int i, ht, y ;

   getpalette(&pal);

   for (i=0; i<pal.size; i++)
	  setrgbpalette( pal.colors[i], i*4, i*4, i*4 );

   /*
   ht = getmaxy() / 16;
   xmax = getmaxx();
   y = 0;
   for (i=0; i<pal.size; i++)
   {
	  setfillstyle(SOLID_FILL, i);
	  bar(0, y, xmax, y+ht);
	  y += ht;
   }
   */
   return ;
}
