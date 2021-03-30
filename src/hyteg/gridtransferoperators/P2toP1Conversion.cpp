/*
 * Copyright (c) 2021 Marcus Mohr.
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

#include "hyteg/gridtransferoperators/P2toP1Conversion.hpp"

#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroCell.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroEdge.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroFace.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroVertex.hpp"
#include "hyteg/p2functionspace/P2MacroCell.hpp"
#include "hyteg/p2functionspace/P2MacroEdge.hpp"
#include "hyteg/p2functionspace/P2MacroFace.hpp"

namespace hyteg {

template < typename ValueType >
void P2toP1Conversion( const P2Function< ValueType >& src,
                       const P1Function< ValueType >& dst,
                       const uint_t&                  P1Level,
                       const DoFType&                 flag )
{
   const auto        P2Level = P1Level - 1;
   auto              storage = src.getStorage();
   BoundaryCondition bc      = src.getBoundaryCondition();

   storage->getTimingTree()->start( "P2toP1Conversion" );

   for ( const auto& it : storage->getVertices() )
   {
      Vertex& vertex = *it.second;

      if ( testFlag( bc.getBoundaryType( vertex.getMeshBoundaryFlag() ), flag ) )
      {
         auto P1Data = vertex.getData( dst.getVertexDataID() )->getPointer( P1Level );
         auto P2Data = vertex.getData( src.getVertexDoFFunction().getVertexDataID() )->getPointer( P2Level );
         P1Data[0]   = P2Data[0];
      }
   }

   for ( const auto& it : storage->getEdges() )
   {
      Edge& edge = *it.second;

      if ( testFlag( bc.getBoundaryType( edge.getMeshBoundaryFlag() ), flag ) )
      {
         auto P1Data   = edge.getData( dst.getEdgeDataID() )->getPointer( P1Level );
         auto P2Data_v = edge.getData( src.getVertexDoFFunction().getEdgeDataID() )->getPointer( P2Level );
         auto P2Data_e = edge.getData( src.getEdgeDoFFunction().getEdgeDataID() )->getPointer( P2Level );

         for ( auto itIdx : vertexdof::macroedge::Iterator( P2Level ) )
         {
            P1Data[vertexdof::macroedge::index( P1Level, itIdx.x() * 2 )] =
                P2Data_v[vertexdof::macroedge::index( P2Level, itIdx.x() )];
         }
         for ( auto itIdx : hyteg::edgedof::macroedge::Iterator( P2Level ) )
         {
            P1Data[vertexdof::macroedge::index( P1Level, itIdx.x() * 2 + 1 )] =
                P2Data_e[hyteg::edgedof::macroedge::index( P2Level, itIdx.x() )];
         }
      }
   }

   for ( const auto& it : storage->getFaces() )
   {
      Face& face = *it.second;

      if ( testFlag( bc.getBoundaryType( face.getMeshBoundaryFlag() ), flag ) )
      {
         auto P1Data   = face.getData( dst.getFaceDataID() )->getPointer( P1Level );
         auto P2Data_v = face.getData( src.getVertexDoFFunction().getFaceDataID() )->getPointer( P2Level );
         auto P2Data_e = face.getData( src.getEdgeDoFFunction().getFaceDataID() )->getPointer( P2Level );

         for ( auto itIdx : vertexdof::macroface::Iterator( P2Level ) )
         {
            P1Data[vertexdof::macroface::index( P1Level, itIdx.x() * 2, itIdx.y() * 2 )] =
                P2Data_v[vertexdof::macroface::index( P2Level, itIdx.x(), itIdx.y() )];
         }
         for ( auto itIdx : edgedof::macroface::Iterator( P2Level ) )
         {
            P1Data[vertexdof::macroface::index( P1Level, itIdx.x() * 2 + 1, itIdx.y() * 2 )] =
                P2Data_e[edgedof::macroface::index( P2Level, itIdx.x(), itIdx.y(), edgedof::EdgeDoFOrientation::X )];
            P1Data[vertexdof::macroface::index( P1Level, itIdx.x() * 2 + 1, itIdx.y() * 2 + 1 )] =
                P2Data_e[edgedof::macroface::index( P2Level, itIdx.x(), itIdx.y(), edgedof::EdgeDoFOrientation::XY )];
            P1Data[vertexdof::macroface::index( P1Level, itIdx.x() * 2, itIdx.y() * 2 + 1 )] =
                P2Data_e[edgedof::macroface::index( P2Level, itIdx.x(), itIdx.y(), edgedof::EdgeDoFOrientation::Y )];
         }
      }
   }

   for ( const auto& it : storage->getCells() )
   {
      Cell& cell = *it.second;

      if ( testFlag( bc.getBoundaryType( cell.getMeshBoundaryFlag() ), flag ) )
      {
         auto P1Data   = cell.getData( dst.getCellDataID() )->getPointer( P1Level );
         auto P2Data_v = cell.getData( src.getVertexDoFFunction().getCellDataID() )->getPointer( P2Level );
         auto P2Data_e = cell.getData( src.getEdgeDoFFunction().getCellDataID() )->getPointer( P2Level );

         for ( auto itIdx : vertexdof::macrocell::Iterator( P2Level ) )
         {
            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2, itIdx.y() * 2, itIdx.z() * 2 )] =
                P2Data_v[vertexdof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z() )];
         }
         for ( auto itIdx : edgedof::macrocell::Iterator( P2Level ) )
         {
            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2 + 1, itIdx.y() * 2, itIdx.z() * 2 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::X )];

            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2, itIdx.y() * 2 + 1, itIdx.z() * 2 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::Y )];

            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2, itIdx.y() * 2, itIdx.z() * 2 + 1 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::Z )];

            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2 + 1, itIdx.y() * 2 + 1, itIdx.z() * 2 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::XY )];

            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2 + 1, itIdx.y() * 2, itIdx.z() * 2 + 1 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::XZ )];

            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2, itIdx.y() * 2 + 1, itIdx.z() * 2 + 1 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::YZ )];
         }

         for ( auto itIdx : edgedof::macrocell::IteratorXYZ( P2Level ) )
         {
            P1Data[vertexdof::macrocell::index( P1Level, itIdx.x() * 2 + 1, itIdx.y() * 2 + 1, itIdx.z() * 2 + 1 )] =
                P2Data_e[edgedof::macrocell::index( P2Level, itIdx.x(), itIdx.y(), itIdx.z(), edgedof::EdgeDoFOrientation::XYZ )];
         }
      }
   }

   storage->getTimingTree()->stop( "P2toP1Conversion" );
}

template void P2toP1Conversion< real_t >( const P2Function< real_t >& src,
                                          const P1Function< real_t >& dst,
                                          const uint_t&               P1Level,
                                          const DoFType&              flag );

} // namespace hyteg
