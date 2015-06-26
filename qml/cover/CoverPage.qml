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

import "../components"
import "../pragma/Helpers.js" as Helpers


CoverBackground {
    id: cover


    CoverPlaceholder {
        text: parkingModel.isRefreshing ? qsTr("Refreshing...") : qsTr("No data.")
        visible: list.count == 0
    }

    SilicaListView {
        id: list

        anchors {
            fill: parent
            leftMargin: Theme.paddingMedium
            rightMargin: Theme.paddingMedium
            topMargin: Theme.paddingLarge
        }
        delegate: Item {
            id: d

            height: nameLabel.height + Theme.paddingSmall
            width: parent.width

            Label {
                id: nameLabel

                anchors {
                    left: parent.left
                    right: freeLabel.left
                    rightMargin: Theme.paddingMedium
                }
                color: Helpers.isOpen(status) ? Theme.primaryColor : Theme.secondaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: name
                truncationMode: TruncationMode.Fade
            }
            Label {
                id: freeLabel

                anchors {
                    right: parent.right
                }
                color: Helpers.isOpen(status) ? Theme.primaryColor : Theme.secondaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: free
            }

            ListView.onAdd: AddAnimation {
                target: d
            }

            ListView.onRemove: RemoveAnimation {
                target: d
            }
        }
        model: parkingModel
    }

    // Could be nice to have an OpacityRampEffect here.

    CoverActionList {
        id: coverAction

        enabled: !parkingModel.isRefreshing

        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: {
                parkingModel.triggerUpdate();
            }
        }
    }

    onStatusChanged: {
        if(status === Cover.Activating || status === Cover.Deactivating)
            parkingModel.toggleFilter()
    }
}
