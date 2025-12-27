import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 400
    height: 400
    visible: true
    title: qsTr("Hello World")

    Button {
        id: button1
        text: qsTr("ButtOff")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 181
        anchors.topMargin: 192
        anchors.centerIn: parent
        flat: true
        highlighted: false
    }

    Button {
        id: button
        text: qsTr("Button")
    }
}
