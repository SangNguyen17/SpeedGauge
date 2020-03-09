import QtQuick 2.0

Item {
    id: needleId

    property int numOfIntervals: 14
    property int startingAngle: 225
    property double angleStep: 19.2
    property int maxSpeed: 280
    property int value: 0

    Rectangle {
        width: needleId.height * 0.02
        height: needleId.height * 0.45
        color: "blue"
        anchors {
            horizontalCenter: needleId.horizontalCenter
        }
        y: needleId.height * 0.05
    }

    rotation: value * angleStep + startingAngle

    Behavior on rotation {
        SmoothedAnimation { velocity: 70 }
    }
}
