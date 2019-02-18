
#include "tinyhhg_core/mesh/MeshInfo.hpp"

#include "core/logging/Logging.h"
#include "core/debug/CheckFunctions.h"
#include "core/debug/Debug.h"

#include <array>
#include <vector>

namespace hhg
{

  namespace meshGenSphShell
  {

    using walberla::real_t;
    using walberla::real_c;


    // Precise type of meshing approach
    typedef enum {
      SHELLMESH_ON_THE_FLY,  //!< meshing is done on-the-fly
      SHELLMESH_CLASSIC      //!< meshing by midpoint refinement
    } shellMeshType;

   
    static void elemIdx2Tuple( uint_t ntan_, uint_t nrad_, uint_t jelem, 
                               uint_t & it, uint_t & is1, uint_t & is2, uint_t & id, uint_t & ir )
    {

      uint_t idx = jelem;
      uint_t aux = 0;

      // Determine layer index ir
      aux = 6 * 10 * (ntan_-1) * (ntan_-1);
      ir = idx / aux;
      idx -= ir * aux;

      // Determine diamond index id
      aux = 6 * (ntan_-1) * (ntan_-1);
      id = idx / aux;
      idx -= id * aux;

      // Determine second spherical index is2
      aux = 6 * (ntan_-1);
      is2 = idx / aux;
      idx -= is2 * aux;

      // Determine first spherical index is1
      is1 = idx / 6;

      // What remains is the number of the tetrahedron
      // withing the local cell
      it = idx - 6 * is1;

      WALBERLA_ASSERT_LESS( it , 6     );
      WALBERLA_ASSERT_LESS( is1, ntan_ );
      WALBERLA_ASSERT_LESS( is2, ntan_ );
      WALBERLA_ASSERT_LESS( ir , nrad_ );
      WALBERLA_ASSERT_LESS( id , 10    );
      WALBERLA_UNUSED( nrad_ );
    }


    static void vertIdx2Tuple( uint_t ntan_, uint_t nrad_, uint_t jvert,
                               uint_t & is1, uint_t & is2, uint_t & id, uint_t & ir ) {

      // Treat non-poles
      if( jvert >= 2*nrad_ ) {

        uint_t aux = 0;
        uint_t idx = jvert - 2*nrad_;

        // get radial layer
        aux  = 10 * (ntan_-1) * (ntan_-1);
        ir   = idx / aux;
        idx -= ir * aux;

        // get diamond index
        aux = (ntan_-1) * (ntan_-1);
        id  = idx / aux;
        idx -= id * aux;

        // get second spherical index
        aux  = (ntan_-1);
        is2  = idx / aux;
        idx -= is2 * aux;
        is2++;

        // get first spherical index
        is1  = idx;

        WALBERLA_ASSERT_LESS( is1, ntan_-1 );
        WALBERLA_ASSERT_GREATER( is2, 0 );
        WALBERLA_ASSERT_LESS( is2, ntan_ );
      }

      // Treat north poles
      else if( jvert < nrad_ ) {
        is1 = 0;
        is2 = 0;
        id  = 0;  // by definition
        ir  = jvert;
      }

      // Treat south poles
      else {
        is1 = 0;
        is2 = 0;
        id  = 5;  // by definition
        ir  = jvert - nrad_;
      }

      WALBERLA_ASSERT_LESS( ir, nrad_ );
      WALBERLA_ASSERT_LESS( id, 10    );

    }

    // =================
    //  findVertexOnArc
    // =================
    void findVertexOnArc( double *vL, double *vR, double &xpos, double &ypos, double &zpos, uint_t nPoints, uint_t idx )
    {

      // angle between left and right vertex
      double alpha = acos( vL[0]*vR[0] + vL[1]*vR[1] + vL[2]*vR[2] );

      // weights for spherical interpolation
      double gamma = (double)idx * ( alpha / (double)(nPoints-1) );
      double beta  = alpha - gamma;
      double omg1 = sin(beta ) / sin(alpha);
      double omg2 = sin(gamma) / sin(alpha);

      // compute vertex coordinates
      xpos = omg1 * vL[0] + omg2 * vR[0];
      ypos = omg1 * vL[1] + omg2 * vR[1];
      zpos = omg1 * vL[2] + omg2 * vR[2];
    }


