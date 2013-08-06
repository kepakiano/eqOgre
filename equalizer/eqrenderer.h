#ifndef EQRENDERER_H
#define EQRENDERER_H

#ifndef GLEW_MX
# define GLEW_MX
#endif

#include <eq/eq.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "equalizer/initdata.h"
#include "equalizer/config.h"

#include "../IRenderer.h"

class EqRenderer : public IRenderer
{
public:
    EqRenderer();
    virtual ~EqRenderer();

    virtual bool init(int argc, char *argv[]);
    virtual bool isRunning();
    virtual void update();
    virtual void clear();
    virtual void exit();

private:
    vr::Config *_config;
    vr::InitData _init_data;
};

#endif // EQRENDERER_H
