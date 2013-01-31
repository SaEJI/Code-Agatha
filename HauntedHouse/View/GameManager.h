#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
 
#include <vector>
#include <Ogre.h>
//#include <OISKeyboard.h>
#include <OgreSingleton.h>
 
//#include "InputManager.h"

namespace OIS {
	class KeyEvent;
}

namespace VIEW
{
	class GameState;
	class InputManager;
 
	class GameManager : public Ogre::FrameListener, //public OIS::KeyListener,
		public Ogre::Singleton<GameManager>
	{
	public:
		GameManager();
		~GameManager();

		void start(GameState* state);
		void loop();

		void changeState(GameState* state);
		void pushState(GameState* state);
		void popState();
		static GameManager& getSingleton(void);
		static GameManager* getSingletonPtr(void);

	protected:
		Ogre::Root* mRoot;
		Ogre::RenderWindow* mRenderWindow;
		InputManager* mInputManager;
 
		void setupResources(void);
		bool configure(void);
 
		void keyClicked(OIS::KeyEvent* e);
		void keyPressed(OIS::KeyEvent* e);
		void keyReleased(OIS::KeyEvent* e);
		
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);
	private:
		std::vector<GameState*> mStates;
	};
}
 
#endif