    static uint_t tuple2VertIdx( uint_t ntan_, uint_t nrad_, uint_t is1, uint_t is2, uint_t id, uint_t ir )
    {

      uint_t jvert = 0;

      WALBERLA_ASSERT_LESS( is1, ntan_ );
      WALBERLA_ASSERT_LESS( is2, ntan_ );
      WALBERLA_ASSERT_LESS( ir , nrad_ );
      WALBERLA_ASSERT_LESS( id , 10    );

      // Treat poles
      if( is1 == 0 && is2 == 0 ) {
        if( id < 5 ) {
          jvert = ir;
        }
        else {
          jvert = nrad_ + ir;
        }
      }

      // Treat normal vertices
      else {

        // Correct tuple in case of vertex on "upper" left edge
        if( is2 == 0 ) {
          is2 = is1;
          is1 = 0;
          id  = (id < 5 ) ? (id+4)%5 : (id+4)%5+5;
        }

        // Correct tuple in case of vertex on "lower" left edge
        else if ( is1 == ntan_-1 ) {
          is1 = (ntan_-1) - is2;
          is2 = ntan_-1;
          id  = (id < 5) ? (id+4)%5 + 5 : id%5;
        }

        // Treat standard case
        WALBERLA_ASSERT_LESS( is1, ntan_-1 );
        WALBERLA_ASSERT_LESS( is2, ntan_   );
        jvert  = ir * (ntan_-1) * (ntan_-1) * 10;
        jvert += id * (ntan_-1) * (ntan_-1);
        jvert += (is2-1) * (ntan_-1);
        jvert += is1;
        jvert += 2 * nrad_;
      }

      return jvert;
    }



    static Point3D compCoordsOnTheFly( uint_t ntan, uint_t is1, uint_t is2, uint_t id, double iNode[12][3], uint_t dNode[10][4] )
    {

      Point3D resultingCoordinates;
  
      // get coords of four vertices of diamond
      double vT[3], vL[3], vR[3], vB[3];

      vT[0] = iNode[ dNode[id][0] ][0];
      vT[1] = iNode[ dNode[id][0] ][1];
      vT[2] = iNode[ dNode[id][0] ][2];

      vL[0] = iNode[ dNode[id][1] ][0];
      vL[1] = iNode[ dNode[id][1] ][1];
      vL[2] = iNode[ dNode[id][1] ][2];

      vB[0] = iNode[ dNode[id][2] ][0];
      vB[1] = iNode[ dNode[id][2] ][1];
      vB[2] = iNode[ dNode[id][2] ][2];

      vR[0] = iNode[ dNode[id][3] ][0];
      vR[1] = iNode[ dNode[id][3] ][1];
      vR[2] = iNode[ dNode[id][3] ][2];

      // account for different meaning of is1, is2 on hemispheres
      uint_t js1 = id < 5 ? is1 : is2;
      uint_t js2 = id < 5 ? is2 : is1;

      // Case 1: it's a pole
      if( is2 == 0 ) {
        WALBERLA_ASSERT_EQUAL( is1, 0 );
        resultingCoordinates[0] = vT[0];
        resultingCoordinates[1] = vT[1];
        resultingCoordinates[2] = vT[2];
      }

      // Case 2: lower right arc (seen from pole)
      else if( js2 == ntan ) {
        findVertexOnArc( vR, vB, resultingCoordinates[0], resultingCoordinates[1], resultingCoordinates[2], ntan, js1 );
      }

      // Case 3: upper right arc (seen from pole)
      else if( js1 == 0 ) {
        findVertexOnArc( vT, vR, resultingCoordinates[0], resultingCoordinates[1], resultingCoordinates[2], ntan, js2 );
      }

      // Case 4: lower left arc (seen from pole)
      else if( js1 == ntan ) {
        WALBERLA_ABORT( "This should not have happened!" );
      }

      // Case 5: vertex on upper triangle (seen from pole)
      else if( js1 + js2 < ntan-1 ) {

        double xL[3], xR[3];
        uint_t k = js1 + js2;

        // find node on left edge
        findVertexOnArc( vT, vL, xL[0], xL[1], xL[2], ntan, k );

        // find node on right edge
        findVertexOnArc( vT, vR, xR[0], xR[1], xR[2], ntan, k );

        // find vertex on arc going left to right
        findVertexOnArc( xL, xR, resultingCoordinates[0], resultingCoordinates[1], resultingCoordinates[2], k+1, js2 );
      }

      // Case 6: vertex on arc separating the triangles
      else if( js1 + js2 == ntan-1 ) {
        findVertexOnArc( vL, vR, resultingCoordinates[0], resultingCoordinates[1], resultingCoordinates[2], ntan, js2 );
      }

      // Case 7: vertex on lower triangle (seen from pole)
      else if( js1 + js2 > ntan-1 ) {

        double xL[3], xR[3];
        uint_t k = js1 + js2 - ntan + 1;

        // find node on left edge
        findVertexOnArc( vL, vB, xL[0], xL[1], xL[2], ntan, k );

        // find node on right edge
        findVertexOnArc( vR, vB, xR[0], xR[1], xR[2], ntan, k );

        // find vertex on arc going left to right
        findVertexOnArc( xL, xR, resultingCoordinates[0], resultingCoordinates[1], resultingCoordinates[2], ntan-k, js2-k );
      }

      // Case 8: FUBAR
      else {
        WALBERLA_ABORT( "This should not have happened!" );
      }

      return resultingCoordinates;
    }



