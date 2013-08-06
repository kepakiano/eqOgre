#ifndef OGRERENDERER_H
#define OGRERENDERER_H

#include <memory>

#include "../IRenderer.h"

class OgreApplication;

class OgreRenderer : public IRenderer
{
public:
    OgreRenderer();
    virtual ~OgreRenderer();

    virtual void update();
    virtual bool init(int argc, char *argv[]);
    virtual bool isRunning();
    virtual void clear();
    virtual void exit();

private:
    std::shared_ptr<OgreApplication> _ogre;
};

#endif // OGRERENDERER_H
