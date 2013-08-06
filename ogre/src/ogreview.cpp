#include "ogreview.h"

#include "ogrerenderer.h"

OgreView::OgreView()
{
    _renderer = std::make_shared<OgreRenderer>();
}

void OgreView::update()
{
    _renderer->update();
}

bool OgreView::isRunning()
{
    return _renderer->isRunning();
}

void OgreView::exit()
{
    _renderer->exit();
}

bool OgreView::init(int argc, char *argv[])
{
    _renderer->init(argc, argv);
}
