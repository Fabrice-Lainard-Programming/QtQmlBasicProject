
QT += quick

CONFIG += c++17

# -------------------------------------------------------------------------
win32:CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
linux:CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
win32:CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug
linux:CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug
# -------------------------------------------------------------------------

SOURCES += \
        Application.cpp \
        MockServer.cpp \
        main.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    App_en_US.ts

LIBS += -L$$DESTDIR/com/dice/widgets -lWidgets
LIBS += -L$$DESTDIR/com/dice/widgets -lWidgets


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DataModel/release/ -lDataModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DataModel/debug/ -lDataModel
else:unix: LIBS += -L$$OUT_PWD/../DataModel/ -lDataModel

INCLUDEPATH += $$PWD/../DataModel
DEPENDPATH += $$PWD/../DataModel

QML_IMPORT_PATH += $$OUT_PWD/com/dice/widgets


INCLUDEPATH += $$PWD\..

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Application.h \
    MockServer.h
