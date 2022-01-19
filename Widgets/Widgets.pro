TEMPLATE = lib
TARGET = Widgets
QT += qml quick
CONFIG += plugin c++17

# Input
SOURCES += \
        widgets_plugin.cpp

HEADERS += \
        widgets_plugin.h

DISTFILES = qmldir \
    AnenometerItemDelegate.qml \
    BaseSensorDelegate.qml \
    CompassItemDelegate.qml \
    DeviceList.qml \
    GPSItemDelegate.qml \
    GyroItemDelegate.qml \
    SensorItem.qml


# -------------------------------------------------------------------------
win32:CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/../App/release/com/dice/widgets
linux:CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/../App/release/com/dice/widgets
win32:CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/../App/debug/com/dice/widgets
linux:CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/../App/debug/com/dice/widgets
# -------------------------------------------------------------------------

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}



unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

RESOURCES += \
    res.qrc
