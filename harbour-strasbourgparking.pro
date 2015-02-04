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

CONFIG += sailfishapp

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
    rpm/harbour-strasbourgparking.changes.in \
    rpm/harbour-strasbourgparking.spec \
    rpm/harbour-strasbourgparking.yaml \
    translations/*.ts \
    harbour-strasbourgparking.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/StrasbourgParking.ts
