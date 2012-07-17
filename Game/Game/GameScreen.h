#include<Windows.h>
#include<gl\GL.H>
#include<gl\GLU.H>
class GameScreen
{
public:
	int texture[75];
	bool isStatesOpened;
	map<string,int> skillMap;
	bool DisableAllLayout;
	int time;
	GameScreen(){angle = 0;time = 0;isStatesOpened = false;DisableAllLayout = false;}
	void LoadTextures()
	{
			texture[0] = LoadGLTexture("images\\others\\BackHP.bmp");
			texture[1] = LoadGLTexture("images\\others\\HP.bmp");	
			texture[2] = LoadGLTexture("images\\aims\\a3.bmp");
			texture[3] = LoadGLTexture("images\\maps\\WorldMap22.bmp");
			texture[4] = LoadGLTexture("images\\faces\\MapsFace.bmp");
			texture[5] = LoadGLTexture("images\\faces\\MapBoss.bmp");
			texture[6] = LoadGLTexture("images\\faces\\MapEnemy.bmp");
			texture[7] = LoadGLTexture("images\\faces\\ZeldaFace.bmp");
			texture[8] = LoadGLTexture("images\\faces\\RazielFace.bmp");
			texture[9] = LoadGLTexture("images\\aims\\a2.bmp");
			texture[10] = LoadGLTexture("images\\others\\MP.bmp");
			texture[11] = LoadGLTexture("images\\others\\EXP.bmp");
			texture[12] = LoadGLTexture("images\\others\\0P.bmp");
			texture[13] = LoadGLTexture("images\\others\\1P.bmp");
			texture[14] = LoadGLTexture("images\\aims\\a4.bmp");
			texture[15] = LoadGLTexture("images\\quests\\Quest1.bmp");
			texture[16] = LoadGLTexture("images\\quests\\Quest2.bmp");
			texture[17] = LoadGLTexture("images\\pop_up\\DoorLocked.bmp");
			texture[18] = LoadGLTexture("images\\pop_up\\EnemyEXP.bmp");
			texture[19] = LoadGLTexture("images\\pop_up\\BossEXP.bmp");
			texture[20] = LoadGLTexture("images\\faces\\sFace1.bmp");
			texture[21] = LoadGLTexture("images\\faces\\sFace2.bmp");
			texture[22] = LoadGLTexture("images\\faces\\sFace3.bmp");
			texture[23] = LoadGLTexture("images\\faces\\sFace4.bmp");
			texture[24] = LoadGLTexture("images\\faces\\sFace5.bmp");
			texture[25] = LoadGLTexture("images\\faces\\sFace6.bmp");
			texture[26] = LoadGLTexture("images\\menus\\LevelUp1.bmp");
			texture[27] = LoadGLTexture("images\\menus\\SM.bmp");
			texture[28] = LoadGLTexture("images\\menus\\SMH.bmp");
			texture[29] = LoadGLTexture("images\\menus\\SMHB.bmp");
			texture[30] = LoadGLTexture("images\\menus\\SN.bmp");
			texture[31] = LoadGLTexture("images\\menus\\SNL.bmp");
			texture[32] = LoadGLTexture("images\\menus\\SNLU.bmp");
			texture[33] = LoadGLTexture("images\\menus\\SNSM.bmp");
			texture[34] = LoadGLTexture("images\\menus\\SNSML.bmp");
			texture[35] = LoadGLTexture("images\\menus\\SNSMLH.bmp");
			texture[36] = LoadGLTexture("images\\menus\\SNSMLHU.bmp");
			texture[37] = LoadGLTexture("images\\menus\\SNSMLHUB.bmp");
			texture[38] = LoadGLTexture("images\\menus\\SNSMLU.bmp");
			texture[39] = LoadGLTexture("images\\menus\\SNSMH.bmp");
			texture[40] = LoadGLTexture("images\\menus\\SNSMHB.bmp");
			texture[41] = LoadGLTexture("images\\skills\\L.bmp");
			texture[42] = LoadGLTexture("images\\skills\\B.bmp");
			texture[43] = LoadGLTexture("images\\skills\\H.bmp");
			texture[44] = LoadGLTexture("images\\skills\\V.bmp");
			texture[45] = LoadGLTexture("images\\skills\\SM1.bmp");
			texture[46] = LoadGLTexture("images\\skills\\SN1.bmp");
			texture[47] = LoadGLTexture("images\\skills\\U.bmp");
			texture[48] = LoadGLTexture("images\\skills\\S.bmp");
			texture[49] = LoadGLTexture("images\\skills\\LC.bmp");
			texture[50] = LoadGLTexture("images\\skills\\BC.bmp");
			texture[51] = LoadGLTexture("images\\skills\\HC.bmp");
			texture[52] = LoadGLTexture("images\\skills\\VC.bmp");
			texture[53] = LoadGLTexture("images\\skills\\SMC.bmp");
			texture[54] = LoadGLTexture("images\\skills\\SNC.bmp");
			//texture[55] = LoadGLTexture("images\\skills\\UC.bmp");
			texture[56] = LoadGLTexture("images\\skills\\SC.bmp");
			texture[57] = LoadGLTexture("images\\others\\SkillSlots.bmp");
			texture[58] = LoadGLTexture("images\\menus\\LInfo.bmp");
			texture[59] = LoadGLTexture("images\\menus\\BInfo.bmp");
			texture[60] = LoadGLTexture("images\\menus\\HInfo.bmp");
			texture[61] = LoadGLTexture("images\\menus\\VInfo.bmp");
			texture[62] = LoadGLTexture("images\\menus\\SMInfo.bmp");
			texture[63] = LoadGLTexture("images\\menus\\SNInfo.bmp");
			texture[64] = LoadGLTexture("images\\menus\\UInfo.bmp");
			texture[65] = LoadGLTexture("images\\menus\\SInfo.bmp");
			texture[66] = LoadGLTexture("images\\pop_up\\KeyFound.bmp");
			texture[67] = LoadGLTexture("images\\others\\Tele.bmp");
			texture[68] = LoadGLTexture("images\\pop_up\\MissionComplete.bmp");
			texture[69] = LoadGLTexture("images\\pop_up\\BossInc.bmp");
			texture[70] = LoadGLTexture("images\\maps\\WorldMap23.bmp");
			GenerateSkillMap();
	}
	void GenerateSkillMap()
	{
		skillMap["L"] = texture[41];
		skillMap["B"] = texture[42];
		skillMap["H"] = texture[43];
		skillMap["V"] = texture[44];
		skillMap["SM"] = texture[45];
		skillMap["SN"] = texture[46];
		skillMap["U"] = texture[47];
		skillMap["S"] = texture[48];
		skillMap["LC"] = texture[49];
		skillMap["BC"] = texture[50];
		skillMap["HC"] = texture[51];
		skillMap["VC"] = texture[52];
		skillMap["SMC"] = texture[53];
		skillMap["SNC"] = texture[54];
		skillMap["UC"] = texture[55];
		skillMap["SC"] = texture[56];
		skillMap["LInfo"] = texture[58];
		skillMap["BInfo"] = texture[59];
		skillMap["HInfo"] = texture[60];
		skillMap["VInfo"] = texture[61];
		skillMap["SMInfo"] = texture[62];
		skillMap["SNInfo"] = texture[63];
		skillMap["UInfo"] = texture[64];
		skillMap["SInfo"] = texture[65];
	}
	void DrawAutoLookMark(FinalBoss &currentEnemy)
	{
		if(DisableAllLayout)
			return;
		glColor4f(1,1,1,0.5);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDepthMask(false);
		glTranslatef(currentEnemy.GetPosition().x,-10,currentEnemy.GetPosition().z);
		glBindTexture(GL_TEXTURE_2D,texture[9]);
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
	}
	void DrawAutoLookMark(Boss &currentEnemy)
	{
		if(DisableAllLayout)
			return;
		glColor4f(1,1,1,0.5);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDepthMask(false);
		glTranslatef(currentEnemy.GetPosition().x,-10,currentEnemy.GetPosition().z);
		glBindTexture(GL_TEXTURE_2D,texture[9]);
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
	}
	void DrawAutoLookMark(NormalEnemy &currentEnemy)
	{
		if(DisableAllLayout)
			return;
		glColor4f(1,1,1,0.5);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDepthMask(false);
		glTranslatef(currentEnemy.GetPosition().x,-10,currentEnemy.GetPosition().z);
		glBindTexture(GL_TEXTURE_2D,texture[9]);
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
	}
	void UpdateMiniMap(Hero &hero,Boss &boss,NormalEnemy e[],int lvl)
	{
		if(DisableAllLayout)
			return;
		glColor3f(1,1,1);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		{
			glTranslatef(1.29,-1.78,0);
			glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D,texture[0]);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(0.24,-0.02,0);
				glTexCoord2f(1,1);
				glVertex3f(.51,-0.02,0);
				glTexCoord2f(1,0);
				glVertex3f(.51,.52,0);		
				glTexCoord2f(0,0);
				glVertex3f(0.24,.52,0);
			}
			glEnd();
			if(lvl == 1)
				glBindTexture(GL_TEXTURE_2D,texture[3]);
			else if(lvl == 2)
				glBindTexture(GL_TEXTURE_2D,texture[70]);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(0.25,0,0);
				glTexCoord2f(1,1);
				glVertex3f(.5,0,0);
				glTexCoord2f(1,0);
				glVertex3f(.5,.5,0);		
				glTexCoord2f(0,0);
				glVertex3f(0.25,.5,0);
			}
			glEnd();
			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D,texture[4]);
				glColor3f(1,1,1);
				glTranslatef(0.24,0.5,0);
				glScalef(2,2,0);
				glTranslatef((hero.Position.x+550)/(4500*2),-(hero.Position.z-150)/(6200*2),0);
				glBegin(GL_POLYGON);
				{
					glTexCoord2f(0,1);
					glVertex3f(0.0,-0.01,0);
					glTexCoord2f(1,1);
					glVertex3f(.01,-0.01,0);
					glTexCoord2f(1,0);
					glVertex3f(.01,0,0);		
					glTexCoord2f(0,0);
					glVertex3f(0.0,0,0);
				}
				glEnd();
			}
			glPopMatrix();
			for(int i = 0 ; i < 10 ; i++)
			{
				if(e[i].IsDead())
					continue;
				glPushMatrix();
				{
					glBindTexture(GL_TEXTURE_2D,texture[6]);
					glColor3f(1,1,1);
					glTranslatef(0.24,0.5,0);
					glScalef(0.5,0.5,0);
					glTranslatef(((e[i].GetPosition().x+550)/(4500*2))*4,-((e[i].GetPosition().z-150)/(6200*2))*4,0);
					glBegin(GL_POLYGON);
					{
						glTexCoord2f(0,1);
						glVertex3f(0.0,-0.01,0);
						glTexCoord2f(1,1);
						glVertex3f(.01,-0.01,0);
						glTexCoord2f(1,0);
						glVertex3f(.01,0,0);		
						glTexCoord2f(0,0);
						glVertex3f(0.0,0,0);
					}
					glEnd();
				}
				glPopMatrix();
			}
			glPushMatrix();
			{
				if(!boss.IsDead())
				{
					glBindTexture(GL_TEXTURE_2D,texture[5]);
					glTranslatef(0.24,0.5,0);
					glScalef(2,2,0);
					glTranslatef((boss.GetPosition().x+550)/(4500*2),-(boss.GetPosition().z-150)/(6200*2),0);
					glBegin(GL_POLYGON);
					{
						glTexCoord2f(0,1);
						glVertex3f(0.0,-0.01,0);
						glTexCoord2f(1,1);
						glVertex3f(.01,-0.01,0);
						glTexCoord2f(1,0);
						glVertex3f(.01,0,0);		
						glTexCoord2f(0,0);
						glVertex3f(0.0,0,0);
					}
					glEnd();
				}
			}
			glPopMatrix();
				
		}
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	void DrawLayOut(Hero &hero,NormalEnemy &currentEnemy,Boss &boss,int Index)
	{	
		if(DisableAllLayout)
			return;
		glLoadIdentity();
		float EnemyHealthDecreased;
		glDisable(GL_LIGHTING);
		if(hero.isAutoLook && !hero.NoTarget)
		{
			glPushMatrix();
			{
				if(Index == 11)
				{
					if(boss.HP > 0)
					{
						EnemyHealthDecreased = (0.48-0.02)/boss.MaxHP*(boss.MaxHP-boss.HP);
					}
					else
						EnemyHealthDecreased = (0.48-0.02)/boss.MaxHP*boss.MaxHP;
				}
				else if(currentEnemy.HP > 0)
					EnemyHealthDecreased = (0.48-0.02)/currentEnemy.MaxHP*(currentEnemy.MaxHP-currentEnemy.HP);
				else 
					EnemyHealthDecreased = (0.48-0.02)/currentEnemy.MaxHP*currentEnemy.MaxHP;
				glBindTexture(GL_TEXTURE_2D,texture[0]);
				glTranslatef(0.5,0.8,0);
				glBegin(GL_POLYGON);
				{
					glTexCoord2f(0,1);
					glVertex3f(0,0.11,0);
					glTexCoord2f(1,1);
					glVertex3f(.5,0.11,0);
					glTexCoord2f(1,0);
					glVertex3f(.5,.20,0);		
					glTexCoord2f(0,0);
					glVertex3f(0,.20,0);
				}
				glEnd();
				glBindTexture(GL_TEXTURE_2D,texture[1]);
				glColor3f(EnemyHealthDecreased*2.5,1-EnemyHealthDecreased*2.5,0);
				glBegin(GL_POLYGON);
				{
					glTexCoord2f(0,1);
					glVertex3f(0.02,0.12,0);
					glTexCoord2f(1,1);
					glVertex3f(.48-EnemyHealthDecreased,0.12,0);
					glTexCoord2f(1,0);
					glVertex3f(.48-EnemyHealthDecreased,.19,0);		
					glTexCoord2f(0,0);
					glVertex3f(0.02,.19,0);
				}
				glEnd();
				if(Index == 11)
					glBindTexture(GL_TEXTURE_2D,texture[7]);
				else
					glBindTexture(GL_TEXTURE_2D,texture[8]);
				glColor3f(1,1,1);
				glTranslatef(-0.2,-0.1,0);
				glBegin(GL_POLYGON);
				{
					glTexCoord2f(0,1);
					glVertex3f(0.1,0.11,0);
					glTexCoord2f(1,1);
					glVertex3f(.2,0.11,0);
					glTexCoord2f(1,0);
					glVertex3f(.2,.3,0);		
					glTexCoord2f(0,0);
					glVertex3f(0.1,.3,0);
				}
				glEnd();
			}
			glPopMatrix();
		}
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,texture[19+hero.CurrentLevel]);
		glTranslatef(-1,0.7,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(0.0,0.11,0);
			glTexCoord2f(1,1);
			glVertex3f(.15,0.11,0);
			glTexCoord2f(1,0);
			glVertex3f(.15,.3,0);		
			glTexCoord2f(0,0);
			glVertex3f(0.0,.3,0);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glTranslatef(0.2,0.1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(-0.05,0.11,0);
			glTexCoord2f(1,1);
			glVertex3f(.45,0.11,0);
			glTexCoord2f(1,0);
			glVertex3f(.45,.20,0);		
			glTexCoord2f(0,0);
			glVertex3f(-0.05,.20,0);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D,texture[1]);
		glColor3f(hero.HealthPointDecreased*2.5,1-hero.HealthPointDecreased*2.5,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(-0.04,0.12,0);
			glTexCoord2f(1,1);
			glVertex3f(.44-hero.HealthPointDecreased,0.12,0);
			glTexCoord2f(1,0);
			glVertex3f(.44-hero.HealthPointDecreased,.19,0);		
			glTexCoord2f(0,0);
			glVertex3f(-0.04,.19,0);
		}
		glEnd();
		glColor3f(1,1,1);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D,texture[0]);
			glTranslatef(0,-0.14,0);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(-0.05,0.16,0);
				glTexCoord2f(1,1);
				glVertex3f(.45,0.16,0);
				glTexCoord2f(1,0);
				glVertex3f(.45,.25,0);		
				glTexCoord2f(0,0);
				glVertex3f(-0.05,.25,0);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D,texture[10]);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(-0.04,0.17,0);
				glTexCoord2f(1,1);
				glVertex3f(.44-hero.ManaPointDecreased,0.17,0);
				glTexCoord2f(1,0);
				glVertex3f(.44-hero.ManaPointDecreased,.24,0);		
				glTexCoord2f(0,0);
				glVertex3f(-0.04,.24,0);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D,texture[0]);
			glTranslatef(0,0.12,0);
			glTranslatef(-0.2,-0.14,0);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(0,0.13,0);
				glTexCoord2f(1,1);
				glVertex3f(.65,0.13,0);
				glTexCoord2f(1,0);
				glVertex3f(.65,.19,0);		
				glTexCoord2f(0,0);
				glVertex3f(0,.19,0);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D,texture[11]);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(0.01,0.14,0);
				glTexCoord2f(1,1);
				glVertex3f(0.01+hero.EXPincreased,0.14,0);
				glTexCoord2f(1,0);
				glVertex3f(0.01+hero.EXPincreased,.18,0);		
				glTexCoord2f(0,0);
				glVertex3f(0.01,.18,0);
			}
			glEnd();
			glLoadIdentity();
			glBindTexture(GL_TEXTURE_2D,texture[57]);
			glTranslatef(-0.96,0.4,0);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(-0.04,-1.0,0);
				glTexCoord2f(1,1);
				glVertex3f(.08,-1.0,0);
				glTexCoord2f(1,0);
				glVertex3f(.08,.25,0);		
				glTexCoord2f(0,0);
				glVertex3f(-0.04,.25,0);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D,texture[44]);
			glScalef(0.8,0.8,1);
			glTranslatef(0.01,0.04,0);
			int numSkills = hero.Skills.size();
			for(int i = 0 ; i < numSkills;i++)
			{
				if(hero.Skills[i]->isSkillOnCoolDown)
					glBindTexture(GL_TEXTURE_2D,skillMap[hero.Skills[i]->SkillName+"C"]);
				else
					glBindTexture(GL_TEXTURE_2D,skillMap[hero.Skills[i]->SkillName]);
				glBegin(GL_POLYGON);
				{
					glTexCoord2f(0,1);
					glVertex3f(-0.04,0.02,0);
					glTexCoord2f(1,1);
					glVertex3f(.07,0.02,0);
					glTexCoord2f(1,0);
					glVertex3f(.07,.2,0);		
					glTexCoord2f(0,0);
					glVertex3f(-0.04,.2,0);
				}
				glEnd();
				glTranslatef(0,-0.245,0);
			}
		}
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	void DrawEXP(NormalEnemy &currentEnemy,ThirdPersonCamera &camera)
	{
		if(currentEnemy.timeAfterDeath > 300)
			return;
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[18]);
		glDepthMask(false);
		glTranslatef(currentEnemy.GetPosition().x,-10,currentEnemy.GetPosition().z);
		glRotatef(camera.Rot.y,0,1,0);
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
		glEnable(GL_LIGHTING);
	}
	void DrawEXP(Boss &currentEnemy,ThirdPersonCamera &camera)
	{
		if(currentEnemy.timeAfterDeath > 300)
			return;
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[19]);
		glDepthMask(false);
		glTranslatef(currentEnemy.GetPosition().x,-10,currentEnemy.GetPosition().z);
		glRotatef(camera.Rot.y,0,1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(5,2,0);
			glTexCoord2f(0,1);
			glVertex3f(5,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-5,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-5,2,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	void DrawEXP(FinalBoss &currentEnemy,ThirdPersonCamera &camera)
	{
		if(currentEnemy.timeAfterDeath > 300)
			return;
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[19]);
		glDepthMask(false);
		glTranslatef(currentEnemy.GetPosition().x,-10,currentEnemy.GetPosition().z);
		glRotatef(camera.Rot.y,0,1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(5,2,0);
			glTexCoord2f(0,1);
			glVertex3f(5,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-5,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-5,2,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	float angle;
	void DrawTeleporter(int x,int z,ThirdPersonCamera &camera)
	{
		angle++;
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[67]);
		glDepthMask(false);
		glTranslatef(x,-10,z);
		glRotatef(camera.Rot.y,0,1,0);
		glRotatef(angle,0,0,1);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(10,20,0);
			glTexCoord2f(0,1);
			glVertex3f(10,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-10,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-10,20,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	void DrawBossMessage(ThirdPersonCamera &camera,bool &isOpen)
	{
		if(time++ > 300)
		{
			isOpen = false;
			time = 0;
		}
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[69]);
		glDepthMask(false);
		glTranslatef(camera.T.x,-10,camera.T.z);
		glRotatef(camera.Rot.y,0,1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(10,5,0);
			glTexCoord2f(0,1);
			glVertex3f(10,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-10,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-10,5,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	void DrawMissionMessage(ThirdPersonCamera &camera,bool &isOpen)
	{
		if(time++ > 300)
		{
			isOpen = false;
			time = 0;
		}
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[68]);
		glDepthMask(false);
		glTranslatef(camera.T.x,-10,camera.T.z);
		glRotatef(camera.Rot.y,0,1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(10,5,0);
			glTexCoord2f(0,1);
			glVertex3f(10,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-10,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-10,5,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	void DrawBoxMessage(Model_3DS &chest,ThirdPersonCamera &camera,bool &isOpen)
	{
		if(time++ > 300)
		{
			isOpen = false;
			time = 0;
		}
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[66]);
		glDepthMask(false);
		glTranslatef(camera.T.x,-10,camera.T.z);
		glRotatef(camera.Rot.y,0,1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(10,5,0);
			glTexCoord2f(0,1);
			glVertex3f(10,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-10,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-10,5,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	void DrawDoorMessage(Model_3DS &door,ThirdPersonCamera &camera,bool &isOpen)
	{
		if(time++ > 300)
		{
			isOpen = false;
			time = 0;
		}
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[17]);
		glDepthMask(false);
		glTranslatef(camera.T.x,-10,camera.T.z);
		glRotatef(camera.Rot.y,0,1,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(10,5,0);
			glTexCoord2f(0,1);
			glVertex3f(10,0,0);
			glTexCoord2f(1,1);
			glVertex3f(-10,0,0);
			glTexCoord2f(1,0);
			glVertex3f(-10,5,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
	void DrawAttackMark(ThirdPersonCamera &camera)
	{
		if(DisableAllLayout)
			return;
		Vector3 P = camera.T + camera.GetLookDirection()*10;
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[2]);
		glDepthMask(false);
		glTranslatef(P.x,P.y+10,P.z);
		glRotatef(camera.Rot.y+20,0,1,0);
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
		glEnable(GL_LIGHTING);
	}
	void SetStatesAndSkills(Hero &hero,int x,int y)
	{
		if(hero.availabeAttributePoint)
		{
			//MS
			if(x > 758 && x < 792 && y > 209 && y < 233)
			{
				hero.availabeAttributePoint = !hero.availabeAttributePoint;
				hero.Speed += hero.Speed * 0.2; 
			}
			//HP
			if(x > 758 && x < 792 && y > 239 && y < 263)
			{
				hero.availabeAttributePoint = !hero.availabeAttributePoint;
				hero.MaxHP += hero.MaxHP * 0.2; 
			}
			//MP
			if(x > 758 && x < 792 && y > 265 && y < 289)
			{
				hero.availabeAttributePoint = !hero.availabeAttributePoint;
				hero.MaxMP += hero.MaxMP * 0.2; 
			}
			//AD
			if(x > 758 && x < 792 && y > 296 && y < 320)
			{
				hero.availabeAttributePoint = !hero.availabeAttributePoint;
				hero.damage ++; 
			}
		}
		if(hero.availabeSkillPoint)
		{
			//defensive tree
			//SM
			Skill* s;
			if(x > 590 && x < 660 && y > 375 && y < 435)
			{
				hero.availabeSkillPoint = !hero.availabeSkillPoint;
				s = new SlowMotionSkill();
				hero.Skills.push_back(s);
			}
			//H
			if(x > 590 && x < 660 && y > 445 && y < 505)
				if(hero.SearchForSkill("SM"))
				{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new HiddenSkill();
					hero.Skills.push_back(s);
				}
			//B
			if(x > 590 && x < 660 && y > 510 && y < 570)
				if(hero.SearchForSkill("H"))
				{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new BuffSkill();
					hero.Skills.push_back(s);
				}
			//V
			if(x > 590 && x < 660 && y > 575 && y < 635)
				if(hero.SearchForSkill("B"))
				{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new VampireAuraSkill();
					hero.Skills.push_back(s);
				}

			//offensive tree
			//SN
			if(x > 710 && x < 780 && y > 375 && y < 435)
			{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new SniperSkill();
					hero.Skills.push_back(s);
			}
			//L
			if(x > 710 && x < 780 && y > 445 && y < 505)
				if(hero.SearchForSkill("SN"))
				{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new LightningSkill();
					hero.Skills.push_back(s);
				}
			//U
			if(x > 710 && x < 780 && y > 510 && y < 570)
				if(hero.SearchForSkill("L"))
				{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new UpgradeSkill();
					hero.Skills.push_back(s);
				}
			//S
			if(x > 710 && x < 780 && y > 575 && y < 635)
				if(hero.SearchForSkill("U"))
				{
					hero.availabeSkillPoint = !hero.availabeSkillPoint;
					s = new StormSkill();
					hero.Skills.push_back(s);
				}
		}
	}
	void SetSkillsInfo(int x,int y)
	{
		int tex = -1;
		//SM
		if(x > 590 && x < 660 && y > 375 && y < 435)
			tex = skillMap["SMInfo"];
		//H
		if(x > 590 && x < 660 && y > 445 && y < 505)
			tex = skillMap["HInfo"];
		//B
		if(x > 590 && x < 660 && y > 510 && y < 570)
			tex = skillMap["BInfo"];
		//V
		if(x > 590 && x < 660 && y > 575 && y < 635)
			tex = skillMap["VInfo"];
		//offensive tree
		//SN
		if(x > 710 && x < 780 && y > 375 && y < 435)
			tex = skillMap["SNInfo"];
		//L
		if(x > 710 && x < 780 && y > 445 && y < 505)
			tex = skillMap["LInfo"];
		//U
		if(x > 710 && x < 780 && y > 510 && y < 570)
			tex = skillMap["UInfo"];
		//S
		if(x > 710 && x < 780 && y > 575 && y < 635)
			tex = skillMap["SInfo"];
		if(tex != -1)
		{
			glLoadIdentity();
			glBindTexture(GL_TEXTURE_2D,tex);
			glDisable(GL_LIGHTING);
			//glTranslatef(0.0,0.5,0);
			glBegin(GL_POLYGON);
			{
				glTexCoord2f(0,1);
				glVertex3f(-0.2,-0.20,0);
				glTexCoord2f(1,1);
				glVertex3f(.7,-0.20,0);
				glTexCoord2f(1,0);
				glVertex3f(.7,.20,0);		
				glTexCoord2f(0,0);
				glVertex3f(-0.2,.20,0);
			}
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}
	void DrawLevelUp(Hero &hero)
	{
		isStatesOpened = true;
		int size = hero.Skills.size();
		string skills[] = {"SN","SM","L","H","U","B"};
		string TexName = "";
		int currentTexture  = 0;
		if(size != 0)
		{
			for(int j = 0 ; j < 6; j++)
			{
				if(hero.SearchForSkill(skills[j]))
				{
					TexName += skills[j];
					continue;
				}
			}
		}
		else
			TexName = "LevelUp1";
		if(TexName == "LevelUp1")
			currentTexture = texture[26];
		if(TexName == "SM")
			currentTexture = texture[27];
		if(TexName == "SMH")
			currentTexture = texture[28];
		if(TexName == "SMHB")
			currentTexture = texture[29];
		if(TexName == "SN")
			currentTexture = texture[30];
		if(TexName == "SNL")
			currentTexture = texture[31];
		if(TexName == "SNLU")
			currentTexture = texture[32];
		if(TexName == "SNSM")
			currentTexture = texture[33];
		if(TexName == "SNSML")
			currentTexture = texture[34];
		if(TexName == "SNSMLH")
			currentTexture = texture[35];
		if(TexName == "SNSMLHU")
			currentTexture = texture[36];
		if(TexName == "SNSMLHUB")
			currentTexture = texture[37];
		if(TexName == "SNSMLU")
			currentTexture = texture[38];
		if(TexName == "SNSMH")
			currentTexture = texture[39];
		if(TexName == "SNSMHB")
			currentTexture = texture[40];
		glLoadIdentity();
		glBindTexture(GL_TEXTURE_2D,currentTexture);
		glDisable(GL_LIGHTING);
		glTranslatef(0,0.5,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(-0.2,-1.25,0);
			glTexCoord2f(1,1);
			glVertex3f(.2,-1.25,0);
			glTexCoord2f(1,0);
			glVertex3f(.2,.25,0);		
			glTexCoord2f(0,0);
			glVertex3f(-0.2,.25,0);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D,texture[12+hero.availabeSkillPoint]);
		glTranslatef(-0.005,0,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(-0.052,-1.22,0);
			glTexCoord2f(1,1);
			glVertex3f(-.02,-1.22,0);
			glTexCoord2f(1,0);
			glVertex3f(-.02,-1.174,0);		
			glTexCoord2f(0,0);
			glVertex3f(-0.052,-1.174,0);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D,texture[12+hero.availabeAttributePoint]);
		glTranslatef(0.2,0,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(-0.052,-1.22,0);
			glTexCoord2f(1,1);
			glVertex3f(-.02,-1.22,0);
			glTexCoord2f(1,0);
			glVertex3f(-.02,-1.174,0);		
			glTexCoord2f(0,0);
			glVertex3f(-0.052,-1.174,0);
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	void DrawQuestMenu(int lvl)
	{
		glLoadIdentity();
		if(lvl == 1)
			glBindTexture(GL_TEXTURE_2D,texture[15]);
		if(lvl == 2)
			glBindTexture(GL_TEXTURE_2D,texture[16]);
		glDisable(GL_LIGHTING);
		glTranslatef(0.5,0.5,0);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,1);
			glVertex3f(-0.2,-1.25,0);
			glTexCoord2f(1,1);
			glVertex3f(.2,-1.25,0);
			glTexCoord2f(1,0);
			glVertex3f(.2,.25,0);		
			glTexCoord2f(0,0);
			glVertex3f(-0.2,.25,0);
		}
		glEnd();
	}
	void DrawSniperView(ThirdPersonCamera &camera)
	{
		DisableAllLayout = true;
		Vector3 P = camera.P - camera.GetLookDirection()*12;
		glColor4f(1,1,1,1);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,texture[14]);
		glDepthMask(false);
		glTranslatef(P.x,P.y,P.z);
		glRotatef(camera.Rot.y,0,1,0);
		glRotatef(camera.Rot.x,1,0,0);
		glScalef(2,2,2);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(5,5,0);
			glTexCoord2f(0,1);
			glVertex3f(5,-5,0);
			glTexCoord2f(1,1);
			glVertex3f(-5,-5,0);
			glTexCoord2f(1,0);
			glVertex3f(-5,5,0);
		}
		glEnd();
		glDepthMask(true);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
};

