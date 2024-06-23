import QtQuick 2.0
import QtQuick.Controls 2.0
import QtMultimedia 5.0

Rectangle {
    id: notificationId

    width: parent.width
    height: parent.height
    color: "black"
    border.color: "#17a81a"
    border.width: 5
    radius: 10
    opacity: 0.75
    visible: false

    // Signals:
    signal playOrNotClicked()

    // Catch any mouse activity.
    MouseArea {
        anchors.fill: parent
    }

    //Quit timer. Additional delay to close app gracefully.
    Timer {
        id: quitTimer
        interval: 200  // 1000 milliseconds = 1 second
        repeat: false   // Run only once
        onTriggered: Qt.quit()  // Call Qt.quit() when the timer triggers
    }


    // First button as a non-clickable label
    Button {
        id: notificationButtonId
        text: "note"
        anchors.centerIn: parent
        contentItem: Text {
            text: notificationButtonId.text
            font.pointSize: 18
            opacity: enabled ? 1.0 : 0.3
            color: "#17a81a"  // Text color
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 40
            color: "black"  // Background color
            opacity: enabled ? 0.3 : 0.3
            border.color:  "#17a81a"   // Border color
            border.width: 1
            radius: 2
        }
    }

    // Second Button - Confirm Yes
    Button {
        id: yesButtonId
        text: "new game"
        anchors.top: notificationButtonId.bottom
        anchors.topMargin: 40  // Increased margin
        anchors.horizontalCenter: notificationButtonId.horizontalCenter
        contentItem: Text {
            text: yesButtonId.text
            font.pointSize: 12
            opacity: enabled ? 1.0 : 0.3
            color: yesButtonId.down ? "#17a81a" : "#21be2b"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 40
            color: "black"
            opacity: enabled ? 0.3 : 0.3
            border.color: yesButtonId.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }
        onClicked: {
            console.log("qml: dbg::Notification:: Human wants play again.")

            notificationId.visible = false
            //emit signal to reflesh/restart board
            playOrNotClicked()
            // Inform C++ backend about human move.
            gomokuGameServerGUI.frontend_is_play_again( 1 );
        }
    }

    // Third Button - Confirm No
    Button {
        id: noButtonId
        text: "end game"
        anchors.top: yesButtonId.bottom
        anchors.horizontalCenter: yesButtonId.horizontalCenter
        contentItem: Text {
            text: noButtonId.text
            font.pointSize: 12
            opacity: enabled ? 1.0 : 0.3
            color: noButtonId.down ? "#17a81a" : "#21be2b"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 40
            color: "black"
            opacity: enabled ? 0.3 : 0.3
            border.color: noButtonId.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }
        onClicked: {
            console.log("qml: dbg::Notification:: Human wants end game.")

            notificationId.visible = false
            //emit signal to reflesh/restart board
            playOrNotClicked()
            // Inform C++ backend about human move.
            gomokuGameServerGUI.frontend_is_play_again( 0 )

            //start quit timer
            quitTimer.start()
        }
    }

    function onShowNotificationMsg(msg) {
        notificationButtonId.text = msg
        notificationId.visible = true
    }
}
