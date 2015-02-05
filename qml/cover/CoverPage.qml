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

CoverBackground {
    id: cover


    property var current    // ListView currentItem : we get the values from it.


    CoverPlaceholder {
        text: qsTr("Add Favorites")
        visible: false
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
            text: current.parkingName
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
            text: current.parkingStatus
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
            text: current.freePlaces
        }
    }

    CoverActionList {
        id: coverAction

        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: {
                triggerUpdate();
            }
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: {
                //FIXME: cycle through favorites only.
                pageStack.currentPage.view.incrementCurrentIndex();

                console.log("currentIndex :", pageStack.currentPage.view.currentIndex);
                console.log("currentItem :", pageStack.currentPage.view.currentItem);
                console.log("current :", current);
            }
        }
    }

    /*
     * We bind values showed on the cover directly to the corresponding ListPage.view delegate.
     * This allow us to get updated values on the cover easily :
     *   A signal triggers the data update.
     *   The model is updated, and so are the ListPage.view delegates.
     *   Finally, the (bounded) values on the cover are also updated.
     */
    Binding {
        target: cover
        property: "current"
        value: pageStack.currentPage.view.currentItem
    }
}
