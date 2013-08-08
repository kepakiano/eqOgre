#ifndef EQSERIALIZATION_H
#define EQSERIALIZATION_H

#include "serializablediffactor.h"
#include "serializableogreactor.h"
#include <eq/eq.h>


/*
 * Partial template specializations for our custom classes.
 */
namespace co
{

template<> inline
DataOStream& DataOStream::operator << ( const SerializableOgreActor& value )
{
    value.writeToStream(*this);
    return *this;
}
template<> inline
DataIStream& DataIStream::operator >> ( SerializableOgreActor& value )
{
    value.loadFromStream(*this);
    return *this;
}

template<> inline
DataOStream& DataOStream::operator << ( const SerializableDiffActor& value )
{
    value.writeToStream(*this);
    return *this;
}
template<> inline
DataIStream& DataIStream::operator >> ( SerializableDiffActor& value )
{
    value.loadFromStream(*this);
    return *this;
}

}
#endif // EQSERIALIZATION_H
