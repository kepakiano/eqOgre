#include "ogrerenderer.h"

#include "ogreapplication.h"

#include <OgreWindowEventUtilities.h>

OgreRenderer::OgreRenderer()
{
}

OgreRenderer::~OgreRenderer()
{
    _ogre.reset();
}

bool OgreRenderer::init(int argc, char *argv[])
{
    _ogre = std::make_shared<OgreApplication>();
    return _ogre->initStart() && _ogre->initFinish(_ogreActors, true);
}

bool OgreRenderer::isRunning()
{
    return _ogre->isRunning();
}

void OgreRenderer::clear()
{
}

void OgreRenderer::update()
{
//    std::cout << "OgreRenderer::update" << std::endl <<
//             "#ogreActors: " << _ogreActors.size() << std::endl <<
//                 "#diffActors: " << _diffActors.size() << std::endl <<
//                 "#newOgreActors: " << _newOgreActors.size() << std::endl;

    _ogre->updateNodes(_newOgreActors, _diffActors);
    _ogre->getRoot()->renderOneFrame();
    _ogre->getWindow()->update(true);
    Ogre::WindowEventUtilities::messagePump() ;
}

void OgreRenderer::exit()
{
    _ogre->exit();
}
