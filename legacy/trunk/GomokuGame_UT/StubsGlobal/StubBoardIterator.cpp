/////////////////////////////////////////////////////////////////////////////////////////
/// @file BoardIterator.cpp
///
/// BoardIterator class definition.
///
/// @par Full Description.
/// Providing iterator for board class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 15-May-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "BoardIterator.hpp"    // For BoardIterator declaration.
#include <assert.h>             // For assert.

// FORWARD REFERENCES
// <none>

/// Check if collection has next element.
bool BoardIterator::HasNext() const
{
    assert( false );
    return true;
}

/// Get the next element.
graph::Node BoardIterator::GetNext()
{
    assert( false );
    return static_cast<graph::Node>( 0 );
}

/// Get index of current element.
uint32_t BoardIterator::GetIndex() const
{
    assert( false );
    return 0;
}
