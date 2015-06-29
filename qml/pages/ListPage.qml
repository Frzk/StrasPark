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

import org.kubler.StrasbourgParking 1.0

import "../components"
import "../pragma/Helpers.js" as Helpers


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
        model: parkingModel
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
            running: view.count === 0 && parkingModel.status === ParkingModel.Refreshing
            size: BusyIndicatorSize.Large
        }

        PullDownMenu {
            busy: parkingModel.status === ParkingModel.Refreshing
            quickSelect: true

            MenuItem {
                enabled: parkingModel.status !== ParkingModel.Refreshing
                text: qsTr("Refresh")
                onClicked: {
                    parkingModel.triggerUpdate()
                }
            }

            MenuLabel {
                text: parkingModel.status === ParkingModel.Refreshing ? qsTr("Updating...") :
                          parkingModel.status === ParkingModel.NoError && Date.parse(parkingModel.lastUpdate) ?
                              qsTr("Updated %1").arg(Qt.formatDateTime(parkingModel.lastUpdate, Qt.DefaultLocaleShortDate)) :
                              qsTr("No data.")
            }
        }

        ViewPlaceholder {
            enabled: (parkingModel.status === ParkingModel.NetworkError) ||
                     (parkingModel.status === ParkingModel.JsonError) ||
                     (parkingModel.status === ParkingModel.NoError && view.count === 0)
            hintText: Helpers.getErrorHintText(parkingModel.status)
            text: parkingModel.status !== ParkingModel.NoError ? qsTr("An error occured :(") : qsTr("No data !")
        }

        VerticalScrollDecorator {}
    }
}
