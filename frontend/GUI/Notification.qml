import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.0

Rectangle {
    id: notificationId

    width:          parent.width
    height:         parent.height
    color:          "black"
    border.color:   "#17a81a"
    border.width:   5
    radius:         10
    opacity:        0.75
    visible:        false

    // Signals:
    signal resetBoardInstance()

    // Catch any mouse activity.
    MouseArea {
        anchors.fill: parent
        // nothing to do
    }

    Button {
        id: notificationButtonId

        text: "note"
        anchors.centerIn: parent

        contentItem: Text {
            text: notificationButtonId.text
            //font: notificationButtonId.font
            font.pointSize: 18
            opacity: enabled ? 1.0 : 0.3
            color: notificationButtonId.down ? "#17a81a" : "#21be2b"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 40
            color: "black"
            opacity: enabled ? 1 : 0.3
            border.color: notificationButtonId.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }

        onClicked: {
            console.log("qml: dbg::Notification:: Human has read message.")

            // Inform C++ backend about human move.
            gomokuInputStream.frontendeventhumanmsg( "\n--->>NewGame.\n" )
            notificationId.visible = false

            // Emit signal.
            resetBoardInstance()
        }
    }

    function onShowNotificationMsg( msg )
    {
        notificationButtonId.text = msg
        notificationId.visible = true
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
