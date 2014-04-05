import QtQuick 1.0



ListView {
    id: menuBarListView

    VisualDataModel {
        id : menuBarModel
        FileMenu {
            width: menuBarListView.width
            height: 400

        }
        EditMenu {

        }
    }


    Rectangle {
        id: labelList
        z : 1

        Row {
            anchors.centerIn: parent
            spacing: 40
            Button {
                label: "File"
                id: fileButton
                onButtonClick: menuBarListView.currentIndex = 0
                buttonColor: "lightblue"

            }
            Button {
                label: "Edit"
                id: editButton
                onButtonClick: menuBarListView.currentIndex = 1
                buttonColor: "lightblue"

            }
        }
    }
}
