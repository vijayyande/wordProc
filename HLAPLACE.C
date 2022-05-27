#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <alloc.h>

#define thr 130

struct node
{
	float intensity ;
	float freq;
	struct node *next;
};

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
   struct node *start = NULL, *temp;
   struct node *insert_node(struct node *, float);
   int inten;
   float total = 0;
   printf("Give the filename ");
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

/*   initgraph(&gdriver, &gmode,""); */

   half_width = info.biWidth/2;

   fread(prev_bitmap, 1, half_width, fp);
   fread(cur_bitmap, 1, half_width, fp);

   for (j=1; j<info.biHeight-1; j++)
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
			 printf("(%.2f)",f);
		 if (f >= thr)
			putpixel(i*2-1,info.biHeight-j,z5); */
		 if (f != 0)
		 {
			start = insert_node(start, floor(f));
			total = total + 1;
		 }
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
			 printf("(%.2f)",f);
		 if (f >= thr)
			putpixel(i*2,info.biHeight-j,z5); */
		 if (f != 0)
		 {
			start = insert_node(start, floor(f));
			total = total + 1;
		 }
	  }
	  for (i=0; i<half_width; i++)
	  {
		 prev_bitmap[i] = cur_bitmap[i];
		 cur_bitmap[i] = next_bitmap[i];
	  }
   }
   printf("Total = %.2f \n", total);
   temp = start;
   while (temp != NULL)
   {
	   printf("(%.2f %.2f)\t", temp->intensity, temp->freq);
	   temp = temp->next;
   }
   getchar();
   initgraph(&gdriver, &gmode,"\\turbo-c\\bgi");
   line(100,50,100,500);
   line(50,450,600,450);
   temp = start ;
   i = 7 ;
   while (temp != NULL)
   {
/*	   gotoxy(100+i, 460); */
	   printf("%.2f ", temp->intensity);
	   line(100+i,450, 100+i, 450 - (temp->freq*2));
	   temp = temp->next ;
	   i = i + 7;
   }
   getchar();
   closegraph();
}

struct node *insert_node(struct node *head, float inten)
{
	struct node *temp_node, *back_node, *curr_node;
	struct node *new_node(void);

	back_node = NULL;
	curr_node = head;
	while (curr_node != NULL && curr_node->intensity > inten)
	{
		back_node = curr_node ;
		curr_node = curr_node->next;
	}
	if (curr_node != NULL && curr_node->intensity == inten)
	   curr_node->freq++;
	else
	{
		temp_node = new_node();
		temp_node->intensity = inten;
		if (back_node == NULL)
		{
		   temp_node->next = head;
		   head = temp_node;
		}
		else
		{
		   back_node->next = temp_node;
		   temp_node->next = curr_node;
		}
	}
	return(head);
}

struct node *new_node()
{
	struct node *temp_node ;
	temp_node = (struct node *) malloc (sizeof(struct node)) ;
	temp_node->freq = 1 ;
	temp_node->next = NULL ;
	return(temp_node);
}