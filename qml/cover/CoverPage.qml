/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
