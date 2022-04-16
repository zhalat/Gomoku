/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuOutputStream.h
///
/// Output stream for gomoku backend.
///
/// @par Full Description.
/// Output stream for gomoku backend.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 09-Apr-2017 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef GOMOKUOUTPUTSTREAM_H
#define GOMOKUOUTPUTSTREAM_H

// SYSTEM INCLUDES
#include <QObject>
#include <QTimer>
#include <QVariant>
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
/// CLASS NAME: GomokuOutputStream
///
/// Stream for processing gomoku algorythm output.
///
/// @par Full Description.
/// Stream for processing gomoku algorythm output.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuOutputStream: public QObject, public std::ostringstream
{
    Q_OBJECT

public:

    // All avaliable events.
    enum Event
    {
        EVENT_NONE,
        HUMAN_WON,
        CPU_WON,
        STALEMATE,
        CHOOSE_COLOR,
        CPU_MOVE,
        HUMAN_MOVE,
        INVALID_USER_MOVE,
        INVALID_PARAMETER
    };

    // Last move put on board.
    struct LastMove
    {
        uint32_t m_x;
        uint32_t m_y;
        bool m_IsValid;

        LastMove( uint32_t x = 0, uint32_t y = 0, bool valid = false )
         : m_x( x )
         , m_y( y )
         , m_IsValid( valid )
        {}

        bool operator == ( const LastMove& x ) const
        {
            const bool retVal = ( x.m_x == m_x ) &&
                                ( x.m_y == m_y ) &&
                                ( x.m_IsValid == m_IsValid );
            return retVal;
        }

        bool operator != ( const  LastMove& x ) const
        {
            const bool retVal = ( *this == x );
            return retVal;
        }

        friend std::ostream& operator<<( std::ostream& _stream, const LastMove& rLastMove )
        {
            _stream << rLastMove.m_x <<rLastMove.m_y;
            return _stream;
        }
    };

    // Message format to communicate with external process.
    struct GomokuExeMsg
    {
        Event m_Event;
        bool m_Pending;
        LastMove m_Move;
        LastMove m_WinningMove1;
        LastMove m_WinningMove2;
        LastMove m_WinningMove3;
        LastMove m_WinningMove4;
        LastMove m_WinningMove5;

        GomokuExeMsg( const Event event,
                      bool pending,
                      const LastMove lastCpuMove,
                      const LastMove win1,
                      const LastMove win2,
                      const LastMove win3,
                      const LastMove win4,
                      const LastMove win5 )
         : m_Event( event )
         , m_Pending( pending )
         , m_Move( lastCpuMove )
         , m_WinningMove1( win1 )
         , m_WinningMove2( win2 )
         , m_WinningMove3( win3 )
         , m_WinningMove4( win4 )
         , m_WinningMove5( win5 )
        {}
    };

    //Default arguments for running exec.
    static const LastMove MOVE_INVALID;

    // Time out for timer.
    static const uint32_t TIMEOUT;

    // Default Constructor.
    GomokuOutputStream();

signals:
    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuOutputStream::backendevent
    ///
    /// Pass backend event to frontend. GUI<-GOMOKU ALGORYTHM
    ///
    /// @par Full Description
    /// Transfers cpu replay taken from external process to frontend.
    /// GUI<-GOMOKU ALGORYTHM
    /// This method can be handled in QML object.
    ///
    /// @param dataString Data to be transfered to qml GUI.
    ///////////////////////////////////////////////////////////////////////
    void backendevent( QString foo );

private slots:
    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuOutputStream::onTimer
    ///
    /// Capture a timer expire event.
    ///
    /// @par Full Description
    /// Checks if data is avaliable in stream.
    ///////////////////////////////////////////////////////////////////////
    void onTimeout();

private:
    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuOutputStream::Dispatcher
    ///
    /// Parse data received from external exec process.
    ///
    /// @par Full Description
    /// Parse data received from process. The data writes to m_RecentMsg
    ///
    /// @param cpuReply  Data received from process.
    ///
    /// @retval True if data parsed corectly.
    ///////////////////////////////////////////////////////////////////////
    bool Dispatcher( const QString& cpuReply );

    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuOutputStream::GetCpuMove
    ///
    /// Retreives last move that has been put on the board.
    ///
    /// @par Full Description
    /// Retreives last move that has been put on the board.
    ///
    /// @param cpuReply  Data received from process.
    ///////////////////////////////////////////////////////////////////////
    LastMove GetCpuMove( const QString& data );

    ///////////////////////////////////////////////////////////////////////
    /// METHOD NAME: GomokuOutputStream::GetWinnerMovies
    ///
    /// Retreives whole five movies that stat five in row.
    ///
    /// @par Full Description
    /// @param data             Backend cpu msg.
    /// @param rGomokuExeMsg    Container where winning movies will be put.
    ///
    /// @param cpuReply  Data received from backedn.
    ///////////////////////////////////////////////////////////////////////
    void GetWinnerMovies( const QString& data, GomokuExeMsg& rGomokuExeMsg );

    // Exteral process message.
    GomokuExeMsg m_RecentMsg;

    // Periodically checks stream for input data.
    QTimer m_Timer;

    // Playing sound.
    QSoundEffect m_HumanMoveSound;
    QSoundEffect m_CpuMoveSound;
    QSoundEffect m_CpuWonSound;
    QSoundEffect m_HumanWonSound;
};

#endif // GOMOKUOUTPUTSTREAM_H

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
