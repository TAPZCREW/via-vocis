import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ".";

RowLayout {
    anchors.fill: parent
    Frame {
        RowLayout {
            anchors.fill: parent
            Pane {
                id: main_chanel
                Layout.fillHeight: true
                RowLayout {
                    anchors.fill: parent
                    ColumnLayout {
                        Layout.fillHeight: true
                        Label {
                            text: "Applications à tranférer"
                            font.pointSize: 8
                            Layout.fillWidth: true
                        }
                        Frame {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            ColumnLayout {
                                anchors.fill: parent
                                ProcessEntry {
                                    process_name: "explorer.exe"
                                    process_color: "blue"

                                    Layout.fillWidth: true
                                }
                                ProcessEntry {
                                    process_name: "zen.exe"
                                    process_color: "green"

                                    Layout.fillWidth: true
                                }
                                Item {
                                    Layout.fillHeight: true
                                }
                            }
                        }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Label {
                            text: "Master"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true

                            Layout.preferredHeight: 30
                            Layout.fillWidth: true
                        }
                        Label {
                            text: "Périphériques"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true

                            Layout.preferredHeight: 30
                            Layout.fillWidth: true
                        }
                        Slider {
                            orientation: Qt.Vertical
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                    }
                }
            }
            Channel {
                channel_name: "Game"
                Layout.fillHeight: true

                ProcessEntry {
                    process_name: "hollow knight.exe"
                    process_color: "red"

                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillHeight: true
                }
            }
            Channel {
                channel_name: "Chat"
                Layout.fillHeight: true

                ProcessEntry {
                    process_name: "Discord.exe"
                    process_color: "purple"

                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillHeight: true
                }
            }

            Item {
                Layout.fillWidth: true
            }
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
    Button {
        text: "Ajouter un canal"
        // Layout.fillHeight: true
    }
}
