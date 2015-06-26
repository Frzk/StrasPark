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

.pragma library


/**
 * Returns the name of a parking lot.
 * The name is prefixed with "P+R" when the parking lot is a "Parking+Tramway" relay.
 *
 * @param   string  name        Name of the parking lot, as given by the JSON source.
 * @param   bool    isRelay     True if the parking lot is a relay.
 *
 * @return  string
 */
function getName(name, isRelay)
{
    return (isRelay ? "P+R " : "") + name;
}

/**
 * Returns the status of a parking lot into a human-firendly text.
 *
 * @param   string  status      Status of the parking lot, as given by the JSON source
 *                              (can be either "status_1", "status_2", "status_3" or "status_4").
 *                              (aww...and sometimes we get a "status_0" which isn't documented).
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

/**
 * Returns the color associated with the status of the parking lot.
 *
 * @param   string  status      Status of the parking lot, as given by the JSON source.
 *
 * @return  string
 */
function getColor(status)
{
    var r = "";     // Unknown/Unavailable : this should be replaced by Theme.secondaryColor in the QML file.

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
 * @param   string  status      Status of the parking lot, as given by the JSON source
 *                              (can be either "status_1", "status_2", "status_3" or "status_4").
 *
 * @return  string
 */
function isOpen(status)
{
    return status === "status_1";
}

/**
 * Returns an error string depending on the given error code.
 *
 * @param   int err     Error code
 *
 * @return  string
 */
function getErrorHintText(err)
{
    var r = "";

    switch(err)
    {
        case 0: // ParkingModel.None
            r = qsTr("Pull to refresh.");
            break;
        case 1: // ParkingModel.Networking
            r = qsTr("The source of data can't be reached.");
            break;
        case 2: // ParkingModel.Json
            r = qsTr("The data returned by the webservice can't be used.");
            break;
        default:
            r = qsTr("Unknown cause.");
            break;
    }

    return r;
}
