#pragma once
#include <iterator>

namespace hhg
{
namespace P1Face
{

using walberla::uint_t;

namespace CoordsVertex {
enum DirVertex {
  VERTEX_S  = 0,
  VERTEX_SE = 1,
  VERTEX_W  = 2,
  VERTEX_C  = 3,
  VERTEX_E  = 4,
  VERTEX_NW = 5,
  VERTEX_N  = 6
};

const DirVertex neighbors_with_center[] =
    {VERTEX_C,
     VERTEX_S, VERTEX_SE, VERTEX_E, VERTEX_N, VERTEX_NW, VERTEX_W};
const DirVertex neighbors[] =
    {VERTEX_S, VERTEX_SE, VERTEX_E, VERTEX_N, VERTEX_NW, VERTEX_W};

template<size_t Level>
inline size_t index(size_t col, size_t row, DirVertex dir) {
  const size_t vertexBaseLength = levelinfo::num_microvertices_per_edge(Level);
  WALBERLA_ASSERT_LESS(col+row,vertexBaseLength);
  const size_t totalVertices = vertexBaseLength * (vertexBaseLength + 1) / 2;
  const size_t center = (totalVertices - (vertexBaseLength-row)*(vertexBaseLength-row+1)/2) + col;
  switch (dir) {
    case VERTEX_C:
      return center;
    case VERTEX_N:
      return center + vertexBaseLength - row;
    case VERTEX_E:
      return center + 1;
    case VERTEX_S:
      return center - vertexBaseLength - 1 + row;
    case VERTEX_W:
      return center - 1;
    case VERTEX_SE:
      return center - vertexBaseLength + row;
    case VERTEX_NW:
      return center + vertexBaseLength - row - 1;
  }

  WALBERLA_ASSERT(false, "wrong dir");
  return std::numeric_limits<size_t>::max();
}
}//namespace CoordsVertex

namespace CoordsCellGray {
enum DirVertex {
  VERTEX_SW = 0,
  VERTEX_SE = 1,
  VERTEX_NW = 2
};

const DirVertex neighbors[] = {VERTEX_SW, VERTEX_SE, VERTEX_NW};

template<size_t Level>
inline size_t index(size_t col, size_t row, DirVertex dir) {
  //typedef hhg::P1Face::CoordsVertex CoordsVertex;

  switch(dir){
    case VERTEX_SW:
      return hhg::P1Face::CoordsVertex::index<Level>(col,row,hhg::P1Face::CoordsVertex::VERTEX_C);
    case VERTEX_SE:
      return hhg::P1Face::CoordsVertex::index<Level>(col,row,hhg::P1Face::CoordsVertex::VERTEX_E);
    case VERTEX_NW:
      return hhg::P1Face::CoordsVertex::index<Level>(col,row,hhg::P1Face::CoordsVertex::VERTEX_N);
  }

  WALBERLA_ASSERT(false, "wrong dir");
  return std::numeric_limits<size_t>::max();
}
} //namespace CoordsCellGray

namespace CoordsCellBlue {
enum DirVertex {
  VERTEX_SE = 0,
  VERTEX_NW = 1,
  VERTEX_NE = 2
};

const DirVertex neighbors[] = {VERTEX_SE, VERTEX_NW, VERTEX_NE};

template<size_t Level>
inline size_t index(size_t col, size_t row, DirVertex dir) {
  switch(dir){
    case VERTEX_SE:
      return hhg::P1Face::CoordsVertex::index<Level>(col,row,hhg::P1Face::CoordsVertex::VERTEX_E);
    case VERTEX_NW:
      return hhg::P1Face::CoordsVertex::index<Level>(col,row,hhg::P1Face::CoordsVertex::VERTEX_N);
    case VERTEX_NE:
      return hhg::P1Face::CoordsVertex::index<Level>(col+1,row+1,hhg::P1Face::CoordsVertex::VERTEX_C);
  }

  WALBERLA_ASSERT(false, "wrong dir");
  return std::numeric_limits<size_t>::max();
}
} //namespace CoordsCellBlue

enum DofType {
  VERTEX = 0,
  VERTEX_INNER = 1
  //VERTEX_INNER: vertex dofs that are connected to the boundary
};

/// Iterator to get the indices for one specific edge and DofType in the face memory
/// Be aware that the iterator also handles orientation e.g. if unpacking from a buffer filled with
/// data from the edge the indices are either increasing or decrase depending on the orientation of
/// the edge
class indexIterator : public std::iterator< std::forward_iterator_tag, walberla::uint_t >
{
 public:
  /*!
   * @brief begin iterator
   * @param face
   * @param edge corresponding edge
   * @param type Doftype can be VERTEX,CELL_GRAY,CELL_BLUE, VERTEX_INNER
   * @param level multigrid level
   */
  inline indexIterator(uint_t edgeIndex, int edgeOrientation, DofType type, walberla::uint_t level);
  /*!
   * @brief end iterator
   */
  inline indexIterator();

