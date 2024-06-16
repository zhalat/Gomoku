import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
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

    Rectangle {
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
        property int longerEdge:        ((hView > wView) ? hView:wView)
        property int shortenEdge:       ((hView > wView) ? wView:hView)
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
        Flickable {
            id: flick
            anchors.fill: parent
            clip: true
            contentWidth: 1*realGomokuBoard.width; contentHeight: 1.5*realGomokuBoard.height

            property alias realGomokuBoardAlias: realGomokuBoard
            GomokuBoard
            {
                id: realGomokuBoard
                screenSize: Math.max(gomokuBoardWindow.wView, gomokuBoardWindow.hView)
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
           incTextCase: "human"
           initText: "Your Score: 0/0"
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
           incTextCase: "cpu"
           initText: "AI Score: 0/0"
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
        gomokuBoardWindow.flickAlias.realGomokuBoardAlias.hotMoveUp.connect( goButton.onHotMoveUp )
        gomokuBoardWindow.flickAlias.realGomokuBoardAlias.hotMoveDown.connect( goButton.onHotMoveDown )
        gomokuBoardWindow.flickAlias.realGomokuBoardAlias.cpuReplyReceived.connect( goButton.onCpuReplyReceived )
        // b. Connect goButton event to human reply function.
        goButton.goButtonSt2IdAlias.goButtonMouseAreaIdAlias.clicked.connect( gomokuBoardWindow.flickAlias.realGomokuBoardAlias.humanReply )
        // c. Connect game over signal to notification object (gloabalNotificationId).
        gomokuBoardWindow.flickAlias.realGomokuBoardAlias.showNotificationMsg.connect( gloabalNotificationId.onShowNotificationMsg )
        // d. Connect notification restart event to function restarting GUI.
        gloabalNotificationId.playOrNotClicked.connect( gomokuBoardWindow.flickAlias.realGomokuBoardAlias.onResetBoardInstance );
        gloabalNotificationId.playOrNotClicked.connect( goButton.onResetInstance )
        // e. Connect game over notyfication to score human & AI
        gomokuBoardWindow.flickAlias.realGomokuBoardAlias.scoreUp.connect(yourScoreSt1Id.onScoreUp)
        gomokuBoardWindow.flickAlias.realGomokuBoardAlias.scoreUp.connect(aiScoreSt1Id.onScoreUp)
    }
}
