import QtQuick 2.0
import GameModel 1.0

Item {
    id: root

    property int typeImg: 0

    Image {
        id: img
        source: {
            switch (typeImg) {
            case 1:
                "../icons/Female-Amphiprion.png"
                break;
            case 2:
                "../icons/Male-Amphiprion.png"
                break;
            case 3:
                "../icons/Female-Shark.png"
                break;
            case 4:
                "../icons/Male-Shark.png"
                break;
            case 5:
                "../icons/Rock.png"
                break;
            default:
                "../icons/Bubbles.png"
            }

        }
        smooth: true
        anchors.fill: parent
    }

}
