/*
 * Copyright (c) 2017-2024 Dominik Thoennes, Nils Kohl, Marcus Mohr.
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
#include "core/mpi/Environment.h"

#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/primitivestorage/PrimitiveStorage.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"

namespace hyteg {

/**
 * \page BA.01_PrimitiveStorage Tutorial BA.01 - Representing Your Problem Domain
 *
 * \dontinclude tutorials/basics-for-apps/BA.01_PrimitiveStorage.cpp
 *
 * \brief In this tutorial we will demonstrate how to set up a distributed unstructured coarse
 * mesh to represent the problem domain for a Finite Element simulation.
 *
 * \section BA01-intro Introduction
 *
 * HyTeG is build on the concept of Hierarchical Hybrid Grids. In this concept one starts with
 * a coarse (potentially unstructured) triangular or tetrahedral mesh to represent the problem
 * domain. The elements of this mesh are split into their geometric primitives (vertices, edges,
 * faces and cells). In the HyTeG terminology we refer to these as macro-primitives.
 *
 * In HyTeG the macro-primitives act as containers for storing associated data (like Finite
 * Element functions) and form the smallest entity for distributing data between MPI processes.
 *
 * Actual Finite Element discretisations of PDEs are usually not performed on the coarse base
 * mesh, but on a significantly finer mesh. The latter is generated by structured refinement
 * of the macro-primitives. The geometric entities of finer meshes are then refered to as
 * micro-vertices and so on.
 * For full details please take a look at the corresponding papers in our
 * <a href="https://i10git.cs.fau.de/hyteg/hyteg#publications">publication list</a>.
 *
 * The central class for representing the coarse mesh and its primitives it the PrimitiveStorage.
 * A PrimitiveStorage contains references to all process-local Primitive instances and therefore
 * implements a totally distributed data structure to represent the simulation domain.
 *
 * It stores information about the neighborhood of the local primitives. Additionally it
 * is used to add simulation data to the primitives and provides iterators to loop over the
 * process-local primitives.
 *
 * Construction of a PrimitiveStorage object is a three step process:
 *
 * -# creating a MeshInfo object
 * -# creating a SetupPrimitiveStorage from the MeshInfo object
 * -# creating a distributed PrimitiveStorage from the SetupPrimitiveStorage
 *
 * \section BA01-mesh Creating a MeshInfo
 *
 * The MeshInfo class is used to load / parse mesh files of different formats and store the
 * information in an instance. This extra step was introduced to provide an interface for
 * different mesh file formats.
 *
 * To parse a mesh file simple use the respective static method of the class. To parse a
 * file in GMSH format, run:
 * \snippet{trimleft} this MeshInfo
 *
 * Alternatively you can use one of the inline mesh generators available in HyTeG. The
 * code below e.g. will generate a regular criss-cross mesh composed of (3 x 2) sub-cells
 * (each split into four triangles) on the 2D rectangle \f$(-2,1) \times (0,3)\f$:
 *
 * \code{.cpp}
 hyteg::MeshInfo meshInfo = MeshInfo::meshRectangle( Point2D( -2.0, 0.0 ), Point2D( 1.0, 3.0 ), MeshInfo::CRISSCROSS, 3, 2 );
 \endcode
 *
 * Inline generators are provided for a selection of standard geometries such as e.g.
 * rectangle, annulus, thick spherical shell. See the MeshInfo class documentation for
 * a complete list and their options. Additionally you can take a look at and/or run the
 * \link show_mesh.cpp show_mesh app\endlink.
 *
 * \section BA01-setupstorage Creating a SetupPrimitiveStorage
 *
 * Before we can create the distributed storage, we need to perform an intermediate step:
 * we need to create a SetupPrimitiveStorage.
 *
 * This class creates the respective Primitive instances 
 * from the MeshInfo. The resulting storage object is not distributed. However, in this phase the
 * primitives only carry metadata and no actual simulation data is allocated on them, yet.
 *
 * \snippet{trimleft} this SetupPrimitiveStorage
 *
 * The main purpose of the SetupPrimitiveStorage is to assign the primitives to the processes.
 * We achieve this by calling a load balancing function on it. There are some simple load balancers
 * available in the library, from which the user can chose. However, if they do not call one, then
 * the class will select a default loadbalancer from the library automatically. Anyway, here is an
 * example of how to use them in practice:
 *
 * \snippet{trimleft} this Loadbalancing
 *
 * We can ask the SetupPrimitiveStorage object to provide us with some statistics. We only want to
 * get the output once, so we place it inside a WALBERLA_LOG_INFO_ON_ROOT macro.
 *
 * \snippet{trimleft} this Statistics
 *
 * Running the example with the tri_4el.msh and three MPI processes will give us something like the
 * following:
 *
 * \verbatim
[0][INFO    ]------(0.000 sec) SetupPrimitiveStorage:
[0]                             - Processes (overall):          3
[0]                             - Processes (empty)  :          0
[0]                             - Number of...
[0]                               +  Vertices:          6 | 6/6 on boundary
[0]                               +     Edges:          9 | 6/9 on boundary
[0]                               +     Faces:          4 | 0/4 on boundary
[0]                               +     Cells:          0 | 0/0 on boundary
[0]                             - Primitives per process...
[0]                               +      min:          6
[0]                               +      max:          7
[0]                               +      avg:    6.33333
\endverbatim
 *
 * The first lines tell us that overall there are three processes and each of them "owns" some
 * primitives, so none is "empty". From the next block we get that we have a total of 19 primitives
 * in our mesh and how these are distributed amongst the four different categories. As we are dealing
 * with a 2D mesh, there, obviously, are no macro-cells involved. The final block provides some
 * statistics on the distribution of primitives.
 *
 * \section BA01-storage Creating a distributed PrimitiveStorage
 *
 * Finally we are able to create the distributed PrimitiveStorage object:
 *
 * \snippet{trimleft} this PrimitiveStorage
 *
 * The data structure is now distributed and different ranks carry different primitives. Querying the
 * number of primitives should therefore (in general) result in different numbers on different processes:
 *
 * \snippet{trimleft} this NumberOfPrimitives
 *
 * Indeed, running our example again with three processes results in (output manually sorted ;-)
 *
 * \verbatim
[0][INFO    ]------(0.000 sec) Number of macro-vertices on rank 0: 2
[1][INFO    ]------(0.000 sec) Number of macro-vertices on rank 1: 2
[2][INFO    ]------(0.000 sec) Number of macro-vertices on rank 2: 2

[0][INFO    ]------(0.000 sec) Number of macro-edges    on rank 0: 3
[1][INFO    ]------(0.000 sec) Number of macro-edges    on rank 1: 3
[2][INFO    ]------(0.000 sec) Number of macro-edges    on rank 2: 3

[0][INFO    ]------(0.000 sec) Number of macro-faces    on rank 0: 2
[1][INFO    ]------(0.000 sec) Number of macro-faces    on rank 1: 1
[2][INFO    ]------(0.000 sec) Number of macro-faces    on rank 2: 1
\endverbatim
 * 
 * \section BA01-Code Complete Program
 * \include tutorials/basics-for-apps/BA.01_PrimitiveStorage.cpp
 *
 *
 *
 */

