/*
 * Copyright (c) 2017-2021 Daniel Drzisga, Dominik Thoennes, Marcus Mohr, Nils Kohl, Benjamin Mann.
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

#include "hyteg/fenics/fenics.hpp"
#include "hyteg/forms/P1LinearCombinationForm.hpp"
#include "hyteg/forms/P1RowSumForm.hpp"
#include "hyteg/forms/P2LinearCombinationForm.hpp"
#include "hyteg/forms/P2RowSumForm.hpp"
#include "hyteg/forms/form_fenics_base/P1FenicsForm.hpp"
#include "hyteg/forms/form_hyteg_generated/p1/p1_diffusion_affine_q2.hpp"
#include "hyteg/forms/form_hyteg_generated/p1/p1_mass_affine_qe.hpp"
#include "hyteg/p1functionspace/P1Operator.hpp"

namespace hyteg {

using walberla::real_t;

template < class P1Form, bool Diagonal = false, bool Lumped = false, bool InvertDiagonal = false >
class P1ConstantOperator : public P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >
{
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::P1Operator;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::storage_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::form_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::minLevel_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::maxLevel_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::vertexStencilID_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::edgeStencilID_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::faceStencilID_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::edgeStencil3DID_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::faceStencil3DID_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::cellStencilID_;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_edge_init;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_face_init;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_cell_init;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_edge;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_edge3D;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_face;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_face3D;
   using P1Operator< P1Form, Diagonal, Lumped, InvertDiagonal >::assemble_variableStencil_cell;

 public:
   P1ConstantOperator( const std::shared_ptr< PrimitiveStorage >& storage, size_t minLevel, size_t maxLevel );

   P1ConstantOperator( const std::shared_ptr< PrimitiveStorage >& storage, size_t minLevel, size_t maxLevel, const P1Form& form );

   void scale( real_t scalar );

   /*  todo
   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P1Function< idx_t >&                  src,
                  const P1Function< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      const auto storage = src.getStorage();

      for ( auto& it : this->getStorage()->getVertices() )
      {
         Vertex& vertex = *it.second;

         const DoFType vertexBC = dst.getBoundaryCondition().getBoundaryType( vertex.getMeshBoundaryFlag() );
         if ( testFlag( vertexBC, flag ) )
         {
            vertexdof::macrovertex::saveOperator(
                vertex, this->getVertexStencilID(), src.getVertexDataID(), dst.getVertexDataID(), mat, level );
         }
      }

      for ( auto& it : this->getStorage()->getEdges() )
      {
         Edge& edge = *it.second;

         const DoFType edgeBC = dst.getBoundaryCondition().getBoundaryType( edge.getMeshBoundaryFlag() );
         if ( testFlag( edgeBC, flag ) )
         {
            vertexdof::macroedge::saveOperator(
                level, edge, *storage, this->getEdgeStencilID(), src.getEdgeDataID(), dst.getEdgeDataID(), mat );
         }
      }

      if ( level >= 2 )
      {
         for ( auto& it : this->getStorage()->getFaces() )
         {
            Face& face = *it.second;

            const DoFType faceBC = dst.getBoundaryCondition().getBoundaryType( face.getMeshBoundaryFlag() );
            if ( testFlag( faceBC, flag ) )
            {
               if ( storage->hasGlobalCells() )
               {
                  vertexdof::macroface::saveOperator3D(
                      level, face, *storage, this->getFaceStencil3DID(), src.getFaceDataID(), dst.getFaceDataID(), mat );
               }
               else
               {
                  vertexdof::macroface::saveOperator(
                      level, face, this->getFaceStencilID(), src.getFaceDataID(), dst.getFaceDataID(), mat );
               }
            }
         }

         for ( auto& it : this->getStorage()->getCells() )
         {
            Cell& cell = *it.second;

            const DoFType cellBC = dst.getBoundaryCondition().getBoundaryType( cell.getMeshBoundaryFlag() );
            if ( testFlag( cellBC, flag ) )
            {
               vertexdof::macrocell::saveOperator(
                   level, cell, this->getCellStencilID(), src.getCellDataID(), dst.getCellDataID(), mat );
            }
         }
      }
   }
   */

 protected:
   /// stencil assembly: stencils are pre-assembled -> nothing to do here! ///////////

   /* Initialize assembly of variable edge stencil.
      Will be called before iterating over edge whenever the stencil is applied.
   */
   inline void assemble_stencil_edge_init( Edge& edge, const uint_t level ) const {}

   /* Assembly of edge stencil.
      Will be called before stencil is applied to a particuar edge-DoF.
   */
   inline void assemble_stencil_edge( real_t* edge_stencil, const uint_t i ) const {}

   /* Initialize assembly of face stencil.
      Will be called before iterating over face whenever the stencil is applied.
   */
   inline void assemble_stencil_face_init( Face& face, const uint_t level ) const {}

   /* Assembly of face stencil.
      Will be called before stencil is applied to a particuar face-DoF of a 2d domain.
   */
   inline void assemble_stencil_face( real_t* face_stencil, const uint_t i, const uint_t j ) const {}

   /* Assembly of face stencil.
      Will be called before stencil is applied to a particuar face-DoF of a 3D domain.
   */
   inline void assemble_stencil_face3D( vertexdof::macroface::StencilMap_T& face_stencil, const uint_t i, const uint_t j ) const
   {}

   /* Initialize assembly of cell stencil.
      Will be called before iterating over cell whenever the stencil is applied.
   */
   inline void assemble_stencil_cell_init( Cell& cell, const uint_t level ) const {}

   /* Assembly of cell stencil.
      Will be called before stencil is applied to a particuar cell-DoF.
   */
   inline void assemble_stencil_cell( vertexdof::macrocell::StencilMap_T& cell_stencil,
                                      const uint_t                        i,
                                      const uint_t                        j,
                                      const uint_t                        k ) const
   {}

   /////////////////////////////////////////////////////////////////////////////////////////////////

   inline void apply_face3D_generated( Face&                                                    face,
                                       const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcId,
                                       const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstId,
                                       const uint_t&                                            level,
                                       UpdateType                                               update ) const;

   inline void apply_face_generated( Face&                                                    face,
                                     const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcId,
                                     const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstId,
                                     const uint_t&                                            level,
                                     UpdateType                                               update ) const;

   inline void apply_cell_generated( Cell&                                                    cell,
                                     const PrimitiveDataID< FunctionMemory< real_t >, Cell >& srcId,
                                     const PrimitiveDataID< FunctionMemory< real_t >, Cell >& dstId,
                                     const uint_t&                                            level,
                                     UpdateType                                               update ) const;

   inline void smooth_sor_face3D_generated( Face&                                                    face,
                                            const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstId,
                                            const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsId,
                                            const uint_t&                                            level,
                                            real_t                                                   relax,
                                            const bool&                                              backwards = false ) const;

   inline void smooth_sor_face_generated( Face&                                                    face,
                                          const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstId,
                                          const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsId,
                                          const uint_t&                                            level,
                                          real_t                                                   relax,
                                          const bool&                                              backwards = false ) const;

   inline void smooth_sor_cell_generated( Cell&                                                    cell,
                                          const PrimitiveDataID< FunctionMemory< real_t >, Cell >& dstId,
                                          const PrimitiveDataID< FunctionMemory< real_t >, Cell >& rhsId,
                                          const uint_t&                                            level,
                                          real_t                                                   relax,
                                          const bool&                                              backwards = false ) const;

   inline bool backwards_sor_available() const { return true; }
   inline bool variableStencil() const { return false; }

   // assemble stencils for macro-edges, -faces and -cells
   void assembleStencils();
};

typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, fenics::NoAssemble > > P1ZeroOperator;

typedef P1ConstantOperator< P1FenicsForm< p1_diffusion_cell_integral_0_otherwise, p1_tet_diffusion_cell_integral_0_otherwise > >
    P1ConstantLaplaceOperator;
// typedef P1ConstantOperator< forms::p1_diffusion_affine_q2 > P1ConstantLaplaceOperator;
typedef P1ConstantOperator< P1FenicsForm< p1_diffusion_cell_integral_0_otherwise, fenics::UndefinedAssembly >, true >
    P1DiagonalLaplaceOperator;

typedef P1ConstantOperator< P1FenicsForm< p1_stokes_epsilon_cell_integral_0_otherwise > > P1ConstantEpsilonOperator_11;
typedef P1ConstantOperator< P1FenicsForm< p1_stokes_epsilon_cell_integral_1_otherwise > > P1ConstantEpsilonOperator_12;
typedef P1ConstantOperator< P1FenicsForm< p1_stokes_epsilon_cell_integral_2_otherwise > > P1ConstantEpsilonOperator_21;
typedef P1ConstantOperator< P1FenicsForm< p1_stokes_epsilon_cell_integral_3_otherwise > > P1ConstantEpsilonOperator_22;

typedef P1ConstantOperator< P1FenicsForm< p1_div_cell_integral_0_otherwise, p1_tet_div_tet_cell_integral_0_otherwise > >
    P1DivxOperator;
