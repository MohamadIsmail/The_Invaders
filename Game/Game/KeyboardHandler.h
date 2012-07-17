#ifndef KEYBOARDHANDLER_H_
#define KEYBOARDHANDLER_H_


class KeyboardHandler
{
public:
	KeyboardHandler(){}
	virtual void GetKeyboardDownPress(int)=0;
	virtual void GetKeyboardUpPress(int)=0;
	virtual void GetSpecialDownPress(int)=0;
	virtual void GetDoubleKeyPress()=0;
};

#endif