  inline indexIterator& operator++();
  inline indexIterator operator++(int);
  inline walberla::uint_t operator*() const;
  inline bool operator==(const indexIterator& other) const;
  inline bool operator!=(const indexIterator& other) const;


 private:
  int idx_;
  int counter_;
  int num_perEdge_;
  int offset_;
  int offsetOffset_;
  int edge_orientation_;
  uint_t edge_index_;
  bool ended_;
};

indexIterator::indexIterator(uint_t edgeIndex, int edgeOrientation, DofType type, walberla::uint_t level)
    : idx_(0),
      counter_(0),
      num_perEdge_(0),
      offset_(0),
      offsetOffset_(0),
      edge_orientation_(edgeOrientation),
      edge_index_(edgeIndex),
      ended_(false)
{
  WALBERLA_ASSERT(edge_orientation_ == -1 || edge_orientation_ == 1,"Invalid edge Orientation: " << edge_orientation_);

  num_perEdge_ = walberla::int_c(hhg::levelinfo::num_microvertices_per_edge(level));
  int maximum = walberla::int_c(hhg::levelinfo::num_microvertices_per_face(level)) - 1;
  switch(type){
    case VERTEX:
      break;
    case VERTEX_INNER:
      //This is handled in the next switch
      break;
    default:
      WALBERLA_ASSERT(false, "Wrong DofType: " << type);
      break;
  }

  switch (edge_index_) {
    case 0:
      if (edge_orientation_ == 1) {
        idx_ += 0;
        offset_ = 1;
        offsetOffset_ = 0;
        if(type == VERTEX_INNER){
          idx_ += num_perEdge_;
          num_perEdge_--;
        }
      } else {
        idx_ += num_perEdge_ - 1;
        offset_ = -1;
        offsetOffset_ = 0;
        if(type == VERTEX_INNER){
          idx_ += num_perEdge_ -1;
          num_perEdge_--;
        }
      }
      break;
    case 1:
      if (edge_orientation_ == 1) {
        idx_ += num_perEdge_ - 1;
        offset_ = num_perEdge_ - 1;
        offsetOffset_ = -1;
        if(type == VERTEX_INNER){
          idx_--;
          num_perEdge_--;
        }
      } else {
        idx_ += maximum;
        offset_ = -1;
        offsetOffset_ = -1;
        if(type == VERTEX_INNER){
          idx_-=2;
          num_perEdge_--;
          offset_ += offsetOffset_;
        }
      }
      break;
    case 2:
      if (edge_orientation_ == 1) {
        idx_ += maximum;
        offset_ = -2;
        offsetOffset_ = -1;
        if(type == VERTEX_INNER){
          idx_--;
          num_perEdge_--;
          offset_ += offsetOffset_;
        }
      } else {
        idx_ += 0;
        offset_ = num_perEdge_;
        offsetOffset_ = -1;
        if(type == VERTEX_INNER){
          idx_++;
          num_perEdge_--;
        }
      }
      break;
    default:
      WALBERLA_ASSERT(false, "invalid edge index");
      break;
  }
}

indexIterator &indexIterator::operator++()
{
  idx_ += offset_;
  offset_ += offsetOffset_;
  counter_++;
  if(counter_ == num_perEdge_) ended_ = true;
  return *this;
}

indexIterator indexIterator::operator++(int)
{
  indexIterator tmp(*this);
  operator++();
  return tmp;
}

walberla::uint_t indexIterator::operator*() const {
  return walberla::uint_c(idx_);
}

bool indexIterator::operator==(const indexIterator &other) const {
  if (ended_ || other.ended_)
  {
    return (ended_ == other.ended_);
  }
  return (idx_ == other.idx_);
}

bool indexIterator::operator!=(const indexIterator &other) const {
  return !(*this == other);
}

indexIterator::indexIterator()
    :ended_(true)
{}

} //namespace P1Face
} //namespace hhg