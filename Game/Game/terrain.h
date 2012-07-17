#include<Windows.h>
#include<gl\GL.H>
#include<gl\GLU.H>
#include <cstdio>
#include<iostream>
#include"Vector3.h"
using namespace std;

#define		MAP_HEIGHT	  3072
#define		MAP_WIDTH	  1024
#define		STEP_SIZE	  16						
#define		HEIGHT_RATIO  1.5f
struct coordinate
{
	int S,E;
};
class Terrain
{
public:
	BYTE g_HeightMap[MAP_HEIGHT*MAP_WIDTH];
	float scaleValue;
	int lvl;
	Terrain()
	{
		scaleValue  = 1;
	}
	void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)
	{
		FILE *pFile = NULL;
		pFile = fopen( strName, "rb" );
		if ( pFile == NULL )	
		{
			MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
			return;
		}
		fread( pHeightMap, 1, nSize, pFile );
		int result = ferror( pFile );
		if (result)
		{
			MessageBox(NULL, "Failed To Get Data!", "Error", MB_OK);
		}
		fclose(pFile);
	}
	int Height(BYTE *pHeightMap, int X, int Y)
	{
		int x = X % MAP_WIDTH;					
		int y = Y % MAP_HEIGHT;								
		if(!pHeightMap) return 0;							// Make Sure Our Data Is Valid

		return pHeightMap[x + (y * MAP_WIDTH)];				// Index Into Our Height Array And Return The Height
	}

	void SetVertexColor(BYTE *pHeightMap, int x, int y)		// Sets The Color Value For A Particular Index, Depending On The Height Index
	{
		if(!pHeightMap) return;								// Make Sure Our Height Data Is Valid
		float fColor = -0.15f + (Height(pHeightMap, x, y ) / 256.0f);
		glColor3f(0, fColor, 0 );
	}
	Vector3 PlayerPos;
	Vector3 E1Pos;
	Vector3 E2Pos;
	Vector3 E3Pos;
	Vector3 E4Pos;
	Vector3 E5Pos;
	Vector3 BossPos;
	Vector3 En1Pos;
	Vector3 En2Pos;
	Vector3 En3Pos;
	Vector3 En4Pos;
	Vector3 En5Pos;
	coordinate StartAndEndY[64];

	bool StartCountingInY;
	int counter;
	int GetXfromGraph(Graph *g,int z)
	{
		int start = 0;
		int min,max;
		int RandomIndex;
		int Difference;
		for(int i = 0 ; i < 64 ; i++)
		{
			if(g->Nodes[z][i].x != -1 && start == 0)
			{
				start++;
				min = i;
			}
			if(g->Nodes[z][i].x == -1 && start == 1)
			{
				start++;
				max = i-1;
			}	
		}
		if(start == 2)
		{
			Difference = max-min-10;
			RandomIndex = rand()%Difference + min+5;
			return g->Nodes[z][RandomIndex].x;
		}
		return -1;
	}
	void initializeGamePositions(Graph *g,BYTE pHeightMap[])
	{
		int X = 0,Y = 0;
		counter = 0;
		int y;
		StartCountingInY = false;
		for ( X = 0; X < MAP_WIDTH; X +=16 )
		{
			StartAndEndY[counter].S = -1;
			StartAndEndY[counter].E = -1;
			for ( Y = 0; Y < MAP_HEIGHT; Y +=16 )
			{
				y = Height(pHeightMap, X, Y );	
				if(y >= 0 && y <= 30 && !StartCountingInY)
				{
					StartAndEndY[counter].S = Y;
					StartCountingInY = true;
					continue;
				}
				if(y >= 0 && y <= 30)
				{
					StartAndEndY[counter].E = Y;
				}
			}
			counter++;
			StartCountingInY = false;
		}
		int MaxY = 0;
		int MinY = 1000;
		for(int i = 0 ; i < 63 ; i++)
		{
			if(StartAndEndY[i].S  < MinY && StartAndEndY[i].S != -1)
				MinY = StartAndEndY[i].S;
			if(StartAndEndY[i].E > MaxY)
				MaxY = StartAndEndY[i].E;
		}
		int Distance = MaxY - MinY;
		if(lvl == 1)
		{
			float z = (Distance/100)*95+MinY;
			float x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			PlayerPos.x = x;
			PlayerPos.z = z;
			//E1 Position
			z = (Distance/100)*9+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			E1Pos.x = x;
			E1Pos.z = z;
			//E2 Position
			z = (Distance/100)*30+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			E2Pos.x = x;
			E2Pos.z = z;
			//E3 Position
			z = (Distance/100)*30+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			E3Pos.x = x;
			E3Pos.z = z;
			//E4 Position
			z = (Distance/100)*55+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			E4Pos.x = x;
			E4Pos.z = z;
			//E5 Position
			z = (Distance/100)*53+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			E5Pos.x = x;
			E5Pos.z = z;
			//Boss Position
			z = (Distance/100)*10+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			//x -= 500;
			BossPos.x = x;
			BossPos.z = z;
		}
		else if(lvl == 2)
		{
			float z = (Distance/100)*90+MinY;
			float x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			PlayerPos.x = x;
			PlayerPos.z = z;
			//E1 Position
			z = (Distance/100)*20+MinY;
			x = GetXfromGraph(g,z/16)-250 -220;
			z += 100 -230;
			x -= 500;
			En1Pos.x = x+220;
			En1Pos.z = z+230;
			E1Pos.x = x;
			E1Pos.z = z;
			//E2 Position
			z = (Distance/100)*47+MinY ;
			x = GetXfromGraph(g,z/16) +20 -200;
			z += 40  +190;
			x -= 500;
			En2Pos.x = x+200;
			En2Pos.z = z-190;
			E2Pos.x = x;
			E2Pos.z = z;
			//E3 Position
			z = (Distance/100)*20+MinY;
			x = GetXfromGraph(g,z/16)+480 +250;
			z += 100  - 40 - 230;
			x -= 500;
			En3Pos.x = x-250;
			En3Pos.z = z+230;
			E3Pos.x = x;
			E3Pos.z = z;
			//E4 Position
			z = (Distance/100)*47+MinY  +330;
			x = GetXfromGraph(g,z/16)+420  +600;
			z += 120;
			x -= 500;
			En4Pos.x = x-300;
			En4Pos.z = z-330;
			E4Pos.x = x;
			E4Pos.z = z;
			//E5 Position
			//Boss Position
			z = (Distance/100)*90+MinY;
			x = GetXfromGraph(g,z/16);
			z += 100;
			x -= 500;
			En5Pos.x = x;
			En5Pos.z = z-200;
			BossPos.x = x;
			BossPos.z = z;
		}
	}
	void BuildGraph(Graph *g,BYTE pHeightMap[])
	{
		g->InitializeNodes();
		cout << endl;
		int i = 0;
		int j = 0;
		int y = 0;
		for (int X = 0; X < (MAP_HEIGHT-STEP_SIZE); X += STEP_SIZE )
		{
			for (int Y = 0; Y < (MAP_WIDTH-STEP_SIZE); Y += STEP_SIZE )
			{
				y = Height(pHeightMap, Y, X );	
				if(y < 180)
				{
					g->Nodes[i][j] = Vector3(Y,0,X);
					cout << 'x';
				}
				else
				{
					cout << ' ';
				}
				j++;
			}
			cout << endl;
			i++;
			j = 0;
		}
		initializeGamePositions(g,pHeightMap);
	}
	void RenderHeightMap(BYTE pHeightMap[])			
	{
		int X = 0, Y = 0;								
		int x, y, z;									
		if(!pHeightMap) return;		
		glBegin( GL_QUADS );						
		for ( X = 0; X < (MAP_WIDTH-STEP_SIZE); X += STEP_SIZE )
		{
			for ( Y = 0; Y < (MAP_HEIGHT-STEP_SIZE); Y += STEP_SIZE )
			{

				x = X;							
				y = Height(pHeightMap, X, Y );	
				z = Y;		
				glTexCoord2f(0,0);
				glVertex3i(x, y, z);						

				x = X;										
				y = Height(pHeightMap, X, Y + STEP_SIZE );  
				z = Y + STEP_SIZE ;							
				
				glTexCoord2f(0,1);
				glVertex3i(x, y, z);						

				x = X + STEP_SIZE; 
				y = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE ); 
				z = Y + STEP_SIZE ;
				glTexCoord2f(1,1);
				glVertex3i(x, y, z);						

				x = X + STEP_SIZE; 
				y = Height(pHeightMap, X + STEP_SIZE, Y ); 
				z = Y;
				glTexCoord2f(1,0);
				glVertex3i(x, y, z);						
			}
		}
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
	}
};