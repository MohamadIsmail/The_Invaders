#ifndef PAUSESCREEN_H_
#define PAUSESCREEN_H_
#include "AllIncludes.h"


class PauseScreen:public Screen, public IDrawable
{
private:
	struct MenuItems
	{
		Screen* _ptrScreen;
		char* title;
	};
	static const bool is2D = true;
	static const int SIZE = 4;
	int select_index ;
	SaveAndLoad *s;
	MenuItems menuItemsArray[SIZE];
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
	PauseScreen(int texture,SaveAndLoad &sa)
	{
		this->texture = texture;
		s = &sa;
	}
	PauseScreen(int texture)
	{
		this->texture = texture;
	}
	bool Is2D(){return this->is2D;}

	void Initialize()
	{
		select_index = 0;
		menuItemsArray[0]._ptrScreen = NULL;
		menuItemsArray[0].title = "Continue";
		menuItemsArray[1]._ptrScreen = new LoadScreen();
		menuItemsArray[1].title = "Load";

		menuItemsArray[2]._ptrScreen = new SaveScreen(*s);
		menuItemsArray[2].title = "Save";

		menuItemsArray[3]._ptrScreen= new ExitScreen();
		menuItemsArray[3].title = "Exit";
	}

	void Draw()
	{
		glEnable(GL_TEXTURE_1D);
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D,texture);
		glClearColor(1,1,1,1);
		glScalef(10, 10, 10);
		DrawCanvase();
		int yPos = 2;
		for ( int i = 0 ; i < SIZE ; i ++ )
		{
			if ( select_index == i )
				glColor3f(0,.5,1);
			else
				glColor3f(1,1,1);
			TextHelper::DrawString(-2,yPos-3-i, GLUT_BITMAP_TIMES_ROMAN_24, menuItemsArray[i].title);

		}
		glColor3f(1,1,1);
		glEnable(GL_LIGHTING);
	}

	void Update()
	{
	}

	void GetSpecialDownPress(int key)
	{
		if ( key == GLUT_KEY_DOWN )
			select_index = min(SIZE-1, select_index+1);
		else if ( key == GLUT_KEY_UP )
			select_index = max(0, select_index-1);
	}

	void GetKeyboardDownPress(int key)
	{
		if(key == 27)
			ScreenManager::RemoveScreen();
		if ( key == '\r' )
		{
			if(menuItemsArray[select_index].title == "Continue")
				ScreenManager::RemoveScreen();
			else
			{
				ScreenManager::AddScreen(menuItemsArray[select_index]._ptrScreen);
			}
		}
	}
};
#endif