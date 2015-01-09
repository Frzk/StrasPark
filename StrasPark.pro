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
TARGET = StrasPark

CONFIG += sailfishapp

SOURCES += src/StrasPark.cpp \
    src/ParkingListModel.cpp \
    src/ParkingModel.cpp \
    src/Storage.cpp \
    src/JSONRequest.cpp

OTHER_FILES += qml/StrasPark.qml \
    qml/cover/CoverPage.qml \
    qml/components/ListDelegate.qml \
    qml/data/database.js \
    qml/pages/ListPage.qml \
    qml/pages/AboutPage.qml \
    rpm/StrasPark.changes.in \
    rpm/StrasPark.spec \
    rpm/StrasPark.yaml \
    translations/*.ts \
    StrasPark.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/StrasPark-de.ts

HEADERS += \
    src/ParkingListModel.h \
    src/ParkingModel.h \
    src/Storage.h \
    src/JSONRequest.h

QT += \
    sql
