#include<Windows.h>
#include<gl\GL.H>

class Material
{
public :
	float mat_diffuse[4];
	float mat_ambient[4];
	float mat_specular[4];
	float mat_shininess;
	float mat_emission[4];

	Material()
	{
		mat_diffuse[0] = 1;
		mat_diffuse[1] = 1;
		mat_diffuse[2] = 1;
		mat_diffuse[3] = 1;
		mat_ambient[0] = 1;
		mat_ambient[1] = 1;
		mat_ambient[2] = 1;
		mat_ambient[3] = 0;
		mat_specular[0] = 1;
		mat_specular[1] = 1;
		mat_specular[2] = 1;
		mat_specular[3] = 1;
		mat_shininess = 80;
		mat_emission[0] = 0;
		mat_emission[1] = 0;
		mat_emission[2] = 0;
		mat_emission[3] = 1;
	}
	void SetMaterial()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	}
};