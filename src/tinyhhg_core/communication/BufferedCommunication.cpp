
#include "tinyhhg_core/communication/BufferedCommunication.hpp"
#include "core/logging/Logging.h"

#include <functional>

namespace hhg {
namespace communication {

const std::array< std::string, BufferedCommunicator::NUM_COMMUNICATION_DIRECTIONS > BufferedCommunicator::COMMUNICATION_DIRECTION_STRINGS = {{
      "vertex -> edge  ",
      "edge   -> vertex",
      "edge   -> face  ",
      "face   -> edge  "
}};

const std::array< std::string, BufferedCommunicator::NUM_LOCAL_COMMUNICATION_MODES > BufferedCommunicator::LOCAL_COMMUNICATION_MODE_STRINGS = {{
    "direct",
    "buffered MPI"
}};

BufferedCommunicator::BufferedCommunicator( std::weak_ptr< PrimitiveStorage > primitiveStorage, const LocalCommunicationMode & localCommunicationMode ) :
    primitiveStorage_( primitiveStorage ), primitiveStorageModificationStamp_( primitiveStorage_.lock()->getModificationStamp() ), localCommunicationMode_( localCommunicationMode )
{
  int baseTag = 0;
  for ( auto & bufferSystem : bufferSystems_ )
  {
    bufferSystem = std::shared_ptr< walberla::mpi::OpenMPBufferSystem >( new walberla::mpi::OpenMPBufferSystem( walberla::mpi::MPIManager::instance()->comm(), baseTag++ ) );
  }

  setupBeforeNextCommunication();

#ifndef NDEBUG
  for ( auto & communicationInProgress : communicationInProgress_ )
  {
    communicationInProgress = false;
  }
#endif
}

void BufferedCommunicator::addPackInfo( const std::shared_ptr< PackInfo > & packInfo )
{
  setupBeforeNextCommunication();
  packInfos_.push_back( packInfo );
}

void BufferedCommunicator::writeHeader( SendBuffer & sendBuffer, const PrimitiveID & senderID, const PrimitiveID & receiverID )
{
  sendBuffer << senderID << receiverID;
}

void BufferedCommunicator::readHeader ( RecvBuffer & recvBuffer,       PrimitiveID & senderID,       PrimitiveID & receiverID )
{
  recvBuffer >> senderID >> receiverID;
}

void BufferedCommunicator::startTimer( const std::string & timerString )
{
  if ( timingTree_ )
  {
    timingTree_->start( timerString );
  }
}

void BufferedCommunicator::stopTimer( const std::string & timerString )
{
  if ( timingTree_ )
  {
    timingTree_->stop( timerString );
  }
}

void BufferedCommunicator::setupBeforeNextCommunication()
{
  setupBeforeNextCommunication_.fill( true );
}

}
}