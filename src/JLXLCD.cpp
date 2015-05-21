#include "JLXLCD.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
JLXLCD::JLXLCD()
{
    mutipler=8;
    for(int i=0 ; i<128 ; i++)
        for(int j=0 ; j<64 ; j++)
            pix[i][j]=true;
}

JLXLCD::~JLXLCD()
{

}



void JLXLCD::draw()
{
    glBegin(GL_POINTS);
	for(int i=1 ; i<=128 ; i++)
        for(int j=1 ; j<=64 ; j++)
        {
            if(pix[i-1][j-1])
            {
				int x,y;
				x=i*mutipler;
				y=j*mutipler;
				for(int w=0 ; w<mutipler ; w++)
					for(int h=0 ; h<mutipler ; h++)
					{
						glVertex2d(x+w,y+h);
					}	
						//glVertex2d(x,y);
						//glVertex2d(x,y+mutipler-1);
						//glVertex2d(x+mutipler-1,y);
						//glVertex2d(x+mutipler-1,y+mutipler-1);		
			}	
		}
	    glEnd();
}


char JLXLCD::booltochar(bool *arr)
{
                //0x     A       B
		//    1 2 3 4 5 6 7 8
                //
                //    arr[7]  8  
                //    arr[6]  7
                //    arr[5]  6
                //    arr[4]  5
                //    arr[3]  4
                //    arr[2]  3
                //    arr[1]  2
                //    arr[0]  1


		char temp = 0x00;
		if(arr[0])
			temp|=0x80;
		if(arr[1])
			temp|=0x40;
		if(arr[2])
			temp|=0x20;
		if(arr[3])	
			temp|=0x10;
		if(arr[4])
			temp|=0x08;
		if(arr[5])
			temp|=0x04;
		if(arr[6])
			temp|=0x02;
		if(arr[7])
			temp|=0x01;
		return temp;
}

void JLXLCD::save(char *filename)
{
	FILE *f = fopen(filename,"wb");
	struct Image temp;
	bool arr[8];
	unsigned char line[128];
	int shift=0;
	for(int i=0 ; i<8 ; i++)
	{
		for(int j=0 ; j<128 ; j++)
		{
			for(int k=0 ; k<8 ; k++)
			{
				arr[k]=pix[j][k+shift];
			}
			line[j]=booltochar(arr);
		}
		shift+=8;
		memcpy(temp.data[8-i-1],line,128);
	}

		
	for(int i=0 ; i<8 ; i++)
	{
		for(int j=0 ; j<128 ; j++)
		{
			fwrite(&temp.data[i][j],1,1,f);
		}
	}

	fclose(f);
}


