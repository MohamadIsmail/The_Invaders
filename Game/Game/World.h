#include<Windows.h>
#include<gl\GL.H>
#include<gl\GLU.H>
#include"terrain.h"
#include "TextureHelper.h"
class World
{
public:
	enum direction{X_axis,Z_axis,NegX_axis,NegZ_axis};
	Terrain terrain;
	UINT texture[10];
	World()
	{
		
	}
	void loadTextures(int lvl)
	{
		terrain.lvl = lvl;
		if(lvl == 1)
			terrain.LoadRawFile("worlds\\world22.raw", MAP_HEIGHT * MAP_WIDTH, terrain.g_HeightMap);
		if(lvl == 2)
			terrain.LoadRawFile("worlds\\world23.raw", MAP_HEIGHT * MAP_WIDTH, terrain.g_HeightMap);
		texture[0] = LoadGLTexture("images\\world\\grass.bmp");
		texture[1] = LoadGLTexture("images\\world\\l1.bmp");
		texture[2] = LoadGLTexture("images\\world\\l2.bmp");
		texture[3] = LoadGLTexture("images\\world\\l3.bmp");
		texture[4] = LoadGLTexture("images\\world\\l4.bmp");
		texture[5] = LoadGLTexture("images\\world\\l5.bmp");
		texture[6] = LoadGLTexture("images\\world\\l6.bmp");
	}
	void BuildGraph(Graph *graph)
	{
		terrain.BuildGraph(graph,terrain.g_HeightMap);
	}
	void InitializeEnemiesPosition(NormalEnemy e[],Boss &boss,FinalBoss &fboss,int lvl)
	{	
		if(lvl == 1)
		{
			e[0].SetPlayerPosition(terrain.E1Pos.x,terrain.E1Pos.z);
			e[1].SetPlayerPosition(terrain.E2Pos.x,terrain.E2Pos.z);
			e[2].SetPlayerPosition(terrain.E3Pos.x,terrain.E3Pos.z);
			e[3].SetPlayerPosition(terrain.E4Pos.x,terrain.E4Pos.z);
			e[4].SetPlayerPosition(terrain.E5Pos.x,terrain.E5Pos.z);
			e[5].SetPlayerPosition(10+terrain.E1Pos.x,terrain.E1Pos.z);
			e[6].SetPlayerPosition(-10+terrain.E2Pos.x,terrain.E2Pos.z);
			e[7].SetPlayerPosition(-10+terrain.E3Pos.x,terrain.E3Pos.z);
			e[8].SetPlayerPosition(10+terrain.E4Pos.x,terrain.E4Pos.z);
			e[9].SetPlayerPosition(-10+terrain.E5Pos.x,terrain.E5Pos.z);
			e[10].SetPlayerPosition(-10+terrain.E2Pos.x,terrain.E2Pos.z+50);
			e[11].SetPlayerPosition(-10+terrain.E3Pos.x,terrain.E3Pos.z+50);
			e[12].SetPlayerPosition(10+terrain.E4Pos.x,terrain.E4Pos.z+50);
			e[13].SetPlayerPosition(-10+terrain.E5Pos.x,terrain.E5Pos.z+50);
			boss.SetPlayerPosition(terrain.BossPos.x,terrain.BossPos.z);
		}
		if(lvl == 2)
		{
			e[0].SetPlayerPosition(terrain.E1Pos.x,terrain.E1Pos.z);
			e[1].SetPlayerPosition(terrain.E2Pos.x,terrain.E2Pos.z);
			e[2].SetPlayerPosition(terrain.E3Pos.x,terrain.E3Pos.z);
			e[3].SetPlayerPosition(terrain.E4Pos.x,terrain.E4Pos.z);
			e[4].SetPlayerPosition(terrain.E1Pos.x,terrain.E1Pos.z);
			e[5].SetPlayerPosition(terrain.E2Pos.x,terrain.E2Pos.z);
			e[6].SetPlayerPosition(terrain.E3Pos.x,terrain.E3Pos.z);
			e[7].SetPlayerPosition(terrain.E4Pos.x,terrain.E4Pos.z);
			e[8].SetPlayerPosition(terrain.E1Pos.x,terrain.E1Pos.z);
			e[9].SetPlayerPosition(terrain.E2Pos.x,terrain.E2Pos.z);
			e[10].SetPlayerPosition(terrain.E3Pos.x,terrain.E3Pos.z);
			e[11].SetPlayerPosition(terrain.E4Pos.x,terrain.E4Pos.z);
			e[12].SetPlayerPosition(terrain.E1Pos.x,terrain.E1Pos.z);
			e[13].SetPlayerPosition(terrain.E2Pos.x,terrain.E2Pos.z);
			e[14].SetPlayerPosition(terrain.E3Pos.x,terrain.E3Pos.z);
			e[15].SetPlayerPosition(terrain.E4Pos.x,terrain.E4Pos.z);
			e[16].SetPlayerPosition(terrain.E1Pos.x,terrain.E1Pos.z);
			e[17].SetPlayerPosition(terrain.E2Pos.x,terrain.E2Pos.z);
			e[18].SetPlayerPosition(terrain.E3Pos.x,terrain.E3Pos.z);
			e[19].SetPlayerPosition(terrain.E4Pos.x,terrain.E4Pos.z);
			fboss.SetPlayerPosition(terrain.BossPos.x,terrain.BossPos.z);

			e[0].SetEntrancePosition(terrain.En1Pos.x,terrain.En1Pos.z);
			e[1].SetEntrancePosition(terrain.En2Pos.x,terrain.En2Pos.z);
			e[2].SetEntrancePosition(terrain.En3Pos.x,terrain.En3Pos.z);
			e[3].SetEntrancePosition(terrain.En4Pos.x,terrain.En4Pos.z);
			e[4].SetEntrancePosition(terrain.En1Pos.x,terrain.En1Pos.z);
			e[5].SetEntrancePosition(terrain.En2Pos.x,terrain.En2Pos.z);
			e[6].SetEntrancePosition(terrain.En3Pos.x,terrain.En3Pos.z);
			e[7].SetEntrancePosition(terrain.En4Pos.x,terrain.En4Pos.z);
			e[8].SetEntrancePosition(terrain.En1Pos.x,terrain.En1Pos.z);
			e[9].SetEntrancePosition(terrain.En2Pos.x,terrain.En2Pos.z);
			e[10].SetEntrancePosition(terrain.En3Pos.x,terrain.En3Pos.z);
			e[11].SetEntrancePosition(terrain.En4Pos.x,terrain.En4Pos.z);
			e[12].SetEntrancePosition(terrain.En1Pos.x,terrain.En1Pos.z);
			e[13].SetEntrancePosition(terrain.En2Pos.x,terrain.En2Pos.z);
			e[14].SetEntrancePosition(terrain.En3Pos.x,terrain.En3Pos.z);
			e[15].SetEntrancePosition(terrain.En4Pos.x,terrain.En4Pos.z);
			e[16].SetEntrancePosition(terrain.En1Pos.x,terrain.En1Pos.z);
			e[17].SetEntrancePosition(terrain.En2Pos.x,terrain.En2Pos.z);
			e[18].SetEntrancePosition(terrain.En3Pos.x,terrain.En3Pos.z);
			e[19].SetEntrancePosition(terrain.En4Pos.x,terrain.En4Pos.z);
			fboss.SetEntrancePosition(terrain.En5Pos.x,terrain.En5Pos.z);
		}
	}
	void InitializeObjectsPosition(Flame flame[],Light l[])
	{
		flame[0].SetFlamePosition(terrain.E1Pos.x,-22,terrain.E1Pos.z);
		flame[1].SetFlamePosition(terrain.E2Pos.x,-22,terrain.E2Pos.z);
		flame[2].SetFlamePosition(terrain.E3Pos.x,-22,terrain.E3Pos.z);
		flame[3].SetFlamePosition(terrain.E4Pos.x,-22,terrain.E4Pos.z);
		flame[4].SetFlamePosition(terrain.E5Pos.x,-22,terrain.E5Pos.z);
		for(int i = 0 ; i < 5 ; i++)
		{
			l[i+1].LightPosition[0] = flame[i].Position.x;
			l[i+1].LightPosition[1] = flame[i].Position.y+100;
			l[i+1].LightPosition[2] = flame[i].Position.z;
		}
	}
	void validateMovement(ThirdPersonCamera &camera,int tempX,int tempZ,bool dir[])
	{
		if(dir[direction::X_axis])
		{
			if(camera.T.x > tempX)
				camera.T.x = tempX;
		}
		else if(dir[direction::NegX_axis])
		{
			if(camera.T.x < tempX)
				camera.T.x = tempX;
		}
		if(dir[direction::Z_axis])
		{
			if(camera.T.z > tempZ)
				camera.T.z = tempZ;
		}
		else if(dir[direction::NegZ_axis])
		{
			if(camera.T.z < tempZ)
				camera.T.z = tempZ;
		}
	}
	void CheckMapBoundaries(Hero &hero,bool dir[])
	{
		int checkDis = 15;
		if(GetY(hero.Position.x+checkDis,hero.Position.z) > 0)
		{
			dir[direction::X_axis] = 1;
		}
		else if(GetY(hero.Position.x-checkDis,hero.Position.z) > 0)
		{ 
			dir[direction::NegX_axis] = 1;
		}
		else if(GetY(hero.Position.x,hero.Position.z+checkDis) > 0)
		{
			dir[direction::Z_axis] = 1;
		}
		else if(GetY(hero.Position.x,hero.Position.z-checkDis) > 0)
		{
			dir[direction::NegZ_axis] = 1;
		}
		else if(GetY(hero.Position.x-checkDis,hero.Position.z-checkDis) > 0)
		{
			dir[direction::NegZ_axis] = 1;
			dir[direction::NegX_axis] = 1;
		}
		else if(GetY(hero.Position.x+checkDis,hero.Position.z+checkDis) > 0)
		{
			dir[direction::Z_axis] = 1;
			dir[direction::X_axis] = 1;
		}
		else if(GetY(hero.Position.x+checkDis,hero.Position.z-checkDis) > 0)
		{
			dir[direction::NegZ_axis] = 1;
			dir[direction::X_axis] = 1;
		}
		else if(GetY(hero.Position.x-checkDis,hero.Position.z+checkDis) > 0)
		{
			dir[direction::Z_axis] = 1;
			dir[direction::NegX_axis] = 1;
		}
		else
		{
			for(int i = 0 ; i < 4 ; i++)
				dir[i] = 0;
		}
	}
	float GetY(float x,float z)
	{
		return (terrain.Height(terrain.g_HeightMap,x+500,z-100)-130)* HEIGHT_RATIO + 7;
	}
	void Draw()
	{
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glPushMatrix();
		{
			glScalef(1, 1 * HEIGHT_RATIO, 1);
			glTranslatef(-500,-130,100);
			for(int i = 0 ; i < 5000 ; i+=50)
				for(int j = 0 ; j < 5000 ; j+=50)
				{
					glBegin(GL_POLYGON);
					{
						glTexCoord2f(0,0);
						glVertex3f(i,170,j);
						glTexCoord2f(0,1);
						glVertex3f(i,170,j-50);
						glTexCoord2f(1,1);
						glVertex3f(i-50,170,j-50);
						glTexCoord2f(1,0);
						glVertex3f(i-50,170,j);
					}
					glEnd();
				}
				
			glBindTexture(GL_TEXTURE_2D,texture[4]);
			for(int i = 0 ; i < 5000 ; i+=50)
				for(int j = 0 ; j < 5000 ; j+=50)
				{
					glBegin(GL_POLYGON);
					{
						glTexCoord2f(0,0);
						glVertex3f(i,115,j);
						glTexCoord2f(0,1);
						glVertex3f(i,115,j-50);
						glTexCoord2f(1,1);
						glVertex3f(i-50,115,j-50);
						glTexCoord2f(1,0);
						glVertex3f(i-50,115,j);
					}
					glEnd();
				}
			glBindTexture(GL_TEXTURE_2D,texture[0]);
			terrain.RenderHeightMap(terrain.g_HeightMap);
		}

	}
}; 