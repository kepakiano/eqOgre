#ifndef OGREVIEW_H
#define OGREVIEW_H

#include "../IGameView.h"

class OgreView : public IGameView
{
public:
    OgreView();

    virtual bool init(int argc, char *argv[]);
    virtual void update();
    virtual bool isRunning();
    virtual void exit();
};

#endif // OGREVIEW_H
