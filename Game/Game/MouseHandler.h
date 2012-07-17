#ifndef MOUSEHANDLER_H_	
#define MOUSEHANDLER_H_	

class MouseHandler
{
public:
	MouseHandler()
	{}
	virtual void HandleMouse(int,int,int, int) = 0;
	virtual void MouseActiveMotion(int, int)=0;
	virtual void MousePassiveMotion(int, int)=0;
};
#endif