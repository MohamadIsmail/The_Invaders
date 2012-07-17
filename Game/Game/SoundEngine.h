#ifndef SOUNDENGINE_H_
#define SOUNDENGINE_H_

#include"Sound.h"
class SoundEngine
{
	SoundClass *sound;
	HWND hwnd;
	bool isFirstTimeToPlayBackMusic;
	bool isHeroDied;
public:
	enum WhoGotHit{NONE,ENEMY,HERO};
	SoundEngine()
	{
		isFirstTimeToPlayBackMusic = true;
		isHeroDied = false;
		sound = new SoundClass();
	}
	void SetWindowHandler(HWND hwnd)
	{
		this->hwnd = hwnd;
	}
	void StartBackMusic(int musicIndex)
	{
		if(isFirstTimeToPlayBackMusic)
		{
			if(musicIndex == 0)
				PlaySound("musics\\start.wav",NULL, SND_ASYNC );
			if(musicIndex == 1)
				PlaySound("musics\\lvl1.wav",NULL, SND_ASYNC );
			if(musicIndex == 2)
				PlaySound("musics\\lvl2.wav",NULL, SND_ASYNC );
			isFirstTimeToPlayBackMusic = false;
		}
	}
	void SomeOneGotHit(int who,int x)
	{
		if(x == 'n')
			return;
		switch(who)
		{
		case ENEMY:
			sound->Initialize(hwnd,"sounds\\EP.wav");
			break;
		case HERO:
			sound->Initialize(hwnd,"sounds\\PP.wav");
			break;
		}
	}
	void SomeOneDied(int who)
	{
		switch(who)
		{
		case ENEMY:
			sound->Initialize(hwnd,"sounds\\ED.wav");
			break;
		case HERO:
			if(!isHeroDied)
			{
				sound->Initialize(hwnd,"sounds\\PD.wav");
				isHeroDied = true;
			}
			break;
		}
	}
	void WeaponAttack(int which)
	{
	
	}
};
#endif