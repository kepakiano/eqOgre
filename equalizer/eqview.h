#ifndef EQVIEW_H
#define EQVIEW_H

#include "../IGameView.h"

class EqView : public IGameView
{
public:
    EqView();

    virtual bool init(int argc, char *argv[]);
    virtual void update();
    virtual bool isRunning();
    virtual void exit();
};

#endif // EQVIEW_H
