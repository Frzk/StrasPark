import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: indicator

    property int orientation: Qt.Horizontal

    height: orientation === Qt.Horizontal ? Theme.paddingSmall : Theme.paddingLarge
    radius: Theme.paddingSmall / 2
    width: orientation === Qt.Horizontal ? Theme.paddingLarge : Theme.paddingSmall
}
