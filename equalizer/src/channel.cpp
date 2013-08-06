/*
* Copyright (C) 2013
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


#include "../headers/channel.h"

#include <iostream>

#include "../headers/pipe.h"
#include "../headers/window.h"
#include "../headers/node.h"
#include "../headers/framedata.h"
#include "../headers/initdata.h"

#include "../../ogre/headers/ogreapplication.h"

#include <GL/glut.h>


Ogre::Matrix4 toOgreMatrix(eq::Matrix4f eqMat){
    Ogre::Matrix4 ogreMat;
    for(size_t x = 0; x < 4; x++)
        for(size_t y = 0; y < 4; y++)
            ogreMat[x][y] = eqMat[x][y];
    return ogreMat;
}

namespace vr {
    Channel::Channel(eq::Window *parent)
    : eq::Channel(parent)
    {
    }

    bool Channel::configInit(const eq::uint128_t &init_id)
    {
        if (!eq::Channel::configInit(init_id))
            return false;
        return true;
    }

    void Channel::frameDraw(const eq::uint128_t &frame_id)
    {
        // Setup OpenGL state (view frustum etc.)
        eq::Channel::frameDraw(frame_id);

        // Get data
        const Config *config = static_cast<Config *>(getConfig());
        const Node *node = static_cast<Node *>(getNode());
        const InitData &init_data = node->getInitData();
        const Pipe *pipe = static_cast<Pipe *>(getPipe());
        const FrameData &frame_data = pipe->getFrameData();
        Window *window = static_cast<Window *>(getWindow());        

        Ogre::Camera *cam = pipe->_ogre->getCamera();

        // Set the projection matrix
        const eq::Frustumf & frustum = getFrustum();

        cam->setCustomProjectionMatrix(true, toOgreMatrix(frustum.compute_matrix()));

        // Get current camera properties
        const Ogre::Vector3 eye( frame_data.data.camera_pos[0],
                                 frame_data.data.camera_pos[1],
                                 frame_data.data.camera_pos[2] );
        const Ogre::Vector3 look_at( frame_data.data.camera_look_at[0],
                                  frame_data.data.camera_look_at[1],
                                  frame_data.data.camera_look_at[2]);
        const Ogre::Vector3 up( frame_data.data.camera_up[0],
                                frame_data.data.camera_up[1],
                                frame_data.data.camera_up[2]);

        // Calculate the view matrix from the camera properties
        Ogre::Matrix4 ogreViewMatrix = calcViewMatrix(eye, look_at, up);
        const eq::Matrix4f eqViewMatrix = getHeadTransform();
        // Adjust it according to equalizer's view matrix
        ogreViewMatrix = toOgreMatrix(eqViewMatrix) * ogreViewMatrix;
        cam->setCustomViewMatrix(true, ogreViewMatrix);
        cam->setNearClipDistance(frustum.near_plane());
        cam->setFarClipDistance(frustum.far_plane());

        // Set the viewport
        eq::PixelViewport winPvp = window->getPixelViewport();
        eq::PixelViewport pvp	 = getPixelViewport();
        window->setViewport((float)pvp.x/(float)winPvp.w,
                          1.0f - (float)(pvp.h + pvp.y)/(float)winPvp.h,
                          (float)pvp.w/(float)winPvp.w,
                          (float)pvp.h/(float)winPvp.h);

        // Render
        window->render();
    }

    Ogre::Matrix4 Channel::calcViewMatrix( Ogre::Vector3 eye, Ogre::Vector3 target, Ogre::Vector3 up ) const
    {
        Ogre::Vector3 zaxis = -(target - eye).normalisedCopy();    // The "look-at" vector.
        Ogre::Vector3 xaxis = (up.crossProduct(zaxis)).normalisedCopy();// The "right" vector.
        Ogre::Vector3 yaxis = zaxis.crossProduct(xaxis);     // The "up" vector.

        // Create a 4x4 orientation matrix from the right, up, and at vectors
        Ogre::Matrix4 orientation = {
            xaxis.x, xaxis.y, xaxis.z, 0,
            yaxis.x, yaxis.y, yaxis.z, 0,
            zaxis.x, zaxis.y, zaxis.z, 0,
              0,       0,       0,     1
        };
        return orientation;
    }


}
