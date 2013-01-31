//#include <OgreEventProcessor.h>

#include "InputManager.h"
#include <OgreRenderWindow.h>
 
using namespace VIEW;

template<> InputManager* Ogre::Singleton<InputManager>::msSingleton = 0;
OIS::InputManager* InputManager::mInputSystem = 0;
 
InputManager::InputManager()
	: mKeyboard(0)
{
    //mEventProcessor = new Ogre::EventProcessor();
    //mEventProcessor->initialise(rwindow);
    //mEventProcessor->startProcessingEvents();
    //mInputDevice = mEventProcessor->getInputReader();




}
 
InputManager::~InputManager()
{
    //if (mEventProcessor)
    //    delete mEventProcessor;
    //assert(mInputDevice);
    //Ogre::PlatformManager::getSingleton().destroyInputReader(mInputDevice);
	if( mInputSystem ) { 
        if( mKeyboard ) {
            mInputSystem->destroyInputObject( mKeyboard );
            mKeyboard = 0;
        } 
        // If you use OIS1.0RC1 or above, uncomment this line
        // and comment the line below it
        mInputSystem->destroyInputSystem( mInputSystem );
        //mInputSystem->destroyInputSystem();
        mInputSystem = 0;
 
        // Clear Listeners
        //mJoystickListeners.clear();
    }
}

void InputManager::Initialize(Ogre::RenderWindow* rwindow)
{
	if( !mInputSystem ) {
		// Setup basic variables
		OIS::ParamList paramList;    
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		// Get window handle
		rwindow->getCustomAttribute( "WINDOW", &windowHnd );

		// Fill parameter list
		windowHndStr << (unsigned int) windowHnd;
		paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );

		// Create inputsystem
		mInputSystem = OIS::InputManager::createInputSystem( paramList );

		// If possible create a buffered keyboard
		// (note: if below line doesn't compile, try:  if (mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
		//if( mInputSystem->numKeyboards() > 0 ) {
		if (mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
			mKeyboard = static_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
			mKeyboard->setEventCallback( this );
		}
	}
}

void InputManager::capture() 
{
    mKeyboard->capture();
}

// KeyListener
bool InputManager::keyPressed(const OIS::KeyEvent &evt) {
    return true;
}
 
bool InputManager::keyReleased(const OIS::KeyEvent &evt) {
    //if (evt.key == OIS::KC_ESCAPE)
    //    m_simulation->requestStateChange(SHUTDOWN);
 
    return true;
}

InputManager* InputManager::getSingletonPtr(void)
{
    return msSingleton;
}
 
InputManager& InputManager::getSingleton(void)
{  
    assert(msSingleton);
    return *msSingleton;
}