# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-strasbourgparking

CONFIG += sailfishapp \
    sailfishapp_i18n

HEADERS += \
    src/ParkingListModel.h \
    src/ParkingModel.h \
    src/JSONRequest.h \
    src/SortedParkingListModel.h \
    src/FavoritesStorage.h \
    src/Controller.h

SOURCES += src/StrasbourgParking.cpp \
    src/ParkingListModel.cpp \
    src/ParkingModel.cpp \
    src/JSONRequest.cpp \
    src/SortedParkingListModel.cpp \
    src/FavoritesStorage.cpp \
    src/Controller.cpp

OTHER_FILES += qml/StrasbourgParking.qml \
    qml/cover/CoverPage.qml \
    qml/components/ListDelegate.qml \
    qml/components/StatusIndicator.qml \
    qml/pages/ListPage.qml \
    qml/pragma/Helpers.js \
    rpm/$${TARGET}.changes.in \
    rpm/$${TARGET}.spec \
    rpm/$${TARGET}.yaml \
    $${TARGET}.desktop

TRANSLATIONS += translations/$${TARGET}-en_EN.ts \
                translations/$${TARGET}-fr_FR.ts
