// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

import QtQuick 2.15
import QtQuick.Controls 2.15
import com.dice.widgets 1.0

ApplicationWindow {
    width: 640
    height: 600
    visible: true
    title: qsTr("C++/Qml Demo")
    id: root
    objectName: "root"
    property var sensorModel


        DeviceList
        {
            anchors.fill: parent

        }

}
