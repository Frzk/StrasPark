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


/**
 * The following are made available through C++ (Q_PROPERTY or Q_INVOKABLE) :
 *  - parkingListModel :    the data model.
 *  - isRefreshing :        true when we are gathering the status of parking lots.
 *  - lastUpdate :          Date object : last successful update date and time.
 *  - triggerUpdate() :     call this one whenever you want to refresh the data.
 */

Page {
    id: page


    property alias view: view


    SilicaListView {
        id: view

        anchors {
            fill: parent
        }
        currentIndex: -1
        delegate: ListDelegate {}
        header: PageHeader {
            title: qsTr("Parking lots in Strasbourg")
        }
        keyNavigationWraps: true;
        model: parkingListModel
        section {
            criteria: ViewSection.FullString
            delegate: SectionHeader {
                text: section === "true" ? qsTr("Favorites") : qsTr("Others")
            }
            property: "isFavorite"
        }


        BusyIndicator {
            id: busyIndicator

            anchors.centerIn: parent
            running: view.count==0 && isRefreshing
            size: BusyIndicatorSize.Large
        }

        PullDownMenu {
            busy: isRefreshing
            quickSelect: true

            MenuItem {
                enabled: !isRefreshing
                text: qsTr("Refresh")
                onClicked: triggerUpdate()
            }

            MenuLabel {
                text: isRefreshing ? qsTr("Updating...") : (lastUpdate ? qsTr("Updated %1").arg(Qt.formatDateTime(lastUpdate)) : qsTr("No data."))
            }
        }

        ViewPlaceholder {
            enabled: view.count == 0 && !isRefreshing
            hintText: qsTr("Pull to refresh.")
            text: qsTr("No data !")
        }

        VerticalScrollDecorator {}
    }
}
