#ifndef _JLXLCD_H_
#define _JLXLCD_H_

#ifdef _WIN32
#   error "unsupport compiler"
#elif __APPLE__
        #include <GLUT/glut.h>
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
#elif __linux__
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#elif __unix__ // all unices not caught above
#   error "unsupport compiler"
#elif defined(_POSIX_VERSION)
#   error "unsupport compiler"
#else
#   error "Unknown compiler"
#endif





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
