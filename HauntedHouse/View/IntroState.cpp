#include "IntroState.h"

using namespace VIEW;

void IntroState::enter() {



}
void IntroState::exit(){}
 
void IntroState::pause(){}
void IntroState::resume(){}
 
void IntroState::keyClicked(OIS::KeyEvent* e) {}
void IntroState::keyPressed(OIS::KeyEvent* e) {}
void IntroState::keyReleased(OIS::KeyEvent* e) {}

bool IntroState::frameStarted(const Ogre::FrameEvent& evt) 
{
	return true;
}
bool IntroState::frameEnded(const Ogre::FrameEvent& evt)
{
	return true;
}