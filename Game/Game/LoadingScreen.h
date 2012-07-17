#ifndef LOADINGSCREEN_H_
#define LOADINGSCREEN_H_
#include "AllIncludes.h"
#include "Screen.h"
#include "ExitScreen.h"
#include "IDrawable.h"

class LoadingScreen:public Screen,public IDrawable
{
	SaveAndLoad *Load;
	bool NewGame;
	static const bool is2D = true;
	bool Is2D(){return this->is2D;}
	GLuint tex[5];
	int Count;
	int lvl;
	void Initialize()
	{
		Count = 0;
		tex[0] = LoadGLTexture("images\\screens\\Load0.bmp");
		tex[1] = LoadGLTexture("images\\screens\\Load1.bmp");
		tex[2] = LoadGLTexture("images\\screens\\Load2.bmp");
		tex[3] = LoadGLTexture("images\\screens\\Load3.bmp");
		tex[4] = LoadGLTexture("images\\screens\\Load4.bmp");
	}
	World world;
	ThirdPersonCamera camera;
	Hero hero;
	Boss boss;
	FinalBoss fBoss;
	//ThirdPersonCamera *camera;
	//Hero *hero;
	bool flags[18];
	Ally ally;
	Graph graph;
	NormalEnemy e[20];
	//Boss *boss;
	//FinalBoss *fBoss;
	int SomeValues[5];
	Flame flame[5];
	GameScreen GS;
	Model_3DS chesto;
	Model_3DS chestc;
	Model_3DS Prison;
	Model_3DS Door1;
	Model_3DS Door2;
	Model_3DS base;
	Model_3DS crystal;
	GLuint texture;
	void LoadNewGame(int c)
	{
		//fe moshkela hena fe el pointers
		if(lvl == 1)
		{
			if(c == 0)
			{
				world.loadTextures(lvl);

				world.BuildGraph(&graph);
				world.Draw();
				Vector3 P = world.terrain.PlayerPos;
				camera.Reset(0, 0, 900, P.x, 0, P.z, 0, 1, 0,180);
				hero.LoadPlayer();
				hero.LoadTextures();
				ally.LoadPlayer();
			}
			if(c == 1)
			{
				texture = LoadGLTexture("images\\screens\\GamePausedScreen.bmp");
				for(int i = 0 ; i < 14 ; i++)
				{
					e[i].LoadPlayer();
					e[i].LoadTexture();
					e[i].setGraph(&graph);
					e[i].MapLevel = 1;
				}
			}
			if(c == 2)
			{
				boss.LoadPlayer();
				boss.LoadTexture();
				boss.MapLevel = 1;
				chestc.Load("models\\ClosedChest.3DS");
				chesto.Load("models\\OpenChest.3DS");
				Prison.Load("models\\Prison.3DS");
				Door1.Load("models\\Door.3DS");
				Door2.Load("models\\Door.3DS");
			}
			if(c == 3)
			{
				for(int i = 0 ; i < 5 ; i++)	
					flame[i].loadTexture();
			}
			if(c == 4)
			{
				GS.LoadTextures();
			}
			if(c == 5)
			{
				world.InitializeEnemiesPosition(e,boss,fBoss,lvl);
				ally.SetPlayerPosition(boss.GetPosition().x,boss.GetPosition().z+100);
				chestc.scale = 0.2;
				chesto.scale = 0.2;
				Prison.scale = 0.7;
				Door1.scale = 1.5;
				Door2.scale = 1.5;
				chestc.pos.x = e[0].GetPosition().x;
				chestc.pos.y = -21;
				chestc.pos.z = e[0].GetPosition().z - 200;
				chesto.pos.x = e[0].GetPosition().x;
				chesto.pos.y = -21;
				chesto.pos.z = e[0].GetPosition().z - 200;
				Prison.pos.x = boss.GetPosition().x;
				Prison.pos.y = -21;
				Prison.pos.z = boss.GetPosition().z + 100;
				Door1.pos.x = e[0].GetPosition().x;
				Door1.pos.y = -21;
				Door1.pos.z = e[0].GetPosition().z + 200;
				Door2.pos.x = boss.GetPosition().x + 100;
				Door2.pos.y = -21;
				Door2.pos.z = boss.GetPosition().z + 400;
			}
		}
		else if(lvl == 2)
		{
			if(c == 0)
			{
				world.loadTextures(lvl);
				world.BuildGraph(&graph);
				world.Draw();
				Vector3 P = world.terrain.PlayerPos;
				camera.Reset(0, 0, 900, P.x, 0, P.z, 0, 1, 0,180);
				hero.LoadPlayer();
				hero.LoadTextures();
			}
			if(c == 1)
			{
				texture = LoadGLTexture("images\\screens\\GamePausedScreen.bmp");
				for(int i = 0 ; i < 20 ; i++)
				{
					e[i].LoadPlayer();
					e[i].LoadTexture();
					e[i].setGraph(&graph);
					e[i].MapLevel = 2;
				}
			}
			if(c == 2)
			{
				fBoss.LoadPlayer();
				fBoss.LoadTexture();
				fBoss.MapLevel = 2;
				crystal.Load("models\\Crystal.3DS");
				base.Load("models\\Base.3DS");
			}
			if(c == 3)
			{
				for(int i = 0 ; i < 5 ; i++)	
					flame[i].loadTexture();
			}
			if(c == 4)
			{
				GS.LoadTextures();
			}
			if(c == 5)
			{
				world.InitializeEnemiesPosition(e,boss,fBoss,lvl);
				base.pos.x = world.terrain.PlayerPos.x + 50;
				base.pos.y = -21;
				base.pos.z = world.terrain.PlayerPos.z - 1100;
				crystal.pos.x = world.terrain.PlayerPos.x-5 + 50;
				crystal.pos.y = -3;
				crystal.pos.z = world.terrain.PlayerPos.z-1 - 1100;
			}
		}
	}
	void LoadTheSave(int c)
	{
		if(Load->lvl == 1)
		{
			if(c == 0)
			{
				lvl = Load->lvl;
				world.loadTextures(lvl);
				world.BuildGraph(&graph);
				world.Draw();
				Vector3 P = Load->rhero.Position;
				camera = Load->rcamera;

				hero.EXP = Load->rhero.EXP;
				hero.Dead = Load->rhero.Dead;
				hero.HP = Load->rhero.HP;
				hero.MP = Load->rhero.MP;
				hero.Position = Load->rhero.Position;
				hero.Rotation = Load->rhero.Rotation;
				hero.weaponNumber = Load->rhero.weaponNumber;
				hero.EXPincreased = Load->rhero.EXPincreased;
				hero.HealthPointDecreased = Load->rhero.HealthPointDecreased;
				hero.ManaPointDecreased = Load->rhero.ManaPointDecreased;
				hero.EXP = Load->rhero.EXP;
				hero.CurrentLevel = Load->rhero.CurrentLevel;
				hero.Skills = Load->rhero.Skills;
				hero.damage = Load->rhero.damage;
				hero.Speed = Load->rhero.Speed;
				hero.MaxHP = Load->rhero.MaxHP;
				hero.MaxMP = Load->rhero.MaxMP;
				
				hero.LoadPlayer();
				hero.LoadTextures();
				ally.LoadPlayer();
			}
			if(c == 1)
			{
				texture = LoadGLTexture("images\\screens\\GamePausedScreen.bmp");
				for(int i = 0 ; i < 14 ; i++)
				{
					e[i].Dead = Load->re[i].Dead;
					e[i].EnemyDepth = Load->re[i].EnemyDepth;
					e[i].EnemyRight = Load->re[i].EnemyRight;
					e[i].HP = Load->re[i].HP;
					e[i].Position = Load->re[i].Position;

					e[i].LoadPlayer();
					e[i].LoadTexture();
					e[i].setGraph(&graph);
					e[i].MapLevel = 1;
				}
			}
			if(c == 2)
			{
				boss.Dead = Load->rboss.Dead;
				boss.EnemyDepth = Load->rboss.EnemyDepth;
				boss.EnemyRight = Load->rboss.EnemyRight;
				boss.HP = Load->rboss.HP;
				boss.Position = Load->rboss.Position;

				boss.LoadPlayer();
				boss.LoadTexture();
				boss.MapLevel = 1;
				chestc.Load("models\\ClosedChest.3DS");
				chesto.Load("models\\OpenChest.3DS");
				Prison.Load("models\\Prison.3DS");
				Door1.Load("models\\Door.3DS");
				Door2.Load("models\\Door.3DS");
			}
			if(c == 3)
			{
				SomeValues[0] = Load->Timer;
				SomeValues[1] = Load->numberOfEnemyKilled;
				SomeValues[2] = Load->monstersCounter;
				SomeValues[3] = Load->Divider;
				SomeValues[4] = Load->waveNumber;
				for(int i = 0 ; i < 5 ; i++)	
					flame[i].loadTexture();
			}
			if(c == 4)
			{
				for(int i = 0 ; i < 18 ; i++)
					flags[i] = Load->flags[i];
				GS.LoadTextures();
			}
			if(c == 5)
			{
				//world.InitializeEnemiesPosition(e,boss,fBoss,lvl);
				ally.SetPlayerPosition(boss.GetPosition().x,boss.GetPosition().z+100);
				chestc.scale = 0.2;
				chesto.scale = 0.2;
				Prison.scale = 0.7;
				Door1.scale = 1.5;
				Door2.scale = 1.5;
				chestc.pos.x = e[0].GetPosition().x;
				chestc.pos.y = -21;
				chestc.pos.z = e[0].GetPosition().z - 200;
				chesto.pos.x = e[0].GetPosition().x;
				chesto.pos.y = -21;
				chesto.pos.z = e[0].GetPosition().z - 200;
				Prison.pos.x = boss.GetPosition().x;
				Prison.pos.y = -21;
				Prison.pos.z = boss.GetPosition().z + 100;
				Door1.pos.x = e[0].GetPosition().x;
				Door1.pos.y = -21;
				Door1.pos.z = e[0].GetPosition().z + 200;
				Door2.pos.x = boss.GetPosition().x + 100;
				Door2.pos.y = -21;
				Door2.pos.z = boss.GetPosition().z + 400;
			}
		}
		else if(Load->lvl == 2)
		{
			if(c == 0)
			{
				world.loadTextures(lvl);
				world.BuildGraph(&graph);
				world.Draw();
				Vector3 P = Load->rhero.Position;
				camera = Load->rcamera;

				hero.EXP = Load->rhero.EXP;
				hero.Dead = Load->rhero.Dead;
				hero.HP = Load->rhero.HP;
				hero.MP = Load->rhero.MP;
				hero.Position = Load->rhero.Position;
				hero.Rotation = Load->rhero.Rotation;
				hero.weaponNumber = Load->rhero.weaponNumber;
				hero.EXPincreased = Load->rhero.EXPincreased;
				hero.HealthPointDecreased = Load->rhero.HealthPointDecreased;
				hero.ManaPointDecreased = Load->rhero.ManaPointDecreased;
				hero.EXP = Load->rhero.EXP;
				hero.CurrentLevel = Load->rhero.CurrentLevel;
				hero.Skills = Load->rhero.Skills;
				hero.damage = Load->rhero.damage;
				hero.Speed = Load->rhero.Speed;
				hero.MaxHP = Load->rhero.MaxHP;
				hero.MaxMP = Load->rhero.MaxMP;

				hero.LoadPlayer();
				hero.LoadTextures();
			}
			if(c == 1)
			{
				texture = LoadGLTexture("images\\screens\\GamePausedScreen.bmp");
				for(int i = 0 ; i < 20 ; i++)
				{
					e[i].Dead = Load->re[i].Dead;
					e[i].EnemyDepth = Load->re[i].EnemyDepth;
					e[i].EnemyRight = Load->re[i].EnemyRight;
					e[i].HP = Load->re[i].HP;
					e[i].Position = Load->re[i].Position;

					e[i].LoadPlayer();
					e[i].LoadTexture();
					e[i].setGraph(&graph);
					e[i].MapLevel = 2;
				}
			}
			if(c == 2)
			{
				fBoss.Dead = Load->rfboss.Dead;
				fBoss.EnemyDepth = Load->rfboss.EnemyDepth;
				fBoss.EnemyRight = Load->rfboss.EnemyRight;
				fBoss.HP = Load->rfboss.HP;
				fBoss.Position = Load->rfboss.Position;

				fBoss.LoadPlayer();
				fBoss.LoadTexture();
				fBoss.MapLevel = 2;
				crystal.Load("models\\Crystal.3DS");
				base.Load("models\\Base.3DS");
			}
			if(c == 3)
			{
				for(int i = 0 ; i < 5 ; i++)	
					flame[i].loadTexture();
			}
			if(c == 4)
			{
				for(int i = 0 ; i < 18 ; i++)
					flags[i] = Load->flags[i];
				GS.LoadTextures();
			}
			if(c == 5)
			{
				base.pos.x = world.terrain.PlayerPos.x + 50;
				base.pos.y = -21;
				base.pos.z = world.terrain.PlayerPos.z - 1100;
				crystal.pos.x = world.terrain.PlayerPos.x-5 + 50;
				crystal.pos.y = -3;
				crystal.pos.z = world.terrain.PlayerPos.z-1 - 1100;
			}
		}
	}
	void Loading(int c)
	{
		if(NewGame)
			LoadNewGame(c);
		else
			LoadTheSave(c);
	}
	void Draw()
	{
		glClearColor(1,1,1,1);
		glDisable(GL_LIGHTING);
		glColor3f(1,1,1);
		glScalef(10, 10, 10);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, tex[Count]);
		DrawCanvase();
		Loading(Count);
		if(Count == 5)
			ScreenManager::AddScreen(new GameEngine(!NewGame,SomeValues,flags,controls,world,camera,hero,graph,boss,flame,e,GS,chestc,chesto,Prison,Door1,Door2,ally,lvl,fBoss,base,crystal,texture));
		Count++;
		glColor3f(1,1,1);		
		glEnable( GL_LIGHTING );
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
	LoadingScreen(){}
	LoadingScreen(int level){lvl = level;NewGame = true;}
	LoadingScreen(SaveAndLoad &L){Load = &L;NewGame = false;}
	//static int Count;
};
#endif