/*
  Copyright (C) 2015 François KUBLER
  Contact: François Kubler <francois@kubler.org>
  All rights reserved.

    This file is part of StrasbourgParking.

    StrasbourgParking is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    StrasbourgParking is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../pragma/Helpers.js" as Helpers


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


    menu: contextMenu


    GlassItem {
        id: statusIndicator

        anchors {
            left: parent.left
            leftMargin: -(width / 2)
            verticalCenter: nameLabel.verticalCenter
        }
        brightness: 1.0
        color: Helpers.getColor(status) ? Helpers.getColor(status) : Theme.secondaryColor
        height: width
        width: Theme.itemSizeExtraSmall
    }

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
        text: Helpers.getName(name, isRelay)
        truncationMode: TruncationMode.Fade
    }

    Label {
        id: statusLabel

        anchors {
            baseline: nameLabel.baseline
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        color: Helpers.isOpen(status) ? (highlighted ? Theme.highlightColor : Theme.primaryColor)
                              : (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        font {
            pixelSize: Theme.fontSizeExtraSmall
        }
        horizontalAlignment: Text.AlignRight
        text: Helpers.getStatus(status)
    }

    Label {
        id: occupation

        anchors {
            left: nameLabel.left
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
