import QtQuick 2.0
import Sailfish.Silica 1.0

import "../pragma/Helpers.js" as Helpers


ListItem {
    id: listDelegate


    // These properties are also used in the CoverPage.
    property int freePlaces: free
    property string parkingStatus: Helpers.getStatus(status)
    property string parkingName: Helpers.getName(name, isRelay)


    function markAsFavorite(f)
    {
        var s = qsTr("Adding to Favorites");

        if(!f)
            s = qsTr("Removing from Favorites");

        remorseAction(s, function() {
            ListView.view.model.markAsFavorite(index, f);
        }, 3000);
    }


    menu: contextMenu


    Label {
        id: nameLabel

        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: statusLabel.left
            rightMargin: Theme.paddingLarge
        }
        color: Helpers.isOpen(status) ? (highlighted ? Theme.highlightColor : Theme.primaryColor)
                              : (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        text: parkingName //Helpers.getName(name, isRelay)
        truncationMode: TruncationMode.Fade
    }

    Label {
        id: statusLabel

        anchors {
            baseline: nameLabel.baseline
            right: statusIndicator.left
            rightMargin: Theme.paddingMedium
        }
        color: Helpers.isOpen(status) ? (highlighted ? Theme.highlightColor : Theme.primaryColor)
                              : (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        font {
            pixelSize: Theme.fontSizeExtraSmall
        }
        horizontalAlignment: Text.AlignRight
        text: parkingStatus //Helpers.getStatus(status)
    }

    StatusIndicator {
        id: statusIndicator

        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: statusLabel.verticalCenter
        }
        color: Helpers.getColor(status) ? Helpers.getColor(status) : Theme.secondaryColor
    }

    Label {
        id: occupation

        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
            top: nameLabel.bottom
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font {
            pixelSize: Theme.fontSizeExtraSmall
        }
        text: qsTr("%Ln free place(s) (%L1)", "", free).arg(total)
    }

    Component {
        id: contextMenu

        ContextMenu {
            /*
             * FIXME: sadly not feasible for now.
             *        this should be implemented as soon as Jolla provides the necessary API/tools.
             *
            MenuItem {
                text: qsTr("Go there")
                onClicked: console.log("FIXME.")
            }
            */
            MenuItem {
                text: qsTr("Add to favorites")
                visible: !isFavorite
                onClicked: {
                    markAsFavorite(true)
                }
            }
            MenuItem {
                text: qsTr("Remove from favorites")
                visible: isFavorite
                onClicked: {
                    markAsFavorite(false)
                }
            }
        }
    }


    ListView.onAdd: AddAnimation {
        target: listDelegate
    }

    ListView.onRemove: RemoveAnimation {
        target: listDelegate
    }
}
