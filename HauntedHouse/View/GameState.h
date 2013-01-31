#ifndef GAMESTATE_H
#define GAMESTATE_H
 
#include <Ogre.h>
#include "GameManager.h"

//namespace OIS {
//	class KeyEvent;
//}

//namespace Ogre {
//	struct FrameEvent;
//}

namespace VIEW
{
	class GameState
	{
	public:
		virtual void enter() = 0;
		virtual void exit() = 0;
 
		virtual void pause() = 0;
		virtual void resume() = 0;
 
		virtual void keyClicked(OIS::KeyEvent* e) = 0;
		virtual void keyPressed(OIS::KeyEvent* e) = 0;
		virtual void keyReleased(OIS::KeyEvent* e) = 0;

		virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
		virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;
 
		void changeState(GameState* state)	{ GameManager::getSingletonPtr()->changeState(state); }
		void pushState(GameState* state)	{ GameManager::getSingletonPtr()->pushState(state); }
		void popState()						{ GameManager::getSingletonPtr()->popState(); }

	protected:
		GameState() { }
		virtual ~GameState() { }
	};
}
 
#endif