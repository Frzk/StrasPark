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
     *                          (aww...and sometimes we get a "status_0" which isn't documented).
     *
     * @return  string
     */
    function getStatus(status)
    {
        var r = qsTr("Open");

        switch(status)
        {
            case "status_0":
                r = qsTr("Unknown");
                break;
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

    function getColor(status)
    {
        var r = Theme.secondaryColor;      // Unknown / Unavailable

        switch(status)
        {
            case "status_1":    // Open
                r = "#009900";
                break;
            case "status_2":    // Full
                r = "#990000";
                break;
            case "status_4":    // Closed
                r = "#000000";
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


    Label {
        id: nameLabel

        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: statusLabel.left
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
            right: statusIndicator.left
            rightMargin: Theme.paddingMedium
        }
        color: isOpen(status) ? (highlighted ? Theme.highlightColor : Theme.primaryColor)
                              : (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        font {
            pixelSize: Theme.fontSizeExtraSmall
        }
        horizontalAlignment: Text.AlignRight
        text: getStatus(status)
    }

    StatusIndicator {
        id: statusIndicator

        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: statusLabel.verticalCenter
        }
        color: getColor(status)
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
