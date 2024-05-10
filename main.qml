import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World!!!!!")

    Rectangle {
        width: 250
        height: 100
        color: "blue"
        anchors.centerIn: parent
    }

    SyntaxHighlightEditor {
        anchors.fill: parent
    }

    property int counter: 0
}
