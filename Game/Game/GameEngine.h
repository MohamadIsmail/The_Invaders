#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_
#include "AllIncludes.h"
#include "Screen.h"
using namespace std;
class GameEngine: public Screen
{
	//map <int ,int> Controls;
	static const bool is2D = false;
	CollisionDetectionHandler CDH;
	GameScreen *GS;
	Graph *graph;
	SoundEngine SE;
	Hero *hero;
	Flame *flame;
	Ally *ally;
	Boss *boss;
	FinalBoss *Fboss;
	NormalEnemy *e;
	Material mat;
	World *world;
	Light l[6];
	SaveAndLoad SAL;
	float lastx, lasty;
	ThirdPersonCamera *camera;
	map<char,bool> keys;
	UINT texture[20];
	bool dir[4];
	float xrot;
	float yrot;
	int Timer;
	int numberOfEnemyKilled;
	int lvl;
	int monstersCounter;
	int Divider;
	int waveNumber;
	GLuint tex;
	PacketsManager PM;
	Particle p;
	bool drawQuest;
	bool drawStatus;
	bool isDoubleKey;
	bool isMouseRightClick;
	bool isChestOpen;
	bool showDoorLocked;
	bool showKeyFound;
	bool OpenDoor1;
	bool OpenDoor2;
	bool Door1Opened;
	bool Door2Opened;
	bool Unprison;
	bool free;
	bool MissionComplete;
	bool isMDone;
	bool bossInc;
	bool waveDone;
	bool gameStarted;
	Model_3DS *chesto;
	Model_3DS *chestc;
	Model_3DS *Prison;
	Model_3DS *Door1;
	Model_3DS *Door2;
	Model_3DS *base;
	Model_3DS *crystal;
public:
	bool Is2D()
	{
		return this->is2D;
	}
	GameEngine()
	{
		isDoubleKey = false;
		isMouseRightClick = false;
		xrot = 0;
		yrot = 0;
		for(int i = 0 ; i < 4 ; i++)
			dir[i] = 0;
	}
	GameEngine(bool isLoaded,int *SomeValues,bool *flags,map<int,int> controls,World &w,ThirdPersonCamera &c,Hero &h,Graph &g,Boss &b,Flame *f,NormalEnemy *e,GameScreen &s,Model_3DS &m1,Model_3DS &m2,Model_3DS &m3,Model_3DS &m4,Model_3DS &m5,Ally &aly,int lvl,FinalBoss &fBoss,Model_3DS &ba,Model_3DS &cr,GLuint texture)
	{
		this->controls = controls;
		tex = texture;
		gameStarted = false;
		bossInc = false;
		waveDone = false;
		isMDone = false;
		MissionComplete = false;
		Unprison = false;
		free = false;
		Door1Opened = false;
		Door2Opened = false;
		OpenDoor1 = false;
		OpenDoor2 = false;
		showDoorLocked = false;
		showKeyFound = false;
		isChestOpen = false;
		drawStatus = false;
		drawQuest = false;
		isDoubleKey = false;
		isMouseRightClick = false;
		this->lvl = lvl;
		Divider = 1;
		waveNumber = 1;
		monstersCounter = 0;
		Timer = 0;
		numberOfEnemyKilled = 0;
		if(isLoaded)
		{
			Divider = SomeValues[3];
			waveNumber = SomeValues[4];
			monstersCounter = SomeValues[2];
			Timer = SomeValues[0];
			numberOfEnemyKilled = SomeValues[1];
			bossInc = flags[FLAG::_bossInc];
			Door1Opened = flags[FLAG::_Door1Opened];
			Door2Opened = flags[FLAG::_Door2Opened];
			drawQuest = flags[FLAG::_drawQuest];
			drawStatus = flags[FLAG::_drawStatus];
			free = flags[FLAG::_free];
			gameStarted = flags[FLAG::_gameStarted];
			isChestOpen = flags[FLAG::_isChestOpen];
			isMDone = flags[FLAG::_isMDone];
			MissionComplete = flags[FLAG::_MissionComplete];
			OpenDoor1 = flags[FLAG::_OpenDoor1];
			OpenDoor2 = flags[FLAG::_OpenDoor2];
			showDoorLocked = flags[FLAG::_showDoorLocked];
			showKeyFound = flags[FLAG::_showKeyFound];
			Unprison = flags[FLAG::_Unprison];
			waveDone = flags[FLAG::_waveDone];
		}
		xrot = 0;
		yrot = 0;
		for(int i = 0 ; i < 4 ; i++)
			dir[i] = 0;
		world = &w;
		camera = &c;
		hero = &h;
		graph = &g;
		boss = &b;
		flame = f;
		this->e = e;
		GS = &s;
		chestc = &m1;
		chesto = &m2;
		Prison = &m3;
		Door1 = &m4;
		Door2 = &m5;
		ally = &aly;
		Fboss = &fBoss;
		base = &ba;
		crystal = &cr;
	}

