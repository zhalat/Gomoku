/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuOutputStream.cpp
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

// SYSTEM INCLUDES
#include <QThread>
#include <QDebug>
#include <QRegularExpression>
#include <assert.h>
#include <iostream>
#include <sstream>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GomokuOutputStream.h"

// FORWARD REFERENCES
// <none>

// Usefull definitions.
QString TERMINATOR_MSG           ( "##" );
QString WINNER_MSG               ( "--->>Game over. You won." );
QString LOOSER_MSG               ( "--->>Game over. Computer won." );
QString STALEMATE_MSG            ( "--->>Game over. Stalemate." );
QString CHOOSING_COLOR_MSG       ( "--->>Choose your color: x or o." );
QString YOUR_MOVE_MSG            ( "--->>Your move:" );
QString LAST_CPU_MOVE_MSG        ( "--->>Last cpu move:" );
QString LAST_HUMAN_MOVE_MSG      ( "--->>Last human move:" );
QString INVALID_MOVE_MSG         ( "!--->>Invalid move." );
QString INVALID_PARAMETER_MSG    ( "!--->>Invalid parameter." );
QString NEW_LINE                 ( "\\n" );
QString WINNER_MOVIES_MARK       ( "w" );

// Arguments passes to run exec.
const GomokuOutputStream::LastMove GomokuOutputStream::MOVE_INVALID = LastMove( 0, 0, false );

// Time out for timer.
const uint32_t GomokuOutputStream::TIMEOUT = 500;

/// Default Constructor.
GomokuOutputStream::GomokuOutputStream()
 : std::ostringstream()
 , m_RecentMsg( EVENT_NONE, false, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID )
{
    // Clear the stream.
    this->str("");
    this->clear();

    // Connect timer event to slot.
    connect( &m_Timer, SIGNAL( timeout() ), this, SLOT( onTimeout() ) );
    m_Timer.start( TIMEOUT );

    m_CpuMoveSound.setSource(QUrl("qrc:/Sound/yourMove.wav"));
    m_HumanMoveSound.setSource(QUrl("qrc:/Sound/pcMove.wav"));
	m_CpuWonSound.setSource(QUrl("qrc:/Sound/youLost.wav"));
	m_HumanWonSound.setSource(QUrl("qrc:/Sound/youWon.wav"));
}

/// Capture a timer expire event.
void GomokuOutputStream::onTimeout()
{
    static std::string cpuRepy;
    cpuRepy += this->str();

    // Clear the stream.
    this->str("");
    this->clear();

    const bool status = Dispatcher( QString::fromStdString( cpuRepy ) );
    if( status )
    {
        std::ostringstream ostream;
        std::string str;

        switch( m_RecentMsg.m_Event )
        {
        case CPU_MOVE:
            qDebug() << "c++: dbg::GUI<-BackEND:: Event Type:[" << m_RecentMsg.m_Event << "]. Data: " << "(" << m_RecentMsg.m_Move.m_x << ", " << m_RecentMsg.m_Move.m_y << ")";
            m_CpuMoveSound.play();

            ostream<<m_RecentMsg.m_Event<<"\n"<<m_RecentMsg.m_Move.m_x<<"\n"<<m_RecentMsg.m_Move.m_y<<"\n";
            str = ostream.str();
            emit backendevent( QString::fromStdString(str) );
            break;

        case CPU_WON:
            qDebug() << "c++: dbg::GUI<-BackEND:: Event Type:[" << m_RecentMsg.m_Event << "]";
			m_CpuWonSound.play();

            ostream<<m_RecentMsg.m_Event<<"\n"<<m_RecentMsg.m_Move.m_x<<"\n"<<m_RecentMsg.m_Move.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove1.m_x<<"\n"<<m_RecentMsg.m_WinningMove1.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove2.m_x<<"\n"<<m_RecentMsg.m_WinningMove2.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove3.m_x<<"\n"<<m_RecentMsg.m_WinningMove3.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove4.m_x<<"\n"<<m_RecentMsg.m_WinningMove4.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove5.m_x<<"\n"<<m_RecentMsg.m_WinningMove5.m_y<<"\n";
            str = ostream.str();
            emit backendevent( QString::fromStdString(str) );

            break;
        case HUMAN_WON:
            qDebug() << "c++: dbg::GUI<-BackEND:: Event Type:[" << m_RecentMsg.m_Event << "]";
			m_HumanWonSound.play();

            ostream<<m_RecentMsg.m_Event<<"\n"<<m_RecentMsg.m_Move.m_x<<"\n"<<m_RecentMsg.m_Move.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove1.m_x<<"\n"<<m_RecentMsg.m_WinningMove1.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove2.m_x<<"\n"<<m_RecentMsg.m_WinningMove2.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove3.m_x<<"\n"<<m_RecentMsg.m_WinningMove3.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove4.m_x<<"\n"<<m_RecentMsg.m_WinningMove4.m_y<<"\n";
            ostream<<m_RecentMsg.m_WinningMove5.m_x<<"\n"<<m_RecentMsg.m_WinningMove5.m_y<<"\n";
            str = ostream.str();
            emit backendevent( QString::fromStdString(str) );

            break;
        case HUMAN_MOVE:
            qDebug() << "c++: dbg::GUI->BackEND:: Event Type:[" << m_RecentMsg.m_Event << "]" << "accepted";
            m_HumanMoveSound.play();
            break;
        default:
            qDebug() << "c++: dbg::GUI<-BackEND:: Event Type:[" << m_RecentMsg.m_Event << "]";
            break;
        }

        // Message has been got. Clear buffers.
        cpuRepy.clear();
        ostream.clear();
        str.clear();
    }
}

