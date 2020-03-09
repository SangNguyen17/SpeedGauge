import QtQuick 2.12
// import QtQuick.Window 2.12
import QMLHandler 1.0
Rectangle {
    id: mainqmlId
    width: 400
    height: 400
    color: "black"

    property int numOfIntervals: 14
    property int startingAngle: 225
    property double angleStep: 19.3
    property int maxSpeed: 280

    QMLHandler {
        id: qmlhandlerId
    }

    Image {
        id: gaugeImage
        anchors.fill: parent
        source: "NE567.png"
    }

    Needle {
        anchors {
            bottom: parent.bottom
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        value: qmlhandlerId.speed
        startingAngle: mainqmlId.startingAngle
        angleStep: mainqmlId.angleStep / (mainqmlId.maxSpeed / mainqmlId.numOfIntervals);
    }

}
