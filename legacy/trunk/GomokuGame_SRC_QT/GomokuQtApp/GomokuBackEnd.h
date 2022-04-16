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

#ifndef BACKEND_H
#define BACKEND_H

// SYSTEM INCLUDES
#include <QThread>
#include <QDebug>
#include <sstream>
#include <string>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
// <none>

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: GomokuBackEnd
///
/// Interaction between GUI and gomoku algorythm.
///
/// @par Full Description.
/// Handles actions between user (GUI) and gomoku algorythm.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuBackEnd: public QThread
{
public:
    // Constructor.
    GomokuBackEnd()
     : m_pInStream( NULL )
     , m_pOutStream( NULL )
     , m_BoardSize( 0 )
     , m_pHumanColor( NULL )
     , m_GameLevel( 0 )
     , m_IsRandomize( false )
     , m_MaxTime( 0 )
    {}

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuBackEnd::Init
    //
    /// Initialize of game.
    ///
    /// @par Full Description
    /// Setting basic parameter of the game.
    ///
    /// @param size       The board size.
    /// @param humanColor Humans' name/sign.
    /// @param level      Level of the game.
    /// @param isRandomize  If true isRandomize is enabled.
    /// @param maxTime    max time for cpu move.
    /// @param inStream   Input stream.
    /// @param outStream  Output stream.
    ///////////////////////////////////////////////////////////////////////
    void Init( const uint32_t size,
               const char* pHumanColor,
               const uint32_t level,
               const bool isRandomize,
               const uint32_t maxTime,
               std::istream& inStream,
               std::ostream& outStream );

private:
    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuBackEnd::run
    ///
    /// Thread running Gomoku algorithm.
    ///
    /// @par Full Description
    /// Thread running Gomoku algorithm.
    ///////////////////////////////////////////////////////////////////////
    void run();

    // Game settings.
    std::istream* m_pInStream;
    std::ostream* m_pOutStream;
    uint32_t m_BoardSize;
    const char* m_pHumanColor;
    uint32_t m_GameLevel;
    bool m_IsRandomize;
    uint32_t m_MaxTime;
};

#endif // BACKEND_H

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