/// Parse data received from external exec process.
bool GomokuOutputStream::Dispatcher( const QString& cpuReply )
{
    bool retVal = false;
    GomokuExeMsg gomokuExeMsg( EVENT_NONE, false, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID, MOVE_INVALID );

    // Check what kind of message was being sent.
    bool isEnd = false;
    Event eventSM = HUMAN_WON;
    QRegularExpression re;

    for( ; !isEnd; )
    {
        switch( eventSM )
        {

        case HUMAN_WON:
        {
            re.setPattern( WINNER_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );

            if( matchResult.hasMatch() )
            {
                gomokuExeMsg.m_Event = HUMAN_WON;
                // Get the winning movies
                GetWinnerMovies( cpuReply, gomokuExeMsg );
                isEnd = true;
            }
            else
            {
                eventSM = CPU_WON;
            }

            break;
        }

        case CPU_WON:
        {
            re.setPattern( LOOSER_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );

            if( matchResult.hasMatch() )
            {
                gomokuExeMsg.m_Event = CPU_WON;

                // Get the winning movies
                GetWinnerMovies( cpuReply, gomokuExeMsg );

                // There is need to get last cpu move.
                gomokuExeMsg.m_Pending = true;
                eventSM = CPU_MOVE;
            }
            else
            {
                eventSM = STALEMATE;
            }
            break;
        }

        case STALEMATE:
        {
            re.setPattern( STALEMATE_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );
            if( matchResult.hasMatch() )
            {
                gomokuExeMsg.m_Event = STALEMATE;
                isEnd = true;
            }
            else
            {
                eventSM = CHOOSE_COLOR;
            }
            break;
        }

        case CHOOSE_COLOR:
        {
            re.setPattern( CHOOSING_COLOR_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );
            if( matchResult.hasMatch() )
            {
                gomokuExeMsg.m_Event = CHOOSE_COLOR;
                isEnd = true;
            }
            else
            {
                eventSM = CPU_MOVE;
            }
            break;
        }

        case CPU_MOVE:
        {
            re.setPattern( LAST_CPU_MOVE_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );
            if( matchResult.hasMatch() )
            {
                if( gomokuExeMsg.m_Pending )
                {
                    // Cpu won. Provide only winning move.
                    gomokuExeMsg.m_Pending = false;
                }
                else
                {
                    gomokuExeMsg.m_Event = CPU_MOVE;
                }

                gomokuExeMsg.m_Move = GetCpuMove( cpuReply );
                assert( gomokuExeMsg.m_Move.m_IsValid );

                isEnd = true;
            }
            else
            {
                eventSM = HUMAN_MOVE;
            }
            break;
        }

        case HUMAN_MOVE:
        {
            re.setPattern( LAST_HUMAN_MOVE_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );
            if( matchResult.hasMatch() )
            {
                // This is an echo. Skip rereiving the move.
                gomokuExeMsg.m_Event = HUMAN_MOVE;
                isEnd = true;
            }
            else
            {
                eventSM = INVALID_USER_MOVE;
            }
            break;
        }

        case INVALID_USER_MOVE:
        {
            re.setPattern( INVALID_MOVE_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );
            if( matchResult.hasMatch() )
            {
                gomokuExeMsg.m_Event = INVALID_USER_MOVE;
                isEnd = true;
            }
            else
            {
                eventSM = INVALID_PARAMETER;
            }
            break;
        }

        case INVALID_PARAMETER:
        {
            re.setPattern( INVALID_PARAMETER_MSG );
            const QRegularExpressionMatch matchResult = re.match( cpuReply );
            if( matchResult.hasMatch() )
            {
                gomokuExeMsg.m_Event = INVALID_PARAMETER;
            }
            isEnd = true;

            break;
        }

        }
    }

    m_RecentMsg = gomokuExeMsg;

    retVal = ( ( gomokuExeMsg.m_Event != EVENT_NONE ) && ( !gomokuExeMsg.m_Pending ) );
    return retVal;
}

