import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: yourScoreSt1Id

    color                     : "transparent"
    width                     : 0
    height                    : 0
    property int allSets      : 0
    property int score        : 0
    property var incTextCase  : ""
    property var initText     : ""

    property alias yourScoreSt2IdAlias: yourScoreSt2Id
    Rectangle
    {
        id: yourScoreSt2Id

        anchors.centerIn: parent
        width           : 0.95*parent.width
        height          : 0.8*parent.height
        radius          : 20
        border.width    : 3
        border.color    : "black"
        gradient: Gradient {
            GradientStop { position: 0.0; color: "gray" }
            GradientStop { position: 1.0; color: "black" }
        }

        Text {
            id: yourScoreSt2TextId

            text: "NULL"
            anchors.centerIn: parent

            font.pointSize: 14;
            font.bold: false
            color: "white"
        }

        function setText( msg )
        {
            yourScoreSt2TextId.text = msg
        }
    }

    // Constructor.
    Component.onCompleted: {
        yourScoreSt2IdAlias.setText(initText)
    }

    function onScoreUp(msg)
    {
        if( msg == incTextCase )
        {
            score = score + 1
        }

        allSets = allSets + 1
        var split1 = initText.split(":")
        var newMessage = split1[0] + ":" + score + "/" + allSets
        console.log(newMessage)

        yourScoreSt2Id.setText( newMessage )
    }
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

