#ifndef SAVESCREEN_H_
#define SAVESCREEN_H_
#include "AllIncludes.h"
#include "Screen.h"
#include "ExitScreen.h"
#include "IDrawable.h"

class SaveScreen:public Screen,public IDrawable
{
	SaveAndLoad *save;
	static const int MenuSize = 8;
	char* menuItemsArray[MenuSize];
	int select_index;
	GLuint texture[11];
	static const bool is2D = true;
	bool Is2D(){return this->is2D;}
	void Initialize()
	{
		select_index = 1;
		texture[0] = LoadGLTexture("images\\screens\\SaveScreen.bmp");
		menuItemsArray[0]= "Save_1" ;
		menuItemsArray[1]= "Save_2" ;
		menuItemsArray[2]= "Save_3" ;
		menuItemsArray[3]= "Save_4" ;
		menuItemsArray[4]= "Save_5" ;
		menuItemsArray[5]= "Save_6" ;
		menuItemsArray[6]= "Save_7" ;
		menuItemsArray[7]= "Save_8" ;

		char fileName[] = "save\\Save_1.tga";
		for(int i = 1 ; i < 10 ; i++)
		{
			fileName[10] = '0'+i;
			texture[i] = LoadGLTexture(fileName); 
		}
		texture[10] = LoadGLTexture("images\\others\\boarder2.bmp");
	}
	void Draw()
	{
		glDisable(GL_LIGHTING);
		glClearColor(1,1,1,1);
		glScalef(10, 10, 10);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texture[0] );
		DrawCanvase();
		glColor3f(1,1,1);		
		int yPos = 3;
		int j =0;
		for ( int i = 0 ; i < MenuSize ; i ++ )
		{
			if ( (select_index-1) == i )
				glColor3f(0,.5,1);
			else
				glColor3f(1,1,1);
			TextHelper::DrawString(-8,yPos-i, GLUT_BITMAP_TIMES_ROMAN_24, menuItemsArray[i]);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(3,3,0);
			glScalef(0.2,0.2,0.1);
			glBindTexture(GL_TEXTURE_2D,texture[10]);
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glTexCoord2f(0,1);
			glVertex3f(-22, -22, 0);
			glTexCoord2f(0,0);
			glVertex3f(-22, 22, 0);
			glTexCoord2f(1,0);
			glVertex3f(22, 22, 0);
			glTexCoord2f(1,1);
			glVertex3f(22, -22, 0);
			glEnd();
			if(select_index > 0 && select_index < 9)
				glBindTexture(GL_TEXTURE_2D,texture[select_index]);
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glTexCoord2f(0,1);
			glVertex3f(-20, -20, 0);
			glTexCoord2f(0,0.05);
			//glTexCoord2f(0,0.25);
			glVertex3f(-20, 20, 0);
			glTexCoord2f(1,0.05);
			//glTexCoord2f(0.78,0.25);
			glVertex3f(20, 20, 0);
			glTexCoord2f(1,1);
			//glTexCoord2f(0.78,1);
			glVertex3f(20, -20, 0);
			glEnd();
		}
		glPopMatrix();
		glColor3f(1,1,1);
		glEnable(GL_LIGHTING);
	}
	void GetSpecialDownPress(int key)
	{
		if ( key == GLUT_KEY_DOWN )
			select_index = min(MenuSize, select_index+1);
		else if ( key == GLUT_KEY_UP )
			select_index = max(1, select_index-1);
	}
	void GetKeyboardDownPress(int key)
	{
		if ( key == '\r' )
		{
			char fileName[64];
			sprintf(fileName,"save\\%s",menuItemsArray[select_index-1]);
			save->FileName = fileName;
			save->SaveGame();	
			char* textureName = menuItemsArray[select_index-1];
			int j = 0;
			while(!(textureName[j] <= '9' && textureName[j] >= '1'))
			{
				fileName[j] = textureName[j];
				j++;
			}
			fileName[j++] = textureName[j];
			fileName[j++] = '.';
			fileName[j++] = 't';
			fileName[j++] = 'g';
			fileName[j++] = 'a';
			fileName[j] = 0;
			char filePath[64];
			j = 0;
			filePath[j++] = 's';
			filePath[j++] = 'a';
			filePath[j++] = 'v';
			filePath[j++] = 'e';
			filePath[j++] = '\\';
			int k = 0;
			while(fileName[k] != 0)
			{
				filePath[j++] = fileName[k++];
			}
			filePath[j] = 0;
			texture[select_index] = LoadGLTexture(filePath); 
		}
		if( key == 27 )
		{
			ScreenManager::RemoveScreen();
		}
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
	SaveScreen(){}
	SaveScreen(SaveAndLoad &SA)
	{
		save = &SA;
	}
};
#endif