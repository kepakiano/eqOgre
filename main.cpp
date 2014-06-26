/*
* Copyright (C) 2013-2014
* Sebastian Schmitz <sschmitz@informatik.uni-siegen.de>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include "equalizer/headers/config.h"
#include "equalizer/headers/nodefactory.h"
#include "equalizer/headers/initdata.h"
#include "datastructures/headers/ogreactor.h"

int start_x = -5, end_x = 5;
Vec3 axis(0, 2, -5);


// Let the ogreheads move like a wave so that we can see something is happening
std::list<std::shared_ptr<DiffActor>> getDiffActors(size_t frame)
{
    std::list<std::shared_ptr<DiffActor>> diffActors;
    for(int x = start_x; x <= end_x; x++){
        Vec4 rotation(0,sin(x/2.0f + frame/50.0f),0,1);
        Vec3 position = axis;
        position = position + Vec3(x, sin(x/2.0f + frame/50.0f), 0.0f);

        std::stringstream ss;
        ss << "object_" << x;
        std::string objectName = ss.str();

        std::shared_ptr<DiffActor> diffActor = std::make_shared<DiffActor>(objectName, position, rotation);
        diffActors.push_back(diffActor);
    }
    return diffActors;
}

/*
 * Main
 */

int main(int argc, char *argv[])
{

    /* Initialize Equalizer */
    vr::NodeFactory nodeFactory;
    if (!eq::init(argc, argv, &nodeFactory))
    {
        std::cerr << "Equalizer initialization failed!" << std::endl;
        return 1;
    }

    /* Initialize InitData */
    vr::InitData initData;
    initData.data.seed = static_cast<unsigned int>(time(NULL));

    // Create some ogre heads and let them float
    for(int x = start_x; x <= end_x; x++){
        Vec4 rotation(0,0,0,1);
        Vec3 position = axis;
        position = position + Vec3(x, 0.0f, 0.0f);
        Vec3 scale(0.007f,0.007f,0.007f);

        std::stringstream ss;
        ss << "object_" << x;
        std::string objectName = ss.str();
        std::string meshname = "ogrehead.mesh";
        std::string entname = "ENT_" + objectName;
        std::shared_ptr<OgreActor> ogreActor = std::make_shared<OgreActor>
            (objectName, OgreEntity, position, rotation, meshname, entname, "", true, scale);
        initData._ogreActors.push_back(ogreActor);
    }

    /* Get a configuration */
    bool error = false;
    vr::Config *config = static_cast<vr::Config *>(eq::getConfig(argc, argv));
    size_t frames = 0;
    // The following code is only executed on the application node because
    // eq::getConfig() does not return on other nodes.
    if (config)
    {
        /* Initialize configuration */
        if (config->init(initData))
        {
            /* Run main loop */
            while (config->isRunning())
            {
                // Pass no new OgreActors to our config (which passes it to the frame data), but make the existing ogreheads move
                config->setGameState(std::list<std::shared_ptr<OgreActor>>(), getDiffActors(frames));

                config->startFrame();
                config->finishFrame();
                frames++;
            }
            /* Exit configuration */
            config->exit();
        }
        else
        {
            std::cerr << "EqConfig initialization failed" << std::endl;
            error = true;
        }
        /* Release configuration */
        eq::releaseConfig(config);
    }
    else
    {
        std::cerr << "Cannot get configuration" << std::endl;
        error = true;
    }

    /* Exit */
    eq::exit();
    return error ? 1 : 0;
}
