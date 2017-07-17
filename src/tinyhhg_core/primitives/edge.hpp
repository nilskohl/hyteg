#ifndef EDGE_HPP
#define EDGE_HPP

#include "tinyhhg_core/types/pointnd.hpp"

#include <vector>

#include <tinyhhg_core/types/pointnd.hpp>
#include <tinyhhg_core/types/flags.hpp>
#include <tinyhhg_core/primitives/Primitive.hpp>
#include <tinyhhg_core/primitives/SetupEdge.hpp>

#include <core/DataTypes.h>
#include <core/Deprecated.h>

namespace hhg
{

class Vertex;
class Face;

class EdgeMemory;

class Edge : public Primitive
{
public:

  friend class PrimitiveStorage;

  Edge(size_t id, DoFType type, Vertex* v0, Vertex* v1);
  Edge( PrimitiveStorage & storage, const SetupPrimitiveStorage & setupStorage, const PrimitiveID & primitiveID );
  void addFace(Face* face);

  size_t vertex_index(const Vertex& vertex) const;
  size_t face_index(const Face& face) const;

  Vertex* get_opposite_vertex(const Vertex& vertex) const;

  size_t id;
  walberla::uint_t rank;
  DoFType type;
  Vertex* v0;
  Vertex* v1;

  Point3D direction;
  real_t length;
  Point3D tangent;
  Point3D normal_2d;

  std::vector<Face*> faces;

  std::vector<EdgeMemory*> memory;

  friend std::ostream &operator<<(std::ostream &os, const Edge &edge);

  /// Returns a pointer to the data that belongs to the passed \ref PrimitiveDataID.
  /// \param index the \ref PrimitiveDataID of the data that should be returned
  template< typename DataType >
  DataType* getData( const PrimitiveDataID< DataType, Edge > & index ) const
  {
    return genericGetData< DataType >( index );
  }

protected:

  /// Not public in order to guarantee that data is only added through the governing structure.
  /// This ensures valid DataIDs.
  template< typename DataType >
  inline void addData( const PrimitiveDataID< DataType, Edge > & index,
		       const PrimitiveDataHandling< DataType, Edge > & dataHandling )
  {
    genericAddData( index, dataHandling, this );
  }

};

class EdgeMemory
{
public:
  const MemoryType type;
  virtual ~EdgeMemory() { }

protected:
  EdgeMemory(MemoryType t) : type(t) { ; }
};
}

#endif /* EDGE_HPP */
