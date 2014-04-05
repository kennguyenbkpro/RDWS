import QtQuick 1.0

Row {
    anchors.centerIn: parent
    spacing: parent.width/6

    Button {
        id : loadButton
        buttonColor: "#1114cd"
        label: "Load"
    }
    Button {
        id : saveButton
        buttonColor: "#4d1411"
        label: "Save"
    }
    Button {
        id : exitButton
        buttonColor: "#114d13"
        label: "Exit"
        onButtonClick: Qt.quit()
    }
}
