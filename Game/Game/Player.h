#pragma once
#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.H>
#include<gl\glut.h>
#include"Bullet.h"
#include "Md3.h"

///////////////////////////////////////////////////////////////////Player////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Player
{
public:
	Vector3 Position;
	CModelMD3 model;
	int HP;
	int MaxHP;
	bool Dead;
	float Speed;
	Vector3 InitialLookDirection;
	float Rotation;
	int targetIndex;
	Vector3 Target;
	vector<Bullet> Bullets;
	int damage;
	int texture[5];
	bool Visible;
	bool Upgraded;
	int MapLevel;
public:
	Player()
	{MapLevel = 1;Upgraded = false;Dead = false;}
	void SetRotation(float Angle)
	{
		Rotation = Angle;
	}
	void PlayerGotHit()
	{
		model.SetTorsoAnimation(TORSO_DROP);
		model.SetLegsAnimation("LEGS_IDLE");
	}
	void SetPlayerPosition(Vector3 Pos)
	{
		Position  = Pos;
	}
	virtual void SetPlayerPosition(int x,int z){};
	void CheckIfDead()
	{
		if(HP <= 0 && !Dead)
		{
			Die();
			Dead = true;
		}
	}
	bool IsDead()
	{
		return  Dead;
	}
	void Die()
	{
		model.SetTorsoAnimation(BOTH_DEATH1);
		model.SetLegsAnimation(BOTH_DEATH1);
	}
	void SetTarget(const Vector3 &Target,int Index)
	{
		this->Target = Vector3(Target);
		targetIndex = Index;
	}
	virtual bool Update() = 0;
	virtual void Attack() = 0;
	void LoadPlayer()
	{
		model.LoadWeapon("models","railgun\\railgun");
		model.SetTorsoAnimation("TORSO_STAND");
		model.SetLegsAnimation("LEGS_WALK");
	}
	void LoadTexture()
	{
		texture[0] = LoadGLTexture("images\\bullets\\B4.bmp");
		texture[1] = LoadGLTexture("images\\bullets\\B6.bmp");
	}
	virtual Vector3 GetPosition() =0;
	virtual AABoundingBox GetAABB() const =0;
	virtual void ShootAt() =0;
	void UpdateBullets()
	{
		size_t nb = Bullets.size();
		for(int b=nb-1; b>=0; b--) {
			Bullets[b].Update();
			if(Bullets[b].HasExpired())
			{
				if(b < 0 || b >= Bullets.size())
					return;
				Bullets.erase(Bullets.begin() + b);
			}
		}
		DrawBullets();
	}
	void DrawBullets()
	{
		size_t nb = Bullets.size();
		if(Upgraded)
			glBindTexture(GL_TEXTURE_2D,texture[1]);
		else
			glBindTexture(GL_TEXTURE_2D,texture[0]);
		for(int b=0; b<nb; b++)
			Bullets[b].Render(Rotation);
	}
	virtual void Draw()=0;
};

