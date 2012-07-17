#ifndef _MAIN_H
#define _MAIN_H

#pragma warning(disable: 4786)						

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include <gl\gl.h>										
#include <gl\glu.h>										
//#include <gl\glaux.h>
#include <crtdbg.h>
using namespace std;

#define SCREEN_WIDTH 800								
#define SCREEN_HEIGHT 600								
#define SCREEN_DEPTH 16	
#define MAX_TEXTURES 100	

class CVector3 
{
public:
	float x, y, z;
};

class CVector2 
{
public:
	float x, y;
};

struct tFace
{
	int vertIndex[3];		
	int coordIndex[3];		
};
struct tMaterialInfo
{
	char  strName[255];		
	char  strFile[255];		
	BYTE  color[3];			
	int   texureId;			
	float uTile;			  
	float vTile;				
	float uOffset;			
	float vOffset;			
} ;
struct t3DObject 
{
	int  numOfVerts;			
	int  numOfFaces;			
	int  numTexVertex;			
	int  materialID;			
	bool bHasTexture;			
	char strName[255];			
	CVector3  *pVerts;			
	CVector3  *pNormals;		
	CVector2  *pTexVerts;		
	tFace *pFaces;				
};

struct tAnimationInfo
{
	char strName[255];			
	int startFrame;				
	int endFrame;				
	int loopingFrames;			
	int framesPerSecond;		
};
struct t3DModel 
{
	int numOfObjects;					
	int numOfMaterials;					
	vector<tMaterialInfo> pMaterials;	
	vector<t3DObject> pObject;			
	int numOfAnimations;				 
	int currentAnim;					 
	int currentFrame;					 
	int nextFrame;						
	float t;							
	float lastTime;						
	vector<tAnimationInfo> pAnimations; 
	int numOfTags;						
	t3DModel			**pLinks;		
	struct tMd3Tag		*pTags;			
};

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd);
bool init(void);
void SetupWorldList();
void SpecialKeysUP(int key, int x, int y);
void action(void);
void SpecialKeys(int key, int x, int y);
void Key(unsigned char key, int x, int y );
void Display(void);
void Reshape(int w, int h);

#endif 