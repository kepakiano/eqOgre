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


#include "../headers/window.h"

#include "../headers/node.h"
#include "../../ogre/headers/ogreapplication.h"

#include <OgreRoot.h>
#include <boost/regex.hpp>

namespace vr
{
    Window::Window(eq::Pipe *parent)
        : eq::Window(parent), _ogreInitialised(false)
    {
    }

    bool Window::configInitGL(const eq::uint128_t &init_id)
    {
        if (!eq::Window::configInitGL(init_id))
            return false;

        // Get data
        const Config *config  = static_cast<Config *>(getConfig());
        const Node *node = static_cast<Node *>(getNode());
        const InitData &init_data = node->getInitData();

        // Create objects
#ifdef GLX
        eq::glx::WindowIF* glxWindow = dynamic_cast< eq::glx::WindowIF* >(
                                           getSystemWindow( ));
        const XID parentWnd = glxWindow ? glxWindow->getXDrawable() : 0;

        if( parentWnd )
        {
            Ogre::NameValuePairList params; // typedef std::map<std::string,std::string>

            Display* const display = glxWindow->getXDisplay();
            XSync(display, false);

            const char* displayString = DisplayString( display );
            const boost::regex regex( ":([0-9]+)\\." );
            boost::cmatch match;
            unsigned displayNum = 0;
            if( boost::regex_match( displayString, match, regex ))
                displayNum = std::atoi( match[1].first );

            XWindowAttributes wa;
            XGetWindowAttributes( display, parentWnd, &wa );
            Screen* screen = wa.screen;
            Visual* visual = wa.visual;

            const int screenNumber = XScreenNumberOfScreen(screen);
            XVisualInfo info;
            lunchbox::setZero( &info, sizeof( XVisualInfo ));

            info.visual = visual;
            info.visualid = XVisualIDFromVisual(visual);
            info.screen = screenNumber;
            info.depth = 32;

            params["externalWindowHandle"] =
                Ogre::StringConverter::toString( displayNum ) + ":" +
                Ogre::StringConverter::toString( unsigned(screenNumber)) + ":" +
                Ogre::StringConverter::toString( unsigned( parentWnd )) + ":" +
                Ogre::StringConverter::toString( size_t( &info ));

            params["externalGLControl"] = Ogre::String("True");

            const eq::PixelViewport& pvp  = getPixelViewport();

            // create window by size of pvp.
            Pipe *pipe = static_cast<Pipe *>(getPipe());
            Ogre::Root *root = pipe->_ogre->getRoot();
            mWindow = root->createRenderWindow( getName(), pvp.w, pvp.h, false,
                                                &params );
            mWindow->setActive(true);
            mWindow->setDeactivateOnFocusChange(false);

            return true;
        }
        else
#endif
            return false;
    }

    bool Window::configExitGL()
    {
        return eq::Window::configExitGL();
    }

    void Window::setViewport(float left, float top, float width, float height)
        {
            if (mWindow->getNumViewports() <= 0)
                return;
            if (_vp)
                _vp->setDimensions(  Ogre::Real(left),
                                Ogre::Real(top),
                                Ogre::Real(width),
                                Ogre::Real(height) );
        }

    void Window::addViewport()
    {
        Pipe *pipe = static_cast<Pipe *>(getPipe());
        Ogre::Camera *cam = pipe->_ogre->getCamera();
        _vp = mWindow->addViewport(cam);
        _vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
        cam->setAspectRatio(
               Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));

    }

    void Window::frameStart( const eq::uint128_t& frameID, const uint32_t frameNumber )
    {
        if (!_ogreInitialised){
            addViewport();
            _ogreInitialised = true;
        }
        eq::Window::frameStart( frameID, frameNumber );
    }

    void Window::frameFinish( const eq::uint128_t& frameID, const uint32_t frameNumber ){
        eq::Window::frameFinish( frameID, frameNumber );

    }

    void Window::render()
    {
        Pipe *pipe = static_cast<Pipe *>(getPipe());
        Ogre::Root *root = pipe->_ogre->getRoot();
        root->_fireFrameStarted();
        root->_fireFrameRenderingQueued();
        mWindow->update(false);
        root->_fireFrameEnded();
    }
}
