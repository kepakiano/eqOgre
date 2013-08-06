#ifndef EQSERIALIZATION_H
#define EQSERIALIZATION_H

#include "serializablediffactor.h"
#include "serializableogreactor.h"
#include <eq/eq.h>


/*
 * We have to override these templates, otherwise equalizer would use the wrong
 * methode for serializing our custom classes.
 */
namespace co{
    template<> DataOStream& DataOStream::operator << ( const std::vector<SerializableOgreActor > & value );
    template<> DataIStream& DataIStream::operator >> ( std::vector< SerializableOgreActor  >& value );
    template<> DataOStream& DataOStream::operator << ( const std::vector<SerializableDiffActor> & value );
    template<> DataIStream& DataIStream::operator >> ( std::vector< SerializableDiffActor  >& value );
}
#endif // EQSERIALIZATION_H
