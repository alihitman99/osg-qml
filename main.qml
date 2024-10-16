import QtQuick 2.12
import QtQuick.Window 2.12
import OSGQMLItem 1.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13
import QtQuick.Dialogs

Window {
    id:mWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("OSGQMLItem")


    OSGItem{
        id:osgItem
        anchors.centerIn: parent
        anchors.fill: parent
        source: "tree.osgb"
    }
    RowLayout {

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.rightMargin: 10
        Text {
            id: lblInput
            height: 100
            //        anchors.centerIn: parent
            //            anchors.left: parent.left
            //            anchors.top: parent.top
            //            anchors.leftMargin: 10
            //            anchors.topMargin: 10
            text: qsTr("Source:")
            font.pixelSize: 16
            color: "red"
        }
        Text {
            id:txtInput
            //            anchors.left: lblInput.right
            //            anchors.leftMargin: 10
            //            anchors.top: parent.top
            //            anchors.topMargin: 10
            Layout.minimumWidth: 200
            Layout.fillWidth: true
            text: osgItem.source.toString()
            color: "green"
        }
        Button {
            id:btnInput
            //            anchors.left: txtInput.right
            //            anchors.leftMargin: 10
            //            anchors.top: parent.top
            //            anchors.topMargin: 10
            font.pixelSize: 14
            text: "Load Model"
            height: 5
            onClicked: {
                fileDialog.open();
            }
        }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a model"
//        folder: "/home/client110/Documents/projects/hooshan/QTMAP3D/source/map3d/data/models"
        onAccepted: {
            txtInput.text = fileDialog.currentFile.toString()
            osgItem.source = fileDialog.currentFile.toString()
        }
        onRejected: {
            console.log("Canceled")

        }
//        Component.onCompleted: visible = true
    }

    //    Rectangle {
    //        width:400
    //        height: 400
    //        anchors.centerIn: parent
    //        color: "red"
    //    }
    //    Rectangle {
    //        width:200
    //        height: 200
    //        anchors.centerIn: parent
    //        color: "yellow"
    //    }
}
