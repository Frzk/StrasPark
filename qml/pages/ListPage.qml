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
                text: isRefreshing ? qsTr("Updating...") : (lastUpdate ? qsTr("Updated %1").arg(Qt.formatDateTime(lastUpdate, Qt.DefaultLocaleShortDate)) : qsTr("No data."))
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
