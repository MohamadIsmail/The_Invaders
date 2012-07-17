#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.H>
#include<gl\glut.h>
#include "TextureHelper.h"
class Flame
{
public:
	UINT texture[8];
	int fireCounter;
	Vector3 Position;
	int counter;
	Flame()
	{
		counter = 0;
		fireCounter = 0;
	}
	void loadTexture()
	{
		texture[0] = LoadGLTexture("images\\particles\\f1.bmp");
		texture[1] = LoadGLTexture("images\\particles\\f2.bmp");
		texture[2] = LoadGLTexture("images\\particles\\f3.bmp");
		texture[3] = LoadGLTexture("images\\particles\\f4.bmp");
		texture[4] = LoadGLTexture("images\\particles\\f5.bmp");
		texture[5] = LoadGLTexture("images\\particles\\f6.bmp");
		texture[6] = LoadGLTexture("images\\particles\\f7.bmp");
		texture[7] = LoadGLTexture("images\\particles\\f8.bmp");
	}
	void SetFlamePosition(int x,int y,int z)
	{
		Position.x = x;
		Position.y = y;
		Position.z = z;
	}
	void Update()
	{
		counter++;
		if(!(counter % 3))
		{
			counter = 0;
			fireCounter++;
			if(!(fireCounter%8))
				fireCounter = 0;
		}
		Draw();
	}
	void Draw()
	{
		glLoadIdentity();
		glEnable(GL_BLEND);
		glDepthMask(false);
		glBindTexture(GL_TEXTURE_2D,texture[fireCounter]);
		glTranslatef(Position.x,Position.y,Position.z);
		glScalef(0.1,0.1,0.1);
		glPushMatrix();
		{
			glScalef(2,2,2);
			glTranslatef(0,-10,0);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,0);
				glVertex3f(50,100,0);
				glTexCoord2f(0,1);
				glVertex3f(50,0,0);
				glTexCoord2f(1,1);
				glVertex3f(-50,0,0);
				glTexCoord2f(1,0);
				glVertex3f(-50,100,0);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,0);
				glVertex3f(0,100,50);
				glTexCoord2f(0,1);
				glVertex3f(0,0,50);
				glTexCoord2f(1,1);
				glVertex3f(0,0,-50);
				glTexCoord2f(1,0);
				glVertex3f(0,100,-50);
			}
			glEnd();
		}
		glPopMatrix();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		{
			glTranslatef(0,0,-7);
			glScalef(1,0.5,10);
			glutSolidCube(10);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(5,0,-5);
			glScalef(10,0.5,1);
			glutSolidCube(10);
		}
		glPopMatrix();
		glLoadIdentity();
	}
};