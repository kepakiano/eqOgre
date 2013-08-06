#include "eqrenderer.h"
#include <iostream>

#include "equalizer/node.h"
#include "equalizer/pipe.h"
#include "equalizer/window.h"
#include "equalizer/channel.h"
#include "equalizer/node.h"
#include "equalizer/nodefactory.h"
#include "equalizer/serializableogreactor.h"

#define SAFE_DELETE(x) if(x) delete x; x=NULL;

EqRenderer::EqRenderer()
{
}

EqRenderer::~EqRenderer()
{
    SAFE_DELETE(_config);
}

bool EqRenderer::init(int argc, char *argv[])
{
    /* Initialize Equalizer */
    vr::NodeFactory node_factory;
    if (!eq::init(argc, argv, &node_factory)) {
        std::cerr << "Equalizer initialization failed!" << std::endl;
        return 1;
    }

    /* Initialize InitData */
    _init_data.data.seed = static_cast<unsigned int>(time(NULL));
    _init_data.data.tracking = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            _init_data.data.tracking = true;
            break;
        }
    }

    _init_data._ogreActors.clear();
    for(std::shared_ptr<OgreActor> actor : _ogreActors)
        _init_data._ogreActors.push_back(SerializableOgreActor(actor));

    /* Get a configuration */
    // The following code is only executed on the application node because
    // eq::getConfig() does not return on other nodes.
    _config = static_cast<vr::Config *>(eq::getConfig(argc, argv));

    return _config->init(_init_data);
}


bool EqRenderer::isRunning()
{
    return _config->isRunning();
}

void EqRenderer::update()
{
    _config->setGameState(_newOgreActors, _diffActors);

    _config->startFrame();
    _config->finishFrame();
}

void EqRenderer::clear()
{
    // TODO clear anything you know about the current level
}

void EqRenderer::exit()
{
    if(_config){
        /* Exit configuration */
        _config->exit();
        /* Release configuration */
        eq::releaseConfig(_config);
        /* Exit */
        eq::exit();
    }
}
