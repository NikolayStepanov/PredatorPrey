import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import GameModel 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1800
    height: 1000
    title: qsTr("Life")

    TableView {
        id: tableView
        anchors.fill: parent
        anchors.centerIn: parent
        anchors.leftMargin: 10
        anchors.topMargin: 10

        rowSpacing: 1
        columnSpacing: 1

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}

        delegate: Rectangle {
            id: cell
            implicitWidth: 100
            implicitHeight: 100

            color:"#a6d3fb"

            CellIcon
            {
                id:cellIcon
                anchors.centerIn: parent
                width: cell.width
                height: cell.height
                typeImg: model.type
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    gameModel.changeTypeCell(id,type,index)
                }
            }
        }

        //model
        model: GameModel {
            id: gameModel
        }

        contentX: (contentWidth - width) / 2;
        contentY: (contentHeight - height) / 2;
    }

    footer: Rectangle {
        signal nextStep

        id: footer
        height: 50
        color: "#F3F3F4"

        RowLayout {
            anchors.centerIn: parent

            Button {
                text: qsTr("Next")
                onClicked: gameModel.nextStep()
            }

            Item {
                width: 50
            }

            Slider {
                id: slider
                x: 245
                y: 17
                from: 0
                to: 1
                value: 0.1
            }

            Button {
                text: timer.running ? "❙❙" : "▶️"
                onClicked: timer.running = !timer.running
            }
        }

        Timer {
            id: timer
            interval: 1000 - (980 * slider.value)
            running: true
            repeat: true
            onTriggered: gameModel.nextStep()
        }
    }
}
