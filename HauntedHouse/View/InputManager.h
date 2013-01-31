#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//#include <map>
#include <OgreSingleton.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>

namespace Ogre {
	class renderWindow;
}
namespace VIEW 
{
	class InputManager : public Ogre::Singleton<InputManager>, public OIS::KeyListener
	{
	public:
		InputManager();
		virtual ~InputManager();
		void Initialize(Ogre::RenderWindow* rwindow);

		void capture();
		bool keyPressed(const OIS::KeyEvent &evt);
		bool keyReleased(const OIS::KeyEvent &evt);

		static InputManager& getSingleton(void);
		static InputManager* getSingletonPtr(void);
		//inline Ogre::InputReader* getInputDevice() const { return mInputDevice; }
		//inline Ogre::EventProcessor* getEventProcessor() const { return mEventProcessor; }
	private:
		//Ogre::EventProcessor* mEventProcessor;
		//Ogre::InputReader* mInputDevice;
		OIS::Keyboard *mKeyboard;
		//std::map<std::string, OIS::KeyListener*> mKeyListeners;

		static OIS::InputManager *mInputSystem;
	};
}
 
#endif