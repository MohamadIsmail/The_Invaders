enum FLAG{_drawQuest,_drawStatus,_isDoubleKey,_isMouseRightClick,_isChestOpen,_showDoorLocked,_showKeyFound,_OpenDoor1,_OpenDoor2,_Door1Opened,_Door2Opened,_Unprison,_free,_MissionComplete,_isMDone,_bossInc,_waveDone,_gameStarted};
class SaveAndLoad
{
public:
	bool flags[18];
	int lvl;
	NormalEnemy *e;
	Hero *hero;
	FinalBoss *fboss;
	Boss *boss;
	ThirdPersonCamera *camera;
	GLubyte *pixels;

	int Timer;
	int numberOfEnemyKilled;
	int monstersCounter;
	int Divider;
	int waveNumber;

	char *FileName;

	void SetAttributes(bool flags[18],int lvl,NormalEnemy e[],Hero &hero,FinalBoss fboss,Boss &boss,ThirdPersonCamera &camera,GLubyte *pixels,int Timer,int numberOfEnemyKilled,int monstersCounter,int Divider,int waveNumber)
	{
		for(int i = 0 ; i < 18 ; i++)
			this->flags[i] = flags[i];
		this->lvl = lvl;
		this->e = e;
		this->hero = &hero;
		this->fboss = &fboss;
		this->boss = &boss;
		this->camera = &camera;
		this->pixels = pixels;
		this->Timer = Timer;
		this->numberOfEnemyKilled = numberOfEnemyKilled;
		this->monstersCounter = monstersCounter;
		this->Divider = Divider;
		this->waveNumber = waveNumber;
	}
	void SaveGame()
	{
		char fileName[64];	
		SaveTGA(pixels);
		
		int i = 0;
		while(!(FileName[i] <= '9' && FileName[i] >= '1'))
		{
			fileName[i] = FileName[i];
			i++;
		}
		fileName[i++] = FileName[i];
		fileName[i++] = '.';
		fileName[i++] = 't';
		fileName[i++] = 'x';
		fileName[i++] = 't';
		fileName[i] = 0;
		FILE *saveFile;
		saveFile = fopen(fileName,"wb");
		ofstream o(saveFile);
		o << lvl << endl;
		for(int j = 0 ; j < 18 ;j++)
			o << flags[j] << endl;
		o << hero->Dead << endl;
		o << hero->HP << endl;
		o << hero->MP << endl;
		o << hero->Position.x << endl;
		o << hero->Position.y << endl;
		o << hero->Position.z << endl;
		o << hero->Rotation << endl;
		o << hero->weaponNumber << endl;
		o << hero->EXP << endl;
		o << hero->EXPincreased << endl;
		o << hero->HealthPointDecreased << endl;
		o << hero->ManaPointDecreased << endl;
		o << hero->CurrentLevel << endl;
		int size = hero->Skills.size();
		o << size << endl;
		string skills[] = {"SN","SM","L","H","U","B"};
		if(size != 0)
		{
			for(int j = 0 ; j < 6; j++)
			{
				if(hero->SearchForSkill(skills[j]))
				{
					o << skills[j] << endl;
				}
			}
		}
		o << hero->damage << endl;
		o << hero->Speed << endl;
		o << hero->MaxHP << endl;
		o << hero->MaxMP << endl;
		o << camera->N.x << endl;
		o << camera->N.y << endl;
		o << camera->N.z << endl;
		o << camera->R.x << endl;
		o << camera->R.y << endl;
		o << camera->R.z << endl;
		o << camera->U.x << endl;
		o << camera->U.y << endl;
		o << camera->U.z << endl;
		o << camera->P.x << endl;
		o << camera->P.y << endl;
		o << camera->P.z << endl;
		o << camera->T.x << endl;
		o << camera->T.y << endl;
		o << camera->T.z << endl;
		o << camera->Rot.x << endl;
		o << camera->Rot.y << endl;
		o << camera->Rot.z << endl;
		o << boss->Dead << endl;
		o << boss->EnemyDepth << endl;
		o << boss->EnemyRight << endl;
		o << boss->HP << endl;
		o << boss->Position.x << endl;
		o << boss->Position.y << endl;
		o << boss->Position.z << endl;
		o << fboss->Dead << endl;
		o << fboss->EnemyDepth << endl;
		o << fboss->EnemyRight << endl;
		o << fboss->HP << endl;
		o << fboss->Position.x << endl;
		o << fboss->Position.y << endl;
		o << fboss->Position.z << endl;
		o << Timer << endl;
		o << numberOfEnemyKilled << endl;
		o << monstersCounter << endl;
		o << Divider << endl;
		o << waveNumber << endl;
		int MobsNumber;
		if(lvl == 1)
			MobsNumber = 14;
		if(lvl == 2)
			MobsNumber = 20;
		for(int i = 0 ; i < MobsNumber ; i++)
		{
			o << e[i].Dead << endl;
			o << e[i].EnemyDepth << endl;
			o << e[i].EnemyRight << endl;
			o << e[i].HP << endl;
			o << e[i].Position.x << endl;
			o << e[i].Position.y << endl;
			o << e[i].Position.z << endl;
		}
		////remember to save the keys
	}
	char* SaveTGA(GLubyte *pixels)
	{

		char cFileName[64];
		FILE *fScreenshot;
		int nSize = 1024 * 1024 * 3;

		//GLubyte *pixels = new GLubyte [nSize];
		if (pixels == NULL) return "";    

		/*int nShot = 0;
		while (nShot < 64)
		{
			sprintf(cFileName,"Save_%d.tga",nShot);
			fScreenshot = fopen(cFileName,"rb");
			if (fScreenshot == NULL) break;
			else fclose(fScreenshot);

			++nShot;
		}   */
		sprintf(cFileName,"%s.tga",FileName);
		fScreenshot = fopen(cFileName,"wb");

		//glReadPixels(0, 0, 1024, 800, GL_RGB, 
		//	GL_UNSIGNED_BYTE, pixels);

		//convert to BGR format    
		unsigned char temp;
		int i = 0;
		while (i < nSize)
		{
			temp = pixels[i];       //grab blue
			pixels[i] = pixels[i+2];//assign red to blue
			pixels[i+2] = temp;     //assign blue to red

			i += 3;     //skip to next blue byte
		}

		unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
		unsigned char header[6] = {1024%256,1024/256,
			800%256,800/256,24,0};

		fwrite(TGAheader, sizeof(unsigned char), 12, fScreenshot);
		fwrite(header, sizeof(unsigned char), 6, fScreenshot);
		fwrite(pixels, sizeof(GLubyte), nSize, fScreenshot);
		fclose(fScreenshot);

		delete [] pixels;   

		return cFileName;
	}
	NormalEnemy *re;
	Hero rhero;
	Boss rboss;
	FinalBoss rfboss;
	ThirdPersonCamera rcamera;
	
