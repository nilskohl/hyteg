/*
 * Copyright (c) 2023 Marcus Mohr, Roman Freissler.
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

#include <adios2.h>
#include <variant>

#include "hyteg/BuildInfo.hpp"
#include "hyteg/Git.hpp"
#include "hyteg/functions/FunctionMultiStore.hpp"

using walberla::uint_t;

namespace hyteg::adiosHelpers {

// Here define valid ADIOS2 data types
typedef std::variant< int, long, float, double, uint_t, bool, std::string > adiostype_t;

// Templated convenience wrapper for std::variant<>
template < typename T, typename VARIANT_T >
struct isAdiosDataType;

/// Template specialization for type checking of variables intended as ADIOS2 attributes
///
/// We use this to check if a given std::variant is consistent with adiostype_t
template < typename T, typename... ALL_T >
struct isAdiosDataType< T, std::variant< ALL_T... > > : public std::disjunction< std::is_same< T, ALL_T >... >
{};

std::string generateVTKMetaInfo( const std::vector< std::string >& namesOfPointDataFunctions,
                                 const std::vector< std::string >& namesOfCellDataFunctions );

/// Name of scalar variable to be used in exporting time-step information
///
/// We use this variable to ensure consistency between the different places where this
/// variable name is needed, e.g in genewrateVTKMetaInfo and putTimeStepInfo. Note, though,
/// that currently TIME is the only allowed value.
extern const std::string nameOfTimeStepVariable;

/// Schedule information on current time step to be exported
inline void putTimeStepInfo( adios2::IO& io, adios2::Engine& engine, uint_t timestep )
{
   adios2::Variable< real_t > varTimeStep = io.InquireVariable< real_t >( nameOfTimeStepVariable );
   if ( !varTimeStep )
   {
      varTimeStep = io.DefineVariable< real_t >( nameOfTimeStepVariable );
   }
   engine.Put( varTimeStep, real_c( timestep ) );
}

/// Check whether the current process owns primitives with data to export (faces, or cell depending on dimension)
inline bool mpiProcessHasMacrosOfHighestDimension( const std::shared_ptr< PrimitiveStorage >& storage )
{
   bool weStoreRelevantData = false;
   if ( storage->hasGlobalCells() && storage->getCells().size() > 0 )
   {
      return true;
   }
   else if ( storage->getFaces().size() > 0 )
   {
      return true;
   }
   return false;
}

/// Write meta data on the software used for simulation into the given stream
inline std::ostream& printSoftwareMetaData( std::ostream& outStream )
{
   // clang-format off
   outStream << "Data generated with HyTeG (https://i10git.cs.fau.de/hyteg)\n"
             << "git branch         : " << gitBranch()     << '\n'
             << "SHA1 of last commit: " << gitSHA1()       << '\n'
             << "build type         : " << buildType()     << '\n'
             << "compiler           : " << compilerInfo()  << '\n'
             << "compiler flags     : " << compilerFlags() << '\n'
             << "mpi version        : " << mpiVersion()    << std::endl;
   // clang-format on

   return outStream;
}

/// Schedule meta data on the software used for simulation for export
inline void generateSoftwareMetaData( adios2::IO& io )
{
   adios2::Attribute< std::string > infoSoftware = io.InquireAttribute< std::string >( "Software" );
   if ( !infoSoftware )
   {
      std::stringstream oStream;
      printSoftwareMetaData( oStream );
      infoSoftware = io.DefineAttribute( "Software", oStream.str(), "", "" );
   }
}

/// auxilliary function to read attributes, will abort, if attribute is not found
template < typename T >
adios2::Attribute< T > readAttribute( adios2::IO& io, const std::string& name )
{
   adios2::Attribute< T > attribute = io.InquireAttribute< T >( name );
   if ( !attribute )
   {
      WALBERLA_ABORT( "Attribute '" << name << "' seems to be missing from checkpoint!" );
   }
   return std::move( attribute );
}

/// Write a single value attribute to ADIOS2 ouptut
template < typename T >
inline void writeAttribute( adios2::IO& io, const std::string& key, const T& val )
{
   adios2::Attribute< T > infoAttribute = io.InquireAttribute< T >( key );
   if ( !infoAttribute )
   {
      infoAttribute = io.DefineAttribute< T >( key, val );
   }
   else
   {
      WALBERLA_LOG_INFO_ON_ROOT( "ADIOS2 file: Attribute " << infoAttribute.Name() << "already written" );
   }
}

/// Write all user-defined single-value attributes from a map to ADIOS2 ouptut
inline void writeAllAttributes( adios2::IO& io, const std::map< std::string, adiostype_t >& userDefinedAttributes )
{
   // integer datatype for output
   using intData_t = ADIOS2_PARAVIEW_INT_TYPE;

   if ( userDefinedAttributes.empty() )
   {
      WALBERLA_LOG_PROGRESS_ON_ROOT( "No additional user-defined attributes/metadata written to ADIOS2 output" );
      return;
   }

// see issue #273
#ifdef CPP2020
   for ( auto const& [key, val] : userDefinedAttributes )
   {
      std::visit(
          [&io, key]( const auto& arg ) {
             using T = std::decay_t< decltype( arg ) >;
             if ( isAdiosDataType< T, adiostype_t >::value )
             {
                // For Fortran compatibility, cast unsigned integer to signed integers, if ADIOS2_PARAVIEW_INT_TYPE is signed
                if constexpr ( std::is_same_v< T, uint_t > && std::is_signed_v< intData_t > )
                   writeAttribute( io, key, static_cast< intData_t >( arg ) );
                else if constexpr ( std::is_same_v< T, bool > )
                {
                   std::string sflag = arg ? "true" : "false";
                   writeAttribute( io, key, sflag );
                }
                else
                   writeAttribute( io, key, arg );
             }
             else
             {
                WALBERLA_LOG_WARNING_ON_ROOT( "The user-defined ADIOS2 attribute " << key << " does not hold a valid datatype" );
             }
          },
          val );
   }
#else
   for ( auto const& entry : userDefinedAttributes )
   {
      std::visit(
          [&io, &entry]( const auto& arg ) {
             using T = std::decay_t< decltype( arg ) >;
             const std::string& key = entry.first;

             if ( isAdiosDataType< T, adiostype_t >::value )
             {

                // For Fortran compatibility, cast unsigned integer to signed integers, if ADIOS2_PARAVIEW_INT_TYPE is signed
                if constexpr ( std::is_same_v< T, uint_t > && std::is_signed_v< intData_t > )
                   writeAttribute( io, key, static_cast< intData_t >( arg ) );
                else if constexpr ( std::is_same_v< T, bool > )
                {
                   std::string sflag = arg ? "true" : "false";
                   writeAttribute( io, key, sflag );
                }
                else
                   writeAttribute( io, key, arg );
             }
             else
             {
                WALBERLA_LOG_WARNING_ON_ROOT( "The user-defined ADIOS2 attribute " << key << " does not hold a valid datatype" );
             }
          },
          entry.second );
   }
#endif
}

/// Write all user-defined single-value attributes from a map to ADIOS2 ouptut
inline void readAllAttributes( adios2::IO& io, std::map< std::string, adiostype_t >& userDefinedAttributes )
{
   // integer datatype for output
   using intData_t = ADIOS2_PARAVIEW_INT_TYPE;

   if ( userDefinedAttributes.empty() )
   {
      WALBERLA_LOG_PROGRESS_ON_ROOT( "No additional user-defined attributes/metadata written to ADIOS2 output" );
      return;
   }

// see issue #273
#ifdef CPP2020
   for ( auto& [key, val] : userDefinedAttributes )
   {
      std::visit(
          [&io, key]( const auto& arg ) {
             using T = std::decay_t< decltype( arg ) >;
             if ( isAdiosDataType< T, adiostype_t >::value )
             {
                // For Fortran compatibility, cast unsigned integer to signed integers, if ADIOS2_PARAVIEW_INT_TYPE is signed
                if constexpr ( std::is_same_v< T, uint_t > && std::is_signed_v< intData_t > )
                {
                   adios2::Attribute< intData_t > data = readAttribute<intData_t>( io, key );
                   entry.second = static_cast< T >( data.Data()[0] );
                }
                else if constexpr ( std::is_same_v< T, bool > )
                {
                   adios2::Attribute< std::string > data = readAttribute<std::string>( io, key );
                   entry.second = (data.Data()[0] == std::string("true"));
                }
                else
                {
                  adios2::Attribute< T > data = readAttribute<T>( io, key );
                  entry.second = data.Data()[0];
                }
             }
             else
             {
                WALBERLA_LOG_WARNING_ON_ROOT( "The user-defined ADIOS2 attribute " << key << " does not hold a valid datatype" );
             }
          },
          val );
   }
#else
   for ( auto& entry : userDefinedAttributes )
   {
      std::visit(
          [&io, &entry]( const auto& arg ) {
             using T = std::decay_t< decltype( arg ) >;
             const std::string& key = entry.first;

             if ( isAdiosDataType< T, adiostype_t >::value )
             {
                // For Fortran compatibility, cast unsigned integer to signed integers, if ADIOS2_PARAVIEW_INT_TYPE is signed
                if constexpr ( std::is_same_v< T, uint_t > && std::is_signed_v< intData_t > )
                {
                   adios2::Attribute< intData_t > data = readAttribute<intData_t>( io, key );
                   entry.second = static_cast< T >( data.Data()[0] );
                }
                else if constexpr ( std::is_same_v< T, bool > )
                {
                   adios2::Attribute< std::string > data = readAttribute<std::string>( io, key );
                   entry.second = (data.Data()[0] == std::string("true"));
                }
                else
                {
                  adios2::Attribute< T > data = readAttribute<T>( io, key );
                  entry.second = data.Data()[0];
                }
             }
             else
             {
                WALBERLA_LOG_WARNING_ON_ROOT( "The user-defined ADIOS2 attribute " << key << " does not hold a valid datatype" );
             }
          },
          entry.second );
   }
#endif
}

} // namespace hyteg::adiosHelpers
