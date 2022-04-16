/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuBackEnd.hpp
///
/// Interaction between GUI and gomoku algorythm.
///
/// @par Full Description.
/// Handles actions between user (GUI) and gomoku algorythm.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 26-Mar-2017 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <QMutex>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GomokuBackEnd.h"      // GomokuBackEnd declaration.
#include "GomokuGame.hpp"       // For GomokuGame algorithm.
#include "GomokuInputStream.h"

// FORWARD REFERENCES
// <none>

void GomokuBackEnd::Init( const uint32_t size,
                          const char* pHumanColor,
                          const uint32_t level,
                          const bool isRandomize,
                          const uint32_t maxTime,
                          std::istream& inStream,
                          std::ostream& outStream )
{
    m_pInStream = &inStream;
    m_pOutStream = &outStream;
    m_BoardSize = size;
    m_pHumanColor = pHumanColor;
    m_GameLevel = level;
    m_IsRandomize = isRandomize;
    m_MaxTime = maxTime;
}

/// Thread running Gomoku algorithm.
void GomokuBackEnd::run()
{
    GomokuGame gomokuGame;

    assert( m_pInStream );
    assert( m_pOutStream );

    gomokuGame.Init( m_BoardSize,
                     Board::String2Player( m_pHumanColor ),
                     static_cast<TwoPlayersGame::Level>( m_GameLevel ),
                     m_IsRandomize,
                     m_MaxTime,
                     *m_pInStream,
                     *m_pOutStream );
    gomokuGame.Play();

    exec();
}

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
