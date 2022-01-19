// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

import QtQuick 2.0

Rectangle
{
    property var content
    property bool isBlink: false
    color: "white"
    height: 48 + cContent.height
    width: listView.width
    //anchors.left: parent.left
    //anchors.right: parent.right
    Item
    {
        id: cBar
        height: 48
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Rectangle {
            id: rect
            width: 16
            height: 16
            radius: width*0.5
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            color: statecolor

        }

        Text {
            id: titleText
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#111111"
            font.pixelSize: 14
            text: "[" + type + "] - " + name

        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 400
            horizontalAlignment: Text.AlignRight
            text: signalStrength + " %"
        }
    }
    Rectangle {
        id: cContent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: cBar.bottom
        height: 0
        visible: false
        color: "white"
        data: [
                content
            ]
        }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: "#aaaaaa"
    }


    MouseArea {
        anchors.fill: parent
        cursorShape: "PointingHandCursor"
        onClicked: parent.state === "expanded" ? parent.state = "" : parent.state = "expanded"
    }

    SequentialAnimation {
        id: animationId
        running: true
        loops: Animation.Infinite
        PropertyAnimation {
            target: rect
            property: "opacity"
            to: 1
            duration: 400
        }
        PauseAnimation {
            duration: 300
        }
        PropertyAnimation {
            target: rect
            property: "opacity"
            to: 0.6
            duration: 400
        }
    }

    states: [
        State {
            name: "expanded"
            PropertyChanges { target: cContent; visible: true}
            PropertyChanges { target: cContent; height: 35 }
            PropertyChanges { target: titleText; font.bold: true }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                duration: 200;
                properties: "height,visible"
            }
        }
    ]

}
