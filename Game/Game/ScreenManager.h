#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include "AllIncludes.h"
#include "Screen.h"
#include "SoundEngine.h"
using namespace std;
class ScreenManager
{
private: 
	static int elapsed_ticks;
	static GLuint texture;
	static stack <Screen*> active_screens;
	//static SoundEngine soundEngine;
	//static map <string, GLuint> all_textures;
public:
	static int window_XPos;
	static int window_YPos;
	static int window_Height;
	static int window_Width;
	static char* window_Title;
	static int update_Rate;
	static void Initialize(int,char* [],Screen*,int);
	static void AddScreen(Screen*);
	static void RemoveScreen();
	static void RemoveScreen(map<int,int> controls);
	static Screen *RemoveScreen_ptr();
	static void DrawScreen();
	static void UpdateScreen();
	static void GoToNextLevel(map<int,int>controls);
	static void LoadGame(SaveAndLoad &Load);

	static void GetKeyboardDownPress(unsigned char, int, int);
	static void GetKeyboardUpPress(unsigned char, int, int);
	static void GetSpecialDownPress(int, int, int);
	static void HandleMouse(int, int ,int, int);
	static void MouseActiveMotion(int, int);
	static void MousePassiveMotion(int, int);
	static void GetDoubleKeyPress();
	static void HandleWindowResize(int, int);
	static void Reshape (int,int);
	static void SetControls(map<int,int> controls);
};
#endif