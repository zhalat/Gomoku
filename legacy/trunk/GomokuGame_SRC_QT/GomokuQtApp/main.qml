import QtQuick 2.5
import QtQuick.Window 2.2

Window
{
    id: root
    title: qsTr("Gomoku HalSoft")

    visible: true
    color: "white"

    Image {
        id: wallpaper

        width   : parent.width
        height  : parent.height
        fillMode: Image.Stretch
        source  : "Images/mainBackGroundBlack.jpg"
    }

    // Flickable playing board.
    Rectangle
    {
        id: gomokuBoardWindow

        // Define margins:
        property real topMarginPercent:    (12/100)
        property real bottomMarginPercent: (12/100)
        property real leftMarginPercent:   (0/100)
        property real rightMarginPercent:  (0/100)

        // Compute positionign & size.
        property int topMarginSize:     (topMarginPercent * parent.height)
        property int bottomMarginSize:  (topMarginPercent * parent.height)
        property int leftMarginSize:    (leftMarginPercent * parent.width)
        property int rightMarginSize:   (rightMarginPercent * parent.width)
        property int wView:             (parent.width - leftMarginSize - rightMarginSize)
        property int hView:             (parent.height - topMarginSize - bottomMarginSize)
        property int longView:          ((hView > wView) ? hView:wView)
        property int posX:              (leftMarginSize)
        property int posY:              (topMarginSize)

        // Real gomoku board initial size. Shall be square.
        property real realGomokuBoardSize:    1085
        property real minrealGomokuBoardSizeScale: (longView/realGomokuBoardSize)

        // Anchor itme on the window.
        width:  wView
        height: hView
        x:      posX
        y:      posY

        // Set color or wallpapper.
        color: "transparent"

        property alias flickAlias: flick
        Flickable
        {
            id: flick
            anchors.fill: parent
            contentWidth: gomokuBoardWindow.realGomokuBoardSize
            contentHeight: gomokuBoardWindow.realGomokuBoardSize
            clip: true

            property alias pinchAlias: pinch
            PinchArea
            {
                id: pinch
                width: Math.max(flick.contentWidth, flick.width)
                height: Math.max(flick.contentHeight, flick.height)
                pinch.minimumRotation : 0
                pinch.maximumRotation : 0
                property bool isScaleAllowed: true
                property real initialWidth
                property real initialHeight

                //----------------Start::Events handlers------------
                onPinchStarted: {
                    initialWidth = flick.contentWidth
                    initialHeight = flick.contentHeight
                }

                onPinchUpdated: {
                    isScaleAllowed = !(initialWidth * pinch.scale < gomokuBoardWindow.longView)
                    if( isScaleAllowed )
                    {
                        // adjust content pos due to drag
                        flick.contentX += pinch.previousCenter.x - pinch.center.x
                        flick.contentY += pinch.previousCenter.y - pinch.center.y

                        // Resize. If you are close (15%) to minimal scale use magnetic.
                        var isMagnetic = (initialWidth * pinch.scale/gomokuBoardWindow.longView) < 1.15
                        if(isMagnetic)
                        {
                            flick.resizeContent( gomokuBoardWindow.minrealGomokuBoardSizeScale * gomokuBoardWindow.realGomokuBoardSize, gomokuBoardWindow.longView, pinch.center)
                        }
                        else
                        {
                            flick.resizeContent(initialWidth * pinch.scale, initialHeight * pinch.scale, pinch.center)
                        }
                    }
                }

                onPinchFinished: {
                    // Move its content within bounds.
                    flick.returnToBounds()
                }
                //----------------End::Events handlers------------

                property alias realGomokuBoardWindowAlias: realGomokuBoardWindow
                Rectangle
                {
                    id: realGomokuBoardWindow
                    width: flick.contentWidth
                    height: flick.contentHeight
                    color: "transparent"

                    // Real gomoku board.
                    property alias realGomokuBoardAlias:realGomokuBoard
                    GomokuBoard
                    {
                        id: realGomokuBoard
                    }
                }
            }
        }
    }

    // Get info about top margin. It depends on gomokuBoardWindow.
    property real rootTopMarginPercent   : (2/100)
    property real rootTopMarginSize      : (rootTopMarginPercent*height)
    property real rootTopBarPercent      : (90/100)
    property real rootTopBarSize         : ((gomokuBoardWindow.topMarginSize-rootTopMarginSize)*rootTopBarPercent)
    property real rootTopMarginWSize     : (gomokuBoardWindow.width)

    // Get info about bottom margin. It depends on gomokuBoardWindow.
    property int rootBottomMarginWSize  : (gomokuBoardWindow.width)
    property int rootBottomMarginHSize  : (gomokuBoardWindow.bottomMarginSize)
    property int rootBottomHStart       : (gomokuBoardWindow.posY+gomokuBoardWindow.height)
    property int rootBottomHEnd         : (gomokuBoardWindow.posY+gomokuBoardWindow.width+gomokuBoardWindow.bottomMarginSize)
    property real distanceBottomPercent : (0/100)
    property real distanceBottomSize    : (distanceBottomPercent*gomokuBoardWindow.bottomMarginSize)

    // Bottom grind shape.
    property real gridCellWSize         : (rootBottomMarginWSize/3)
    property real gridCellHSize         : (rootBottomMarginHSize-2*distanceBottomSize)
    property real bottomLineSize        : 1

    // Top bar.   
    TopBar
    {
        width           : rootTopMarginWSize
        height          : rootTopBarSize
        fullWindowW     : parent.width
        fullWindowH     : parent.height
    }

    //Top bar line.
    Rectangle
    {
        id: topBarLine

        width        : rootTopMarginWSize
        height       : 1
        border.width : 1
        border.color : "black"
        color        : "transparent"
        y            : gomokuBoardWindow.topMarginSize
    }

    // Bottom bar line
    Rectangle
    {
        id: bottomBarLine

        width           : (rootBottomMarginWSize)
        height          : (bottomLineSize)
        border.width    : 1
        border.color    : "black"
        color           : "transparent"
        y               : (rootBottomHStart+distanceBottomSize)
    }

    // Bottom buttons.
    Grid
    {
        id: bottomRootGrid

        columns   : 3
        rows      : 1
        spacing   : 0
        y         : (rootBottomHStart+distanceBottomSize+bottomLineSize)

        Score
        {  id: yourScoreSt1Id
           width: gridCellWSize
           height: gridCellHSize
           incTextCase: gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.humanWonNotyfication
           initText: "Your Score: 0/0" // Must be ":" in this string! See score.qml
        }

        GoButton
        { id: goButton;
          width: gridCellWSize
          height: gridCellHSize
        }

        Score
        {  id: aiScoreSt1Id
           width: gridCellWSize
           height: gridCellHSize
           incTextCase: gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.cpuWonNotyfication
           initText: "AI Score: 0/0" // Must be ":" in this string! See score.qml
        }
    }

    // Global notifications.
    Notification
    {
        id: gloabalNotificationId
    }

    // Constructor.
    Component.onCompleted: {
        // Signal connections.
        // a. Enable goButton when user set any cell.
        gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.hotMoveUp.connect( goButton.onHotMoveUp )
        gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.hotMoveDown.connect( goButton.onHotMoveDown )
        gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.cpuReplyReceived.connect( goButton.onCpuReplyReceived )
        // b. Connect goButton event to human reply function.
        goButton.goButtonSt2IdAlias.goButtonMouseAreaIdAlias.clicked.connect( gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.humanReply )
        // c. Connect game over signal to notification object (gloabalNotificationId).
        gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.showNotificationMsg.connect( gloabalNotificationId.onShowNotificationMsg )
        // d. Connect notification restart event to function restarting GUI.
        gloabalNotificationId.resetBoardInstance.connect( gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.onResetBoardInstance );
        gloabalNotificationId.resetBoardInstance.connect( goButton.onResetInstance )
        // e. Connect game over notyfication to score human & AI
        gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.showNotificationMsg.connect(yourScoreSt1Id.onShowNotificationMsg)
        gomokuBoardWindow.flickAlias.pinchAlias.realGomokuBoardWindowAlias.realGomokuBoardAlias.showNotificationMsg.connect(aiScoreSt1Id.onShowNotificationMsg)
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
