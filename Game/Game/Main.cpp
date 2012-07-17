#include <iostream>
#include "AllIncludes.h"
//#include "Screen.h"
#include "ScreenManager.h"
#include "IntroductionScreen.h"
//#include "WelcomingScreen.h"

using namespace std;
int main(int argc, char* argv[])
{
	ScreenManager::Initialize(argc,argv,new WelcomingScreen(),5);
	//ScreenManager::Initialize(argc,argv,new IntroductionScreen(),5);
}
