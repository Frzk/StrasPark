import QtQuick 2.0
import Sailfish.Silica 1.0


ListItem {
    id: listDelegate


    function markAsFavorite(f)
    {
        var s = qsTr("Adding to Favorites");

        if(!f)
            s = qsTr("Removing from Favorites");

        remorseAction(s, function() {
            ListView.view.model.markAsFavorite(index, f);
        }, 3000);
    }

    /**
     * Returns the status of a parking lot into a human-firendly text.
     *
     * @param   string  status  Status of the parking lot, as given by the JSON source
     *                          (can be either "status_1", "status_2", "status_3" or "status_4").
     *
     * @return  string
     */
    function getStatus(status)
    {
        var r = qsTr("Open");

        switch(status)
        {
            case "status_2":
                r = qsTr("Full");
                break;
            case "status_3":
                r = qsTr("Unavailable");
                break;
            case "status_4":
                r = qsTr("Closed");
                break;
        }

        return r;
    }

    /**
     * Returns true if the parking is open and not full, false otherwise.
     *
     * @param   string  status  Status of the parking lot, as given by the JSON source
     *                          (can be either "status_1", "status_2", "status_3" or "status_4").
     *
     * @return  string
     */
    function isOpen(status)
    {
        return status === "status_1";
    }


    menu: contextMenu


    Image {
        id: favIcon

        anchors {
            verticalCenter: nameLabel.verticalCenter
            left: parent.left
            leftMargin: Theme.paddingLarge
        }
        //color: highlighted ? Theme.hightlightColor : Theme.primaryColor
        height: Theme.iconSizeSmall
        source: "image://theme/icon-s-favorite"
        visible: isFavorite
        width: height
    }

    Label {
        id: nameLabel

        anchors {
            left: isFavorite ? favIcon.right : parent.left
            right: statusLabel.left
            leftMargin: isFavorite ? Theme.paddingMedium : Theme.paddingLarge
            rightMargin: Theme.paddingLarge
        }
        color: isOpen(status) ? (highlighted ? Theme.highlightColor : Theme.primaryColor)
                              : (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        text: (isRelay ? "P+R " : "") + name
        truncationMode: TruncationMode.Fade
    }

    Label {
        id: statusLabel

        anchors {
            baseline: nameLabel.baseline
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        color: isOpen(status) ? (highlighted ? Theme.highlightColor : Theme.primaryColor)
                              : (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        font {
            pixelSize: Theme.fontSizeExtraSmall
        }
        horizontalAlignment: Text.AlignRight
        text: getStatus(status)
    }

    Label {
        id: occupation

        anchors {
            left: parent.left
            right: parent.right
            top: nameLabel.bottom
            leftMargin: Theme.paddingLarge
            rightMargin: Theme.paddingLarge
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