typedef P1ConstantOperator< P1FenicsForm< p1_div_cell_integral_1_otherwise, p1_tet_div_tet_cell_integral_1_otherwise > >
                                                                                                           P1DivyOperator;
typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, p1_tet_div_tet_cell_integral_2_otherwise > > P1DivzOperator;

typedef P1ConstantOperator< P1FenicsForm< p1_divt_cell_integral_0_otherwise, p1_tet_divt_tet_cell_integral_0_otherwise > >
    P1DivTxOperator;
typedef P1ConstantOperator< P1FenicsForm< p1_divt_cell_integral_1_otherwise, p1_tet_divt_tet_cell_integral_1_otherwise > >
                                                                                                            P1DivTyOperator;
typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, p1_tet_divt_tet_cell_integral_2_otherwise > > P1DivTzOperator;

typedef P1ConstantOperator< P1FenicsForm< p1_mass_cell_integral_0_otherwise, p1_tet_mass_cell_integral_0_otherwise > >
    P1ConstantMassOperator;
typedef P1ConstantOperator< P1FenicsForm< p1_mass_cell_integral_0_otherwise, p1_tet_mass_cell_integral_0_otherwise >,
                            false,
                            true,
                            false >
    P1LumpedMassOperator;

typedef P1ConstantOperator< P1FenicsForm< p1_mass_cell_integral_0_otherwise, p1_tet_mass_cell_integral_0_otherwise >,
                            false,
                            true,
                            true >
    P1LumpedInvMassOperator;

typedef P1ConstantOperator< P1FenicsForm< p1_pspg_cell_integral_0_otherwise, p1_tet_pspg_tet_cell_integral_0_otherwise > >
    P1PSPGOperator;
typedef P1ConstantOperator< P1FenicsForm< p1_pspg_cell_integral_0_otherwise, p1_tet_pspg_tet_cell_integral_0_otherwise >,
                            true,
                            false,
                            true >
    P1PSPGInvDiagOperator;

typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, p2_to_p1_tet_div_tet_cell_integral_0_otherwise > >
    P2ToP1DivxVertexToVertexConstantOperator;
typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, p2_to_p1_tet_div_tet_cell_integral_1_otherwise > >
    P2ToP1DivyVertexToVertexConstantOperator;
typedef P1ConstantOperator< P1FenicsForm< fenics::UndefinedAssembly, p2_to_p1_tet_div_tet_cell_integral_2_otherwise > >
    P2ToP1DivzVertexToVertexConstantOperator;

typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, p1_to_p2_tet_divt_tet_cell_integral_0_otherwise > >
    P1ToP1DivTxVertexToVertexConstantOperator;
typedef P1ConstantOperator< P1FenicsForm< fenics::NoAssemble, p1_to_p2_tet_divt_tet_cell_integral_1_otherwise > >
    P1ToP1DivTyVertexToVertexConstantOperator;
typedef P1ConstantOperator< P1FenicsForm< fenics::UndefinedAssembly, p1_to_p2_tet_divt_tet_cell_integral_2_otherwise > >
    P1ToP1DivTzVertexToVertexConstantOperator;

typedef P1ConstantOperator< P1LinearCombinationForm > P1ConstantLinearCombinationOperator;

} // namespace hyteg
