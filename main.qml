import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import com.testobj 1.0

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

    ObjectTest {
        id: objectTest
    }

    Button {
        text: "Click me"
        onClicked: {
            counter++
            console.log("Button clicked " + counter + " times")
            console.log("Plaintext: " + plaintext)

            plaintext += "Hello World"
            objectTest.test2();
        }
    }

    property int counter: 0
    property string plaintext: ""
}
