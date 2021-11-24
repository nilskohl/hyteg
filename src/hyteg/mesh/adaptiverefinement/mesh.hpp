/*
 * Copyright (c) 2021 Benjamin Mann
 *
 * This file is part of HyTeG
 * (see https://i10git.cs.fau.de/hyteg/hyteg).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <set>

#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"

#include "simplex.hpp"

namespace hyteg {
namespace adaptiveRefinement {

// adaptively refinable mesh for K-dimensional domains
template < class K_Simplex >
class K_Mesh
{
 public:
   // Mesh( const std::vector< Point3D >& vertices, const std::set< std::shared_ptr< K_Simplex > >& elements )
   // : _vertices( vertices )
   // , _T( elements )
   // {}

   /* construct adaptable mesh from MeshInfo */
   K_Mesh( const MeshInfo& meshInfo );

   /* apply red-green refinement to this mesh
      @param elements_to_refine  subset of elements eligible for red refinement
   */
   void refineRG( const std::set< std::shared_ptr< K_Simplex > >& elements_to_refine );

   const std::vector< Point3D >& vertices() const { return _vertices; }

   const std::set< std::shared_ptr< K_Simplex > >& elements() const { return _T; }

   // get minimum and maximum angle of the elements in T
   std::pair< real_t, real_t > min_max_angle() const;

   // compute total volume of the triangulated domain
   real_t volume() const;

   // get SetupPrimitiveStorage corresponding to current refinement
   inline SetupPrimitiveStorage& get_setupStorage() { return _setupStorage; };

 private:
   /* remove green edges from _T and replace the corresponding faces in R with their parents
   */
   void remove_green_edges( std::set< std::shared_ptr< K_Simplex > >& R );

   /* find all elements in U which require a red refinement step
      @param U set of unprocessed elements
      @return set R of elements requiring red refinement
   */
   std::set< std::shared_ptr< K_Simplex > > find_elements_for_red_refinement( const std::set< std::shared_ptr< K_Simplex > >& U );

   /*
      apply red refinement to all elements in R and remove them from U
      @param R set of elements marked for refinement
      @param U set of elements which have not been subject to refinement yet
      @return R_refined
   */
   std::set< std::shared_ptr< K_Simplex > > refine_red( const std::set< std::shared_ptr< K_Simplex > >& R,
                                                        std::set< std::shared_ptr< K_Simplex > >&       U );

   /* apply green refinement to all elements in U which
      have a new vertex on one of their edges,
      remove these elements from U and
      add the new elements to _T
      @param U set of elements which have not been subject to refinement yet
      @return U_refined = set newly refined elements
   */
   std::set< std::shared_ptr< K_Simplex > > refine_green( std::set< std::shared_ptr< K_Simplex > >& U );

   /* apply red refinement to element
      @return sub-elements
   */
   std::set< std::shared_ptr< K_Simplex > > refine_element_red( std::shared_ptr< K_Simplex > element );

   /* construct SetupPrimitiveStorage from current refinement */
   void update_setupStorage();

   /* initialize _T for the base mesh (called by constructor) */
   void init_elements( const std::map< Idx< 3 >, std::shared_ptr< Simplex2 > >& faces,
                       const std::set< std::shared_ptr< Simplex3 > >&           cells );

   std::vector< Point3D >                   _vertices;
   std::set< std::shared_ptr< K_Simplex > > _T;            // set of elements of current refinement level
   SetupPrimitiveStorage                    _setupStorage; // primitive storage of current refinement level
};

using Mesh2D = K_Mesh< Simplex2 >;
using Mesh3D = K_Mesh< Simplex3 >;

} // namespace adaptiveRefinement
} // namespace hyteg
