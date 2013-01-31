#include <Windows.h>
#include "View\GameManager.h"
#include "View\IntroState.h"

#pragma warning( disable : 4251 )
#define WIN32_LEAN_AND_MEAN

int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	VIEW::GameManager *app = new VIEW::GameManager;
	VIEW::IntroState *inState = new VIEW::IntroState;

	app->start(inState);
	app->loop();

	//try {
	//	app.go();
	//} catch( Ogre::Exception& e ) {
	//	MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	//}
	delete inState;
	delete app;
	
    return 0;
}