    static Point3D getVertex( uint_t idx, uint_t ntan, uint_t nrad, double iNode[12][3], uint_t dNode[10][4], std::vector< double > layers,
                              double**** nodeCoords, shellMeshType flavour )
    {
      // Find address tuple of vertex
      uint_t is1, is2, id, ir;
      vertIdx2Tuple( ntan, nrad, idx, is1, is2, id, ir );

      WALBERLA_ASSERT_LESS( ir, nrad );

      // Compute vertex coordinates
      Point3D vertex;
      switch( flavour ) {

      case SHELLMESH_ON_THE_FLY:
        vertex = compCoordsOnTheFly( ntan, is1, is2, id, iNode, dNode ) * layers[ir];
        break;

      case SHELLMESH_CLASSIC:
        {
          WALBERLA_ASSERT_NOT_NULLPTR( nodeCoords );
          double x = nodeCoords[is1][is2][id][0] * layers[ir];
          double y = nodeCoords[is1][is2][id][1] * layers[ir];
          double z = nodeCoords[is1][is2][id][2] * layers[ir];
          vertex = Point3D( { x, y, z } );
          break;
        }

      default:
        WALBERLA_ABORT( "Unreachable branch reached!" );
      }

      return vertex;
    }


    static std::vector< uint_t > getCell( uint_t ntan, uint_t nrad, uint_t idx, uint_t offset[8][3], uint_t tNode[6][4], uint_t sNode[6][4] )
    {
      // Find address tuple of element
      uint_t it, is1, is2, id, ir;
      elemIdx2Tuple( ntan, nrad, idx, it, is1, is2, id, ir );

      // Determine global indices of the eight vertices of the local cell
      uint_t vIdx[8], ks1, ks2, kr;
      for( uint_t k = 0; k < 8; k++ ) {

        // compute address tuple of vertex (Northern hemisphere)
        if( id <= 4 ) {
          ks1 = is1 + offset[k][0];
          ks2 = is2 + offset[k][1];
          kr  = ir  + offset[k][2];
        }

        // compute address tuple of vertex (Southern hemisphere)
        else {
          ks1 = is1 + offset[k][1];
          ks2 = is2 + offset[k][0];
          kr  = ir  + offset[k][2];
        }

        // convert to global index
        vIdx[k] = tuple2VertIdx( ntan, nrad, ks1, ks2, id, kr );
      }

      // Find the four vertices of the local cell that make up our element
      std::vector< uint_t > vertexIDs( 4 );
      if( id <= 4 ) {
        // Northern hemisphere
        vertexIDs[0] = vIdx[ tNode[it][0] ];
        vertexIDs[1] = vIdx[ tNode[it][1] ];
        vertexIDs[2] = vIdx[ tNode[it][2] ];
        vertexIDs[3] = vIdx[ tNode[it][3] ];
      } else {
        // Southern hemisphere
        vertexIDs[0] = vIdx[ sNode[it][0] ];
        vertexIDs[1] = vIdx[ sNode[it][1] ];
        vertexIDs[2] = vIdx[ sNode[it][2] ];
        vertexIDs[3] = vIdx[ sNode[it][3] ];
      }

      return vertexIDs;
    }


