//#include <Ogre.h>
 #include <OgrePlugin.h>

#include "GameManager.h"
#include "InputManager.h"
#include "GameState.h"
 
//using namespace Ogre;
//using namespace OIS;
using namespace VIEW;
 
template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = 0;
 
GameManager::GameManager() 
	: mRoot(0), mInputManager(0)
{
    //mRoot = 0;
    //mInputManager = 0;
}
 
GameManager::~GameManager()
{
    // clean up all the states
    while (!mStates.empty()) {
        //mStates.back()->exit();
        mStates.pop_back();
    }
 
    if (mInputManager)
        delete mInputManager;
 
    if (mRoot)
        delete mRoot;
}
 
void GameManager::start(GameState* state)
{
    mRoot = new Ogre::Root("", "", "LowLevelOgre.log");
 
    if (!configure()) return;
	
	setupResources();
 
    mRoot->addFrameListener(this);
	mInputManager = new InputManager();
	mInputManager->Initialize(mRenderWindow);//mRoot->getAutoCreatedWindow());

   // mInputManager->getEventProcessor()->addKeyListener(this);
 
    changeState(state);
 
    mRoot->startRendering();
}

void GameManager::loop()
{
	while(true)
	{
		// Pump window messages for nice behaviour
		Ogre::WindowEventUtilities::messagePump();

		// Render a frame
		mRoot->renderOneFrame();

		mInputManager->capture();

		if(mRenderWindow->isClosed())
		{
			return;
		}
	}
}
 
void GameManager::changeState(GameState* state)
{
    // cleanup the current state
    if ( !mStates.empty() ) {
        mStates.back()->exit();
        mStates.pop_back();
    }
 
    // store and init the new state
    mStates.push_back(state);
    mStates.back()->enter();
}
 
void GameManager::pushState(GameState* state)
{
    // pause current state
    if ( !mStates.empty() ) {
        mStates.back()->pause();
    }
 
    // store and init the new state
    mStates.push_back(state);
    mStates.back()->enter();
}
 
void GameManager::popState()
{
    // cleanup the current state
    if ( !mStates.empty() ) {
        mStates.back()->exit();
        mStates.pop_back();
    }
 
    // resume previous state
    if ( !mStates.empty() ) {
        mStates.back()->resume();
    }
}
 
void GameManager::setupResources(void)
{
    //// load resource paths from config file
    //ConfigFile cf;
    //cf.load("resources.cfg");
 
    //// go through all settings in the file
    //ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
    //String secName, typeName, archName;
    //while (seci.hasMoreElements())
    //{
    //    secName = seci.peekNextKey();
    //    ConfigFile::SettingsMultiMap *settings = seci.getNext();
    //    ConfigFile::SettingsMultiMap::iterator i;
    //    for (i = settings->begin() ; i != settings->end() ; ++i)
    //    {
    //        typeName = i->first;
    //        archName = i->second;
    //        ResourceGroupManager::getSingleton().addResourceLocation(
    //            archName, typeName, secName);
    //    }
    //}
}
 
bool GameManager::configure(void)
{
    //// load config settings from ogre.cfg
    //if (!mRoot->restoreConfig())
    //{
    //    // if there is no config file, show the configuration dialog
    //    if (!mRoot->showConfigDialog())
    //    {
    //        return false;
    //    }
    //}
 
    //// initialise and create a default rendering window
    //mRenderWindow = mRoot->initialise(true);
 
    //ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// -- NEW --

	// A list of required plugins
    Ogre::StringVector required_plugins;
    required_plugins.push_back("GL RenderSystem");
   // required_plugins.push_back("Octree & Terrain Scene Manager");
 
    // List of plugins to load
    Ogre::StringVector plugins_toLoad;
    plugins_toLoad.push_back("RenderSystem_GL");
    //plugins_toLoad.push_back("Plugin_OctreeSceneManager");
 
    // Load the OpenGL RenderSystem and the Octree SceneManager plugins
    for (Ogre::StringVector::iterator j = plugins_toLoad.begin(); j != plugins_toLoad.end(); j++)
    {
#ifdef _DEBUG
        mRoot->loadPlugin(*j + Ogre::String("_d"));
#else
        mRoot->loadPlugin(*j);
#endif;
    }
 
    // Check if the required plugins are installed and ready for use
    // If not: exit the application
    Ogre::Root::PluginInstanceList ip = mRoot->getInstalledPlugins();
    for (Ogre::StringVector::iterator j = required_plugins.begin(); j != required_plugins.end(); j++)
    {
        bool found = false;
        // try to find the required plugin in the current installed plugins
        for (Ogre::Root::PluginInstanceList::iterator k = ip.begin(); k != ip.end(); k++) {
            if ((*k)->getName() == *j) {
                found = true;
                break;
            }
        }
        if (!found)  // return false because a required plugin is not available
        {
            return false;
        }
    }
 
////-------------------------------------------------------------------------------------
//    // setup resources
//    // Only add the minimally required resource locations to load up the Ogre head mesh
//    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../media/materials/programs", "FileSystem", "General");
//    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../media/materials/scripts", "FileSystem", "General");
//    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../media/materials/textures", "FileSystem", "General");
//    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../media/models", "FileSystem", "General");
// 
//-------------------------------------------------------------------------------------
    // configure
    // Grab the OpenGL RenderSystem, or exit
    Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
    if(!(rs->getName() == "OpenGL Rendering Subsystem"))
    {
        return false; //No RenderSystem found
    }
    // configure our RenderSystem
    rs->setConfigOption("Full Screen", "No");
    rs->setConfigOption("VSync", "No");
    rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit");
 
    mRoot->setRenderSystem(rs);
 
    mRenderWindow = mRoot->initialise(true, "LowLevelOgre Render Window");
 
    return true;
}
 
//void GameManager::keyClicked(KeyEvent* e)
//{
//    // call keyClicked of current state
//    mStates.back()->keyClicked(e);
//}
// 
//void GameManager::keyPressed(KeyEvent* e)
//{
//    // call keyPressed of current state
//    mStates.back()->keyPressed(e);
//}
// 
//void GameManager::keyReleased(KeyEvent* e)
//{
//    // call keyReleased of current state
//    mStates.back()->keyReleased(e);
//}
 
bool GameManager::frameStarted(const Ogre::FrameEvent& evt)
{
    // call frameStarted of current state
    return mStates.back()->frameStarted(evt);
}
 
bool GameManager::frameEnded(const Ogre::FrameEvent& evt)
{
    // call frameEnded of current state
    return mStates.back()->frameEnded(evt);
}
 
GameManager* GameManager::getSingletonPtr(void)
{
    return msSingleton;
}
 
GameManager& GameManager::getSingleton(void)
{  
    assert(msSingleton);
    return *msSingleton;
}