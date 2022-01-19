// -------------------------------------------------------------------------
//
//  C++/QML DEMO PROJECT
//
// Written by Fabrice Lainard, jan 2022
// www.FLProgramming.fr
// -------------------------------------------------------------------------

import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4

SensorItemDelegate {

    content :
        RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5
        Text {
                text: Qt.formatTime(object.dt,"(hh:mm:ss)")
        }

        Label { text: qsTr("Wind direction: ") }
        Text {
        horizontalAlignment: Text.AlignRight
        text: object.windDirection + "°"
        }
        Label { text: qsTr("Wind gust: ") }
        Text {
        horizontalAlignment: Text.AlignRight
        text: object.windGust + " kts"
        }

    }



}
