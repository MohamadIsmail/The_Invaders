#include<string>
#include<iostream>

using namespace std;
class Skill
{
public:
	Skill(string Name){SkillName = Name;Buff = false;Storm = false;Vam= false;sniper = false;isSkillOnCoolDown = false;isSkillUsed= false;bulletLifeTime = 100;bulletSpeed = 40;damage=1; ebulletSpeed = 40;speedReduction = 0.4;SkillDurationEnded = false;hasDuration = false;
	Emission = Vector3(0,0,0);Ambient = Vector3(1,1,1);Visible = true;}
	string SkillName;
	Vector3 Emission;
	Vector3 Ambient;
	int damage;
	int bulletSpeed;
	int ebulletSpeed;
	float speedReduction;
	int Mana;
	int duration;
	bool Vam;
	bool Storm;
	bool Buff;
	bool sniper;
	bool SkillDurationEnded;
	bool hasDuration;
	bool Visible;
	int coolDown;
	int currentTime;
	float bulletLifeTime;
	bool isSkillUsed;
	bool isSkillOnCoolDown;
	virtual void UseSkill(ThirdPersonCamera &camera)=0;
	virtual void SkillDone(ThirdPersonCamera &camera)=0;
	virtual void SkillOnCoolDown()=0;
};

class SniperSkill : public Skill
{
public:
	//100 = 2 sec
	SniperSkill():Skill("SN"){coolDown = 100;Mana = 10;}
	void UseSkill(ThirdPersonCamera &camera)
	{
		if(!isSkillOnCoolDown)
		{
			sniper = true;
			isSkillUsed = true;
			camera.SniperMode = true;
			damage = 10;
			bulletSpeed = 100;
			bulletLifeTime = 700;
		}
	}
	void SkillDone(ThirdPersonCamera &camera)
	{
		sniper = false;
		isSkillOnCoolDown = true;
		camera.SniperMode = false;
		damage = 1;
		bulletSpeed = 40;
		bulletLifeTime = 100;
		currentTime = 0;
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
			{
				isSkillOnCoolDown = false;
				isSkillUsed = false;
			}
		}
	}

};

class SlowMotionSkill : public Skill
{
public:
	SlowMotionSkill():Skill("SM"){duration = 600;currentTime = 0;coolDown = 500;Mana = 20;SkillDurationEnded = false;hasDuration = true;}
	void UseSkill(ThirdPersonCamera &camera )
	{
		if(!isSkillOnCoolDown)
		{
			Emission = Vector3(1,0,0);
			Ambient = Vector3(1,0,0);
			isSkillUsed = true;
			speedReduction = 0.2;
			ebulletSpeed = 5;
			currentTime ++;
			if(currentTime > duration)
				SkillDurationEnded = true;
		}
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
		isSkillOnCoolDown = true;
		isSkillUsed = false;
		SkillDurationEnded = false;
		currentTime = 0;
		Emission = Vector3(0,0,0);
		Ambient = Vector3(1,1,1);
		ebulletSpeed = 40;
		speedReduction = 0.4;
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
				isSkillOnCoolDown = false;
		}
	}

};

class HiddenSkill : public Skill
{
public:
	HiddenSkill():Skill("H"){duration = 600;currentTime = 0;coolDown = 500;Mana = 20;SkillDurationEnded = false;hasDuration = true;}
	void UseSkill(ThirdPersonCamera &camera )
	{
		if(!isSkillOnCoolDown)
		{
			Emission = Vector3(0.7,0,1);
			Ambient = Vector3(0.7,0,1);
			isSkillUsed = true;
			currentTime ++;
			Visible = false;
			if(currentTime > duration)
				SkillDurationEnded = true;
		}
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
		isSkillOnCoolDown = true;
		isSkillUsed = false;
		SkillDurationEnded = false;
		currentTime = 0;
		Emission = Vector3(0,0,0);
		Ambient = Vector3(1,1,1);
		Visible = true;
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
				isSkillOnCoolDown = false;
		}
	}

};

class BuffSkill : public Skill
{
public:
	BuffSkill():Skill("B"){duration = 600;currentTime = 0;coolDown = 500;Mana = 20;SkillDurationEnded = false;hasDuration = true;}
	void UseSkill(ThirdPersonCamera &camera )
	{
		if(!isSkillOnCoolDown)
		{
			Emission = Vector3(1,0.6,0);
			Ambient = Vector3(1,0.6,0);
			Buff = true;
			currentTime ++;
			isSkillUsed = true;
			if(currentTime > duration)
				SkillDurationEnded = true;
		}
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
		isSkillOnCoolDown = true;
		isSkillUsed = false;
		SkillDurationEnded = false;
		currentTime = 0;
		Emission = Vector3(0,0,0);
		Ambient = Vector3(1,1,1);
		Buff = false;
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
				isSkillOnCoolDown = false;
		}
	}

};

class VampireAuraSkill : public Skill
{
public:
	VampireAuraSkill():Skill("V"){duration = 100;currentTime = 0;coolDown = 800;Mana = 40;SkillDurationEnded = false;hasDuration = true;}
	void UseSkill(ThirdPersonCamera &camera )
	{
		if(!isSkillOnCoolDown)
		{
			Emission = Vector3(1,0.2,0.2);
			Ambient = Vector3(1,0.2,0.2);
			currentTime ++;
			isSkillUsed = true;
			if(currentTime > duration)
				SkillDurationEnded = true;
			Vam = true;
		}
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
		isSkillOnCoolDown = true;
		currentTime = 0;
		Vam = false;
		isSkillUsed = false;
		SkillDurationEnded = false;
		Emission = Vector3(0,0,0);
		Ambient = Vector3(1,1,1);
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
				isSkillOnCoolDown = false;
		}
	}

};

class LightningSkill : public Skill
{
public:
	LightningSkill():Skill("L"){currentTime = 0;coolDown = 100;Mana = 5;}
	void UseSkill(ThirdPersonCamera &camera )
	{
		if(!isSkillOnCoolDown)
		{
			isSkillUsed = true;
		}
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
		isSkillOnCoolDown = true;
		isSkillUsed = false;
		currentTime = 0;
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
				isSkillOnCoolDown = false;
		}
	}

};

class UpgradeSkill : public Skill
{
public:
	UpgradeSkill():Skill("U"){}
	void UseSkill(ThirdPersonCamera &camera )
	{
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
	}
	void SkillOnCoolDown()
	{
	}

};

class StormSkill : public Skill
{
public:
	StormSkill():Skill("S"){duration = 300;currentTime = 0;coolDown = 800;Mana = 40;SkillDurationEnded = false;hasDuration = true;}
	void UseSkill(ThirdPersonCamera &camera )
	{
		if(!isSkillOnCoolDown)
		{		
			Emission = Vector3(0.2,0.2,1);
			Ambient = Vector3(0.2,0.2,1);
			currentTime ++;
			isSkillUsed = true;
			if(currentTime > duration)
				SkillDurationEnded = true;
			Storm = true;
		}
	}
	void SkillDone(ThirdPersonCamera &camera )
	{
		isSkillOnCoolDown = true;
		currentTime = 0;
		Storm = false;
		isSkillUsed = false;
		SkillDurationEnded = false;
		Emission = Vector3(0,0,0);
		Ambient = Vector3(1,1,1);
	}
	void SkillOnCoolDown()
	{
		if(isSkillOnCoolDown)
		{
			if(currentTime < coolDown)
				currentTime++;
			else
				isSkillOnCoolDown = false;
		}
	}

};