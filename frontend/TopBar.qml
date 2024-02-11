import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1


Rectangle
{
    id: topBarSt1Id

    width           : 0
    height          : 0
    border.width    : 3
    border.color    : "black"
    color           : "red"
    y               : rootTopMarginSize
    radius          : 20
    property real marginLeftWPercent      : (2/100)
    property real marginRightWPercent     : (2/100)
    property real middleWPercent          : ((marginLeftWPercent+marginRightWPercent)/100)
    property real marginLeftWPercentSize  : (marginLeftWPercent*parent.width)
    property real marginRightWPercentSize : (marginRightWPercent*parent.width)
    property real middleWPercentSize      : (middleWPercent*parent.width)
    property real imageW                  : 0.7*topBarSt1Id.height
    property real imageH                  : 0.7*topBarSt1Id.height
    property real fullWindowW             : 0
    property real fullWindowH             : 0
    property real marginPercent           : (2/100)
    property real marginSize              : (marginPercent*parent.width)
    property int  repeaterNo              : ((parent.width-2*marginSize)/imageW)

    // Menu icons.
    property int  backIconNo              : 0
    property int  revertIconNo            : 1
    property int  infoIconNo              : 3
    property int  exitIconNo              : 4

    gradient: Gradient {
        GradientStop { position: 0.0; color: "black" }
        GradientStop { position: 1.0; color: "gray" }
    }

    // This is a row with menu images.
    Row
    {
        id: layoutId
        anchors.verticalCenter  : parent.verticalCenter
        spacing                 : ((parent.width - 2*marginSize - repeaterNo*imageW)/(repeaterNo-1))
        x                       : marginSize

        Repeater
        {
            id          : repeaterId
            model       : 5//repeaterNo

            Rectangle
            {
                width   : imageW
                height  : imageH
                color   : "transparent"

                Image
                {
                    id      : imageId
                    width   : parent.width
                    height  : parent.height

                    fillMode: Image.Stretch
                }

                MouseArea
                {
                    id: mouseAreaId
                    anchors.fill: parent
                    onClicked:
                    {
                        if( index==backIconNo )
                        {
                            console.log("backIconNo ", index)
                        }
                        else if( index==revertIconNo)
                        {
                            console.log("revertIconNo ", index)
                        }
                        else if( index==infoIconNo)
                        {
                            console.log("infoIconNo ", index)
                            if( drawerId.position == 0 )
                            {
                                drawerId.open()
                            }
                            else if( drawerId.position == 1 )
                            {
                                drawerId.close()
                            }
                        }
                        else if( index==exitIconNo )
                        {
                            console.log("exitIconNo ", index)
                        }
                    }
                }

                function putImage( src )
                {
                    imageId.source = src
                }
            }

            onItemAdded:
            {
                if( index==backIconNo )
                {
                    console.log("update ", index)
                    item.putImage( "Images/menu/icons8-go-back-filled-100_disabled.png" )
                }
                else if( index==revertIconNo )
                {
                    console.log("update ", index)
                    item.putImage( "Images/menu/icons8-time-machine-filled-100_disabled.png" )
                }
                else if( index==infoIconNo )
                {
                    console.log("update ", index)
                    item.putImage( "Images/menu/icons8-info-filled-100.png" )
                }
                else if( index==exitIconNo )
                {
                    console.log("update ", index)
                    item.putImage( "Images/menu/icons8-cancel-filled-100_disabled.png" )
                }
            }
        }
    }

    Drawer
    {
        id: drawerId

        width       : Math.min(topBarSt1Id.fullWindowW, topBarSt1Id.fullWindowH) / 3 * 1
        height      : topBarSt1Id.fullWindowH
        dragMargin  : 0
        edge        : Qt.RightEdge

        background: Rectangle {
            color: "grey"
            anchors.fill: parent
        }

        // Catch any mouse activity to not pass click event below.
        MouseArea
        {
            anchors.fill: parent
            // nothing to do
        }

        Text {
            color: "#00FF00"
            text: "<b>Release</b> <br> 04.2018:: <i>v1.0</i>"
        }
    }
}