void PrimitiveStorageTutorial()
{
  uint_t rank         = uint_c( walberla::mpi::MPIManager::instance()->rank() );
  uint_t numProcesses = uint_c( walberla::mpi::MPIManager::instance()->numProcesses() );

  /// [MeshInfo]
  hyteg::MeshInfo meshInfo = MeshInfo::fromGmshFile( "../../data/meshes/tri_4el.msh" );
  /// [MeshInfo]

  /// [SetupPrimitiveStorage]
  hyteg::SetupPrimitiveStorage setupStorage( meshInfo, numProcesses );
  /// [SetupPrimitiveStorage]

  /// [Loadbalancing]
  hyteg::loadbalancing::roundRobin( setupStorage );
  /// [Loadbalancing]

  /// [Statistics]
  WALBERLA_LOG_INFO_ON_ROOT( setupStorage );
  /// [Statistics]

  /// [PrimitiveStorage]
  hyteg::PrimitiveStorage storage( setupStorage );
  /// [PrimitiveStorage]

  // For nicer output
  WALBERLA_MPI_BARRIER();

  /// [NumberOfPrimitives]
  WALBERLA_LOG_INFO( "Number of macro-vertices on rank " << rank << ": " << storage.getNumberOfLocalVertices() );
  WALBERLA_LOG_INFO( "Number of macro-edges    on rank " << rank << ": " << storage.getNumberOfLocalEdges() );
  WALBERLA_LOG_INFO( "Number of macro-faces    on rank " << rank << ": " << storage.getNumberOfLocalFaces() );
  /// [NumberOfPrimitives]
}

} // namespace hyteg

int main( int argc, char** argv )
{
  walberla::mpi::Environment env( argc, argv );
  walberla::mpi::MPIManager::instance()->useWorldComm();
  hyteg::PrimitiveStorageTutorial();
  return 0;
}
