import QtQuick 2.5
import QtQuick.Window 2.1
import QtMultimedia 5.0

Rectangle {
    id          : realGomokuBoard
    objectName  : "qmlRealGomokuBoard"

    //anchors.fill: parent

    property int realGomokuBoardSize      : (19)
    property real workingArea             : (parent.width-(gridSpacingSize*(realGomokuBoardSize+2-1))) // due to 2xframe
    property real cellBoardFrameHPercent  : (2.95/100)
    property real cellBoardFrameHSize     : (cellBoardFrameHPercent*workingArea)
    property real cellInteriorSize        : ((workingArea-2*cellBoardFrameHSize)/realGomokuBoardSize)
    property real cellBoardFrameWSize     : cellInteriorSize
    property int gridSpacingSize          : (1)
    property color realGomokuBoardBackgroundColor: ("black")
    property bool isUserWhite             : (false)
    property var currentHotCell           : { "posx": -1, "posy": -1 }
    property var previousHotCell          : { "posx": -1, "posy": -1 }
    property var redDotBallIndex          : (-1)
    property var humanWonNotyfication     : "You_Won!"
    property var cpuWonNotyfication       : "AI_Won"
    width                                 : (parent.width)
    height                                : (parent.width)
    color                                 : (realGomokuBoardBackgroundColor)

    // Signals:
    signal hotMoveUp()                      // Emits when user set pretended move.
    signal hotMoveDown()                    // Emits when user accepts pretended move (no move selected on board any more - set ball)
    signal cpuReplyReceived()               // Emits when cpu put move.
    signal showNotificationMsg( string msg) // Emits when cpu/human won.

    // Handle BACKEND -> GUI signals.
    Connections {
        target: gomokuGameServerGUI // class must be defined in C++ and registered by setContextProperty()
        onBackendevent_restart : onBackendevent_restart()
        onBackendevent_human_won : onBackendevent_human_won(positions)
        onBackendevent_cpu_won : onBackendevent_cpu_won(positions)
        onBackendevent_stalemate : onBackendevent_stalemate()
        onBackendevent_cpu_move : onBackendevent_cpu_move(cpuRow,cpuColumn)
        onBackendevent_human_move_invalid : onBackendevent_human_move_invalid()
    }

    Grid {
            id                          : realGomokuBoardGrid
            property int gridSize       : realGomokuBoardSize +2 //due to 2xframe
            spacing                     : gridSpacingSize
            rows                        : gridSize
            columns                     : gridSize

            // row frame top:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/corner_top_left.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_01.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_02.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_03.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_04.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_05.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_06.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_07.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_08.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_09.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_10.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_11.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_12.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_13.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_14.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_15.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_16.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_17.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_18.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_top_19.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/corner_top_right.gif"}
            // row 0:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_01.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:0; backgroundImg: "Images/boardInterior/interior_01.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:1; backgroundImg: "Images/boardInterior/interior_02.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:2; backgroundImg: "Images/boardInterior/interior_03.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:3; backgroundImg: "Images/boardInterior/interior_04.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:4; backgroundImg: "Images/boardInterior/interior_05.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:5; backgroundImg: "Images/boardInterior/interior_06.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:6; backgroundImg: "Images/boardInterior/interior_07.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:7; backgroundImg: "Images/boardInterior/interior_08.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:8; backgroundImg: "Images/boardInterior/interior_09.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:9; backgroundImg: "Images/boardInterior/interior_10.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:10; backgroundImg: "Images/boardInterior/interior_11.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:11; backgroundImg: "Images/boardInterior/interior_12.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:12; backgroundImg: "Images/boardInterior/interior_13.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:13; backgroundImg: "Images/boardInterior/interior_14.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:14; backgroundImg: "Images/boardInterior/interior_15.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:15; backgroundImg: "Images/boardInterior/interior_16.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:16; backgroundImg: "Images/boardInterior/interior_17.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:17; backgroundImg: "Images/boardInterior/interior_18.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:0; posY:18; backgroundImg: "Images/boardInterior/interior_19.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_01.gif"}
            // row 1:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_02.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:0; backgroundImg: "Images/boardInterior/interior_20.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:1; backgroundImg: "Images/boardInterior/interior_21.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:2; backgroundImg: "Images/boardInterior/interior_22.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:3; backgroundImg: "Images/boardInterior/interior_23.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:4; backgroundImg: "Images/boardInterior/interior_24.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:5; backgroundImg: "Images/boardInterior/interior_25.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:6; backgroundImg: "Images/boardInterior/interior_26.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:7; backgroundImg: "Images/boardInterior/interior_27.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:8; backgroundImg: "Images/boardInterior/interior_28.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:9; backgroundImg: "Images/boardInterior/interior_29.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:10; backgroundImg: "Images/boardInterior/interior_30.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:11; backgroundImg: "Images/boardInterior/interior_31.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:12; backgroundImg: "Images/boardInterior/interior_32.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:13; backgroundImg: "Images/boardInterior/interior_33.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:14; backgroundImg: "Images/boardInterior/interior_34.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:15; backgroundImg: "Images/boardInterior/interior_35.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:16; backgroundImg: "Images/boardInterior/interior_36.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:17; backgroundImg: "Images/boardInterior/interior_37.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:1; posY:18; backgroundImg: "Images/boardInterior/interior_38.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_02.gif"}
            // row 2:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_03.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:0; backgroundImg: "Images/boardInterior/interior_39.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:1; backgroundImg: "Images/boardInterior/interior_40.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:2; backgroundImg: "Images/boardInterior/interior_41.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:3; backgroundImg: "Images/boardInterior/interior_42.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:4; backgroundImg: "Images/boardInterior/interior_43.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:5; backgroundImg: "Images/boardInterior/interior_44.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:6; backgroundImg: "Images/boardInterior/interior_45.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:7; backgroundImg: "Images/boardInterior/interior_46.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:8; backgroundImg: "Images/boardInterior/interior_47.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:9; backgroundImg: "Images/boardInterior/interior_48.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:10; backgroundImg: "Images/boardInterior/interior_49.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:11; backgroundImg: "Images/boardInterior/interior_50.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:12; backgroundImg: "Images/boardInterior/interior_51.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:13; backgroundImg: "Images/boardInterior/interior_52.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:14; backgroundImg: "Images/boardInterior/interior_53.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:15; backgroundImg: "Images/boardInterior/interior_54.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:16; backgroundImg: "Images/boardInterior/interior_55.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:17; backgroundImg: "Images/boardInterior/interior_56.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:2; posY:18; backgroundImg: "Images/boardInterior/interior_57.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_03.gif"}
            // row 3:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_04.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:0; backgroundImg: "Images/boardInterior/interior_58.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:1; backgroundImg: "Images/boardInterior/interior_59.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:2; backgroundImg: "Images/boardInterior/interior_60.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:3; backgroundImg: "Images/boardInterior/interior_61.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:4; backgroundImg: "Images/boardInterior/interior_62.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:5; backgroundImg: "Images/boardInterior/interior_63.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:6; backgroundImg: "Images/boardInterior/interior_64.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:7; backgroundImg: "Images/boardInterior/interior_65.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:8; backgroundImg: "Images/boardInterior/interior_66.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:9; backgroundImg: "Images/boardInterior/interior_67.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:10; backgroundImg: "Images/boardInterior/interior_68.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:11; backgroundImg: "Images/boardInterior/interior_69.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:12; backgroundImg: "Images/boardInterior/interior_70.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:13; backgroundImg: "Images/boardInterior/interior_71.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:14; backgroundImg: "Images/boardInterior/interior_72.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:15; backgroundImg: "Images/boardInterior/interior_73.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:16; backgroundImg: "Images/boardInterior/interior_74.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:17; backgroundImg: "Images/boardInterior/interior_75.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:3; posY:18; backgroundImg: "Images/boardInterior/interior_76.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_04.gif"}
            // row 4:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_05.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:0; backgroundImg: "Images/boardInterior/interior_77.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:1; backgroundImg: "Images/boardInterior/interior_78.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:2; backgroundImg: "Images/boardInterior/interior_79.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:3; backgroundImg: "Images/boardInterior/interior_80.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:4; backgroundImg: "Images/boardInterior/interior_81.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:5; backgroundImg: "Images/boardInterior/interior_82.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:6; backgroundImg: "Images/boardInterior/interior_83.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:7; backgroundImg: "Images/boardInterior/interior_84.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:8; backgroundImg: "Images/boardInterior/interior_85.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:9; backgroundImg: "Images/boardInterior/interior_86.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:10; backgroundImg: "Images/boardInterior/interior_87.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:11; backgroundImg: "Images/boardInterior/interior_88.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:12; backgroundImg: "Images/boardInterior/interior_89.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:13; backgroundImg: "Images/boardInterior/interior_90.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:14; backgroundImg: "Images/boardInterior/interior_91.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:15; backgroundImg: "Images/boardInterior/interior_92.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:16; backgroundImg: "Images/boardInterior/interior_93.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:17; backgroundImg: "Images/boardInterior/interior_94.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:4; posY:18; backgroundImg: "Images/boardInterior/interior_95.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_05.gif"}
            // row 5:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_06.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:0; backgroundImg: "Images/boardInterior/interior_96.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:1; backgroundImg: "Images/boardInterior/interior_97.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:2; backgroundImg: "Images/boardInterior/interior_98.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:3; backgroundImg: "Images/boardInterior/interior_99.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:4; backgroundImg: "Images/boardInterior/interior_100.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:5; backgroundImg: "Images/boardInterior/interior_101.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:6; backgroundImg: "Images/boardInterior/interior_102.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:7; backgroundImg: "Images/boardInterior/interior_103.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:8; backgroundImg: "Images/boardInterior/interior_104.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:9; backgroundImg: "Images/boardInterior/interior_105.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:10; backgroundImg: "Images/boardInterior/interior_106.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:11; backgroundImg: "Images/boardInterior/interior_107.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:12; backgroundImg: "Images/boardInterior/interior_108.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:13; backgroundImg: "Images/boardInterior/interior_109.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:14; backgroundImg: "Images/boardInterior/interior_110.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:15; backgroundImg: "Images/boardInterior/interior_111.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:16; backgroundImg: "Images/boardInterior/interior_112.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:17; backgroundImg: "Images/boardInterior/interior_113.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:5; posY:18; backgroundImg: "Images/boardInterior/interior_114.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_06.gif"}
            // row 6:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_07.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:0; backgroundImg: "Images/boardInterior/interior_115.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:1; backgroundImg: "Images/boardInterior/interior_116.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:2; backgroundImg: "Images/boardInterior/interior_117.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:3; backgroundImg: "Images/boardInterior/interior_118.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:4; backgroundImg: "Images/boardInterior/interior_119.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:5; backgroundImg: "Images/boardInterior/interior_120.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:6; backgroundImg: "Images/boardInterior/interior_121.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:7; backgroundImg: "Images/boardInterior/interior_122.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:8; backgroundImg: "Images/boardInterior/interior_123.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:9; backgroundImg: "Images/boardInterior/interior_124.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:10; backgroundImg: "Images/boardInterior/interior_125.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:11; backgroundImg: "Images/boardInterior/interior_126.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:12; backgroundImg: "Images/boardInterior/interior_127.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:13; backgroundImg: "Images/boardInterior/interior_128.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:14; backgroundImg: "Images/boardInterior/interior_129.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:15; backgroundImg: "Images/boardInterior/interior_130.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:16; backgroundImg: "Images/boardInterior/interior_131.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:17; backgroundImg: "Images/boardInterior/interior_132.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:6; posY:18; backgroundImg: "Images/boardInterior/interior_133.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_07.gif"}
            // row 7:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_08.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:0; backgroundImg: "Images/boardInterior/interior_134.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:1; backgroundImg: "Images/boardInterior/interior_135.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:2; backgroundImg: "Images/boardInterior/interior_136.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:3; backgroundImg: "Images/boardInterior/interior_137.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:4; backgroundImg: "Images/boardInterior/interior_138.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:5; backgroundImg: "Images/boardInterior/interior_139.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:6; backgroundImg: "Images/boardInterior/interior_140.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:7; backgroundImg: "Images/boardInterior/interior_141.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:8; backgroundImg: "Images/boardInterior/interior_142.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:9; backgroundImg: "Images/boardInterior/interior_143.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:10; backgroundImg: "Images/boardInterior/interior_144.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:11; backgroundImg: "Images/boardInterior/interior_145.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:12; backgroundImg: "Images/boardInterior/interior_146.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:13; backgroundImg: "Images/boardInterior/interior_147.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:14; backgroundImg: "Images/boardInterior/interior_148.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:15; backgroundImg: "Images/boardInterior/interior_149.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:16; backgroundImg: "Images/boardInterior/interior_150.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:17; backgroundImg: "Images/boardInterior/interior_151.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:7; posY:18; backgroundImg: "Images/boardInterior/interior_152.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_08.gif"}
            // row 8:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_09.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:0; backgroundImg: "Images/boardInterior/interior_153.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:1; backgroundImg: "Images/boardInterior/interior_154.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:2; backgroundImg: "Images/boardInterior/interior_155.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:3; backgroundImg: "Images/boardInterior/interior_156.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:4; backgroundImg: "Images/boardInterior/interior_157.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:5; backgroundImg: "Images/boardInterior/interior_158.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:6; backgroundImg: "Images/boardInterior/interior_159.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:7; backgroundImg: "Images/boardInterior/interior_160.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:8; backgroundImg: "Images/boardInterior/interior_161.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:9; backgroundImg: "Images/boardInterior/interior_162.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:10; backgroundImg: "Images/boardInterior/interior_163.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:11; backgroundImg: "Images/boardInterior/interior_164.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:12; backgroundImg: "Images/boardInterior/interior_165.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:13; backgroundImg: "Images/boardInterior/interior_166.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:14; backgroundImg: "Images/boardInterior/interior_167.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:15; backgroundImg: "Images/boardInterior/interior_168.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:16; backgroundImg: "Images/boardInterior/interior_169.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:17; backgroundImg: "Images/boardInterior/interior_170.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:8; posY:18; backgroundImg: "Images/boardInterior/interior_171.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_09.gif"}
            // row 9:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_10.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:0; backgroundImg: "Images/boardInterior/interior_172.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:1; backgroundImg: "Images/boardInterior/interior_173.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:2; backgroundImg: "Images/boardInterior/interior_174.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:3; backgroundImg: "Images/boardInterior/interior_175.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:4; backgroundImg: "Images/boardInterior/interior_176.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:5; backgroundImg: "Images/boardInterior/interior_177.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:6; backgroundImg: "Images/boardInterior/interior_178.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:7; backgroundImg: "Images/boardInterior/interior_179.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:8; backgroundImg: "Images/boardInterior/interior_180.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:9; backgroundImg: "Images/boardInterior/interior_181.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:10; backgroundImg: "Images/boardInterior/interior_182.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:11; backgroundImg: "Images/boardInterior/interior_183.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:12; backgroundImg: "Images/boardInterior/interior_184.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:13; backgroundImg: "Images/boardInterior/interior_185.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:14; backgroundImg: "Images/boardInterior/interior_186.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:15; backgroundImg: "Images/boardInterior/interior_187.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:16; backgroundImg: "Images/boardInterior/interior_188.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:17; backgroundImg: "Images/boardInterior/interior_189.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:9; posY:18; backgroundImg: "Images/boardInterior/interior_190.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_10.gif"}
            // row 10:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_11.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:0; backgroundImg: "Images/boardInterior/interior_191.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:1; backgroundImg: "Images/boardInterior/interior_192.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:2; backgroundImg: "Images/boardInterior/interior_193.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:3; backgroundImg: "Images/boardInterior/interior_194.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:4; backgroundImg: "Images/boardInterior/interior_195.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:5; backgroundImg: "Images/boardInterior/interior_196.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:6; backgroundImg: "Images/boardInterior/interior_197.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:7; backgroundImg: "Images/boardInterior/interior_198.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:8; backgroundImg: "Images/boardInterior/interior_199.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:9; backgroundImg: "Images/boardInterior/interior_200.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:10; backgroundImg: "Images/boardInterior/interior_201.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:11; backgroundImg: "Images/boardInterior/interior_202.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:12; backgroundImg: "Images/boardInterior/interior_203.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:13; backgroundImg: "Images/boardInterior/interior_204.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:14; backgroundImg: "Images/boardInterior/interior_205.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:15; backgroundImg: "Images/boardInterior/interior_206.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:16; backgroundImg: "Images/boardInterior/interior_207.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:17; backgroundImg: "Images/boardInterior/interior_208.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:10; posY:18; backgroundImg: "Images/boardInterior/interior_209.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_11.gif"}
            // row 11:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_12.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:0; backgroundImg: "Images/boardInterior/interior_210.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:1; backgroundImg: "Images/boardInterior/interior_211.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:2; backgroundImg: "Images/boardInterior/interior_212.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:3; backgroundImg: "Images/boardInterior/interior_213.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:4; backgroundImg: "Images/boardInterior/interior_214.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:5; backgroundImg: "Images/boardInterior/interior_215.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:6; backgroundImg: "Images/boardInterior/interior_216.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:7; backgroundImg: "Images/boardInterior/interior_217.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:8; backgroundImg: "Images/boardInterior/interior_218.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:9; backgroundImg: "Images/boardInterior/interior_219.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:10; backgroundImg: "Images/boardInterior/interior_220.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:11; backgroundImg: "Images/boardInterior/interior_221.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:12; backgroundImg: "Images/boardInterior/interior_222.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:13; backgroundImg: "Images/boardInterior/interior_223.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:14; backgroundImg: "Images/boardInterior/interior_224.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:15; backgroundImg: "Images/boardInterior/interior_225.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:16; backgroundImg: "Images/boardInterior/interior_226.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:17; backgroundImg: "Images/boardInterior/interior_227.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:11; posY:18; backgroundImg: "Images/boardInterior/interior_228.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_12.gif"}
            // row 12:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_13.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:0; backgroundImg: "Images/boardInterior/interior_229.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:1; backgroundImg: "Images/boardInterior/interior_230.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:2; backgroundImg: "Images/boardInterior/interior_231.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:3; backgroundImg: "Images/boardInterior/interior_232.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:4; backgroundImg: "Images/boardInterior/interior_233.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:5; backgroundImg: "Images/boardInterior/interior_234.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:6; backgroundImg: "Images/boardInterior/interior_235.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:7; backgroundImg: "Images/boardInterior/interior_236.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:8; backgroundImg: "Images/boardInterior/interior_237.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:9; backgroundImg: "Images/boardInterior/interior_238.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:10; backgroundImg: "Images/boardInterior/interior_239.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:11; backgroundImg: "Images/boardInterior/interior_240.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:12; backgroundImg: "Images/boardInterior/interior_241.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:13; backgroundImg: "Images/boardInterior/interior_242.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:14; backgroundImg: "Images/boardInterior/interior_243.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:15; backgroundImg: "Images/boardInterior/interior_244.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:16; backgroundImg: "Images/boardInterior/interior_245.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:17; backgroundImg: "Images/boardInterior/interior_246.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:12; posY:18; backgroundImg: "Images/boardInterior/interior_247.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_13.gif"}
            // row 13:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_14.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:0; backgroundImg: "Images/boardInterior/interior_248.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:1; backgroundImg: "Images/boardInterior/interior_249.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:2; backgroundImg: "Images/boardInterior/interior_250.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:3; backgroundImg: "Images/boardInterior/interior_251.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:4; backgroundImg: "Images/boardInterior/interior_252.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:5; backgroundImg: "Images/boardInterior/interior_253.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:6; backgroundImg: "Images/boardInterior/interior_254.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:7; backgroundImg: "Images/boardInterior/interior_255.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:8; backgroundImg: "Images/boardInterior/interior_256.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:9; backgroundImg: "Images/boardInterior/interior_257.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:10; backgroundImg: "Images/boardInterior/interior_258.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:11; backgroundImg: "Images/boardInterior/interior_259.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:12; backgroundImg: "Images/boardInterior/interior_260.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:13; backgroundImg: "Images/boardInterior/interior_261.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:14; backgroundImg: "Images/boardInterior/interior_262.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:15; backgroundImg: "Images/boardInterior/interior_263.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:16; backgroundImg: "Images/boardInterior/interior_264.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:17; backgroundImg: "Images/boardInterior/interior_265.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:13; posY:18; backgroundImg: "Images/boardInterior/interior_266.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_14.gif"}
            // row 14:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_15.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:0; backgroundImg: "Images/boardInterior/interior_267.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:1; backgroundImg: "Images/boardInterior/interior_268.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:2; backgroundImg: "Images/boardInterior/interior_269.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:3; backgroundImg: "Images/boardInterior/interior_270.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:4; backgroundImg: "Images/boardInterior/interior_271.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:5; backgroundImg: "Images/boardInterior/interior_272.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:6; backgroundImg: "Images/boardInterior/interior_273.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:7; backgroundImg: "Images/boardInterior/interior_274.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:8; backgroundImg: "Images/boardInterior/interior_275.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:9; backgroundImg: "Images/boardInterior/interior_276.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:10; backgroundImg: "Images/boardInterior/interior_277.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:11; backgroundImg: "Images/boardInterior/interior_278.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:12; backgroundImg: "Images/boardInterior/interior_279.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:13; backgroundImg: "Images/boardInterior/interior_280.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:14; backgroundImg: "Images/boardInterior/interior_281.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:15; backgroundImg: "Images/boardInterior/interior_282.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:16; backgroundImg: "Images/boardInterior/interior_283.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:17; backgroundImg: "Images/boardInterior/interior_284.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:14; posY:18; backgroundImg: "Images/boardInterior/interior_285.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_15.gif"}
            // row 15:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_16.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:0; backgroundImg: "Images/boardInterior/interior_286.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:1; backgroundImg: "Images/boardInterior/interior_287.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:2; backgroundImg: "Images/boardInterior/interior_288.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:3; backgroundImg: "Images/boardInterior/interior_289.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:4; backgroundImg: "Images/boardInterior/interior_290.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:5; backgroundImg: "Images/boardInterior/interior_291.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:6; backgroundImg: "Images/boardInterior/interior_292.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:7; backgroundImg: "Images/boardInterior/interior_293.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:8; backgroundImg: "Images/boardInterior/interior_294.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:9; backgroundImg: "Images/boardInterior/interior_295.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:10; backgroundImg: "Images/boardInterior/interior_296.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:11; backgroundImg: "Images/boardInterior/interior_297.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:12; backgroundImg: "Images/boardInterior/interior_298.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:13; backgroundImg: "Images/boardInterior/interior_299.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:14; backgroundImg: "Images/boardInterior/interior_300.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:15; backgroundImg: "Images/boardInterior/interior_301.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:16; backgroundImg: "Images/boardInterior/interior_302.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:17; backgroundImg: "Images/boardInterior/interior_303.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:15; posY:18; backgroundImg: "Images/boardInterior/interior_304.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_16.gif"}
            // row 16:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_17.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:0; backgroundImg: "Images/boardInterior/interior_305.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:1; backgroundImg: "Images/boardInterior/interior_306.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:2; backgroundImg: "Images/boardInterior/interior_307.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:3; backgroundImg: "Images/boardInterior/interior_308.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:4; backgroundImg: "Images/boardInterior/interior_309.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:5; backgroundImg: "Images/boardInterior/interior_310.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:6; backgroundImg: "Images/boardInterior/interior_311.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:7; backgroundImg: "Images/boardInterior/interior_312.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:8; backgroundImg: "Images/boardInterior/interior_313.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:9; backgroundImg: "Images/boardInterior/interior_314.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:10; backgroundImg: "Images/boardInterior/interior_315.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:11; backgroundImg: "Images/boardInterior/interior_316.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:12; backgroundImg: "Images/boardInterior/interior_317.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:13; backgroundImg: "Images/boardInterior/interior_318.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:14; backgroundImg: "Images/boardInterior/interior_319.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:15; backgroundImg: "Images/boardInterior/interior_320.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:16; backgroundImg: "Images/boardInterior/interior_321.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:17; backgroundImg: "Images/boardInterior/interior_322.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:16; posY:18; backgroundImg: "Images/boardInterior/interior_323.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_17.gif"}
            // row 17:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_18.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:0; backgroundImg: "Images/boardInterior/interior_324.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:1; backgroundImg: "Images/boardInterior/interior_325.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:2; backgroundImg: "Images/boardInterior/interior_326.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:3; backgroundImg: "Images/boardInterior/interior_327.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:4; backgroundImg: "Images/boardInterior/interior_328.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:5; backgroundImg: "Images/boardInterior/interior_329.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:6; backgroundImg: "Images/boardInterior/interior_330.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:7; backgroundImg: "Images/boardInterior/interior_331.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:8; backgroundImg: "Images/boardInterior/interior_332.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:9; backgroundImg: "Images/boardInterior/interior_333.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:10; backgroundImg: "Images/boardInterior/interior_334.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:11; backgroundImg: "Images/boardInterior/interior_335.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:12; backgroundImg: "Images/boardInterior/interior_336.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:13; backgroundImg: "Images/boardInterior/interior_337.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:14; backgroundImg: "Images/boardInterior/interior_338.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:15; backgroundImg: "Images/boardInterior/interior_339.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:16; backgroundImg: "Images/boardInterior/interior_340.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:17; backgroundImg: "Images/boardInterior/interior_341.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:17; posY:18; backgroundImg: "Images/boardInterior/interior_342.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_18.gif"}
            // row 18:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_left_19.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:0; backgroundImg: "Images/boardInterior/interior_343.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:1; backgroundImg: "Images/boardInterior/interior_344.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:2; backgroundImg: "Images/boardInterior/interior_345.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:3; backgroundImg: "Images/boardInterior/interior_346.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:4; backgroundImg: "Images/boardInterior/interior_347.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:5; backgroundImg: "Images/boardInterior/interior_348.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:6; backgroundImg: "Images/boardInterior/interior_349.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:7; backgroundImg: "Images/boardInterior/interior_350.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:8; backgroundImg: "Images/boardInterior/interior_351.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:9; backgroundImg: "Images/boardInterior/interior_352.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:10; backgroundImg: "Images/boardInterior/interior_353.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:11; backgroundImg: "Images/boardInterior/interior_354.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:12; backgroundImg: "Images/boardInterior/interior_355.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:13; backgroundImg: "Images/boardInterior/interior_356.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:14; backgroundImg: "Images/boardInterior/interior_357.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:15; backgroundImg: "Images/boardInterior/interior_358.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:16; backgroundImg: "Images/boardInterior/interior_359.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:17; backgroundImg: "Images/boardInterior/interior_360.gif"}
            Cell{cellSizeW:cellInteriorSize; cellSizeH:cellInteriorSize; posX:18; posY:18; backgroundImg: "Images/boardInterior/interior_361.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameWSize; backgroundImg: "Images/boardBorder/border_right_19.gif"}
            // row frame bottom:
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/corner_bottom_left.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_01.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_02.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_03.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_04.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_05.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_06.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_07.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_08.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_09.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_10.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_11.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_12.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_13.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_14.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_15.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_16.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_17.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_18.gif"}
            Cell{cellSizeW:cellBoardFrameWSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/border_bottom_19.gif"}
            Cell{cellSizeW:cellBoardFrameHSize; cellSizeH:cellBoardFrameHSize; backgroundImg: "Images/boardBorder/corner_bottom_right.gif"}
    }

    // Methods:

    // Object constructor.
    Component.onCompleted: {
        // Signal connections:

    }

    // Revert instance to initial state.
    function onResetBoardInstance()
    {
        console.log( "qml: dbg::GomokuBoard Clearing board..." )
        for (var i = 0; i < realGomokuBoardGrid.children.length; i++)
        {
            realGomokuBoardGrid.children[i].resetInstance()
        }
        previousHotCell.posx = -1
        previousHotCell.posy = -1
        currentHotCell.posx = -1
        currentHotCell.posy = -1
        redDotBallIndex = -1
    }

    // Function marks a field which human clicked.
    function onCellClicked( xx, yy )
    {
        console.log("qml: dbg::GomokuBoard onCellClicked: (", xx, ",",yy, ")" )

        // Shift position due to frame.
        currentHotCell.posx = xx + 1
        currentHotCell.posy = yy + 1

        // Release the previous hot cell and select the new one.
        if(previousHotCell.posx!==-1 && previousHotCell.posy!==-1)
        {
            var indexPrevious = previousHotCell.posx * realGomokuBoardGrid.gridSize + previousHotCell.posy
            realGomokuBoardGrid.children[indexPrevious].resetHotState()
        }

        previousHotCell.posx = currentHotCell.posx
        previousHotCell.posy = currentHotCell.posy

        var indexCurrent = currentHotCell.posx * realGomokuBoardGrid.gridSize + currentHotCell.posy
        realGomokuBoardGrid.children[indexCurrent].setHotState()

        // Emit signal.
        hotMoveUp()
    }

    // BACKEND -> GUI. Handlers
    function onBackendevent_restart()
    {
        onResetBoardInstance()
    }

    function onBackendevent_human_won(positions)
    {
        for(var i =0; i<positions.length; ++i)
        {
            var map = positions[i]
            cpuReplyWinnerMarkHelper( Number(map["x"]), Number(map["y"]) );
        }

        // Emit signal.
        showNotificationMsg(humanWonNotyfication);
    }

    function onBackendevent_cpu_won(positions)
    {
        for(var i =0; i<positions.length; ++i)
        {
            var map = positions[i]
            cpuReplyWinnerMarkHelper( Number(map["x"]), Number(map["y"]) );
        }

        // Emit signal.
        showNotificationMsg(cpuWonNotyfication);
    }

    function onBackendevent_stalemate()
    {
    }

    function onBackendevent_cpu_move(cpuRow,cpuColumn)
    {
        console.log("qml: dbg::GomokuBoard cpu move: (", cpuRow, ",",cpuColumn, ")" )

        // Conversion need to be added.
        var indexCpu = (cpuRow+1) * realGomokuBoardGrid.gridSize + (cpuColumn+1)
        if( -1 == redDotBallIndex )
        {
            realGomokuBoardGrid.children[indexCpu].setBallRedDot(!isUserWhite)
        }
        else
        {
            realGomokuBoardGrid.children[redDotBallIndex].setBall(!isUserWhite)
            realGomokuBoardGrid.children[indexCpu].setBallRedDot(!isUserWhite)
        }
        redDotBallIndex = indexCpu

        cpuReplyReceived()

    }

    function onBackendevent_human_move_invalid()
    {
    }

    function cpuReplyWinnerMarkHelper( cpuRow, cpuColumn )
    {
        // Conversion need to be added.
        var indexCpu = (cpuRow+1) * realGomokuBoardGrid.gridSize + (cpuColumn+1)
        realGomokuBoardGrid.children[indexCpu].setWinnerBall()
    }

    // GUI -> BACKEND. Function put HUMAN ball.
    function humanReply()
    {
        var indexHuman = currentHotCell.posx*realGomokuBoardGrid.gridSize+currentHotCell.posy
        realGomokuBoardGrid.children[indexHuman].setBall(isUserWhite)
        previousHotCell.posx = -1
        previousHotCell.posy = -1

        // Conversion need to be added.
        var humanRow = currentHotCell.posx - 1
        var humanColumn = currentHotCell.posy - 1

        // Inform C++ backend about human move.
        gomokuInputStream.frontendeventmove( humanRow, humanColumn );

        // Emit signal.
        hotMoveDown()
    }
}
