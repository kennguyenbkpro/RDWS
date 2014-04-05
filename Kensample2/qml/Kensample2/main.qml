import QtQuick 1.0

Rectangle {
    id : demoButton
    width: 200; height: 60
    property color buttonColor: "#a1b2cd"
    property color onHoverColor: "#0011ff"
    property color borderColor: "white"
    property string label: "I'm a button"

    color: buttonMouseArea.pressed? (Qt.darker(buttonColor, 1.5)) : buttonColor
    border.color: borderColor

    signal buttonClick()
    onButtonClick: {
        console.log (buttonLabel.text + " clicked!")
    }

    Text {
        id: buttonLabel
        text: label
        anchors.centerIn: parent
        font.pointSize: 24
    }
    MouseArea {
        id : buttonMouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: buttonClick()
        onEntered: parent.border.color = onHoverColor
        onExited: parent.border.color = borderColor
    }


}
