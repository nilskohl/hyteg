//======================================================================================================================
//
//  This file is part of waLBerla. waLBerla is free software: you can
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of
//  the License, or (at your option) any later version.
//
//  waLBerla is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//  for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with waLBerla (see COPYING.txt). If not, see <http://www.gnu.org/licenses/>.
//
//! \file
//! \author Sebastian Eibl <sebastian.eibl@fau.de>
//
//======================================================================================================================

//======================================================================================================================
//
//  THIS FILE IS GENERATED - PLEASE CHANGE THE TEMPLATE !!!
//
//======================================================================================================================

#pragma once

#include <unresolved_particles/data/DataTypes.h>
#include <unresolved_particles/data/ParticleStorage.h>
#include <unresolved_particles/mpi/notifications/NotificationType.h>
#include <unresolved_particles/mpi/notifications/reset.h>

#include <core/mpi/Datatype.h>
#include <core/mpi/RecvBuffer.h>
#include <core/mpi/SendBuffer.h>

namespace walberla {
namespace unresolved_particles {

/**
 * Transmits force and torque information.
 */
class NumContactNotification
{
public:
   struct Parameters
   {
      id_t uid_;
      uint_t numContacts_;
   };

   inline explicit NumContactNotification( const data::Particle& p ) : p_(p) {}

   const data::Particle& p_;
};

template <>
void reset<NumContactNotification>(data::Particle& p)
{
   p.setNumContacts( 0 );
}

void reduce(data::Particle&& p, const NumContactNotification::Parameters& objparam)
{
   p.getNumContactsRef() += objparam.numContacts_;
}

void update(data::Particle&& p, const NumContactNotification::Parameters& objparam)
{
   p.setNumContacts( objparam.numContacts_ );
}

}  // namespace unresolved_particles
}  // namespace walberla

//======================================================================================================================
//
//  Send/Recv Buffer Serialization Specialization
//
//======================================================================================================================

namespace walberla {
namespace mpi {

template< typename T,    // Element type of SendBuffer
          typename G>    // Growth policy of SendBuffer
mpi::GenericSendBuffer<T,G>& operator<<( mpi::GenericSendBuffer<T,G> & buf, const unresolved_particles::NumContactNotification& obj )
{
   buf.addDebugMarker( "pn" );
   buf << obj.p_.getUid();
   buf << obj.p_.getNumContacts();
   return buf;
}

template< typename T>    // Element type  of RecvBuffer
mpi::GenericRecvBuffer<T>& operator>>( mpi::GenericRecvBuffer<T> & buf, unresolved_particles::NumContactNotification::Parameters& objparam )
{
   buf.readDebugMarker( "pn" );
   buf >> objparam.uid_;
   buf >> objparam.numContacts_;
   return buf;
}

template< >
struct BufferSizeTrait< unresolved_particles::NumContactNotification > {
   static const bool constantSize = true;
   static const uint_t size = BufferSizeTrait<id_t>::size +
                              BufferSizeTrait<uint_t>::size +
                              mpi::BUFFER_DEBUG_OVERHEAD;
};

} // mpi
} // walberla