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


#include "../headers/ogreactor.h"

OgreActor::OgreActor()
{
}

OgreActor::OgreActor(std::string nodeName,
                     OgreType type,
                     Vec3 position,
                     Vec4 orientation,
                     std::string meshName,
                     std::string entName,
                     std::string materialName,
                     bool castShadows, Vec3 scale)
    : _nodeName(nodeName), _type(type), _position(position), _orientation(orientation),
      _meshName(meshName), _entName(entName), _materialName(materialName), _castShadows(castShadows),
      _scale(scale)
{
}

OgreActor::~OgreActor()
{

}
