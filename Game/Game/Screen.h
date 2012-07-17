#ifndef SCREEN_H_
#define SCREEN_H_
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include<map>
class Screen:public KeyboardHandler,public MouseHandler
{
public:
	std::map<int,int> controls;
	virtual bool Is2D();
	virtual void Initialize();
	virtual void Draw();
	virtual void Update();
	void GetKeyboardDownPress(int key){}
	void GetKeyboardUpPress(int key){}
	void GetSpecialDownPress(int key){}
	void HandleMouse(int buttton,int state, int x, int y){}
	void GetDoubleKeyPress(){}
	void MouseActiveMotion(int x, int y){}
	void MousePassiveMotion(int x, int y){}
};
#endif