	void setTransform()
	{  
		glMatrixMode(GL_PROJECTION);
		GS->DrawLayOut(*hero,e[hero->TargetIndices[hero->EnemyIndex]],*boss,hero->TargetIndices[hero->EnemyIndex]);
		GS->UpdateMiniMap(*hero,*boss,e,lvl);
		if(hero->LevelUp && !drawStatus || drawStatus)
			GS->DrawLevelUp(*hero);
		if(hero->LevelUp)
			GS->SetSkillsInfo(lastx,lasty);
		if(drawQuest)
			GS->DrawQuestMenu(lvl);
		SE.SetWindowHandler(GetActiveWindow());
		if(lvl == 1 && controls[6] == 'y')
			SE.StartBackMusic(lvl);
		if(lvl == 2 && !gameStarted)
		{
			PlaySound("sounds\\EP.wav",NULL, SND_ASYNC);
			gameStarted = true;
		}
		if(lvl == 2 && Timer > 3900  && controls[6] == 'y')
			SE.StartBackMusic(lvl);
		char X[1000];
		itoa(lastx,X,10);
		char Y[1000];
		itoa(lasty,Y,10);
		camera->Tellgl(); 
	}
	void OpenDoor(int doorNumber)
	{
		if(doorNumber == 1 && OpenDoor1)
		{
			Door1->pos.y+= 0.25;
			if(Door1->pos.y > 20)
				OpenDoor1 = false;
		}
		else if(doorNumber == 2 && OpenDoor2)
		{
			Door2->pos.y+= 0.25;
			if(Door2->pos.y > 20)
				OpenDoor2 = false;
		}
	}
	void OpenPrison()
	{
		Prison->pos.y+= 0.25;
		if(Prison->pos.y > 20)
		{
			Unprison = false;
			free = true;
		}
	}
	void ResetEnemies()
	{
		world->InitializeEnemiesPosition(e,*boss,*Fboss,2);
		for(int i = 0 ; i < 20 ; i++)
		{
			e[i].HP = e[i].MaxHP;
			e[i].Dead = false;
			e[i].timeAfterDeath = 0;
			e[i].firstDeath = false;
			e[i].isDone = false;
			e[i].Reset();
		}
	}
	void Updatelvl1()
	{
		glLoadIdentity();
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setTransform();
		l[0].Update();
		l[0].LightPosition[0] = camera->GetTarget().x;
		l[0].LightPosition[1] = camera->GetTarget().y+100;
		l[0].LightPosition[2] = camera->GetTarget().z;	
		for(int i = 0 ; i < 5 ; i++)
			l[i+1].Update();
		mat.SetMaterial();	
		world->Draw();
		SE.SomeOneGotHit(CDH.HandleCollisions(lvl,e,*hero,*boss,*Fboss),controls[6]);
		hero->SetPlayerPosition(camera->GetTarget()); 
		world->CheckMapBoundaries(*hero,dir);
		if(world->GetY(camera->P.x,camera->P.z) > 0)
			camera->ZoomIn();
		else
			camera->ZoomOut();
		if(isChestOpen)
			chesto->Draw();
		else
			chestc->Draw();
		Prison->Draw();
		Door1->Draw();
		Door2->Draw();
		if(Unprison)
			OpenPrison();
		OpenDoor(1);
		OpenDoor(2);
		if(MissionComplete)
		{
			GS->DrawTeleporter(ally->Position.x,ally->Position.z-100,*camera);
			if(isMDone)
				GS->DrawMissionMessage(*camera,isMDone);
		}
		ally->Update();
		if(hero->isAutoLook)
		{
			hero->AutoLook(e,*boss,*Fboss);
			if(hero->NoTarget)
				hero->SetAutoLook();
		}
		else
			hero->SetRotation(camera->Rot.y-80);
		if(showKeyFound)
			GS->DrawBoxMessage(*chestc,*camera,showKeyFound);
		if(showDoorLocked)
			GS->DrawDoorMessage(*Door1,*camera,showDoorLocked);
		p.Draw(hero->GetPosition(),camera->Rot.y);
		hero->setHeroDirection(camera->GetLookDirection());
		camera->T.y = hero->y-19;
		hero->CamPos = camera->P;
		hero->R = camera->R;
		hero->breathValue = camera->breathValue;
		if(hero->Update())
			SE.SomeOneDied(SE.HERO);
		glLoadIdentity();
		glTranslatef(hero->Position.x,-20,hero->Position.z);
		glScalef(0.2,0.2,0.2);
		for(int i = 0 ; i < hero->Skills.size() ; i++)
			if(hero->Skills[i]->hasDuration && hero->Skills[i]->isSkillUsed)
				if(hero->Skills[i]->SkillDurationEnded)
					hero->EndSkill(i+1,*camera,e,*boss,*Fboss,mat);
				else
					hero->UseSkillsWithDuration(i+1,*camera,e,*boss,*Fboss,mat);
		if(hero->isAutoLook)
			if(hero->TargetIndices[hero->EnemyIndex] == 11)
				GS->DrawAutoLookMark(*boss);
			else if(hero->TargetIndices[hero->EnemyIndex] == 12)
				GS->DrawAutoLookMark(*Fboss);
			else
				GS->DrawAutoLookMark(e[hero->TargetIndices[hero->EnemyIndex]]);
		for(int i = 0 ; i < 14 ; i++)
		{
			e[i].SetTarget(hero->Position,-1);
			if(e[i].Update())
			{
				if(!e[i].firstDeath)
				{
					SE.SomeOneDied(SE.ENEMY);
					hero->IncreaseExpBy(15);
					hero->EXPincreased = ((0.64-0.01)/(hero->levels[hero->CurrentLevel]-hero->levels[hero->CurrentLevel-1]))*(hero->EXP);
					PM.DropPacket(e[i].GetPosition());
					e[i].firstDeath = true;
					numberOfEnemyKilled++;
				}
				GS->DrawEXP(e[i],*camera);
			}
		}
		boss->SetTarget(hero->Position,-1);
		if(boss->Update())	
		{
			if(!boss->firstDeath)
			{
				SE.SomeOneDied(SE.ENEMY);
				hero->IncreaseExpBy(50);
				hero->EXPincreased = ((0.68-0.02)/(hero->levels[hero->CurrentLevel]-hero->levels[hero->CurrentLevel-1]))*(hero->EXP);
				boss->firstDeath = true;
			}
			GS->DrawEXP(*boss,*camera);
		}
		for(int i = 0 ; i < 5 ; i++)
			flame[i].Update();
		PM.UpdatePackets(*hero,p);
		if(!hero->isAutoLook)
			GS->DrawAttackMark(*camera);
		if(camera->SniperMode)
			GS->DrawSniperView(*camera);
		else
			GS->DisableAllLayout = false;
		glFlush();
		glutSwapBuffers();
		glutPostRedisplay();
	}
	void Updatelvl2()
	{
		Timer ++;
		cout << Timer << endl;
		glLoadIdentity();
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setTransform();
		l[0].Update();
		l[0].LightPosition[0] = camera->GetTarget().x;
		l[0].LightPosition[1] = camera->GetTarget().y+100;
		l[0].LightPosition[2] = camera->GetTarget().z;	
		for(int i = 0 ; i < 5 ; i++)
			l[i+1].Update();
		mat.SetMaterial();	
		world->Draw();
		SE.SomeOneGotHit(CDH.HandleCollisions(lvl,e,*hero,*boss,*Fboss),controls[6]);
		hero->SetPlayerPosition(camera->GetTarget()); 
		world->CheckMapBoundaries(*hero,dir);
		if(world->GetY(camera->P.x,camera->P.z) > 0)
			camera->ZoomIn();
		else
			camera->ZoomOut();
		if(MissionComplete)
		{
			GS->DrawTeleporter(hero->Position.x,hero->Position.z,*camera);
			if(isMDone)
				GS->DrawMissionMessage(*camera,isMDone);
		}
		if(bossInc)
			GS->DrawBossMessage(*camera,bossInc);
		if(hero->isAutoLook)
		{
			hero->AutoLook(e,*boss,*Fboss);
			if(hero->NoTarget)
				hero->SetAutoLook();
		}
		else
			hero->SetRotation(camera->Rot.y-80);
		if(showKeyFound)
			GS->DrawBoxMessage(*chestc,*camera,showKeyFound);
		if(showDoorLocked)
			GS->DrawDoorMessage(*Door1,*camera,showDoorLocked);
		p.Draw(hero->GetPosition(),camera->Rot.y);
		hero->setHeroDirection(camera->GetLookDirection());
		camera->T.y = hero->y-19;
		hero->CamPos = camera->P;
		hero->R = camera->R;
		hero->breathValue = camera->breathValue;
		base->Draw();
		crystal->Draw();
		if(hero->Update())
			SE.SomeOneDied(SE.HERO);
		glLoadIdentity();
		glTranslatef(hero->Position.x,-20,hero->Position.z);
		glScalef(0.2,0.2,0.2);
		for(int i = 0 ; i < hero->Skills.size() ; i++)
			if(hero->Skills[i]->hasDuration && hero->Skills[i]->isSkillUsed)
				if(hero->Skills[i]->SkillDurationEnded)
					hero->EndSkill(i+1,*camera,e,*boss,*Fboss,mat);
				else
					hero->UseSkillsWithDuration(i+1,*camera,e,*boss,*Fboss,mat);
		if(hero->isAutoLook)
			if(hero->TargetIndices[hero->EnemyIndex] == 11)
				GS->DrawAutoLookMark(*boss);
			else if(hero->TargetIndices[hero->EnemyIndex] == 12)
				GS->DrawAutoLookMark(*Fboss);
			else
				GS->DrawAutoLookMark(e[hero->TargetIndices[hero->EnemyIndex]]);
		if(Timer >= 3000)
		{
			if(!(Timer %(int)(1000/Divider)))
			{
				waveDone = false;
				if(monstersCounter < waveNumber)
				{
					monstersCounter++;
					Divider += 2;
				}
			}
			for(int i = 0 ; i < monstersCounter*4 ; i++)
			{
				e[i].SetTarget(hero->Position,-1);
				if(e[i].Update())
				{
					if(!e[i].firstDeath)
					{
						SE.SomeOneDied(SE.ENEMY);
						hero->IncreaseExpBy(15);
						hero->EXPincreased = ((0.64-0.01)/(hero->levels[hero->CurrentLevel]-hero->levels[hero->CurrentLevel-1]))*(hero->EXP);
						PM.DropPacket(e[i].GetPosition());
						e[i].firstDeath = true;
						numberOfEnemyKilled++;
					}
					GS->DrawEXP(e[i],*camera);
				}
			}
			if(numberOfEnemyKilled >= waveNumber*4 && !waveDone)
			{
				if(waveNumber < 5)
				{
					numberOfEnemyKilled = 0;
					waveDone = true;
					ResetEnemies();
					waveNumber++;
					monstersCounter = 1;
					Divider = 1;
				}
			}
		}
		if(Timer >= 10000)
		{
			bossInc = true;
			Fboss->SetTarget(hero->Position,-1);
			if(Fboss->Update())	
			{
				if(!Fboss->firstDeath)
				{
					SE.SomeOneDied(SE.ENEMY);
					hero->IncreaseExpBy(100);
					hero->EXPincreased = ((0.68-0.02)/(hero->levels[hero->CurrentLevel]-hero->levels[hero->CurrentLevel-1]))*(hero->EXP);
					Fboss->firstDeath = true;
				}
				GS->DrawEXP(*Fboss,*camera);
				GS->DrawEXP(*Fboss,*camera);
			}
		}
		for(int i = 0 ; i < 5 ; i++)
			flame[i].Update();
		PM.UpdatePackets(*hero,p);
		if(!hero->isAutoLook)
			GS->DrawAttackMark(*camera);
		if(camera->SniperMode)
			GS->DrawSniperView(*camera);
		else
			GS->DisableAllLayout = false;
		glFlush();
		glutSwapBuffers();
		glutPostRedisplay();
	}
	void Update()
	{
		if(lvl == 1)
			Updatelvl1();
		else if(lvl == 2)
			Updatelvl2();
	}



