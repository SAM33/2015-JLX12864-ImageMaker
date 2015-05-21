#ifndef _JLXLCD_H_
#define _JLXLCD_H_
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
struct Image
{
	char data[8][128];
};


class JLXLCD
{
	public:
	bool pix[128][64]; //defencr overflow
	int mutipler;
	JLXLCD();
	~JLXLCD();
	void draw();
	char booltochar(bool *arr);
	void save(char *filename);
	

};


#endif