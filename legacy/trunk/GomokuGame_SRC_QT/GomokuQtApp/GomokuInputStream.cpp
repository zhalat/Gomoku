/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuInputStream.h
///
/// Input stream for gomoku backend.
///
/// @par Full Description.
/// Input stream for gomoku backend.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 06-Apr-2017 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>
#include <sstream>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GomokuInputStream.h"
#include "GomokuOutputStream.h"


// FORWARD REFERENCES
// <none>

/// Default Constructor.
GomokuInputStream::GomokuInputStream()
 : std::istringstream()
{
    // Reset the status of stream.
    this->clear();
    m_NewStageSound.setSource(QUrl("qrc:/Sound/newGame.wav"));
}

/// Provides human move. GUI->GOMOKU ALGORYTHM.
void GomokuInputStream::frontendeventmove( const int humanX, const int humanY )
{
    qDebug() << "c++: dbg::GUI->BackEND:: Event Type:[" << GomokuOutputStream::HUMAN_MOVE << "]. Data: " << "(" << humanX << ", " << humanY << ")";

    // Convert data into string.
    std::stringstream ss;
    ss << static_cast<uint32_t>( humanX ) << std::endl << static_cast<uint32_t>( humanY )<< std::endl;
    const std::string stringData = ss.str();

    // Put user move into stream.
    this->str( stringData );

    // Data avaliable.
    this->ProcessData();
}

/// New stage.
void GomokuInputStream::frontendeventhumanmsg( QString msg )
{
    qDebug() << "c++: dbg::GUI->BackEND:: End game message passing." << msg;
    m_NewStageSound.play();

    // Put user move into stream.
    this->str( msg.toStdString() );

    // Data avaliable.
    this->ProcessData();
}

/// Check for input data.
void GomokuInputStream::WaitForData()
{
     m_QSemaphore.acquire();
}

/// Use it after put some data to stream.
void GomokuInputStream::ProcessData()
{
    m_QSemaphore.release();
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

