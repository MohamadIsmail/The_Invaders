#pragma once
#include<Windows.h>
#include<gl\GL.H>
#include<gl\GLU.H>

static int LightCounter = 0x4000;
class Light
{
public:
	float LightAmbient[4];    
	float LightDiffuse[4];    
	float LightPosition[4]; 
	float LightDirection[3];
	int LightIndex;
	Light()
	{
		LightAmbient[0] = 1;
		LightAmbient[1] = 0.7;
		LightAmbient[2] = 0;
		LightAmbient[3] = 1;
		LightDiffuse[0] = 1;
		LightDiffuse[1] = 1;
		LightDiffuse[2] = 1;
		LightDiffuse[3] = 1;
		LightPosition[0] = 0;
		LightPosition[1] = 5;
		LightPosition[2] = 1;
		LightPosition[3] = 1;
		LightDirection[0] = 0;
		LightDirection[1] = -1;
		LightDirection[2] = 0;
		LightIndex = LightCounter+= 0x0001;
		if(LightCounter == 8)
			LightCounter = 0;
	}
	Light(float AmbientR,float AmbientG,float AmbientB,float DiffuseR,float DiffuseG,float DiffuseB,float X,float Y,float Z,float DirX,float DirY,float DirZ)
	{
	 	
	}
	void Update()
	{
		glEnable(GL_LIGHTING);
		glLightf(LightIndex,GL_SPOT_EXPONENT,5);
		glLightf( LightIndex, GL_SPOT_CUTOFF, 90.0 );
		glLightfv(LightIndex,GL_SPOT_DIRECTION,LightDirection);
		glLightfv(LightIndex, GL_AMBIENT, LightAmbient);
		glLightfv(LightIndex, GL_DIFFUSE, LightDiffuse); 
		glLightfv(LightIndex, GL_POSITION,LightPosition);
		glEnable(LightIndex);
	}
};

