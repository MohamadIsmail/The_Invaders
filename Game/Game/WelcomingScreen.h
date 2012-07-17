#ifndef WELCOMINGSCREEN_H_
#define WELCOMINGSCREEN_H_

#include "AllIncludes.h"
#include <windows.h>
#include "Screen.h"
#include "IDrawable.h"
#include "IntroductionScreen.h"
#include <concrt.h>
#include "TextHelper.h"
#include "GameEngine.h"
class WelcomingScreen: public Screen,public IDrawable
{
	static const bool is2D = true;
	void Initialize()
	{
		counter = 0;
		counter1 = 0;
		startCount = false;
		texture = LoadGLTexture("images\\screens\\Welcoming Screen.bmp");
	}
	void Draw()
	{
		glClearColor(1,1,1,1);
		glScalef(10, 10, 10);
		glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, texture);
		DrawCanvase();
		glColor3f(1,1,1);
		char* sayWelcome0 = "Welcome to Our Game";
		glColor3f(1,1,1);
		//TextHelper::DrawString(-4 , 4, GLUT_BITMAP_TIMES_ROMAN_24, sayWelcome0);

		//char* sayWelcome1 = "Just let the adrenaline flow";
		//TextHelper::DrawString(-3.25 , 5.25, GLUT_BITMAP_9_BY_15, sayWelcome1);

		char* cont = "Press SPACE to continue";
		glColor3f(1,1,1);
		TextHelper::DrawString(-4 , -7, GLUT_BITMAP_9_BY_15, cont);
		glColor3f(1,1,1);
		if(counter1 == 0)
			MoveWindow(GetActiveWindow(),400,100,500,500,1);
		counter1++;
		if(startCount)
			counter++;
		
		if(counter1 >= 6000)
		{
			glutHideWindow();
			startCount = true;
		}
		if(counter >= 1)
		{	
			glutShowWindow();
			ScreenManager::AddScreen(new IntroductionScreen());
		}
	}

	void Update()
	{
		
		//Sleep(3000);
		//ScreenManager::AddScreen(new IntroductionScreen());
	}

	bool Is2D(){return this->is2D;}
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
	int counter;
	int counter1;
	bool startCount;
	void GetKeyboardDownPress(int key)
	{
		if ( key == ' ' )
		{
			glutHideWindow();
			startCount = true;
		}
	}
};
#endif