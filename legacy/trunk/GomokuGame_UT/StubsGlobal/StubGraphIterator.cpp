/////////////////////////////////////////////////////////////////////////////////////////
/// @file GraphIterator.cpp
///
/// GraphIterator class definition.
///
/// @par Full Description.
/// Providing iterator for graph class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 12-May-2016 Initial revision.
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
#include "GraphIterator.hpp"    // For Graph declaration.
#include <assert.h>             // For assert.

// FORWARD REFERENCES
// <none>

/// Check if collection has next element.
bool GraphIterator::HasNext() const
{
    assert( false );
    return true;
}

/// Get the next element.
graph::Node GraphIterator::GetNext()
{
    assert( false );
    return static_cast<graph::Node>( 0 );
}

/// Get index of current element.
uint32_t GraphIterator::GetIndex() const
{
    assert( false );
    return 0;
}
