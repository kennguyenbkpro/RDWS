import QtQuick 1.0

Row {
    anchors.centerIn: parent
    spacing: parent.width/6

    Button {
        id : cutButton
        buttonColor: "#1114cd"
        label: "Cut"
    }
    Button {
        id : copyButton
        buttonColor: "#4d1411"
        label: "Copy"
    }
    Button {
        id : selectButton
        buttonColor: "#114d13"
        label: "Select All"
    }
}
