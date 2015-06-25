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

import "pages"

ApplicationWindow
{
    allowedOrientations: Orientation.All
    initialPage: Component { ListPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")

    ParkingModel {
        id: parkingModel
        dataSource: dataSource

        onDataSourceChanged: {
            triggerUpdate()
        }
    }

    DataSource {
        id: dataSource
    }
}
