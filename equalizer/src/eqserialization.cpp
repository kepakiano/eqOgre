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


#include "../headers/eqserialization.h"

namespace co{
    template<> DataOStream&
    DataOStream::operator << ( const std::vector<SerializableOgreActor> & value )
    {
       const uint64_t nElems = value.size();
       (*this) << nElems;
       for( uint64_t i = 0; i < nElems; ++i ){
           value[i].writeToStream(*this);
       }
       return *this;
    }
    template<> DataIStream&
    DataIStream::operator >> ( std::vector< SerializableOgreActor> & value )
    {
        uint64_t nElems = 0;
        read( &nElems, sizeof( nElems ));
        value.resize( nElems );
        for( uint64_t i = 0; i < nElems; i++ ){
            value[i].loadFromStream(*this);
        }

        return *this;
    }

    template<> DataOStream&
    DataOStream::operator << ( const std::vector<SerializableDiffActor> & value )
    {
       const uint64_t nElems = value.size();
       (*this) << nElems;
       for( uint64_t i = 0; i < nElems; ++i ){
           value[i].writeToStream(*this);
       }
       return *this;
    }
    template<> DataIStream&
    DataIStream::operator >> ( std::vector< SerializableDiffActor> & value )
    {
        uint64_t nElems = 0;
        read( &nElems, sizeof( nElems ));
        value.resize( nElems );
        for( uint64_t i = 0; i < nElems; i++ ){
            value[i].loadFromStream(*this);
        }

        return *this;
    }
}
