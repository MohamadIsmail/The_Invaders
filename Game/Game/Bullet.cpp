#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "Bullet.h"

const float Bullet::DefaultLifeTime = 3;
void Bullet::Update() {
	P += 0.1 * V;
}
void Bullet::Render(float Angle) const {
	if(isSniper)
		return;
	glLoadIdentity();
	glPushMatrix();
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDepthMask(false);
	glColor3f(1,1,1);
	glTranslatef(P.x, P.y, P.z);
	glRotatef(Angle+90,0,1,0);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0,0);
		glVertex3f(5,5,0);
		glTexCoord2f(0,1);
		glVertex3f(5,0,0);
		glTexCoord2f(1,1);
		glVertex3f(-5,0,0);
		glTexCoord2f(1,0);
		glVertex3f(-5,5,0);
	}
	glEnd();
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}