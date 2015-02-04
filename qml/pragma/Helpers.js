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
