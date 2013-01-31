#ifndef INTROSTATE_H
#define INTROSTATE_H
 
#include "GameState.h"

namespace VIEW
{
	class IntroState : public GameState
	{
	public:
		void enter();
		void exit();
 
		void pause();
		void resume();
 
		void keyClicked(OIS::KeyEvent* e);
		void keyPressed(OIS::KeyEvent* e);
		void keyReleased(OIS::KeyEvent* e);

		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);

		IntroState() : GameState() { }
		~IntroState() { }
	};
}
 
#endif