	void LoadGame(char *FileName)
	{
		FILE *loadFile;
		loadFile = fopen(FileName,"rb");
		ifstream i(loadFile);
		char x[1000];
		//char z[1000];
		//char c[1000];
		i >> x;
		lvl = atoi(x);
		/*i >> x;
		int q = 0;
		while((z[q]=x[q++]) != 0);
		world = z;
		i >> x;
		q = 0;
		while((c[q]=x[q++]) != 0);
		worldTexture = c;
		*/
		for(int j = 0 ; j < 18;j++)
		{
			i >> x;
			flags[j] = atoi(x);
		}
		i >> x;
		rhero.Dead = atoi(x);
		i >> x;
		rhero.HP = atoi(x);
		i >> x;
		rhero.MP = atoi(x);
		i >> x;
		rhero.Position.x = atof(x);
		i >> x;
		rhero.Position.y = atof(x);
		i >> x;
		rhero.Position.z = atof(x);
		i >> x;
		rhero.Rotation = atof(x);
		i >> x;
		rhero.weaponNumber = atof(x);
		i >> x;
		rhero.EXP = atof(x);
		i >> x;
		rhero.EXPincreased = atof(x);
		i >> x;
		rhero.HealthPointDecreased = atof(x);
		i >> x;
		rhero.ManaPointDecreased = atof(x);
		i >> x;
		rhero.CurrentLevel = atof(x);
		i >> x;
		int size = atof(x);
		i >> x;
		Skill *s;
		if(size != 0 )
		{
			for(int j = 0 ; j < size ; j++)
			{
				if(x == "SN")
				{
					s = new SniperSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "SM")
				{
					s = new SlowMotionSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "L")
				{
					s = new LightningSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "H")
				{
					s = new HiddenSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "U")
				{
					s = new UpgradeSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "B")
				{
					s = new BuffSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "V")
				{
					s = new VampireAuraSkill();
					rhero.Skills.push_back(s);
				}
				if(x == "S")
				{
					s = new StormSkill();
					rhero.Skills.push_back(s);
				}
				i >> x;
			}
		}
		rhero.damage = atof(x);
		i >> x;
		rhero.Speed = atof(x);
		i >> x;
		rhero.MaxHP = atof(x);
		i >> x;
		rhero.MaxMP = atof(x);
		i >> x;
		rcamera.N.x = atof(x);
		i >> x;
		rcamera.N.y = atof(x);
		i >> x;
		rcamera.N.z = atof(x);
		i >> x;
		rcamera.R.x = atof(x);
		i >> x;
		rcamera.R.y = atof(x);
		i >> x;
		rcamera.R.z = atof(x);
		i >> x;
		rcamera.U.x = atof(x);
		i >> x;
		rcamera.U.y = atof(x);
		i >> x;
		rcamera.U.z = atof(x);
		i >> x;
		rcamera.P.x = atof(x);
		i >> x;
		rcamera.P.y = atof(x);
		i >> x;
		rcamera.P.z = atof(x);
		i >> x;
		rcamera.T.x = atof(x);
		i >> x;
		rcamera.T.y = atof(x);
		i >> x;
		rcamera.T.z = atof(x);
		i >> x;
		rcamera.Rot.x = atof(x);
		i >> x;
		rcamera.Rot.y = atof(x);
		i >> x;
		rcamera.Rot.z = atof(x);
		i >> x;
		rboss.Dead = atoi(x);
		i >> x;
		rboss.EnemyDepth = atoi(x);
		i >> x;
		rboss.EnemyRight = atoi(x);
		i >> x;
		rboss.HP = atoi(x);
		i >> x;
		rboss.Position.x = atof(x);
		i >> x;
		rboss.Position.y = atof(x);
		i >> x;
		rboss.Position.z = atof(x);
		i >> x;
		rfboss.Dead = atoi(x);
		i >> x;
		rfboss.EnemyDepth = atoi(x);
		i >> x;
		rfboss.EnemyRight = atoi(x);
		i >> x;
		rfboss.HP = atoi(x);
		i >> x;
		rfboss.Position.x = atof(x);
		i >> x;
		rfboss.Position.y = atof(x);
		i >> x;
		rfboss.Position.z = atof(x);
		i >> x;
		Timer = atoi(x);
		i >> x;
		numberOfEnemyKilled = atof(x);
		i >> x;
		monstersCounter = atof(x);
		i >> x;
		Divider = atof(x);
		i >> x;
		waveNumber = atof(x);
		int MobsNumber;
		if(lvl == 1)
		{
			re = new NormalEnemy[14];
			MobsNumber = 14;
		}
		if(lvl == 2)
		{
			re = new NormalEnemy[20];
			MobsNumber = 20;
		}
		for(int a = 0 ; a < MobsNumber ; a++)
		{
			i >> x;
			re[a].Dead = atoi(x);
			i >> x;
			re[a].EnemyDepth = atoi(x);
			i >> x;
			re[a].EnemyRight = atoi(x);
			i >> x;
			re[a].HP = atoi(x);
			i >> x;
			re[a].Position.x = atof(x);
			i >> x;
			re[a].Position.y = atof(x);
			i >> x;
			re[a].Position.z = atof(x);
		}
	}
};

//make a copy constructor for hero and enemy and boss and fboss 