#ifndef INTRODUCTIONsCREEN_H_
#define INTRODUCTIONsCREEN_H_
#include "AllIncludes.h"
#include "Screen.h"
#include "ExitScreen.h"
#include "IDrawable.h"
#include"LoadingScreen.h"


class IntroductionScreen: public Screen,public IDrawable
{
public:
	IntroductionScreen()
	{
		controls[0]='w';
		controls[1]='s';
		controls[2]='a';
		controls[3]='d';
		controls[4]=' ';
		controls[5]='j';
		controls[6]='y';
	}
private:
	struct MenuItems
	{
		Screen* _ptrScreen;
		char* title;
	};
	static const bool is2D = true;
	static const int MenuSize = 4;
	MenuItems menuItemsArray[MenuSize];
	int select_index;

	void Initialize()
	{
		glutFullScreen();
		select_index = 0;
		menuItemsArray[0]._ptrScreen = new LoadingScreen(1);
		menuItemsArray[0].title = "New Game";
		menuItemsArray[1]._ptrScreen = new LoadScreen();
		menuItemsArray[1].title = "Load";
		menuItemsArray[2]._ptrScreen = new OptionsScreen();
		menuItemsArray[2].title = "Options";

		menuItemsArray[3]._ptrScreen= new ExitScreen();
		menuItemsArray[3].title = "Exit";
		texture = LoadGLTexture("images\\screens\\StartScreen.bmp");	
		PlaySound("musics\\start.wav",NULL, SND_ASYNC);
	}
	void Draw()
	{
		glDisable(GL_LIGHTING);
		glClearColor(1,1,1,1);
		glScalef(10, 10, 10);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texture );
		DrawCanvase();
		int yPos = 2;
		for ( int i = 0 ; i < MenuSize ; i ++ )
		{
			if ( select_index == i )
				glColor3f(0,.5,1);
			else
				glColor3f(1,1,1);
			TextHelper::DrawString(3,yPos-3-i, GLUT_BITMAP_TIMES_ROMAN_24, menuItemsArray[i].title);

		}
		glColor3f(1,1,1);
		glEnable( GL_LIGHTING );
	}

	bool Is2D(){return this->is2D;}
	void GetSpecialDownPress(int key)
	{
		if ( key == GLUT_KEY_DOWN )
			select_index = min(MenuSize-1, select_index+1);
		else if ( key == GLUT_KEY_UP )
			select_index = max(0, select_index-1);
	}
	void GetKeyboardDownPress(int key)
	{
		if ( key == '\r' )
		{
			ScreenManager::AddScreen(menuItemsArray[select_index]._ptrScreen);
			if(select_index == 0 ||select_index == 1)
				ScreenManager::SetControls(controls);
		}
	}
	void HandleMouse(int button,int state,int x, int y)
	{
		
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
};
#endif