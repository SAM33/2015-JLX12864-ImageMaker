#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
using namespace std;

bool mousepushleft;
bool mousepushright;

struct Image
{
	char data[8][128];
};

class JLXLCD
{
	public:
	bool pix[128][64]; //defencr overflow
	int mutipler;
	JLXLCD()
	{
		mutipler=8;
		for(int i=0 ; i<128 ; i++)
			for(int j=0 ; j<64 ; j++)
				pix[i][j]=true;
	}

	void draw()
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

	char booltochar(bool *arr)
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

	void save(char *filename)
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

};


JLXLCD LCD;


static void Repaint()
{
	glutPostRedisplay();
}

static void Draw()
{
	int m = LCD.mutipler;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	LCD.draw();	
	glutSwapBuffers();
}

static void MouseClick(int button,int state,int x,int y)
{
	int shift=0;
	int mw = 128*LCD.mutipler;
        int mh = 64*LCD.mutipler;
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        if(w!=mw || h!=mh)
        {
                x = (float)x/((float)w/(float)mw);
                y = (float)y/((float)h/(float)mh);
        }
        y = 64*LCD.mutipler-y;
	//printf("x=%d y=%d state=%d button=%d\n",x,y,state,button);
	if(x<0 || x>mw || y<0 || y>mh)
		return;
	if(state==1)
	{
		mousepushleft=false;
		mousepushright=false;
	}
	if(state==0)
	{	
		if(button==0)
		{
			mousepushleft=true;
			LCD.pix[x/LCD.mutipler+shift][y/LCD.mutipler+shift]=true;
		}
		if(button==2)
		{
                        mousepushright=true;
                        LCD.pix[x/LCD.mutipler+shift][y/LCD.mutipler+shift]=false;

		}
	}

}

static void MouseMove(int x,int y)
{
	int shift=0;
	int mw = 128*LCD.mutipler;
	int mh = 64*LCD.mutipler;
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	if(w!=mw || h!=mh)
	{
		x = (float)x/((float)w/(float)mw);
	        y = (float)y/((float)h/(float)mh);
	}
	y = 64*LCD.mutipler-y;
        if(x<0 || x>mw || y<0 || y>mh)
                return;
	if(mousepushleft)
		LCD.pix[x/LCD.mutipler+shift][y/LCD.mutipler+shift]=true;
	if(mousepushright)
		LCD.pix[x/LCD.mutipler+shift][y/LCD.mutipler+shift]=false;
}

static void KeyDown(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'c' :
		case 'C' :
		for(int i=0 ; i<128 ; i++)
                for(int j=0 ; j<64 ; j++)
                	LCD.pix[i][j]=false;
		break;
		
		case 'f' :
		case 'F' :
                for(int i=0 ; i<128 ; i++)
                for(int j=0 ; j<64 ; j++)
                        LCD.pix[i][j]=true;
                break;
		
		case 's' :
		case 'S' :
		printf("save...\n");
		LCD.save("newfile.img12864");
		printf("save...ok\n");
		break;

        }
}


int main(int argc, char** argv)
{
	const int w = 128*LCD.mutipler;
	const int h = 64*LCD.mutipler;
	mousepushleft=false;
	mousepushright=false;
	/*  init opengl (glu,glut...)  */
	glutInit(&argc, argv);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(w+2*LCD.mutipler,h+2*LCD.mutipler);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutCreateWindow("JLX12864_ImageMaker");
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,w+2*LCD.mutipler,0,h+2*LCD.mutipler);
	glutIdleFunc(Repaint);
	glutDisplayFunc(Draw);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(KeyDown);
	glutMainLoop(); //nerver return
	return 0;
}

