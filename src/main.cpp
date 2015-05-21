#include <iostream>
#include <stdio.h>
#include <string.h>
#include "JLXLCD.h"

using namespace std;

bool mousepushleft;
bool mousepushright;

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

