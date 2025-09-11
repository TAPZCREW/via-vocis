import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    id: main
    
    property string channel_name
    default property alias content: process_layout.children

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Label {
                id: channel_name_label
                text: main.channel_name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                
                Layout.preferredHeight: 30
                Layout.fillWidth: true
            }
            ToolButton {
                text: "edit"
                Layout.preferredHeight: 30
            }
            Layout.preferredHeight: 30
            Layout.fillWidth: true
        }
        ComboBox {
            id: output_device_box
            model: ["Speakers", "Screen 01 Speakers", "Screen 02 Speakers"]

            Layout.preferredHeight: 30
            Layout.fillWidth: true
        }
        Slider {
            id: volume_slider
            orientation: Qt.Vertical

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        ColumnLayout {
            Label {
                text: "Applications"
                font.pointSize: 8
            }
            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ColumnLayout {
                    id: process_layout

                    anchors.fill: parent
                }
            }
            Layout.fillWidth: true
        }
    }
}