	void HandleMouse(int button,int state ,int x , int y)
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			hero->Attack();
			if(GS->isStatesOpened)
				GS->SetStatesAndSkills(*hero,x,y);
			if(hero->isAutoLook && hero->weaponNumber == 2)
			{
				if(hero->TargetIndices[hero->EnemyIndex] == 11)
					boss->HP -= 2;
				else
					e[hero->TargetIndices[hero->EnemyIndex]].HP -= 2;
			}
			break;
		}
	}
	void MousePassiveMotion(int x, int y) {
		int diffx=x-lastx; 
		int diffy=y-lasty; 
		if(diffx == 0)
			return;
		lastx=x; 
		lasty=y; 
		xrot += (float) diffy; 
		if(diffx < 0)
		{
			camera->RotateLeft();
			camera->RotateLeft();
			camera->RotateLeft();
		}
		else
		{
			camera->RotateRight();
			camera->RotateRight();
			camera->RotateRight();
		}
		if(x < 10 || x > 1024)
			SetCursorPos(512,400);
	}

	void Initialize()
	{
		world->InitializeObjectsPosition(flame,l);
	}

	void GetDoubleKeyPress()
	{

		float xrotrad, yrotrad;
		int tempX = camera->T.x;
		int tempZ = camera->T.z;/*
			controls[0]='w';
			controls[1]='s';
			controls[2]='a';
			controls[3]='d';
			controls[4]=' ';
			controls[5]='j';*/
		if(keys[controls[2]]&&keys[controls[0]])
		{
			isDoubleKey = true;
			hero->Walk();
			camera->Walk(0.1*hero->Speed);
			camera->Strafe(-0.05*hero->Speed);
		}
		if(keys[controls[3]]&&keys[controls[0]])
		{
			isDoubleKey = true;
			hero->Walk();
			camera->Walk(0.1*hero->Speed);
			camera->Strafe(0.05*hero->Speed);
		}
		if(keys[controls[3]]&&keys[controls[1]])
		{
			isDoubleKey = true;
			hero->Walk();
			camera->Walk(-0.1*hero->Speed);
			camera->Strafe(0.05*hero->Speed);
		}
		if(keys[controls[2]]&&keys[controls[1]])
		{
			isDoubleKey = true;
			hero->Walk();
			camera->Walk(-0.1*hero->Speed);
			camera->Strafe(-0.05*hero->Speed);
		}
		if(keys[controls[2]] && !isDoubleKey)
		{
			hero->Turn();
			camera->Strafe(-0.05*hero->Speed);
		}
		if(keys[controls[3]] && !isDoubleKey)
		{
			hero->Turn();
			camera->Strafe(0.05*hero->Speed);
		}
		if(keys[controls[0]] && !isDoubleKey)
		{
			hero->Walk();
			camera->Walk(0.1*hero->Speed);
		}
		if(keys[controls[1]] && !isDoubleKey)
		{
			hero->Walk();
			camera->Walk(-0.1*hero->Speed);
		}
		ValidatePosition();
		world->validateMovement(*camera,tempX,tempZ,dir);
		glutPostRedisplay();
	}
	void GetSpecialDownPress(int key)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			camera->RotateUp();
			break;
		case GLUT_KEY_DOWN:
			camera->RotateDown();
			break;
		case GLUT_KEY_LEFT:
			camera->RotateLeft();
			break;
		case GLUT_KEY_RIGHT:
			camera->RotateRight();
			break;
		}
	}

	void GetKeyboardUpPress(int key)
	{
		keys[key] = false;
		if(key == controls[0] ||key == controls[1] ||key == controls[2] ||key == controls[3])
			isDoubleKey = false;
		if (key == controls[0] || key == controls[1] || key == controls[2] || key == controls[3])
		{
			hero->Idle();
		}
		glutPostRedisplay();
	}
	void Unlock()
	{
		if(lvl == 1)
		{
			if(hero->Position.x > chestc->pos.x-30 && hero->Position.x < chestc->pos.x+30 && hero->Position.z > chestc->pos.z-50 && hero->Position.z < chestc->pos.z+50 ) 
			{
				if(numberOfEnemyKilled >= 10)
				{
					showKeyFound = true;
					isChestOpen = true;
				}
			}
			else if(hero->Position.x > Door1->pos.x-100 && hero->Position.x < Door1->pos.x+100 && hero->Position.z > Door1->pos.z-50 && hero->Position.z < Door1->pos.z+50 )
			{
				if(numberOfEnemyKilled >= 8)	
				{
					OpenDoor1 = true;
					Door1Opened = true;
				}
			}
			else if(!isChestOpen && hero->Position.x > Door2->pos.x-100 && hero->Position.x < Door2->pos.x+100 && hero->Position.z > Door2->pos.z-50 && hero->Position.z < Door2->pos.z+50 )
			{
				showDoorLocked = true;
			}
			else if(isChestOpen && hero->Position.x > Door2->pos.x-100 && hero->Position.x < Door2->pos.x+100 && hero->Position.z > Door2->pos.z-50 && hero->Position.z < Door2->pos.z+50 )
			{
				OpenDoor2 = true;
				Door2Opened = true;
			}
			else if(free && (hero->Position.x > ally->Position.x-30 && hero->Position.x < ally->Position.x+30 && hero->Position.z > ally->Position.z-50 && hero->Position.z < ally->Position.z+50 )) 
			{
				ally->Revive();
				MissionComplete = true;
				isMDone = true;
			}
			else if(hero->Position.x > Prison->pos.x-100 && hero->Position.x < Prison->pos.x+100 && hero->Position.z > Prison->pos.z-100 && hero->Position.z < Prison->pos.z+100 ) 
			{
				if(boss->Dead || boss->firstDeath)
					Unprison = true;
			}
			else if(MissionComplete && (hero->Position.x > ally->Position.x-30 && hero->Position.x < ally->Position.x+30 && hero->Position.z > ally->Position.z-100-50 && hero->Position.z < ally->Position.z-100+50 )) 
			{
				ScreenManager::GoToNextLevel(controls);
			}
		}
	}
	void ValidatePosition()
	{
		if(lvl == 1)
		{
			if(hero->Position.x > chestc->pos.x-30 && hero->Position.x < chestc->pos.x+30 && hero->Position.z > chestc->pos.z-30 && hero->Position.z < chestc->pos.z+30 )
			{
				dir[World::direction::NegZ_axis] = 1;
			}
			if(!Door1Opened && !OpenDoor1)
				if(hero->Position.x > Door1->pos.x-100 && hero->Position.x < Door1->pos.x+100 && hero->Position.z > Door1->pos.z-30 && hero->Position.z < Door1->pos.z+30)
					dir[World::direction::NegZ_axis] = 1;
			if(!Door2Opened && !OpenDoor2)
				if(hero->Position.x > Door2->pos.x-100 && hero->Position.x < Door2->pos.x+100 && hero->Position.z > Door2->pos.z-30 && hero->Position.z < Door2->pos.z+30)
					dir[World::direction::NegZ_axis] = 1;
			if(free && (hero->Position.x > ally->Position.x-10 && hero->Position.x < ally->Position.x+10 && hero->Position.z > ally->Position.z-20 && hero->Position.z < ally->Position.z+20 )) 
			{
				dir[World::direction::NegZ_axis] = 1;
			}
			if(!free && (hero->Position.x > Prison->pos.x-30 && hero->Position.x < Prison->pos.x+30 && hero->Position.z > Prison->pos.z-30 && hero->Position.z < Prison->pos.z+30  )) 
				dir[World::direction::NegZ_axis] = 1;
		}
	}
	void GetKeyboardDownPress(int key)
	{
		for(int i = 0 ; i < 6 ; i++)
			if(key == controls[i])
				keys[controls[i]] = true;
		keys[key] = true;
		if(key ==  27 )
		{
			GLubyte *pixels = new GLubyte [1024*1024*3];
			glReadPixels(0, 0, 1024, 1024, GL_RGB,GL_UNSIGNED_BYTE, pixels);
			bool flags[18];
			flags[FLAG::_bossInc] = bossInc;
			flags[FLAG::_Door1Opened] = Door1Opened;
			flags[FLAG::_Door2Opened] = Door2Opened;
			flags[FLAG::_drawQuest] = drawQuest;
			flags[FLAG::_drawStatus] = drawStatus;
			flags[FLAG::_free] = free;
			flags[FLAG::_gameStarted] = gameStarted;
			flags[FLAG::_isChestOpen] = isChestOpen;
			flags[FLAG::_isDoubleKey] = isDoubleKey;
			flags[FLAG::_isMDone] = isMDone;
			flags[FLAG::_isMouseRightClick] = isMouseRightClick;
			flags[FLAG::_MissionComplete] = MissionComplete;
			flags[FLAG::_OpenDoor1] = OpenDoor1;
			flags[FLAG::_OpenDoor2] = OpenDoor2;
			flags[FLAG::_showDoorLocked] = showDoorLocked;
			flags[FLAG::_showKeyFound] = showKeyFound;
			flags[FLAG::_Unprison] = Unprison;
			flags[FLAG::_waveDone] = waveDone;
			SAL.SetAttributes(flags,lvl,e,*hero,*Fboss,*boss,*camera,pixels,Timer,numberOfEnemyKilled,monstersCounter,Divider,waveNumber);
			ScreenManager::AddScreen(new PauseScreen(tex,SAL));
			ScreenManager::SetControls(controls);
		}
		if(key == controls[4])
			hero->Jump();
		if(key == controls[5])
		{
			hero->Attack();
			if(hero->isAutoLook && hero->weaponNumber == 2)
			{
				if(hero->TargetIndices[hero->EnemyIndex] == 11)
					boss->HP -= 2;
				else
					e[hero->TargetIndices[hero->EnemyIndex]].HP -= 2;
			}
		}
		switch(toupper(key))
		{
		case '1':
			if(hero->isSkillUsed(1))
				hero->EndSkill(1,*camera,e,*boss,*Fboss,mat);
			hero->UseSkill(1,*camera,e,*boss,*Fboss);
			break;
		case '2':
			if(hero->isSkillUsed(2))
				hero->EndSkill(2,*camera,e,*boss,*Fboss,mat);
			hero->UseSkill(2,*camera,e,*boss,*Fboss);
			break;
		case '3':
			if(hero->isSkillUsed(3))
				hero->EndSkill(3,*camera,e,*boss,*Fboss,mat);
			hero->UseSkill(3,*camera,e,*boss,*Fboss);
			break;
		case '4':
			if(hero->isSkillUsed(4))
				hero->EndSkill(4,*camera,e,*boss,*Fboss,mat);
			hero->UseSkill(4,*camera,e,*boss,*Fboss);
			break;
		case '5':
			if(hero->isSkillUsed(5))
				hero->EndSkill(5,*camera,e,*boss,*Fboss,mat);
			hero->UseSkill(5,*camera,e,*boss,*Fboss);
			break;
		case '6':
			if(hero->isSkillUsed(6))
				hero->EndSkill(6,*camera,e,*boss,*Fboss,mat);
			hero->UseSkill(6,*camera,e,*boss,*Fboss);
			break;
		case 'E':
			Unlock();
			break;
		case 'Q':
			drawQuest = !drawQuest;
			break;
		case 'F':
			hero->ChangeWeaponBetweenMeleeAndRanged();
			break;
		//case 'X':
		//	hero->ChangeRangedWeapons();
		//	break;
		case 'R':
			hero->ChangeWalkingMode();
			break;
		case 'L':
			hero->SetAutoLook();
			break;
		case 'C':
			drawStatus = !drawStatus;
			break;
		case 'V':
			hero->ChangeTarget();
			break;
		/*case 'T':
			camera->ZoomIn();
			break;
		case 'G':
			camera->ZoomOut();
			break;*/
		}
	}

};
#endif 
