/*
* Copyright (c) 2017-2022 Nils Kohl.
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

#include "hyteg/dgfunctionspace/DGVectorLaplaceForm.hpp"
#include "hyteg/dgfunctionspace/DGVectorMassForm.hpp"
#include "hyteg/egfunctionspace/EGDivForm.hpp"
#include "hyteg/egfunctionspace/EGDivtForm.hpp"

#include "hyteg/dgfunctionspace/DGDivForm.hpp"
#include "hyteg/egfunctionspace/EGFunction.hpp"
#include "hyteg/mixedoperators/P0ScalarToP1VectorOperator.hpp"
#include "hyteg/mixedoperators/P1VectorToP0ScalarOperator.hpp"
#include "hyteg/operators/Operator.hpp"
#include "hyteg/operators/ScalarToVectorOperator.hpp"
#include "hyteg/operators/VectorLaplaceOperator.hpp"
#include "hyteg/operators/VectorMassOperator.hpp"
#include "hyteg/operators/VectorToScalarOperator.hpp"
#include "hyteg/p0functionspace/P0Operator.hpp"
#include "hyteg/p1functionspace/P1ConstantOperator.hpp"
#include "hyteg/p1functionspace/P1EpsilonOperator.hpp"
namespace hyteg {
namespace dg {
namespace eg {

class P0ToEGDivTOperator final : public Operator< P0Function< real_t >, EGFunction< real_t > >
{
 public:
   P0ToEGDivTOperator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< P0Function< real_t >, EGFunction< real_t > >( storage, minLevel, maxLevel )

   , p0_to_p1x( storage, minLevel, maxLevel )
   , p0_to_p1y( storage, minLevel, maxLevel )
   , p0_to_p1z( storage, minLevel, maxLevel )
   // ,   p0_to_p1( storage, minLevel, maxLevel )
    , p0_to_edg( storage, minLevel, maxLevel )
   {}

   void apply( const P0Function< real_t >& src,
               const EGFunction< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      //p0_to_p1.apply( src, *dst.getConformingPart(), level, flag, updateType );

      p0_to_p1x.apply( src, dst.getConformingPart()->component( 0 ), level, flag, updateType );
      p0_to_p1y.apply( src, dst.getConformingPart()->component( 1 ), level, flag, updateType );
      if ( src.getDimension() == 3 )
      {
         p0_to_p1z.apply( src, dst.getConformingPart()->component( 2 ), level, flag, updateType );
      }

      p0_to_edg.apply( src, *dst.getDiscontinuousPart(), level, flag, updateType );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P0Function< idx_t >&                  src,
                  const EGFunction< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      communication::syncVectorFunctionBetweenPrimitives( *dst.getConformingPart(), level );
      dst.getDiscontinuousPart()->communicate( level );
      src.communicate( level );

      p0_to_p1x.toMatrix( mat, src, dst.getConformingPart()->component( 0 ), level, flag );
      p0_to_p1y.toMatrix( mat, src, dst.getConformingPart()->component( 1 ), level, flag );
      if ( src.getDimension() == 3 )
      {
         p0_to_p1z.toMatrix( mat, src, dst.getConformingPart()->component( 2 ), level, flag );
      }

     // p0_to_p1.toMatrix( mat, src, *dst.getConformingPart(), level, flag );
      p0_to_edg.toMatrix( mat, src, *dst.getDiscontinuousPart(), level, flag );
   }

 private:

   P0ToP1Operator< EGDivtFormP1P0_0 > p0_to_p1x;
   P0ToP1Operator< EGDivtFormP1P0_1 > p0_to_p1y;
   P0ToP1Operator< EGDivtFormP1P0_2 > p0_to_p1z;

  // P0ToP1ConstantDivTOperator p0_to_p1;
    P0Operator< EGDivtFormEP0 >        p0_to_edg;
};

class EGToP0DivOperator final : public Operator< EGFunction< real_t >, P0Function< real_t > >
{
 public:
   EGToP0DivOperator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< EGFunction< real_t >, P0Function< real_t > >( storage, minLevel, maxLevel )
   , p1x_to_p0( storage, minLevel, maxLevel )
   , p1y_to_p0( storage, minLevel, maxLevel )
   , p1z_to_p0( storage, minLevel, maxLevel )

    // ,  p1_to_p0( storage, minLevel, maxLevel )
    , edg_to_p0( storage, minLevel, maxLevel )
   {}

   void apply( const EGFunction< real_t >& src,
               const P0Function< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {

      communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
      dst.communicate( level );
      src.getDiscontinuousPart()->communicate( level );


      p1x_to_p0.apply( src.getConformingPart()->component( 0 ), dst, level, flag, updateType );
      p1y_to_p0.apply( src.getConformingPart()->component( 1 ), dst, level, flag, Add );
      if ( src.getDimension() == 3 )
      {
         p1z_to_p0.apply( src.getConformingPart()->component( 2 ), dst, level, flag, Add );
      }

     // p1_to_p0.apply( *src.getConformingPart(), dst, level, flag, updateType );

      edg_to_p0.apply( *src.getDiscontinuousPart(), dst, level, flag, Add );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const EGFunction< idx_t >&                  src,
                  const P0Function< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
      dst.communicate( level );
      src.getDiscontinuousPart()->communicate( level );


      p1x_to_p0.toMatrix( mat, src.getConformingPart()->component( 0 ), dst, level, flag );
      p1y_to_p0.toMatrix( mat, src.getConformingPart()->component( 1 ), dst, level, flag );
      if ( src.getDimension() == 3 )
      {
         p1z_to_p0.toMatrix( mat, src.getConformingPart()->component( 2 ), dst, level, flag );
      }
  //    p1_to_p0.toMatrix( mat, *src.getConformingPart(), dst, level, flag );
      edg_to_p0.toMatrix( mat, *src.getDiscontinuousPart(), dst, level, flag );
   }

 private:

   P1ToP0Operator< EGDivFormP0P1_0 > p1x_to_p0;
   P1ToP0Operator< EGDivFormP0P1_1 > p1y_to_p0;
   P1ToP0Operator< EGDivFormP0P1_2 > p1z_to_p0;
   //P1ToP0ConstantDivOperator p1_to_p0;
   P0Operator< EGDivFormP0E >        edg_to_p0;
};

class EGMassOperator final : public Operator< EGFunction< real_t >, EGFunction< real_t > >
{
 public:
   EGMassOperator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< EGFunction< real_t >, EGFunction< real_t > >( storage, minLevel, maxLevel )
   , cg_to_cg_coupling_( storage, minLevel, maxLevel )
   , eg_to_cg_coupling_( storage, minLevel, maxLevel )
   , cg_to_eg_coupling_( storage, minLevel, maxLevel )
   , eg_to_eg_coupling_( storage, minLevel, maxLevel, std::make_shared< dg::eg::EGVectorMassFormEE >() )
   {}

   void apply( const EGFunction< real_t >& src,
               const EGFunction< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      eg_to_cg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag, updateType );
      cg_to_cg_coupling_.apply( *src.getConformingPart(), *dst.getConformingPart(), level, flag, Add );

      cg_to_eg_coupling_.apply( *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag, updateType );
      eg_to_eg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag, Add );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const EGFunction< idx_t >&                  src,
                  const EGFunction< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
      communication::syncVectorFunctionBetweenPrimitives( *dst.getConformingPart(), level );
      src.getDiscontinuousPart()->communicate( level );
      dst.getDiscontinuousPart()->communicate( level );

      cg_to_cg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getConformingPart(), level, flag );
      eg_to_cg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag );
      cg_to_eg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag );
      eg_to_eg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag );
   }

 private:
   P1ConstantVectorMassOperator                  cg_to_cg_coupling_;
   EGMassP1toP0Coupling                          cg_to_eg_coupling_;
   EGMassP0toP1Coupling                          eg_to_cg_coupling_;
   P0Operator< EGVectorMassFormEE >              eg_to_eg_coupling_;
};

class EGSIPGLaplaceOperator final : public Operator< EGFunction< real_t >, EGFunction< real_t > >
{
 public:
   EGSIPGLaplaceOperator(const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< EGFunction< real_t >, EGFunction< real_t > >( storage, minLevel, maxLevel )
   , cg_to_cg_coupling_( storage, minLevel, maxLevel )
   , eg_to_cg_coupling_( storage, minLevel, maxLevel )
   , cg_to_eg_coupling_( storage, minLevel, maxLevel )
   , eg_to_eg_coupling_( storage, minLevel, maxLevel, std::make_shared< dg::eg::EGVectorLaplaceFormEE >() )
   {}

   void apply( const EGFunction< real_t >& src,
               const EGFunction< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      eg_to_cg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag, updateType );
      cg_to_cg_coupling_.apply( *src.getConformingPart(), *dst.getConformingPart(), level, flag, Add );

      cg_to_eg_coupling_.apply( *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag, updateType );
      eg_to_eg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag, Add );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const EGFunction< idx_t >&                  src,
                  const EGFunction< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
      communication::syncVectorFunctionBetweenPrimitives( *dst.getConformingPart(), level );
      src.getDiscontinuousPart()->communicate( level );
      dst.getDiscontinuousPart()->communicate( level );

      cg_to_cg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getConformingPart(), level, flag );
      eg_to_cg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag );
      cg_to_eg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag );
      eg_to_eg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag );
   }

 private:
   P1ConstantVectorLaplaceOperator cg_to_cg_coupling_;

   //  P1ElementwiseVectorLaplaceOperator     cg_to_cg_coupling_;
   EGVectorLaplaceP1ToP0Coupling       cg_to_eg_coupling_;
   EGVectorLaplaceP0ToP1Coupling       eg_to_cg_coupling_;
   P0Operator< EGVectorLaplaceFormEE > eg_to_eg_coupling_;
};

class EGConstantEpsilonOperator final : public Operator< EGFunction< real_t >, EGFunction< real_t > >
{
 public:
   EGConstantEpsilonOperator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< EGFunction< real_t >, EGFunction< real_t > >( storage, minLevel, maxLevel )
   , cg_to_cg_coupling_( storage, minLevel, maxLevel )
   , eg_to_cg_coupling_( storage, minLevel, maxLevel )
   , cg_to_eg_coupling_( storage, minLevel, maxLevel )
   , eg_to_eg_coupling_( storage, minLevel, maxLevel, std::make_shared< dg::eg::EGConstEpsilonFormEE >() )
   {}

   void apply( const EGFunction< real_t >& src,
               const EGFunction< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      eg_to_cg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag, updateType );
      cg_to_cg_coupling_.apply( *src.getConformingPart(), *dst.getConformingPart(), level, flag, Add );

      cg_to_eg_coupling_.apply( *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag, updateType );
      eg_to_eg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag, Add );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const EGFunction< idx_t >&                  src,
                  const EGFunction< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
      communication::syncVectorFunctionBetweenPrimitives( *dst.getConformingPart(), level );
      src.getDiscontinuousPart()->communicate( level );
      dst.getDiscontinuousPart()->communicate( level );

      cg_to_cg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getConformingPart(), level, flag );
      eg_to_cg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag );
      cg_to_eg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag );
      eg_to_eg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag );
   }

 private:
   P1ConstantEpsilonOperator          cg_to_cg_coupling_;
   EGConstantEpsilonP1ToP0Coupling    cg_to_eg_coupling_;
   EGConstantEpsilonP0ToP1Coupling    eg_to_cg_coupling_;
   P0Operator< EGConstEpsilonFormEE > eg_to_eg_coupling_;
};

class EGEpsilonOperator final : public Operator< EGFunction< real_t >, EGFunction< real_t > >
{
 public:
   EGEpsilonOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                      uint_t                                     minLevel,
                      uint_t                                     maxLevel,
                      std::function< real_t( const Point3D& ) >  viscosity )
   : Operator< EGFunction< real_t >, EGFunction< real_t > >( storage, minLevel, maxLevel )
   , cg_to_cg_coupling_( storage, minLevel, maxLevel, viscosity )
   , eg_to_cg_coupling_( storage,
                         minLevel,
                         maxLevel,
                         { std::make_shared< dg::eg::EGEpsilonFormP1E_0 >( viscosity ),
                           std::make_shared< dg::eg::EGEpsilonFormP1E_1 >( viscosity ),
                           std::make_shared< dg::DGFormAbort >() } )
   , cg_to_eg_coupling_( storage,
                         minLevel,
                         maxLevel,
                         { std::make_shared< dg::eg::EGEpsilonFormEP1_0 >( viscosity ),
                           std::make_shared< dg::eg::EGEpsilonFormEP1_1 >( viscosity ),
                           std::make_shared< dg::DGFormAbort >() } )
   , eg_to_eg_coupling_( storage, minLevel, maxLevel, std::make_shared< dg::eg::EGEpsilonFormEE >( viscosity ) )
   {}

   void apply( const EGFunction< real_t >& src,
               const EGFunction< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      eg_to_cg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag, updateType );
      cg_to_cg_coupling_.apply( *src.getConformingPart(), *dst.getConformingPart(), level, flag, Add );

      cg_to_eg_coupling_.apply( *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag, updateType );
      eg_to_eg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag, Add );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const EGFunction< idx_t >&                  src,
                  const EGFunction< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
      communication::syncVectorFunctionBetweenPrimitives( *dst.getConformingPart(), level );
      src.getDiscontinuousPart()->communicate( level );
      dst.getDiscontinuousPart()->communicate( level );

      cg_to_cg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getConformingPart(), level, flag );
      eg_to_cg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag );
      cg_to_eg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag );
      eg_to_eg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag );
   }

 private:
   P1ElementwiseAffineEpsilonOperator cg_to_cg_coupling_;
   EGEpsilonP1ToP0Coupling            cg_to_eg_coupling_;
   EGEpsilonP0ToP1Coupling            eg_to_cg_coupling_;
   P0Operator< EGEpsilonFormEE >      eg_to_eg_coupling_;
};

class EGNIPGLaplaceOperator final : public Operator< EGFunction< real_t >, EGFunction< real_t > >
    {
    public:
    EGNIPGLaplaceOperator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
                : Operator< EGFunction< real_t >, EGFunction< real_t > >( storage, minLevel, maxLevel )
                , cg_to_cg_coupling_( storage, minLevel, maxLevel )
                , eg_to_cg_coupling_( storage, minLevel, maxLevel )
                , cg_to_eg_coupling_( storage, minLevel, maxLevel )
                , eg_to_eg_coupling_( storage, minLevel, maxLevel, std::make_shared< dg::eg::EGNIPGVectorLaplaceFormEE >() )
        {}

        void apply( const EGFunction< real_t >& src,
                    const EGFunction< real_t >& dst,
                    size_t                      level,
                    DoFType                     flag,
                    UpdateType                  updateType ) const override
        {
            eg_to_cg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag, updateType );
            cg_to_cg_coupling_.apply( *src.getConformingPart(), *dst.getConformingPart(), level, flag, Add );

            cg_to_eg_coupling_.apply( *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag, updateType );
            eg_to_eg_coupling_.apply( *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag, Add );
        }

        void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                       const EGFunction< idx_t >&                  src,
                       const EGFunction< idx_t >&                  dst,
                       size_t                                      level,
                       DoFType                                     flag ) const override
        {
            communication::syncVectorFunctionBetweenPrimitives( *src.getConformingPart(), level );
            communication::syncVectorFunctionBetweenPrimitives( *dst.getConformingPart(), level );
            src.getDiscontinuousPart()->communicate( level );
            dst.getDiscontinuousPart()->communicate( level );

            cg_to_cg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getConformingPart(), level, flag );
            eg_to_cg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getConformingPart(), level, flag );
            cg_to_eg_coupling_.toMatrix( mat, *src.getConformingPart(), *dst.getDiscontinuousPart(), level, flag );
            eg_to_eg_coupling_.toMatrix( mat, *src.getDiscontinuousPart(), *dst.getDiscontinuousPart(), level, flag );
        }

    private:
        P1ConstantVectorLaplaceOperator cg_to_cg_coupling_;

        //  P1ElementwiseVectorLaplaceOperator     cg_to_cg_coupling_;
        EGNIPGVectorLaplaceP1ToP0Coupling       cg_to_eg_coupling_;
        EGNIPGVectorLaplaceP0ToP1Coupling       eg_to_cg_coupling_;
        P0Operator< EGNIPGVectorLaplaceFormEE > eg_to_eg_coupling_;
    };

} // namespace eg
} // namespace dg
} // namespace hyteg
