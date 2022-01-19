// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

import QtQuick 2.5

import Qt.labs.qmlmodels 1.0
import QtQuick.Controls.Material 2.12


Rectangle {
      width: 300
    height: 600
    color: "#dddddd"

    Material.theme: Material.Light
    Material.accent: Material.Green

    DelegateChooser {
        id: delegateChooser
        role: "type"
        DelegateChoice {
           roleValue: "Anenometer"
           AnenometerItemDelegate {
           }
        }
        DelegateChoice {
            roleValue: "Gyro"
           GyroItemDelegate {}
        }
        DelegateChoice {
            roleValue: "GPS"
            GPSItemDelegate {}
        }
        DelegateChoice {
            roleValue: "Compass"
            CompassItemDelegate {}
        }
    }


    ListView {
        id: listView
        anchors.fill: parent
        header: heading
        delegate: delegateChooser
        model: root.sensorModel
        }




    Component {
           id: heading
           Rectangle {
               anchors.left: parent.left
               anchors.right: parent.right
               height: 60

               Text {
                   anchors.fill: parent
                   anchors.leftMargin: 20
                     height: 70
                   text: qsTr("Sensors")
                   font.bold: true
                   font.pixelSize: 22

                   verticalAlignment: Text.AlignVCenter
               }
               Rectangle {
                   anchors.left: parent.left
                   anchors.right: parent.right
                   anchors.bottom: parent.bottom
                   height: 1
                   color: "#aaaaaa"
               }
           }
       }
}
//https://ortogonal.github.io/qt-qml-delegatechooser/


