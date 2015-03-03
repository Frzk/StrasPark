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


/**
 * The following are made available through C++ (Q_PROPERTY or Q_INVOKABLE) :
 *  - parkingListModel :    the data model.
 *  - isRefreshing :        true when we are gathering the status of parking lots.
 *  - isFavorite(row) :     true if the item at given row is a Favorite.
 *  - triggerUpdate() :     call this one whenever you want to refresh the data.
 */

CoverBackground {
    id: cover


    property int currentIndex: -1
    property var current: null
    property bool refreshing: isRefreshing


    signal refresh;


    function next() {
        //FIXME
        var newIndex = -1;
        var n = currentIndex + 1;

        if(isFavorite(n))
            newIndex = n;
        else
            if(currentIndex >= 0)
                newIndex = 0;

        currentIndex = newIndex;
        refresh();
    }

    function updateCurrentIndex(row, fav) {
        //FIXME
        if(fav) // Added a new Favorite
        {
            currentIndex = 0;
        }
        else    // Removed a Favorite
        {
            if(row <= currentIndex)
            {
                if(row > 0)
                    currentIndex--;
                else
                    if(isFavorite(0))
                        currentIndex = 0;
                    else
                        currentIndex = -1;
            }
        }

        refresh();
    }

    function updateCurrent() {
        current = currentIndex >= 0 ? parkingListModel.getParking(currentIndex) : null;
    }


    CoverPlaceholder {
        text: qsTr("Mark some parking lots as Favorites.")
        visible: !current
    }

    Column
    {
        anchors {
            fill: parent
            leftMargin: Theme.paddingMedium
            rightMargin: Theme.paddingMedium
            topMargin: Theme.paddingLarge
        }
        spacing: Theme.paddingMedium

        Label {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.primaryColor
            font {
                pixelSize: Theme.fontSizeMedium
            }
            horizontalAlignment: Text.AlignHCenter
            maximumLineCount: 3
            text: current ? Helpers.getName(current.name, current.isRelay) : ""
            truncationMode: TruncationMode.Fade
            width: parent.width - ( 2 * Theme.paddingLarge) // Set a width so that wrapMode works.
            wrapMode: Text.WordWrap
        }

        Label {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            font {
                pixelSize: Theme.fontSizeSmall
            }
            horizontalAlignment: Text.AlignHCenter
            text: current ? Helpers.getStatus(current.status) : ""
        }

        Label {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.primaryColor
            font {
                pixelSize: Theme.fontSizeHuge
            }
            horizontalAlignment: Text.AlignHCenter
            text: current ? current.free : ""
        }
    }

    CoverActionList {
        id: coverAction

        enabled: current

        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: {
                triggerUpdate();
            }
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: {
                next();
            }
        }
    }

    onRefreshingChanged: {
        if(!refreshing)
            updateCurrent();
    }

    onRefresh: {
        updateCurrent();
    }

    Component.onCompleted: {
        pageStack.currentPage.view.onCountChanged.connect(next);
        parkingListModel.favoriteChanged.connect(updateCurrentIndex);
    }
}
