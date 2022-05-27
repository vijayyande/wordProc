#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <mouse.h>

void far*img,far*img1;
int x,y,x1,y1,run=0;

void main1();

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

	getimage(x,y,x+24,y+24,img1);
	putimage(x,y,img,1);

    }
	//putimage(x,y,img,0);

    x1 = x;
    y1 = y;
    run = 0;
  }
  old();
}

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
   char bitmap[2000];
   FILE *fp;
   char fname[40] = "\\windows\\winlogo.bmp";
   int i, j, gdriver=DETECT, gmode=EGAHI, colors;
   int half_width;
   unsigned MUL;

   printf("Give the filename ");
   gets(fname);

   if ((fp = fopen(fname,"rb")) == NULL)
   {
	  printf("Cannot open bmp file\n");
	  exit(0);
   }

   printf("%d\n", fread(&head, 1, sizeof(struct BITMAPFILEHEADER), fp));
   printf("%d\n", fread(&info, 1, sizeof(struct BITMAPINFOHEADER), fp));
   colors = pow(2, info.biBitCount);

   printf("%d\n",fread(color_table, 1, sizeof(struct RGBQUAD) * colors, fp));

   printf("Offset %ld Width %ld Height %ld bit count %d colors %d\n",
		   head.bfOffBits, info.biWidth, info.biHeight,
		   info.biBitCount, colors);
   printf("Size %ld X %ld Y %ld\n", info.biSizeImage, info.biXPelsPerMeter, info.biYPelsPerMeter);
   getch();

   initgraph(&gdriver, &gmode,"\\turbo-c\\bgi");

   half_width = info.biWidth / 2;

   for( MUL = 0x00 ; MUL <= 0xFF ; MUL++)
   for (j = 0 ; j < info.biHeight ; j++)
   {
	  fread(bitmap, 1, half_width, fp);
	  for (i = 0 ; i < half_width ; i++)
	  {
	     putpixel( i * 2 - 1,  info.biHeight - j ,  ( color_table[bitmap[i] & 0xF0].rgbBlue +
				   color_table[bitmap[i] & 0xF0].rgbRed +
				   color_table[bitmap[i] & 0xF0].rgbGreen));

	     putpixel( i * 2    ,  info.biHeight - j ,  (color_table[bitmap[i] & 0x0F].rgbBlue +
				   color_table[bitmap[i] & 0x0F].rgbRed +
				   color_table[bitmap[i] & 0x0F].rgbGreen));


	  }
   }
   getch();
    settextstyle(4,0,6);
    outtextxy(50,100,"Jai Bajarang Bali");
   main1();

 return;
}


void main1()
{

//    InitGraph();

    line( 12,0,12,24);
    line( 0,12,24,12);

    img  = farmalloc(imagesize(0,0,24,24));
    img1 = farmalloc(imagesize(0,0,24,24));

    getimage(0,0,24,24,img);

       settextstyle(4,0,10);
       outtextxy(50,100,"Vijay");
       bar(100,300,500,400);

    old = getvect(0x1c);
    setvect(0x1c,handler);

    getchar();

 return;
}