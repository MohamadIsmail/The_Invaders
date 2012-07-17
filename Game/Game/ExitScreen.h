#ifndef EXITSCREEN_H_ 
#define EXITSCREEN_H_

#include "Screen.h"
#include "TextHelper.h"
#include "IDrawable.h"

class ExitScreen: public Screen, public IDrawable
{
	static const bool is2D = true;
	bool Is2D(){return this->is2D;}
	void Initialize()
	{
		texture = LoadGLTexture("images\\screens\\ExitScreen.bmp");
		counter = 0 ;
	}
	int counter;
	void Draw()
	{
		counter++;
		if(counter >= 2000)
			exit(0);
		glDisable(GL_LIGHTING);
		glClearColor(1,1,1,1);
		glColor3f(1,1,1);
		glScalef(10, 10, 10);
		glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, texture);
		DrawCanvase();
		//char* centerTitle = "Thanks for using Our Game";
		//glColor3f(1,.5,1);
		//TextHelper::DrawString(-30,0, GLUT_BITMAP_TIMES_ROMAN_24, centerTitle);		
		glEnable( GL_LIGHTING );
	}
	void GetKeyboardDownPress(int key)
	{
		if ( key == '\r' )
			exit(0);
	}
	void DrawCanvase()
	{
		glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);
		glVertex2f(-10.f, -10.f);

		glTexCoord2d(1.0,0.0);
		glVertex2f(10.f, -10.f);

		glTexCoord2d(1.0,1.0);
		glVertex2f(10.f, 10.f);

		glTexCoord2d(0.0,1.0);
		glVertex2f(-10.f, 10.f);
		glEnd();
	}
public:
	ExitScreen(){}
};
#endif