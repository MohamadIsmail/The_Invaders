#ifndef MAINGAMESCREEN_H_
#define MAINGAMESCREEN_H_

#include "Screen.h"
//#include "GameWorld.h"
class MainGameScreen:public Screen
{
	static const bool is2D = true;
	//GameWorld _theWorld;
	
	void Initialize()
	{
		 this->_theWorld = GameWorld(100,10,30,3,80);
	}

	void Draw(){
		this->_theWorld.Draw();
		glColor3f(0, 0, 0);
	}
	void Update()
	{
		this->_theWorld.Update();
	}
	
	bool Is2D(){return this->is2D;}
    void GetKeyboardDownPress(int key)
	{
		if(key == 27)
			ScreenManager::RemoveScreen();
		else if(key == 'g')
			this->_theWorld.withGravity = true;
		else if(key == 'f')
			this->_theWorld.withGravity = false;
		else if(key == 'r')
			this->_theWorld = GameWorld(100,10,30,3,80);
		else if(key == 'e')
			this->_theWorld.Electric();
		
	}
	void GetKeyboardUpPress(int key)
	{
	}
    void GetSpecialDownPress(int key)
	{
		if ( key == GLUT_KEY_UP )
			this->_theWorld.player_circle._velocity.Y +=10;
		if ( key == GLUT_KEY_DOWN )
			this->_theWorld.player_circle._velocity.Y -=5;
		if ( key == GLUT_KEY_RIGHT )
			this->_theWorld.player_circle._velocity.X +=10;
		if ( key == GLUT_KEY_LEFT )
			this->_theWorld.player_circle._velocity.X -=5;
	}
};


#endif