    static void setupCoordsClassic( uint_t ntan, double iNode[12][3], uint_t dNode[10][4], double***** coords ) {

      double**** nodeCoords;

      // -------------------
      //  Consistency Check
      // -------------------
      uint_t power = ntan - 1;
      uint_t lvl = 0;
      while( power > 0 ) {
        ++lvl;
        power /= 2;
      }
      --lvl;
      if( 1u << lvl != ntan - 1 ) {
        WALBERLA_ABORT( "ERROR: For SHELLMESH_CLASSIC (ntan-1) must be a power of 2, but ntan is " << ntan );
      }

      // --------------------------
      //  Allocate 4D memory array
      // --------------------------
      WALBERLA_ASSERT_NULLPTR( *coords );

      size_t memsize;

      memsize = ntan;
      nodeCoords = new double*** [memsize];

      memsize *= ntan;
      nodeCoords[0] = new double** [memsize];
 
      memsize *= 10;
      nodeCoords[0][0] = new double* [memsize];

      memsize *= 3;
      nodeCoords[0][0][0] = new double[memsize];

      // set pointers
      for( uint_t k = 1; k < ntan; ++k ) {
        nodeCoords[k] = nodeCoords[0] + k * ntan;
      }
      for( uint_t  k = 1; k < ntan * ntan; ++k ) {
        nodeCoords[0][k] = nodeCoords[0][0] + k * 10;
      }
      for( uint_t  k = 1; k < 10 * ntan * ntan; ++k ) {
        nodeCoords[0][0][k] = nodeCoords[0][0][0] + k * 3;
      }

      // ------------------------
      //  Meshing of unit sphere
      // ------------------------
      for( uint_t  id = 0; id < 10; ++id ) {

        // "left" and "right" w.r.t. dNode depend on hemisphere
        uint_t  L, R;
        if( id < 5 ) {
          L = 1;
          R = 3;
        }
        else {
          R = 1;
          L = 3;
        }

        // Insert coordinates of four nodes of this icosahedral diamond
        nodeCoords[   0  ][   0  ][id][0] = iNode[ dNode[id][0] ][0];
        nodeCoords[   0  ][   0  ][id][1] = iNode[ dNode[id][0] ][1];
        nodeCoords[   0  ][   0  ][id][2] = iNode[ dNode[id][0] ][2];
    
        nodeCoords[ntan-1][   0  ][id][0] = iNode[ dNode[id][L] ][0];
        nodeCoords[ntan-1][   0  ][id][1] = iNode[ dNode[id][L] ][1];
        nodeCoords[ntan-1][   0  ][id][2] = iNode[ dNode[id][L] ][2];

        nodeCoords[ntan-1][ntan-1][id][0] = iNode[ dNode[id][2] ][0];
        nodeCoords[ntan-1][ntan-1][id][1] = iNode[ dNode[id][2] ][1];
        nodeCoords[ntan-1][ntan-1][id][2] = iNode[ dNode[id][2] ][2];

        nodeCoords[   0  ][ntan-1][id][0] = iNode[ dNode[id][R] ][0];
        nodeCoords[   0  ][ntan-1][id][1] = iNode[ dNode[id][R] ][1];
        nodeCoords[   0  ][ntan-1][id][2] = iNode[ dNode[id][R] ][2];

        // Loop over refinement levels
        uint_t  m, l, l2, j1, j2, i1, i2;
        double x, y, z, scl;
        for( m = 1; m < ntan-1; m *= 2 ) {

          l  = (ntan-1) / m;
          l2 = l / 2;

          // rows of diamond
          for( j1 = 0; j1 <= m; ++j1 ) {
            for( j2 = 0; j2 < m; ++j2 ) {

              // compute coordinates of new node
              i1 = j1 * l;
              i2 = j2 * l + l2;

              // compute new node as midpoint of arc
              x = nodeCoords[i1][i2-l2][id][0] + nodeCoords[i1][i2+l2][id][0];
              y = nodeCoords[i1][i2-l2][id][1] + nodeCoords[i1][i2+l2][id][1];
              z = nodeCoords[i1][i2-l2][id][2] + nodeCoords[i1][i2+l2][id][2];

              scl = sqrt( x*x + y*y + z*z );

              nodeCoords[i1][i2][id][0] = x / scl;
              nodeCoords[i1][i2][id][1] = y / scl;
              nodeCoords[i1][i2][id][2] = z / scl;
            }
          }

          // columns of diamond
          for( j1 = 0; j1 <= m; ++j1 ) {
            for( j2 = 0; j2 < m; ++j2 ) {

              // compute coordinates of new node
              i1 = j2 * l + l2;
              i2 = j1 * l;

              // compute new node as midpoint of arc
              x = nodeCoords[i1-l2][i2][id][0] + nodeCoords[i1+l2][i2][id][0];
              y = nodeCoords[i1-l2][i2][id][1] + nodeCoords[i1+l2][i2][id][1];
              z = nodeCoords[i1-l2][i2][id][2] + nodeCoords[i1+l2][i2][id][2];

              scl = sqrt( x*x + y*y + z*z );

              nodeCoords[i1][i2][id][0] = x / scl;
              nodeCoords[i1][i2][id][1] = y / scl;
              nodeCoords[i1][i2][id][2] = z / scl;
            }
          }

          // diagonals of diamond
          for( j1 = 0; j1 < m; ++j1 ) {
            for( j2 = 0; j2 < m; ++j2 ) {

              // compute coordinates of new node
              i1 = j1 * l + l2;
              i2 = j2 * l + l2;

              // compute new node as midpoint of arc
              x = nodeCoords[i1-l2][i2+l2][id][0] + nodeCoords[i1+l2][i2-l2][id][0];
              y = nodeCoords[i1-l2][i2+l2][id][1] + nodeCoords[i1+l2][i2-l2][id][1];
              z = nodeCoords[i1-l2][i2+l2][id][2] + nodeCoords[i1+l2][i2-l2][id][2];

              scl = sqrt( x*x + y*y + z*z );

              nodeCoords[i1][i2][id][0] = x / scl;
              nodeCoords[i1][i2][id][1] = y / scl;
              nodeCoords[i1][i2][id][2] = z / scl;
            }
          }
        }
      }

      // hand back 4D Array
      *coords = nodeCoords;

    }

  } // namespace meshGenSphShell

