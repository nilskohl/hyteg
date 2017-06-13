#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <fmt/ostream.h>
#include "tinyhhg_core/types/pointnd.hpp"
#include <core/DataTypes.h>
#include <tinyhhg_core/types/flags.hpp>

#include <vector>


namespace hhg
{

class Edge;
class Face;

class VertexMemory;

/// \brief  Macro-Vertex primitive
/// \author Daniel Drzisga (drzisga@ma.tum.de)
/// \date   March, 2017
///
/// The Vertex class represents a Macro-Vertex primitve. It saves geometrical and topological information
/// as well as pointers to memory reserved for \ref Function and \ref Operator.
class Vertex
{
public:
  /// Constructs a vertex with given id and coordinates
  /// \param id Id of vertex
  /// \param coords Spatial coordinates of vertex
  Vertex(size_t id, const Point3D& coords);

  /// Adds given edge to \ref edges
  /// \param edge Pointer to edge which will be added
  void addEdge(Edge* edge);

  /// Adds given face to \ref faces
  /// \param face Pointer to face which will be added
  void addFace(Face* face);

  /// Returns the index of \p edge within \ref edges
  /// \param edge Edge
  /// \returns Index of \p edge within \ref edges
  size_t edge_index(const Edge& edge) const;

  /// Id of vertex
  size_t id;

  /// Processor rank this vertex belongs to
  walberla::uint_t rank;

  /// DoF type of vertex
  DoFType type;

  /// Spatial coordinates of vertex
  Point3D coords;

  /// Pointers to edges adjacent to vertex
  std::vector<Edge*> edges;

  /// Pointers to faces adjacent to vertex
  std::vector<Face*> faces;


  /// Vector containing pointers to memory used by \ref Function and \ref Operator
  /// The std::vector corresponds to the memory id of a \ref Function or an \Operator
  /// This replaces the old data and opr_data vectors
  std::vector<VertexMemory*> memory;


  /// Method overload for string formatting
  friend std::ostream &operator<<(std::ostream &os, const Vertex &vertex);
};


class VertexMemory
{
public:
  const MemoryType type;
  virtual ~VertexMemory() { }

protected:
  VertexMemory(MemoryType t) : type(t) { ; }
};

}

#endif /* VERTEX_HPP */
