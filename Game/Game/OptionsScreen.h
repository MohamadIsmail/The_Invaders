#ifndef OPTIONSSCREEN_H_
#define OPTIONSSCREEN_H_
#include "AllIncludes.h"

class OptionsScreen:public Screen,public IDrawable
{
private:
	static const int MenuSize = 10;
	char* menuItemsArray[MenuSize];
	int select_index;
	bool enable_view_of_box,enable_error_box,sound_enabled;
	static const bool is2D = true;
	bool Is2D(){return this->is2D;}
	bool isResolutionChanged;
	GLuint texture2,texture3,texture4;
public:
	map<int,int>controls;
	void GetSpecialDownPress(int key)
	{
		enable_error_box=false;
		if(!enable_view_of_box)
		{
			if ( key == GLUT_KEY_DOWN )
				select_index = min(MenuSize-1, select_index+1);
			else if ( key == GLUT_KEY_UP )
				select_index = max(0, select_index-1);
		}
	}

	void GetKeyboardDownPress(int key)
	{
		isResolutionChanged = false;
		DEVMODE dmode;
		memset(&dmode, 0, sizeof(DEVMODE));// clear all memory
		dmode.dmSize=sizeof(DEVMODE);	   // it's required to specify the size of this struct
		dmode.dmBitsPerPel = 32;	   // color depth; 8/16/32 bit
		dmode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// change resolution, if possible
		//if (ChangeDisplaySettings(&dmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		//{
			// if not... failed to change resolution
		//}
		//ChangeDisplaySettings(NULL,0);
		enable_error_box=false;
		if(enable_view_of_box)
		{
			for(int i = 0 ; i < controls.size() ; i ++)
			{
				if(controls[i]==key &&  i!=select_index)
				{
					enable_error_box=true;
				}
			}
			if(!enable_error_box)
			{
				controls[select_index]=key;
			}
			enable_view_of_box=false;
		}
		if ( key == '\r' && select_index<6 )
		{
			enable_view_of_box=true;
		}
		if(key == '\r' && select_index == 6)
		{
			dmode.dmPelsWidth = 800;	   // width and height of desired resolution
			dmode.dmPelsHeight = 600;
			isResolutionChanged = true;
		}
		if(key == '\r' && select_index == 7)
		{
			dmode.dmPelsWidth = 1024;	   // width and height of desired resolution
			dmode.dmPelsHeight = 768;
			isResolutionChanged = true;
		}
		if(key == '\r' && select_index == 8)
		{
			dmode.dmPelsWidth = 1366;	   // width and height of desired resolution
			dmode.dmPelsHeight = 768;
			isResolutionChanged = true;
		}
		if(isResolutionChanged)
		{
			if (ChangeDisplaySettings(&dmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				cout << "changed";
			}
		}
		if ( key == '\r' && select_index==9 )
		{
			if(menuItemsArray[9]== "ON" )
			{
				menuItemsArray[9]= "OFF" ;
				PlaySound("sounds\\click.wav",NULL, SND_ASYNC);
				controls[6] = 'n';
			}
			else
			{
				menuItemsArray[9]= "ON" ;
				PlaySound("sounds\\start.wav",NULL, SND_ASYNC);
				controls[6] = 'y';
			}
		}
		if(key==27)
		{
			ScreenManager::RemoveScreen(controls);
		}
	}

	void Initialize()
	{
		controls[0]='w';
		controls[1]='s';
		controls[2]='a';
		controls[3]='d';
		controls[4]=' ';
		controls[5]='j';
		controls[6] = 'y';
		enable_view_of_box=false;
		texture = LoadGLTexture("images\\screens\\OptionScreen.bmp");
		texture3=LoadGLTexture("images\\menus\\usedKey.bmp");
		texture2=LoadGLTexture("images\\menus\\PressAnyKey.bmp");
		select_index = 0;
		menuItemsArray[0]= "move forward" ;
		menuItemsArray[1]= "move backward" ;
		menuItemsArray[2]= "move left" ;
		menuItemsArray[3]= "move right" ;
		menuItemsArray[4]= "jump" ;
		menuItemsArray[5]= "attack" ;
		menuItemsArray[6]= "800 X 600" ;
		menuItemsArray[7]= "1024 X 768" ;
		menuItemsArray[8]= "1366 X 768" ;
		menuItemsArray[9]= "ON" ;
		enable_view_of_box=false;
		enable_error_box=false;
		sound_enabled=false;
	}

	void Draw()
	{
		glutFullScreen();
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glClearColor(1,1,1,1);
		glScalef(10, 10, 10);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texture );
		DrawCanvase();
		glColor3f(1,1,1);	

		int yPos = 2;
		int j =0;
		for ( int i = 0 ; i < MenuSize ; i ++ )
		{
			if ( select_index == i )
				glColor3f(0,.5,1);
			else
				glColor3f(1,1,1);
			if(i<6)
			{
				char z=(char)controls[i];
				char * x =&z;
				TextHelper::DrawString(-7,yPos-i, GLUT_BITMAP_TIMES_ROMAN_24, menuItemsArray[i]);
				TextHelper::DrawString(-1,yPos-i, GLUT_BITMAP_TIMES_ROMAN_24, x);
			}
			if (i<9  && i >5)
			{
				TextHelper::DrawString(0,yPos-j, GLUT_BITMAP_TIMES_ROMAN_24, menuItemsArray[i]);
				j++;
			}
			{
				if (i > 8)	
					TextHelper::DrawString(0,-5, GLUT_BITMAP_TIMES_ROMAN_24, menuItemsArray[i]);
			}
		}
		glPopMatrix();

		if(enable_view_of_box)
		{

			glBindTexture(GL_TEXTURE_2D,texture2);
			glPushMatrix();
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glTexCoord2f(0,1);
			glVertex3f(-20, -20, 0);
			glTexCoord2f(0,0);
			glVertex3f(-20, 20, 0);
			glTexCoord2f(1,0);
			glVertex3f(20, 20, 0);
			glTexCoord2f(1,1);
			glVertex3f(20, -20, 0);
			glEnd();
			glPopMatrix();
		}
		if(enable_error_box)
		{

			glBindTexture(GL_TEXTURE_2D,texture3);
			glPushMatrix();
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glTexCoord2f(0,1);
			glVertex3f(-20, -20, 0);
			glTexCoord2f(0,0);
			glVertex3f(-20, 20, 0);
			glTexCoord2f(1,0);
			glVertex3f(20, 20, 0);
			glTexCoord2f(1,1);
			glVertex3f(20, -20, 0);
			glEnd();
			glPopMatrix();
		}
		glColor3f(1, 1, 1);
		glEnable( GL_LIGHTING );

		/*if(sound_enabled)
			glBindTexture(GL_TEXTURE_2D,texture4);
		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(0,1);
		glVertex3f(30, -50, 0);
		glTexCoord2f(0,0);
		glVertex3f(30, -40, 0);
		glTexCoord2f(1,0);
		glVertex3f(40, -40, 0);
		glTexCoord2f(1,1);
		glVertex3f(40, -50, 0);
		glEnd();
		glPopMatrix();*/

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
	OptionsScreen(){}

	map<int,int> GetControls();
};	
#endif