/// Retreives last move that has been put on the board.
GomokuOutputStream::LastMove GomokuOutputStream::GetCpuMove(const QString& data )
{
    // Regular expression that helps to find last move.
    static const QString lastMoveReLine = LAST_CPU_MOVE_MSG + NEW_LINE + "(\\()+[0-9]+(, )+[0-9]+(\\))";
    static const QString onlyDigits = "(\\d+)";
    const uint32_t expectedCapturedNumber = 1;
    LastMove retVal( MOVE_INVALID );

    // Get whole line which contains 'lastMoveReLine' pattern.
    QRegularExpression reLine( lastMoveReLine );
    QRegularExpressionMatchIterator lastMoveIter = reLine.globalMatch( data );

    // Put the result into list.
    QList<QString> reResults;
    while ( lastMoveIter.hasNext() )
    {
        const QRegularExpressionMatch match = lastMoveIter.next();

        #warning "Check how works regular expression in qt."
        reResults << match.captured( 0 );
    }

    const uint32_t reResultsSize = reResults.size();

    assert( expectedCapturedNumber == reResultsSize );

    const QString lastMoveLine = reResults[ 0 ];

    QRegularExpression re( onlyDigits );
    QRegularExpressionMatchIterator digitIter = re.globalMatch( lastMoveLine );

    const uint32_t expectedDigitsFound = 2;
    for( uint32_t i = 0; i < expectedDigitsFound; ++i )
    {
        const QRegularExpressionMatch match = digitIter.next();
        const QString data =  match.captured( 1 );

        const bool isX = ( 0 == i );
        const bool isY = ( 1 == i );

        if( isX )
        {
            retVal.m_x = data.toShort() ;
        }
        else if( isY )
        {
            retVal.m_y = data.toShort() ;
            retVal.m_IsValid = true;
        }
        else
        {
            assert( false );
        }
    }

    return retVal;
}

void GomokuOutputStream::GetWinnerMovies( const QString& data, GomokuExeMsg& rGomokuExeMsg )
{
    // Regular expression that helps to find last move.
    static const QString winnerMoviesReLine = WINNER_MOVIES_MARK + "(\\()+[0-9]+(, )+[0-9]+(\\))";
    static const QString onlyDigits     = "(\\d+)";

    // Get whole line which contains 'winnerMoviesReLine' pattern.
    QRegularExpression winnerReLine( winnerMoviesReLine );
    QRegularExpressionMatchIterator winnerMoveIter = winnerReLine.globalMatch( data );

    // Put the result into list.
    const uint32_t expectedResultsFound = 5;
    uint32_t counter = 0;
    QString reResults;

    while ( winnerMoveIter.hasNext() )
    {
        //1. Set regular expression and get the x, y digits (x ,y) digits.
        const QRegularExpressionMatch match = winnerMoveIter.next();
        reResults = match.captured( 0 );

        QRegularExpression digitsRe( onlyDigits );
        QRegularExpressionMatchIterator digitIter = digitsRe.globalMatch( reResults );

        const uint32_t expectedDigitsFound = 2;
        uint32_t xx = 0;
        uint32_t yy = 0;
        for( uint32_t i = 0; i < expectedDigitsFound; ++i )
        {
            const QRegularExpressionMatch match = digitIter.next();
            const QString data =  match.captured( 1 );

            const bool isX = ( 0 == i );
            const bool isY = ( 1 == i );

            if( isX )
            {
                xx = data.toShort() ;
            }
            else if( isY )
            {
                yy = data.toShort() ;
            }
            else
            {
                assert( false );
            }
        }

        // 2. Put digits to output message.
        if( 0==counter )
        {
            rGomokuExeMsg.m_WinningMove1.m_x = xx;
            rGomokuExeMsg.m_WinningMove1.m_y = yy;
        }
        else if( 1==counter )
        {
            rGomokuExeMsg.m_WinningMove2.m_x = xx;
            rGomokuExeMsg.m_WinningMove2.m_y = yy;
        }
        else if( 2==counter )
        {
            rGomokuExeMsg.m_WinningMove3.m_x = xx;
            rGomokuExeMsg.m_WinningMove3.m_y = yy;
        }
        else if( 3==counter )
        {
            rGomokuExeMsg.m_WinningMove4.m_x = xx;
            rGomokuExeMsg.m_WinningMove4.m_y = yy;
        }
        else if( 4==counter )
        {
            rGomokuExeMsg.m_WinningMove5.m_x = xx;
            rGomokuExeMsg.m_WinningMove5.m_y = yy;
        }
        else
        {
            assert( false );
        }

        reResults.clear();
        counter++;
    }

    assert( counter == expectedResultsFound );
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