  MeshInfo MeshInfo::meshSphericalShell( uint_t ntan, uint_t nrad, double rmin, double rmax )
  {
    std::vector< double > layers( nrad, 0.0 );
    for ( uint_t layer = 0; layer < nrad; layer++ )
      {
        layers[layer] = rmin + ( ( rmax - rmin ) / (double)( nrad - 1 ) ) * (double)layer;
      }
    return meshSphericalShell( ntan, layers );
  }


  MeshInfo MeshInfo::meshSphericalShell( uint_t ntan, const std::vector< double > & layers )
  {
    uint_t nrad = layers.size();

    /// Flavour for generation of the spherical mesh
    ///
    /// The two possible choices for the flavour for generation of the spherical mesh
    /// are
    /// - SHELLMESH_ON_THE_FLY
    /// - SHELLMESH_CLASSIC
    /// Note: The variant SHELLMESH_CLASSIC employs midpoint refinement on the icosahedral
    /// mesh, while the SHELLMESH_ON_THE_FLY variant has a lower memory footprint, but
    /// introduces a bias in the meshing and is _not_ equivalent to midpoint refinement.
    /// The resulting meshes are also not nested!
    meshGenSphShell::shellMeshType shellmeshFlavour = meshGenSphShell::SHELLMESH_CLASSIC;
    // shellMeshType meshFlavour = meshGenSphShell::SHELLMESH_ON_THE_FLY;

    /// Coordinates of the twelve icosahedral nodes of the base grid
    double iNode[12][3];

    /// Association of the ten diamonds to the twelve icosahedral nodes
    ///
    /// For each diamond we store the indices of its vertices on the
    /// icosahedral base grid in this map. Ordering: We start with the
    /// pole and proceed in counter-clockwise fashion.
    uint_t dNode[10][4];

    /// Assign vertices of local cell to its six tetrahedrons on the northern
    /// hemisphere
    uint_t tNode[6][4];

    /// Assign vertices of local cell to its six tetrahedrons on the southern
    /// hemisphere
    uint_t sNode[6][4];

    /// Index offsets (is1, is2, ir) for computing vertex addresses
    uint_t offset[8][3];


    ////////////////
    // Setup Maps //
    ////////////////

    // Determine number of vertices
    uint_t nVerts_ = ( 10 * (ntan-1) * (ntan-1) + 2 ) * nrad;

    // Determine number of elements/tetrahedra
    uint_t nElems_ = (ntan-1) * (ntan-1) * (nrad-1) * 10 * 6;

    // -----------------------------------------
    //  Initialise the twelve icosahedral nodes
    // -----------------------------------------

    // the pentagonal nodes on each "ring" are given in anti-clockwise ordering
    double fifthpi = 0.4 * std::asin( 1.0 );
    double w       = 2.0 * std::acos( 1.0 / ( 2.0 * std::sin(fifthpi) ) );
    double cosw    = std::cos(w);
    double sinw    = std::sin(w);
    double phi     = 0.0;

    // north pole
    iNode[ 0][0] =  0.0;
    iNode[ 0][1] =  0.0;
    iNode[ 0][2] = +1.0;

    // south pole
    iNode[11][0] =  0.0;
    iNode[11][1] =  0.0;
    iNode[11][2] = -1.0;

    // upper ring
    for ( uint_t k = 1; k <= 5; k++ ) {
      phi = 2.0 * ((double)k - 0.5) * fifthpi;
      iNode[k][0] = sinw * std::cos(phi);
      iNode[k][1] = sinw * std::sin(phi);
      iNode[k][2] = cosw;
    }

    // lower ring
    for ( uint_t k = 1; k <= 5; k++ ) {
      phi = 2.0 * ((double)k - 1) * fifthpi;
      iNode[k+5][0] =  sinw * std::cos(phi);
      iNode[k+5][1] =  sinw * std::sin(phi);
      iNode[k+5][2] = -cosw;
    }

    // ----------------------------------------------
    // Setup internal index maps for mesh generation
    // ----------------------------------------------

    // Determine offsets for computing address tuples for the
    // eight vertices of a local cell (is1, is2, ir)
    offset[0][0] = 0; offset[0][1] = 0; offset[0][2] = 1;
    offset[1][0] = 1; offset[1][1] = 0; offset[1][2] = 1;
    offset[2][0] = 1; offset[2][1] = 1; offset[2][2] = 1;
    offset[3][0] = 0; offset[3][1] = 1; offset[3][2] = 1;
    offset[4][0] = 0; offset[4][1] = 0; offset[4][2] = 0;
    offset[5][0] = 1; offset[5][1] = 0; offset[5][2] = 0;
    offset[6][0] = 1; offset[6][1] = 1; offset[6][2] = 0;
    offset[7][0] = 0; offset[7][1] = 1; offset[7][2] = 0;

    // Map icosahedral node indices to diamonds (northern hemisphere)
    dNode[0][0] =  0; dNode[0][1] =  5; dNode[0][2] =  6; dNode[0][3] =  1;
    dNode[1][0] =  0; dNode[1][1] =  1; dNode[1][2] =  7; dNode[1][3] =  2;
    dNode[2][0] =  0; dNode[2][1] =  2; dNode[2][2] =  8; dNode[2][3] =  3;
    dNode[3][0] =  0; dNode[3][1] =  3; dNode[3][2] =  9; dNode[3][3] =  4;
    dNode[4][0] =  0; dNode[4][1] =  4; dNode[4][2] = 10; dNode[4][3] =  5;

    // Map icosahedral node indices to diamonds (southern hemisphere)
    dNode[5][0] = 11; dNode[5][1] =  7; dNode[5][2] =  1; dNode[5][3] =  6;
    dNode[6][0] = 11; dNode[6][1] =  8; dNode[6][2] =  2; dNode[6][3] =  7;
    dNode[7][0] = 11; dNode[7][1] =  9; dNode[7][2] =  3; dNode[7][3] =  8;
    dNode[8][0] = 11; dNode[8][1] = 10; dNode[8][2] =  4; dNode[8][3] =  9;
    dNode[9][0] = 11; dNode[9][1] =  6; dNode[9][2] =  5; dNode[9][3] = 10;

    // Mapping of northern tetrahedron to vertices of local cell
    tNode[0][0] = 0;  tNode[0][1] = 1;  tNode[0][2] = 3;  tNode[0][3] = 7;
    tNode[1][0] = 4;  tNode[1][1] = 7;  tNode[1][2] = 5;  tNode[1][3] = 0;
    tNode[2][0] = 0;  tNode[2][1] = 5;  tNode[2][2] = 1;  tNode[2][3] = 7;
    tNode[3][0] = 1;  tNode[3][1] = 2;  tNode[3][2] = 3;  tNode[3][3] = 6;
    tNode[4][0] = 5;  tNode[4][1] = 7;  tNode[4][2] = 6;  tNode[4][3] = 1;
    tNode[5][0] = 3;  tNode[5][1] = 6;  tNode[5][2] = 7;  tNode[5][3] = 1;

    // Mapping of southern tetrahedron to vertices of local cell
    sNode[0][0] = 4;  sNode[0][1] = 7;  sNode[0][2] = 5;  sNode[0][3] = 1;
    sNode[1][0] = 0;  sNode[1][1] = 1;  sNode[1][2] = 3;  sNode[1][3] = 4;
    sNode[2][0] = 4;  sNode[2][1] = 3;  sNode[2][2] = 7;  sNode[2][3] = 1;
    sNode[3][0] = 7;  sNode[3][1] = 6;  sNode[3][2] = 5;  sNode[3][3] = 2;
    sNode[4][0] = 3;  sNode[4][1] = 1;  sNode[4][2] = 2;  sNode[4][3] = 7;
    sNode[5][0] = 5;  sNode[5][1] = 2;  sNode[5][2] = 1;  sNode[5][3] = 7;

    // if required, run setup routine for meshing unit sphere
    double**** nodeCoords = nullptr;
    if( shellmeshFlavour == meshGenSphShell::SHELLMESH_CLASSIC ) {
      meshGenSphShell::setupCoordsClassic( ntan, iNode, dNode, &nodeCoords );
    }

    ////////////////////////////
    // Create MeshInfo object //
    ////////////////////////////

    MeshInfo meshInfo;
 
    for ( uint_t vertexID = 0; vertexID < nVerts_; vertexID++ )
      {
        auto vertexCoordinates = meshGenSphShell::getVertex( vertexID, ntan, nrad, iNode, dNode, layers, nodeCoords, shellmeshFlavour );
        meshInfo.vertices_[ vertexID ] = MeshInfo::Vertex( vertexID, vertexCoordinates, 0 );
      }

    for ( uint_t cellID = 0; cellID < nElems_; cellID++ )
      {
        auto vertexIDs = meshGenSphShell::getCell( ntan, nrad, cellID, offset, tNode, sNode );
        meshInfo.cells_[ vertexIDs ] = MeshInfo::Cell( vertexIDs, 0 );
      }

    for ( const auto & it : meshInfo.getCells() )
      {
        const std::vector< IDType > cellCoordinates = it.first;
        const MeshInfo::Cell        meshInfoCell    = it.second;

        WALBERLA_ASSERT_EQUAL( cellCoordinates.size(), 4, "[Mesh] Only tetrahedron cells supported." );

        meshInfo.addEdge( Edge( std::array< IDType, 2 >( {{ cellCoordinates[0], cellCoordinates[1] }} ), 0 ) );
        meshInfo.addEdge( Edge( std::array< IDType, 2 >( {{ cellCoordinates[0], cellCoordinates[2] }} ), 0 ) );
        meshInfo.addEdge( Edge( std::array< IDType, 2 >( {{ cellCoordinates[0], cellCoordinates[3] }} ), 0 ) );
        meshInfo.addEdge( Edge( std::array< IDType, 2 >( {{ cellCoordinates[1], cellCoordinates[2] }} ), 0 ) );
        meshInfo.addEdge( Edge( std::array< IDType, 2 >( {{ cellCoordinates[1], cellCoordinates[3] }} ), 0 ) );
        meshInfo.addEdge( Edge( std::array< IDType, 2 >( {{ cellCoordinates[2], cellCoordinates[3] }} ), 0 ) );

        meshInfo.addFace( Face( std::vector< IDType >( {{ cellCoordinates[0], cellCoordinates[1], cellCoordinates[2] }} ), 0 ) );
        meshInfo.addFace( Face( std::vector< IDType >( {{ cellCoordinates[0], cellCoordinates[1], cellCoordinates[3] }} ), 0 ) );
        meshInfo.addFace( Face( std::vector< IDType >( {{ cellCoordinates[0], cellCoordinates[2], cellCoordinates[3] }} ), 0 ) );
        meshInfo.addFace( Face( std::vector< IDType >( {{ cellCoordinates[1], cellCoordinates[2], cellCoordinates[3] }} ), 0 ) );
      }

    // De-allocate 4D array
    if( nodeCoords != nullptr ) {
      delete[] nodeCoords[0][0][0];
      delete[] nodeCoords[0][0];
      delete[] nodeCoords[0];
      delete[] nodeCoords;
    }

    return meshInfo;
  }

} // namespace hhg
