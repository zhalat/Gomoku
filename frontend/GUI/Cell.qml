import QtQuick 2.5
import QtMultimedia 5.7

Rectangle {
    id: cell
    objectName  : "qmlCell"
    //anchors.fill: parent

    // Properties.
    property bool isVacant          : true
    property bool isRedBallMark     : false
    property bool isExcited         : false
    property bool isHot             : false
    property color idleColor        : "grey"
    property string imgExcited      : "Images/markedFields/excited.gif"
    property string imgHot          : "Images/markedFields/excited.gif"
    property real borderIdleSize    : 0
    property real borderActiveSize  : 3
    property real cellSizeW         : 0 //Initial size. To be modyfied by constructor.
    property real cellSizeH         : 0 //Initial size. To be modyfied by constructor.
    property string backgroundImg   : ""
    property string balckBallImg    : ""
    property string whiteBallImg    : ""
    width                           : cellSizeW
    height                          : cellSizeH
    color                           : idleColor
    border.width                    : borderIdleSize
    border.color                    : idleColor

    // Positions (x,y) on the grid. Set to invalid initial position.
    property int posX: -1
    property int posY: -1

    // Signals:
    signal cellClicked( real xpos, real ypos )

    Image {
        id: cellImage

        width   : cell.width
        height  : cell.height
        fillMode: Image.Stretch
    }

    MouseArea {
        id: cellMouseArea

        anchors.fill: parent
        scrollGestureEnabled: false  // 2-finger-flick gesture should pass through to the Flickable

        onEntered: {
            // Field must be empty and clickable (no frame field)
            if(isVacant && !isHot && posX!=-1 && posY!=-1)
            {
                exciteState()
            }
        }

        onClicked: {
            // Field must be empty and clickable (no frame field)
            if(isVacant && posX!=-1 && posY!=-1)
            {
                cellClicked(posX, posY)
            }
        }
    }

    Timer {
        id: cellTimer

        interval: 1000
        running:  false
        repeat:   false

        onTriggered: {
            parent.defaultState()
        }
    }

    // Object constructor.
    Component.onCompleted: {
        // Signal connections:
        cellClicked.connect(realGomokuBoard.onCellClicked)
        if(backgroundImg!="")
        {
            cellImage.source = backgroundImg
        }
    }

    // Methods:

    // Revert instance to initial state.
    function resetInstance()
    {
        isVacant = true
        isRedBallMark = false
        isExcited = false
        isHot = false
        cellImage.source = backgroundImg
    }

    // Go to default state.
    function defaultState()
    {
        console.log("qml: dbg::Cell 'Default state' ")
        if( isExcited )
        {
            cellImage.source = backgroundImg
            cell.border.color = cell.idleColor
            cell.border.width = cell.borderIdleSize
            isExcited = false
        }
    }

    // Go to excite state.
    function exciteState()
    {
       console.log("qml: dbg::Cell 'Excite state' ")
       cellImage.source = imgExcited
       isExcited = true
       isHot = false
       cellTimer.start()
    }

    // Go to hot state.
    function setHotState()
    {
        console.log("qml: dbg::Cell 'Hot state' ")
        cellImage.source = imgHot
        isHot = true
        isExcited = false
    }

    // Go to hot state.
    function resetHotState()
    {
        console.log("qml: dbg::Cell 'Rst hot state' ")
        cellImage.source = backgroundImg
        isHot = false
    }

    // Put ball image into cell.
    function setBall( isWhite )
    {
        if( true == isRedBallMark || true == isVacant )
        {
            isRedBallMark = false
            isVacant = false
            if( isWhite )
            {
                cellImage.source = "Images/white50.gif"
            }
            else
            {
                cellImage.source = "Images/black50.gif"
            }
        }
        else
        {
            console.log("qml: dbg::Cell 'ERROR - Trying to set not vacant cell' ")
        }
    }

    // Put ball image into cell.
    function setBallRedDot( isWhite )
    {
        if( true == isVacant )
        {
            isVacant = false
            isRedBallMark = true
            if( isWhite )
            {
                cellImage.source = "Images/white50RedMark.gif"
            }
            else
            {
                cellImage.source = "Images/black50Redmark.gif"
            }
        }
        else
        {
            console.log("qml: dbg::Cell 'ERROR - Trying to set not vacant cell' ")
        }
    }

    // Put winner ball image into cell.
    function setWinnerBall()
    {
        if( true != isVacant )
        {
            cellImage.source = "Images/red50.gif"
        }
        else
        {
            console.log("qml: dbg::Cell 'ERROR - Trying to set not vacant cell' ")
        }
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
