import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 1.4


Rectangle {
    id: goButtonSt1Id

    color   : "transparent"
    width   : 0
    height  : 0
    property var isHotMoveUp        : false
    property var isCpuReplyReceived : true

    property alias goButtonSt2IdAlias: goButtonSt2Id
    Rectangle
    {
        id: goButtonSt2Id

        anchors.centerIn: parent
        width           : 0.95*parent.width
        height          : 0.8*parent.height
        radius          : 20
        border.width    : 3
        border.color    : "black"
        opacity         : 1
        gradient: Gradient {
            GradientStop { position: 0.0; color: "gray" }
            GradientStop { position: 1.0; color: "black" }
        }

        Text {
            id: goButtonTextId

            text: "Go"
            anchors.centerIn: parent

            font.pointSize: 16;
            font.bold: true
            color: "white"
        }

        property alias goButtonMouseAreaIdAlias: goButtonMouseAreaId
        MouseArea {

            id: goButtonMouseAreaId

            anchors.fill: parent
            onClicked: {
                console.log("qml: GoButton has been clicked")
            }
        }
    }

    // Constructor.
    Component.onCompleted: {
        goButtonSt1Id.goButtonSt2IdAlias.goButtonMouseAreaIdAlias.enabled = false
        goButtonSt1Id.goButtonSt2IdAlias.opacity = 0.5
    }

    // Revert instance to initial state.
    function onResetInstance()
    {
       console.log("qml: dbg::Button:: Reset instance")
       isHotMoveUp = false
       isCpuReplyReceived = true
    }

    function onHotMoveUp()
    {
       console.log("qml: dbg::Button:: Enabled")

       isHotMoveUp = true
       if( isCpuReplyReceived && isHotMoveUp )
       {
           goButtonSt1Id.goButtonSt2IdAlias.goButtonMouseAreaIdAlias.enabled = true
           goButtonSt1Id.goButtonSt2IdAlias.opacity = 1
       }
    }

    function onHotMoveDown()
    {
       console.log("qml: dbg::Button:: Disabled")
       goButtonSt1Id.goButtonSt2IdAlias.goButtonMouseAreaIdAlias.enabled = false
       goButtonSt1Id.goButtonSt2IdAlias.opacity = 0.5
       isCpuReplyReceived = false
       isHotMoveUp = false
    }

    function onCpuReplyReceived()
    {
       console.log("qml: dbg::Button:: CpuReplyReceived")

       isCpuReplyReceived = true
       if(isCpuReplyReceived && isHotMoveUp )
       {
           goButtonSt1Id.goButtonSt2IdAlias.goButtonMouseAreaIdAlias.enabled = true
           goButtonSt1Id.goButtonSt2IdAlias.opacity = 1
       }
    }
}
