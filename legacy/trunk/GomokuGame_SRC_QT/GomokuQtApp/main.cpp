/////////////////////////////////////////////////////////////////////////////////////////
/// @file main.cpp
///
/// Runs Gomoku game android application.
///
/// @par Full Description.
/// Runs Gomoku game android application.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 4-Apr-2017 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QQuickView>
#include <QQmlContext>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GomokuBackEnd.h"
#include "GomokuInputStream.h"
#include "GomokuOutputStream.h"

// FORWARD REFERENCES
// <none>

int main( int argc, char *argv[] )
{
    QGuiApplication app( argc, argv );
    QQmlApplicationEngine engine;

    // Validate screen resolution.
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    const bool isScreenOK = ( 0.7 * height ) > ( 0.9 * width );
    if( !isScreenOK )
    {
        qDebug() << "Screen resolution not valid:[ h:" <<height<< " w:" <<width << " ]";
        // todo: sent msg to GUI to inform user and display fail screen.
    }

    // Parameters into Gomoku Game algorythm.
    const uint32_t boardSize = 19;
    const bool isRandomize = false;
    const uint32_t maxTime = 0;
    const char* pHumanColor = "o";
    uint32_t gameLevel = 3;
    GomokuInputStream gomokuInputStream;
    GomokuOutputStream gomokuOutputStream;

    // Register parameters into qml engine, so that will be avaliable in qml files.
    engine.rootContext()->setContextProperty( "gomokuInputStream", &gomokuInputStream );
    engine.rootContext()->setContextProperty( "gomokuOutputStream", &gomokuOutputStream );

    GomokuBackEnd gomokuBackEnd;
    gomokuBackEnd.Init( boardSize,
                         pHumanColor,
                         gameLevel,
                         isRandomize,
                         maxTime,
                         gomokuInputStream,
                         gomokuOutputStream );
    gomokuBackEnd.start();

    engine.load( QUrl( QStringLiteral( "qrc:/main.qml" ) ) );
    return app.exec();
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