///////////////////////////////////////////////////////////////////ENEMY////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum EnemyState{IDLE,CHASING};
enum EnemyDirection{LEFT,RIGHT,FORWARD,BACKWARD};
class Enemy : public Player
{
public:
	int State;
	bool ReadyTofire;
	Vector3 InitialPosition;
	int AttackRange;
	int SightRange;
	int MoveRange;
	float MoveValue;
	bool reachedMaxRange;
	bool MovementDone;
	int moveDirection;
	Vector3 Normal;
	Vector3 Right;
	Vector3 Up;
	int EnemyRight;
	int EnemyDepth;
	int Time;
	bool NotInHisPlace;
	bool isDone;
	bool firstDeath;
	int bulletSpeed;
	int timeAfterDeath;
	vector<Vector3> path;
	Graph *g;
	int PathCounter;
	Vector3 P;
	Vector3 EntrancePos;
	bool isFirst;
	bool RealChasing;
	Enemy():Player()
	{
		RealChasing = false;
		isFirst = true;
		PathCounter = 0;
		State = EnemyState::IDLE;
		firstDeath = false;
		isDone = false;
		Dead = false;
		reachedMaxRange = false;
		MovementDone = true;
		Speed = 20;
		bulletSpeed = 40;
		moveDirection = 1;
		Position.x = 0;
		Position.z = 0;
		Position.y = 0;
		InitialPosition.x = 0;
		InitialPosition.y = 0;
		InitialPosition.z = 0;
		Rotation = 0 ;
		InitialLookDirection.x = 1;
		InitialLookDirection.y = 0;
		InitialLookDirection.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
		timeAfterDeath = 0;
		NotInHisPlace = false;
		Visible = true;
	}
	void setGraph(Graph *graph)
	{
		g = graph;
	}
	bool IsPlayerInSightRange(int x,int z)
	{
		if(!Visible)
			return false;
		if(x > (Position.x + EnemyRight - SightRange) && x < (Position.x + EnemyRight + SightRange) && z > (Position.z + EnemyDepth - SightRange) && z < (Position.z + EnemyDepth + SightRange))
			return true;
		else
			return false;
	}
	void CheckIfPlayerInRange(int x,int z)
	{
		if(MapLevel == 2)
			SightRange = 3000;
		else
			SightRange = 160;
		if(IsPlayerInSightRange(x,z))
		{
			State = EnemyState::CHASING;
			CalculateFaceAngle(x,z);
		}
		else
		{
			State = EnemyState::IDLE;
		}
	}
	int temp;
	void SetPlayerPosition(int x,int z)
	{
		EnemyRight = x;
		EnemyDepth = z;
	}
	// cos(ceta) = A.B/|A|*|B|
	void CalculateFaceAngle(int x, int z)
	{
		Vector3 PlayerPos(x-EnemyRight,0,z-EnemyDepth);
		Vector3 N = PlayerPos-Position;
		N.Normalize();
		float NMagnitude = N.Magnitude();
		float EMagnitude = InitialLookDirection.Magnitude();
		float Res = N.x*InitialLookDirection.x+N.y*InitialLookDirection.y+N.z*InitialLookDirection.z;
		float Ceta = Res/(NMagnitude*EMagnitude);
		if(z > Position.z+EnemyDepth)
			SetRotation(-(180/3.14157)*acos(Ceta));
		else
			SetRotation((180/3.14157)*acos(Ceta));
	}
	void SetEntrancePosition(int x,int z)
	{
		EntrancePos = Vector3(x,0,z);
	}
	bool Update()
	{
		if(HP <= 0 && !Dead)
		{
			Die();
			Dead = true;
			isDone = true;
		}
		if(Dead && !isDone)
		{
			Die();
			isDone = true;
		}
		if(!Dead)
		{
			UpdateBullets();
			CheckIfPlayerInRange(Target.x,Target.z);
			if(State == EnemyState::IDLE)
			{
				if(NotInHisPlace)
					returnToInitialPosition();
				else
					MoveFreely();
				PathCounter = 0;
			}
			else
			{
				NotInHisPlace = true;
				if(MapLevel == 1)
					Chase(Target.x,Target.z);
				else if(MapLevel == 2)
					Chase(EntrancePos.x,EntrancePos.z);
			}
		}
		else
			timeAfterDeath++;
		Draw();
		model.UpdateLowerModel();
		model.UpdateUpperModel();
		return isDone;
	}
	void Reset()
	{
		Position = Vector3(0,0,0);
	}
	void Chase(int x,int z)
	{
		////path = g->A_star(g->GetNearestNode(GetPosition().x,GetPosition().z),g->GetNearestNode(x,z));
		//if(isFirst)
		//{
		//	P = g->GetNextNode(g->GetNearestNode(GetPosition().x,GetPosition().z),g->GetNearestNode(x,z));
		//	isFirst = false;
		//}
		//if(P.x == 0 && P.z == 0)
		//{
		//	isFirst  = true;
		//	ReadyTofire = false;
		//	Time++;
		//	if(!(Time%100))
		//	{
		//		Attack();
		//		ShootAt();
		//		Time = 0;
		//	}
		//	//cout << "N";
		//	return;
		//}
		//Vector3 PlayerPos(P.x -EnemyRight,0,P.z-EnemyDepth);
		//Vector3 N = PlayerPos-Position; 
		//float Distance = N.Magnitude();
		//N.Normalize();
		//if(Distance > 10)
		//{
		//	if(model.GetTorsoCurrentAnimation() != TORSO_STAND)
		//	{
		//		model.SetTorsoAnimation(TORSO_STAND);
		//	}
		//	if(model.GetLegsCurrentAnimation() != LEGS_WALK-7)
		//	{
		//		model.SetLegsAnimation("LEGS_WALK");
		//	}
		//	Position += N*Speed;
		//	//cout << "H";
		//}
		//else
		//{
		//	//cout << "C";
		//	isFirst = true;
		//	//if(PathCounter < path.size()-1)
		//	//{
		//	//	  PathCounter++;
		//	//}
		//}
		Vector3 PlayerPos(x-EnemyRight,0,z-EnemyDepth);
		Vector3 N = PlayerPos-Position; 
		float Distance = N.Magnitude();
		N.Normalize();
		if(Distance > AttackRange && !RealChasing)
		{
			if(model.GetTorsoCurrentAnimation() != TORSO_STAND)
			{
				model.SetTorsoAnimation(TORSO_STAND);
			}
			if(model.GetLegsCurrentAnimation() != LEGS_WALK-7)
			{
				model.SetLegsAnimation("LEGS_WALK");
			}
			Position += N*Speed;
		}
		else
		{
			if(MapLevel == 2)
			{
				RealChasing = true;
				ChaseRealTarget(Target.x,Target.z);
			}
			if(MapLevel == 1)
			{
				ReadyTofire = false;
				Time++;
				if(!(Time%100))
				{
					Attack();
					ShootAt();
					Time = 0;
				}
			}
		}
	}
	void ChaseRealTarget(int x,int z)
	{
		Vector3 PlayerPos(x-EnemyRight,0,z-EnemyDepth);
		Vector3 N = PlayerPos-Position; 
		float Distance = N.Magnitude();
		N.Normalize();
		if(Distance > AttackRange)
		{
			if(model.GetTorsoCurrentAnimation() != TORSO_STAND)
			{
				model.SetTorsoAnimation(TORSO_STAND);
			}
			if(model.GetLegsCurrentAnimation() != LEGS_WALK-7)
			{
				model.SetLegsAnimation("LEGS_WALK");
			}
			Position += N*Speed;
		}
		else
		{
			ReadyTofire = false;
			Time++;
			if(!(Time%100))
			{
				Attack();
				ShootAt();
				Time = 0;
			}
		}
	}
	void returnToInitialPosition()
	{
		Vector3 N = InitialPosition-Position; 
		CalculateFaceAngle(InitialPosition.x+EnemyRight,InitialPosition.z+EnemyDepth);
		float Distance = N.Magnitude();
		N.Normalize();
		if(Distance > 1)
		{
			if(model.GetTorsoCurrentAnimation() != TORSO_STAND)
			{
				model.SetTorsoAnimation(TORSO_STAND);
			}
			if(model.GetLegsCurrentAnimation() != LEGS_WALK-7)
			{
				model.SetLegsAnimation("LEGS_WALK");
			}
			Position += N*Speed;
		}
		else
		{
			NotInHisPlace = false;
		}
	}
	void Attack()
	{
		model.SetTorsoAnimation(TORSO_ATTACK);
		model.SetLegsAnimation("LEGS_IDLE");
	}
	void MoveForward()
	{
		if(!MovementDone)
		{
			if(MoveValue > MoveRange)
				reachedMaxRange = true;
			if(MoveValue < 0)
			{
				reachedMaxRange = false;
				MovementDone = true;
			}
			if(!reachedMaxRange)
			{
				Rotation = 90;
				MoveValue+= Speed;
				Position.z -= Speed;
			}
			else
			{
				Rotation = -90;
				MoveValue-= Speed;
				Position.z += Speed;
			}
		}
	}
	void MoveBackward()
	{
		if(!MovementDone)
		{
			if(MoveValue > MoveRange)
				reachedMaxRange = true;
			if(MoveValue < 0)
			{
				reachedMaxRange = false;
				MovementDone = true;
			}
			if(!reachedMaxRange)
			{
				Rotation = -90;
				MoveValue+= Speed;
				Position.z += Speed;
			}
			else
			{
				Rotation = 90;
				MoveValue-= Speed;
				Position.z -= Speed;
			}
		}
	}
	void MoveLeft()
	{
		if(!MovementDone)
		{
			if(MoveValue > MoveRange)
				reachedMaxRange = true;
			if(MoveValue < 0)
			{
				reachedMaxRange = false;
				MovementDone = true;
			}
			if(!reachedMaxRange)
			{
				Rotation = 180;
				MoveValue+= Speed;
				Position.x -= Speed;
			}
			else
			{
				Rotation = 0;
				MoveValue-= Speed;
				Position.x += Speed;
			}
		}
	}
	void MoveRight()
	{
		if(!MovementDone)
		{
			if(MoveValue > MoveRange)
				reachedMaxRange = true;
			if(MoveValue < 0)
			{
				reachedMaxRange = false;
				MovementDone = true;
			}
			if(!reachedMaxRange)
			{
				Rotation = 0;
				MoveValue+= Speed;
				Position.x += Speed;
			}
			else
			{
				Rotation = 180;
				MoveValue-= Speed;
				Position.x -= Speed;
			}
		}
	}
	void MoveFreely()
	{		
		if(MovementDone)
		{
			moveDirection = rand()%4;
			MovementDone = false;
		}
		switch(moveDirection)
		{
		case EnemyDirection::FORWARD:
			MoveForward();
			break;
		case EnemyDirection::BACKWARD:
			MoveBackward();
			break;
		case EnemyDirection::LEFT:
			MoveLeft();
			break;
		case EnemyDirection::RIGHT:
			MoveRight();
			break;
		}
	}
	Vector3 GetPosition()
	{
		return Vector3(Position.x+EnemyRight,0,Position.z+EnemyDepth); 
	}
	AABoundingBox GetAABB() const {
		Vector3 dims(5, 5, 5);
		Vector3 P(Position.x+EnemyRight,-18,Position.z+EnemyDepth);
		return AABoundingBox(P, 2*dims);
	}
	void ShootAt() {
		Target.y = 0;
		Vector3 bulDir = (Target - GetPosition());
		bulDir.Normalize();
		Bullet bul(Vector3(GetPosition().x,-18,GetPosition().z), bulletSpeed * bulDir);
		Bullets.push_back(bul);
	}
	void Draw()
	{
		glLoadIdentity();
		glTranslatef(EnemyRight+Position.x,-18,EnemyDepth+Position.z);
		glRotatef(Rotation,0,1,0);
	}
};

