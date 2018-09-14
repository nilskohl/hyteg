
#pragma once

#include "tinyhhg_core/p1functionspace/P1Function.hpp"

namespace hhg {

class P1toP1LinearRestriction
{
 public:
   inline void operator()( const P1Function< real_t >& function, const uint_t& sourceLevel, const DoFType& flag ) const
   {
     if ( function.isDummy() )
       return;

     if ( function.getStorage()->hasGlobalCells() )
     {
       restrict3D( function, sourceLevel, flag );
     }
     else
     {
       restrict2D( function, sourceLevel, flag );
     }
   }

 private:

   void restrict2D( const P1Function< real_t >& function, const uint_t& sourceLevel, const DoFType& flag ) const;

   void restrict3D( const P1Function< real_t >& function, const uint_t& sourceLevel, const DoFType& flag ) const;

   void restrictMacroVertex( const real_t* src, real_t* dst, const uint_t& sourceLevel, const uint_t& numNeighborEdges ) const;

   void restrictMacroEdge( const real_t* src, real_t* dst, const uint_t& sourceLevel, const uint_t& numNeighborFaces ) const;

   void restrictMacroFace( const real_t* src, real_t* dst, const uint_t& sourceLevel, const uint_t& numNeighborCells ) const;
};

} // namespace hhg