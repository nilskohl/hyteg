#pragma once

#include "tinyhhg_core/composites/P2P1TaylorHoodFunction.hpp"
#include "tinyhhg_core/gridtransferoperators/P2toP2QuadraticRestriction.hpp"
#include "tinyhhg_core/gridtransferoperators/P1toP1LinearRestriction.hpp"
#include "tinyhhg_core/gridtransferoperators/RestrictionOperator.hpp"

namespace hhg {

class P2P1StokesToP2P1StokesRestriction : public RestrictionOperator< P2P1TaylorHoodFunction< real_t > >
{
public:

    typedef P2toP2QuadraticRestriction VelocityRestriction_T;
    typedef P1toP1LinearRestriction    PressureRestriction_T;

    void restrict ( const P2P1TaylorHoodFunction< real_t > & function, const uint_t & sourceLevel, const DoFType & flag ) override
    {
      quadraticRestrictionOperator_( function.u, sourceLevel, flag );
      quadraticRestrictionOperator_( function.v, sourceLevel, flag );
      linearRestrictionOperator_   ( function.p, sourceLevel, flag );
    }

private:

    P2toP2QuadraticRestriction quadraticRestrictionOperator_;
    P1toP1LinearRestriction    linearRestrictionOperator_;

};
}