///////////////////////////////////////////////////////////////Normal Enemy//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class NormalEnemy : public Enemy
{
public:
	NormalEnemy():Enemy()
	{
		damage = 2;
		HP = 10;
		MaxHP = 10;
		AttackRange = 70;
		SightRange = 140;
		MoveRange = 50;
		MoveValue = 0;
		Speed = 0.4;
	}
	void LoadPlayer()
	{
		model.LoadModel("models\\r7");
		Enemy::LoadPlayer();
	}
	void Draw()
	{
		Enemy::Draw();
		glScalef(0.25,0.25,0.25);
		model.DrawModel();
	}
};


///////////////////////////////////////////////////////////////////////Boss//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Boss :public Enemy
{
public:
	Boss():Enemy()
	{
		damage = 10;
		HP = 50;
		MaxHP = 50;
		AttackRange = 70;
		SightRange = 280;
		MoveRange = 50;
		MoveValue = 0;
		Speed = 1;
	}
	void LoadPlayer()
	{
		model.LoadModel("models\\Onilink");
		Enemy::LoadPlayer();
	}
	void Draw()
	{
		Enemy::Draw();
		glTranslatef(0,8,0);
		glScalef(0.5,0.5,0.5);
		model.DrawModel();
	}
};


///////////////////////////////////////////////////////////////////////Final Boss////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FinalBoss :public Enemy
{
public:
	FinalBoss():Enemy()
	{
		damage = 15;
		HP = 100;
		MaxHP = 100;
		AttackRange = 100;
		SightRange = 100;
		MoveRange = 50;
		MoveValue = 0;
		Speed = 1;
	}
	void LoadPlayer()
	{
		model.LoadModel("models\\Zero");
		Enemy::LoadPlayer();
	}
	AABoundingBox GetAABB() const {
		Vector3 dims(10, 10, 10);
		Vector3 P(Position.x+EnemyRight,-18,Position.z+EnemyDepth);
		return AABoundingBox(P, 2*dims);
	}
	void Draw()
	{
		Enemy::Draw();
		glTranslatef(0,8,0);
		glScalef(0.8,0.8,0.8);
		model.DrawModel();
	}
};
////////////////////////////////////////////////////////////////////Hero////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class Hero : public Player
{
public:
	float EXPincreased;
	float HealthPointDecreased;
	float ManaPointDecreased;
	int EXP;
	int CurrentLevel;
	int MP;
	int MaxMP;
	float y;
	bool Visible;
	bool isAutoLook;
	bool shootLaser;
	int counting;
	bool laser;
	bool NoTarget;
	bool run;
	bool isUp;
	bool JumpEnded;
	Vector3 LookDirection;
	int weaponNumber;
	int targetIndex;
	int EnemiesCounter;
	int EnemyIndex;
	int TargetIndices[14];
	int levels[6];
	vector<Skill*> Skills;
	int bulletSpeed;
	float bulletLifeTime;
	static const int MAXLEVEL = 5;
	bool LevelUp;
	int availabeSkillPoint;
	int availabeAttributePoint;
	bool sniper;
	float breathValue;
	bool Buffed;
	bool storm;
	bool Vam;
	Vector3 CamPos;
	Vector3 R;
	Particle PE;
	Hero():Player()
	{
		storm = false;
		Buffed = false;
		sniper = false;
		Visible = true;
		Vam = false;
		skillAttackSpeed = 0;
		bulletSpeed = 40;
		bulletLifeTime = 100;
		damage = 1;
		LevelUp = false;
		levels[0] = 0;
		levels[1] = 16;//75
		levels[2] = 32;//210
		levels[3] = 70;
		levels[4] = 130;
		levels[5] = 230;
		availabeSkillPoint = 0;
		availabeAttributePoint = 0;
		HP = 100;
		MP = 100;
		EXP = 0;
		MaxHP = 100;
		MaxMP = 100;
		CurrentLevel = 1;
		EXPincreased = 0;
		ManaPointDecreased = 0;
		HealthPointDecreased = 0;
		y= 0;
		Speed = 20;
		isAutoLook = false;
		shootLaser = false;
		counting = 0;
		weaponNumber = 1;
		laser = false;
		NoTarget = true;
		run = false;
		isUp = true;
		JumpEnded = true;
		InitialLookDirection = Vector3(0,0,-1);
		Target = Vector3(0,0,0);
		LookDirection = Vector3(0,0,-1);
		EnemiesCounter = 0;
		EnemyIndex = 0;
	}
	void setHeroDirection(Vector3 Dir)
	{
		LookDirection = Dir;
	}
	void CheckIfDead()
	{
		if(HP <= 0 && !Dead)
		{
			Die();
			Dead = true;
		}
	}
	void StateUpdated()
	{
		if(!availabeAttributePoint && !availabeSkillPoint)
			LevelUp = false;
	}
	void UpdateJump()
	{
		if(isUp)
			y+=2;
		else
			y-=2;
		if( y < 0)
		{
			JumpEnded = true;
			isUp = true;
			y = 0;
		}	
		if(y > 30)
		{
			isUp = false;
		}
	}
	bool SearchForSkill(string SkillName)
	{
		int numSkills = Skills.size();
		for(int i = 0 ; i < numSkills;i++)
			if(Skills[i]->SkillName == SkillName)
				return true;
		return false;
	}
	void LevelUP()
	{
		CurrentLevel++;
		EXP = 0;
		EXPincreased = 0;
		LevelUp = true;
		availabeSkillPoint = 1;
		availabeAttributePoint = 1;
	}
	void CheckIfLevelUp()
	{
		if(EXP + levels[CurrentLevel-1] >= levels[CurrentLevel])
			LevelUP();
	}
	void IncreaseExpBy(int value)
	{
		EXP += value;
		if(EXP > levels[MAXLEVEL])
			EXP = levels[MAXLEVEL];
	}
	void Buff()
	{
		damage = 2;
		MaxHP = 150;
		MaxMP = 150;
		Speed = 30;
	}
	void Upgrade()
	{
		damage = 3;
		bulletLifeTime = 150;
		bulletSpeed = 60;
	}
	bool Update()
	{
		if(SearchForSkill("U"))
		{
			Upgraded = true;
			Upgrade();
		}
		if(Buffed)
			Buff();
		UpdateSkillCoolDown();
		CheckIfLevelUp();
		StateUpdated();
		CheckIfDead();
		UpdateBullets();
		if(shootLaser)
			HeroShootLaser();
		if(!JumpEnded)
			UpdateJump();
		Draw();
		model.UpdateLowerModel();
		model.UpdateUpperModel();
		if(Dead)
			return true;
		else
			return false;
	}
	void SetAutoLook()
	{
		isAutoLook = !isAutoLook;
	}
	void Idle()
	{
		model.SetLegsAnimation(LEGS_IDLE);
	}
	void Walk()
	{
		if(model.GetLegsCurrentAnimation() != LEGS_WALK-7  && model.GetLegsCurrentAnimation() != LEGS_RUN-7 && JumpEnded)
		{
			if(run)
				model.SetLegsAnimation(LEGS_RUN);
			else
				model.SetLegsAnimation(LEGS_WALK);
		}
	}
	void Turn()
	{
		if(model.GetLegsCurrentAnimation() != LEGS_TURN-7 && JumpEnded)
			model.SetLegsAnimation(LEGS_TURN);
	}
	void Jump()
	{
		model.SetLegsAnimation(LEGS_JUMPB);
		JumpEnded = false;
	}
	void Attack()
	{
		if(weaponNumber == 2)
			shootLaser = true;
		else
			shootLaser = false;
		if(weaponNumber == 1)
			ShootAt();
		if(weaponNumber == 1 || weaponNumber == 2 && model.GetTorsoCurrentAnimation() == TORSO_STAND)
			model.SetTorsoAnimation(TORSO_ATTACK);
		else if(weaponNumber == 0 && model.GetTorsoCurrentAnimation() == TORSO_STAND2)
			model.SetTorsoAnimation(TORSO_ATTACK2);
	}
	void LoadPlayer()
	{
		model.LoadModel("models\\sarge");
		Player::LoadPlayer();
		model.SetLegsAnimation("LEGS_IDLE");
	}
	AABoundingBox GetAABB() const {
		Vector3 dims(5, 5, 5);
		Vector3 P(Position.x,-18,Position.z);
		return AABoundingBox(P, 2*dims);
	}
	void ShootAt() {
		Vector3 bulDir;
		Vector3 Pos;
		Pos.x = Position.x;
		Pos.y = 0+breathValue;
		Pos.z = Position.z;
		if(isAutoLook)
		{
			bulDir = (Target - Pos);
			bulDir.Normalize();
		}
		else
			bulDir = Vector3(-LookDirection.x,-LookDirection.y+0.3,-LookDirection.z);
		if(sniper)
		{
			if(LookDirection.z >= 0)
				bulDir = Vector3(-LookDirection.x+0.04,-LookDirection.y,-LookDirection.z);
			else
				bulDir = Vector3(-LookDirection.x-0.04,-LookDirection.y,-LookDirection.z);
			Bullet bul(CamPos, bulletSpeed * bulDir,bulletLifeTime);
			bul.isSniper = true;
			Bullets.push_back(bul);
		}
		else
		{
			Pos = Position + R*2;
			Bullet bul(Pos, bulletSpeed * bulDir,bulletLifeTime);
			Bullets.push_back(bul);
		}
	}
	void ValidateHP()
	{
		if(HP < 0)
			HP = 0;
		if(HP > MaxHP)
			HP = MaxHP;
	}
	void ValidateMP()
	{
		if(MP < 0)
			MP = 0;
		if(MP > MaxMP)
			MP = MaxMP;
	}
	void UseSkill(int skillNumber,ThirdPersonCamera &camera,NormalEnemy e[],Boss &boss,FinalBoss &fboss)
	{
		if(skillNumber <= Skills.size())
		{
			if(Skills[skillNumber-1]->Mana > MP)
				return;
			Skills[skillNumber-1]->UseSkill(camera);
			if(Skills[skillNumber-1]->SkillName == "L")
			{
				shootLaser = true;
				HeroShootLaser();
				for(int i = 0 ; i < 14 ; i++)
					if(TargetIndices[EnemyIndex] == 11)
						boss.HP -= 10;
					else
						e[TargetIndices[EnemyIndex]].HP -= 10;
			}
			ManaPointDecreased = ((0.48-0.02)/MaxMP)*(MaxMP-MP);
			damage = Skills[skillNumber-1]->damage;
			bulletSpeed = Skills[skillNumber-1]->bulletSpeed;
			MP -= Skills[skillNumber-1]->Mana;
			Visible = Skills[skillNumber-1]->Visible;
			sniper = Skills[skillNumber-1]->sniper;
			Buffed = Skills[skillNumber-1]->Buff;
			storm = Skills[skillNumber-1]->Storm;
			Vam = Skills[skillNumber-1]->Vam;
			if(Vam)
			{
				isFirstShoot = true;
				Vampire(e,boss,fboss);
			}
			if(storm)
				Storm(e,boss,fboss);
			bulletLifeTime = Skills[skillNumber-1]->bulletLifeTime;
			for(int i = 0 ; i < 14 ; i++)
			{
				e[i].Speed = Skills[skillNumber-1]->speedReduction;
				e[i].bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
				e[i].Visible = Visible;
			}
			boss.Speed = Skills[skillNumber-1]->speedReduction;
			boss.bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
			fboss.Speed = Skills[skillNumber-1]->speedReduction;
			fboss.bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
		}
	}
	void UseSkillsWithDuration(int skillNumber,ThirdPersonCamera &camera,NormalEnemy e[],Boss &boss,FinalBoss &fboss,Material &mat)
	{
		if(skillNumber <= Skills.size())
		{
			Skills[skillNumber-1]->UseSkill(camera);
			mat.mat_emission[0] = Skills[skillNumber-1]->Emission.x;
			mat.mat_emission[1] = Skills[skillNumber-1]->Emission.y;
			mat.mat_emission[2] = Skills[skillNumber-1]->Emission.z;
			mat.mat_ambient[0] = Skills[skillNumber-1]->Ambient.x;
			mat.mat_ambient[1] = Skills[skillNumber-1]->Ambient.y;
			mat.mat_ambient[2] = Skills[skillNumber-1]->Ambient.z;
			ManaPointDecreased = ((0.48-0.02)/MaxMP)*(MaxMP-MP);
			damage = Skills[skillNumber-1]->damage;
			bulletSpeed = Skills[skillNumber-1]->bulletSpeed;
			Visible = Skills[skillNumber-1]->Visible;
			sniper = Skills[skillNumber-1]->sniper;
			Buffed = Skills[skillNumber-1]->Buff;
			storm = Skills[skillNumber-1]->Storm;
			Vam = Skills[skillNumber-1]->Vam;
			if(Vam)
			{
				Vampire(e,boss,fboss);
			}
			if(storm)
				Storm(e,boss,fboss);
			bulletLifeTime = Skills[skillNumber-1]->bulletLifeTime;
			for(int i = 0 ; i < 14 ; i++)
			{
				e[i].Speed = Skills[skillNumber-1]->speedReduction;
				e[i].bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
				e[i].Visible = Visible;
			}
			boss.Speed = Skills[skillNumber-1]->speedReduction;
			boss.bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
			boss.Visible = Visible;
			fboss.Speed = Skills[skillNumber-1]->speedReduction;
			fboss.bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
			fboss.Visible = Visible;
		}
	}
	void UpdateSkillCoolDown()
	{
		int s = Skills.size();
		for(int i = 0 ; i < s ; i++)
			Skills[i]->SkillOnCoolDown();
	}
	bool isSkillUsed(int skillNumber)
	{
		if(skillNumber <= Skills.size())
			return Skills[skillNumber-1]->isSkillUsed;
		else return false;
	}
	void EndSkill(int skillNumber,ThirdPersonCamera &camera,NormalEnemy e[],Boss &boss,FinalBoss &fboss,Material &mat)
	{
		if(skillNumber <= Skills.size())
		{
			Skills[skillNumber-1]->SkillDone(camera);
			mat.mat_emission[0] = Skills[skillNumber-1]->Emission.x;
			mat.mat_emission[1] = Skills[skillNumber-1]->Emission.y;
			mat.mat_emission[2] = Skills[skillNumber-1]->Emission.z;
			mat.mat_ambient[0] = Skills[skillNumber-1]->Ambient.x;
			mat.mat_ambient[1] = Skills[skillNumber-1]->Ambient.y;
			mat.mat_ambient[2] = Skills[skillNumber-1]->Ambient.z;
			damage = Skills[skillNumber-1]->damage;
			bulletSpeed = Skills[skillNumber-1]->bulletSpeed;
			Visible = Skills[skillNumber-1]->Visible;
			sniper = Skills[skillNumber-1]->sniper;
			Buffed = Skills[skillNumber-1]->Buff;
			storm = Skills[skillNumber-1]->Storm;
			Vam = Skills[skillNumber-1]->Vam;
			bulletLifeTime = Skills[skillNumber-1]->bulletLifeTime;
			for(int i = 0 ; i < 14 ; i++)
			{
				e[i].Speed = Skills[skillNumber-1]->speedReduction;
				e[i].bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
				e[i].Visible = Visible;
			}
			boss.Speed = Skills[skillNumber-1]->speedReduction;
			boss.bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
			boss.Visible = Visible;
			fboss.Speed = Skills[skillNumber-1]->speedReduction;
			fboss.bulletSpeed = Skills[skillNumber-1]->ebulletSpeed;
			fboss.Visible = Visible;
		}	
	}
	void Vampire(NormalEnemy e[],Boss &b,FinalBoss &fb)
	{
		PE.StartAgain('r');
		Vector3 P = Position;
		P.x = Position.x + 50;
		PE.Draw(P,Rotation);
		P.x = Position.x - 50;
		PE.Draw(P,Rotation);
		P.z = Position.z - 50;
		PE.Draw(P,Rotation);
		P.z = Position.z + 50;
		PE.Draw(P,Rotation);
		P.z = Position.z + 50;
		P.x = Position.x + 50;
		PE.Draw(P,Rotation);
		P.z = Position.z + 50;
		P.x = Position.x - 50;
		PE.Draw(P,Rotation);
		P.z = Position.z - 50;
		P.x = Position.x + 50;
		PE.Draw(P,Rotation);
		P.z = Position.z - 50;
		P.x = Position.x - 50;
		PE.Draw(P,Rotation);
		int Sum = 0;
		if(isFirstShoot)
		{
			for(int i = 0 ; i < 14 ; i++)
			{
				if(e[i].GetPosition().x > (Position.x - 50) && e[i].GetPosition().x < (Position.x + 50) && e[i].GetPosition().z > (Position.z - 50) && e[i].GetPosition().z < (Position.z + 50))
					if(!e[i].Dead)
					{
						e[i].HP -= 15;
						Sum += 15;
					}
					if(b.GetPosition().x > (Position.x - 50) && b.GetPosition().x < (Position.x + 50) && b.GetPosition().z > (Position.z - 50) && b.GetPosition().z < (Position.z + 50))
					if(!b.Dead)	
					{
						b.HP -= 15;
						Sum += 15;
					}
					if(fb.GetPosition().x > (Position.x - 50) && fb.GetPosition().x < (Position.x + 50) && fb.GetPosition().z > (Position.z - 50) && fb.GetPosition().z < (Position.z + 50))
					if(!fb.Dead)	
					{
						fb.HP -= 15;
						Sum += 15;
					}
			}
			HP += Sum/5;
			ValidateHP();
			isFirstShoot = false;
		}
	}
	bool isFirstShoot;
	int skillAttackSpeed;
	void Storm(NormalEnemy e[],Boss &b,FinalBoss &fb)
	{
		int range = 40;
		if(counting > 10)
		{
			shootLaser = false;
			counting = 0;
		}
		counting++;
		if(counting%3 == 0)
			laser = !laser;
		glLoadIdentity();
		glTranslatef(Position.x+50,-18,Position.z);
		glColor4f(1,1,1,1);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDepthMask(false);
		if(laser)
			glBindTexture(GL_TEXTURE_2D,texture[2]);
		else
			glBindTexture(GL_TEXTURE_2D,texture[1]);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(-3,7+range,0);
			glTexCoord2f(0,1);
			glVertex3f(3,7+range,0);
			glTexCoord2f(1,1);
			glVertex3f(3,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(-3,-1,0);
		}
		glEnd();

		glLoadIdentity();
		glTranslatef(Position.x-50,-18,Position.z);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(-3,7+range,0);
			glTexCoord2f(0,1);
			glVertex3f(3,7+range,0);
			glTexCoord2f(1,1);
			glVertex3f(3,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(-3,-1,0);
		}
		glEnd();

		glLoadIdentity();
		glTranslatef(Position.x,-18,Position.z+50);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(-3,7+range,0);
			glTexCoord2f(0,1);
			glVertex3f(3,7+range,0);
			glTexCoord2f(1,1);
			glVertex3f(3,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(-3,-1,0);
		}
		glEnd();
		
		glLoadIdentity();
		glTranslatef(Position.x,-18,Position.z-50);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(-3,7+range,0);
			glTexCoord2f(0,1);
			glVertex3f(3,7+range,0);
			glTexCoord2f(1,1);
			glVertex3f(3,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(-3,-1,0);
		}
		glEnd();

		glLoadIdentity();
		glTranslatef(Position.x,28,Position.z);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(0,0);
			glVertex3f(-50,0,50);
			glTexCoord2f(0,1);
			glVertex3f(50,0,50);
			glTexCoord2f(1,1);
			glVertex3f(50,0,-50);
			glTexCoord2f(1,0);
			glVertex3f(-50,0,-50);
		}
		glEnd();

		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);


		skillAttackSpeed ++;
		if(skillAttackSpeed % 40 == 0)
		{
			for(int i = 0 ; i < 14 ; i++)
			{
				if(e[i].GetPosition().x > (Position.x - 50) && e[i].GetPosition().x < (Position.x + 50) && e[i].GetPosition().z > (Position.z - 50) && e[i].GetPosition().z < (Position.z + 50))
					if(!e[i].Dead)
						e[i].HP -= 4;
				if(b.GetPosition().x > (Position.x - 50) && b.GetPosition().x < (Position.x + 50) && b.GetPosition().z > (Position.z - 50) && b.GetPosition().z < (Position.z + 50))
					if(!b.Dead)	
						b.HP -= 4;
				if(fb.GetPosition().x > (Position.x - 50) && fb.GetPosition().x < (Position.x + 50) && fb.GetPosition().z > (Position.z - 50) && fb.GetPosition().z < (Position.z + 50))
					if(!fb.Dead)	
						fb.HP -= 4;
			}
		}
	}
	void HeroShootLaser()
	{
		if(isAutoLook)
		{
			if(counting > 10)
			{
				shootLaser = false;
				counting = 0;
			}
			counting++;
			if(counting%3 == 0)
				laser = !laser;
			Vector3 pos;
			pos.x = Position.x;
			pos.y = 0;
			pos.z = Position.z;

			Vector3 d = Target - pos;
			Vector3 look = d;
			look.Normalize();
			Vector3 P = Vector3(look.x,0,look.z);			
			if(d.Magnitude() < 150)
			{
				glLoadIdentity();
				glTranslatef(Position.x,-18,Position.z);
				glColor4f(1,1,1,1);
				glEnable(GL_BLEND);
				glDisable(GL_LIGHTING);
				glDepthMask(false);
				if(laser)
					glBindTexture(GL_TEXTURE_2D,texture[2]);
				else
					glBindTexture(GL_TEXTURE_2D,texture[1]);
				glBegin(GL_POLYGON);
				{
					glTexCoord2f(0,0);
					glVertex3f(-1,(Position.y+18)/5,-1);
					glTexCoord2f(0,1);
					glVertex3f(1,(Position.y+18)/5,1);
					glTexCoord2f(1,1);
					glVertex3f(P.x*d.Magnitude()+1,0,P.z*d.Magnitude()+1);
					glTexCoord2f(1,0);
					glVertex3f(P.x*d.Magnitude()-1,0,P.z*d.Magnitude()-1);
				}
				glEnd();
				glDepthMask(true);
				glDisable(GL_BLEND);
				glDisable(GL_LIGHTING);
			}
		}
	}
	void ChangeTarget()
	{
		if(EnemyIndex < EnemiesCounter-1)
			EnemyIndex++;
		else
			EnemyIndex = 0;
	}
	void AutoLook(NormalEnemy e[],Boss &boss,FinalBoss &fboss)
	{
		EnemiesCounter = 0;
		for(int i = 0 ; i < 14 ; i++)
			TargetIndices[i] = -1;
		for(int i = 0 ; i < 14 ; i++)
		{
			if(e[i].IsDead())
				continue;
			Vector3 PlayerPos(e[i].GetPosition().x,0,e[i].GetPosition().z);
			Vector3 N = PlayerPos-Position;
			if(N.Magnitude() < bulletLifeTime)
			{
				TargetIndices[EnemiesCounter] = i;
				EnemiesCounter++;
			}
		}
		if(!boss.Dead)
		{
			Vector3 PlayerPos(boss.GetPosition().x,0,boss.GetPosition().z);
			Vector3 N = PlayerPos-Position;
			if(N.Magnitude() < bulletLifeTime)
			{
				TargetIndices[EnemiesCounter] = 11;
				EnemiesCounter++;
			}
		}
		if(!fboss.Dead)
		{
			Vector3 PlayerPos(fboss.GetPosition().x,0,fboss.GetPosition().z);
			Vector3 N = PlayerPos-Position;
			if(N.Magnitude() < bulletLifeTime)
			{
				TargetIndices[EnemiesCounter] = 12;
				EnemiesCounter++;
			}
		}
		float Rotation = 0;
		float NMagnitude;
		if(TargetIndices[EnemyIndex] == -1)
		{
			NoTarget = true;
			return;
		}
		NoTarget = false;
		Vector3 EnemyPos;
		if(TargetIndices[EnemyIndex] == 11)
			EnemyPos = Vector3(boss.Position.x+boss.EnemyRight,0,boss.Position.z+boss.EnemyDepth);
		else if(TargetIndices[EnemyIndex] == 12)
			EnemyPos = Vector3(fboss.Position.x+fboss.EnemyRight,0,fboss.Position.z+fboss.EnemyDepth);
		else
			EnemyPos = Vector3(e[TargetIndices[EnemyIndex]].GetPosition().x,0,e[TargetIndices[EnemyIndex]].GetPosition().z);
		Vector3 Pos;
		Pos.x = Position.x;
		Pos.y = 0;
		Pos.z = Position.z;
		Vector3 N = EnemyPos-Pos;
		SetTarget(EnemyPos,TargetIndices[EnemyIndex]);
		N.Normalize();
		NMagnitude = N.Magnitude();
		float EMagnitude = InitialLookDirection.Magnitude();
		float Res = N.x*InitialLookDirection.x+N.y*InitialLookDirection.y+N.z*InitialLookDirection.z;
		float Ceta = Res/(NMagnitude*EMagnitude);
		if(EnemyPos.x > Position.x)
			SetRotation(-(180/3.14157)*acos(Ceta)+90);
		else
			SetRotation((180/3.14157)*acos(Ceta)+90);
	}
	Vector3 GetPosition()
	{
		return Position;
	}
	void ChangeWeaponBetweenMeleeAndRanged()
	{
		if(model.GetTorsoCurrentAnimation() == TORSO_STAND ||model.GetTorsoCurrentAnimation() == TORSO_ATTACK)
		{
			weaponNumber = 0;
			model.SetTorsoAnimation(TORSO_STAND2);
			return;
		}
		else if(model.GetTorsoCurrentAnimation() == TORSO_STAND2 ||model.GetTorsoCurrentAnimation() == TORSO_ATTACK2)
		{
			weaponNumber = 1;
			model.SetTorsoAnimation(TORSO_STAND);
		}
	}
	void ChangeRangedWeapons()
	{
		weaponNumber++;
		if(weaponNumber == 3)
			weaponNumber = 1;
	}
	void ChangeWalkingMode()
	{
		if((model.GetLegsCurrentAnimation() == LEGS_WALK-7 || model.GetLegsCurrentAnimation() == LEGS_IDLE-7) &&!run)
		{
			run = true;
			Speed += 10;
			return;
		}
		if(model.GetLegsCurrentAnimation() == LEGS_RUN || model.GetLegsCurrentAnimation() == LEGS_IDLE-7)
		{
			Speed -= 10;
			run = false;
		}
	}
	void LoadTextures()
	{
		Player::LoadTexture();
		texture[1] = LoadGLTexture("images\\bullets\\B7.bmp");
		texture[2] = LoadGLTexture("images\\bullets\\B8.bmp");
	}
	void Draw()
	{
		glLoadIdentity();
		Position.y = -16+y;
		glTranslatef(Position.x,Position.y,Position.z);
		glRotatef(Rotation,0,1,0);
		glScalef(0.22,0.22,0.22);
		model.DrawModel();
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////Alies////////////////////////////////////////////////////////////////////////////////////////////

class Ally : public Player
{
public:
	Ally():Player(){}
	void LoadPlayer()
	{
		model.LoadModel("models\\lara");
		model.SetTorsoAnimation("TORSO_STAND");
		model.SetLegsAnimation("LEGS_IDLE");
	}
	
	void SetPlayerPosition(int x,int z){Position.x = x;Position.z = z;}
	void Attack(){}
	Vector3 GetPosition(){return Position;}
	AABoundingBox GetAABB() const {
		Vector3 dims(5, 5, 5);
		Vector3 P(Position.x,-16,Position.z);
		return AABoundingBox(P, 2*dims);
	}
	void ShootAt(){}
	void Revive()
	{
		model.SetTorsoAnimation("TORSO_STAND");
		model.SetLegsAnimation("LEGS_IDLE");
	}
	bool Update()
	{
		CheckIfDead();
		Draw();
		model.UpdateLowerModel();
		model.UpdateUpperModel();
		return true;
	}
	void Draw()
	{
		glLoadIdentity();
		Position.y = -16;
		glTranslatef(Position.x,Position.y,Position.z);
		glRotatef(Rotation+180,0,1,0);
		glScalef(0.22,0.22,0.22);
		model.DrawModel();
	}
};