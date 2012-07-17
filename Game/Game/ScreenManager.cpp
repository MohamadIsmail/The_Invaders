#include"AllIncludes.h"
#include "ScreenManager.h"
#include"LoadingScreen.h"
using namespace std;
 
int ScreenManager::elapsed_ticks;
stack <Screen*> ScreenManager::active_screens;
map <string, GLuint> all_textures;
int ScreenManager::window_XPos;
int ScreenManager::window_YPos;
int ScreenManager::window_Height;
int ScreenManager::window_Width;
char* ScreenManager::window_Title;
int ScreenManager::update_Rate;
GLuint ScreenManager::texture;


//Screen Manager Utilities 
void ScreenManager::Initialize(int argc,char* argv [], Screen* newScreen, int updateRate)
{
	window_XPos   = 100;
	window_YPos   = 100;
	window_Height = 600;
	window_Width  = 800;
	window_Title  = "The Invaders";
	update_Rate   = updateRate;
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(window_XPos,window_YPos);
	glutInitWindowSize(window_Width,window_Height);
	glutCreateWindow(window_Title);

	glutKeyboardUpFunc(&ScreenManager::GetKeyboardUpPress);
	glutSpecialFunc(&ScreenManager::GetSpecialDownPress);
	glutKeyboardFunc(&ScreenManager::GetKeyboardDownPress);
	glutReshapeFunc(&ScreenManager::HandleWindowResize);
	glutDisplayFunc(&ScreenManager::DrawScreen);
	glutMouseFunc(&ScreenManager::HandleMouse);
	glutPassiveMotionFunc(&ScreenManager::MousePassiveMotion);
	AddScreen(newScreen);
	//glutReshapeFunc(&ScreenManager::Reshape);
	glutInit(&argc,argv);
	glutIdleFunc(&ScreenManager::GetDoubleKeyPress);
	glutMainLoop();
}
void ScreenManager::AddScreen(Screen* newScreen)
{
	newScreen->Initialize();
	active_screens.push(newScreen);
	elapsed_ticks = 0;
}
void ScreenManager::SetControls(map<int,int> controls)
{
	active_screens.top()->controls = controls;
}
void ScreenManager::RemoveScreen()
{
	Screen* current = active_screens.top();
	glutPostRedisplay();
	active_screens.pop();
}
void ScreenManager::RemoveScreen(map<int,int> controls)
{
	Screen* current = active_screens.top();
	glutPostRedisplay();
	active_screens.pop();
	active_screens.top()->controls = controls;
}

Screen *ScreenManager::RemoveScreen_ptr()
{
	Screen* current = active_screens.top();
	glutPostRedisplay();
	active_screens.pop();
	return current;
}
void ScreenManager::GoToNextLevel(map<int,int> controls)
{
	AddScreen(new LoadingScreen(2));
	SetControls(controls);
}
void ScreenManager::LoadGame(SaveAndLoad &Load)
{
	AddScreen(new LoadingScreen(Load));
}
void ScreenManager::DrawScreen()
{
	glLoadIdentity();
	glEnable( GL_TEXTURE_2D );
	glClear(GL_COLOR_BUFFER_BIT);	
	
	glViewport(0,0,window_Width,window_Height);
//	ScreenManager::soundEngine.SetWindowHandler(GetActiveWindow());
	//ScreenManager::soundEngine.StartBackMusic();

	// to switch between different views !!
	
	//glutFullScreen();
	
	if (active_screens.top()->Is2D())
	{
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-100,100,-100,100);
	}
	else if(!active_screens.top()->Is2D())
	{
		glutInitDisplayMode(GLUT_RGBA);
		ShowCursor(true);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0f); 
		glEnable(GL_DEPTH_TEST);  
		glDepthFunc(GL_LEQUAL);
	}
	UpdateScreen();
	glClearColor(1, 1, 1, 1);
	active_screens.top()->Draw();
	glFlush();
	glutSwapBuffers();
	//glutPostOverlayRedisplay();
	glutPostRedisplay(); //marks the current or specified window as needing to be redisplayed.
}
void ScreenManager::UpdateScreen()
{
	int current =  glutGet(GLUT_ELAPSED_TIME);
	active_screens.top()->Update();
	if(current - elapsed_ticks > update_Rate)
	{
		active_screens.top()->Update();
		elapsed_ticks = current;
	}
}
void ScreenManager::Reshape (int width, int height) {  
	glViewport(0, 0, (GLsizei)ScreenManager::window_Width, (GLsizei)ScreenManager::window_Height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}  

//Keyboard Handler
void ScreenManager::GetSpecialDownPress(int key, int x, int y)
{
	active_screens.top()->GetSpecialDownPress(key);
}
void ScreenManager::GetKeyboardUpPress(unsigned char key, int x, int y)
{
	active_screens.top()->GetKeyboardUpPress(key);
}
void ScreenManager::GetKeyboardDownPress(unsigned char key, int x, int y)
{
	active_screens.top()->GetKeyboardDownPress(key);
}
void ScreenManager::HandleMouse(int button, int state, int x, int y)
{
	active_screens.top()->HandleMouse(button,state, x, y);
}
void ScreenManager::MouseActiveMotion(int x, int y)
{
	active_screens.top()->MouseActiveMotion(x, y);
}
void ScreenManager::MousePassiveMotion(int x, int y)
{
	active_screens.top()->MousePassiveMotion(x,y);
}
void ScreenManager::HandleWindowResize(int width, int height)
{
	window_Height = height;
	window_Width = width;
}
void ScreenManager::GetDoubleKeyPress()
{
	active_screens.top()->GetDoubleKeyPress();
}