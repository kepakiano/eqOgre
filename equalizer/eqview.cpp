#include "eqview.h"

#include "eqrenderer.h"

EqView::EqView()
{
    _renderer = std::make_shared<EqRenderer>();
}

void EqView::update()
{
    _renderer->update();
}

bool EqView::isRunning()
{
    return _renderer->isRunning();
}

void EqView::exit()
{
    _renderer->exit();
}

bool EqView::init(int argc, char *argv[])
{
    _renderer->init(argc, argv);
}
