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

#ifndef GOMOKUINPUTSTREAM_H
#define GOMOKUINPUTSTREAM_H

// SYSTEM INCLUDES
#include <QDebug>
#include <QThread>
#include <QSemaphore>
#include <QObject>
#include <QSoundEffect>
#include <iostream>
#include <sstream>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
// <none>

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: GomokuInputStream
///
/// Input stream for gomoku backend.
///
/// @par Full Description.
/// Input stream for gomoku backend.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuInputStream: public QObject, public std::istringstream
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuInputStream::frontendeventmove
    ///
    /// Provides human move.
    ///
    /// @par Full Description
    /// Transfers human replay taken from frondend to backend.
    /// GUI->GOMOKU ALGORYTHM
    /// This method can be inoked in QML object.
    ///
    /// @param humanX Row
    /// @param humanY Column
    ///////////////////////////////////////////////////////////////////////
    Q_INVOKABLE void frontendeventmove( const int humanX, const int humanY );

    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuInputStream::frontendeventhumanmsg
    ///
    /// New stage.
    ///
    /// @par Full Description
    /// Game over. Create new stage.
    /// GUI->GOMOKU ALGORYTHM
    /// This method can be inoked in QML object.
    ///
    /// @param msg Message to be transported to backend.
    ///////////////////////////////////////////////////////////////////////
    Q_INVOKABLE void frontendeventhumanmsg( QString msg );

    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuInputStream::WaitForData
    ///
    /// Check for input data.
    ///
    /// @par Full Description
    /// Block current thread if data not avaliable.
    ///////////////////////////////////////////////////////////////////////
    void WaitForData();

    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuInputStream::ProcessData
    ///
    /// Unblock thread to process data.
    ///
    /// @par Full Description
    /// Use it after put some data to stream.
    ///////////////////////////////////////////////////////////////////////
    void ProcessData();

    // Default Constructor.
    GomokuInputStream();

private:
    // Wait for data.
    QSemaphore m_QSemaphore;

    // Playing sound.
    QSoundEffect m_NewStageSound;
};

#endif // GOMOKUINPUTSTREAM_H

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
